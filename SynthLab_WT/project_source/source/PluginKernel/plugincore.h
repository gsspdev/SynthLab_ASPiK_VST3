// -----------------------------------------------------------------------------
//    ASPiK Plugin Kernel File:  plugincore.h
//
/**
    \file   plugincore.h
    \author Will Pirkle
    \date   17-September-2018
    \brief  base class interface file for ASPiK plugincore object
    		- http://www.aspikplugins.com
    		- http://www.willpirkle.com
*/
// -----------------------------------------------------------------------------
#ifndef __pluginCore_h__
#define __pluginCore_h__

#include "pluginbase.h"

// --- synths
#include "examples/synthlab_examples/synthengine.h"

// --- dynamic strings only
#include "customviews.h"
#include "source/dm_support/synthlabds.h"

// --- for DM ONLY
#include "source/dm_support/synthlabdm.h"

#define RAFX_PLUGIN 1
//#define VST_PLUGIN 1
//#define AU_PLUGIN 1
//#define AAAX_PLUGIN 1 // not supported at this time

// **--0x7F1F--**

// --- Plugin Variables controlID Enumeration 

enum controlID {
	lfo1_waveform = 1,
	lfo1_mode = 2,
	lfo1_frequency_Hz = 3,
	lfo1_outputAmplitude = 4,
	lfo1_ModKnobA = 6,
	lfo1_ModKnobB = 7,
	lfo1_ModKnobC = 8,
	lfo1_ModKnobD = 9,
	lfo1_quantize = 5,
	ampEG_attackTime_mSec = 22,
	ampEG_decayTime_mSec = 23,
	ampEG_sustainLevel = 24,
	ampEG_releaseTime_mSec = 25,
	ampEGMode = 21,
	ampEG_ModKnobA = 26,
	ampEG_ModKnobB = 27,
	ampEG_ModKnobC = 28,
	ampEG_ModKnobD = 29,
	osc1_waveform = 81,
	osc1CoarseDetune = 82,
	osc1FineDetune = 83,
	osc1_panValue = 84,
	osc1OutputAmplitude_dB = 85,
	osc1_ModKnobA = 86,
	osc1_ModKnobB = 87,
	osc1_ModKnobC = 88,
	osc1_ModKnobD = 89,
	filter1Algorithm = 51,
	filter1_ModKnobA = 56,
	filter1_ModKnobB = 57,
	filter1_ModKnobC = 58,
	filter1_ModKnobD = 59,
	filter1_fc = 52,
	filter1_Q = 53,
	filter1Output_dB = 55,
	enableFilter1KeyTrack = 54,
	filterEGMode = 31,
	filterEG_attackTime_mSec = 32,
	filterEG_decayTime_mSec = 33,
	filterEG_sustainLevel = 34,
	filterEG_releaseTime_mSec = 35,
	filterEG_ModKnobA = 36,
	filterEG_ModKnobB = 37,
	filterEG_ModKnobC = 38,
	filterEG_ModKnobD = 39,
	lfo2_waveform = 11,
	lfo2_mode = 12,
	lfo2_frequency_Hz = 13,
	lfo2_outputAmplitude = 14,
	lfo2_quantize = 15,
	lfo2_ModKnobA = 16,
	lfo2_ModKnobB = 17,
	lfo2_ModKnobC = 18,
	lfo2_ModKnobD = 19,
	auxEGMode = 41,
	auxEG_attackTime_mSec = 42,
	auxEG_decayTime_mSec = 43,
	auxEG_sustainLevel = 44,
	auxEG_releaseTime_mSec = 45,
	auxEG_ModKnobA = 46,
	auxEG_ModKnobB = 47,
	auxEG_ModKnobC = 48,
	auxEG_ModKnobD = 49,
	filter2Algorithm = 61,
	filter2_fc = 62,
	filter2_Q = 63,
	enableFilter2KeyTrack = 64,
	filter2Output_dB = 65,
	filter2_ModKnobA = 66,
	filter2_ModKnobB = 67,
	filter2_ModKnobC = 68,
	filter2_ModKnobD = 69,
	globalVolume_dB = 79,
	globalTuning = 78,
	globalUnisonDetune_Cents = 77,
	globalPitchBendSens = 76,
	synthMode = 75,
	osc2_waveform = 91,
	osc2CoarseDetune = 92,
	osc2FineDetune = 93,
	osc2_panValue = 94,
	osc2OutputAmplitude_dB = 95,
	osc2_ModKnobA = 96,
	osc2_ModKnobB = 97,
	osc2_ModKnobC = 98,
	osc2_ModKnobD = 99,
	osc3_waveform = 101,
	osc3CoarseDetune = 102,
	osc3FineDetune = 103,
	osc3_panValue = 104,
	osc3OutputAmplitude_dB = 105,
	osc3_ModKnobA = 106,
	osc3_ModKnobB = 107,
	osc3_ModKnobC = 108,
	osc3_ModKnobD = 109,
	osc4_waveform = 111,
	osc4CoarseDetune = 112,
	osc4FineDetune = 113,
	osc4_panValue = 114,
	osc4OutputAmplitude_dB = 115,
	osc4_ModKnobA = 116,
	osc4_ModKnobB = 117,
	osc4_ModKnobC = 118,
	osc4_ModKnobD = 119,
	glideTime_mSec = 74,
	osc123_fo_Int = 162,
	osc4_fo_Int = 163,
	osc123_Mod_Int = 164,
	osc4_Mod_Int = 165,
	filter1_fc_Int = 166,
	filter2_fc_Int = 167,
	lfo2_fo_Int = 161,
	lfo1SourceInt = 170,
	lfo2SourceInt = 180,
	auxEGSourceInt = 200,
	auxEGBiasedSourceInt = 210,
	lfo1_lfo2_fc = 171,
	lfo1_osc123_fc = 172,
	lfo1_osc04_fc = 173,
	lfo1_osc123_Mod = 174,
	lfo1_osc04_Mod = 175,
	lfo1_filter1_fc = 176,
	lfo1_filter2_fc = 177,
	lfo2_lfo2_fc = 181,
	lfo2_osc123_fc = 182,
	lfo2_osc04_fc = 183,
	lfo2_osc123_Mod = 184,
	lfo2_osc04_Mod = 185,
	lfo2_filter1_fc = 186,
	lfo2_filter2_fc = 187,
	auxEG_lfo2_fc = 201,
	auxEG_osc123_fc = 202,
	auxEG_osc04_fc = 203,
	auxEG_osc123_Mod = 204,
	auxEG_osc04_Mod = 205,
	auxEG_filter1_fc = 206,
	auxEG_filter2_fc = 207,
	auxEGB_lfo2_fc = 211,
	auxEGB_osc123_fc = 212,
	auxEGB_osc04_fc = 213,
	auxEGB_osc123_Mod = 214,
	auxEGB_osc04_Mod = 215,
	auxEGB_filter1_fc = 216,
	auxEGB_filter2_fc = 217,
	filterModeIndex = 70,
	enableDelayFX = 140,
	leftDelay_mSec = 141,
	rightDelay_mSec = 142,
	feedback_Pct = 143,
	dryLevel_dB = 144,
	wetLevel_dB = 145,
	ampEGIntensity = 149,
	ampEGTrigInt = 169,
	lfo1_ampEGTrig = 179,
	lfo2_ampEGTrig = 189,
	auxEG_ampEGTrig = 209,
	auxEGB_ampEGTrig = 219,
	dcaPanInt = 168,
	lfo1_dcaPan = 178,
	lfo2_dcaPan = 188,
	auxEG_dcaPan = 208,
	auxEGB_dcaPan = 218,
	filterEGSourceInt = 190,
	filterEG_lfo2_fc = 191,
	filterEG_osc123_fc = 192,
	filterEG_osc04_fc = 193,
	filterEG_osc123_Mod = 194,
	filterEG_osc04_Mod = 195,
	filterEG_filter1_fc = 196,
	filterEG_filter2_fc = 197,
	filterEG_dcaPan = 198,
	filterEG_ampEGTrig = 199,
	lfo1Core = 0,
	lfo2Core = 10,
	ampEGCore = 20,
	filterEGCore = 30,
	auxEGCore = 40,
	filter1Core = 50,
	filter2Core = 60,
	osc1Core = 80,
	osc2Core = 90,
	osc3Core = 100,
	osc4Core = 110,
	OSC_SWITCHER = 65568,
	LFO_SWITCHER = 65569,
	EG_SWITCHER = 65570,
	FILTER_SWITCHER = 65571,
	MAIN_SWITCHER = 65572
};

	// **--0x0F1F--**

