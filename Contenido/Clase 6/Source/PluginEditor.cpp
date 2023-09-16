#include "PluginProcessor.h"
#include "PluginEditor.h"

ProyectoECTCursoAudioProcessorEditor::ProyectoECTCursoAudioProcessorEditor (ProyectoECTCursoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    prepareSliders();
    prepareButtons();
    prepareComboBox();
    
    setLookAndFeel (&lookAndFeelKnob);
    
    setSize (600, 400);
}

ProyectoECTCursoAudioProcessorEditor::~ProyectoECTCursoAudioProcessorEditor()
{
    volumenSlider.removeListener (this);
    volumenSlider.setLookAndFeel (nullptr);
    
    paneoSlider.removeListener   (this);
    
    lfoStateButton.removeListener (this);
    lfoChoiceCombo.removeListener (this);
    
    setLookAndFeel (nullptr);
}

void ProyectoECTCursoAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);
}

void ProyectoECTCursoAudioProcessorEditor::resized()
{
    rateSlider.setBounds (20, 122, 95, 95);
    lfoChoiceCombo.setBounds (140, 115, 150, 20);
    lfoStateButton.setBounds (190, 150, 50, 50);
    
    lowFreqSlider.setBounds  (50, 300, 90, 90);
    highFreqSlider.setBounds (180, 300, 90, 90);
    
    paneoSlider.setBounds (410, 122, 95, 95);
    
    dryWetSlider.setBounds  (getWidth()/2 + 55, 300, 90, 90);
    volumenSlider.setBounds (getWidth()/2 + 175, 300, 90, 90);
}

void ProyectoECTCursoAudioProcessorEditor::prepareSliders()
{
    //======================================== Volumen ========================================//
    volumenSlider.setSliderStyle  (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    volumenSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0.0f, 0.0f);
    volumenSlider.addListener (this);
    addAndMakeVisible (volumenSlider);
    
    volumenAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.apvts,
                                                                                            "Volume",
                                                                                            volumenSlider);
    
    volumenLabel.setText ("Volume", juce::dontSendNotification);
    volumenLabel.setJustificationType (juce::Justification::centred);
    volumenLabel.setColour (juce::Label::textColourId, juce::Colours::black);
    volumenLabel.attachToComponent (&volumenSlider, false);
    addAndMakeVisible (volumenLabel);
    
    //======================================== Paneo ========================================//
    paneoSlider.setSliderStyle  (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    paneoSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0.0f, 0.0f);
    paneoSlider.setColour (juce::Slider::ColourIds::trackColourId, juce::Colours::green);
    paneoSlider.addListener (this);
    addAndMakeVisible (paneoSlider);
    
    paneoAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.apvts, "Pan", paneoSlider);
    
    paneoLabel.setText ("Pan", juce::dontSendNotification);
    paneoLabel.setJustificationType (juce::Justification::centred);
    paneoLabel.setColour (juce::Label::textColourId, juce::Colours::black);
    paneoLabel.attachToComponent (&paneoSlider, false);
    addAndMakeVisible (paneoLabel);
    
    //======================================== LFO ========================================//
    rateSlider.setSliderStyle  (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0.0f, 0.0f);
    rateSlider.setColour (juce::Slider::ColourIds::thumbColourId, juce::Colours::green);
    rateSlider.setColour (juce::Slider::ColourIds::backgroundColourId, juce::Colours::black);
    addAndMakeVisible (rateSlider);
    
    rateAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.apvts, "Rate", rateSlider);
    
    rateLabel.setText ("Rate", juce::dontSendNotification);
    rateLabel.setJustificationType (juce::Justification::centred);
    rateLabel.setColour (juce::Label::textColourId, juce::Colours::black);
    rateLabel.attachToComponent (&rateSlider, false);
    addAndMakeVisible (rateLabel);
    
    //======================================== DryWet ========================================//
    dryWetSlider.setSliderStyle  (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dryWetSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0.0f, 0.0f);
    dryWetSlider.setColour (juce::Slider::ColourIds::thumbColourId, juce::Colours::green);
    dryWetSlider.setColour (juce::Slider::ColourIds::backgroundColourId, juce::Colours::black);
    addAndMakeVisible (dryWetSlider);
    
    dryWetAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.apvts, "DryWet", dryWetSlider);
    
    dryWetLabel.setText ("DryWet", juce::dontSendNotification);
    dryWetLabel.setJustificationType (juce::Justification::centred);
    dryWetLabel.setColour (juce::Label::textColourId, juce::Colours::black);
    dryWetLabel.attachToComponent (&dryWetSlider, false);
    addAndMakeVisible (dryWetLabel);
    
    //======================================== Low Freq ========================================//
    lowFreqSlider.setSliderStyle  (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lowFreqSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0.0f, 0.0f);
    lowFreqSlider.setColour (juce::Slider::ColourIds::thumbColourId, juce::Colours::green);
    lowFreqSlider.setColour (juce::Slider::ColourIds::backgroundColourId, juce::Colours::black);
    addAndMakeVisible (lowFreqSlider);
    
    lowFreqAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.apvts, "LowFreq", lowFreqSlider);
    
    lowFreqLabel.setText ("Low Freq", juce::dontSendNotification);
    lowFreqLabel.setJustificationType (juce::Justification::centred);
    lowFreqLabel.setColour (juce::Label::textColourId, juce::Colours::black);
    lowFreqLabel.attachToComponent (&lowFreqSlider, false);
    addAndMakeVisible (lowFreqLabel);
    
    //======================================== High Freq ========================================//
    highFreqSlider.setSliderStyle  (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    highFreqSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0.0f, 0.0f);
    highFreqSlider.setColour (juce::Slider::ColourIds::thumbColourId, juce::Colours::green);
    highFreqSlider.setColour (juce::Slider::ColourIds::backgroundColourId, juce::Colours::black);
    addAndMakeVisible (highFreqSlider);
    
    highFreqAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.apvts, "HighFreq", highFreqSlider);
    
    highFreqLabel.setText ("High Freq", juce::dontSendNotification);
    highFreqLabel.setJustificationType (juce::Justification::centred);
    highFreqLabel.setColour (juce::Label::textColourId, juce::Colours::black);
    highFreqLabel.attachToComponent (&highFreqSlider, false);
    addAndMakeVisible (highFreqLabel);
}

