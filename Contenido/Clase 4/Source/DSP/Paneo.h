#pragma once
#include <JuceHeader.h>

class Paneo
{
    public:
    
        Paneo();
    
        ~Paneo();
    
        void process (juce::AudioBuffer<float>& buffer, float panValue);
    
    private:
    
        float PI = juce::MathConstants<float>::pi;

};
