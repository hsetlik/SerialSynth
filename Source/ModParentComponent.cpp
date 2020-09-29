/*
  ==============================================================================

    ModParentComponent.cpp
    Created: 25 Sep 2020 11:26:11am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ModParentComponent.h"

//==============================================================================

ModParentComponent::~ModParentComponent()
{
}

void ModParentComponent::paint (juce::Graphics& g)
{

}

void ModParentComponent::resized()
{
    int n = getHeight() / 24;
    oscSet.setBounds(0, 0, getWidth() - (5 * n),18 * n);
    lfoSet.setBounds(0, 18 * n, 8 * n, 6.25 * n);
    mixer.setBounds(getWidth() - (5 * n), 0, 5 * n, 18 * n);
}

juce::DragAndDropTarget::SourceDetails ModParentComponent::getActiveSourceDetails(ModDestination* dest)
{
    auto activeDesc = getCurrentDragDescription();
    juce::Point<int> relativePoint = dest->getMouseXYRelative();
    juce::Component* activeComp;
    if(activeDesc == "lfo0Comp")
    {
        //activeComp = &lfo0;
    }
    else
    {
        activeComp = nullptr;
    }
    auto details = juce::DragAndDropTarget::SourceDetails(activeDesc, activeComp, relativePoint);
    return details;
}

void ModParentComponent::sliderValueChanged(juce::Slider* slider)
{
    DepthSlider* dSlider = dynamic_cast<DepthSlider*>(slider);
    int changedIndex = dSlider->oscIndex;
    juce::String newDestId = dSlider->destId;
    juce::String newSourceId = dSlider ->sourceId;
    auto rawValue = dSlider->getValue();
    float adjustedValue;
    if(rawValue >= 0)
        adjustedValue = pow(4.5f, 10.0 * (rawValue - 1));
    else
    {
        auto rawAbs = std::fabs(rawValue);
        auto adjustedAbs = pow(8.0f, 3.0 * (rawAbs - 1));
        adjustedValue = -1.0f * adjustedAbs;
    }
    audioProcessor.setModDepth(newSourceId, newDestId, changedIndex, adjustedValue);
}
