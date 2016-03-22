#include "AutoTalent.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"

const int kNumPrograms = 1;

enum EParams
{
  kMix = 0,
  kShift,
  kTune,
  kAmount,
  kGlide,
  kC,
  kDb,
  kD,
  kEb,
  kE,
  kF,
  kGb,
  kG,
  kAb,
  kA,
  kBb,
  kB,
  kScale,
  kRoot,
  kNumParams
};

enum ELayout
{
  kWidth = GUI_WIDTH,
  kHeight = GUI_HEIGHT,
  
  kKnob1X = 30,
  kKnob2X = kKnob1X+90,
  kKnob3X = kKnob2X+90,
  kKnob4X = kKnob3X+90,
  
  kKnobsY = 37,
  
  kKeyboardX = 76,
  kKeyboardY = 166,
  kKeyboardSpacingW = 39,
  kKeyboardSpacingB = 26,
  
  kTitlesY = 17,
  kKnobFrames = 63
};

AutoTalent::AutoTalent(IPlugInstanceInfo instanceInfo):
IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{
  TRACE;
  //======================================================================================================
  
  init(fs);
  
  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
  
  // Define parameter ranges, display units, labels.
  //arguments are: name, defaultVal, minVal, maxVal, step, label
  GetParam(kMix)->InitDouble("Mix", 100., 0., 100., 0.01, "%");
  GetParam(kShift)->InitDouble("Transpose", 0.0, -12., 12., 1., "st");
  GetParam(kTune)->InitDouble("Fine Tune", 0.0, -100., 100., 1, "ct");
  GetParam(kAmount)->InitDouble("Amount", 100., 0., 100., 0.01, "%");
  GetParam(kGlide)->InitDouble("Glide", 0.0, 0., 1000., 0.01, "ms");
  
  GetParam(kC)->InitDouble("C", 100., 0., 100., 0.01, "%");
  GetParam(kDb)->InitDouble("Db", 100., 0., 100., 0.01, "%");
  GetParam(kD)->InitDouble("D", 100., 0., 100., 0.01, "%");
  GetParam(kEb)->InitDouble("Eb", 100., 0., 100., 0.01, "%");
  GetParam(kE)->InitDouble("E", 100., 0., 100., 0.01, "%");
  GetParam(kF)->InitDouble("F", 100., 0., 100., 0.01, "%");
  GetParam(kGb)->InitDouble("Gb", 100., 0., 100., 0.01, "%");
  GetParam(kG)->InitDouble("G", 100., 0., 100., 0.01, "%");
  GetParam(kAb)->InitDouble("Ab", 100., 0., 100., 0.01, "%");
  GetParam(kA)->InitDouble("A", 100., 0., 100., 0.01, "%");
  GetParam(kBb)->InitDouble("Bb", 100., 0., 100., 0.01, "%");
  GetParam(kB)->InitDouble("B", 100., 0., 100., 0.01, "%");
  
  GetParam(kRoot)->InitEnum("Root", 0, 12);
  GetParam(kRoot)->SetDisplayText(0, "C");
  GetParam(kRoot)->SetDisplayText(1, "Db");
  GetParam(kRoot)->SetDisplayText(2, "D");
  GetParam(kRoot)->SetDisplayText(3, "Eb");
  GetParam(kRoot)->SetDisplayText(4, "E");
  GetParam(kRoot)->SetDisplayText(5, "F");
  GetParam(kRoot)->SetDisplayText(6, "Gb");
  GetParam(kRoot)->SetDisplayText(7, "G");
  GetParam(kRoot)->SetDisplayText(8, "Ab");
  GetParam(kRoot)->SetDisplayText(9, "A");
  GetParam(kRoot)->SetDisplayText(10, "Bb");
  GetParam(kRoot)->SetDisplayText(11, "B");
  
  GetParam(kScale)->InitEnum("Scale", 0, 13);
  GetParam(kScale)->SetDisplayText(0, "Chromatic");
  GetParam(kScale)->SetDisplayText(1, "Major");
  GetParam(kScale)->SetDisplayText(2, "Minor");
  GetParam(kScale)->SetDisplayText(3, "Dorian");
  GetParam(kScale)->SetDisplayText(4, "Mixolydian");
  GetParam(kScale)->SetDisplayText(5, "Lydian");
  GetParam(kScale)->SetDisplayText(6, "Phrygian");
  GetParam(kScale)->SetDisplayText(7, "Locrian");
  GetParam(kScale)->SetDisplayText(8, "Harmonic Minor");
  GetParam(kScale)->SetDisplayText(9, "Melodic Minor");
  GetParam(kScale)->SetDisplayText(10, "Major Pentatonic");
  GetParam(kScale)->SetDisplayText(11, "Minor Pentatonic");
  GetParam(kScale)->SetDisplayText(12, "Minor Blues");

  GetParam(kScale)->SetIsMeta(true);
  GetParam(kRoot)->SetIsMeta(true);
  

  
  IBitmap Knob = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, kKnobFrames);
  IBitmap KeyC = pGraphics->LoadIBitmap(KEYC_ID, KEYC_FN, 2);
  IBitmap KeyD = pGraphics->LoadIBitmap(KEYD_ID, KEYD_FN, 2);
  IBitmap KeyE = pGraphics->LoadIBitmap(KEYE_ID, KEYE_FN, 2);
  IBitmap KeyF = pGraphics->LoadIBitmap(KEYF_ID, KEYF_FN, 2);
  IBitmap KeyG = pGraphics->LoadIBitmap(KEYG_ID, KEYG_FN, 2);
  IBitmap KeyA = pGraphics->LoadIBitmap(KEYA_ID, KEYA_FN, 2);
  IBitmap KeyB = pGraphics->LoadIBitmap(KEYB_ID, KEYB_FN, 2);
  IBitmap KeyBlack = pGraphics->LoadIBitmap(KEYBLACK_ID, KEYBLACK_FN, 2);
  
  Keys[0] = new ISwitchControl(this, kKeyboardX, kKeyboardY, kC, &KeyC);
  Keys[1] = new ISwitchControl(this, kKeyboardX + kKeyboardSpacingB, kKeyboardY, kDb, &KeyBlack);
  Keys[2] = new ISwitchControl(this, kKeyboardX + kKeyboardSpacingW, kKeyboardY, kD, &KeyD);
  Keys[3] = new ISwitchControl(this, kKeyboardX + kKeyboardSpacingW + kKeyboardSpacingB, kKeyboardY, kEb, &KeyBlack);
  Keys[4] = new ISwitchControl(this, kKeyboardX + 2 * kKeyboardSpacingW, kKeyboardY, kE, &KeyE);
  Keys[5] = new ISwitchControl(this, kKeyboardX + 3 * kKeyboardSpacingW, kKeyboardY, kF, &KeyF);
  Keys[6] = new ISwitchControl(this, kKeyboardX + 3 * kKeyboardSpacingW + kKeyboardSpacingB, kKeyboardY, kGb, &KeyBlack);
  Keys[7] = new ISwitchControl(this, kKeyboardX + 4 * kKeyboardSpacingW, kKeyboardY, kG, &KeyG);
  Keys[8] = new ISwitchControl(this, kKeyboardX + 4 * kKeyboardSpacingW + kKeyboardSpacingB, kKeyboardY, kAb, &KeyBlack);
  Keys[9] = new ISwitchControl(this, kKeyboardX + 5 * kKeyboardSpacingW, kKeyboardY, kA, &KeyA);
  Keys[10] = new ISwitchControl(this, kKeyboardX + 5 * kKeyboardSpacingW + kKeyboardSpacingB, kKeyboardY, kBb, &KeyBlack);
  Keys[11] = new ISwitchControl(this, kKeyboardX + 6 * kKeyboardSpacingW, kKeyboardY, kB, &KeyB);
  
  for (int i=0; i<12; i++) {
    pGraphics->AttachControl(Keys[i]);
  }
  
  pGraphics->AttachBackground(BACKGROUND_ID, BACKGROUND_FN);
  
  
  IText caption = IText(17, &COLOR_WHITE, "Futura", IText::kStyleNormal, IText::kAlignCenter);
  IText label = IText(17, &COLOR_WHITE, "Futura", IText::kStyleNormal, IText::kAlignNear);
  IText title = IText(20, &COLOR_WHITE, "Futura", IText::kStyleNormal, IText::kAlignCenter);

  
  mRootControl = new IPopUpMenuControl(this, IRECT(110, 140, 149, 155), LIGHT_GRAY, COLOR_WHITE, LIGHT_YELLOW, kRoot);
  
  mScaleControl = new IPopUpMenuControl(this, IRECT(197, 140, 300, 155), LIGHT_GRAY, COLOR_WHITE, LIGHT_YELLOW, kScale);
  
  pGraphics->AttachControl(mRootControl);
  pGraphics->AttachControl(mScaleControl);
  
  
  
  pGraphics->AttachControl(new ITextControl(this, IRECT(77, 141, 110, 154), &label, "Root:"));
  pGraphics->AttachControl(new ITextControl(this, IRECT(160, 141, 197, 154), &label, "Scale:"));
  
  
  
  //pGraphics->AttachControl(new IKnobMultiControl(this, kKnob1X, kKnobsY, kShift, &Knob));
  //pGraphics->AttachControl(new IKnobMultiControl(this, kKnob2X, kKnobsY, kTune, &Knob));
  //pGraphics->AttachControl(new IKnobMultiControl(this, kKnob3X, kKnobsY, kAmount, &Knob));
  //pGraphics->AttachControl(new IKnobMultiControl(this, kKnob4X, kKnobsY, kGlide, &Knob));
  
  pGraphics->AttachControl(new IKnobMultiControlText(this, IRECT(kKnob1X, kKnobsY, kKnob1X+83, kKnobsY+90), kShift, &Knob, &caption, true));
  pGraphics->AttachControl(new IKnobMultiControlText(this, IRECT(kKnob2X, kKnobsY, kKnob2X+83, kKnobsY+90), kTune, &Knob, &caption, true));
  pGraphics->AttachControl(new IKnobMultiControlText(this, IRECT(kKnob3X, kKnobsY, kKnob3X+83, kKnobsY+90), kGlide, &Knob, &caption, true));
  pGraphics->AttachControl(new IKnobMultiControlText(this, IRECT(kKnob4X, kKnobsY, kKnob4X+83, kKnobsY+90), kAmount, &Knob, &caption, true));
  
  pGraphics->AttachControl(new ITextControl(this, IRECT(kKnob1X, kTitlesY, kKnob1X+83, kKnobsY), &title, "Transpose"));
  pGraphics->AttachControl(new ITextControl(this, IRECT(kKnob2X, kTitlesY, kKnob2X+83, kKnobsY), &title, "Fine Tune"));
  pGraphics->AttachControl(new ITextControl(this, IRECT(kKnob3X, kTitlesY, kKnob3X+83, kKnobsY), &title, "Glide"));
  pGraphics->AttachControl(new ITextControl(this, IRECT(kKnob4X, kTitlesY, kKnob4X+83, kKnobsY), &title, "Amount"));
  
  
  IText versionText = IText(12, &LIGHTER_GRAY, "Futura");
  pGraphics->AttachControl(new ITextControl(this, IRECT(170, 332, 220, 340), &versionText, version));
  
  AttachGraphics(pGraphics);
  
  
  //MakePreset("preset 1", ... );
  
}

