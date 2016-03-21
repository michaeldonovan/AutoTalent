// Double quotes, spaces OK.
#define PLUG_MFR "OliLarkin"
#define PLUG_NAME "autotalent"

// No quotes or spaces.
#define PLUG_CLASS_NAME IPlugin

// OSX crap.
// - Manually edit the info.plist file to set the CFBundleIdentifier to the either the string 
// "com.BUNDLE_MFR.audiounit.BUNDLE_NAME" or "com.BUNDLE_MFR.vst.BUNDLE_NAME".
// Double quotes, no spaces.
#define BUNDLE_MFR "OliLarkin"
#define BUNDLE_NAME "autotalent"

// - Manually create a PLUG_CLASS_NAME.exp file with two entries: _PLUG_ENTRY and _PLUG_VIEW_ENTRY
// (these two defines, each with a leading underscore).
// No quotes or spaces.
#define PLUG_ENTRY IPlugin_Entry
#define PLUG_VIEW_ENTRY IPlugin_ViewEntry

// The same strings, with double quotes.  There's no other way, trust me.
#define PLUG_ENTRY_STR "IPlugin_Entry"
#define PLUG_VIEW_ENTRY_STR "IPlugin_ViewEntry"

// This is the exported cocoa view class, some hosts display this string.
// No quotes or spaces.
#define VIEW_CLASS IPlugin_View
#define VIEW_CLASS_STR "IPlugin_View"

// This is interpreted as 0xMAJR.MN.BG
#define PLUG_VER 0x00010000

// http://service.steinberg.de/databases/plugin.nsf/plugIn?openForm
// 4 chars, single quotes. At least one capital letter
#define PLUG_UNIQUE_ID 'AutT'
#define PLUG_MFR_ID 'oliL' // make sure this is not the same as BUNDLE_MFR

#define PLUG_CHANNEL_IO "1-1 2-2"

#define PLUG_LATENCY 0
#define PLUG_IS_INST 0
#define PLUG_DOES_MIDI 0
#define PLUG_DOES_STATE_CHUNKS 0

