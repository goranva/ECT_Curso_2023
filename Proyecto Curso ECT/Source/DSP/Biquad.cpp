/*
  ==============================================================================

    Biquad.cpp
    Created: 14 Oct 2023 12:53:07am
    Author:  Drogui

  ==============================================================================
*/

#include "Biquad.h"

LPF_Biquad::LPF_Biquad() {}

LPF_Biquad::~LPF_Biquad() {}

void LPF_Biquad::prepare(double inSampleRate) 
{
  sampleRate = inSampleRate;
  updateFilter();
}

void LPF_Biquad::process(juce::AudioBuffer<float>& inBuffer) 
{
  for (int channel = 0; channel < inBuffer.getNumChannels(); channel++) 
  {
    for (int i = 0; i < inBuffer.getNumSamples(); i++) 
    {
      float sample = inBuffer.getSample(channel, i);

      float sampleOut = processSample(sample, channel);

      inBuffer.setSample(channel, i, sampleOut);
    }
  }
}

float LPF_Biquad::processSample(float inSample, int channel) 
{
  auto y = (b0 / a0) * inSample + (b1 / a0) * x1[channel] +
           (b2 / a0) * x2[channel] + (-a1 / a0) * y1[channel] +
           (-a2 / a0) * y2[channel];

  x2[channel] = x1[channel];
  x1[channel] = inSample;
  y2[channel] = y1[channel];
  y1[channel] = y;

  return y;
}

void LPF_Biquad::setFrequency(float inFrequency) 
{
  frequency = inFrequency;
  updateFilter();
}

void LPF_Biquad::setQ(float inQ) 
{
  Q = inQ;
  updateFilter();
}

void LPF_Biquad::updateFilter() 
{
  w0 = (juce::MathConstants<float>::twoPi * frequency) /
       static_cast<float>(sampleRate);
  alpha = sinf(w0) / (2.0f * Q);

  b0 = (1.0f - cosf(w0)) / 2.0f;
  b1 = 1.0f - cosf(w0);
  b2 = (1.0f - cosf(w0)) / 2.0f;

  a0 = 1.0f + alpha;
  a1 = -2.0f * cosf(w0);
  a2 = 1.0f - alpha;
}
