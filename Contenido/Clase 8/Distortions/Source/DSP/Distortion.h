/*
  ==============================================================================

    Distortion.h
    Created: 21 Oct 2022 10:07:56pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <cmath>

class Distorion
{
public:
    void setGain (float inGain);
    void setDistortion (int inDistortionIndex);
    
    float softClipping (float inSample);
    float hardClipping (float inSample);
    float bitCrusher (float inSample);
    
    void process (juce::AudioBuffer<float>& inBuffer);

private:
    int distortionIndex { 0 };
    float distortionGain { 1.0f };
};

