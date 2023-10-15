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

    auto backgroundImage = juce::ImageCache::getFromMemory(
      BinaryData::AxolotlBG_png, BinaryData::AxolotlBG_pngSize);
  background.setImage(backgroundImage);
  background.setImagePlacement(juce::RectanglePlacement::centred);
  addAndMakeVisible(background);

      prepareSliders();
  prepareButtons();
  prepareComboBox();

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
    modulatorBypassButton.setBounds(100, 50, 100, 50);
        modulatorTypeChoiceCombo.setBounds(0, 100, 100, 50);

    background.setBounds(getLocalBounds());
}

void ProyectoCursoECTAudioProcessorEditor::prepareSliders() 
{  
    // Volume Slider:
    volumeSlider.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);

    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    addAndMakeVisible(volumeSlider);

    volumeAttach =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.apvts, "Volume", volumeSlider);
}

void ProyectoCursoECTAudioProcessorEditor::prepareButtons() 
{
    modulatorBypassButton.setButtonText("AM");

    modulatorBypassButton.setClickingTogglesState(true);
    addAndMakeVisible(modulatorBypassButton);

    modulatorBypassButton.addListener(this);

    modulatorBypassAttach =
        std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
            audioProcessor.apvts, "Modulation Rate", modulatorBypassButton);
}

void ProyectoCursoECTAudioProcessorEditor::prepareComboBox() 
{
         modulatorTypeChoiceCombo.addItem("Sine", 1);
    modulatorTypeChoiceCombo.addItem("Square", 2);
         modulatorTypeChoiceCombo.addItem("Saw", 3);
    modulatorTypeChoiceCombo.addItem("Triangle", 4);
         modulatorTypeChoiceCombo.setJustificationType(
             juce::Justification::centred);
    addAndMakeVisible(modulatorTypeChoiceCombo);

    modulatorChoiceAttach = std::make_unique<
        juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
        audioProcessor.apvts, "Modulation Type", modulatorTypeChoiceCombo);
}

void ProyectoCursoECTAudioProcessorEditor::sliderValueChanged(
    juce::Slider* slider) 
{
    if (slider == &volumeSlider) {
      DBG("Volumen value: " << slider->getValue());
    }
}

void ProyectoCursoECTAudioProcessorEditor::buttonClicked(juce::Button* button) 
{
    if (button == &modulatorBypassButton) {
      DBG("Button state: " << (int)*audioProcessor.apvts.getRawParameterValue(
              "Modulation Bypass"));
    }
}
