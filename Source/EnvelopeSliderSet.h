/*
  ==============================================================================

    EnvelopeSliderSet.h
    Created: 24 Sep 2020 6:16:13pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class EnvelopeSliderSet  : public juce::Component
{
public:
    EnvelopeSliderSet(int index) : oscIndex(index)
    {
        addAndMakeVisible(aSlider);
        aSlider.setRange(1.0f, 15000.0f);
        aSlider.setSliderStyle(juce::Slider::Rotary);
        aSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        aSlider.setNumDecimalPlacesToDisplay(0);
        
        addAndMakeVisible(dSlider);
        dSlider.setRange(1.0f, 15000.0f);
        dSlider.setSliderStyle(juce::Slider::Rotary);
        dSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        dSlider.setNumDecimalPlacesToDisplay(0);
        
        addAndMakeVisible(sSlider);
        sSlider.setRange(0.0f, 1.0f);
        sSlider.setSliderStyle(juce::Slider::Rotary);
        sSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
        sSlider.setNumDecimalPlacesToDisplay(2);
        
        addAndMakeVisible(rSlider);
        rSlider.setRange(1.0f, 15000.0f);
        rSlider.setSliderStyle(juce::Slider::Rotary);
        rSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 45, 20);
        rSlider.setNumDecimalPlacesToDisplay(0);
    }
    ~EnvelopeSliderSet() override
    {
        
    }
    void resized() override
    {
        int n = getWidth() / 20;
        aSlider.setBounds(n, n, 3 * n, 4 * n);
        dSlider.setBounds(6 * n, n, 3 * n, 4 * n);
        sSlider.setBounds(11 * n, n, 3 * n, 4 * n);
        rSlider.setBounds(16 * n, n, 3 * n, 4 * n);
    }
    void paint(juce::Graphics& g) override
    {
        
    }
    juce::Slider aSlider;
    juce::Slider dSlider;
    juce::Slider sSlider;
    juce::Slider rSlider;
private:
    int oscIndex;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeSliderSet)
};
