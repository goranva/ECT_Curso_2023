#include "DryWet.h"

DryWet::DryWet() {}

DryWet::~DryWet() {}

void DryWet::process (juce::AudioBuffer<float>& dryBuffer,
                      juce::AudioBuffer<float>& wetBuffer,
                      float drywetValue)
{
    drywetValue = drywetValue / 100.0f;
    
    for (int channel = 0; channel < dryBuffer.getNumChannels(); ++channel)
    {
        for (int i = 0; i < dryBuffer.getNumSamples(); i++)
        {
            float wet = wetBuffer.getSample (channel, i);
            float dry = dryBuffer.getSample (channel, i);
            float out = dry * (1.0f - drywetValue) + (drywetValue * wet);
            
            wetBuffer.setSample (channel, i, out);
        }
    }
}
