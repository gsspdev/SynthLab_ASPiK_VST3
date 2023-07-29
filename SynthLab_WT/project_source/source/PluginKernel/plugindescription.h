// --- CMAKE generated variables for your plugin

#include "pluginstructures.h"

#ifndef _plugindescription_h
#define _plugindescription_h

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)
#define AU_COCOA_VIEWFACTORY_STRING STR(AU_COCOA_VIEWFACTORY_NAME)
#define AU_COCOA_VIEW_STRING STR(AU_COCOA_VIEW_NAME)

// --- AU Plugin Cocoa View Names (flat namespace) 
#define AU_COCOA_VIEWFACTORY_NAME AUCocoaViewFactory_EB1A91494401341F979D9C6AEF94F175
#define AU_COCOA_VIEW_NAME AUCocoaView_EB1A91494401341F979D9C6AEF94F175

// --- BUNDLE IDs (MacOS Only) 
const char* kAAXBundleID = "developer.aax.synthlabwt.bundleID";
const char* kAUBundleID = "developer.au.synthlabwt.bundleID";
const char* kVST3BundleID = "developer.vst3.synthlabwt.bundleID";

// --- Plugin Names 
const char* kPluginName = "SynthLabWT_DM";
const char* kShortPluginName = "SynthLabWT_DM";
const char* kAUBundleName = "SynthLab_WT";

// --- Plugin Type 
const pluginType kPluginType = pluginType::kSynthPlugin;

// --- VST3 UUID 
const char* kVSTFUID = "{eb1a9149-4401-341f-979d-9c6aef94f175}";

// --- 4-char codes 
const int32_t kFourCharCode = 'Sl01';
const int32_t kAAXProductID = 'Sl01';
const int32_t kManufacturerID = 'WILL';

// --- Vendor information 
const char* kVendorName = "Will Pirkle";
const char* kVendorURL = "www.willpirkle.com";
const char* kVendorEmail = "willpirkle@gmail.com";

// --- Plugin Options 
const bool kWantSidechain = false;
const uint32_t kLatencyInSamples = 0;
const double kTailTimeMsec = 0.000000;
const bool kVSTInfiniteTail = false;
const bool kVSTSAA = false;
const uint32_t kVST3SAAGranularity = 1;
const uint32_t kAAXCategory = aaxPlugInCategory_None;

#endif
