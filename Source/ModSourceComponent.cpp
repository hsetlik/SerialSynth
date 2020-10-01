/*
  ==============================================================================

    ModSourceComponent.cpp
    Created: 25 Sep 2020 11:25:38am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "ModSourceComponent.h"

//==============================================================================
ModSourceComponent::ModSourceComponent(juce::String desc, juce::DragAndDropContainer* parentContainer) : parent(parentContainer), description(desc)
{
    //printf("Component %s created\n", desc.toUTF16());
}

void ModSourceComponent::paint (juce::Graphics& g)
{
    juce::Rectangle<float> area = getLocalBounds().toFloat();
    g.setColour(ringColor);
    g.fillEllipse(area);
    g.setColour(centerColor);
    g.fillEllipse(area.reduced(5.0));
}

void ModSourceComponent::resized()
{

}

LfoComponent::LfoComponent(juce::String desc, juce::DragAndDropContainer* parentContainer, int index) : modSource(desc, parentContainer), LfoIndex(index)
{
    addAndMakeVisible(&modSource);
    addAndMakeVisible(&freqSlider);
    addAndMakeVisible(&waveform);
    
    freqSlider.setSliderStyle(juce::Slider::Rotary);
    freqSlider.setRange(0.01f, 20.0f); //range goes into very low audio rate
    freqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    freqSlider.setSkewFactorFromMidPoint(1.5);
    freqSlider.setNumDecimalPlacesToDisplay(0);
    
    waveform.addItem("Sine", 1);
    waveform.addItem("Saw", 2);
    waveform.addItem("Triangle", 3);
    waveform.addItem("Square", 4);
    waveform.setSelectedItemIndex(1);
    waveform.setEditableText(false);
    
}

LfoComponent::LfoComponent(juce::String desc, juce::DragAndDropContainer* parentContainer, int index, juce::Colour modSourceColor) : modSource(desc, parentContainer), LfoIndex(index)
{
    addAndMakeVisible(&modSource);
    addAndMakeVisible(&freqSlider);
    addAndMakeVisible(&waveform);
    
    modSource.changeCenterColor(modSourceColor);
    
    freqSlider.setSliderStyle(juce::Slider::Rotary);
    freqSlider.setRange(0.01f, 20.0f); //range goes into very low audio rate
    freqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    freqSlider.setSkewFactorFromMidPoint(1.5);
    freqSlider.setNumDecimalPlacesToDisplay(0);
    
    
    waveform.addItem("Sine", 1);
    waveform.addItem("Saw", 2);
    waveform.addItem("Triangle", 3);
    waveform.addItem("Square", 4);
    waveform.setSelectedItemIndex(1);
    waveform.setEditableText(false);
}

void LfoComponent::paint(juce::Graphics &g)
{
    juce::Colour background = modSource.getCenterColor();
    auto darkened = color.blend(background, juce::Colours::black, 0.1);
    g.fillAll(darkened);
    juce::Rectangle<float> area = getLocalBounds().toFloat();
    juce::Colour outlineColor = color.RGBColor(210, 210, 210);
    g.setColour(outlineColor);
    g.drawRect(area, 1.0f);
}

void LfoComponent::resized()
{
    int n = getHeight() / 10;
    modSource.setBounds(2.5 * n, n, 2 * n,  2 * n);
    freqSlider.setBounds(n, 4.65 * n, 5 * n, 5 * n);
    waveform.setBounds(5 * n, 1.5 * n, 5 * n, 1.5 * n);
    
}

TabbedLfoComponent::TabbedLfoComponent(juce::DragAndDropContainer* parentContainer) : juce::TabbedComponent(juce::TabbedButtonBar::TabsAtTop)
{
    auto color0 = color.RGBColor(191, 227, 242);
    auto color1 = color.RGBColor(210, 87, 91);
    auto color2 = color.RGBColor(240, 175, 86);
    
    contents.add(new LfoComponent("lfo0Source", parentContainer, 0, color0));
    contents.add(new LfoComponent("lfo1Source", parentContainer, 1, color1));
    contents.add(new LfoComponent("lfo2Source", parentContainer, 2, color2));
    
    setTabBarDepth(10);
    
    addTab("LFO 1", color0, contents[0], false);
    addTab("LFO 2", color1, contents[1], false);
    addTab("LFO 3", color2, contents[2], false);
    
    setCurrentTabIndex(0);
}

void TabbedLfoComponent::attachAllToTree(juce::AudioProcessorValueTreeState *target)
{
    contents[0]->attachToTree(target);
    contents[1]->attachToTree(target);
    contents[2]->attachToTree(target);
}

EnvelopeComponent::EnvelopeComponent(juce::String desc, juce::DragAndDropContainer* parentContainer, int index, juce::Colour modSourceColor) :
modSource(desc, parentContainer),
graph(&aSlider, &dSlider, &sSlider, &rSlider),
envIndex(index)
{
    addAndMakeVisible(&modSource);
    modSource.changeCenterColor(modSourceColor);
    
    addAndMakeVisible(&graph);
    
    addAndMakeVisible(&aSlider);
    aSlider.setSliderStyle(juce::Slider::Rotary);
    aSlider.setRange(1.0f, 20000.0f);
    aSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    aSlider.setSkewFactorFromMidPoint(150);
    aSlider.setNumDecimalPlacesToDisplay(0);
    
    addAndMakeVisible(&dSlider);
    dSlider.setSliderStyle(juce::Slider::Rotary);
    dSlider.setRange(1.0f, 20000.0f);
    dSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    dSlider.setSkewFactorFromMidPoint(150);
    dSlider.setNumDecimalPlacesToDisplay(0);
    
    addAndMakeVisible(&sSlider);
    sSlider.setSliderStyle(juce::Slider::Rotary);
    sSlider.setRange(0.0001f, 1.0f);
    sSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    sSlider.setSkewFactorFromMidPoint(0.5f);
    sSlider.setNumDecimalPlacesToDisplay(0);
    
    addAndMakeVisible(&rSlider);
    rSlider.setSliderStyle(juce::Slider::Rotary);
    rSlider.setRange(1.0f, 20000.0f);
    rSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    rSlider.setSkewFactorFromMidPoint(150);
    rSlider.setNumDecimalPlacesToDisplay(0);
}

void EnvelopeComponent::paint(juce::Graphics &g)
{
    juce::Colour background = modSource.getCenterColor();
    auto darkened = color.blend(background, juce::Colours::black, 0.1);
    g.fillAll(darkened);
    juce::Rectangle<float> area = getLocalBounds().toFloat();
    juce::Colour outlineColor = color.RGBColor(210, 210, 210);
    g.setColour(outlineColor);
    g.drawRect(area, 1.0f);
}

void EnvelopeComponent::resized()
{
    int n = getWidth() / 40;
    
    aSlider.setBounds(2 * n, 8 * n, 6 * n, 7 * n);
    dSlider.setBounds(12 * n, 8 * n, 6 * n, 7 * n);
    sSlider.setBounds(22 * n, 8 * n, 6 * n, 7 * n);
    rSlider.setBounds(32 * n, 8 * n, 6 * n, 7 * n);
    modSource.setBounds(2 * n, n, 3.5 * n, 3.5 * n);
    graph.setBounds(8 * n, n, 10 * n, 6 * n);
}


TabbedEnvelopeComponent::TabbedEnvelopeComponent(juce::DragAndDropContainer* parentContainer) : juce::TabbedComponent(juce::TabbedButtonBar::TabsAtTop)
{
    auto color0 = color.RGBColor(191, 227, 242);
    auto color1 = color.RGBColor(210, 87, 91);
    auto color2 = color.RGBColor(240, 175, 86);
    
    contents.add(new EnvelopeComponent("env0Source", parentContainer, 0, color0));
    contents.add(new EnvelopeComponent("env1Source", parentContainer, 1, color1));
    contents.add(new EnvelopeComponent("env2Source", parentContainer, 2, color2));
    
    setTabBarDepth(10);
    
    addTab("ENV 1", color0, contents[0], false);
    addTab("ENV 2", color1, contents[1], false);
    addTab("ENV 3", color2, contents[2], false);
    
    setCurrentTabIndex(0);
    juce::Path* trace0 = &contents[0]->graph.trace;
    juce::Path* trace1 = &contents[1]->graph.trace;
    juce::Path* trace2 = &contents[2]->graph.trace;
    
    contents[0]->graph.addSecondTrace(trace1);
    contents[0]->graph.addThirdTrace(trace2);
    
    contents[1]->graph.addSecondTrace(trace0);
    contents[1]->graph.addThirdTrace(trace2);
    
    contents[2]->graph.addSecondTrace(trace0);
    contents[2]->graph.addThirdTrace(trace1);
    
    contents[0]->graph.setTraceColors(color0, color1, color2);
    contents[1]->graph.setTraceColors(color1, color0, color2);
    contents[2]->graph.setTraceColors(color2, color0, color1);
}

void TabbedEnvelopeComponent::attachAllToTree(juce::AudioProcessorValueTreeState *target)
{
    contents[0]->attachToTree(target);
    contents[1]->attachToTree(target);
    contents[2]->attachToTree(target);
}
