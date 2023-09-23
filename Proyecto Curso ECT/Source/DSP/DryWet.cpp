/*
  ==============================================================================

    DryWet.cpp
    Created: 23 Sep 2023 10:53:18am
    Author:  rod_f

  ==============================================================================
*/

#include "DryWet.h"


DryWet::DryWet()
{

}

DryWet::~DryWet()
{

}

void DryWet::process(juce::AudioBuffer<float>& dryBuffer, juce::AudioBuffer<float>& wetBuffer, float dryWetValue)
{
    dryWetValue /= 100.0f;

    for (int channel = 0; channel < wetBuffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < wetBuffer.getNumSamples(); i++)
        {
            float drySample = dryBuffer.getSample(channel, i);

            float wetSample = wetBuffer.getSample(channel, i);

            float out = drySample * (1.0f - dryWetValue) + (dryWetValue * wetSample);

            wetBuffer.setSample(channel, i, out);
        }
    }
}
