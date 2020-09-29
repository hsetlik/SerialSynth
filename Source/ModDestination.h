/*
  ==============================================================================

    ModDestination.h
    Created: 25 Sep 2020 1:05:12pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include "ModSourceComponent.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/

class ModDestination  : public juce::Component, public juce::DragAndDropTarget
{
public:
    //functions
    ModDestination(juce::DragAndDropContainer* parentContainer, juce::String idStr, int index, SpectrumTable1AudioProcessor& proc);
    ~ModDestination() {}
    void paint (juce::Graphics&) override;
    void setColors(juce::Colour ring, juce::Colour center)
    {
        ringColor = ring;
        centerColor = center;
    }
    void setCenterColor(juce::Colour newCenter)
    {
        centerColor = newCenter;
    }
    void itemDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
        juce::Component* sourceComponent = dragSourceDetails.sourceComponent.get();
        ModSourceComponent* newSource = dynamic_cast<ModSourceComponent*>(sourceComponent);
        setCenterColor(newSource->getCenterColor());
        sources.push_back(newSource);
        juce::String sourceId = newSource->description;
       
    }
    void itemDragEnter(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
        
    }
    void itemDragExit(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
        
    }
    void itemDragMove(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
        
    }
    bool isInterestedInDragSource(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
        return true;
    }
    bool shouldDrawDragImageWhenOver() override
    {
        return false;
    }
    void mouseDown(const juce::MouseEvent& e) override
    {
        if(e.mods.isRightButtonDown())
        {
            setCenterColor(emptyColor);
            sources.clear();
        }
    }
    //data
    int oscIndex;
    juce::String idString;
    juce::DragAndDropContainer* parent;
    std::vector<ModSourceComponent*> sources;
    juce::Colour emptyColor;
    SpectrumTable1AudioProcessor& processor;
private:
    ColorCreator color;
    juce::Colour ringColor;
    juce::Colour centerColor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModDestination)
};
