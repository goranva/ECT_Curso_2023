#include "PluginProcessor.h"
#include "PluginEditor.h"

ProyectoECTCursoAudioProcessor::ProyectoECTCursoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, nullptr, "Parameters", createParameters())
#endif
{
}

ProyectoECTCursoAudioProcessor::~ProyectoECTCursoAudioProcessor() {}

juce::AudioProcessorValueTreeState::ParameterLayout ProyectoECTCursoAudioProcessor::createParameters()
{
    float PI = juce::MathConstants<float>::pi;
    juce::AudioProcessorValueTreeState::ParameterLayout parameters;
    
    parameters.add (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Volume", 1), "Volume", 0.0f, 1.0f, 1.0f));
    
    parameters.add (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Pan", 1), "Pan", 0.0f, PI/2.0f, PI/4.0f));
    
    parameters.add (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Rate", 1), "Rate", 0.1f, 20.0f, 1.0f));
    
    parameters.add (std::make_unique<juce::AudioParameterBool>(juce::ParameterID("LFOState", 1), "LFOState", true));
    
    parameters.add (std::make_unique<juce::AudioParameterChoice>(juce::ParameterID("LFOChoice", 1), "LFOChoice",
                                                                 juce::StringArray("Sine", "Square", "Saw", "Triangle"), 0));
    
    parameters.add (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("LowFreq", 1), "LowFreq", 20.0f, 20000.0f, 1000.0f));
    
    parameters.add (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("HighFreq", 1), "HighFreq", 20.0f, 20000.0f, 1000.0f));
    
    parameters.add (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("DryWet", 1), "DryWet", 0.0f, 100.0f, 100.0f));
    
    return parameters;
}

const juce::String ProyectoECTCursoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ProyectoECTCursoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ProyectoECTCursoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ProyectoECTCursoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ProyectoECTCursoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ProyectoECTCursoAudioProcessor::getNumPrograms()
{
    return 1;
}

int ProyectoECTCursoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ProyectoECTCursoAudioProcessor::setCurrentProgram (int index) {}

const juce::String ProyectoECTCursoAudioProcessor::getProgramName (int index)
{
    return {};
}

void ProyectoECTCursoAudioProcessor::changeProgramName (int index, const juce::String& newName) {}

void ProyectoECTCursoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // LFO
    lfoObject.prepare (sampleRate);
    
    // Filters
    juce::dsp::ProcessSpec spec;
    spec.sampleRate       = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels      = getTotalNumOutputChannels();
    
    bandPassFilter.prepare (spec);
    lowPassFilter.prepare  (spec);
    highPassFilter.prepare (spec);
    
    // Biquad
    lowpassFilterBiquad.prepare      (sampleRate);
    lowpassFilterBiquad.setFrequency (1000.0f);
    lowpassFilterBiquad.setQ         (0.71f);
}

void ProyectoECTCursoAudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ProyectoECTCursoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif
    return true;
  #endif
}
#endif

void ProyectoECTCursoAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    dryBuffer.makeCopyOf (buffer);

    float volValue     = apvts.getRawParameterValue ("Volume")->load();
    float panValue     = apvts.getRawParameterValue ("Pan")->load();
    float lfoState     = apvts.getRawParameterValue ("LFOState")->load();
    float rateValue     = apvts.getRawParameterValue ("Rate")->load();
    float lowFreqValue = apvts.getRawParameterValue ("LowFreq")->load();
    float dryWetValue  = apvts.getRawParameterValue ("DryWet")->load();
    
    paneoObject.process   (buffer, panValue);
    volumenObject.process (buffer, volValue);
    
    if (lfoState)
        lfoObject.process (buffer, rateValue);
    
    // Filter
    //bandPassFilter.processBandPass (buffer);
    //highPassFilter.processHighPass (buffer);
    //lowPassFilter.processLowPass   (buffer);
    lowpassFilterBiquad.setFrequency (lowFreqValue);
    lowpassFilterBiquad.process (buffer);
    
    dryWetObject.process  (dryBuffer, buffer, dryWetValue);
}

bool ProyectoECTCursoAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* ProyectoECTCursoAudioProcessor::createEditor()
{
    return new ProyectoECTCursoAudioProcessorEditor (*this);
}

void ProyectoECTCursoAudioProcessor::getStateInformation (juce::MemoryBlock& destData) {}

void ProyectoECTCursoAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ProyectoECTCursoAudioProcessor();
}
