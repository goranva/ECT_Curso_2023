/*
  ==============================================================================

    Volume.h
    Created: 16 Sep 2023 10:32:21am
    Author:  rod_f

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Volume
{
public:
	Volume();
	~Volume();

    void process(juce::AudioBuffer<float>& buffer, float gainValue);

private:

};
