//
//  PeakFollower.hpp
//  
//
//

#ifndef PeakFollower_hpp
#define PeakFollower_hpp

class PeakFollower {
public:
    PeakFollower(double sampleRate);
    ~PeakFollower();
    float process(double input);

protected:
    float scalar;
    float output;
};



#endif /* PeakFollower_h */

