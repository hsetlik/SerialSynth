/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SpectrumSynthVoice.h"
#include "OscilloscopeComponent.h"
#include "MaxiOscGraph.h"
//==============================================================================
/**
*/
class SpectrumTable1AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SpectrumTable1AudioProcessor();
    ~SpectrumTable1AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    void setModDepth(juce::String sourceId, juce::String destId, int index, float value);
    void addVoiceModulation(juce::String sourceId, juce::String destId, int index);
    void removeVoiceModulation(juce::String sourceId, juce::String destId, int index, juce::Component* mSlider);
    
    SpectrumVoice* thisVoice;
    juce::AudioProcessorValueTreeState tree;
    std::vector<GraphValueSet> allGraphValues;
    //GraphValueSet graphValues1;
    
   
private:
    juce::Synthesiser synth;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrumTable1AudioProcessor)
};
