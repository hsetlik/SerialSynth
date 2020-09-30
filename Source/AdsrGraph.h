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
    void paint(juce::Graphics &g) override;
    void timerCallback() override
    {
        repaint();
    }
    
    juce::Path trace;
private:
    ColorCreator color;
    juce::Colour background = juce::Colours::darkgrey;
    juce::Colour traceColor = juce::Colours::orange;
    double lastAttack;
    double lastDecay;
    double lastSustain;
    double lastRelease;
    juce::Slider* pAttack;
    juce::Slider* pDecay;
    juce::Slider* pSustain;
    juce::Slider* pRelease;
};
