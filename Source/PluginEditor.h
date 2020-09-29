/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SpectrumParameterSet.h"
#include "OscilloscopeComponent.h"
#include "OscillatorGroup.h"
#include "ModParentComponent.h"

//==============================================================================
/**
*/
class SpectrumTable1AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SpectrumTable1AudioProcessorEditor (SpectrumTable1AudioProcessor&);
    ~SpectrumTable1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SpectrumTable1AudioProcessor& audioProcessor;
    //MaxiOscGraph graph;
    ModParentComponent masterComp;
    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrumTable1AudioProcessorEditor)
};
