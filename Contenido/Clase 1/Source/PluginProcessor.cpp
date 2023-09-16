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
                       )
#endif
{
}

ProyectoECTCursoAudioProcessor::~ProyectoECTCursoAudioProcessor() {}

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
