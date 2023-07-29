// --- CMAKE generated variables for your plugin

#include "pluginstructures.h"

#ifndef _plugindescription_h
#define _plugindescription_h

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)
#define AU_COCOA_VIEWFACTORY_STRING STR(AU_COCOA_VIEWFACTORY_NAME)
#define AU_COCOA_VIEW_STRING STR(AU_COCOA_VIEW_NAME)

// --- AU Plugin Cocoa View Names (flat namespace) 
#define AU_COCOA_VIEWFACTORY_NAME AUCocoaViewFactory_3AF9A5D934723D89A67A3D684FB721A6
#define AU_COCOA_VIEW_NAME AUCocoaView_3AF9A5D934723D89A67A3D684FB721A6

// --- BUNDLE IDs (MacOS Only) 
const char* kAAXBundleID = "developer.aax.synthlabks.bundleID";
const char* kAUBundleID = "developer.au.synthlabks.bundleID";
const char* kVST3BundleID = "developer.vst3.synthlabks.bundleID";

// --- Plugin Names 
const char* kPluginName = "SynthLabKS_DM";
const char* kShortPluginName = "SynthLabKS_DM";
const char* kAUBundleName = "SynthLab_KS";

// --- Plugin Type 
const pluginType kPluginType = pluginType::kSynthPlugin;

// --- VST3 UUID 
const char* kVSTFUID = "{3af9a5d9-3472-3d89-a67a-3d684fb721a6}";

// --- 4-char codes 
const int32_t kFourCharCode = 'SyKs';
const int32_t kAAXProductID = 'SyKs';
const int32_t kManufacturerID = 'SyKs';

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
