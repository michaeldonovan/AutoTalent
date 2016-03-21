#ifndef __IPLUGIN__
#define __IPLUGIN__

#include "IPlug_include_in_plug_hdr.h"
#define L2SC (float)3.32192809488736218171

#include "mayer_fft.c"
#include "fftsetup.h"

class IPlugin : public IPlug
{
public:
	
	IPlugin(IPlugInstanceInfo instanceInfo);
	~IPlugin();
	
	// Implement these if your audio or GUI logic requires doing something, when params change or when audio processing stops/starts.
	void Reset();
	void OnParamChange(int paramIdx);

	void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);
	
	void init(unsigned long sr);
	
	unsigned long fs; // Sample rate

private:
	
	// parameters
	
	float fMix;
	float fShift;
	float fTune;
	float fA;
	float fBb;
	float fB;
	float fC;
	float fDb;
	float fD;
	float fEb;
	float fE;
	float fF;
	float fGb;
	float fG;
	float fAb;
	float fAmount;
	float fGlide;
	
	fft_vars* fmembvars; // member variables for fft routine
	
	
	unsigned long cbsize; // size of circular buffer
	unsigned long corrsize; // cbsize/2 + 1
	unsigned long cbiwr;
	unsigned long cbord;
	float* cbi; // circular input buffer
	float* cbo; // circular output buffer
	float* cbonorm; // circular output buffer used to normalize signal
	
	float* cbwindow; // hann of length N/2, zeros for the rest
	float* acwinv; // inverse of autocorrelation of window
	float* hannwindow; // length-N hann
	int noverlap;
	
	float* ffttime;
	float* fftfreqre;
	float* fftfreqim;
	
	// VARIABLES FOR LOW-RATE SECTION
	float aref; // A tuning reference (Hz)
	float pperiod; // Pitch period (seconds)
	float pitch; // Pitch (semitones)
	float pitchpers; // Pitch persist (semitones)
	float conf; // Confidence of pitch period estimate (between 0 and 1)
	float vthresh; // Voiced speech threshold
	
	float pmax; // Maximum allowable pitch period (seconds)
	float pmin; // Minimum allowable pitch period (seconds)
	unsigned long nmax; // Maximum period index for pitch prd est
	unsigned long nmin; // Minimum period index for pitch prd est
	
	float lrshift; // Shift prescribed by low-rate section
	int ptarget; // Pitch target, between 0 and 11
	float sptarget; // Smoothed pitch target
	int wasvoiced; // 1 if previous frame was voiced
	float persistamt; // Proportion of previous pitch considered during next voiced period
	float glidepersist;
	
	// VARIABLES FOR PITCH SHIFTER
	float phprd; // phase period
	float phprdd; // default (unvoiced) phase period
	float phinc; // input phase increment
	float phincfact; // factor determining output phase increment
	float phasein;
	float phaseout;
	float* frag; // windowed fragment of speech
	unsigned long fragsize; // size of fragment in samples	
		
};

////////////////////////////////////////

#endif