AutoTalent::~AutoTalent(){
  fft_des(fmembvars);
  free(cbi);
  free(cbo);
  free(cbonorm);
  free(cbwindow);
  free(hannwindow);
  free(acwinv);
  free(frag);
  free(ffttime);
  free(fftfreqre);
  free(fftfreqim);
};



/**
 This is the main loop where we'll process our samples
 */
void AutoTalent::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
  // Mutex is already locked for us.
  
  double* in1 = inputs[0];
  double* out1 = outputs[0];
  double* out2 = outputs[1];
  // copy struct variables to local
  /*
   float fMix = fMix;
   float fShift = fShift;
   float fTune = fTune;
   float fA = fA;
   float fBb = fBb;
   float fB = fB;
   float fC = fC;
   float fDb = fDb;
   float fD = fD;
   float fEb = fEb;
   float fE = fE;
   float fF = fF;
   float fGb = fGb;
   float fG = fG;
   float fAb = fAb;
   float fGlide = fGlide;
   float fAmount = fAmount;
   */
  float fPersist = glidepersist;
  
  aref = (float)440*pow(2,fTune/12);
		
  unsigned long N = cbsize;
  unsigned long Nf = corrsize;
  //unsigned long fs = fs;
  /*
   float pmax = pmax;
   float pmin = pmin;
   unsigned long nmax = nmax;
   unsigned long nmin = nmin;
   
   float pperiod = pperiod;
   float pitch = pitch;
   float conf = conf;
   float aref = aref;
   */
  //
  
  long int ti;
  long int ti2;
  long int ti3;
  float tf;
  float tf2;
  float tf3;
  
  
  //double samplesPerBeat = GetSamplesPerBeat();
  //double samplePos = (double) GetSamplePos();
  
  for (int s = 0; s < nFrames; ++s, ++in1, ++out1, ++out2)
  {
    
    // load data into circular buffer
    tf = (float) *in1;
    cbi[cbiwr] = tf;
    cbiwr++;
    if (cbiwr >= N) {
      cbiwr = 0;
    }
    
    
    // ********************
    // * Low-rate section *
    // ********************
    
    // Every N/noverlap samples, run pitch estimation / correction code
    if ((cbiwr)%(N/noverlap) == 0) {
      
      
      // ---- Obtain autocovariance ----
      
      // Window and fill FFT buffer
      ti2 = (long) cbiwr;
      for (ti=0; ti<(long)N; ti++) {
        ffttime[ti] = (float)(cbi[(ti2-ti)%N]*cbwindow[ti]);
      }
      
      // Calculate FFT
      fft_forward(fmembvars, ffttime, fftfreqre, fftfreqim);
      
      // Remove DC
      fftfreqre[0] = 0;
      fftfreqim[0] = 0;
      
      // Take magnitude squared
      for (ti=1; ti< (long) Nf; ti++) {
        fftfreqre[ti] = (fftfreqre[ti])*(fftfreqre[ti]) + (fftfreqim[ti])*(fftfreqim[ti]);
        fftfreqim[ti] = 0;
      }
      
      // Calculate IFFT
      fft_inverse(fmembvars, fftfreqre, fftfreqim, ffttime);
      
      // Normalize
      for (ti=1; ti<(long)N; ti++) {
        ffttime[ti] = ffttime[ti] / ffttime[0];
      }
      ffttime[0] = 1;
      
      //  ---- END Obtain autocovariance ----
      
      
      //  ---- Calculate pitch and confidence ----
      
      // Calculate pitch period
      //   Pitch period is determined by the location of the max (biased)
      //     peak within a given range
      //   Confidence is determined by the corresponding unbiased height
      tf2 = 0;
      pperiod = pmin;
      for (ti=nmin; ti<(long)nmax; ti++) {
        ti2 = ti-1;
        ti3 = ti+1;
        if (ti2<0) {
          ti2 = 0;
        }
        if (ti3>(long)Nf) {
          ti3 = Nf;
        }
        tf = ffttime[ti];
        
        if (tf>ffttime[ti2] && tf>=ffttime[ti3] && tf>tf2) {
          tf2 = tf;
          conf = tf*acwinv[ti];
          pperiod = (float)ti/fs;
        }
      }
      
      // Convert to semitones
      pitch = (float) -12*log10((float)aref*pperiod)*L2SC;
      pitch = pitch;
      pperiod = pperiod;
      conf = conf;
      
      //  ---- END Calculate pitch and confidence ----
      
      
      //  ---- Determine pitch target ----
      
      // If voiced
      if (conf>=vthresh) {
        // TODO: Scale sliders
        // Determine pitch target
        tf = -1;
        tf2 = 0;
        tf3 = 0;
        for (ti=0; ti<12; ti++) {
          switch (ti) {
            case 0:
              tf2 = fNotes[9];
              break;
            case 1:
              tf2 = fNotes[10];
              break;
            case 2:
              tf2 = fNotes[11];
              break;
            case 3:
              tf2 = fNotes[0];
              break;
            case 4:
              tf2 = fNotes[1];
              break;
            case 5:
              tf2 = fNotes[2];
              break;
            case 6:
              tf2 = fNotes[3];
              break;
            case 7:
              tf2 = fNotes[4];
              break;
            case 8:
              tf2 = fNotes[5];
              break;
            case 9:
              tf2 = fNotes[6];
              break;
            case 10:
              tf2 = fNotes[7];
              break;
            case 11:
              tf2 = fNotes[8];
              break;
          }
          /* 	  if (ti==ptarget) { */
          /* 	    tf2 = tf2 + 0.01; // add a little hysteresis */
          /* 	  } */
          tf2 = tf2 - (float)fabs( (pitch-(float)ti)/6 - 2*floorf(((pitch-(float)ti)/12 + 0.5)) ); // like a likelihood function
          if (tf2>=tf) {                                                                           // that we're maximizing
            tf3 = (float)ti;                                                                       // to find the target pitch
            tf = tf2;
          }
        }
        ptarget = tf3;
        
        // Glide persist
        if (wasvoiced == 0) {
          wasvoiced = 1;
          tf = persistamt;
          sptarget = (1-tf)*ptarget + tf*sptarget;
          persistamt = 1;
        }
        
        // Glide on circular scale
        tf3 = (float)ptarget - sptarget;
        tf3 = tf3 - (float)12*floorf(tf3/12 + 0.5);
        if (fGlide>0) {
          tf2 = (float)1-pow((float)1/24, (float)N * 1000/ (noverlap*fs*fGlide));
        }
        else {
          tf2 = 1;
        }
        sptarget = sptarget + tf3*tf2;
      }
      // If not voiced
      else {
        wasvoiced = 0;
        
        // Keep track of persist amount
        if (fPersist>0) {
          tf = pow((float)1/2, (float)N * 1000/ (noverlap*fs*fPersist));
        }
        else {
          tf = 0;
        }
        persistamt = persistamt * tf; // Persist amount decays exponentially
      }
      // END If voiced
      
      //  ---- END Determine pitch target ----
      
      
      // ---- Determine correction to feed to the pitch shifter ----
      tf = sptarget - pitch; // Correction amount
      tf = tf - (float)12*floorf(tf/12 + 0.5); // Never do more than +- 6 semitones of correction
      if (conf<vthresh) {
        tf = 0;
      }
      lrshift = fShift + fAmount*tf;  // Add in pitch shift slider
      
      
      // ---- Compute variables for pitch shifter that depend on pitch ---
      phincfact = (float)pow(2, lrshift/12);
      if (conf>=vthresh) {  // Keep old period when unvoiced
        phinc = (float)1/(pperiod*fs);
        phprd = pperiod*2;
      }
    }
    // ************************
    // * END Low-Rate Section *
    // ************************
    
    
    // *****************
    // * Pitch Shifter *
    // *****************
    
    // TODO: Pre-filter with some kind of filter (maybe cheby2 or just svf)
    // TODO: Use cubic spline interpolation
    
    // IMPROVE QUALITY OF PITCH SHIFTER!
    // what is the glitch at "lAaAack"? probably pitch shifter
    
    //   Better snippet management
    //   Pre-filter
    //   Cubic spline interp
    // Pitch shifter (overlap-add, pitch synchronous)
    //   Note: pitch estimate is naturally N/2 samples old
    phasein = phasein + phinc;
    phaseout = phaseout + phinc*phincfact;
    
    //   If it happens that there are no snippets placed at the output, grab a new snippet!
    /*     if (cbonorm[((long int)cbord + (long int)(N/2*(1 - (float)1 / phincfact)))%N] < 0.2) { */
    /*       fprintf(stderr, "help!"); */
    /*       phasein = 1; */
    /*       phaseout = 1; */
    /*     } */
    
    //   When input phase resets, take a snippet from N/2 samples in the past
    if (phasein >= 1) {
      phasein = phasein - 1;
      ti2 = cbiwr - (long int)N/2;
      for (ti=-((long int)N)/2; ti<(long int)N/2; ti++) {
        frag[ti%N] = cbi[(ti + ti2)%N];
      }
    }
    
    //   When output phase resets, put a snippet N/2 samples in the future
    if (phaseout >= 1) {
      fragsize = fragsize*2;
      if (fragsize >= N) {
        fragsize = N;
      }
      phaseout = phaseout - 1;
      ti2 = cbord + N/2;
      ti3 = (long int)(((float)fragsize) / phincfact);
      for (ti=-ti3/2; ti<(ti3/2); ti++) {
        tf = hannwindow[(long int)N/2 + ti*(long int)N/ti3];
        cbo[(ti + ti2)%N] = cbo[(ti + ti2)%N] + frag[((int)(phincfact*ti))%N]*tf;
        cbonorm[(ti + ti2)%N] = cbonorm[(ti + ti2)%N] + tf;
      }
      fragsize = 0;
    }
    fragsize++;
    
    //   Get output signal from buffer
    tf = cbonorm[cbord];
    //   Normalize
    if (tf>0.5) {
      tf = (float)1/tf;
    }
    else {
      tf = 1;
    }
    tf = tf*cbo[cbord]; // read buffer
    tf = cbo[cbord];
    cbo[cbord] = 0; // erase for next cycle
    cbonorm[cbord] = 0;
    cbord++; // increment read pointer
    if (cbord >= N) {
      cbord = 0;
    }
    
    // *********************
    // * END Pitch Shifter *
    // *********************
    
    
    // Write audio to output of plugin
    // Mix (blend between original (delayed) =0 and shifted/corrected =1)
    *out1 = *out2 = (double) fMix*tf + (1-fMix)*cbi[(cbiwr - N + 1)%N];
  }
  
}


