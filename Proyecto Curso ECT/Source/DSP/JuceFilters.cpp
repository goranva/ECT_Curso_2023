/*
  ==============================================================================

    JuceFilters.cpp
    Created: 14 Oct 2023 1:53:53am
    Author:  Drogui

  ==============================================================================
*/

#include "JuceFilters.h"

JuceFilter::JuceFilter() {}

JuceFilter::~JuceFilter() {}

void JuceFilter::prepare(juce::dsp::ProcessSpec& specs) 
{
  // Bandpass Filter
  bandpassFilterCoefficients =
      juce::dsp::IIR::Coefficients<float>::makeBandPass(specs.sampleRate,
                                                        1000.0f);

  for (auto& filter : bandpassFilter) 
  {
    filter.prepare(specs);
    filter.coefficients = bandpassFilterCoefficients;
  }

  // Highpass Filter:
  highpassFilter.prepare(specs);
  *highpassFilter.state =
      juce::dsp::IIR::ArrayCoefficients<float>::makeHighPass(specs.sampleRate,
                                                             1000.0f);

  // Lowpass Filter:
  lowpassFilter.prepare(specs);
  lowpassFilter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
  lowpassFilter.setCutoffFrequency(1000.0f);
}

// Slow implementation method:
void JuceFilter::processBandPass(juce::AudioBuffer<float>& buffer) 
{
  for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
    for (int n = 0; n < buffer.getNumSamples(); ++n) {
      auto sample = buffer.getSample(channel, n);

      auto outSample = bandpassFilter[channel].processSample(sample);

      buffer.setSample(channel, n, outSample);
    }
  }
}

// Quick implementation methods:
void JuceFilter::processHighPass(juce::AudioBuffer<float>& buffer) 
{
  auto audioBlock = juce::dsp::AudioBlock<float>(buffer);
  auto context = juce::dsp::ProcessContextReplacing<float>(audioBlock);
  highpassFilter.process(context);
}

void JuceFilter::processLowPass(juce::AudioBuffer<float>& buffer) 
{
  auto audioBlock = juce::dsp::AudioBlock<float>(buffer);
  auto context = juce::dsp::ProcessContextReplacing<float>(audioBlock);
  lowpassFilter.process(context);
}