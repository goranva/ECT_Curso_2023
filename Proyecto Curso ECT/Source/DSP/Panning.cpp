/*
  ==============================================================================

    Panning.cpp
    Created: 23 Sep 2023 9:25:46am
    Author:  rod_f

  ==============================================================================
*/

#include "Panning.h"

Panning::Panning()
{

}

Panning::~Panning()
{

}

void Panning::process(juce::AudioBuffer<float>& buffer, float panValue)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float sample = buffer.getSample(channel, i);

            if (channel == 0)
            {
                // Left Processing
                sample *= (sqrtf(((PI / 2.0f) - panValue) * (2.0f / PI) * (cosf(panValue))));
            }
            else
            {
                // Right Processing
                sample *= sqrtf(panValue * (2.0f / PI) * (sinf(panValue)));
            }

            buffer.setSample(channel, i, sample);
        }
    }
}
