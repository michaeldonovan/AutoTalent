//
//  CParamSmooth.h
//
//  Author: alexirae@gmail.com
//  from musicdsp.org archives
//

#ifndef CParamSmooth_hpp
#define CParamSmooth_hpp

class CParamSmooth
{
public:
    CParamSmooth();
    CParamSmooth(float smoothingTimeInMs, float samplingRate);

    ~CParamSmooth(){};
                 
    double process(double in);

private:
    float a;
    float b;
    float z;
};

#endif /* CParamSmooth_hpp */
