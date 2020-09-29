/*
  ==============================================================================

    SpectrumOscillator.cpp
    Created: 22 Sep 2020 12:03:30pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "SpectrumOscillator.h"

HarmonicOscillator::HarmonicOscillator(int maxOvertones, int index, VoiceModGenerators* genSet) :
p1ModProc("p1Dest", index, gens),
p0ModProc("p0Dest", index, gens),
nModProc("nDest", index, gens),
gens(genSet),
maxHarmonicCount(maxOvertones)
{
    /*
    envelope1.setAttack(20.0f);
    envelope1.setRelease(85.0f);
    envelope1.setSustain(0.6f);
    envelope1.setRelease(150.0f);
     */
    for(int i = 0; i < maxHarmonicCount; ++i)
    {
        std::unique_ptr<HarmonicData> newHarmonic(new HarmonicData(i));
        std::unique_ptr<maxiOsc> newOsc(new maxiOsc);
        harmonics.push_back(*newHarmonic);
        oscillators.push_back(*newOsc);
    }
}
void HarmonicOscillator::applyModulations()
{
    if(p0ModProc.sources.size() != 0)
    {
    auto p0Delta = p0ModProc.getParameterDelta();
    auto maxIncrease = 15.0 - currentP0;
    auto maxDecrease = currentP0;
    if(p0Delta > 0)
        currentP0 += (maxIncrease * p0Delta);
    else
        currentP0 += (maxDecrease * p0Delta);
    }
    if(p1ModProc.sources.size() != 0)
    {
    auto p1Delta = p1ModProc.getParameterDelta();
    auto p1maxIncrease = 15.0 - currentP1;
    auto p1maxDecrease = currentP1;
    if(p1Delta > 0)
        currentP1 += (p1maxIncrease * p1Delta);
    else
        currentP1 += (p1maxDecrease * p1Delta);
    }
    if(nModProc.sources.size() != 0)
    {
    auto nDelta = nModProc.getParameterDelta();
    auto nMaxIncrease = 40.0 - currentHarmonicCount;
    auto nMaxDecrease = currentHarmonicCount;
    if(nDelta > 0)
        currentHarmonicCount += (nMaxIncrease * nDelta);
    else
        currentHarmonicCount += (nMaxDecrease * nDelta);
    }
    
    
}

float HarmonicOscillator::getNextSample()
{
    applyModulations();
    float returnSample = 0.0f;
    for(int i = 0; i < (int)floor(currentHarmonicCount); ++i)
    {
        double newFreq;
        double newAmp;
        if(secondAlgOn)
        {
            newFreq = fundamental * harmonics[i].getFrequencyFactor2(currentP1, currentP0);
            newAmp = harmonics[i].getAmplitudeFactor2(currentP1, currentP0);
        }
        else
        {
            newFreq = fundamental * harmonics[i].getFrequencyFactor1(currentP1);
            newAmp = harmonics[i].getAmplitudeFactor1(currentP0);
        }
        float newPreEnv = oscillators[i].sinewave(newFreq);
        returnSample += (newPreEnv * newAmp);
    }
    return returnSample;
}
