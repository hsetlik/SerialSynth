/*
  ==============================================================================

    MaxiOscGraph.cpp
    Created: 24 Sep 2020 9:23:02am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "MaxiOscGraph.h"

OscillatorGraph::OscillatorGraph(OscillatorMonitor* osc, int index) : oscIndex(index), source(osc)
{
    background = color.RGBColor(37, 50, 53);
    traceColor = color.RGBColor(250, 172, 63);
    
    graphP0 = source->lastP0;
    graphP1 = source->lastP1;
    graphN = source->lastN;
    yValues.ensureStorageAllocated(pointsPerFrame);
    yValues.resize(pointsPerFrame);
    yValues.fill(0.0f);
    
    currentAngles.ensureStorageAllocated(maxHarmonics);
    currentAngles.resize(maxHarmonics);
    currentAngles.fill(0.0f);
    
    angleDeltas.ensureStorageAllocated(maxHarmonics);
    angleDeltas.resize(maxHarmonics);
    angleDeltas.fill(0.0f);
    
    amplitudes.ensureStorageAllocated(maxHarmonics);
    amplitudes.resize(maxHarmonics);
    amplitudes.fill(0.0f);
    
    startTimerHz(frameRate);
}

void OscillatorGraph::calculateYValues()
{
    yValues.clear();
    yValues.ensureStorageAllocated(pointsPerFrame);
    currentAngles.clear();
    angleDeltas.clear();
    amplitudes.clear();
    int numHarmonics = (int)ceil(graphN);
    currentAngles.resize(numHarmonics);
    currentAngles.fill(0.0f);
    //calculate the amplitude and frequency for each harmonic
    double baseAngleDelta = (cyclesPerFrame * juce::MathConstants<float>::twoPi) / pointsPerFrame;
    for(int i = 0; i < numHarmonics; ++i)
    {
        float newAngleDelta;
        float newAmplitude;
        if(graphAlg2)
        {
            newAngleDelta = baseAngleDelta * ((graphP0 * i) + graphP1);
            newAmplitude = 1.0f / (((graphP0 * i) + graphP1) - (graphP1 - 1.0f));
            
        }
        else
        {
            newAngleDelta = baseAngleDelta * ((graphP1 * i) + 1.0f);
            newAmplitude = 1.0f / ( (graphP0 * i) + 1.0f);
            
        }
        amplitudes.add(newAmplitude);
        angleDeltas.add(newAngleDelta);
    }
    for(int i = 0; i < pointsPerFrame; ++i)
    {
        float pointSum = 0.0f;
        for(int n = 0; n < numHarmonics; ++n)
        {
            float angle = currentAngles[n];
            float sineLevel = (std::sin(angle) * amplitudes[n]);
            pointSum += sineLevel;
            currentAngles.set(n, angle + angleDeltas[n]);
        }
        yValues.add(pointSum);
    }
}

void OscillatorGraph::timerCallback()
{
    updateValues();
    calculateYValues();
    repaint();
}

void OscillatorGraph::paint(juce::Graphics &g)
{
    g.setColour(background);
    g.fillAll();
    g.setColour(traceColor);
    
    juce::Rectangle<float> area = getLocalBounds().toFloat();
    float xDelta = (area.getWidth() / pointsPerFrame);
    juce::Path trace;
    trace.preallocateSpace((3 * pointsPerFrame) + 7);
    float yOffset = area.getHeight() / 2.0f;
    if(yValues.size() == pointsPerFrame)
    {
        for(int i = 0; i < pointsPerFrame; ++i)
        {
            float newX = xDelta * i;
            float newY = (yValues[i] * gain * graphLevel) + yOffset;
            if(i == 0)
                trace.startNewSubPath(newX, newY);
            else
                trace.lineTo(newX, newY);
        }
    }
    trace.lineTo(area.getWidth(), area.getHeight());
    trace.lineTo(area.getX(), area.getHeight());
    trace.closeSubPath();
    
    auto stroke = juce::PathStrokeType(1.0f);
    g.strokePath(trace, stroke);
    
    g.setColour(background);
    g.drawRect(area);
}
