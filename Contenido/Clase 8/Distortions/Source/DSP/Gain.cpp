/*
  ==============================================================================

    Gain.cpp
    Created: 21 Oct 2022 10:07:26pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#include "Gain.h"

void Gain::setGain (float inGain)
{
    gainValue = inGain;
}

void Gain::process (juce::AudioBuffer<float> &inBuffer)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < inBuffer.getNumSamples();  i++)
        {
            auto sample = inBuffer.getSample (channel, i);
            inBuffer.setSample(channel, i, gainValue * sample);
        }
    }
}
