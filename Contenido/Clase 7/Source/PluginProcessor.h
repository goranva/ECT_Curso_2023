#pragma once
#include <JuceHeader.h>
#include "./DSP/Volumen.h"
#include "./DSP/Paneo.h"
#include "./DSP/LFO.h"
#include "./DSP/DryWet.h"
#include "./DSP/Filter.h"
#include "./DSP/Biquad.h"

class ProyectoECTCursoAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    
    ProyectoECTCursoAudioProcessor();
    ~ProyectoECTCursoAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    juce::AudioProcessorValueTreeState apvts;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    
    juce::AudioBuffer<float> dryBuffer;

private:
    
    Volumen volumenObject;
    Paneo paneoObject;
    LFO lfoObject;
    DryWet dryWetObject;
    Filter bandPassFilter;
    Filter lowPassFilter;
    Filter highPassFilter;
    LPF_Biquad lowpassFilterBiquad;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProyectoECTCursoAudioProcessor)
};
