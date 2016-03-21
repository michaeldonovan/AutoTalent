//
//  PeakFollower.cpp
//  
//
//
#include <math.h>
#include "PeakFollower.h"

const float HALF_LIFE = .5;
const float VERY_SMALL_FLOAT = 0.0001;

// halfLife = time in seconds for output to decay to half value after an impulse

PeakFollower::PeakFollower(double sampleRate){
    scalar = pow( 0.5, 1.0/(HALF_LIFE * sampleRate));
    output = 0.;
};

float PeakFollower::process(double input){
    input = fabs(input);

    if ( input >= output )
    {
        /* When we hit a peak, ride the peak to the top. */
        output = input;
    }
    else
    {
        /* Exponential decay of output when signal is low. */
        output = output * scalar;
        /*
         ** When current gets close to 0.0, set current to 0.0 to prevent FP underflow
         ** which can cause a severe performance degradation due to a flood
         ** of interrupts.
         */
        if( output < VERY_SMALL_FLOAT ) output = 0.0;
    }
    return output;
}
