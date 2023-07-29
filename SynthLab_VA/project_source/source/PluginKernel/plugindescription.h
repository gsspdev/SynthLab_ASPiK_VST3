// --- CMAKE generated variables for your plugin

#include "pluginstructures.h"

#ifndef _plugindescription_h
#define _plugindescription_h

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)
#define AU_COCOA_VIEWFACTORY_STRING STR(AU_COCOA_VIEWFACTORY_NAME)
#define AU_COCOA_VIEW_STRING STR(AU_COCOA_VIEW_NAME)

// --- AU Plugin Cocoa View Names (flat namespace) 
#define AU_COCOA_VIEWFACTORY_NAME AUCocoaViewFactory_83B382E4F166359CB7AD567949856F18
#define AU_COCOA_VIEW_NAME AUCocoaView_83B382E4F166359CB7AD567949856F18

// --- BUNDLE IDs (MacOS Only) 
const char* kAAXBundleID = "developer.aax.synthlabva.bundleID";
const char* kAUBundleID = "developer.au.synthlabva.bundleID";
const char* kVST3BundleID = "developer.vst3.synthlabva.bundleID";

// --- Plugin Names 
const char* kPluginName = "SynthLabVA_DM";
const char* kShortPluginName = "SynthLabVA_DM";
const char* kAUBundleName = "SynthLab_VA";

// --- Plugin Type 
const pluginType kPluginType = pluginType::kSynthPlugin;

// --- VST3 UUID 
const char* kVSTFUID = "{83b382e4-f166-359c-b7ad-567949856f18}";

// --- 4-char codes 
const int32_t kFourCharCode = 'SlvA';
const int32_t kAAXProductID = 'SlvA';
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