void AutoTalent::init(unsigned long sr)
{
  
  unsigned long ti;
  
  fs = sr;
  aref = 440;
  
  if (fs >=88200) {
    cbsize = 4096;
  }
  else {
    cbsize = 2048;
  }
  corrsize = cbsize / 2 + 1;
  
  pmax = 1/(float)70;  // max and min periods (ms)
  pmin = 1/(float)700; // eventually may want to bring these out as sliders
  
  pperiod = pmax;
  
  nmax = (unsigned long)(fs * pmax);
  if (nmax > corrsize) {
    nmax = corrsize;
  }
  nmin = (unsigned long)(fs * pmin);
  
  cbi = (float*) calloc(cbsize, sizeof(float));
  cbo = (float*) calloc(cbsize, sizeof(float));
  cbonorm = (float*) calloc(cbsize, sizeof(float));
  
  cbiwr = 0;
  cbord = 0;
  
  // Standard raised cosine window, max height at N/2
  hannwindow = (float*) calloc(cbsize, sizeof(float));
  for (ti=0; ti<cbsize; ti++) {
    hannwindow[ti] = -0.5*cos(2*PI*ti/(cbsize - 1)) + 0.5;
  }
  
  // Generate a window with a single raised cosine from N/4 to 3N/4
  cbwindow = (float*) calloc(cbsize, sizeof(float));
  for (ti=0; ti<(cbsize / 2); ti++) {
    cbwindow[ti+cbsize/4] = -0.5*cos(4*PI*ti/(cbsize - 1)) + 0.5;
  }
  
  noverlap = 4;
  
  fmembvars = fft_con(cbsize);
  
  ffttime = (float*) calloc(cbsize, sizeof(float));
  fftfreqre = (float*) calloc(corrsize, sizeof(float));
  fftfreqim = (float*) calloc(corrsize, sizeof(float));
  
  
  // ---- Calculate autocorrelation of window ----
  acwinv = (float*) calloc(cbsize, sizeof(float));
  for (ti=0; ti<cbsize; ti++) {
    ffttime[ti] = cbwindow[ti];
  }
  fft_forward(fmembvars, cbwindow, fftfreqre, fftfreqim);
  for (ti=0; ti<corrsize; ti++) {
    fftfreqre[ti] = (fftfreqre[ti])*(fftfreqre[ti]) + (fftfreqim[ti])*(fftfreqim[ti]);
    fftfreqim[ti] = 0;
  }
  fft_inverse(fmembvars, fftfreqre, fftfreqim, ffttime);
  for (ti=1; ti<cbsize; ti++) {
    acwinv[ti] = ffttime[ti]/ffttime[0];
    if (acwinv[ti] > 0.000001) {
      acwinv[ti] = (float)1/acwinv[ti];
    }
    else {
      acwinv[ti] = 0;
    }
  }
  acwinv[0] = 1;
  // ---- END Calculate autocorrelation of window ----
  
  lrshift = 0;
  ptarget = 0;
  sptarget = 0;
  wasvoiced = 0;
  persistamt = 0;
  
  glidepersist = 100; // 100 ms glide persist
  
  vthresh = 0.8;  //  The voiced confidence (unbiased peak) threshold level
  
  // Pitch shifter initialization
  phprdd = 0.01; // Default period
  phprd = phprdd;
  phinc = (float)1/(phprd * fs);
  phincfact = 1;
  phasein = 0;
  phaseout = 0;
  frag = (float*) calloc(cbsize, sizeof(float));
  fragsize = 0;
}




