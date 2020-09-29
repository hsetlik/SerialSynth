/*
  ==============================================================================

    MaxiOscGraph.h
    Created: 24 Sep 2020 9:23:02am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "maximilian.h"
#include "SpectrumOscillator.h"
#include "OscilloscopeComponent.h"
#include "RGBColor.h"
//==============================================================================
/*
*/
const int frameRate = 24;

class GraphValueSet
{
public:
    //functions
    GraphValueSet(int maxOvertones);
    ~GraphValueSet() {}
    void setNumHarmonics(float value)
    {
        currentNumHarmonics = value;
    }
    void setP0(float value)
    {
        currentP0 = value;
    }
    void setP1(float value)
    {
        currentP1 = value;
    }
    void setAlgSelection(bool value)
    {
        secondAlgOn = value;
    }
    void setPitch(float pitch)
    {
        currentFundamental = pitch;
    }
    void setMasterVol(float amp)
    {
        masterAmplitude = amp;
    }
    void setDisplayPoints();
    //data
    std::vector<HarmonicData> harmonicData;
    std::vector<float> fAmplitudes;
    std::vector<float> pointsToDisplay;
    std::vector<float> angleDeltas;
    std::vector<float> currentAngles;
    
private:
    float masterAmplitude = 1.0f;
    float currentFundamental = 440.0f;
    int currentNumHarmonics = 0;
    bool secondAlgOn = false;
    float currentP0 = 1;
    float currentP1 = 1;
};



class MaxiOscGraph  : public juce::Component, public juce::Timer
{
public:
    MaxiOscGraph(GraphValueSet* valueSet);
    ~MaxiOscGraph() override;
    void timerCallback() override
    {
        repaint();
    }
    void paint (juce::Graphics&) override;
private:
    std::vector<float> waveDataPoints;
    float amplitude = 100.0f;
    GraphValueSet* values;
    juce::Colour backgroundColor = juce::Colours::darkgrey;
    juce::Colour traceColor = juce::Colours::orange;
    ColorCreator color;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MaxiOscGraph)
};
