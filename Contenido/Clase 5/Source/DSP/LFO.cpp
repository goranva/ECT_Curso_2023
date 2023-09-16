#include "LFO.h"

LFO::LFO() {}

LFO::~LFO() {}

void LFO::prepare (double inSampleRate)
{
    sampleRate = static_cast<float> (inSampleRate);
}

void LFO::process (juce::AudioBuffer<float>& buffer, float rateValue)
{
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float sample = buffer.getSample (channel, i);
            
            float sinValue = (0.5f * sinf(2.0f * PI * fase[channel])) + 0.5f;
            
            buffer.setSample (channel, i, sample * sinValue);
            
            fase[channel] += rateValue * (1.0f / sampleRate);
            
            if (fase[channel] >= 1.0f)
                fase[channel] = 0.0f;
        }
    }
}
