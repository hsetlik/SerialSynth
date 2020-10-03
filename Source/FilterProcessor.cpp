/*
  ==============================================================================

    FilterProcessor.cpp
    Created: 1 Oct 2020 7:45:26am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "FilterProcessor.h"
/*
FilterProcessor::FilterProcessor(VoiceModGenerators* gens, HarmonicOscillator* osc) :
cutoffDest("cutoffDest", 0, gens),
resDest("resDest", 0, gens),
mixDest("filterMixDest", 0, gens),
oscillator(osc)
{
    
}

void FilterProcessor::updateModulations()
{
    if(cutoffDest.sources.size() != 0)
    {
        auto delta = cutoffDest.getParameterDelta();
        auto maxIncrease = 20000.0f - currentCutoff;
        auto maxDecrease = currentCutoff;
        if(delta > 0)
            currentCutoff += (maxIncrease * delta);
        else
            currentCutoff += (maxDecrease * delta);
    }
    if(resDest.sources.size() != 0)
    {
        auto delta = resDest.getParameterDelta();
        auto maxIncrease = 100.0f - currentRes;
        auto maxDecrease = currentRes;
        if(delta > 0)
            currentRes += (maxIncrease * delta);
        else
            currentRes += (maxDecrease * delta);
    }
    if(mixDest.sources.size() != 0)
    {
        auto delta = mixDest.getParameterDelta();
        auto maxIncrease = 1.0f - currentMix;
        auto maxDecrease = currentMix;
        if(delta > 0)
            currentMix += (maxIncrease * delta);
        else
            currentMix += (maxDecrease * delta);
    }
}
*/
