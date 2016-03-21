//
//  LinkwitzRiley.h
//  AutoTalentMD
//
//  Created by Michael Donovan on 3/9/16.
//  Original from T. Lossius - ttblue project
//

#ifndef LinkwitzRiley_h
#define LinkwitzRiley_h

enum FilterType {
    Lowpass = 0,
    Highpass,
};

class LinkwitzRiley{
public:
    LinkwitzRiley(){
        sr = 44100;
        filterType = 0;
        fc = 1000;
        calcFilter();
    }
    
    LinkwitzRiley(float sampleRate, const int& type, double cutoffFreq){
        sr = sampleRate;
        filterType = type;
        fc = cutoffFreq;
        
        calcFilter();
    };
    
    double getCuttoff(){ return fc; };
    
    ~LinkwitzRiley(){};
    
    
    //  Process sample of audio
    double process(double sample, int channel){
        double tempx = sample;
        double tempy = a0*tempx+a1*buffX[channel][0]+a2*buffX[channel][1]+a3*buffX[channel][2]+a4*buffX[channel][3]-b1*buffY[channel][0]-b2*buffY[channel][1]-b3*buffY[channel][2]-b4*buffY[channel][3];
        
        buffX[channel][3]=buffX[channel][2];
        buffX[channel][2]=buffX[channel][1];
        buffX[channel][1]=buffX[channel][0];
        buffX[channel][0]=tempx;
        
        buffY[channel][3]=buffY[channel][2];
        buffY[channel][2]=buffY[channel][1];
        buffY[channel][1]=buffY[channel][0];
        buffY[channel][0]=tempy;
        
        return tempy;
    }
    
    //  Set cutoff frequency (Hz)
    void setCutoff(double freq){
        fc = freq;
        calcFilter();
    }
    
private:
    void calcFilter(){
        double wc, wc2, wc3, wc4, k, k2, k3, k4, sqrt2, sq_tmp1, sq_tmp2, a_tmp;
        
        for (int i=0; i<4; i++) {
            buffX[0][i]=0;
            buffX[1][i]=0;
            buffY[0][i]=0;
            buffY[1][i]=0;
        }
        
        wc=2*pi*fc;
        wc2=wc*wc;
        wc3=wc2*wc;
        wc4=wc2*wc2;
        k=wc/tan(pi*fc/sr);
        k2=k*k;
        k3=k2*k;
        k4=k2*k2;
        sqrt2=sqrt(2);
        sq_tmp1=sqrt2*wc3*k;
        sq_tmp2=sqrt2*wc*k3;
        a_tmp=4*wc2*k2+2*sq_tmp1+k4+2*sq_tmp2+wc4;
        
        b1=(4*(wc4+sq_tmp1-k4-sq_tmp2))/a_tmp;
        b2=(6*wc4-8*wc2*k2+6*k4)/a_tmp;
        b3=(4*(wc4-sq_tmp1+sq_tmp2-k4))/a_tmp;
        b4=(k4-2*sq_tmp1+wc4-2*sq_tmp2+4*wc2*k2)/a_tmp;
        
        if (filterType==Lowpass) {
            a0=wc4/a_tmp;
            a1=4*wc4/a_tmp;
            a2=6*wc4/a_tmp;
            a3=a1;
            a4=a0;
        }
        else{
            a0=k4/a_tmp;
            a1=-4*k4/a_tmp;
            a2=6*k4/a_tmp;
            a3=a1;
            a4=a0;
        }
        
        
    };
    
    
    //	Params
    int filterType;
    double fc;
    double sr;
 
    //	Coefficients
    double a0, a1, a2, a3, a4, b1, b2, b3, b4;
    
    //  Buffer
    double buffX[2][4];
    double buffY[2][4];
};

#endif /* LinkwitzRiley_h */
