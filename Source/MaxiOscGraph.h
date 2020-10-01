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

class OscillatorMonitor
{
public:
    OscillatorMonitor(int index): oscIndex(index)
    {
        
    }
    ~OscillatorMonitor() {}
    void setAlg2(bool value)
    {
        alg2 = value;
    }
    void setP0(float* value)
    {
        lastP0 = *value;
    }
    void setP1(float* value)
    {
        lastP1 = *value;
    }
    void setN(float* value)
    {
        lastN = *value;
    }
    void setLevel(float value)
    {
        lastLevel = value;
    }
    int oscIndex;
    float lastP0 = 1.0f;
    float lastP1 = 1.0f;
    float lastN = 6.0f;
    float lastLevel;
    bool alg2 = false;
};


const int frameRate = 24;


class OscillatorGraph : public juce::Component, public juce::Timer
{
public:
    //functions
    OscillatorGraph(OscillatorMonitor* osc, int index);
    ~OscillatorGraph() {}
    void timerCallback() override;
    void paint(juce::Graphics& g) override;
    void calculateYValues();
    void updateValues()
    {
        graphP0 = source->lastP0;
        graphP1 = source->lastP1;
        graphN = source->lastN;
        graphAlg2 = source->alg2;
        graphLevel = source->lastLevel;
    }
    //data
private:
    juce::Array<float> yValues;
    juce::Array<float> currentAngles;
    juce::Array<float> angleDeltas;
    juce::Array<float> amplitudes;
    const int cyclesPerFrame = 3;
    const int frameRate = 24;
    const int pointsPerFrame = 200;
    const int maxHarmonics = 40;
    const float gain = 100.0f;
    float graphP0;
    float graphP1;
    float graphN;
    float graphLevel;
    bool graphAlg2;
    ColorCreator color;
    juce::Colour background;
    juce::Colour traceColor;
    int oscIndex;
    OscillatorMonitor* source;
};
