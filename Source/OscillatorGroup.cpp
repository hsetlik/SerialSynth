/*
  ==============================================================================

    OscillatorGroup.cpp
    Created: 24 Sep 2020 12:07:40pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscillatorGroup.h"

juce::AudioProcessorParameterGroup OscillatorSet::createGroup()
{
    juce::AudioProcessorParameterGroup newGroup = juce::AudioProcessorParameterGroup("AllOscs", "Oscs", "|");
    std::unique_ptr<juce::AudioProcessorParameterGroup> newPtr = std::make_unique<juce::AudioProcessorParameterGroup>(pSet1.createParamGroup());
    newGroup.addChild(std::make_unique<juce::AudioProcessorParameterGroup>(pSet1.createParamGroup()));
    newGroup.addChild(std::make_unique<juce::AudioProcessorParameterGroup>(pSet2.createParamGroup()));
    newGroup.addChild(std::make_unique<juce::AudioProcessorParameterGroup>(pSet3.createParamGroup()));
    
    return newGroup;
}

//==============================================================================


