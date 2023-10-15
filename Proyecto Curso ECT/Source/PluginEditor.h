/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LookAndFeel.h"

//==============================================================================
/**
*/
class ProyectoCursoECTAudioProcessorEditor : public juce::AudioProcessorEditor,
                                             public juce::Slider::Listener,
                                             public juce::Button::Listener 
{
public:
    ProyectoCursoECTAudioProcessorEditor (ProyectoCursoECTAudioProcessor&);
    ~ProyectoCursoECTAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void prepareSliders();
    void prepareButtons();
    void prepareComboBox();

    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ProyectoCursoECTAudioProcessor& audioProcessor;

    LookAndFeel lookAndFeel;

    // Sliders:
    juce::Slider volumeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volumeAttach;

    // Button:
    juce::TextButton modulatorBypassButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>
        modulatorBypassAttach;

    // Combobox
    juce::ComboBox modulatorTypeChoiceCombo;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>
        modulatorChoiceAttach;

    // Background:
    juce::ImageComponent background;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProyectoCursoECTAudioProcessorEditor)
};
