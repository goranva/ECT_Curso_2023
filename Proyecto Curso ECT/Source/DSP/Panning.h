/*
  ==============================================================================

    Panning.h
    Created: 23 Sep 2023 9:25:46am
    Author:  rod_f

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#define PI juce::MathConstants<float>::pi

class Panning
{
public:
    Panning();
    ~Panning();

    void process(juce::AudioBuffer<float>& buffer, float panValue);

private:

};
