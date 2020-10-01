/*
  ==============================================================================

    FilterProcessor.h
    Created: 1 Oct 2020 7:45:26am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "maximilian.h"

class BaseFilter {
    double gain;
    double input;
    double output;
    double inputs[10];
    double outputs[10];
    double cutoff1;
    double x;//speed
    double y;//pos
    double z;//pole
    double c;//filter coefficient

public:
    BaseFilter():x(0.0), y(0.0), z(0.0), c(0.0){};
    double cutoff;
    double resonance;
    double lores(double input, double cutoff1, double resonance);
    double hires(double input, double cutoff1, double resonance);
    double bandpass(double input, double cutoff1, double resonance);
    double lopass(double input, double cutoff);
    double hipass(double input, double cutoff);

    // ------------------------------------------------
    // getters/setters
    void setCutoff(double cut){
        cutoff = cut;
    }

    void setResonance(double res){
        resonance = res;
    }

    double getCutoff() const{
        return cutoff;
    }

    double getResonance() const{
        return resonance;
    }
    // ------------------------------------------------
};
