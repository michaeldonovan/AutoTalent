//
//  IKnobMultiControlText.h
//  AutoTalentMD
//
//  Created by Michael on 3/21/16.
//
//

#ifndef IKnobMultiControlText_h
#define IKnobMultiControlText_h

#include "IControl.h"

class IKnobMultiControlText : public IKnobControl
{
private:
    IRECT mTextRECT, mImgRECT, mInputRECT;
    IBitmap mBitmap;
    bool mShowParamLabel;
public:
    IKnobMultiControlText(IPlugBase* pPlug, IRECT pR, int paramIdx, IBitmap* pBitmap, IText* pText, bool showParamLabel)
    : IKnobControl(pPlug, pR, paramIdx), mBitmap(*pBitmap), mShowParamLabel(showParamLabel)
    {
        mText = *pText;
        mTextRECT = IRECT(mRECT.L, mRECT.B-20, mRECT.R, mRECT.B);
        mImgRECT = IRECT(mRECT.L, mRECT.T, &mBitmap);
        mInputRECT = IRECT(mTextRECT.L+25, mTextRECT.T, mTextRECT.R-25, mTextRECT.B);
        mDisablePrompt = false;
    }
    
    ~IKnobMultiControlText() {}
    
    bool Draw(IGraphics* pGraphics)
    {
        int i = 1 + int(0.5 + mValue * (double) (mBitmap.N - 1));
        i = BOUNDED(i, 1, mBitmap.N);
        pGraphics->DrawBitmap(&mBitmap, &mImgRECT, i, &mBlend);
        //pGraphics->FillIRect(&COLOR_WHITE, &mTextRECT);
        
        char disp[20];
        mPlug->GetParam(mParamIdx)->GetDisplayForHost(disp);
        std::string str(disp);
        if (CSTR_NOT_EMPTY(disp))
        {
            if (mShowParamLabel)
            {
                str += " ";
                str += mPlug->GetParam(mParamIdx)->GetLabelForHost();
            }
            const char* cstr = str.c_str();
            return pGraphics->DrawIText(&mText, (char*)cstr, &mTextRECT);
        }
        return true;
    }
    
    void OnMouseDown(int x, int y, IMouseMod* pMod)
    {
        if (mTextRECT.Contains(x, y)) PromptUserInput(&mInputRECT);
#ifdef RTAS_API
        else if (pMod->A)
        {
            if (mDefaultValue >= 0.0)
            {
                mValue = mDefaultValue;
                SetDirty();
            }
        }
#endif
        else
        {
            OnMouseDrag(x, y, 0, 0, pMod);
        }
    }
    
    void OnMouseDblClick(int x, int y, IMouseMod* pMod)
    {
#ifdef RTAS_API
        PromptUserInput(&mTextRECT);
#else
        if (mDefaultValue >= 0.0)
        {
            mValue = mDefaultValue;
            SetDirty();
        }
#endif
    }
    
};


#endif /* IKnobMultiControlText_h */
