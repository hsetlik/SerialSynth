/*
  ==============================================================================

    SpectrumSynthVoice.cpp
    Created: 3 Oct 2020 10:09:08am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "SpectrumSynthVoice.h"

void SpectrumVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    //updateJuceFilter();
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
float SpectrumVoice::getEnvAttack(int index)
{
    EnvelopeProcessor* thisEnv;
    switch(index)
    {
        case 0:
        {
            thisEnv = allGens.pEnv0;
            break;
        }
        case 1:
        {
            thisEnv = allGens.pEnv1;
            break;
        }
        case 2:
        {
            thisEnv = allGens.pEnv2;
            break;
        }
    }
    return thisEnv->attackValue();
}
float SpectrumVoice::getEnvDecay(int index)
{
    EnvelopeProcessor* thisEnv;
    switch(index)
    {
        case 0:
        {
            thisEnv = allGens.pEnv0;
            break;
        }
        case 1:
        {
            thisEnv = allGens.pEnv1;
            break;
        }
        case 2:
        {
            thisEnv = allGens.pEnv2;
            break;
        }
    }
    return thisEnv->decayValue();
}
float SpectrumVoice::getEnvSustain(int index)
{
    EnvelopeProcessor* thisEnv;
    switch(index)
    {
        case 0:
        {
            thisEnv = allGens.pEnv0;
            break;
        }
        case 1:
        {
            thisEnv = allGens.pEnv1;
            break;
        }
        case 2:
        {
            thisEnv = allGens.pEnv2;
            break;
        }
    }
    return thisEnv->sustainValue();
}
float SpectrumVoice::getEnvRelease(int index)
{
    EnvelopeProcessor* thisEnv;
    switch(index)
    {
        case 0:
        {
            thisEnv = allGens.pEnv0;
            break;
        }
        case 1:
        {
            thisEnv = allGens.pEnv1;
            break;
        }
        case 2:
        {
            thisEnv = allGens.pEnv2;
            break;
        }
    }
    return thisEnv->releaseValue();
}

void SpectrumVoice::setLfoRate(std::atomic<float>* value, int index)
{
    LfoProcessor* thisLfo;
    switch(index)
    {
        case 0:
        {
            thisLfo = allGens.pLfo0;
            break;
        }
        case 1:
        {
            thisLfo = allGens.pLfo1;
            break;
        }
        case 2:
        {
            thisLfo = allGens.pLfo2;
            break;
        }
    }
    thisLfo->setRate(*value);
}
void SpectrumVoice::setModAttack(std::atomic<float>* value, int index)
{
    EnvelopeProcessor* thisEnv;
    switch(index)
    {
        case 0:
        {
            thisEnv = allGens.pEnv0;
            break;
        }
        case 1:
        {
            thisEnv = allGens.pEnv1;
            break;
        }
        case 2:
        {
            thisEnv = allGens.pEnv2;
            break;
        }
    }
    thisEnv->setAttack(*value);
}
void SpectrumVoice::setModDecay(std::atomic<float>* value, int index)
{
    EnvelopeProcessor* thisEnv;
    switch(index)
    {
        case 0:
        {
            thisEnv = allGens.pEnv0;
            break;
        }
        case 1:
        {
            thisEnv = allGens.pEnv1;
            break;
        }
        case 2:
        {
            thisEnv = allGens.pEnv2;
            break;
        }
    }
    thisEnv->setDecay(*value);
}
void SpectrumVoice::setModSustain(std::atomic<float>* value, int index)
{
    EnvelopeProcessor* thisEnv;
    switch(index)
    {
        case 0:
        {
            thisEnv = allGens.pEnv0;
            break;
        }
        case 1:
        {
            thisEnv = allGens.pEnv1;
            break;
        }
        case 2:
        {
            thisEnv = allGens.pEnv2;
            break;
        }
    }
    thisEnv->setSustain(*value);
}
void SpectrumVoice::setModRelease(std::atomic<float>* value, int index)
{
    EnvelopeProcessor* thisEnv;
    switch(index)
    {
        case 0:
        {
            thisEnv = allGens.pEnv0;
            break;
        }
        case 1:
        {
            thisEnv = allGens.pEnv1;
            break;
        }
        case 2:
        {
            thisEnv = allGens.pEnv2;
            break;
        }
    }
    thisEnv->setRelease(*value);
}
void SpectrumVoice::setLfoWave(std::atomic<float>* value, int n)
{
    LfoProcessor* thisLfo;
    switch(n)
    {
        case 0:
        {
            thisLfo = allGens.pLfo0;
            break;
        }
        case 1:
        {
            thisLfo = allGens.pLfo1;
            break;
        }
        case 2:
        {
            thisLfo = allGens.pLfo2;
            break;
        }
    }
    int choiceIndex = (int)*value;
    switch(choiceIndex)
    {
        case 0:
        {
            thisLfo->setWaveType("Sine");
            break;
        }
        case 1:
        {
            thisLfo->setWaveType("Saw");
            break;
        }
        case 2:
        {
            thisLfo->setWaveType("Triangle");
            break;
        }
        case 3:
        {
            thisLfo->setWaveType("Square");
            break;
        }
    }
}
