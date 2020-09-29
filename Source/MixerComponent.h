/*
  ==============================================================================

    MixerComponenr.h
    Created: 29 Sep 2020 10:38:46am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscMixerComponent : public juce::Component
{
public:
    //functions
    OscMixerComponent();
    ~OscMixerComponent() {}
    void attachToTree(juce::AudioProcessorValueTreeState* tree);
    void resized() override;
    //data
    juce::Slider levelSlider0;
    juce::Slider levelSlider1;
    juce::Slider levelSlider2;
    juce::Slider masterSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> level0Attach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> level1Attach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> level2Attach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterLevelAttach;
    
};
