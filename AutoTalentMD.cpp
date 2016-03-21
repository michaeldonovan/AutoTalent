#include "AutoTalentMD.h"
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
  kInfo,
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
  
  kTitlesY = 17,
  kKnobFrames = 63
};

AutoTalentMD::AutoTalentMD(IPlugInstanceInfo instanceInfo):
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
  GetParam(kTune)->InitDouble("Fine Tune", 0.0, -1., 1., 0.01, "st");
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

  GetParam(kInfo)->InitBool("Info", false);
  
  
  IBitmap Knob = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, kKnobFrames);
  IBitmap Info = pGraphics->LoadIBitmap(INFO_ID, INFO_FN);

  pGraphics->AttachBackground(BACKGROUND_ID, BACKGROUND_FN);

  IText caption = IText(14, &COLOR_WHITE, "Futura", IText::kStyleNormal, IText::kAlignCenter);
  IText title = IText(20, &COLOR_WHITE, "Futura", IText::kStyleNormal, IText::kAlignCenter);
  //pGraphics->AttachControl(new IKnobMultiControl(this, kKnob1X, kKnobsY, kShift, &Knob));
  //pGraphics->AttachControl(new IKnobMultiControl(this, kKnob2X, kKnobsY, kTune, &Knob));
  //pGraphics->AttachControl(new IKnobMultiControl(this, kKnob3X, kKnobsY, kAmount, &Knob));
  //pGraphics->AttachControl(new IKnobMultiControl(this, kKnob4X, kKnobsY, kGlide, &Knob));
  
  pGraphics->AttachControl(new IKnobMultiControlText(this, IRECT(kKnob1X, kKnobsY, kKnob1X+83, kKnobsY+90), kShift, &Knob, &caption, true));
  pGraphics->AttachControl(new IKnobMultiControlText(this, IRECT(kKnob2X, kKnobsY, kKnob2X+83, kKnobsY+90), kTune, &Knob, &caption, true));
  pGraphics->AttachControl(new IKnobMultiControlText(this, IRECT(kKnob3X, kKnobsY, kKnob3X+83, kKnobsY+90), kAmount, &Knob, &caption, true));
  pGraphics->AttachControl(new IKnobMultiControlText(this, IRECT(kKnob4X, kKnobsY, kKnob4X+83, kKnobsY+90), kGlide, &Knob, &caption, true));
  
  pGraphics->AttachControl(new ITextControl(this, IRECT(kKnob1X, kTitlesY, kKnob1X+83, kKnobsY), &title, "Transpose"));
  pGraphics->AttachControl(new ITextControl(this, IRECT(kKnob2X, kTitlesY, kKnob2X+83, kKnobsY), &title, "Tune"));
  pGraphics->AttachControl(new ITextControl(this, IRECT(kKnob3X, kTitlesY, kKnob3X+83, kKnobsY), &title, "Amount"));
  pGraphics->AttachControl(new ITextControl(this, IRECT(kKnob4X, kTitlesY, kKnob4X+83, kKnobsY), &title, "Glide"));

  shiftCaption = new ICaptionControl(this, IRECT(kKnob1X, kKnobsY+70, kKnob1X+83, kKnobsY+80), kShift, &caption, true);
  tuneCaption = new ICaptionControl(this, IRECT(kKnob2X, kKnobsY+70, kKnob2X+83, kKnobsY+80), kTune, &caption, true);
  amountCaption = new ICaptionControl(this, IRECT(kKnob3X, kKnobsY+70, kKnob3X+83, kKnobsY+80), kAmount, &caption, true);
  glideCaption = new ICaptionControl(this, IRECT(kKnob4X, kKnobsY+70, kKnob4X+83, kKnobsY+80), kGlide, &caption, true);
  //pGraphics->AttachControl(shiftCaption);
  //pGraphics->AttachControl(tuneCaption);
  //pGraphics->AttachControl(amountCaption);
 // pGraphics->AttachControl(glideCaption);
  
  IText versionText = IText(12, &LIGHTER_GRAY, "Futura");
  pGraphics->AttachControl(new ITextControl(this, IRECT(170, 312, 220, 320), &versionText, version));

  AttachGraphics(pGraphics);
  
  
   //MakePreset("preset 1", ... );

}

AutoTalentMD::~AutoTalentMD(){
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
void AutoTalentMD::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
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
              tf2 = fA;
              break;
            case 1:
              tf2 = fBb;
              break;
            case 2:
              tf2 = fB;
              break;
            case 3:
              tf2 = fC;
              break;
            case 4:
              tf2 = fDb;
              break;
            case 5:
              tf2 = fD;
              break;
            case 6:
              tf2 = fEb;
              break;
            case 7:
              tf2 = fE;
              break;
            case 8:
              tf2 = fF;
              break;
            case 9:
              tf2 = fGb;
              break;
            case 10:
              tf2 = fG;
              break;
            case 11:
              tf2 = fAb;
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


void AutoTalentMD::init(unsigned long sr)
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




void AutoTalentMD::Reset()
{
  TRACE;
  IMutexLock lock(this);
  
  unsigned long sr = GetSampleRate();
  
  if( fs != sr) init(sr);
}



void AutoTalentMD::OnParamChange(int paramIdx)
{
  IMutexLock lock(this);
  
  switch (paramIdx)
  {
    case kMix:
      fMix = GetParam(kMix)->Value() / 100.;
      break;
    case kShift:
      fShift = GetParam(kShift)->Value();
      shiftCaption->SetDirty(false);
      break;
    case kTune:
      fTune = GetParam(kTune)->Value();
      tuneCaption->SetDirty(false);
      break;
    case kAmount:
      fAmount = GetParam(kAmount)->Value() / 100.;
      amountCaption->SetDirty(false);
      break;
    case kGlide:
      fGlide = GetParam(kGlide)->Value() / 1000.;
      glideCaption->SetDirty(false);
      break;
    case kC:
      fC = GetParam(kC)->Value() / 100.;
      break;
    case kDb:
      fDb = GetParam(kDb)->Value() / 100.;
      break;
    case kD:
      fD = GetParam(kD)->Value() / 100.;
      break;
    case kEb:
      fEb = GetParam(kEb)->Value() / 100.;
      break;
    case kE:
      fE = GetParam(kE)->Value() / 100.;
      break;
    case kF:
      fF = GetParam(kF)->Value() / 100.;
      break;
    case kGb:
      fGb = GetParam(kGb)->Value() / 100.;
      break;
    case kG:
      fG = GetParam(kG)->Value() / 100.;
      break;
    case kAb:
      fAb = GetParam(kAb)->Value() / 100.;
      break;
    case kA:
      fA = GetParam(kA)->Value() / 100.;
      break;
    case kBb:
      fBb = GetParam(kBb)->Value() / 100.;
      break;
    case kB:
      fB = GetParam(kB)->Value() / 100.;
      break;
    default:
      break;
  }
}

