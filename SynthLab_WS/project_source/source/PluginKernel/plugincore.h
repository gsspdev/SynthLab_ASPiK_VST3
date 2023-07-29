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

// **--0x7F1F--**

// --- Plugin Variables controlID Enumeration 

enum controlID {
	lfo1Core = 0,
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
	ampEGCore = 20,
	ampEGMode = 21,
	ampEG_ModKnobA = 26,
	ampEG_ModKnobB = 27,
	ampEG_ModKnobC = 28,
	ampEG_ModKnobD = 29,
	filter1Core = 50,
	filter1Algorithm = 51,
	filter1_ModKnobA = 56,
	filter1_ModKnobB = 57,
	filter1_ModKnobC = 58,
	filter1_ModKnobD = 59,
	filter1_fc = 52,
	filter1_Q = 53,
	filter1Output_dB = 55,
	enableFilter1KeyTrack = 54,
	filterEGCore = 30,
	filterEGMode = 31,
	filterEG_attackTime_mSec = 32,
	filterEG_decayTime_mSec = 33,
	filterEG_sustainLevel = 34,
	filterEG_releaseTime_mSec = 35,
	filterEG_ModKnobA = 36,
	filterEG_ModKnobB = 37,
	filterEG_ModKnobC = 38,
	filterEG_ModKnobD = 39,
	lfo2Core = 10,
	lfo2_waveform = 11,
	lfo2_mode = 12,
	lfo2_frequency_Hz = 13,
	lfo2_outputAmplitude = 14,
	lfo2_quantize = 15,
	lfo2_ModKnobA = 16,
	lfo2_ModKnobB = 17,
	lfo2_ModKnobC = 18,
	lfo2_ModKnobD = 19,
	auxEGCore = 40,
	auxEGMode = 41,
	auxEG_attackTime_mSec = 42,
	auxEG_decayTime_mSec = 43,
	auxEG_sustainLevel = 44,
	auxEG_releaseTime_mSec = 45,
	auxEG_ModKnobA = 46,
	auxEG_ModKnobB = 47,
	auxEG_ModKnobC = 48,
	auxEG_ModKnobD = 49,
	filter2Core = 60,
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
	glideTime_mSec = 74,
	ws1WaveAmp_dB = 83,
	ws1StepLenIndex = 80,
	ws1XFadeLenIndex = 81,
	ws1Pitch_semi = 84,
	ws1PitchProb_pct = 85,
	ws1ModValue = 86,
	ws1ModProb_pct = 87,
	ws1WaveIndex = 82,
	ws2StepLenIndex = 90,
	ws2XFadeLenIndex = 91,
	ws2WaveIndex = 92,
	ws2WaveAmp_dB = 93,
	ws2Pitch_semi = 94,
	ws2PitchProb_pct = 95,
	ws2ModValue = 96,
	ws2ModProb_pct = 97,
	ws3StepLenIndex = 100,
	ws3XFadeLenIndex = 101,
	ws3WaveIndex = 102,
	ws3WaveAmp_dB = 103,
	ws3Pitch_semi = 104,
	ws3PitchProb_pct = 105,
	ws3ModValue = 106,
	ws3ModProb_pct = 107,
	ws4StepLenIndex = 110,
	ws4XFadeLenIndex = 111,
	ws4WaveIndex = 112,
	ws4WaveAmp_dB = 113,
	ws4Pitch_semi = 114,
	ws4PitchProb_pct = 115,
	ws4ModValue = 116,
	ws4ModProb_pct = 117,
	ws5StepLenIndex = 120,
	ws5XFadeLenIndex = 121,
	ws5WaveIndex = 122,
	ws5WaveAmp_dB = 123,
	ws5Pitch_semi = 124,
	ws5PitchProb_pct = 125,
	ws5ModValue = 126,
	ws5ModProb_pct = 127,
	ws6StepLenIndex = 130,
	ws6XFadeLenIndex = 131,
	ws6WaveIndex = 132,
	ws6WaveAmp_dB = 133,
	ws6Pitch_semi = 134,
	ws6PitchProb_pct = 135,
	ws6ModValue = 136,
	ws6ModProb_pct = 137,
	ws7StepLenIndex = 140,
	ws7XFadeLenIndex = 141,
	ws7WaveIndex = 142,
	ws7WaveAmp_dB = 143,
	ws7Pitch_semi = 144,
	ws7PitchProb_pct = 145,
	ws7ModValue = 146,
	ws7ModProb_pct = 147,
	ws8StepLenIndex = 150,
	ws8XFadeLenIndex = 151,
	ws8WaveIndex = 152,
	ws8WaveAmp_dB = 153,
	ws8Pitch_semi = 154,
	ws8PitchProb_pct = 155,
	ws8ModValue = 156,
	ws8ModProb_pct = 157,
	timingStartIndex = 168,
	timingEndIndex = 169,
	timingLoopDir = 179,
	waveStartIndex = 188,
	waveEndIndex = 189,
	waveLoopDir = 199,
	pitchStartIndex = 208,
	pitchEndIndex = 209,
	pitchLoopDir = 219,
	stepSeqModStartIndex = 228,
	stepSeqModEndIndex = 229,
	stepSeqModLoopDir = 239,
	timing1Meter = 160,
	timing2Meter = 161,
	timing3Meter = 162,
	timing4Meter = 163,
	timing5Meter = 164,
	timing6Meter = 165,
	timing7Meter = 166,
	timing8Meter = 167,
	wave1Meter = 170,
	wave2Meter = 171,
	wave3Meter = 172,
	wave4Meter = 173,
	wave5Meter = 174,
	wave6Meter = 175,
	wave7Meter = 176,
	wave8Meter = 177,
	pitch1Meter = 180,
	pitch2Meter = 181,
	pitch3Meter = 182,
	pitch4Meter = 183,
	pitch5Meter = 184,
	pitch6Meter = 185,
	pitch7Meter = 186,
	pitch8Meter = 187,
	ssMod1Meter = 190,
	ssMod2Meter = 191,
	ssMod3Meter = 192,
	ssMod4Meter = 193,
	ssMod5Meter = 194,
	ssMod6Meter = 195,
	ssMod7Meter = 196,
	ssMod8Meter = 197,
	timeStretch = 200,
	step1Type = 88,
	step2Type = 98,
	step3Type = 108,
	step4Type = 118,
	step5Type = 128,
	step6Type = 138,
	step7Type = 148,
	step8Type = 158,
	interpolateStepSeqMod = 210,
	randomizeStepOrder = 178,
	randomizePitchOrder = 218,
	filterModeIndex = 70,
	enableDelayFX = 310,
	leftDelay_mSec = 311,
	rightDelay_mSec = 312,
	feedback_Pct = 313,
	dryLevel_dB = 314,
	wetLevel_dB = 315,
	randomizeWaveOrder = 198,
	randomizeSSModOrder = 238,
	lfo2_fo_Int = 241,
	osc_fo_Int = 242,
	osc_UniqueInt = 243,
	filterEGTrigInt = 244,
	auxEGTrigInt = 245,
	filter1_fc_Int = 246,
	filter2_fc_Int = 247,
	dcaPanInt = 248,
	ampEGTrigInt = 249,
	lfo1SourceInt = 250,
	lfo1_lfo2_fc = 251,
	lfo1_osc_fc = 252,
	lfo1_oscUnique = 253,
	lfo1_filterEGTrig = 254,
	lfo1_auxEGTrig = 255,
	lfo1_filter1_fc = 256,
	lfo1_filter2_fc = 257,
	lfo1_dcaPan = 258,
	lfo1_ampEGTrig = 259,
	lfo2SourceInt = 260,
	lfo2_lfo2_fc = 261,
	lfo2_osc_fc = 262,
	lfo2_oscUnique = 263,
	lfo2_filterEGTrig = 264,
	lfo2_auxEGTrig = 265,
	lfo2_filter1_fc = 266,
	lfo2_filter2_fc = 267,
	lfo2_dcaPan = 268,
	lfo2_ampEGTrig = 269,
	filterEGSourceInt = 270,
	filterEG_lfo2_fc = 271,
	filterEG_osc_fc = 272,
	filterEG_oscUnique = 273,
	filterEG_filterEGTrig = 274,
	filterEG_auxEGTrig = 275,
	filterEG_filter1_fc = 276,
	filterEG_filter2_fc = 277,
	filterEG_dcaPan = 278,
	filterEG_ampEGTrig = 279,
	auxEGSourceInt = 280,
	auxEG_lfo2_fc = 281,
	auxEG_osc_fc = 282,
	auxEG_oscUnique = 283,
	auxEG_filterEGTrig = 284,
	auxEG_auxEGTrig = 285,
	auxEG_filter1_fc = 286,
	auxEG_filter2_fc = 287,
	auxEG_dcaPan = 288,
	auxEG_ampEGTrig = 289,
	auxEGBiasedSourceInt = 290,
	auxEGB_lfo2_fc = 291,
	auxEGB_osc_fc = 292,
	auxEGB_filterEGTrig = 294,
	auxEGB_oscUnique = 293,
	auxEGB_auxEGTrig = 295,
	auxEGB_filter1_fc = 296,
	auxEGB_filter2_fc = 297,
	auxEGB_dcaPan = 298,
	auxEGB_ampEGTrig = 299,
	waveSeqModSourceInt = 300,
	waveSeqMod_lfo2_fc = 301,
	waveSeqMod_osc_fo = 302,
	waveSeqMod_oscUnique = 303,
	waveSeqMod_filterEGTrig = 304,
	waveSeqMod_auxEGTrig = 305,
	waveSeqMod_filter1_fc = 306,
	waveSeqMod_filter2_fc = 307,
	waveSeqMod_dcaPan = 308,
	waveSeqMod_ampEGTrig = 309,
	ampEGIntensity = 319,
	wseq1_panValue = 320,
	wseq2_panValue = 330,
	wseq3_panValue = 340,
	wseq4_panValue = 350,
	wseq5_panValue = 360,
	wseq6_panValue = 370,
	wseq7_panValue = 380,
	wseq8_panValue = 390,
	wseq1HardSync = 321,
	wseq1Morph = 322,
	wseq2HardSync = 331,
	wseq2Morph = 332,
	wseq3HardSync = 341,
	wseq3Morph = 342,
	wseq4HardSync = 351,
	wseq4Morph = 352,
	wseq5HardSync = 361,
	wseq5Morph = 362,
	wseq6HardSync = 371,
	wseq6Morph = 372,
	wseq7HardSync = 381,
	wseq7Morph = 382,
	wseq8HardSync = 391,
	wseq8Morph = 392,
	wseq1DetuneSemis = 323,
	wseq1DetuneCents = 324,
	wseq2DetuneSemis = 333,
	wseq2DetuneCents = 334,
	wseq3DetuneSemis = 343,
	wseq3DetuneCents = 344,
	wseq4DetuneSemis = 353,
	wseq4DetuneCents = 354,
	wseq5DetuneSemis = 363,
	wseq5DetuneCents = 364,
	wseq6DetuneSemis = 373,
	wseq6DetuneCents = 374,
	wseq7DetuneSemis = 383,
	wseq7DetuneCents = 384,
	wseq8DetuneSemis = 393,
	wseq8DetuneCents = 394,
	LFO_SW = 65568,
	EG_SW = 65569,
	FILTER_SW = 65570,
	MAIN_SW = 65571,
	soloWaveLane = 201,
	runStopWS = 202
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
	virtual ~PluginCore();

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
	void updateSequencerLEDs();
	
