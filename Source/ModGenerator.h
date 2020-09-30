/*
  ==============================================================================

    ModGenerator.h
    Created: 26 Sep 2020 11:58:26am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "maximilian.h"

/*
 abstract base class for anything that generates a modulation signal as a floating point number between 0 and 1
 override the getNextSampleValue function to do calculations from the source
 */
class ModGenerator
{
public:
    ModGenerator(juce::String type) : typeId(type)
    {
    }
    virtual ~ModGenerator() {}
    virtual float getNextSampleValue()
    {
        return 0.0f;
    }
    juce::String typeId;
    
};

class LfoProcessor : public ModGenerator
{
public:
    LfoProcessor(juce::String idStr) : ModGenerator(idStr)
    {
        lfoRate = 1.0f;
    }
    ~LfoProcessor(){}
    void setRate(float newRate)
    {
        lfoRate = newRate;
    }
    void setWaveType(juce::String newType)
    {
        currentWaveType = newType;
    }
    float getNextSampleValue() override
    {
        float sample = 0.0;
        if(currentWaveType == "Sine")
            sample = ((osc.sinebuf(lfoRate) + 1.0f) / 2.0f); //changes range from -1, 1 to 0, 1
        else if(currentWaveType == "Saw")
            sample = ((osc.saw(lfoRate) + 1.0f) / 2.0f);
        else if(currentWaveType == "Triangle")
            sample = ((osc.triangle(lfoRate) + 1.0f) / 2.0f);
        else if(currentWaveType == "Square")
            sample = ((osc.square(lfoRate) + 1.0f) / 2.0f);
        return sample;
    }
private:
    juce::String currentWaveType;
    float lfoRate = 0;
    maxiOsc osc;
};

class EnvelopeProcessor : public ModGenerator
{
public:
    EnvelopeProcessor(juce::String idStr) : ModGenerator(idStr)
    {
        
    }
    ~EnvelopeProcessor() {}
    float getNextSampleValue() override
    {
        return(envelope.adsr(1.0, envelope.trigger));
    }
    void setAttack(float value)
    {
        envelope.setAttack(value);
        
    }
    void setDecay(float value)
    {
        envelope.setDecay(value);
        
    }
    void setSustain(float value)
    {
        envelope.setSustain(value);
        
    }
    void setRelease(float value)
    {
        envelope.setRelease(value);
        
    }
    void triggerOn()
    {
        envelope.trigger = 1;
    }
    void triggerOff()
    {
        envelope.trigger = 0;
    }
    float attackValue()
    {
        return envelope.attack;
    }
    float decayValue()
    {
        return envelope.decay;
    }
    float sustainValue()
    {
        return envelope.sustain;
    }
    float releaseValue()
    {
        return envelope.release;
    }
private:
    maxiEnv envelope;
    
};


class VoiceModGenerators
//each voice needs to own one of these, it stores all the ModGenerator subclasses and allows the oscillators to be intialized with a reference to this object
{
public:
    VoiceModGenerators()
    {
        //every mod source for the synth needs to be added here like so
        gens.add(new LfoProcessor("lfo0Source"));
        pLfo0 = dynamic_cast<LfoProcessor*>(gens.getLast());
        gens.add(new LfoProcessor("lfo1Source"));
        pLfo1 = dynamic_cast<LfoProcessor*>(gens.getLast());
        gens.add(new LfoProcessor("lfo2Source"));
        pLfo2 = dynamic_cast<LfoProcessor*>(gens.getLast());
        
        gens.add(new EnvelopeProcessor("env0Source"));
        pEnv0 = dynamic_cast<EnvelopeProcessor*>(gens.getLast());
        gens.add(new EnvelopeProcessor("env1Source"));
        pEnv1 = dynamic_cast<EnvelopeProcessor*>(gens.getLast());
        gens.add(new EnvelopeProcessor("env2Source"));
        pEnv2 = dynamic_cast<EnvelopeProcessor*>(gens.getLast());
    }
    ~VoiceModGenerators() {}
    void allTriggersOn()
    {
        pEnv0->triggerOn();
        pEnv1->triggerOn();
        pEnv2->triggerOn();
    }
    void allTriggersOff()
    {
        pEnv0->triggerOff();
        pEnv1->triggerOff();
        pEnv2->triggerOff();
    }
    juce::OwnedArray<ModGenerator> gens;
    LfoProcessor* pLfo0;
    LfoProcessor* pLfo1;
    LfoProcessor* pLfo2;
    EnvelopeProcessor* pEnv0;
    EnvelopeProcessor* pEnv1;
    EnvelopeProcessor* pEnv2;
};



