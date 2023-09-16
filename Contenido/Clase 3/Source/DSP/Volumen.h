#pragma once
#include <JuceHeader.h>

class Volumen
{
    public:
    
        Volumen();
        
        ~Volumen();
    
        void process (juce::AudioBuffer<float>& buffer, float volumenValue);
        
        
    
};
