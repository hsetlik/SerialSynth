/*
  ==============================================================================

    FilterProcessor.cpp
    Created: 1 Oct 2020 7:45:26am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "FilterProcessor.h"

//I particularly like these. cutoff between 0 and 1
double BaseFilter::lopass(double input, double cutoff) {
    output=outputs[0] + cutoff*(input-outputs[0]);
    outputs[0]=output;
    return(output);
}

//as above
double BaseFilter::hipass(double input, double cutoff) {
    output=input-(outputs[0] + cutoff*(input-outputs[0]));
    outputs[0]=output;
    return(output);
}
//awesome. cuttof is freq in hz. res is between 1 and whatever. Watch out!
double BaseFilter::lores(double input,double cutoff1, double resonance) {
    cutoff=cutoff1;
    if (cutoff<10) cutoff=10;
    if (cutoff>(maxiSettings::sampleRate)) cutoff=(maxiSettings::sampleRate);
    if (resonance<1.) resonance = 1.;
    z=cos(TWOPI*cutoff/maxiSettings::sampleRate);
    c=2-2*z;
    double r=(sqrt(2.0)*sqrt(-pow((z-1.0),3.0))+resonance*(z-1))/(resonance*(z-1));
    x=x+(input-y)*c;
    y=y+x;
    x=x*r;
    output=y;
    return(output);
}

//working hires filter
double BaseFilter::hires(double input,double cutoff1, double resonance) {
    cutoff=cutoff1;
    if (cutoff<10) cutoff=10;
    if (cutoff>(maxiSettings::sampleRate)) cutoff=(maxiSettings::sampleRate);
    if (resonance<1.) resonance = 1.;
    z=cos(TWOPI*cutoff/maxiSettings::sampleRate);
    c=2-2*z;
    double r=(sqrt(2.0)*sqrt(-pow((z-1.0),3.0))+resonance*(z-1))/(resonance*(z-1));
    x=x+(input-y)*c;
    y=y+x;
    x=x*r;
    output=input-y;
    return(output);
}

//This works a bit. Needs attention.
double BaseFilter::bandpass(double input,double cutoff1, double resonance) {
    cutoff=cutoff1;
    if (cutoff>(maxiSettings::sampleRate*0.5)) cutoff=(maxiSettings::sampleRate*0.5);
    if (resonance>=1.) resonance=0.999999;
    z=cos(TWOPI*cutoff/maxiSettings::sampleRate);
    inputs[0] = (1-resonance)*(sqrt(resonance*(resonance-4.0*pow(z,2.0)+2.0)+1));
    inputs[1] = 2*z*resonance;
    inputs[2] = pow((resonance*-1),2);

    output=inputs[0]*input+inputs[1]*outputs[1]+inputs[2]*outputs[2];
    outputs[2]=outputs[1];
    outputs[1]=output;
    return(output);
}
