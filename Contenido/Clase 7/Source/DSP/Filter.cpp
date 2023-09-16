#include "Filter.h"

Filter::Filter() {}

Filter::~Filter() {}

void Filter::prepare (juce::dsp::ProcessSpec& inSpec)
{
    // BandPass
    bandpassFilterCoefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass (inSpec.sampleRate, 1000.0f);
    
    for (auto& filter : bandpassFilter)
    {
        filter.prepare (inSpec);
        filter.coefficients = bandpassFilterCoefficients;
    }
    
    // HighPass
    highpassFilter.prepare (inSpec);
    *highpassFilter.state = juce::dsp::IIR::ArrayCoefficients<float>::makeHighPass (inSpec.sampleRate, 1000.0f);
    
    // LowPass
    lowpassFilter.prepare (inSpec);
    lowpassFilter.setType (juce::dsp::StateVariableTPTFilterType::lowpass);
    lowpassFilter.setCutoffFrequency (500.0f);
}

void Filter::processBandPass (juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        for (int n = 0; n < buffer.getNumSamples(); ++n)
        {
            auto sample = buffer.getSample (channel, n);
            
            auto out = bandpassFilter[channel].processSample (sample);
            
            buffer.setSample(channel, n, out);
        }
    }
}

void Filter::processHighPass (juce::AudioBuffer<float>& buffer)
{
    auto audioBlock = juce::dsp::AudioBlock<float> (buffer);
    auto context = juce::dsp::ProcessContextReplacing<float> (audioBlock);
    highpassFilter.process (context);
}

void Filter::processLowPass (juce::AudioBuffer<float>& buffer)
{
    auto audioBlock = juce::dsp::AudioBlock<float> (buffer);
    auto context = juce::dsp::ProcessContextReplacing<float> (audioBlock);
    lowpassFilter.process (context);
}
