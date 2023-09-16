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

void ProyectoECTCursoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {}

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

    float volValue = apvts.getRawParameterValue ("Volume")->load();
    float panValue = apvts.getRawParameterValue ("Pan")->load();
    
    paneoObject.process   (buffer, panValue);
    volumenObject.process (buffer, volValue);
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
