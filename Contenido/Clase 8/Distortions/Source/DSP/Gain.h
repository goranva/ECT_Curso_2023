/*
  ==============================================================================

    Gain.h
    Created: 21 Oct 2022 10:07:26pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Gain
{
public:
    void setGain (float inGain);
    void process (juce::AudioBuffer<float>& inBuffer);
private:
    float gainValue { 1.0f };
};

