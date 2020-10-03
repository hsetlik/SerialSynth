/*
  ==============================================================================

    FilterControls.cpp
    Created: 1 Oct 2020 7:28:02am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "FilterControls.h"


void FilterControls::attachToTree(juce::AudioProcessorValueTreeState *tree)
{
    cutoffAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*tree, "cutoffParam", cutoffKnob.paramSlider));
    resAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*tree, "resParam", resKnob.paramSlider));
    mixAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*tree, "filterMixParam", cutoffKnob.paramSlider));
    
    cutoffKnob.paramSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 45, 15);
    resKnob.paramSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 45, 15);
    mixKnob.paramSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 45, 15);
}

void FilterControls::resized()
{
    int n = getWidth() / 21;
    cutoffKnob.setBounds(15 * n, n, 5 * n, 8 * n);
    resKnob.setBounds(8 * n, n, 5 * n, 8 * n);
    mixKnob.setBounds(n, n, 5 * n, 8 * n);
}

void FilterControls::paint(juce::Graphics &g)
{
    g.setColour(color.RGBColor(226, 76, 86));
    g.fillAll();
}
