/*
  ==============================================================================

    SpectrumSynthVoice.h
    Created: 22 Sep 2020 10:29:40am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SpectrumOscillator.h"
#include "ModProcessor.h"
#include "MixProcessor.h"
#include "FilterProcessor.h"

class SpectrumSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int /*midiNoteNumber*/) //just plays this sound for any midi note
    {
        return true;
    }
    bool appliesToChannel(int /*midiChannel*/) //plays the sound on both channels
    {
        return true;
    }
};

class SpectrumVoice : public juce::SynthesiserVoice
{
public:
    SpectrumVoice() : filter(juce::dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000.0f, 0.1f))
    {
        for(int i = 0; i < 3; ++i)
        {
            allOscs.add(new HarmonicOscillator(40, i, &allGens));
        }
    }
    
    float getEnvAttack(int index);
    float getEnvDecay(int index);
    float getEnvSustain(int index);
    float getEnvRelease(int index);
    void setLfoRate(std::atomic<float>* value, int index);
    void setModAttack(std::atomic<float>* value, int index);
    void setModDecay(std::atomic<float>* value, int index);
    void setModSustain(std::atomic<float>* value, int index);
    void setModRelease(std::atomic<float>* value, int index);
    void setOscLevel(std::atomic<float>* value, int n)
    {
        mixer.setOscLevel(*value, n);
    }
    void setMasterLevel(std::atomic<float>* value)
    {
        mixer.masterLevel = *value;
    }
    void setLfoWave(std::atomic<float>* value, int n);
    //PARAMETER INPUT FUNCTIONS
    void setVoiceP0(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = allOscs[index];
        if(thisOsc->p0Snap)
            thisOsc->currentP0 = floor(*value);
        else
            thisOsc->currentP0 = *value;
    }
    void setVoiceP1(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = allOscs[index];
        if(thisOsc->p1Snap)
            thisOsc->currentP1 = floor(*value);
       else
           thisOsc->currentP1 = *value;
    }
    void setVoiceP1Snap(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = allOscs[index];
        thisOsc->p1Snap = (bool)(*value);
    }
    void setVoiceP0Snap(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = allOscs[index];
        thisOsc->p0Snap = (bool)(*value);
    }
    void setNumHarmonics(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = allOscs[index];
        thisOsc->currentHarmonicCount = floor(*value);
    }
    void setAlgChoice(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = allOscs[index];
        thisOsc->secondAlgOn = (bool)(*value);
    }
    void setDetune(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = allOscs[index];
        thisOsc->currentDetune = *value;
    }
    void setAttack(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = allOscs[index];
        thisOsc->envelope1.setAttack(*value);
    }
    void setDecay(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = allOscs[index];
        thisOsc->envelope1.setDecay(*value);
    }
    void setSustain(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = allOscs[index];
        thisOsc->envelope1.setSustain(*value);
    }
    void setRelease(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = allOscs[index];
        thisOsc->envelope1.setRelease(*value);
    }
    //FILTER============================
    void updateFilter();
    //END PARAMETER INPUTS================================
    bool canPlaySound(juce::SynthesiserSound* sound)
    {
        return dynamic_cast<SpectrumSound*>(sound) != nullptr;
    }
    void prepareVoice(double sampleRate, int samplesPerBlock);
    
    void startNote (int midiNoteNumber,
                    float velocity,
                    juce::SynthesiserSound *sound,
                    int currentPitchWheelPosition)
    {
        auto newPitch = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        for(int i = 0; i < 3; ++i)
        {
            allOscs[i]->setFundamental(newPitch);
            allOscs[i]->envelope1.trigger = 1;
            allOscs[i]->lastMidiNote = midiNoteNumber;
        }
        allGens.allTriggersOn();
    }
    void stopNote (float velocity, bool allowTailOff)
    {
        for(int i = 0; i < 3; ++i)
        {
            allOscs[i]->envelope1.trigger = 0;
            
        }
        allGens.allTriggersOff();
        allowTailOff = true;
        if(velocity == 0)
            clearCurrentNote();
    }
    //===========================================
    void pitchWheelMoved(int newPitchWheelVal)
    {
        
    }
    //=============================================
    void controllerMoved(int controllerNumber, int controllerValue)
    {
        
    }
    //===============================================
    void aftertouchChanged (int newAftertouchValue)
    {

    }
    //==============================================
    void channelPressureChanged (int newChannelPressureValue)
    {
        
    }
    //====================================================
    void updateJuceFilter()
    {
        
    }
    
    //===============================================
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
    {
        for(int i = 0; i < numSamples; ++i)
        {
            float sum = 0.0f;
            for(int g = 0; g < 3; ++g)
            {
                allOscs[g]->applyModulations();
                float newPreEnv = allOscs[g]->getNextSample();
                newPreEnv *= mixer.getOscLevel(g);
                sum += (allOscs[g]->envelope1.adsr(newPreEnv, allOscs[g]->envelope1.trigger));
            }
            float rawSample = sum / 3.0f;
            rawSample *= mixer.masterLevel;
            for(int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, rawSample);
            }
            ++startSample;
        }
        
    }
    //==============================================
    void setCurrentPlaybackSampleRate (double newRate)
    {
        
    }
    double lastSampleRate = 44100;
    
    juce::OwnedArray<HarmonicOscillator> allOscs;
    VoiceModGenerators allGens;
    MixerProcessor mixer;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> filter;
};
