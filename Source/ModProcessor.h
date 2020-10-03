/*
  ==============================================================================

    ModProcessor.h
    Created: 26 Sep 2020 11:54:30am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ModGenerator.h"


class ModSourceProcessor //each destination that a generator has creates its own ModSourceProcessor
{
public:
    //functions
    ModSourceProcessor(juce::String source, ModGenerator* gen) : generator(gen) , sourceId(source)
    {
        
    }
    ~ModSourceProcessor() {}
    void setDepth(float newDepth)
    {
        //issue: this is never getting called
        depth = newDepth;
    }
    float getNextSampleValue()
    {
        return (generator->getNextSampleValue()) * depth;
    }
    //data
    float depth = 0.0f;
    ModGenerator* generator;
    juce::String sourceId;
};



class ModDestProcessor
{
public:
    //functions
    ModDestProcessor(juce::String dId, int index, VoiceModGenerators* gens) : destId(dId), oscIndex(index), allGens(gens)
    {
        
    }
    ~ModDestProcessor() {}
    
    //this calls to the
    void addSource(juce::String sourceId);
    void removeSource(juce::String sourceId);
    float getParameterDelta(); //returns the value to be added to the target parameter value this sample
    //data
    juce::String destId;
    int oscIndex;
    VoiceModGenerators* allGens;
    juce::OwnedArray<ModSourceProcessor> sources;
private:
};
