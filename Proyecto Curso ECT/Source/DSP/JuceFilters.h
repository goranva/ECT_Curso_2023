/*
  ==============================================================================

    JuceFilters.h
    Created: 14 Oct 2023 1:53:53am
    Author:  Drogui

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class JuceFilter 
{
 public:
  JuceFilter();
  ~JuceFilter();

      void prepare(juce::dsp::ProcessSpec& specs);

      void processBandPass(juce::AudioBuffer<float>& buffer);
      void processHighPass(juce::AudioBuffer<float>& buffer);
      void processLowPass(juce::AudioBuffer<float>& buffer);

  private:
  std::array<juce::dsp::IIR::Filter<float>, 2> bandpassFilter;

  typename juce::dsp::IIR::Coefficients<float>::Ptr bandpassFilterCoefficients;

  juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> highpassFilter;

  juce::dsp::StateVariableTPTFilter<float> lowpassFilter;
};
