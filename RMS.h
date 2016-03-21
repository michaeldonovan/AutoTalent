//
//  RMS.h
//
//  Created by Michael Donovan on 3/8/16.
//
//

#ifndef RMS_h
#define RMS_h

class RMSFollower
{
public:
    RMSFollower(){
        sum=0;
        buffer = new double[1000];
        for (int i=0; i<1000; i++) {
            buffer[i]=0;
        }
    }
    
    ~RMSFollower(){
        delete [] buffer;
    }
    
    double getRMS(double sample, int channel){
        double RMSLevel;
        if (channel%2==0) {
            for (int i=0; i<998; i++) {
                buffer[i]=buffer[i+1];
            }
            buffer[999]=sample*sample;
            sum+=buffer[999]-buffer[0];
        }
        RMSLevel = sum/10;
        return sqrt(RMSLevel);
    }
    
private:
    double sum;
    double* buffer;
};

#endif /* RMS_h */