void ProyectoECTCursoAudioProcessorEditor::prepareButtons()
{
    lfoStateButton.setButtonText ("LFO");
    lfoStateButton.setClickingTogglesState (true);
    lfoStateButton.addListener (this);
    addAndMakeVisible (lfoStateButton);

    auto buttonColour = juce::Colour (26, 34, 57);
    lfoStateButton.setColour (juce::TextButton::ColourIds::buttonColourId, buttonColour);
    lfoStateButton.setColour (juce::TextButton::ColourIds::buttonOnColourId, buttonColour.brighter());
    
    lfoStateButtonAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (audioProcessor.apvts,
                                                                                                   "LFOState",
                                                                                                   lfoStateButton);
}

void ProyectoECTCursoAudioProcessorEditor::prepareComboBox()
{
    lfoChoiceCombo.addItem ("Sine", 1);
    lfoChoiceCombo.addItem ("Square", 2);
    lfoChoiceCombo.addItem ("Saw", 3);
    lfoChoiceCombo.addItem ("Triangle", 4);
    lfoChoiceCombo.setJustificationType (juce::Justification::centred);
    lfoChoiceCombo.addListener (this);
    addAndMakeVisible (lfoChoiceCombo);

    lfoChoiceCombo.setColour (juce::ComboBox::ColourIds::backgroundColourId, juce::Colour(26, 34, 57));
    
    lfoChoiceAttach = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (audioProcessor.apvts,
                                                                                                "LFOChoice",
                                                                                                lfoChoiceCombo);
}

void ProyectoECTCursoAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &volumenSlider)
        DBG ("Volumen: " << volumenSlider.getValue());

    else if (slider == &paneoSlider)
        DBG ("Paneo: " << paneoSlider.getValue());
}

void ProyectoECTCursoAudioProcessorEditor::buttonClicked (juce::Button* button)
{
    if (button == &lfoStateButton)
        DBG ("Click");
}

void ProyectoECTCursoAudioProcessorEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &lfoChoiceCombo)
        DBG ("Combobox: " << lfoChoiceCombo.getText());
}
