/*
  ==============================================================================

    OscilloscopeComponent.cpp
    Created: 23 Sep 2020 10:26:42am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscilloscopeComponent.h"

//==============================================================================
OscilloscopeComponent::OscilloscopeComponent(OscilloscopeSource* src)
{
    source = src;
    startTimerHz(24); //24 frames per second
}



void OscilloscopeComponent::resizeToFrequency()
{
    auto frequency = source->fundamental;
    auto smplRt = source->sampleRate;
    int samplesPerFrame =  2 * ceil(smplRt / frequency);
    samplesPerPoint = samplesPerFrame / pointsPerFrame;
    //jassert(samplesPerPoint < 1);
    
    auto samplesPerBuffer = source->bufferSize;
    int minimumNeededBuffers = ceil(samplesPerFrame / samplesPerBuffer);
    numBuffersToGet = minimumNeededBuffers + 2;
    source->buffersToHold = numBuffersToGet + 2;
}

void OscilloscopeComponent::pullBuffers()
{
    availableBuffers.clear();
    int startIndex = (int)(source->relevantBuffers.size()) - numBuffersToGet;
    startIndex -= 1;
    for(int i = 0; i < numBuffersToGet; ++i)
    {
        availableBuffers.push_back(source->relevantBuffers[i + startIndex]);
    }
}

void OscilloscopeComponent::trigger()
{
    //put everything into the sample vector
    sampleOptions.clear();
    for(int i = 0; i < availableBuffers.size(); ++i)
    {
        for(int n = 0; n < availableBuffers[i].getNumSamples(); ++n)
        {
            float newSample = availableBuffers[i].getSample(0, n);
            sampleOptions.push_back(newSample);
        }
    }
    
    //average the samples into levels
    pointOptions.clear();
    int numPointsToGet = (int)ceil(sampleOptions.size() / (samplesPerPoint));
    for(int i = 0; i < numPointsToGet; ++i)
    {
        auto sum = 0.0f;
        for(int n = 0; n < samplesPerPoint; ++n)
        {
            auto index = (samplesPerPoint * i) + n;
            sum += sampleOptions[index];
        }
        pointOptions.push_back(sum / samplesPerPoint);
    }
    //find a rising edge
    int startingIndex = 0;
    bool edgeFound = false;
    for(int i = 0; i < numPointsToGet; ++i)
    {
        if(pointOptions[i] < 0 && pointOptions[i + 10] > 0)
        {
            startingIndex = i;
            edgeFound = true;
            break;
        }
    }
    //put the right points into the screen vector
    pointsOnScreen.clear();
    for(int i = 0; i < pointsPerFrame; ++i)
    {
        pointsOnScreen.push_back(pointOptions[i + startingIndex]);
    }
    
}

void OscilloscopeComponent::paint (juce::Graphics& g)
{
    if(pointsOnScreen.size() != 0)
    {
    g.setColour(backgroundColor);
    g.fillAll();
    g.setColour(traceColor);
    juce::Path trace;
    juce::Rectangle<float> area = getLocalBounds().toFloat();
    trace.scaleToFit(area.getX(), area.getY(), area.getWidth(), area.getHeight(), true);
    auto xDelta = area.getWidth() / pointsPerFrame;
    float amplitude = 100;
    for(int i = 0; i < pointsPerFrame; ++i)
    {
        float newX = xDelta * i;
        float newY = (pointsOnScreen[i] * amplitude) + (area.getHeight() / 2);
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
    
    auto strokeType = juce::PathStrokeType(1.0f);
    g.strokePath(trace, strokeType);
    }
}
