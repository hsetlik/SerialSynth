/*
  ==============================================================================

    ModSourceComponent.h
    Created: 25 Sep 2020 11:25:38am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "maximilian.h"
#include "RGBColor.h"
#include "AdsrGraph.h"
//#include "ModParentComponent.h"
//==============================================================================
/*
*/
class ModSourceComponent  : public juce::Component //any modulation source components (LFOs, Envelopes, Noise, etc.) need to include an instance of this class
{
public:
    ModSourceComponent(juce::String desc, juce::DragAndDropContainer* parentContainer);
    ~ModSourceComponent() {}
    void mouseDown(const juce::MouseEvent& e) override
    {
        parent->startDragging(description, this);
    }
    void paint (juce::Graphics&) override;
    void resized() override;
    void changeCenterColor(juce::Colour newColor)
    {
        centerColor = newColor;
    }
    void updateValue(float newValue)
    {
        dataValue = newValue;
    }
    float getValue()
    {
        return dataValue;
    }
    juce::Colour getCenterColor()
    {
        return centerColor;
    }
    juce::DragAndDropContainer* parent;
    juce::String description;
private:
    float dataValue = 0.0f;
    juce::Colour ringColor = juce::Colours::black;
    juce::Colour centerColor = juce::Colours::skyblue;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModSourceComponent)
};


class LfoComponent : public juce::Component
{
public:
    LfoComponent(juce::String desc, juce::DragAndDropContainer* parentContainer, int index);
    LfoComponent(juce::String desc, juce::DragAndDropContainer* parentContainer, int index, juce::Colour modSourceColor);
    ~LfoComponent() {}
    void resized() override;
    void paint(juce::Graphics& g) override;
    void attachToTree(juce::AudioProcessorValueTreeState* target)
    {
        juce::String iStr = juce::String(LfoIndex);
        auto pId = "lfoRateParam"+ iStr;
        auto typeId = "lfoWaveParam" + iStr;
        freqAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*target, pId, freqSlider));
        waveformAttach.reset(new juce::AudioProcessorValueTreeState::ComboBoxAttachment(*target, typeId, waveform));
    }
    ModSourceComponent modSource;
    int LfoIndex;
    juce::Slider freqSlider;
    juce::ComboBox waveform;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freqAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveformAttach;
    ColorCreator color;
    
};

class TabbedLfoComponent : public juce::TabbedComponent
{
public:
    //functions
    TabbedLfoComponent(juce::DragAndDropContainer* container);
    ~TabbedLfoComponent() {}
    void attachAllToTree(juce::AudioProcessorValueTreeState* target);
    //data
    juce::OwnedArray<LfoComponent> contents;
    ColorCreator color;
};


class EnvelopeComponent : public juce::Component
{
public:
    //functions
    EnvelopeComponent(juce::String desc, juce::DragAndDropContainer* parentContainer, int index, juce::Colour modSourceColor);
    ~EnvelopeComponent() {}
    void paint(juce::Graphics& g) override;
    void resized() override;
    void attachToTree(juce::AudioProcessorValueTreeState* tree)
    {
        juce::String iStr = juce::String(envIndex);
        auto attackId = "modEnvAttackParam" + iStr;
        auto decayId = "modEnvDecayParam" + iStr;
        auto sustainId = "modEnvSustainParam" + iStr;
        auto releaseId = "modEnvReleaseParam" + iStr;
        
        aAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*tree, attackId, aSlider));
        dAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*tree, decayId, dSlider));
        sAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*tree, sustainId, sSlider));
        rAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*tree, releaseId, rSlider));
    }
    //data
    ModSourceComponent modSource;
    AdsrGraph graph;
    int envIndex;
    juce::Slider aSlider;
    juce::Slider dSlider;
    juce::Slider sSlider;
    juce::Slider rSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> aAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rAttach;
    
    ColorCreator color;
};

class TabbedEnvelopeComponent : public juce::TabbedComponent
{
public:
    //functions
    TabbedEnvelopeComponent(juce::DragAndDropContainer* container);
    ~TabbedEnvelopeComponent() {}
    void attachAllToTree(juce::AudioProcessorValueTreeState* tree);
    //data
    juce::OwnedArray<EnvelopeComponent> contents;
    ColorCreator color;
    
    
};


