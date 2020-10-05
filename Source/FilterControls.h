/*
  ==============================================================================

    FilterControls.h
    Created: 1 Oct 2020 7:28:02am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "maximilian.h"
#include "MultiModDestination.h"
#include "RGBColor.h"
class FilterControls : public juce::Component
{
public:
    //functions
    FilterControls(SpectrumTable1AudioProcessor& proc, juce::Slider::Listener* lstnr) :
    mixKnob("filterMixDest", false, 0.0f, 1.0f, 1, lstnr, proc, juce::Slider::Rotary),
    resKnob("resDest", false, 1.0f, 100.0f, 1, lstnr, proc, juce::Slider::Rotary),
    cutoffKnob("cutoffDest", false, 1.0f, 20000.0f, 20000.0f, lstnr, proc, juce::Slider::Rotary)
    {
        addAndMakeVisible(cutoffKnob);
        addAndMakeVisible(resKnob);
        addAndMakeVisible(mixKnob);
        
        cutoffKnob.paramSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 45, 15);
        resKnob.paramSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 45, 15);
        mixKnob.paramSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 45, 15);
    }
    ~FilterControls() {}
    void attachToTree(juce::AudioProcessorValueTreeState* tree);
    void paint(juce::Graphics& g) override;
    void resized() override;
    //data
    MultiModDestination mixKnob;
    MultiModDestination resKnob;
    MultiModDestination cutoffKnob;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffAttach;
private:
    ColorCreator color;
    
};
