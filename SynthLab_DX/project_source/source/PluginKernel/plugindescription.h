// --- CMAKE generated variables for your plugin

#include "pluginstructures.h"

#ifndef _plugindescription_h
#define _plugindescription_h

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)
#define AU_COCOA_VIEWFACTORY_STRING STR(AU_COCOA_VIEWFACTORY_NAME)
#define AU_COCOA_VIEW_STRING STR(AU_COCOA_VIEW_NAME)

// --- AU Plugin Cocoa View Names (flat namespace) 
#define AU_COCOA_VIEWFACTORY_NAME AUCocoaViewFactory_1E1232FB63BE3FA1AE5500F4797761D3
#define AU_COCOA_VIEW_NAME AUCocoaView_1E1232FB63BE3FA1AE5500F4797761D3

// --- BUNDLE IDs (MacOS Only) 
const char* kAAXBundleID = "developer.aax.synthlabdx.bundleID";
const char* kAUBundleID = "developer.au.synthlabdx.bundleID";
const char* kVST3BundleID = "developer.vst3.synthlabdx.bundleID";

// --- Plugin Names 
const char* kPluginName = "SynthLabDX_DM";
const char* kShortPluginName = "SynthLabDX_DM";
const char* kAUBundleName = "SynthLab_DX";

// --- Plugin Type 
const pluginType kPluginType = pluginType::kSynthPlugin;

// --- VST3 UUID 
const char* kVSTFUID = "{1e1232fb-63be-3fa1-ae55-00f4797761d3}";

// --- 4-char codes 
const int32_t kFourCharCode = 'SyDx';
const int32_t kAAXProductID = 'SyDx';
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
