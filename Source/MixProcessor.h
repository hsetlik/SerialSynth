/*
  ==============================================================================

    MixProcessor.h
    Created: 29 Sep 2020 11:09:26am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MixerProcessor
{
public:
    MixerProcessor()
    {
        
    }
    ~MixerProcessor() {}
    void setOscLevel(float newLevel, int index)
    {
        if(index == 0)
            level0 = newLevel;
        else if (index == 1)
            level1 = newLevel;
        else if(index == 2)
            level2 = newLevel;
    }
    float getOscLevel(int index)
    {
        if(index == 0)
            return level0;
        else if(index == 1)
            return level1;
        else
            return level2;
    }
    void setMasterLevel(float newLevel)
    {
        masterLevel = newLevel;
    }
    float level0;
    float level1;
    float level2;
    float masterLevel;
    
};
