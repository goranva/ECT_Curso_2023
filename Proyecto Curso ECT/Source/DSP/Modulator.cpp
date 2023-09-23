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
    sampleRate = (float)inSampleRate;
}

void Modulator::process(juce::AudioBuffer<float>& buffer, float rateValue)
{
    // Bypass:
    if (rateValue <= 0.01f)
    {
        return;
    }

    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float sample = buffer.getSample(channel, i);

            float sinValue = (0.5f * sinf (2.0f * PI * x[channel])) + 0.5f;

            buffer.setSample(channel, i, sample * sinValue);

            x[channel] += rateValue * (1.0f / sampleRate);

            if (x[channel] >= 1.0f)
            {
                x[channel] = 0.0f;
            }
        }
    }
}
