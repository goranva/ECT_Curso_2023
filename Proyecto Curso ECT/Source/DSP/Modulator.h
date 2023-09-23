/*
  ==============================================================================

    Modulator.h
    Created: 23 Sep 2023 10:08:13am
    Author:  rod_f

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#define PI juce::MathConstants<float>::pi

class Modulator
{
public:
    Modulator();
	~Modulator();

    void prepare(double inSampleRate);

    void process(juce::AudioBuffer<float>& buffer, float rateValue);

private:

    float sampleRate = 0.0f;

    float x[2] { 0.0f };
};
