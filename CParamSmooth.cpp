//
//  CParamSmooth.cpp
//
//  Author: alexirae@gmail.com
//  from musicdsp.org archives
//
#include "CParamSmooth.h"
#include <math.h>

CParamSmooth::CParamSmooth(){
    const float c_twoPi = 6.283185307179586476925286766559f;
    
    a = exp(-c_twoPi / (5 * 0.001f * 44100));
    b = 1.0f - a;
    z = 0.0f;
}

CParamSmooth::CParamSmooth(float smoothingTimeInMs, float samplingRate)
{
    const float c_twoPi = 6.283185307179586476925286766559f;
    
    a = exp(-c_twoPi / (smoothingTimeInMs * 0.001f * samplingRate));
    b = 1.0f - a;
    z = 0.0f;
}

    
double CParamSmooth::process(double in)
{
    z = (in * b) + (z * a);
    return z;
}
    
