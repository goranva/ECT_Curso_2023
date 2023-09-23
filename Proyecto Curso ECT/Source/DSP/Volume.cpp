/*
  ==============================================================================

    Volume.cpp
    Created: 16 Sep 2023 10:32:21am
    Author:  rod_f

  ==============================================================================
*/

#include "Volume.h"


Volume::Volume()
{

}

Volume::~Volume()
{

}

void Volume::process(juce::AudioBuffer<float>& buffer, float gainValue)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float sample = buffer.getSample(channel, i);

            float processedSample = sample * gainValue;

            buffer.setSample(channel, i, processedSample);
        }
    }
}
