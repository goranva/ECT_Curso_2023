#pragma once
#include <JuceHeader.h>

class DryWet
{
public:
    
    DryWet();
    
    ~DryWet();
    
    void process (juce::AudioBuffer<float>& dryBuffer,
                  juce::AudioBuffer<float>& wetBuffer,
                  float drywetValue);
    
};
