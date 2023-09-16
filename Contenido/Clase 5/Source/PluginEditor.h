#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class ProyectoECTCursoAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    
    ProyectoECTCursoAudioProcessorEditor (ProyectoECTCursoAudioProcessor&);
    ~ProyectoECTCursoAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    ProyectoECTCursoAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProyectoECTCursoAudioProcessorEditor)
};