// --- block processing data struct
//
// --- contains info about the block to process, 
//     and pointers to the needed arrays
struct ProcessBlockInfo
{
	ProcessBlockInfo() { }

	float** inputs = nullptr;			///< audio input buffers
	float** outputs = nullptr;			///< audio output buffers
	float** auxInputs = nullptr;			///< aux (sidechain) input buffers
	float** auxOutputs = nullptr;			///< aux outputs - for future use

	uint32_t numAudioInChannels = 0;		///< audio input channel count
	uint32_t numAudioOutChannels = 0;		///< audio input channel count
	uint32_t numAuxAudioInChannels = 0;		///< audio input channel count
	uint32_t numAuxAudioOutChannels = 0;		///< audio input channel count

	uint32_t currentBlock = 0;			///< index of this block
	uint32_t blockSize = 64;			///< size of this block
	uint32_t blockStartIndex = 0;			///< start
	uint32_t blockEndIndex = 0;			///< end

	// --- should make these const?
	HostInfo* hostInfo = nullptr;			///< pointer to host data for this buffer
	IMidiEventQueue* midiEventQueue = nullptr;	///< MIDI event queue
};


/**
\class PluginCore
\ingroup ASPiK-Core
\brief
The PluginCore object is the default PluginBase derived object for ASPiK projects.
Note that you are fre to change the name of this object (as long as you change it in the compiler settings, etc...)


PluginCore Operations:
- overrides the main processing functions from the base class
- performs reset operation on sub-modules
- processes audio
- processes messages for custom views
- performs pre and post processing functions on parameters and audio (if needed)

\author Will Pirkle http://www.willpirkle.com
\remark This object is included in Designing Audio Effects Plugins in C++ 2nd Ed. by Will Pirkle
\version Revision : 1.0
\date Date : 2018 / 09 / 7
*/
class PluginCore : public PluginBase
{
public:
    PluginCore();

