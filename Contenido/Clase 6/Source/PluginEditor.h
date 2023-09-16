#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "./LookAndFeel/KnobLookAndFeel.h"

class ProyectoECTCursoAudioProcessorEditor : public juce::AudioProcessorEditor,
                                             juce::Slider::Listener,
                                             juce::Button::Listener,
                                             juce::ComboBox::Listener
{
public:
    
    ProyectoECTCursoAudioProcessorEditor (ProyectoECTCursoAudioProcessor&);
    
    ~ProyectoECTCursoAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    
    void resized() override;
    
    // Prepares
    void prepareSliders();
    
    void prepareButtons();
    
    void prepareComboBox();
    
    // Listeners
    void sliderValueChanged (juce::Slider* slider) override;
    
    void buttonClicked (juce::Button* button) override;
    
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;

private:

    ProyectoECTCursoAudioProcessor& audioProcessor;
    
    // Sliders
    juce::Slider volumenSlider, paneoSlider, rateSlider, dryWetSlider;
    juce::Label volumenLabel, paneoLabel, rateLabel, dryWetLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volumenAttach, paneoAttach, rateAttach, dryWetAttach;
    KnobLookAndFeel lookAndFeelKnob;
    
    // Filters
    juce::Slider lowFreqSlider, highFreqSlider;
    juce::Label lowFreqLabel, highFreqLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowFreqAttach, highFreqAttach;
    
    // Buttons
    juce::TextButton lfoStateButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> lfoStateButtonAttach;
    
    // Combobox
    juce::ComboBox lfoChoiceCombo;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> lfoChoiceAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProyectoECTCursoAudioProcessorEditor)
};
