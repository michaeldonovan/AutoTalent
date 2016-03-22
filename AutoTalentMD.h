#ifndef __AUTOTALENTMD__
#define __AUTOTALENTMD__

#include "IPlug_include_in_plug_hdr.h"
#include "CParamSmooth.h"
#include "IPopupMenuControl.h"
#include "PeakFollower.h"
#include "IKnobLabelControl.h"
#include "mayer_fft.c"
#include "fftsetup.h"
#include "IKnobMultiControlText.h"
#include "Scales.h"

#define L2SC (float)3.32192809488736218171

class AutoTalentMD : public IPlug
{
public:
  AutoTalentMD(IPlugInstanceInfo instanceInfo);
  ~AutoTalentMD();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);
  double ProcessDistortion(double sample, int distType);
  
  void init(unsigned long sr);
  
  unsigned long fs; // Sample rate
  
private:
  //////////////////////////////////
  char* version = "v0.1.0";
  //////////////////////////////////
  
  //Functions
  void SetScale();
  
  //Controls
  IPopUpMenuControl* mRootControl;
  IPopUpMenuControl* mScaleControl;
  
  //Set Colors
  IColor DARK_GRAY = IColor(255,50,50,50);
  IColor LIGHT_GRAY = IColor(255,70,70,70);
  IColor MID_GRAY = IColor(255,60,60,60);
  IColor LIGHTER_GRAY = IColor(255,170,170,170);
  IColor LIGHT_YELLOW = IColor(255,255,234,39);

  ISwitchControl* Keys[12];
  
  bool scales[8][12];
  
  // parameters
  
  float fMix;
  float fShift;
  float fTune;
//  float fA;
//  float fBb;
//  float fB;
//  float fC;
//  float fDb;
//  float fD;
//  float fEb;
//  float fE;
//  float fF;
//  float fGb;
//  float fG;
//  float fAb;
  float fNotes[12];
  float fAmount;
  float fGlide;
  
  fft_vars* fmembvars; // member variables for fft routine
  
  IScales mScales;
  
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

#endif
