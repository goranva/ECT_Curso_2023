/*
  ==============================================================================

    Modulator.cpp
    Created: 23 Sep 2023 10:08:13am
    Author:  rod_f

  ==============================================================================
*/

#include "Modulator.h"


Modulator::Modulator()
{
}

Modulator::~Modulator()
{
}

void Modulator::prepare(double inSampleRate)
{
    sampleRate = static_cast<float> (inSampleRate);

    for (int channel = 0; channel < 2; channel++) 
    {
      time[channel] = 0.0f;
      deltaTime[channel] = 1.0f / sampleRate;
    }
}

void Modulator::process(juce::AudioBuffer<float>& buffer, float rateValue)
{
    // Bypass:
    if (rateValue <= 0.01f)
    {
        return;
    }

    frequency = rateValue;

    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float sample = buffer.getSample(channel, i);

            // If comparisons:
            float sinValue = sineWave(channel);

            buffer.setSample(channel, i, sample * sinValue);
            
            time[channel] += deltaTime[channel];
        }
    }
}

float Modulator::sineWave(int channel) 
{
    return 0.5f + (0.5f * sinf(juce::MathConstants<float>::twoPi * frequency * time[channel]));
}

float Modulator::squareWave(int channel) {
    float fullPeriodTime = 1.0f / frequency;
    float halfPeriodTime = fullPeriodTime / 2.0f;
    float localTime = fmod(time[channel], fullPeriodTime);

    if (localTime < halfPeriodTime)
        return 1.0f;
    else
        return 0.0f;
}

float Modulator::triangleWave(int channel) {
    float res = 0.0f;
    float fullPeriodTime = 1.0f / frequency;
    float localTime = fmod(time[channel], fullPeriodTime);

    float value = localTime / fullPeriodTime;

    if (value < 0.25f) {
        res = value * 4.0f;
    } else if (value < 0.75f) {
        res = 2.0f - (value * 4.0f);
    } else {
        res = value * 4.0f - 4.0f;
    }

    return res;
}

float Modulator::sawtoothWave(int channel) {
    float fullPeriodTime = 1.0f / frequency;
    float localTime = fmod(time[channel], fullPeriodTime);

    return (localTime / fullPeriodTime) * 2.0f - 1.0f;
}
