#include "Paneo.h"

Paneo::Paneo() {}

Paneo::~Paneo() {}

void Paneo::process (juce::AudioBuffer<float>& buffer, float panValue)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // Get sample
            float sample = buffer.getSample (channel, i);
            
            // Left channel
            if (channel == 0)
            {
                sample *= sqrtf (((PI/2.0f)-panValue) * (2.0f/PI) * cosf (panValue));
                buffer.setSample (channel, i, sample);
            }
            
            // Right channel
            else
            {
                sample *= sqrtf (panValue * (2.0f/PI) * sinf (panValue));
                buffer.setSample (channel, i, sample);
            }
        }
    }
}
