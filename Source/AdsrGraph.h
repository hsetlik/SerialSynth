/*
  ==============================================================================

    AdsrGraph.h
    Created: 29 Sep 2020 8:29:24pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "RGBColor.h"

class AdsrGraph : public juce::Component, public juce::Timer
{
public:
    AdsrGraph(juce::Slider* aSlider, juce::Slider* dSlider, juce::Slider* sSlider, juce::Slider* rSlider) :
    pAttack(aSlider),
    pDecay(dSlider),
    pSustain(sSlider),
    pRelease(rSlider)
    {
        //grabValues();
        lastAttack = 20.0f;
        lastDecay = 100.0f;
        lastSustain = 0.6f;
        lastRelease = 250.0f;
        startTimerHz(24);
    }
    ~AdsrGraph() {}
    void grabValues()
    {
        if(pAttack->getValue())
        {
        lastAttack = pAttack->getValue();
        lastDecay = pDecay->getValue();
        lastSustain = pSustain->getValue();
        lastRelease = pRelease->getValue();
        }
    }
    void setTraceColors(juce::Colour color1, juce::Colour color2, juce::Colour color3)
    {
        traceColor = color1;
        trace2Color = color.blend(color2, background, 0.05);
        trace3Color = color.blend(color3, background, 0.05);
    }
    void paint(juce::Graphics &g) override;
    void timerCallback() override
    {
        repaint();
    }
    void addSecondTrace(juce::Path* path)
    {
        secondTrace = path;
        hasSecondTrace = true;
    }
    void addThirdTrace(juce::Path* path)
    {
        thirdTrace = path;
        hasThirdTrace = true;
    }
    juce::Path trace;
    bool hasSecondTrace = false;
    juce::Path* secondTrace;
    bool hasThirdTrace = false;
    juce::Path* thirdTrace;
    
private:
    ColorCreator color;
    juce::Colour background = juce::Colours::darkgrey;
    juce::Colour traceColor = juce::Colours::orange;
    juce::Colour trace2Color;
    juce::Colour trace3Color;
    double lastAttack;
    double lastDecay;
    double lastSustain;
    double lastRelease;
    juce::Slider* pAttack;
    juce::Slider* pDecay;
    juce::Slider* pSustain;
    juce::Slider* pRelease;
};
