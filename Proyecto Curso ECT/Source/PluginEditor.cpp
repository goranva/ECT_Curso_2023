/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ProyectoCursoECTAudioProcessorEditor::ProyectoCursoECTAudioProcessorEditor (ProyectoCursoECTAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Volume Slider:
   volumeSlider.setSliderStyle(
      juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);

   volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

   addAndMakeVisible(volumeSlider);

    volumeAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
           audioProcessor.apvts, "Volume", volumeSlider);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setLookAndFeel(&lookAndFeel);

    setSize (700, 500);
}

ProyectoCursoECTAudioProcessorEditor::~ProyectoCursoECTAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void ProyectoCursoECTAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void ProyectoCursoECTAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    volumeSlider.setBounds(0, 0, 100, 100);
}
