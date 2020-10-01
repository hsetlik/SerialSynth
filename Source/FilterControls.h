/*
  ==============================================================================

    FilterControls.h
    Created: 1 Oct 2020 7:28:02am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "maximilian.h"
#include "MultiModDestination.h"
class FilterControls : public juce::Component
{
public:
    //functions
    FilterControls();
    ~FilterControls() {}
    //data
    MultiModDestination cutoffKnob;
    MultiModDestination resonanceKnob;
    MultiModDestination mixKnob;
};
