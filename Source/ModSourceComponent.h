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


