// --- CMAKE generated variables for your plugin

#include "pluginstructures.h"

#ifndef _plugindescription_h
#define _plugindescription_h

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)
#define AU_COCOA_VIEWFACTORY_STRING STR(AU_COCOA_VIEWFACTORY_NAME)
#define AU_COCOA_VIEW_STRING STR(AU_COCOA_VIEW_NAME)

// --- AU Plugin Cocoa View Names (flat namespace) 
#define AU_COCOA_VIEWFACTORY_NAME AUCocoaViewFactory_76EA5583A428324E866CD0850C989FD2
#define AU_COCOA_VIEW_NAME AUCocoaView_76EA5583A428324E866CD0850C989FD2

// --- BUNDLE IDs (MacOS Only) 
const char* kAAXBundleID = "developer.aax.synthlabpcm.bundleID";
const char* kAUBundleID = "developer.au.synthlabpcm.bundleID";
const char* kVST3BundleID = "developer.vst3.synthlabpcm.bundleID";

// --- Plugin Names 
const char* kPluginName = "SynthLabPCM_DM";
const char* kShortPluginName = "SynthLabPCM_DM";
const char* kAUBundleName = "SynthLab_PCM";

// --- Plugin Type 
const pluginType kPluginType = pluginType::kSynthPlugin;

// --- VST3 UUID 
const char* kVSTFUID = "{76ea5583-a428-324e-866c-d0850c989fd2}";

// --- 4-char codes 
const int32_t kFourCharCode = 'SlPM';
const int32_t kAAXProductID = 'SlPM';
const int32_t kManufacturerID = 'SlPM';

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
