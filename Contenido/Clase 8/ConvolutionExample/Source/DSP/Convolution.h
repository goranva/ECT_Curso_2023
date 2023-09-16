/*
  ==============================================================================

    Convolution.h
    Created: 22 Apr 2023 12:41:32pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Convolution
{
public:

    Convolution();
    ~Convolution();

    void prepare(double inSampleRate, int inSamplesPerBlock, int inNumChannels);

    void process(juce::AudioBuffer<float> inBuffer);

private:
    juce::dsp::Convolution conv;
};
