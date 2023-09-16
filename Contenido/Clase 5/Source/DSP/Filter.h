#pragma once
#include <JuceHeader.h>

class Filter
{
public:
    
    Filter();
    
    ~Filter();
    
    void prepare (juce::dsp::ProcessSpec& inSpec);
    
    void processBandPass (juce::AudioBuffer<float>& buffer);
    
    void processHighPass (juce::AudioBuffer<float>& buffer);
    
    void processLowPass (juce::AudioBuffer<float>& buffer);
    
private:
    
    std::array<juce::dsp::IIR::Filter<float>, 2> bandpassFilter;
    typename juce::dsp::IIR::Coefficients<float>::Ptr bandpassFilterCoefficients;
    
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> highpassFilter;
    
    juce::dsp::StateVariableTPTFilter<float> lowpassFilter;
};