	// --- for all versions RAFX/ASPiK	
	std::unique_ptr<DynamicStringManager> dynStringManager = nullptr;

	// --- for DM ONLY
	DynamicModuleManager dynModuleManager;

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

#ifdef SYNTHLAB_KS
		// --- OSC BLOCK ---
		if (_controlID == controlID::osc1Core ||
			_controlID == controlID::osc2Core ||
			_controlID == controlID::osc3Core ||
			_controlID == controlID::osc4Core)
		{
			return SynthLab::KSO_MODULE;
		}
#elif defined SYNTHLAB_WT
		if (_controlID == controlID::osc1Core ||
			_controlID == controlID::osc2Core ||
			_controlID == controlID::osc3Core ||
			_controlID == controlID::osc4Core)
		{
			return SynthLab::KSO_MODULE;
		}
#elif defined SYNTHLAB_VA
		if (_controlID == controlID::osc1Core ||
			_controlID == controlID::osc2Core ||
			_controlID == controlID::osc3Core ||
			_controlID == controlID::osc4Core)
		{
			return SynthLab::VAO_MODULE;
		}

#elif defined SYNTHLAB_PCM
		if (_controlID == controlID::osc1Core ||
			_controlID == controlID::osc2Core ||
			_controlID == controlID::osc3Core ||
			_controlID == controlID::osc4Core)
		{
			return SynthLab::PCMO_MODULE;
		}
#elif defined SYNTHLAB_DX
		if (_controlID == controlID::osc1Core ||
			_controlID == controlID::osc2Core ||
			_controlID == controlID::osc3Core ||
			_controlID == controlID::osc4Core)
		{
			return SynthLab::FMO_MODULE;
		}

#elif defined SYNTHLAB_WS
		//if (_controlID == controlID::osc1Core ||
		//	_controlID == controlID::osc2Core ||
		//	_controlID == controlID::osc3Core ||
		//	_controlID == controlID::osc4Core)
		//{
		//	return SynthLab::WTO_MODULE;
		//}
#endif

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

#ifdef SYNTHLAB_WS
		//if (_controlID == controlID::osc1Core ||
		//	_controlID == controlID::osc2Core ||
		//	_controlID == controlID::osc3Core ||
		//	_controlID == controlID::osc4Core)
		//	return true;
#endif
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
	float glideTime_mSec = 0.f;
	double ws1WaveAmp_dB = 0.0;
	int ws1Pitch_semi = 0;
	double ws1PitchProb_pct = 0.0;
	double ws1ModValue = 0.0;
	double ws1ModProb_pct = 0.0;
	double ws2WaveAmp_dB = 0.0;
	int ws2Pitch_semi = 0;
	double ws2PitchProb_pct = 0.0;
	double ws2ModValue = 0.0;
	double ws2ModProb_pct = 0.0;
	double ws3WaveAmp_dB = 0.0;
	int ws3Pitch_semi = 0;
	double ws3PitchProb_pct = 0.0;
	double ws3ModValue = 0.0;
	double ws3ModProb_pct = 0.0;
	double ws4WaveAmp_dB = 0.0;
	int ws4Pitch_semi = 0;
	double ws4PitchProb_pct = 0.0;
	double ws4ModValue = 0.0;
	double ws4ModProb_pct = 0.0;
	double ws5WaveAmp_dB = 0.0;
	int ws5Pitch_semi = 0;
	double ws5PitchProb_pct = 0.0;
	double ws5ModValue = 0.0;
	double ws5ModProb_pct = 0.0;
	double ws6WaveAmp_dB = 0.0;
	int ws6Pitch_semi = 0;
	double ws6PitchProb_pct = 0.0;
	double ws6ModValue = 0.0;
	double ws6ModProb_pct = 0.0;
	double ws7WaveAmp_dB = 0.0;
	int ws7Pitch_semi = 0;
	double ws7PitchProb_pct = 0.0;
	double ws7ModValue = 0.0;
	double ws7ModProb_pct = 0.0;
	double ws8WaveAmp_dB = 0.0;
	int ws8Pitch_semi = 0;
	double ws8PitchProb_pct = 0.0;
	double ws8ModValue = 0.0;
	double ws8ModProb_pct = 0.0;
	int timingStartIndex = 0;
	int timingEndIndex = 0;
	int waveStartIndex = 0;
	int waveEndIndex = 0;
	int pitchStartIndex = 0;
	int pitchEndIndex = 0;
	int stepSeqModStartIndex = 0;
	int stepSeqModEndIndex = 0;
	double timeStretch = 0.0;
	double leftDelay_mSec = 0.0;
	double rightDelay_mSec = 0.0;
	double feedback_Pct = 0.0;
	double dryLevel_dB = 0.0;
	double wetLevel_dB = 0.0;
	double lfo2_fo_Int = 0.0;
	double osc_fo_Int = 0.0;
	double osc_UniqueInt = 0.0;
	double filterEGTrigInt = 0.0;
	double auxEGTrigInt = 0.0;
	double filter1_fc_Int = 0.0;
	double filter2_fc_Int = 0.0;
	double dcaPanInt = 0.0;
	double ampEGTrigInt = 0.0;
	double lfo1SourceInt = 0.0;
	double lfo2SourceInt = 0.0;
	double filterEGSourceInt = 0.0;
	double auxEGSourceInt = 0.0;
	double auxEGBiasedSourceInt = 0.0;
	double waveSeqModSourceInt = 0.0;
	double ampEGIntensity = 0.0;
	double wseq1_panValue = 0.0;
	double wseq2_panValue = 0.0;
	double wseq3_panValue = 0.0;
	double wseq4_panValue = 0.0;
	double wseq5_panValue = 0.0;
	double wseq6_panValue = 0.0;
	double wseq7_panValue = 0.0;
	double wseq8_panValue = 0.0;
	double wseq1HardSync = 0.0;
	double wseq1Morph = 0.0;
	double wseq2HardSync = 0.0;
	double wseq2Morph = 0.0;
	double wseq3HardSync = 0.0;
	double wseq3Morph = 0.0;
	double wseq4HardSync = 0.0;
	double wseq4Morph = 0.0;
	double wseq5HardSync = 0.0;
	double wseq5Morph = 0.0;
	double wseq6HardSync = 0.0;
	double wseq6Morph = 0.0;
	double wseq7HardSync = 0.0;
	double wseq7Morph = 0.0;
	double wseq8HardSync = 0.0;
	double wseq8Morph = 0.0;
	int wseq1DetuneSemis = 0;
	double wseq1DetuneCents = 0.0;
	int wseq2DetuneSemis = 0;
	double wseq2DetuneCents = 0.0;
	int wseq3DetuneSemis = 0;
	double wseq3DetuneCents = 0.0;
	int wseq4DetuneSemis = 0;
	double wseq4DetuneCents = 0.0;
	int wseq5DetuneSemis = 0;
	double wseq5DetuneCents = 0.0;
	int wseq6DetuneSemis = 0;
	double wseq6DetuneCents = 0.0;
	int wseq7DetuneSemis = 0;
	double wseq7DetuneCents = 0.0;
	int wseq8DetuneSemis = 0;
	double wseq8DetuneCents = 0.0;

