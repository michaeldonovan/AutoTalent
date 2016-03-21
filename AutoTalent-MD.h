#ifndef __AUTOTALENT-MD__
#define __AUTOTALENT-MD__

#include "IPlug_include_in_plug_hdr.h"

class AutoTalent-MD : public IPlug
{
public:
  AutoTalent-MD(IPlugInstanceInfo instanceInfo);
  ~AutoTalent-MD();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
  double mGain;
};

#endif
