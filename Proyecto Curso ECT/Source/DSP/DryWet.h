/*
  ==============================================================================

    DryWet.h
    Created: 23 Sep 2023 10:53:18am
    Author:  rod_f

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DryWet
{
public:
	DryWet();
	~DryWet();

    void process(juce::AudioBuffer<float>& dryBuffer, juce::AudioBuffer<float>& wetBuffer, float dryWetValue);

private:

};