	// --- Discrete Plugin Variables 
	int lfo1Core = 0;
	enum class lfo1CoreEnum { default_0,user_0,user_1,user_2 };	// to compare: if(compareEnumToInt(lfo1CoreEnum::default_0, lfo1Core)) etc... 

	int lfo1_waveform = 0;
	enum class lfo1_waveformEnum { wave_0,wave_1,wave_2,wave_3,wave_4,wave_5,wave_6,wave_7,wave_8,wave_9,wave_10,wave_11,wave_12,wave_13,wave_14,wave_15 };	// to compare: if(compareEnumToInt(lfo1_waveformEnum::wave_0, lfo1_waveform)) etc... 

	int lfo1_mode = 0;
	enum class lfo1_modeEnum { sync,one_shot,free_run };	// to compare: if(compareEnumToInt(lfo1_modeEnum::sync, lfo1_mode)) etc... 

	int ampEGCore = 0;
	enum class ampEGCoreEnum { default_0,user_0,user_1,user_2 };	// to compare: if(compareEnumToInt(ampEGCoreEnum::default_0, ampEGCore)) etc... 

	int ampEGMode = 0;
	enum class ampEGModeEnum { contour0,contour1,contour2,contour3,contour4,contour5,contour6,contour7,contour8,contour9,contour10,contour11,contour12,contour13,contour14,contour15 };	// to compare: if(compareEnumToInt(ampEGModeEnum::contour0, ampEGMode)) etc... 

