// Michael Donovan - 3/10/16

#ifndef IPopupMenuControl_h
#define IPopupMenuControl_h

class IPopUpMenuControl : public IControl
{
public:
    IPopUpMenuControl(IPlugBase *pPlug, IRECT pR, IColor cBG, IColor cFG, IColor textColor , int paramIdx)
    : IControl(pPlug, pR, paramIdx)
    {
        mDisablePrompt = false;
        mDblAsSingleClick = true;
        mColorText = textColor;
        mText = IText(14,&mColorText,"Futura", IText::kStyleNormal, IText::kAlignNear);
        mColor = cBG;
        mColorFG = cFG;
        textRect= IRECT(pR.L+8, pR.T+1, pR.R, pR.B);
    }
    
    bool Draw(IGraphics* pGraphics)
    {
        IColor TriangleColor;
        IChannelBlend blend = IChannelBlend();
        if(IsGrayed()){
            blend.mMethod=blend.kBlendColorDodge;
            blend.mWeight=.8;
            mText = IText(14,&COLOR_GRAY,"Futura", IText::kStyleNormal, IText::kAlignNear);
        }
        else{
            mText = IText(14,&mColorText,"Futura", IText::kStyleNormal, IText::kAlignNear);
            blend = IChannelBlend();
        }

        //pGraphics->FillIRect(&mColor, &mRECT, &blend);
        //pGraphics->FillTriangle(&COLOR_GRAY, mRECT.L+4, mRECT.T+4, mRECT.L+4, mRECT.B-4, mRECT.L+8, (mRECT.T + mRECT.H()/2 ), &blend);
        char disp[32];
        mPlug->GetParam(mParamIdx)->GetDisplayForHost(disp);
        
        if (CSTR_NOT_EMPTY(disp))
        {
            return pGraphics->DrawIText(&mText, disp, &textRect);
        }
        
        return true;
    }
    
    void OnMouseDown(int x, int y, IMouseMod* pMod)
    {
        if (pMod->L)
        {
            PromptUserInput(&mRECT);
        }
        
        mPlug->GetGUI()->SetAllControlsDirty();
    }
    
private:
    IColor mColor;
    IColor mColorFG;
    IColor mColorText;
    IRECT textRect;
};

#endif /* IPopupMenuControl_h */
