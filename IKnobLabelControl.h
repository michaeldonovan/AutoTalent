//
//  IKnobLabelControl.h
//  AutoTalentMD
//
//  Created by Michael on 3/21/16.
//
//

#ifndef IKnobLabelControl_h
#define IKnobLabelControl_h

#include "IControl.h"

#include <string>
#include <cstdio>

class IKnobLabelControl : public IKnobControl{
public:
    IKnobLabelControl(IPlugBase* pPlug, int x, int y, int paramIdx, IBitmap* pBitmap, bool decimal=0,
                      EDirection direction = kVertical, double gearing = DEFAULT_GEARING)
    : IKnobControl(pPlug, IRECT(x, y, pBitmap), paramIdx, direction, gearing), mBitmap(*pBitmap), mDecimal(decimal) {}
    ~IKnobLabelControl() {}
    
    
    bool Draw(IGraphics* pGraphics)
    {
        int i = 1 + int(0.5 + mValue * (double) (mBitmap.N - 1));
        i = BOUNDED(i, 1, mBitmap.N);
        IText text = IText(14, &COLOR_WHITE, "Futura", IText::kStyleNormal, IText::kAlignCenter);
        IRECT textRect = IRECT(mRECT.L+50, mRECT.B, mRECT.R, mRECT.T+40);
        pGraphics->DrawIText(&text, (char*)formatLabel(), &textRect);
        return pGraphics->DrawBitmap(&mBitmap, &mRECT, i, &mBlend);
    }
    
private:
    IBitmap mBitmap;
    bool mDecimal;
    
    const char* formatLabel(){
        std::string s;
        double value = mPlug->GetParam(mParamIdx)->Value();
        const char* label = mPlug->GetParam(mParamIdx)->GetLabelForHost();
        
        if(mDecimal){
            auto format = std::snprintf(&s[0], s.size(), "%.1f", value);
            s.resize(format);
        }
        else{
            auto format = std::snprintf(&s[0], s.size(), "%.0f", value);
            s.resize(format);        }
        std::string out = s + label;
        
        
        return out.c_str();
    }
};
#endif /* IKnobLabelControl_h */
