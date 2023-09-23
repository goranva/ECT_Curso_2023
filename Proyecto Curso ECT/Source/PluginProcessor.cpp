/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#define PI juce::MathConstants<float>::pi

//==============================================================================
ProyectoCursoECTAudioProcessor::ProyectoCursoECTAudioProcessor()
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

ProyectoCursoECTAudioProcessor::~ProyectoCursoECTAudioProcessor()
{
}

//==============================================================================
const juce::String ProyectoCursoECTAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ProyectoCursoECTAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ProyectoCursoECTAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ProyectoCursoECTAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ProyectoCursoECTAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ProyectoCursoECTAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ProyectoCursoECTAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ProyectoCursoECTAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ProyectoCursoECTAudioProcessor::getProgramName (int index)
{
    return {};
}

void ProyectoCursoECTAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ProyectoCursoECTAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    AM.prepare(sampleRate);
}

void ProyectoCursoECTAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ProyectoCursoECTAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void ProyectoCursoECTAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    //juce::ScopedNoDenormals noDenormals;
    //auto totalNumInputChannels  = getTotalNumInputChannels();
    //auto totalNumOutputChannels = getTotalNumOutputChannels();

    //float inputGainValue = apvts.getRawParameterValue("Volume")->load();

    float inputGainValue = *apvts.getRawParameterValue("Volume");

    float inputPanValue = *apvts.getRawParameterValue("Panning");

    float inputRateValue = *apvts.getRawParameterValue("Rate");

    float inputDryWetValue = *apvts.getRawParameterValue("DryWet");

    dryBuffer.makeCopyOf(buffer);

    gain.process(buffer, inputGainValue);
    pan.process(buffer, inputPanValue);
    AM.process(buffer, inputRateValue);
    dryWet.process(dryBuffer, buffer, inputDryWetValue);
}

//==============================================================================
bool ProyectoCursoECTAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ProyectoCursoECTAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor(*this);
    // return new ProyectoCursoECTAudioProcessorEditor (*this);
}

//==============================================================================
void ProyectoCursoECTAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ProyectoCursoECTAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::AudioProcessorValueTreeState::ParameterLayout ProyectoCursoECTAudioProcessor::createParameters()
{
    juce::AudioProcessorValueTreeState::ParameterLayout parameters;

    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "SliderFloat", 1 }, "SliderFloat", 0.0f, 100.0f, 50.0f));

    parameters.add(std::make_unique<juce::AudioParameterInt>(juce::ParameterID{ "SliderInt", 1 }, "SliderInt", 0, 100, 80));

    parameters.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ "Button", 1 }, "Button", false));

    parameters.add(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{ "Options", 1 }, "Options", juce::StringArray{ "1/2", "1/4", "1/8", "1/16" }, 0));

    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "Volume", 1 }, "Volume", 0.0f, 2.0f, 1.0f));

    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "Panning", 1 }, "Panning", 0.0f, PI / 2.0f, PI / 4.0f));

    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "Rate", 1 }, "Rate", 0.01f, 20.0f, 1.0f));

    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "DryWet", 1 }, "DryWet", 0.0f, 100.0f, 50.0f));

    return parameters;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ProyectoCursoECTAudioProcessor();
}
