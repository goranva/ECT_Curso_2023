/*
  ==============================================================================

    Convolution.cpp
    Created: 22 Apr 2023 12:41:32pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#include "Convolution.h"

Convolution::Convolution() {}
Convolution::~Convolution() {}

void Convolution::prepare(double inSampleRate, int inSamplesPerBlock, int inNumChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerBlock;
    spec.numChannels = inNumChannels;
    
    // start convolution
    conv.reset();
    conv.prepare(spec);
    
    // Load IR from binary data
    conv.loadImpulseResponse(BinaryData::_1_Halls_01_Large_Hall__MtoS_wav,
                             BinaryData::_1_Halls_01_Large_Hall__MtoS_wavSize,
                             juce::dsp::Convolution::Stereo::yes,
                             juce::dsp::Convolution::Trim::yes,
                             0,
                             juce::dsp::Convolution::Normalise::yes);
}

void Convolution::process(juce::AudioBuffer<float> inBuffer)
{
    juce::dsp::AudioBlock<float> block(inBuffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    conv.process(context);
}