	/** Destructor: empty in default version */
    virtual ~PluginCore(){}

	// --- PluginBase Overrides ---
	//
	/** this is the creation function for all plugin parameters */
	bool initPluginParameters();

	/** called when plugin is loaded, a new audio file is playing or sample rate changes */
	virtual bool reset(ResetInfo& resetInfo);

	/** one-time post creation init function; pluginInfo contains path to this plugin */
	virtual bool initialize(PluginInfo& _pluginInfo);

	// --- preProcess: sync GUI parameters here; override if you don't want to use automatic variable-binding
	virtual bool preProcessAudioBuffers(ProcessBufferInfo& processInfo);

	/** process frames of data */
	virtual bool processAudioFrame(ProcessFrameInfo& processFrameInfo);

	/** process buffers of data */
	virtual bool processAudioBuffers(ProcessBufferInfo& processBufferInfo);

	/** process sub-blocks of data */
	virtual bool processAudioBlock(ProcessBlockInfo& processBlockInfo);

	/** preProcess: do any post-buffer processing required; default operation is to send metering data to GUI  */
	virtual bool postProcessAudioBuffers(ProcessBufferInfo& processInfo);

	/** called by host plugin at top of buffer proccess; this alters parameters prior to variable binding operation  */
	virtual bool updatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo);

	/** called by host plugin at top of buffer proccess; this alters parameters prior to variable binding operation  */
	virtual bool updatePluginParameterNormalized(int32_t controlID, double normalizedValue, ParameterUpdateInfo& paramInfo);

	/** this can be called: 1) after bound variable has been updated or 2) after smoothing occurs  */
	virtual bool postUpdatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo);

	/** this is ony called when the user makes a GUI control change */
	virtual bool guiParameterChanged(int32_t controlID, double actualValue);

	/** processMessage: messaging system; currently used for custom/special GUI operations */
	virtual bool processMessage(MessageInfo& messageInfo);

	/** processMIDIEvent: MIDI event processing */
	virtual bool processMIDIEvent(midiEvent& event);

	/** specialized joystick servicing (currently not used) */
	virtual bool setVectorJoystickParameters(const VectorJoystickData& vectorJoysickData);

	/** create the presets */
	bool initPluginPresets();

	// --- BEGIN USER VARIABLES AND FUNCTIONS -------------------------------------- //
	//	   Add your variables and methods here

	// --- custom block processing info
	SynthLab::SynthProcessInfo synthBlockProcInfo;
	
	// --- the synth engine
	// std::unique_ptr<SynthLab::SynthEngine> synthEngine = nullptr;

	// --- shared if using dynamic string manager
	std::shared_ptr<SynthLab::SynthEngine> synthEngine = nullptr;

	// --- parameter struct pointers
	std::shared_ptr<SynthLab::SynthEngineParameters> engineParameters = nullptr;
	std::shared_ptr<SynthLab::SynthVoiceParameters> voiceParameters = nullptr;

	// --- block info struct
	ProcessBlockInfo processBlockInfo;

	// --- GUI
	void updateParameters();
	void updateEngineParameters();
	void updateVoiceParameters();
	void updateModMatrixParameters();
	
	// --- for all versions RAFX/ASPiK	
	std::unique_ptr<DynamicStringManager> dynStringManager = nullptr;

	// --- for DM ONLY
	DynamicModuleManager dynModuleManager;

	// --- for disabling (VST3 windows)
	void enableParamSmoothing(bool enable);

	// --- END USER VARIABLES AND FUNCTIONS -------------------------------------- //
	// --- CORE_ADD_STEP 2
	inline uint32_t getSubModuleType(uint32_t _controlID)
	{
		if (_controlID == controlID::lfo1Core ||
			_controlID == controlID::lfo2Core)
			return SynthLab::LFO_MODULE;

		if (_controlID == controlID::ampEGCore ||
			_controlID == controlID::filterEGCore ||
			_controlID == controlID::auxEGCore)
			return SynthLab::EG_MODULE;

		if (_controlID == controlID::filter1Core ||
			_controlID == controlID::filter2Core)
			return SynthLab::FILTER_MODULE;

		// --- OSC BLOCK ---
		if (_controlID == controlID::osc1Core ||
			_controlID == controlID::osc2Core ||
			_controlID == controlID::osc3Core ||
			_controlID == controlID::osc4Core)
		{
#ifdef SYNTHLAB_WT
			return SynthLab::WTO_MODULE;
#endif

#ifdef SYNTHLAB_VA
			return SynthLab::VAO_MODULE;
#endif

#ifdef SYNTHLAB_PCM
			return SynthLab::PCMO_MODULE;
#endif
		}
			
		return SynthLab::UNDEFINED_MODULE;
	}

	// --- CORE_ADD_STEP 3
	inline bool isSubModuleOptionMenu(uint32_t _controlID)
	{
		if (_controlID == controlID::lfo1Core ||
			_controlID == controlID::lfo2Core)
			return true;

		if (_controlID == controlID::ampEGCore ||
			_controlID == controlID::filterEGCore ||
			_controlID == controlID::auxEGCore)
			return true;

		if (_controlID == controlID::filter1Core ||
			_controlID == controlID::filter2Core)
			return true;

		if (_controlID == controlID::osc1Core ||
			_controlID == controlID::osc2Core ||
			_controlID == controlID::osc3Core ||
			_controlID == controlID::osc4Core)
			return true;

		return false;
	}

	// --- helpers for aux parameters
	inline void addAuxParamAtt(uint32_t attID, uint32_t attVal, uint32_t controlID)
	{
		AuxParameterAttribute auxAttribute;
		auxAttribute.reset(attID);
		auxAttribute.setUintAttribute(attVal);
		setParamAuxAttribute(controlID, auxAttribute);
	}

	inline void addModuleParamAtts(moduleAuxParamSet& moduleAuxParams)
	{
		addAuxParamAtt(CUSTOM_OPTION_MENU, moduleAuxParams.attValCoreMenu, moduleAuxParams.coreMenuCtrlID);
		addAuxParamAtt(CUSTOM_OPTION_MENU, moduleAuxParams.attValWaveMenu, moduleAuxParams.waveMenuCtrlID);

		addAuxParamAtt(CUSTOM_KNOB_LABEL, moduleAuxParams.attValModKnobs, moduleAuxParams.modKnob_A_CtrlID);
		addAuxParamAtt(CUSTOM_KNOB_LABEL_INDEX, 0, moduleAuxParams.modKnob_A_CtrlID);

		addAuxParamAtt(CUSTOM_KNOB_LABEL, moduleAuxParams.attValModKnobs, moduleAuxParams.modKnob_B_CtrlID);
		addAuxParamAtt(CUSTOM_KNOB_LABEL_INDEX, 1, moduleAuxParams.modKnob_B_CtrlID);

		addAuxParamAtt(CUSTOM_KNOB_LABEL, moduleAuxParams.attValModKnobs, moduleAuxParams.modKnob_C_CtrlID);
		addAuxParamAtt(CUSTOM_KNOB_LABEL_INDEX, 2, moduleAuxParams.modKnob_C_CtrlID);

		addAuxParamAtt(CUSTOM_KNOB_LABEL, moduleAuxParams.attValModKnobs, moduleAuxParams.modKnob_D_CtrlID);
		addAuxParamAtt(CUSTOM_KNOB_LABEL_INDEX, 3, moduleAuxParams.modKnob_D_CtrlID);
	}

