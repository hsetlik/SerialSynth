/*
  ==============================================================================

    OscilloscopeComponent.h
    Created: 23 Sep 2020 10:26:42am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

const int pointsPerFrame = 256;
//==============================================================================
/*
*/
class OscilloscopeSource
{
public:
    OscilloscopeSource()
    {
        sourceCreated = true;
    }
    ~OscilloscopeSource()
    {
        relevantBuffers.clear();
    }
    void addBuffer(juce::AudioBuffer<float>& bufferToCopy)
    {
        relevantBuffers.push_back(bufferToCopy);
        if(relevantBuffers.size() > 15)
            relevantBuffers.pop_front();
        relevantBuffers.shrink_to_fit();
    }
    bool sourceCreated = false;
    bool buffersAdded = false;
    int bufferSize;
    float fundamental = 440.0f;
    float sampleRate;
    int buffersToHold;
    std::deque<juce::AudioBuffer<float>> relevantBuffers;
    
};
class OscilloscopeComponent  : public juce::Component, public juce::Timer
{
public:
    //functions
    OscilloscopeComponent(OscilloscopeSource* src);
    ~OscilloscopeComponent()
    {
        availableBuffers.clear();
    }
    void resizeToFrequency();
    void pullBuffers();
    void trigger();
    void paint (juce::Graphics&) override;
    void timerCallback() override
    {
        resizeToFrequency();
        pullBuffers();
        if(samplesPerPoint != 0)
        {
            trigger();
            repaint();
        }
        else
            samplesPerPoint = 3;
    }
    //data
    bool finishedInitializing = false;
private:
    OscilloscopeSource* source;
    int numBuffersToGet;
    int samplesPerPoint;
    std::vector<juce::AudioBuffer<float>> availableBuffers;
    std::vector<float> sampleOptions;
    std::vector<float> pointOptions;
    std::vector<float> pointsOnScreen;
    juce::Colour backgroundColor = juce::Colours::darkgrey;
    juce::Colour traceColor = juce::Colours::orange;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscilloscopeComponent)
};
