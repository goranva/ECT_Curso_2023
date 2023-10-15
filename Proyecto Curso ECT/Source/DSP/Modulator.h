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

    float sineWave(int channel);

    float squareWave(int channel);

    float triangleWave(int channel);

    float sawtoothWave(int channel);

private:

    float sampleRate = 0.0f;

    float time[2];
    float deltaTime[2];
    float frequency;
};
