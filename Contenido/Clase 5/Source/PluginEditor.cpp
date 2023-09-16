#include "PluginProcessor.h"
#include "PluginEditor.h"

ProyectoECTCursoAudioProcessorEditor::ProyectoECTCursoAudioProcessorEditor (ProyectoECTCursoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (600, 400);
}

ProyectoECTCursoAudioProcessorEditor::~ProyectoECTCursoAudioProcessorEditor() {}

void ProyectoECTCursoAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    g.setColour (juce::Colours::black);
    g.setFont (20.0f);
    g.drawFittedText ("Proyecto ECT Curso", getLocalBounds(), juce::Justification::centred, 1);
}

void ProyectoECTCursoAudioProcessorEditor::resized() {}
