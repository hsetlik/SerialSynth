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
    }
    ~VoiceModGenerators() {}
    juce::OwnedArray<ModGenerator> gens;
    LfoProcessor* pLfo0;
    LfoProcessor* pLfo1;
    LfoProcessor* pLfo2;
};



