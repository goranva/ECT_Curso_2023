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
    // Header:
    juce::Rectangle<int> header{0, 0, getWidth(), 50};
    g.setColour(juce::Colour(65, 85, 142));
    g.fillRect(header);

    g.setColour(juce::Colour(237, 244, 237));
    g.setFont(20.0f);
    g.drawText("ECT Curso 2023 Septiembre", header,
               juce::Justification::centred);

    g.setColour(juce::Colour(65, 85, 142));
    g.setFont(18.0f);

    // LFO
    g.drawText("LFO", 12, 65, getWidth() - 25, 20, juce::Justification::left);
    g.drawRoundedRectangle(10, 95, getWidth() / 2 - 5, getHeight() * 0.3, 5, 2);    
    
    // Paneo
    g.drawText("Pan", getWidth()/2 + 22, 65, getWidth() - 25, 20,
               juce::Justification::left);
    g.drawRoundedRectangle(getWidth() / 2 + 20, 95, getWidth() / 2 - 30,
                           getHeight() * 0.3, 5, 2);    
    
    // Filter
    g.drawText("Filter", 12, 240, getWidth() - 25, 20,
               juce::Justification::left);
    g.drawRoundedRectangle(10, 270, getWidth() / 2 - 5,
                           getHeight() * 0.3, 5, 2);    
    
    // General
    g.drawText("General", getWidth()/2 + 22, 240, getWidth() - 20, 20,
               juce::Justification::left);
    g.drawRoundedRectangle(getWidth() / 2 + 22, 270, getWidth() / 2 - 30,
                           getHeight() * 0.3, 5, 2);
}


void ProyectoCursoECTAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    //JUCE_LIVE_CONSTANT(0)
    volumeSlider.setBounds(115, 0, 100, 100);
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
