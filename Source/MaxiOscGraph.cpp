/*
  ==============================================================================

    MaxiOscGraph.cpp
    Created: 24 Sep 2020 9:23:02am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "MaxiOscGraph.h"

GraphValueSet::GraphValueSet(int maxOvertones)
{
    for(int i = 0; i < maxOvertones; ++i)
    {
        std::unique_ptr<HarmonicData> newHarmonic(new HarmonicData(i));
        harmonicData.push_back(*newHarmonic);
        //pumping the correct amount of zeroes into these vectors so we have a straight line at the beginning;
        angleDeltas.push_back(0.0f);
        currentAngles.push_back(0.0f);
        fAmplitudes.push_back(0.0f);
    }
    for(int i = 0; i < pointsPerFrame; ++i)
    {
        pointsToDisplay.push_back(0.0f);
    }
}

void GraphValueSet::setDisplayPoints()
{
    int cyclesPerFrame = 3; //how wide should the frame be relative to the fundamental
    for(int i = 0; i < harmonicData.size(); ++i)
    {
        currentAngles[i] = 0.0f;
        if(secondAlgOn)
        {
            auto newDelta = (harmonicData[i].getFrequencyFactor2(currentP1, currentP0) * cyclesPerFrame * juce::MathConstants<float>::twoPi) / pointsPerFrame;
            angleDeltas[i] = newDelta;
            
            auto newAmplitude = (harmonicData[i].getAmplitudeFactor2(currentP1, currentP0));
            fAmplitudes[i] = newAmplitude;
        }
        else
        {
            auto newDelta = (harmonicData[i].getFrequencyFactor1(currentP1) * cyclesPerFrame * juce::MathConstants<float>::twoPi) / pointsPerFrame;
            angleDeltas[i] = newDelta;
            auto newAmplitude = (harmonicData[i].getAmplitudeFactor1(currentP0));
            fAmplitudes[i] = newAmplitude;
            
        }
    }
    for(int i = 0; i < pointsPerFrame; ++i)
    {
        float newPointTotal = 0.0f;
        for(int n = 0; n < currentNumHarmonics; ++n)
        {
            float newPointFull = std::sin(currentAngles[n]);
            float newPointScaled = newPointFull * fAmplitudes[n];
            newPointTotal += newPointScaled;
            currentAngles[n] += angleDeltas[n];
        }
        pointsToDisplay[i] = newPointTotal * masterAmplitude;
    }
}





//==============================================================================
MaxiOscGraph::MaxiOscGraph(GraphValueSet* valueSet) : values(valueSet)
{
    waveDataPoints = std::vector<float>(values->pointsToDisplay);
    startTimerHz(frameRate);
}

MaxiOscGraph::~MaxiOscGraph()
{
}

void MaxiOscGraph::paint (juce::Graphics& g)
{
    waveDataPoints = std::vector<float>(values->pointsToDisplay);
    g.setColour(backgroundColor);
    g.fillAll();
    g.setColour(traceColor);
    if(waveDataPoints.size() != 0)
    {
        juce::Path trace;
        juce::Rectangle<float> area = getLocalBounds().toFloat();
        trace.scaleToFit(area.getX(), area.getY(), area.getWidth(), area.getHeight(), true);
        auto yOffest = area.getHeight() / 2;
        auto xDelta = area.getWidth() / pointsPerFrame;
        for(int i = 0; i < pointsPerFrame; ++i)
        {
            float newX = xDelta * i;
            float newY = (waveDataPoints[i] * amplitude) + yOffest;
            if(i == 0)
            {
                trace.startNewSubPath(newX, newY);
            }
            else
            {
                trace.lineTo(newX, newY);
            }
        }
        trace.lineTo(area.getRight(), area.getHeight());
        trace.lineTo(area.getX(), area.getHeight());
        trace.closeSubPath();
        
        auto strokeType1 = juce::PathStrokeType(1.0f);
        g.strokePath(trace, strokeType1);
        auto frameColor = color.RGBColor(15, 15, 15);
        g.setColour(frameColor);
        g.drawRect(area, 1.5f);
    }
}