private:
	//  **--0x07FD--**

	// --- Continuous Plugin Variables 
	double lfo1_frequency_Hz = 0.0;
	double lfo1_outputAmplitude = 0.0;
	double lfo1_ModKnobA = 0.0;
	double lfo1_ModKnobB = 0.0;
	double lfo1_ModKnobC = 0.0;
	double lfo1_ModKnobD = 0.0;
	int lfo1_quantize = 0;
	double ampEG_attackTime_mSec = 0.0;
	double ampEG_decayTime_mSec = 0.0;
	double ampEG_sustainLevel = 0.0;
	double ampEG_releaseTime_mSec = 0.0;
	double ampEG_ModKnobA = 0.0;
	double ampEG_ModKnobB = 0.0;
	double ampEG_ModKnobC = 0.0;
	double ampEG_ModKnobD = 0.0;
	int osc1CoarseDetune = 0;
	double osc1FineDetune = 0.0;
	double osc1_panValue = 0.0;
	double osc1OutputAmplitude_dB = 0.0;
	double osc1_ModKnobA = 0.0;
	double osc1_ModKnobB = 0.0;
	double osc1_ModKnobC = 0.0;
	double osc1_ModKnobD = 0.0;
	double filter1_ModKnobA = 0.0;
	double filter1_ModKnobB = 0.0;
	double filter1_ModKnobC = 0.0;
	double filter1_ModKnobD = 0.0;
	double filter1_fc = 0.0;
	double filter1_Q = 0.0;
	double filter1Output_dB = 0.0;
	double filterEG_attackTime_mSec = 0.0;
	double filterEG_decayTime_mSec = 0.0;
	double filterEG_sustainLevel = 0.0;
	double filterEG_releaseTime_mSec = 0.0;
	double filterEG_ModKnobA = 0.0;
	double filterEG_ModKnobB = 0.0;
	double filterEG_ModKnobC = 0.0;
	double filterEG_ModKnobD = 0.0;
	double lfo2_frequency_Hz = 0.0;
	double lfo2_outputAmplitude = 0.0;
	int lfo2_quantize = 0;
	double lfo2_ModKnobA = 0.0;
	double lfo2_ModKnobB = 0.0;
	double lfo2_ModKnobC = 0.0;
	double lfo2_ModKnobD = 0.0;
	double auxEG_attackTime_mSec = 0.0;
	double auxEG_decayTime_mSec = 0.0;
	double auxEG_sustainLevel = 0.0;
	double auxEG_releaseTime_mSec = 0.0;
	double auxEG_ModKnobA = 0.0;
	double auxEG_ModKnobB = 0.0;
	double auxEG_ModKnobC = 0.0;
	double auxEG_ModKnobD = 0.0;
	double filter2_fc = 0.0;
	double filter2_Q = 0.0;
	double filter2Output_dB = 0.0;
	double filter2_ModKnobA = 0.0;
	double filter2_ModKnobB = 0.0;
	double filter2_ModKnobC = 0.0;
	double filter2_ModKnobD = 0.0;
	double globalVolume_dB = 0.0;
	double globalTuning = 0.0;
	double globalUnisonDetune_Cents = 0.0;
	double globalPitchBendSens = 0.0;
	int osc2CoarseDetune = 0;
	double osc2FineDetune = 0.0;
	double osc2_panValue = 0.0;
	double osc2OutputAmplitude_dB = 0.0;
	double osc2_ModKnobA = 0.0;
	double osc2_ModKnobB = 0.0;
	double osc2_ModKnobC = 0.0;
	double osc2_ModKnobD = 0.0;
	int osc3CoarseDetune = 0;
	double osc3FineDetune = 0.0;
	double osc3_panValue = 0.0;
	double osc3OutputAmplitude_dB = 0.0;
	double osc3_ModKnobA = 0.0;
	double osc3_ModKnobB = 0.0;
	double osc3_ModKnobC = 0.0;
	double osc3_ModKnobD = 0.0;
	int osc4CoarseDetune = 0;
	double osc4FineDetune = 0.0;
	double osc4_panValue = 0.0;
	double osc4OutputAmplitude_dB = 0.0;
	double osc4_ModKnobA = 0.0;
	double osc4_ModKnobB = 0.0;
	double osc4_ModKnobC = 0.0;
	double osc4_ModKnobD = 0.0;
	float glideTime_mSec = 0.f;
	double osc123_fo_Int = 0.0;
	double osc4_fo_Int = 0.0;
	double osc123_Mod_Int = 0.0;
	double osc4_Mod_Int = 0.0;
	double filter1_fc_Int = 0.0;
	double filter2_fc_Int = 0.0;
	double lfo2_fo_Int = 0.0;
	double lfo1SourceInt = 0.0;
	double lfo2SourceInt = 0.0;
	double auxEGSourceInt = 0.0;
	double auxEGBiasedSourceInt = 0.0;
	double leftDelay_mSec = 0.0;
	double rightDelay_mSec = 0.0;
	double feedback_Pct = 0.0;
	double dryLevel_dB = 0.0;
	double wetLevel_dB = 0.0;
	double ampEGIntensity = 0.0;
	double ampEGTrigInt = 0.0;
	double dcaPanInt = 0.0;
	double filterEGSourceInt = 0.0;

	// --- Discrete Plugin Variables 
	int lfo1_waveform = 0;
	enum class lfo1_waveformEnum { wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15 };	// to compare: if(compareEnumToInt(lfo1_waveformEnum::wave0, lfo1_waveform)) etc... 

	int lfo1_mode = 0;
	enum class lfo1_modeEnum { sync,one_shot,free_run };	// to compare: if(compareEnumToInt(lfo1_modeEnum::sync, lfo1_mode)) etc... 

	int ampEGMode = 0;
	enum class ampEGModeEnum { eg0,eg1,eg2,eg3,eg4,eg5,eg6,eg7,eg8,eg9,eg10,eg11,eg12,eg13,eg14,eg15 };	// to compare: if(compareEnumToInt(ampEGModeEnum::eg0, ampEGMode)) etc... 

	int osc1_waveform = 0;
	enum class osc1_waveformEnum { wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15 };	// to compare: if(compareEnumToInt(osc1_waveformEnum::wave0, osc1_waveform)) etc... 

	int filter1Algorithm = 0;
	enum class filter1AlgorithmEnum { filter0,filter1,filter2,filter3,filter4,filter5,filter6,filter7,filter8,filter9,filter10,filter11,filter12,filter13,filter14,filter15 };	// to compare: if(compareEnumToInt(filter1AlgorithmEnum::filter0, filter1Algorithm)) etc... 

	int enableFilter1KeyTrack = 0;
	enum class enableFilter1KeyTrackEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(enableFilter1KeyTrackEnum::SWITCH_OFF, enableFilter1KeyTrack)) etc... 

	int filterEGMode = 0;
	enum class filterEGModeEnum { eg0,eg1,eg2,eg3,eg4,eg5,eg6,eg7,eg8,eg9,eg10,eg11,eg12,eg13,eg14,eg15 };	// to compare: if(compareEnumToInt(filterEGModeEnum::eg0, filterEGMode)) etc... 

	int lfo2_waveform = 0;
	enum class lfo2_waveformEnum { wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15 };	// to compare: if(compareEnumToInt(lfo2_waveformEnum::wave0, lfo2_waveform)) etc... 

	int lfo2_mode = 0;
	enum class lfo2_modeEnum { sync,one_shot,free_run };	// to compare: if(compareEnumToInt(lfo2_modeEnum::sync, lfo2_mode)) etc... 

	int auxEGMode = 0;
	enum class auxEGModeEnum { eg0,eg1,eg2,eg3,eg4,eg5,eg6,eg7,eg8,eg9,eg10,eg11,eg12,eg13,eg14,eg15 };	// to compare: if(compareEnumToInt(auxEGModeEnum::eg0, auxEGMode)) etc... 

	int filter2Algorithm = 0;
	enum class filter2AlgorithmEnum { No_Filter,LPF1,HPF1,APF1,SVF_LP,SVF_HP,SVF_BP,SVF_BS,Korg35_LP,Korg35_HP,Moog_LP1,Moog_LP2,Moog_LP3,Moog_LP4,Diode_LP4,user };	// to compare: if(compareEnumToInt(filter2AlgorithmEnum::No_Filter, filter2Algorithm)) etc... 

	int enableFilter2KeyTrack = 0;
	enum class enableFilter2KeyTrackEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(enableFilter2KeyTrackEnum::SWITCH_OFF, enableFilter2KeyTrack)) etc... 

	int synthMode = 0;
	enum class synthModeEnum { Mono,Legato,Unison,UniLegato,Poly };	// to compare: if(compareEnumToInt(synthModeEnum::Mono, synthMode)) etc... 

	int osc2_waveform = 0;
	enum class osc2_waveformEnum { wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15 };	// to compare: if(compareEnumToInt(osc2_waveformEnum::wave0, osc2_waveform)) etc... 

	int osc3_waveform = 0;
	enum class osc3_waveformEnum { wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15 };	// to compare: if(compareEnumToInt(osc3_waveformEnum::wave0, osc3_waveform)) etc... 

	int osc4_waveform = 0;
	enum class osc4_waveformEnum { wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15 };	// to compare: if(compareEnumToInt(osc4_waveformEnum::wave0, osc4_waveform)) etc... 

	int lfo1_lfo2_fc = 0;
	enum class lfo1_lfo2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo1_lfo2_fcEnum::SWITCH_OFF, lfo1_lfo2_fc)) etc... 

	int lfo1_osc123_fc = 0;
	enum class lfo1_osc123_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo1_osc123_fcEnum::SWITCH_OFF, lfo1_osc123_fc)) etc... 

	int lfo1_osc04_fc = 0;
	enum class lfo1_osc04_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo1_osc04_fcEnum::SWITCH_OFF, lfo1_osc04_fc)) etc... 

	int lfo1_osc123_Mod = 0;
	enum class lfo1_osc123_ModEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo1_osc123_ModEnum::SWITCH_OFF, lfo1_osc123_Mod)) etc... 

	int lfo1_osc04_Mod = 0;
	enum class lfo1_osc04_ModEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo1_osc04_ModEnum::SWITCH_OFF, lfo1_osc04_Mod)) etc... 

	int lfo1_filter1_fc = 0;
	enum class lfo1_filter1_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo1_filter1_fcEnum::SWITCH_OFF, lfo1_filter1_fc)) etc... 

	int lfo1_filter2_fc = 0;
	enum class lfo1_filter2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo1_filter2_fcEnum::SWITCH_OFF, lfo1_filter2_fc)) etc... 

	int lfo2_lfo2_fc = 0;
	enum class lfo2_lfo2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo2_lfo2_fcEnum::SWITCH_OFF, lfo2_lfo2_fc)) etc... 

	int lfo2_osc123_fc = 0;
	enum class lfo2_osc123_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo2_osc123_fcEnum::SWITCH_OFF, lfo2_osc123_fc)) etc... 

	int lfo2_osc04_fc = 0;
	enum class lfo2_osc04_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo2_osc04_fcEnum::SWITCH_OFF, lfo2_osc04_fc)) etc... 

	int lfo2_osc123_Mod = 0;
	enum class lfo2_osc123_ModEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo2_osc123_ModEnum::SWITCH_OFF, lfo2_osc123_Mod)) etc... 

	int lfo2_osc04_Mod = 0;
	enum class lfo2_osc04_ModEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo2_osc04_ModEnum::SWITCH_OFF, lfo2_osc04_Mod)) etc... 

	int lfo2_filter1_fc = 0;
	enum class lfo2_filter1_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo2_filter1_fcEnum::SWITCH_OFF, lfo2_filter1_fc)) etc... 

	int lfo2_filter2_fc = 0;
	enum class lfo2_filter2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo2_filter2_fcEnum::SWITCH_OFF, lfo2_filter2_fc)) etc... 

	int auxEG_lfo2_fc = 0;
	enum class auxEG_lfo2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEG_lfo2_fcEnum::SWITCH_OFF, auxEG_lfo2_fc)) etc... 

	int auxEG_osc123_fc = 0;
	enum class auxEG_osc123_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEG_osc123_fcEnum::SWITCH_OFF, auxEG_osc123_fc)) etc... 

	int auxEG_osc04_fc = 0;
	enum class auxEG_osc04_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEG_osc04_fcEnum::SWITCH_OFF, auxEG_osc04_fc)) etc... 

	int auxEG_osc123_Mod = 0;
	enum class auxEG_osc123_ModEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEG_osc123_ModEnum::SWITCH_OFF, auxEG_osc123_Mod)) etc... 

	int auxEG_osc04_Mod = 0;
	enum class auxEG_osc04_ModEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEG_osc04_ModEnum::SWITCH_OFF, auxEG_osc04_Mod)) etc... 

	int auxEG_filter1_fc = 0;
	enum class auxEG_filter1_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEG_filter1_fcEnum::SWITCH_OFF, auxEG_filter1_fc)) etc... 

	int auxEG_filter2_fc = 0;
	enum class auxEG_filter2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEG_filter2_fcEnum::SWITCH_OFF, auxEG_filter2_fc)) etc... 

	int auxEGB_lfo2_fc = 0;
	enum class auxEGB_lfo2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEGB_lfo2_fcEnum::SWITCH_OFF, auxEGB_lfo2_fc)) etc... 

	int auxEGB_osc123_fc = 0;
	enum class auxEGB_osc123_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEGB_osc123_fcEnum::SWITCH_OFF, auxEGB_osc123_fc)) etc... 

	int auxEGB_osc04_fc = 0;
	enum class auxEGB_osc04_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEGB_osc04_fcEnum::SWITCH_OFF, auxEGB_osc04_fc)) etc... 

	int auxEGB_osc123_Mod = 0;
	enum class auxEGB_osc123_ModEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEGB_osc123_ModEnum::SWITCH_OFF, auxEGB_osc123_Mod)) etc... 

	int auxEGB_osc04_Mod = 0;
	enum class auxEGB_osc04_ModEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEGB_osc04_ModEnum::SWITCH_OFF, auxEGB_osc04_Mod)) etc... 

	int auxEGB_filter1_fc = 0;
	enum class auxEGB_filter1_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEGB_filter1_fcEnum::SWITCH_OFF, auxEGB_filter1_fc)) etc... 

	int auxEGB_filter2_fc = 0;
	enum class auxEGB_filter2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEGB_filter2_fcEnum::SWITCH_OFF, auxEGB_filter2_fc)) etc... 

	int filterModeIndex = 0;
	enum class filterModeIndexEnum { series,parallel };	// to compare: if(compareEnumToInt(filterModeIndexEnum::series, filterModeIndex)) etc... 

	int enableDelayFX = 0;
	enum class enableDelayFXEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(enableDelayFXEnum::SWITCH_OFF, enableDelayFX)) etc... 

	int lfo1_ampEGTrig = 0;
	enum class lfo1_ampEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo1_ampEGTrigEnum::SWITCH_OFF, lfo1_ampEGTrig)) etc... 

	int lfo2_ampEGTrig = 0;
	enum class lfo2_ampEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo2_ampEGTrigEnum::SWITCH_OFF, lfo2_ampEGTrig)) etc... 

	int auxEG_ampEGTrig = 0;
	enum class auxEG_ampEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEG_ampEGTrigEnum::SWITCH_OFF, auxEG_ampEGTrig)) etc... 

	int auxEGB_ampEGTrig = 0;
	enum class auxEGB_ampEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEGB_ampEGTrigEnum::SWITCH_OFF, auxEGB_ampEGTrig)) etc... 

	int lfo1_dcaPan = 0;
	enum class lfo1_dcaPanEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo1_dcaPanEnum::SWITCH_OFF, lfo1_dcaPan)) etc... 

	int lfo2_dcaPan = 0;
	enum class lfo2_dcaPanEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo2_dcaPanEnum::SWITCH_OFF, lfo2_dcaPan)) etc... 

	int auxEG_dcaPan = 0;
	enum class auxEG_dcaPanEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEG_dcaPanEnum::SWITCH_OFF, auxEG_dcaPan)) etc... 

	int auxEGB_dcaPan = 0;
	enum class auxEGB_dcaPanEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEGB_dcaPanEnum::SWITCH_OFF, auxEGB_dcaPan)) etc... 

	int filterEG_lfo2_fc = 0;
	enum class filterEG_lfo2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(filterEG_lfo2_fcEnum::SWITCH_OFF, filterEG_lfo2_fc)) etc... 

	int filterEG_osc123_fc = 0;
	enum class filterEG_osc123_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(filterEG_osc123_fcEnum::SWITCH_OFF, filterEG_osc123_fc)) etc... 

	int filterEG_osc04_fc = 0;
	enum class filterEG_osc04_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(filterEG_osc04_fcEnum::SWITCH_OFF, filterEG_osc04_fc)) etc... 

	int filterEG_osc123_Mod = 0;
	enum class filterEG_osc123_ModEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(filterEG_osc123_ModEnum::SWITCH_OFF, filterEG_osc123_Mod)) etc... 

	int filterEG_osc04_Mod = 0;
	enum class filterEG_osc04_ModEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(filterEG_osc04_ModEnum::SWITCH_OFF, filterEG_osc04_Mod)) etc... 

	int filterEG_filter1_fc = 0;
	enum class filterEG_filter1_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(filterEG_filter1_fcEnum::SWITCH_OFF, filterEG_filter1_fc)) etc... 

	int filterEG_filter2_fc = 0;
	enum class filterEG_filter2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(filterEG_filter2_fcEnum::SWITCH_OFF, filterEG_filter2_fc)) etc... 

	int filterEG_dcaPan = 0;
	enum class filterEG_dcaPanEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(filterEG_dcaPanEnum::SWITCH_OFF, filterEG_dcaPan)) etc... 

	int filterEG_ampEGTrig = 0;
	enum class filterEG_ampEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(filterEG_ampEGTrigEnum::SWITCH_OFF, filterEG_ampEGTrig)) etc... 

	int lfo1Core = 0;
	enum class lfo1CoreEnum { default_0,user_0,user_1,user_2 };	// to compare: if(compareEnumToInt(lfo1CoreEnum::default_0, lfo1Core)) etc... 

	int lfo2Core = 0;
	enum class lfo2CoreEnum { default_0,user_0,user_1,user_2 };	// to compare: if(compareEnumToInt(lfo2CoreEnum::default_0, lfo2Core)) etc... 

	int ampEGCore = 0;
	enum class ampEGCoreEnum { default_0,user_0,user_1,user_2 };	// to compare: if(compareEnumToInt(ampEGCoreEnum::default_0, ampEGCore)) etc... 

	int filterEGCore = 0;
	enum class filterEGCoreEnum { default_0,user_0,user_1,user_2 };	// to compare: if(compareEnumToInt(filterEGCoreEnum::default_0, filterEGCore)) etc... 

	int auxEGCore = 0;
	enum class auxEGCoreEnum { default_0,user_0,user_1,user_2 };	// to compare: if(compareEnumToInt(auxEGCoreEnum::default_0, auxEGCore)) etc... 

	int filter1Core = 0;
	enum class filter1CoreEnum { default_0,user_0,user_1,user_2 };	// to compare: if(compareEnumToInt(filter1CoreEnum::default_0, filter1Core)) etc... 

	int filter2Core = 0;
	enum class filter2CoreEnum { default_0,user_0,user_1,user_2 };	// to compare: if(compareEnumToInt(filter2CoreEnum::default_0, filter2Core)) etc... 

	int osc1Core = 0;
	enum class osc1CoreEnum { default_0,user_0,user_1,user_2 };	// to compare: if(compareEnumToInt(osc1CoreEnum::default_0, osc1Core)) etc... 

	int osc2Core = 0;
	enum class osc2CoreEnum { default_0,user_0,user_1,user_2 };	// to compare: if(compareEnumToInt(osc2CoreEnum::default_0, osc2Core)) etc... 

	int osc3Core = 0;
	enum class osc3CoreEnum { default_0,user_0,user_1,user_2 };	// to compare: if(compareEnumToInt(osc3CoreEnum::default_0, osc3Core)) etc... 

	int osc4Core = 0;
	enum class osc4CoreEnum { default_0,user_0,user_1,user_2 };	// to compare: if(compareEnumToInt(osc4CoreEnum::default_0, osc4Core)) etc... 

	// --- Non-GUI-bound User Plugin Variables
	float OSC_SWITCHER = 0.f;
	float LFO_SWITCHER = 0.f;
	float EG_SWITCHER = 0.f;
	float FILTER_SWITCHER = 0.f;
	float MAIN_SWITCHER = 0.f;

	// **--0x1A7F--**
    // --- end member variables