void AutoTalent::Reset()
{
  TRACE;
  IMutexLock lock(this);
  
  unsigned long sr = GetSampleRate();
  
  if( fs != sr) init(sr);
}



void AutoTalent::OnParamChange(int paramIdx)
{
  IMutexLock lock(this);
  
  switch (paramIdx)
  {
    case kRoot:
      SetScale();
      break;
      
    case kScale:
      SetScale();
      break;
      
    case kMix:
      fMix = GetParam(kMix)->Value() / 100.;
      break;
    case kShift:
      fShift = GetParam(kShift)->Value();
      break;
    case kTune:
      fTune = GetParam(kTune)->Value() / 100. ;
      break;
    case kAmount:
      fAmount = GetParam(kAmount)->Value() / 100.;
      break;
    case kGlide:
      fGlide = GetParam(kGlide)->Value() / 1000.;
      break;
    case kC:
      fNotes[0] = GetParam(kC)->Value() / 100.;
      break;
    case kDb:
      fNotes[1] = GetParam(kDb)->Value() / 100.;
      break;
    case kD:
      fNotes[2] = GetParam(kD)->Value() / 100.;
      break;
    case kEb:
      fNotes[3] = GetParam(kEb)->Value() / 100.;
      break;
    case kE:
      fNotes[4] = GetParam(kE)->Value() / 100.;
      break;
    case kF:
      fNotes[5] = GetParam(kF)->Value() / 100.;
      break;
    case kGb:
      fNotes[6] = GetParam(kGb)->Value() / 100.;
      break;
    case kG:
      fNotes[7] = GetParam(kG)->Value() / 100.;
      break;
    case kAb:
      fNotes[8] = GetParam(kAb)->Value() / 100.;
      break;
    case kA:
      fNotes[9] = GetParam(kA)->Value() / 100.;
      break;
    case kBb:
      fNotes[10] = GetParam(kBb)->Value() / 100.;
      break;
    case kB:
      fNotes[11] = GetParam(kB)->Value() / 100.;
      break;
    default:
      break;
  }
}

void AutoTalent::SetScale(){
  int sc[12];
  mScales.makeScale(GetParam(kRoot)->Value(), GetParam(kScale)->Value(), sc);
  
  for (int i = 0; i< 12; i++) {
    Keys[i]->SetValueFromPlug(sc[i]);
    Keys[i]->SetDirty(true);
  }
}
