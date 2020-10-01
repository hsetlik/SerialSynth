/*
  ==============================================================================

    ModParentComponent.h
    Created: 25 Sep 2020 11:26:11am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "OscillatorGroup.h"
#include "ModDestination.h"
#include "MixerComponent.h"
#include "FilterControls.h"

//==============================================================================
/*
*/
class ModParentComponent  : public juce::Component, public juce::DragAndDropContainer, public juce::Slider::Listener
{
public:
    ModParentComponent(SpectrumTable1AudioProcessor& proc) :
    filter(proc, this),
    oscSet(proc, this, this),
    lfoSet(this),
    envSet(this),
    audioProcessor(proc)
    {
        addAndMakeVisible(&oscSet);
        addAndMakeVisible(&lfoSet);
        addAndMakeVisible(&mixer);
        addAndMakeVisible(&envSet);
        addAndMakeVisible(&filter);
    }
    ~ModParentComponent() override;
    void paint (juce::Graphics&) override;
    void resized() override;
    void attachAllChildrenToTree(juce::AudioProcessorValueTreeState* state)
    {
        oscSet.attachAllToTree(state);
        lfoSet.attachAllToTree(state);
        envSet.attachAllToTree(state);
        mixer.attachToTree(state);
        filter.attachToTree(state);
    }
    void sliderValueChanged(juce::Slider* slider) override;
    FilterControls filter;
    OscillatorSet oscSet;
    TabbedLfoComponent lfoSet;
    TabbedEnvelopeComponent envSet;
    OscMixerComponent mixer;
    juce::String activeDesc;
    SpectrumTable1AudioProcessor& audioProcessor;
    
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModParentComponent)
};

