/*
  ==============================================================================

    RGBColor.h
    Created: 25 Sep 2020 4:12:40pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
struct ColorCreator
{
    //without fourth argument, returns color with fully opaque alpha
    juce::Colour RGBColor(int r, int g, int b)
    {
        return(juce::Colour(juce::uint8(r), juce::uint8(g), juce::uint8(b), juce::uint8(255)));
    }

    //fourth argument sets alpha
    juce::Colour RGBColor(int r, int g, int b, int a)
    {
        return(juce::Colour(juce::uint8(r), juce::uint8(g), juce::uint8(b), juce::uint8(a)));
    }
};
