/*
  ==============================================================================

    LookAndFeel.h
    Created: 14 Oct 2023 4:07:41am
    Author:  Drogui

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class LookAndFeel : public juce::LookAndFeel_V4
{
 public:
     LookAndFeel()
     { 
         /*knobImage = juce::ImageCache::getFromMemory(BinaryData::knob_png,
                                                   BinaryData::knob_pngSize);*/

         setColour(juce::Slider::ColourIds::thumbColourId,
                 juce::Colours::white);
         setColour(juce::Slider::ColourIds::rotarySliderFillColourId,
                 juce::Colours::green);
     }

     ~LookAndFeel()
     {

     }

     //void drawRotarySlider(juce::Graphics& g, int x, int y, int width,
     //                      int height, float sliderPosProportional,
     //                      float rotaryStartAngle, float rotaryEndAngle,
     //                      juce::Slider& slider) override 
     //{
     //    // FILM STRIP
     //    const int numFrames = knobImage.getHeight() / knobImage.getWidth();
     //    const int frameIndex =
     //        (int)std::ceil(sliderPosProportional * (numFrames - 1));

     //    const float radius = fmin(width * 0.5, height * 0.5);
     //    const float centreX = x + width * 0.5f;
     //    const float centreY = y + height * 0.5f;
     //    const float rx = centreX - radius;
     //    const float ry = centreY - radius;

     //    g.drawImage(knobImage, rx, ry, 2 * radius, 2 * radius, 0,
     //                frameIndex * knobImage.getWidth(), knobImage.getWidth(),
     //                knobImage.getWidth());
     //}

 private:
     juce::Image knobImage;
};