	int filter1Core = 0;
	enum class filter1CoreEnum { default_0,user_0,user_1,user_2 };	// to compare: if(compareEnumToInt(filter1CoreEnum::default_0, filter1Core)) etc... 

	int filter1Algorithm = 0;
	enum class filter1AlgorithmEnum { filter0,filter1,filter2,filter3,filter4,filter5,filter6,filter7,filter8,filter9,filter10,filter11,filter12,filter13,filter14,filter15 };	// to compare: if(compareEnumToInt(filter1AlgorithmEnum::filter0, filter1Algorithm)) etc... 

	int enableFilter1KeyTrack = 0;
	enum class enableFilter1KeyTrackEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(enableFilter1KeyTrackEnum::SWITCH_OFF, enableFilter1KeyTrack)) etc... 

	int filterEGCore = 0;
	enum class filterEGCoreEnum { default_0,user_0,user_1,user_2 };	// to compare: if(compareEnumToInt(filterEGCoreEnum::default_0, filterEGCore)) etc... 

	int filterEGMode = 0;
	enum class filterEGModeEnum { contour0,contour1,contour2,contour3,contour4,contour5,contour6,contour7,contour8,contour9,contour10,contour11,contour12,contour13,contour14,contour15 };	// to compare: if(compareEnumToInt(filterEGModeEnum::contour0, filterEGMode)) etc... 

	int lfo2Core = 0;
	enum class lfo2CoreEnum { default_0,user_0,user_1,user_2 };	// to compare: if(compareEnumToInt(lfo2CoreEnum::default_0, lfo2Core)) etc... 

	int lfo2_waveform = 0;
	enum class lfo2_waveformEnum { wave_0,wave_1,wave_2,wave_3,wave_4,wave_5,wave_6,wave_7,wave_8,wave_9,wave_10,wave_11,wave_12,wave_13,wave_14,wave_15 };	// to compare: if(compareEnumToInt(lfo2_waveformEnum::wave_0, lfo2_waveform)) etc... 

	int lfo2_mode = 0;
	enum class lfo2_modeEnum { sync,one_shot,free_run };	// to compare: if(compareEnumToInt(lfo2_modeEnum::sync, lfo2_mode)) etc... 

	int auxEGCore = 0;
	enum class auxEGCoreEnum { default_0,user_0,user_1,user_2 };	// to compare: if(compareEnumToInt(auxEGCoreEnum::default_0, auxEGCore)) etc... 

	int auxEGMode = 0;
	enum class auxEGModeEnum { contour0,contour1,contour2,contour3,contour4,contour5,contour6,contour7,contour8,contour9,contour10,contour11,contour12,contour13,contour14,contour15 };	// to compare: if(compareEnumToInt(auxEGModeEnum::contour0, auxEGMode)) etc... 

	int filter2Core = 0;
	enum class filter2CoreEnum { default_0,user_0,user_1,user_2 };	// to compare: if(compareEnumToInt(filter2CoreEnum::default_0, filter2Core)) etc... 

	int filter2Algorithm = 0;
	enum class filter2AlgorithmEnum { kLPF1,kHPF1,kAPF1,kSVF_LP,kSVF_HP,kSVF_BP,kSVF_BS,kKorg35_LP,kKorg35_HP,kMoog_LP1,kMoog_LP2,kMoog_LP3,kMoog_LP4,kDiode_LP4,kBypassFilter };	// to compare: if(compareEnumToInt(filter2AlgorithmEnum::kLPF1, filter2Algorithm)) etc... 

	int enableFilter2KeyTrack = 0;
	enum class enableFilter2KeyTrackEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(enableFilter2KeyTrackEnum::SWITCH_OFF, enableFilter2KeyTrack)) etc... 

	int synthMode = 0;
	enum class synthModeEnum { Mono,Legato,Unison,UniLegato,Poly };	// to compare: if(compareEnumToInt(synthModeEnum::Mono, synthMode)) etc... 

	int ws1StepLenIndex = 0;
	enum class ws1StepLenIndexEnum { n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole };	// to compare: if(compareEnumToInt(ws1StepLenIndexEnum::n32ndTrip, ws1StepLenIndex)) etc... 

	int ws1XFadeLenIndex = 0;
	enum class ws1XFadeLenIndexEnum { n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole };	// to compare: if(compareEnumToInt(ws1XFadeLenIndexEnum::n32ndTrip, ws1XFadeLenIndex)) etc... 

	int ws1WaveIndex = 0;
	enum class ws1WaveIndexEnum { wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15,wave16,wave17,wave18,wave19,wave20,wave21,wave22,wave23,wave24,wave25,wave26,wave27,wave28,wave29,wave30,wave31,wave32,wave33,wave34,wave35,wave36,wave37,wave38,wave39,wave40,wave41,wave42,wave43,wave44,wave45,wave46,wave47,wave48,wave49,wave50,wave51,wave52,wave53,wave54,wave55,wave56,wave57,wave58,wave59,wave60,wave61,wave62,wave63 };	// to compare: if(compareEnumToInt(ws1WaveIndexEnum::wave0, ws1WaveIndex)) etc... 

	int ws2StepLenIndex = 0;
	enum class ws2StepLenIndexEnum { n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole };	// to compare: if(compareEnumToInt(ws2StepLenIndexEnum::n32ndTrip, ws2StepLenIndex)) etc... 

	int ws2XFadeLenIndex = 0;
	enum class ws2XFadeLenIndexEnum { n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole };	// to compare: if(compareEnumToInt(ws2XFadeLenIndexEnum::n32ndTrip, ws2XFadeLenIndex)) etc... 

	int ws2WaveIndex = 0;
	enum class ws2WaveIndexEnum { wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15,wave16,wave17,wave18,wave19,wave20,wave21,wave22,wave23,wave24,wave25,wave26,wave27,wave28,wave29,wave30,wave31,wave32,wave33,wave34,wave35,wave36,wave37,wave38,wave39,wave40,wave41,wave42,wave43,wave44,wave45,wave46,wave47,wave48,wave49,wave50,wave51,wave52,wave53,wave54,wave55,wave56,wave57,wave58,wave59,wave60,wave61,wave62,wave63 };	// to compare: if(compareEnumToInt(ws2WaveIndexEnum::wave0, ws2WaveIndex)) etc... 

	int ws3StepLenIndex = 0;
	enum class ws3StepLenIndexEnum { n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole };	// to compare: if(compareEnumToInt(ws3StepLenIndexEnum::n32ndTrip, ws3StepLenIndex)) etc... 

	int ws3XFadeLenIndex = 0;
	enum class ws3XFadeLenIndexEnum { n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole };	// to compare: if(compareEnumToInt(ws3XFadeLenIndexEnum::n32ndTrip, ws3XFadeLenIndex)) etc... 

	int ws3WaveIndex = 0;
	enum class ws3WaveIndexEnum { wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15,wave16,wave17,wave18,wave19,wave20,wave21,wave22,wave23,wave24,wave25,wave26,wave27,wave28,wave29,wave30,wave31,wave32,wave33,wave34,wave35,wave36,wave37,wave38,wave39,wave40,wave41,wave42,wave43,wave44,wave45,wave46,wave47,wave48,wave49,wave50,wave51,wave52,wave53,wave54,wave55,wave56,wave57,wave58,wave59,wave60,wave61,wave62,wave63 };	// to compare: if(compareEnumToInt(ws3WaveIndexEnum::wave0, ws3WaveIndex)) etc... 

	int ws4StepLenIndex = 0;
	enum class ws4StepLenIndexEnum { n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole };	// to compare: if(compareEnumToInt(ws4StepLenIndexEnum::n32ndTrip, ws4StepLenIndex)) etc... 

	int ws4XFadeLenIndex = 0;
	enum class ws4XFadeLenIndexEnum { n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole };	// to compare: if(compareEnumToInt(ws4XFadeLenIndexEnum::n32ndTrip, ws4XFadeLenIndex)) etc... 

	int ws4WaveIndex = 0;
	enum class ws4WaveIndexEnum { wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15,wave16,wave17,wave18,wave19,wave20,wave21,wave22,wave23,wave24,wave25,wave26,wave27,wave28,wave29,wave30,wave31,wave32,wave33,wave34,wave35,wave36,wave37,wave38,wave39,wave40,wave41,wave42,wave43,wave44,wave45,wave46,wave47,wave48,wave49,wave50,wave51,wave52,wave53,wave54,wave55,wave56,wave57,wave58,wave59,wave60,wave61,wave62,wave63 };	// to compare: if(compareEnumToInt(ws4WaveIndexEnum::wave0, ws4WaveIndex)) etc... 

	int ws5StepLenIndex = 0;
	enum class ws5StepLenIndexEnum { n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole };	// to compare: if(compareEnumToInt(ws5StepLenIndexEnum::n32ndTrip, ws5StepLenIndex)) etc... 

	int ws5XFadeLenIndex = 0;
	enum class ws5XFadeLenIndexEnum { n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole };	// to compare: if(compareEnumToInt(ws5XFadeLenIndexEnum::n32ndTrip, ws5XFadeLenIndex)) etc... 

	int ws5WaveIndex = 0;
	enum class ws5WaveIndexEnum { wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15,wave16,wave17,wave18,wave19,wave20,wave21,wave22,wave23,wave24,wave25,wave26,wave27,wave28,wave29,wave30,wave31,wave32,wave33,wave34,wave35,wave36,wave37,wave38,wave39,wave40,wave41,wave42,wave43,wave44,wave45,wave46,wave47,wave48,wave49,wave50,wave51,wave52,wave53,wave54,wave55,wave56,wave57,wave58,wave59,wave60,wave61,wave62,wave63 };	// to compare: if(compareEnumToInt(ws5WaveIndexEnum::wave0, ws5WaveIndex)) etc... 

	int ws6StepLenIndex = 0;
	enum class ws6StepLenIndexEnum { n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole };	// to compare: if(compareEnumToInt(ws6StepLenIndexEnum::n32ndTrip, ws6StepLenIndex)) etc... 

	int ws6XFadeLenIndex = 0;
	enum class ws6XFadeLenIndexEnum { n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole };	// to compare: if(compareEnumToInt(ws6XFadeLenIndexEnum::n32ndTrip, ws6XFadeLenIndex)) etc... 

	int ws6WaveIndex = 0;
	enum class ws6WaveIndexEnum { wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15,wave16,wave17,wave18,wave19,wave20,wave21,wave22,wave23,wave24,wave25,wave26,wave27,wave28,wave29,wave30,wave31,wave32,wave33,wave34,wave35,wave36,wave37,wave38,wave39,wave40,wave41,wave42,wave43,wave44,wave45,wave46,wave47,wave48,wave49,wave50,wave51,wave52,wave53,wave54,wave55,wave56,wave57,wave58,wave59,wave60,wave61,wave62,wave63 };	// to compare: if(compareEnumToInt(ws6WaveIndexEnum::wave0, ws6WaveIndex)) etc... 

	int ws7StepLenIndex = 0;
	enum class ws7StepLenIndexEnum { n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole };	// to compare: if(compareEnumToInt(ws7StepLenIndexEnum::n32ndTrip, ws7StepLenIndex)) etc... 

	int ws7XFadeLenIndex = 0;
	enum class ws7XFadeLenIndexEnum { n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole };	// to compare: if(compareEnumToInt(ws7XFadeLenIndexEnum::n32ndTrip, ws7XFadeLenIndex)) etc... 

	int ws7WaveIndex = 0;
	enum class ws7WaveIndexEnum { wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15,wave16,wave17,wave18,wave19,wave20,wave21,wave22,wave23,wave24,wave25,wave26,wave27,wave28,wave29,wave30,wave31,wave32,wave33,wave34,wave35,wave36,wave37,wave38,wave39,wave40,wave41,wave42,wave43,wave44,wave45,wave46,wave47,wave48,wave49,wave50,wave51,wave52,wave53,wave54,wave55,wave56,wave57,wave58,wave59,wave60,wave61,wave62,wave63 };	// to compare: if(compareEnumToInt(ws7WaveIndexEnum::wave0, ws7WaveIndex)) etc... 

	int ws8StepLenIndex = 0;
	enum class ws8StepLenIndexEnum { n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole };	// to compare: if(compareEnumToInt(ws8StepLenIndexEnum::n32ndTrip, ws8StepLenIndex)) etc... 

	int ws8XFadeLenIndex = 0;
	enum class ws8XFadeLenIndexEnum { n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole };	// to compare: if(compareEnumToInt(ws8XFadeLenIndexEnum::n32ndTrip, ws8XFadeLenIndex)) etc... 

	int ws8WaveIndex = 0;
	enum class ws8WaveIndexEnum { wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15,wave16,wave17,wave18,wave19,wave20,wave21,wave22,wave23,wave24,wave25,wave26,wave27,wave28,wave29,wave30,wave31,wave32,wave33,wave34,wave35,wave36,wave37,wave38,wave39,wave40,wave41,wave42,wave43,wave44,wave45,wave46,wave47,wave48,wave49,wave50,wave51,wave52,wave53,wave54,wave55,wave56,wave57,wave58,wave59,wave60,wave61,wave62,wave63 };	// to compare: if(compareEnumToInt(ws8WaveIndexEnum::wave0, ws8WaveIndex)) etc... 

	int timingLoopDir = 0;
	enum class timingLoopDirEnum { forward,backward,fwrd_bckwrd };	// to compare: if(compareEnumToInt(timingLoopDirEnum::forward, timingLoopDir)) etc... 

	int waveLoopDir = 0;
	enum class waveLoopDirEnum { forward,backward,fwrd_bckwrd };	// to compare: if(compareEnumToInt(waveLoopDirEnum::forward, waveLoopDir)) etc... 

	int pitchLoopDir = 0;
	enum class pitchLoopDirEnum { forward,backward,fwrd_bckwrd };	// to compare: if(compareEnumToInt(pitchLoopDirEnum::forward, pitchLoopDir)) etc... 

	int stepSeqModLoopDir = 0;
	enum class stepSeqModLoopDirEnum { forward,backward,fwrd_bckwrd };	// to compare: if(compareEnumToInt(stepSeqModLoopDirEnum::forward, stepSeqModLoopDir)) etc... 

	int step1Type = 0;
	enum class step1TypeEnum { note,rest };	// to compare: if(compareEnumToInt(step1TypeEnum::note, step1Type)) etc... 

	int step2Type = 0;
	enum class step2TypeEnum { note,rest };	// to compare: if(compareEnumToInt(step2TypeEnum::note, step2Type)) etc... 

	int step3Type = 0;
	enum class step3TypeEnum { note,rest };	// to compare: if(compareEnumToInt(step3TypeEnum::note, step3Type)) etc... 

	int step4Type = 0;
	enum class step4TypeEnum { note,rest };	// to compare: if(compareEnumToInt(step4TypeEnum::note, step4Type)) etc... 

	int step5Type = 0;
	enum class step5TypeEnum { note,rest };	// to compare: if(compareEnumToInt(step5TypeEnum::note, step5Type)) etc... 

	int step6Type = 0;
	enum class step6TypeEnum { note,rest };	// to compare: if(compareEnumToInt(step6TypeEnum::note, step6Type)) etc... 

	int step7Type = 0;
	enum class step7TypeEnum { note,rest };	// to compare: if(compareEnumToInt(step7TypeEnum::note, step7Type)) etc... 

	int step8Type = 0;
	enum class step8TypeEnum { note,rest };	// to compare: if(compareEnumToInt(step8TypeEnum::note, step8Type)) etc... 

	int interpolateStepSeqMod = 0;
	enum class interpolateStepSeqModEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(interpolateStepSeqModEnum::SWITCH_OFF, interpolateStepSeqMod)) etc... 

	int randomizeStepOrder = 0;
	enum class randomizeStepOrderEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(randomizeStepOrderEnum::SWITCH_OFF, randomizeStepOrder)) etc... 

	int randomizePitchOrder = 0;
	enum class randomizePitchOrderEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(randomizePitchOrderEnum::SWITCH_OFF, randomizePitchOrder)) etc... 

	int filterModeIndex = 0;
	enum class filterModeIndexEnum { series,parallel };	// to compare: if(compareEnumToInt(filterModeIndexEnum::series, filterModeIndex)) etc... 

	int enableDelayFX = 0;
	enum class enableDelayFXEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(enableDelayFXEnum::SWITCH_OFF, enableDelayFX)) etc... 

	int randomizeWaveOrder = 0;
	enum class randomizeWaveOrderEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(randomizeWaveOrderEnum::SWITCH_OFF, randomizeWaveOrder)) etc... 

	int randomizeSSModOrder = 0;
	enum class randomizeSSModOrderEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(randomizeSSModOrderEnum::SWITCH_OFF, randomizeSSModOrder)) etc... 

	int lfo1_lfo2_fc = 0;
	enum class lfo1_lfo2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo1_lfo2_fcEnum::SWITCH_OFF, lfo1_lfo2_fc)) etc... 

	int lfo1_osc_fc = 0;
	enum class lfo1_osc_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo1_osc_fcEnum::SWITCH_OFF, lfo1_osc_fc)) etc... 

	int lfo1_oscUnique = 0;
	enum class lfo1_oscUniqueEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo1_oscUniqueEnum::SWITCH_OFF, lfo1_oscUnique)) etc... 

	int lfo1_filterEGTrig = 0;
	enum class lfo1_filterEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo1_filterEGTrigEnum::SWITCH_OFF, lfo1_filterEGTrig)) etc... 

	int lfo1_auxEGTrig = 0;
	enum class lfo1_auxEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo1_auxEGTrigEnum::SWITCH_OFF, lfo1_auxEGTrig)) etc... 

	int lfo1_filter1_fc = 0;
	enum class lfo1_filter1_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo1_filter1_fcEnum::SWITCH_OFF, lfo1_filter1_fc)) etc... 

	int lfo1_filter2_fc = 0;
	enum class lfo1_filter2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo1_filter2_fcEnum::SWITCH_OFF, lfo1_filter2_fc)) etc... 

	int lfo1_dcaPan = 0;
	enum class lfo1_dcaPanEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo1_dcaPanEnum::SWITCH_OFF, lfo1_dcaPan)) etc... 

	int lfo1_ampEGTrig = 0;
	enum class lfo1_ampEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo1_ampEGTrigEnum::SWITCH_OFF, lfo1_ampEGTrig)) etc... 

	int lfo2_lfo2_fc = 0;
	enum class lfo2_lfo2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo2_lfo2_fcEnum::SWITCH_OFF, lfo2_lfo2_fc)) etc... 

	int lfo2_osc_fc = 0;
	enum class lfo2_osc_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo2_osc_fcEnum::SWITCH_OFF, lfo2_osc_fc)) etc... 

	int lfo2_oscUnique = 0;
	enum class lfo2_oscUniqueEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo2_oscUniqueEnum::SWITCH_OFF, lfo2_oscUnique)) etc... 

	int lfo2_filterEGTrig = 0;
	enum class lfo2_filterEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo2_filterEGTrigEnum::SWITCH_OFF, lfo2_filterEGTrig)) etc... 

	int lfo2_auxEGTrig = 0;
	enum class lfo2_auxEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo2_auxEGTrigEnum::SWITCH_OFF, lfo2_auxEGTrig)) etc... 

	int lfo2_filter1_fc = 0;
	enum class lfo2_filter1_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo2_filter1_fcEnum::SWITCH_OFF, lfo2_filter1_fc)) etc... 

	int lfo2_filter2_fc = 0;
	enum class lfo2_filter2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo2_filter2_fcEnum::SWITCH_OFF, lfo2_filter2_fc)) etc... 

	int lfo2_dcaPan = 0;
	enum class lfo2_dcaPanEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo2_dcaPanEnum::SWITCH_OFF, lfo2_dcaPan)) etc... 

	int lfo2_ampEGTrig = 0;
	enum class lfo2_ampEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(lfo2_ampEGTrigEnum::SWITCH_OFF, lfo2_ampEGTrig)) etc... 

	int filterEG_lfo2_fc = 0;
	enum class filterEG_lfo2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(filterEG_lfo2_fcEnum::SWITCH_OFF, filterEG_lfo2_fc)) etc... 

	int filterEG_osc_fc = 0;
	enum class filterEG_osc_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(filterEG_osc_fcEnum::SWITCH_OFF, filterEG_osc_fc)) etc... 

	int filterEG_oscUnique = 0;
	enum class filterEG_oscUniqueEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(filterEG_oscUniqueEnum::SWITCH_OFF, filterEG_oscUnique)) etc... 

	int filterEG_filterEGTrig = 0;
	enum class filterEG_filterEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(filterEG_filterEGTrigEnum::SWITCH_OFF, filterEG_filterEGTrig)) etc... 

	int filterEG_auxEGTrig = 0;
	enum class filterEG_auxEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(filterEG_auxEGTrigEnum::SWITCH_OFF, filterEG_auxEGTrig)) etc... 

	int filterEG_filter1_fc = 0;
	enum class filterEG_filter1_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(filterEG_filter1_fcEnum::SWITCH_OFF, filterEG_filter1_fc)) etc... 

	int filterEG_filter2_fc = 0;
	enum class filterEG_filter2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(filterEG_filter2_fcEnum::SWITCH_OFF, filterEG_filter2_fc)) etc... 

	int filterEG_dcaPan = 0;
	enum class filterEG_dcaPanEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(filterEG_dcaPanEnum::SWITCH_OFF, filterEG_dcaPan)) etc... 

	int filterEG_ampEGTrig = 0;
	enum class filterEG_ampEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(filterEG_ampEGTrigEnum::SWITCH_OFF, filterEG_ampEGTrig)) etc... 

	int auxEG_lfo2_fc = 0;
	enum class auxEG_lfo2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEG_lfo2_fcEnum::SWITCH_OFF, auxEG_lfo2_fc)) etc... 

	int auxEG_osc_fc = 0;
	enum class auxEG_osc_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEG_osc_fcEnum::SWITCH_OFF, auxEG_osc_fc)) etc... 

	int auxEG_oscUnique = 0;
	enum class auxEG_oscUniqueEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEG_oscUniqueEnum::SWITCH_OFF, auxEG_oscUnique)) etc... 

	int auxEG_filterEGTrig = 0;
	enum class auxEG_filterEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEG_filterEGTrigEnum::SWITCH_OFF, auxEG_filterEGTrig)) etc... 

	int auxEG_auxEGTrig = 0;
	enum class auxEG_auxEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEG_auxEGTrigEnum::SWITCH_OFF, auxEG_auxEGTrig)) etc... 

	int auxEG_filter1_fc = 0;
	enum class auxEG_filter1_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEG_filter1_fcEnum::SWITCH_OFF, auxEG_filter1_fc)) etc... 

	int auxEG_filter2_fc = 0;
	enum class auxEG_filter2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEG_filter2_fcEnum::SWITCH_OFF, auxEG_filter2_fc)) etc... 

	int auxEG_dcaPan = 0;
	enum class auxEG_dcaPanEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEG_dcaPanEnum::SWITCH_OFF, auxEG_dcaPan)) etc... 

	int auxEG_ampEGTrig = 0;
	enum class auxEG_ampEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEG_ampEGTrigEnum::SWITCH_OFF, auxEG_ampEGTrig)) etc... 

	int auxEGB_lfo2_fc = 0;
	enum class auxEGB_lfo2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEGB_lfo2_fcEnum::SWITCH_OFF, auxEGB_lfo2_fc)) etc... 

	int auxEGB_osc_fc = 0;
	enum class auxEGB_osc_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEGB_osc_fcEnum::SWITCH_OFF, auxEGB_osc_fc)) etc... 

	int auxEGB_filterEGTrig = 0;
	enum class auxEGB_filterEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEGB_filterEGTrigEnum::SWITCH_OFF, auxEGB_filterEGTrig)) etc... 

	int auxEGB_oscUnique = 0;
	enum class auxEGB_oscUniqueEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEGB_oscUniqueEnum::SWITCH_OFF, auxEGB_oscUnique)) etc... 

	int auxEGB_auxEGTrig = 0;
	enum class auxEGB_auxEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEGB_auxEGTrigEnum::SWITCH_OFF, auxEGB_auxEGTrig)) etc... 

	int auxEGB_filter1_fc = 0;
	enum class auxEGB_filter1_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEGB_filter1_fcEnum::SWITCH_OFF, auxEGB_filter1_fc)) etc... 

	int auxEGB_filter2_fc = 0;
	enum class auxEGB_filter2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEGB_filter2_fcEnum::SWITCH_OFF, auxEGB_filter2_fc)) etc... 

	int auxEGB_dcaPan = 0;
	enum class auxEGB_dcaPanEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEGB_dcaPanEnum::SWITCH_OFF, auxEGB_dcaPan)) etc... 

	int auxEGB_ampEGTrig = 0;
	enum class auxEGB_ampEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(auxEGB_ampEGTrigEnum::SWITCH_OFF, auxEGB_ampEGTrig)) etc... 

	int waveSeqMod_lfo2_fc = 0;
	enum class waveSeqMod_lfo2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(waveSeqMod_lfo2_fcEnum::SWITCH_OFF, waveSeqMod_lfo2_fc)) etc... 

	int waveSeqMod_osc_fo = 0;
	enum class waveSeqMod_osc_foEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(waveSeqMod_osc_foEnum::SWITCH_OFF, waveSeqMod_osc_fo)) etc... 

	int waveSeqMod_oscUnique = 0;
	enum class waveSeqMod_oscUniqueEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(waveSeqMod_oscUniqueEnum::SWITCH_OFF, waveSeqMod_oscUnique)) etc... 

	int waveSeqMod_filterEGTrig = 0;
	enum class waveSeqMod_filterEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(waveSeqMod_filterEGTrigEnum::SWITCH_OFF, waveSeqMod_filterEGTrig)) etc... 

	int waveSeqMod_auxEGTrig = 0;
	enum class waveSeqMod_auxEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(waveSeqMod_auxEGTrigEnum::SWITCH_OFF, waveSeqMod_auxEGTrig)) etc... 

	int waveSeqMod_filter1_fc = 0;
	enum class waveSeqMod_filter1_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(waveSeqMod_filter1_fcEnum::SWITCH_OFF, waveSeqMod_filter1_fc)) etc... 

	int waveSeqMod_filter2_fc = 0;
	enum class waveSeqMod_filter2_fcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(waveSeqMod_filter2_fcEnum::SWITCH_OFF, waveSeqMod_filter2_fc)) etc... 

	int waveSeqMod_dcaPan = 0;
	enum class waveSeqMod_dcaPanEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(waveSeqMod_dcaPanEnum::SWITCH_OFF, waveSeqMod_dcaPan)) etc... 

	int waveSeqMod_ampEGTrig = 0;
	enum class waveSeqMod_ampEGTrigEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(waveSeqMod_ampEGTrigEnum::SWITCH_OFF, waveSeqMod_ampEGTrig)) etc... 

	int soloWaveLane = 0;
	enum class soloWaveLaneEnum { OFF,Wave_WS1,Wave_WS2,Wave_WS3,Wave_WS4,Wave_WS5,Wave_WS6,Wave_WS7,Wave_WS8 };	// to compare: if(compareEnumToInt(soloWaveLaneEnum::OFF, soloWaveLane)) etc... 

	int runStopWS = 0;
	enum class runStopWSEnum { RUN,PAUSE };	// to compare: if(compareEnumToInt(runStopWSEnum::RUN, runStopWS)) etc... 

	// --- Meter Plugin Variables
	float timing1Meter = 0.f;
	float timing2Meter = 0.f;
	float timing3Meter = 0.f;
	float timing4Meter = 0.f;
	float timing5Meter = 0.f;
	float timing6Meter = 0.f;
	float timing7Meter = 0.f;
	float timing8Meter = 0.f;
	float wave1Meter = 0.f;
	float wave2Meter = 0.f;
	float wave3Meter = 0.f;
	float wave4Meter = 0.f;
	float wave5Meter = 0.f;
	float wave6Meter = 0.f;
	float wave7Meter = 0.f;
	float wave8Meter = 0.f;
	float pitch1Meter = 0.f;
	float pitch2Meter = 0.f;
	float pitch3Meter = 0.f;
	float pitch4Meter = 0.f;
	float pitch5Meter = 0.f;
	float pitch6Meter = 0.f;
	float pitch7Meter = 0.f;
	float pitch8Meter = 0.f;
	float ssMod1Meter = 0.f;
	float ssMod2Meter = 0.f;
	float ssMod3Meter = 0.f;
	float ssMod4Meter = 0.f;
	float ssMod5Meter = 0.f;
	float ssMod6Meter = 0.f;
	float ssMod7Meter = 0.f;
	float ssMod8Meter = 0.f;

	// --- Non-GUI-bound User Plugin Variables
	float LFO_SW = 0.f;
	float EG_SW = 0.f;
	float FILTER_SW = 0.f;
	float MAIN_SW = 0.f;

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
