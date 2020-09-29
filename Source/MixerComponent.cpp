/*
  ==============================================================================

    MixerComponenr.cpp
    Created: 29 Sep 2020 10:38:46am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "MixerComponent.h"

OscMixerComponent::OscMixerComponent()
{
    addAndMakeVisible(&levelSlider0);
    addAndMakeVisible(&levelSlider1);
    addAndMakeVisible(&levelSlider2);
    addAndMakeVisible(&masterSlider);
    
    levelSlider0.setRange(0.0f, 0.1f);
    levelSlider1.setRange(0.0f, 0.1f);
    levelSlider2.setRange(0.0f, 0.1f);
    masterSlider.setRange(0.0f, 0.1f);
    
    levelSlider0.setSliderStyle(juce::Slider::Rotary);
    levelSlider1.setSliderStyle(juce::Slider::Rotary);
    levelSlider2.setSliderStyle(juce::Slider::Rotary);
    masterSlider.setSliderStyle(juce::Slider::Rotary);
    
    levelSlider0.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 15);
    levelSlider1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 15);
    levelSlider2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 15);
    masterSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 15);
    
}

void OscMixerComponent::attachToTree(juce::AudioProcessorValueTreeState *tree)
{
    level0Attach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*tree, "osc0LevelParam", levelSlider0));
    level1Attach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*tree, "osc1LevelParam", levelSlider1));
    level2Attach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*tree, "osc2LevelParam", levelSlider2));
    masterLevelAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*tree, "masterLevelParam", masterSlider));
}

void OscMixerComponent::resized()
{
    int n = getHeight() / 20;
    levelSlider0.setBounds(n, n, 3 * n, 4 * n);
    levelSlider1.setBounds(n, 6 * n, 3 * n, 4 * n);
    levelSlider2.setBounds(n, 11 * n, 3 * n, 4 * n);
    masterSlider.setBounds(n, 16 * n, 3 * n, 4 * n);
    
}
