//
//  ICrossoverControl.h
//
//  Created by Michael Donovan on 3/9/16.
//  Inspired by MyGraphicControl class by deisss (https://github.com/Deisss/IPlug-basic-graphic-example)
//

#ifndef ICrossoverControl_H
#define ICrossoverControl_H
#include "IControl.h"

#include "IControl.h"
#include <vector>
#include <algorithm>
#include <sstream>

class CrossoverHandle {
public:
    double x;
    int uid;
    bool operator < (const CrossoverHandle& handle) const { return (this->x < handle.x); };
    bool operator > (const CrossoverHandle& handle) const {	return (this->x > handle.x); };
};

class ICrossoverControl : public IControl {
protected:
    IColor* mColor;
    IColor* mColor2;
    IColor* mColor3; 
    CrossoverHandle handles[3];
    CrossoverHandle selected;
    double minFreq;
    double maxFreq;
    double mValue2;
    double mValue3;
    int mParamIdx2;
    int mParamIdx3;
    bool isDragging;
    
    double percentToCoordinates(double value) {
        double min = (double) this->mRECT.L;
        double distance = (double) this->mRECT.W();
        return value * distance + min;
    };
    double convertToPercent(double value) {
        double min = (double) this->mRECT.L;
        double position = value - min;
        double distance = (double) this->mRECT.W();
        return position / distance;
    };

    
public:
    ICrossoverControl(IPlugBase *pPlug, IRECT pR, IColor *c1, IColor *c2, IColor *c3, int paramIdx1, int paramIdx2, int paramIdx3) : IControl(pPlug, pR, paramIdx1),mColor(c1), mColor2(c2), mColor3(c3),isDragging(false),minFreq(20.),maxFreq(20000.),mParamIdx2(paramIdx2),mParamIdx3(paramIdx3) {
        for (int i=0; i<3; i++) {
            handles[i].uid=i+1;
            handles[i].x=.25*(i+1);
        }
        mValue2=getFreq(2);
        mValue3=getFreq(3);
    };
    ~ICrossoverControl() {};
    
    bool Draw(IGraphics *pGraphics){
        if(!IsGrayed()){
            int y = mRECT.T+mRECT.H()/2;
            for (int i=0; i<3; i++) {
                CrossoverHandle* current = &handles[i];
                
                
                if(i==selected.uid-1){
                    pGraphics->DrawVerticalLine(mColor3, percentToCoordinates(current->x), this->mRECT.B, y+4);
                    pGraphics->DrawVerticalLine(mColor3, percentToCoordinates(current->x), y-4, this->mRECT.T);
                    
                    pGraphics->DrawCircle(mColor3, percentToCoordinates(current->x), y, 3);
                    pGraphics->DrawCircle(mColor3, percentToCoordinates(current->x), y, 4);
                }
                else{
                    pGraphics->DrawVerticalLine(mColor, percentToCoordinates(current->x), this->mRECT.B, y+4);
                    pGraphics->DrawVerticalLine(mColor, percentToCoordinates(current->x), y-4, this->mRECT.T);
                    
                    pGraphics->DrawCircle(mColor, percentToCoordinates(current->x), y, 3);
                    pGraphics->DrawCircle(mColor, percentToCoordinates(current->x), y, 4);
                }
                
                //pGraphics->FillCircle(mColor2, percentToCoordinates(current->x), y, 2);
                
                
                IText text = IText(12, &COLOR_WHITE, "Futura");
                const char* str = (formatFreq(getFreq(i+1)));
                IRECT textRect = IRECT(percentToCoordinates(current->x)-10, this->mRECT.B+2, percentToCoordinates(current->x)+10, this->mRECT.B+22);
                pGraphics->DrawIText(&text, (char*)str, &textRect);
            }
        }
        return true;
    };
    
    CrossoverHandle getHandle(double x, double epsilon){
        for (int i=0; i<3; i++) {
            CrossoverHandle current = handles[i];
            double xh = percentToCoordinates(current.x);
            
            if(x-epsilon < xh && x+epsilon > xh){
                return current;
            }
        }
        
        CrossoverHandle none;
        none.uid=0;
        return none;
    };
    
    void OnMouseUp(int x, int y, IMouseMod* pMouseMod){
        isDragging=false;
        CrossoverHandle none;
        none.uid=0;
        selected=none;
    };
    
    void OnMouseDown(int x, int y,  IMouseMod* pMouseMod){
        CrossoverHandle current = getHandle(x, 10);
        if (current.uid==0) {
            CrossoverHandle none;
            none.uid=0;
            selected=none;
            isDragging=false;
            SetDirty(false);
        }
        else{
            selected = current;
            isDragging = true;
            SetDirty(false);
        }
    };
    
    void OnMouseDrag(int x, int y, int dX, int dY, IMouseMod* pMouseMod){
        if(selected.uid==0 || isDragging==false) return;

        double leftBound;
        double rightBound;
        double xPercent=convertToPercent(x);
        
        if (selected.uid==1) {
            leftBound=0;
            rightBound=handles[1].x;
        }
        else if(selected.uid==3){
            leftBound=handles[1].x;
            rightBound=1;
        }
        else{
            leftBound=handles[selected.uid-2].x;
            rightBound=handles[selected.uid].x;
        }

        if(xPercent<rightBound-.05 && xPercent>leftBound+.05){
            handles[selected.uid-1].x=xPercent;
            updateValues();
        }
  
        SetDirty(true);
    };
    
    
    double getFreq(int band){
        double mF = maxFreq/minFreq;
        double xDist = percentToCoordinates(handles[band-1].x)-mRECT.L;
        return minFreq * std::pow(mF, (double)xDist / (double)(mRECT.W()-1));
    };
    
    void updateValues(){
        mValue = handles[0].x;
        mValue2 = handles[1].x;
        mValue3 = handles[2].x;
    }
    
    const char* formatFreq(double freq){
        std::stringstream ss;
        ss << (int)freq;
        std::string val = ss.str();
        std::string out;
        if(freq>=1000 && freq < 10000){
            out = val.substr(0,1) + "." + val.substr(1,2) + "k";
        }
        else if(freq>=10000){
            out = val.substr(0,2) + "." + val.substr(2,1) + "k";
        }
        else{
            out = val;
        }
        
        return out.c_str();
    }
    
    
    void SetDirty(bool pushParamToPlug)
    {
        mDirty = true;
        if (pushParamToPlug && mPlug && mParamIdx >= 0)
        {
            mPlug->SetParameterFromGUI(mParamIdx, mValue);
            mPlug->SetParameterFromGUI(mParamIdx2, mValue2);
            mPlug->SetParameterFromGUI(mParamIdx3, mValue3);

            IParam* pParam = mPlug->GetParam(mParamIdx);
            
            if (mValDisplayControl)
            {
                WDL_String plusLabel;
                char str[32];
                pParam->GetDisplayForHost(str);
                plusLabel.Set(str, 32);
                plusLabel.Append(" ", 32);
                plusLabel.Append(pParam->GetLabelForHost(), 32);
                
                ((ITextControl*)mValDisplayControl)->SetTextFromPlug(plusLabel.Get());
            }
            
            if (mNameDisplayControl) 
            {
                ((ITextControl*)mNameDisplayControl)->SetTextFromPlug((char*) pParam->GetNameForHost());
            }
        }
    }

};

#endif