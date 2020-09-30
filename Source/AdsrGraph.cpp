/*
  ==============================================================================

    AdsrGraph.cpp
    Created: 29 Sep 2020 8:29:24pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "AdsrGraph.h"

void AdsrGraph::paint(juce::Graphics &g)
{
    trace.clear();
    
    grabValues();
    
    juce::Rectangle<float> area = getLocalBounds().toFloat();
    g.setColour(background);
    g.fillRect(area);
    g.setColour(traceColor);
    double dAttack = (lastAttack / 20000.0f);
    double dDecay = (lastDecay / 20000.0f);
    double dRelease = (lastRelease / 20000.0f);
    
    
    float aExp = std::powf(100.0f,(-2.0f * dAttack)) + 1.0f;
    printf("Last Attack: %f\n", lastAttack);
    float dExp = std::powf(100.0f,(-2.0f * dDecay)) + 1.0f;
    float rExp = std::powf(100.0f, (-2.0f * dRelease)) + 1.0f;
    
    aExp = (-1.0f * aExp) + 2.0f;
    printf("final aExp: %f\n", aExp);
    dExp = (-1.0f * dExp) + 2.0f;
    rExp = (-1.0f * rExp) + 2.0f;
    
    auto totalPreSustain = aExp + dExp;
    auto totalTimeSum = aExp + dExp + rExp;
    
    //scaling down for long parameters
    if(totalTimeSum > 1.0f)
    {
        auto ratio = totalPreSustain / rExp;
        //printf("ratio: %f\n", ratio);
        double factor = pow((ratio * (totalPreSustain) + ((1.0f - ratio) * rExp)), -1.0);
        aExp *= (ratio * factor);
        dExp *= (ratio * factor);
        rExp *= ((1.0 - ratio) * factor);
    }
    
    int fullWidth = getWidth();
    
    int peakX = fullWidth * aExp;
    //printf("PeakX: %d\n", peakX);
    int sustainStartX = peakX + (fullWidth * dExp);
    int releaseX = fullWidth - (fullWidth * rExp);
    
    trace.startNewSubPath(0, area.getHeight());
    trace.lineTo(peakX, 0);
    trace.lineTo(sustainStartX, area.getHeight() * ( 1.0 - lastSustain));
    trace.lineTo(releaseX, area.getHeight() * (1.0 - lastSustain));
    trace.lineTo(area.getWidth(), area.getHeight());
    trace.closeSubPath();
    
    trace.scaleToFit(area.getX(), area.getY(), area.getWidth(), area.getHeight(), false);
    
    auto strokeType = juce::PathStrokeType(1.0);
    
    auto thinStroke = juce::PathStrokeType(0.6);
    if(hasSecondTrace)
    {
        g.setColour(trace2Color);
        g.strokePath(*secondTrace, thinStroke);
    }
    if(hasThirdTrace)
    {
        g.setColour(trace3Color);
        g.strokePath(*thirdTrace, thinStroke);
    }
    g.setColour(traceColor);
    
    g.strokePath(trace, strokeType);
}
