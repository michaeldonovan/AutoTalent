#define PLUG_MFR "Michael Donovan"
#define PLUG_NAME "AutoTalent-MD"

#define PLUG_CLASS_NAME AutoTalentMD

#define BUNDLE_MFR "michaeldonovan"
#define BUNDLE_NAME "AutoTalentMD"

#define PLUG_ENTRY AutoTalentMD_Entry
#define PLUG_VIEW_ENTRY AutoTalentMD_ViewEntry

#define PLUG_ENTRY_STR "AutoTalentMD_Entry"
#define PLUG_VIEW_ENTRY_STR "AutoTalentMD_ViewEntry"

#define VIEW_CLASS AutoTalentMD_View
#define VIEW_CLASS_STR "AutoTalentMD_View"

// Format        0xMAJR.MN.BG - in HEX! so version 10.1.5 would be 0x000A0105
#define PLUG_VER 0x00010000
#define VST3_VER_STR "1.0.0"

// http://service.steinberg.de/databases/plugin.nsf/plugIn?openForm
// 4 chars, single quotes. At least one capital letter
#define PLUG_UNIQUE_ID 'dfdh'
// make sure this is not the same as BUNDLE_MFR
#define PLUG_MFR_ID 'Dnvn'

// ProTools stuff

#if (defined(AAX_API) || defined(RTAS_API)) && !defined(_PIDS_)
  #define _PIDS_
  const int PLUG_TYPE_IDS[2] = {'EFN1', 'EFN2'};
  const int PLUG_TYPE_IDS_AS[2] = {'EFA1', 'EFA2'}; // AudioSuite
#endif

#define PLUG_MFR_PT "michaeldonovan\nmichaeldonovan\nAcme"
#define PLUG_NAME_PT "AutoTalentMD\nIPEF"
#define PLUG_TYPE_PT "Effect"
#define PLUG_DOES_AUDIOSUITE 1

/* PLUG_TYPE_PT can be "None", "EQ", "Dynamics", "PitchShift", "Reverb", "Delay", "Modulation", 
"Harmonic" "NoiseReduction" "Dither" "SoundField" "Effect" 
instrument determined by PLUG _IS _INST
*/

#define PLUG_CHANNEL_IO "1-1 2-2"

#define PLUG_LATENCY 0
#define PLUG_IS_INST 0

// if this is 0 RTAS can't get tempo info
#define PLUG_DOES_MIDI 0

#define PLUG_DOES_STATE_CHUNKS 0

// Unique IDs for each image resource.
#define BACKGROUND_ID 101
#define KNOB_ID 102
#define INFO_ID 103
#define KNOBSTEPPED_ID 104

// Image resource locations for this plug.
#define BACKGROUND_FN "resources/img/Background.png"
#define KNOB_FN "resources/img/Knob.png"
#define INFO_FN "resources/img/Info.png"
#define KNOBSTEPPED_FN "resources/img/KnobStepped.png"

// GUI default dimensions
#define GUI_WIDTH 420
#define GUI_HEIGHT 340

// on MSVC, you must define SA_API in the resource editor preprocessor macros as well as the c++ ones
#if defined(SA_API) && !defined(OS_IOS)
#include "app_wrapper/app_resource.h"
#endif

// vst3 stuff
#define MFR_URL "www.github.com/michaeldonovan"
#define MFR_EMAIL "spam@me.com"
#define EFFECT_TYPE_VST3 "Fx|Distortion"

/* "Fx|Analyzer"", "Fx|Delay", "Fx|Distortion", "Fx|Dynamics", "Fx|EQ", "Fx|Filter",
"Fx", "Fx|Instrument", "Fx|InstrumentExternal", "Fx|Spatial", "Fx|Generator",
"Fx|Mastering", "Fx|Modulation", "Fx|PitchShift", "Fx|Restoration", "Fx|Reverb",
"Fx|Surround", "Fx|Tools", "Instrument", "Instrument|Drum", "Instrument|Sampler",
"Instrument|Synth", "Instrument|Synth|Sampler", "Instrument|External", "Spatial",
"Spatial|Fx", "OnlyRT", "OnlyOfflineProcess", "Mono", "Stereo",
"Surround"
*/
