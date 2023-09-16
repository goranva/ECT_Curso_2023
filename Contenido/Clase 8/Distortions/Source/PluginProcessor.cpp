/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DemoDistortionsAudioProcessor::DemoDistortionsAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
}

DemoDistortionsAudioProcessor::~DemoDistortionsAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout DemoDistortionsAudioProcessor::createParameters()
{
    juce::AudioProcessorValueTreeState::ParameterLayout params;
    
    params.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("PreGain", 1), "PreGain", 0.0f, 5.0f, 1.0f));
    params.add (std::make_unique<juce::AudioParameterChoice>(juce::ParameterID { "Distortion", 1 },
                                                             "Distortion",
                                                             juce::StringArray{"Soft Clipping", "Hard Clipping", "BitCrusher"},
                                                             0));
    params.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Gain", 1), "Gain", 0.0f, 5.0f, 1.0f));
    params.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("OutGain", 1), "OutGain", 0.0f, 5.0f, 1.0f));

    return params;
}

//==============================================================================
const juce::String DemoDistortionsAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DemoDistortionsAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DemoDistortionsAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DemoDistortionsAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DemoDistortionsAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DemoDistortionsAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DemoDistortionsAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DemoDistortionsAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DemoDistortionsAudioProcessor::getProgramName (int index)
{
    return {};
}

void DemoDistortionsAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DemoDistortionsAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DemoDistortionsAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DemoDistortionsAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DemoDistortionsAudioProcessor::updateParameters()
{
    auto preGainValue = apvts.getRawParameterValue ("PreGain") -> load();
    auto gainValue = apvts.getRawParameterValue ("Gain") -> load();
    auto distortionIndex = apvts.getRawParameterValue ("Distortion") -> load();
    auto outGainValue = apvts.getRawParameterValue ("OutGain") -> load();
    
    preGain.setGain (preGainValue);
    distortion.setDistortion(distortionIndex);
    distortion.setGain (gainValue);
    outGain.setGain (outGainValue);
}

void DemoDistortionsAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    updateParameters();
    
    preGain.process (buffer);
    distortion.process (buffer);
    outGain.process (buffer);
}

//==============================================================================
bool DemoDistortionsAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DemoDistortionsAudioProcessor::createEditor()
{
    //return new DemoDistortionsAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void DemoDistortionsAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DemoDistortionsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DemoDistortionsAudioProcessor();
}
