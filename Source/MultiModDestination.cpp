/*
  ==============================================================================

    MultiModDestination.cpp
    Created: 27 Sep 2020 12:51:10pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "MultiModDestination.h"

void MultiDepthSlider::addDepthSlider(juce::String sourceId)
{
    depthSliders.add(new DepthSlider(sourceId, destId, parentIsVertical, oscIndex));
    addTab(sourceId, tabBkgnd, depthSliders.getLast(), false);
    juce::Slider* dSlider = depthSliders.getLast();
    dSlider->addListener(listener);
}

void MultiDepthSlider::mouseDown(const juce::MouseEvent &e)
{
    if(e.mods.isRightButtonDown())
    {
        printf("right click\n");
        DepthSlider* currentSlider = dynamic_cast<DepthSlider*>(getCurrentContentComponent());
        juce::String source = currentSlider->sourceId;
        juce::String dest = currentSlider->destId;
        audioProcessor.removeVoiceModulation(source, dest, oscIndex, this);
        removeTab(getCurrentTabIndex());
    }
}
void MultiModDestination::itemDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails)
{
    if(isInterestedInDragSource(dragSourceDetails))
    {
        juce::Component* sourceComponent = dragSourceDetails.sourceComponent.get();
        ModSourceComponent* newSource = dynamic_cast<ModSourceComponent*>(sourceComponent);
        juce::String sourceId = newSource->description;
        depthSliderSet.addDepthSlider(sourceId);
        audioProcessor.addVoiceModulation(sourceId, destId, oscIndex);
    }
}
bool MultiModDestination::isInterestedInDragSource(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails)
{
    juce::Component* sourceComponent = dragSourceDetails.sourceComponent.get();
    ModSourceComponent* newSource = dynamic_cast<ModSourceComponent*>(sourceComponent);
    juce::String newSourceId = newSource->description;
    for(int i = 0; i < depthSliderSet.sourceIds.size(); ++i)
    {
        if(newSourceId == *depthSliderSet.sourceIds[i])
        {
            return false;
        }
    }
    return true;
}

void MultiModDestination::resized()
{
    int longDim;
    destSliderIsVertical ? (longDim = getHeight()) : (longDim = getWidth());
    int n = longDim / 16;
    if(destSliderIsVertical)
    {
        paramSlider.setBounds(0, 0, 2.5 * n, 10 * n);
        depthSliderSet.setBounds(0, 10 * n, 1.5 * n, 8 * n);
    }
    else
    {
        paramSlider.setBounds(0, 0, 10 * n, 2.5 * n);
        depthSliderSet.setBounds(0, 2.5 * n, 8 * n, 1.5 * n);
    }
    
}
