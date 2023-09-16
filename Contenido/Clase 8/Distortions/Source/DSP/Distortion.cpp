/*
  ==============================================================================

    Distortion.cpp
    Created: 21 Oct 2022 10:07:56pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#include "Distortion.h"

void Distorion::setGain (float inGain)
{
    distortionGain = inGain;
    //DBG("Dist updated" + juce::String(distortionGain));
}

void Distorion::setDistortion (int inDistortionIndex)
{
    distortionIndex = inDistortionIndex;
}

float Distorion::softClipping (float inSample)
{
    float gainSample = distortionGain * inSample;
    return (gainSample) - ( powf(gainSample, 3.0f) / 3.0f) ;
}

float Distorion::hardClipping (float inSample)
{
    float threshold = 0.55f;
    float gainSample = distortionGain * inSample;
    
    if (gainSample > threshold)
    {
        return threshold;
    }
    
    if (gainSample < -threshold)
    {
        return -threshold;
    }
    
    return gainSample;
}

float Distorion::bitCrusher(float inSample)
{
    int BitDepth = 4;
    int max = powf(2, BitDepth) - 1;
    float bitCrushSample = round((inSample + 1.0) * max) / max - 1.0;
    return bitCrushSample;
}


void Distorion::process (juce::AudioBuffer<float> &inBuffer)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < inBuffer.getNumSamples();  i++)
        {
            auto sample = inBuffer.getSample (channel, i);
            float processedSample;
            
            switch (distortionIndex)
            {
                case 0:
                    processedSample = softClipping (sample);
                    break;
                
                case 1:
                    processedSample = hardClipping (sample);
                    break;
                    
                case 2:
                    processedSample = bitCrusher (sample);
                    break;
                    
                default:
                    processedSample = sample;
                    break;
            }
            
            inBuffer.setSample (channel, i, processedSample);
        }
    }
}
