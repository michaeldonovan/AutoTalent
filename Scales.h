//
//  Scales.h
//
//  Created by Michael Donovan on 3/22/16.
//  All rights reserved
//

#ifndef Scales_h
#define Scales_h




class IScales{
public:
    enum EScaleNames{
        kChromatic=0,
        kMajor,
        kMinor,
        kDorian,
        kMixolydian,
        kLydian,
        kPhrygian,
        kLocrian,
        kHarmonicMinor,
        kMelodicMinor,
        kMajorPentatonic,
        kMinorPentatonic,
        kMinorBlues
    };
    
    enum ENotes{
        kNoteC=0,
        kNoteDb,
        kNoteD,
        kNoteEb,
        kNoteE,
        kNoteF,
        kNoteGb,
        kNoteG,
        kNoteAb,
        kNoteA,
        kNoteBb,
        kNoteB
    };
    
    IScales(){};
    
    ~IScales(){};
    
    
    void makeScale(int root, int scaleType, int arr[]){
        int dst = root;
        for (int src=0; src<12; src++, dst++) {
            
            if (dst >= 12) {
                dst -= 12;
            }
            
            arr[dst] = scaleNotes[scaleType][src];
        }
    }
    
protected:
    const int scaleNotes[13][12] = {
        {1,1,1,1,1,1,1,1,1,1,1,1}, //Chromatic
        {1,0,1,0,1,1,0,1,0,1,0,1}, //Major
        {1,0,1,1,0,1,0,1,1,0,1,0}, //Minor
        {1,0,1,1,0,1,0,1,0,1,1,0}, //Dorian
        {1,0,1,0,1,1,0,1,0,1,1,0}, //Mixolydian
        {1,0,1,0,1,0,1,1,0,1,0,1}, //Lydian
        {1,1,0,1,0,1,0,1,1,0,1,0}, //Phyrgian
        {1,1,0,1,0,1,1,0,1,0,1,0}, //Locrian
        {1,0,1,1,0,1,0,1,1,0,0,1}, //Harmonic Minor
        {1,0,1,1,0,1,0,1,0,1,0,1}, //Melodic Minor
        {1,0,1,0,1,0,0,1,0,1,0,0}, //Maj Pentatonic
        {1,0,0,1,0,1,0,1,0,0,1,0}, //Min Pentatonic
        {1,0,0,1,0,1,1,1,0,0,1,0}, //Minor Blues
    };
};


#endif /* Scales_h */
