#pragma once
#include <JuceHeader.h>

class LFO
{
    public:
    
        LFO();
    
        ~LFO();
    
        void prepare (double inSampleRate);
    
        void process (juce::AudioBuffer<float>& buffer, float rateValue);
    
    private:
    
        float sampleRate { 0.0f };
        
        float PI = juce::MathConstants<float>::pi;
    
        float fase[2] { 0.0f };
};
