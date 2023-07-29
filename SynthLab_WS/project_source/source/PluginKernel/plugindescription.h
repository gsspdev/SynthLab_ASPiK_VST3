// --- CMAKE generated variables for your plugin

#include "pluginstructures.h"

#ifndef _plugindescription_h
#define _plugindescription_h

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)
#define AU_COCOA_VIEWFACTORY_STRING STR(AU_COCOA_VIEWFACTORY_NAME)
#define AU_COCOA_VIEW_STRING STR(AU_COCOA_VIEW_NAME)

// --- AU Plugin Cocoa View Names (flat namespace) 
#define AU_COCOA_VIEWFACTORY_NAME AUCocoaViewFactory_8D6BCE9916EE36F29A2014C6E5305C32
#define AU_COCOA_VIEW_NAME AUCocoaView_8D6BCE9916EE36F29A2014C6E5305C32

// --- BUNDLE IDs (MacOS Only) 
const char* kAAXBundleID = "developer.aax.synthlabws.bundleID";
const char* kAUBundleID = "developer.au.synthlabws.bundleID";
const char* kVST3BundleID = "developer.vst3.synthlabws.bundleID";

// --- Plugin Names 
const char* kPluginName = "SynthLabWS_DM";
const char* kShortPluginName = "SynthLabWS_DM";
const char* kAUBundleName = "SynthLab_WS";

// --- Plugin Type 
const pluginType kPluginType = pluginType::kSynthPlugin;

// --- VST3 UUID 
const char* kVSTFUID = "{8d6bce99-16ee-36f2-9a20-14c6e5305c32}";

// --- 4-char codes 
const int32_t kFourCharCode = 'SyWS';
const int32_t kAAXProductID = 'SyWS';
const int32_t kManufacturerID = 'SyWS';

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