public:
    /** static description: bundle folder name

	\return bundle folder name as a const char*
	*/
    static const char* getPluginBundleName();

    /** static description: name

	\return name as a const char*
	*/
    static const char* getPluginName();

	/** static description: short name

	\return short name as a const char*
	*/
	static const char* getShortPluginName();

	/** static description: vendor name

	\return vendor name as a const char*
	*/
	static const char* getVendorName();

	/** static description: URL

	\return URL as a const char*
	*/
	static const char* getVendorURL();

	/** static description: email

	\return email address as a const char*
	*/
	static const char* getVendorEmail();

	/** static description: Cocoa View Factory Name

	\return Cocoa View Factory Name as a const char*
	*/
	static const char* getAUCocoaViewFactoryName();

	/** static description: plugin type

	\return type (FX or Synth)
	*/
	static pluginType getPluginType();

	/** static description: VST3 GUID

	\return VST3 GUID as a const char*
	*/
	static const char* getVSTFUID();

	/** static description: 4-char code

	\return 4-char code as int
	*/
	static int32_t getFourCharCode();

	/** initalizer */
	bool initPluginDescriptors();
    
    /** Status Window Messages for hosts that can show it */
    void sendHostTextMessage(std::string messageString)
    {
        HostMessageInfo hostMessageInfo;
        hostMessageInfo.hostMessage = sendRAFXStatusWndText;
        hostMessageInfo.rafxStatusWndText.assign(messageString);
        if(pluginHostConnector)
            pluginHostConnector->sendHostMessage(hostMessageInfo);
    }

};




#endif /* defined(__pluginCore_h__) */
