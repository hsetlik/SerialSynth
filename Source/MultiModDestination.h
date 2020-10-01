/*
  ==============================================================================

    MultiModDestination.h
    Created: 27 Sep 2020 12:51:10pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ModSourceComponent.h"
#include "PluginProcessor.h"

class DepthSlider : public juce::Slider
{
public:
    DepthSlider(juce::String source, juce::String dest, bool isVertical, int index) :
    oscIndex(index),
    sourceId(source),
    destId(dest)
    {
        auto sliderStyle = (isVertical) ? (juce::Slider::LinearVertical) : (juce::Slider::LinearHorizontal);
        setSliderStyle(sliderStyle);
        setRange(-1.0f, 1.0f);
        setValue(0.0f);
        setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    }
    ~DepthSlider() {}
    int oscIndex;
    
    juce::String sourceId;
    juce::String destId;
};

class MultiDepthSlider : public juce::TabbedComponent
{
public:
    //functions
    MultiDepthSlider(juce::String dest, bool isVertical, int index, juce::Slider::Listener* lstnr, SpectrumTable1AudioProcessor& proc) :
    juce::TabbedComponent( (isVertical) ? juce::TabbedButtonBar::TabsAtLeft : juce::TabbedButtonBar::TabsAtBottom),
    parentIsVertical(isVertical),
    oscIndex(index),
    listener(lstnr),
    destId(dest),
    audioProcessor(proc)
    {
        tabBkgnd = color.RGBColor(110, 110, 110);
        setTabBarDepth(6);
    }
    void addDepthSlider(juce::String sourceId);
    void mouseDown(const juce::MouseEvent &e) override;
    //data
    bool parentIsVertical;
    int oscIndex;
    juce::Slider::Listener* listener;
    juce::String destId;
    juce::OwnedArray<juce::String> sourceIds;
    juce::OwnedArray<DepthSlider> depthSliders;
    juce::Colour tabBkgnd;
    SpectrumTable1AudioProcessor& audioProcessor;
private:
    ColorCreator color;
};


class MultiModDestination : public juce::DragAndDropTarget, public juce::Component
{
public:
    //functions
    MultiModDestination(juce::String idStr, bool isVertical, float min, float max, int index, juce::Slider::Listener* lstnr, SpectrumTable1AudioProcessor& proc, juce::Slider::SliderStyle mainStyle) :
    audioProcessor(proc),
    listener(lstnr),
    depthSliderSet(idStr, isVertical, index, lstnr, proc),
    destSliderIsVertical(isVertical),
    paramMin(min),
    paramMax(max),
    destId(idStr),
    oscIndex(index)
    {
        addAndMakeVisible(&paramSlider);
        addAndMakeVisible(&depthSliderSet);
        //auto sliderStyle = (isVertical) ? (juce::Slider::LinearVertical) : (juce::Slider::LinearHorizontal);
        paramSlider.setSliderStyle(mainStyle);
        if(isVertical)
            paramSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 15);
        else
            paramSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 40, 15);
        paramSlider.setRange(paramMin, paramMax);
        
    }
    ~MultiModDestination() {}
    void resized() override;
    void paint(juce::Graphics& g) override
    {
        g.setColour(juce::Colours::darkgrey);
        g.fillRect(paramSlider.getBounds());
    }
    void mouseDown(const juce::MouseEvent &e) override
    {
        printf("mouse clicked in MultiDest\n");
        if(e.mods.isRightButtonDown())
        {
            if(depthSliderSet.contains(e.getPosition()))
            {
                int index = depthSliderSet.getCurrentTabIndex();
                juce::String source = *depthSliderSet.sourceIds[index];
                
                audioProcessor.removeVoiceModulation(source, destId, index, &depthSliderSet);
                depthSliderSet.sourceIds.remove(index);
                depthSliderSet.depthSliders.remove(index);
                depthSliderSet.removeTab(index);
            }
        }
    }
    //dragdroptarget virtual functions
    void itemDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override;
    void itemDragEnter(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
    }
    void itemDragExit(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
    }
    void itemDragMove(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
    }
    bool isInterestedInDragSource(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override;
    
    bool shouldDrawDragImageWhenOver() override
    {
        return false;
    }
    
    //data
    SpectrumTable1AudioProcessor& audioProcessor;
    juce::Slider::Listener* listener;
    MultiDepthSlider depthSliderSet;
    bool destSliderIsVertical;
    float paramMin;
    float paramMax;
    juce::String destId;
    juce::Slider paramSlider;
    int oscIndex;
private:
    ColorCreator color;
};
