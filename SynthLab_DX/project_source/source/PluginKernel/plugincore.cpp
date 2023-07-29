// -----------------------------------------------------------------------------
//    ASPiK Plugin Kernel File:  plugincore.cpp
//
/**
    \file   plugincore.cpp
    \author Will Pirkle
    \date   17-September-2018
    \brief  Implementation file for PluginCore object
    		- http://www.aspikplugins.com
    		- http://www.willpirkle.com
*/
// -----------------------------------------------------------------------------
#include "plugincore.h"
#include "plugindescription.h"
#pragma warning(disable: 4996)	

/**
\brief PluginCore constructor is launching pad for object initialization

Operations:
- initialize the plugin description (strings, codes, numbers, see initPluginDescriptors())
- setup the plugin's audio I/O channel support
- create the PluginParameter objects that represent the plugin parameters (see FX book if needed)
- create the presets
*/
PluginCore::PluginCore()
{
    // --- describe the plugin; call the helper to init the static parts you setup in plugindescription.h
    initPluginDescriptors();

    // --- default I/O combinations
	// --- for FX plugins
	if (getPluginType() == kFXPlugin)
	{
		addSupportedIOCombination({ kCFMono, kCFMono });
		addSupportedIOCombination({ kCFMono, kCFStereo });
		addSupportedIOCombination({ kCFStereo, kCFStereo });
	}
	else // --- synth plugins have no input, only output
	{
		addSupportedIOCombination({ kCFNone, kCFMono });
		addSupportedIOCombination({ kCFNone, kCFStereo });
	}

	// --- for sidechaining, we support mono and stereo inputs; auxOutputs reserved for future use
	addSupportedAuxIOCombination({ kCFMono, kCFNone });
	addSupportedAuxIOCombination({ kCFStereo, kCFNone });

	// --- create the parameters
    initPluginParameters();

    // --- create the presets
    initPluginPresets();

	// --- setup dynamic module types
	dynModuleManager.addLoadableModule(SynthLab::LFO_MODULE);
	dynModuleManager.addLoadableModule(SynthLab::EG_MODULE);
	dynModuleManager.addLoadableModule(SynthLab::DCA_MODULE);
	dynModuleManager.addLoadableModule(SynthLab::FILTER_MODULE);

	// --- permittable OSC modules
#ifdef SYNTHLAB_WT
	dynModuleManager.addLoadableModule(SynthLab::WTO_MODULE);
#endif
#ifdef SYNTHLAB_VA
	dynModuleManager.addLoadableModule(SynthLab::VAO_MODULE);
#endif
#ifdef SYNTHLAB_PCM
	dynModuleManager.addLoadableModule(SynthLab::PCMO_MODULE);
#endif
#ifdef SYNTHLAB_KS
	dynModuleManager.addLoadableModule(SynthLab::KSO_MODULE);
#endif
#ifdef SYNTHLAB_DX
	dynModuleManager.addLoadableModule(SynthLab::FMO_MODULE);
#endif

}

/**
\brief create all of your plugin parameters here

\return true if parameters were created, false if they already existed
*/
bool PluginCore::initPluginParameters()
{
	if (pluginParameterMap.size() > 0)
		return false;

    // --- Add your plugin parameter instantiation code bewtween these hex codes
	// **--0xDEA7--**


	// --- Declaration of Plugin Parameter Objects 
	PluginParameter* piParam = nullptr;

	// --- discrete control: LFO1 Core
	piParam = new PluginParameter(controlID::lfo1Core, "LFO1 Core", "default 0,user 0,user 1,user 2", "default 0");
	piParam->setBoundVariable(&lfo1Core, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: LFO1 Wave
	piParam = new PluginParameter(controlID::lfo1_waveform, "LFO1 Wave", "wave 0,wave 1,wave 2,wave 3,wave 4,wave 5,wave 6,wave 7,wave 8,wave 9,wave 10,wave 11,wave 12,wave 13,wave 14,wave 15", "wave 0");
	piParam->setBoundVariable(&lfo1_waveform, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: LFO1 Mode
	piParam = new PluginParameter(controlID::lfo1_mode, "LFO1 Mode", "sync,one shot,free run", "sync");
	piParam->setBoundVariable(&lfo1_mode, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: LFO1 Rate
	piParam = new PluginParameter(controlID::lfo1_frequency_Hz, "LFO1 Rate", "Hz", controlVariableType::kDouble, 0.020000, 20.000000, 0.500000, taper::kVoltOctaveTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo1_frequency_Hz, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO1 Output
	piParam = new PluginParameter(controlID::lfo1_outputAmplitude, "LFO1 Output", "", controlVariableType::kDouble, 0.000000, 1.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo1_outputAmplitude, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO1 A
	piParam = new PluginParameter(controlID::lfo1_ModKnobA, "LFO1 A", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo1_ModKnobA, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO1 B
	piParam = new PluginParameter(controlID::lfo1_ModKnobB, "LFO1 B", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo1_ModKnobB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO1 C
	piParam = new PluginParameter(controlID::lfo1_ModKnobC, "LFO1 C", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo1_ModKnobC, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO1 D
	piParam = new PluginParameter(controlID::lfo1_ModKnobD, "LFO1 D", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo1_ModKnobD, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO1 Step
	piParam = new PluginParameter(controlID::lfo1_quantize, "LFO1 Step", "", controlVariableType::kInt, 0.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo1_quantize, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: AmpEG Att
	piParam = new PluginParameter(controlID::ampEG_attackTime_mSec, "AmpEG Att", "mSec", controlVariableType::kDouble, 0.100000, 1000.000000, 25.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ampEG_attackTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: AmpEG Dcy
	piParam = new PluginParameter(controlID::ampEG_decayTime_mSec, "AmpEG Dcy", "mSec", controlVariableType::kDouble, 0.000000, 5000.000000, 300.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ampEG_decayTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: AmpEG Sus
	piParam = new PluginParameter(controlID::ampEG_sustainLevel, "AmpEG Sus", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.707000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ampEG_sustainLevel, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: AmpEG Rel
	piParam = new PluginParameter(controlID::ampEG_releaseTime_mSec, "AmpEG Rel", "mSec", controlVariableType::kDouble, 0.000000, 10000.000000, 1000.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ampEG_releaseTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: AmpEG Core
	piParam = new PluginParameter(controlID::ampEGCore, "AmpEG Core", "default 0,user 0,user 1,user 2", "user 0");
	piParam->setBoundVariable(&ampEGCore, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: AmpEG Mode
	piParam = new PluginParameter(controlID::ampEGMode, "AmpEG Mode", "contour0,contour1,contour2,contour3,contour4,contour5,contour6,contour7,contour8,contour9,contour10,contour11,contour12,contour13,contour14,contour15", "contour0");
	piParam->setBoundVariable(&ampEGMode, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: AmpEG A
	piParam = new PluginParameter(controlID::ampEG_ModKnobA, "AmpEG A", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ampEG_ModKnobA, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: AmpEG B
	piParam = new PluginParameter(controlID::ampEG_ModKnobB, "AmpEG B", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ampEG_ModKnobB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: AmpEG C
	piParam = new PluginParameter(controlID::ampEG_ModKnobC, "AmpEG C", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ampEG_ModKnobC, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: AmpEG D
	piParam = new PluginParameter(controlID::ampEG_ModKnobD, "AmpEG D", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ampEG_ModKnobD, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: Filter1 Core
	piParam = new PluginParameter(controlID::filter1Core, "Filter1 Core", "default 0,user 0,user 1,user 2", "user 0");
	piParam->setBoundVariable(&filter1Core, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Filter1 Type
	piParam = new PluginParameter(controlID::filter1Algorithm, "Filter1 Type", "filter0,filter1,filter2,filter3,filter4,filter5,filter6,filter7,filter8,filter9,filter10,filter11,filter12,filter13,filter14,filter15", "filter0");
	piParam->setBoundVariable(&filter1Algorithm, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: Filter1 A
	piParam = new PluginParameter(controlID::filter1_ModKnobA, "Filter1 A", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filter1_ModKnobA, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Filter1 B
	piParam = new PluginParameter(controlID::filter1_ModKnobB, "Filter1 B", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filter1_ModKnobB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Filter1 C
	piParam = new PluginParameter(controlID::filter1_ModKnobC, "Filter1 C", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filter1_ModKnobC, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Filter1 D
	piParam = new PluginParameter(controlID::filter1_ModKnobD, "Filter1 D", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filter1_ModKnobD, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Filter1 fc
	piParam = new PluginParameter(controlID::filter1_fc, "Filter1 fc", "Hz", controlVariableType::kDouble, 20.000000, 20480.000000, 1000.000000, taper::kVoltOctaveTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&filter1_fc, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Filter1 Q
	piParam = new PluginParameter(controlID::filter1_Q, "Filter1 Q", "", controlVariableType::kDouble, 1.000000, 10.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&filter1_Q, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Filter1 Out
	piParam = new PluginParameter(controlID::filter1Output_dB, "Filter1 Out", "dB", controlVariableType::kDouble, -60.000000, 20.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&filter1Output_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: Filter1 Key Trk
	piParam = new PluginParameter(controlID::enableFilter1KeyTrack, "Filter1 Key Trk", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&enableFilter1KeyTrack, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: FilterEG Core
	piParam = new PluginParameter(controlID::filterEGCore, "FilterEG Core", "default 0,user 0,user 1,user 2", "user 0");
	piParam->setBoundVariable(&filterEGCore, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: FilterEG Mode
	piParam = new PluginParameter(controlID::filterEGMode, "FilterEG Mode", "contour0,contour1,contour2,contour3,contour4,contour5,contour6,contour7,contour8,contour9,contour10,contour11,contour12,contour13,contour14,contour15", "contour0");
	piParam->setBoundVariable(&filterEGMode, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: FilterEG Att
	piParam = new PluginParameter(controlID::filterEG_attackTime_mSec, "FilterEG Att", "mSec", controlVariableType::kDouble, 0.100000, 1000.000000, 25.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filterEG_attackTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FilterEG Dcy
	piParam = new PluginParameter(controlID::filterEG_decayTime_mSec, "FilterEG Dcy", "mSec", controlVariableType::kDouble, 0.000000, 5000.000000, 300.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filterEG_decayTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FilterEG Sus
	piParam = new PluginParameter(controlID::filterEG_sustainLevel, "FilterEG Sus", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.707000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filterEG_sustainLevel, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FilterEG Rel
	piParam = new PluginParameter(controlID::filterEG_releaseTime_mSec, "FilterEG Rel", "mSec", controlVariableType::kDouble, 0.000000, 10000.000000, 1000.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filterEG_releaseTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FilterEG A
	piParam = new PluginParameter(controlID::filterEG_ModKnobA, "FilterEG A", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filterEG_ModKnobA, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FilterEG B
	piParam = new PluginParameter(controlID::filterEG_ModKnobB, "FilterEG B", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filterEG_ModKnobB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FilterEG C
	piParam = new PluginParameter(controlID::filterEG_ModKnobC, "FilterEG C", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filterEG_ModKnobC, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FilterEG D
	piParam = new PluginParameter(controlID::filterEG_ModKnobD, "FilterEG D", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filterEG_ModKnobD, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: LFO2 Core
	piParam = new PluginParameter(controlID::lfo2Core, "LFO2 Core", "default 0,user 0,user 1,user 2", "user 0");
	piParam->setBoundVariable(&lfo2Core, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: LFO2 Wave
	piParam = new PluginParameter(controlID::lfo2_waveform, "LFO2 Wave", "wave 0,wave 1,wave 2,wave 3,wave 4,wave 5,wave 6,wave 7,wave 8,wave 9,wave 10,wave 11,wave 12,wave 13,wave 14,wave 15", "wave 0");
	piParam->setBoundVariable(&lfo2_waveform, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: LFO2 Mode
	piParam = new PluginParameter(controlID::lfo2_mode, "LFO2 Mode", "sync,one shot,free run", "sync");
	piParam->setBoundVariable(&lfo2_mode, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: LFO2 Rate
	piParam = new PluginParameter(controlID::lfo2_frequency_Hz, "LFO2 Rate", "Hz", controlVariableType::kDouble, 0.020000, 20.000000, 0.500000, taper::kVoltOctaveTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo2_frequency_Hz, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO2 Output
	piParam = new PluginParameter(controlID::lfo2_outputAmplitude, "LFO2 Output", "", controlVariableType::kDouble, 0.000000, 1.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo2_outputAmplitude, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO2 Step
	piParam = new PluginParameter(controlID::lfo2_quantize, "LFO2 Step", "", controlVariableType::kInt, 0.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo2_quantize, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: LFO2 A
	piParam = new PluginParameter(controlID::lfo2_ModKnobA, "LFO2 A", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo2_ModKnobA, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO2 B
	piParam = new PluginParameter(controlID::lfo2_ModKnobB, "LFO2 B", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo2_ModKnobB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO2 C
	piParam = new PluginParameter(controlID::lfo2_ModKnobC, "LFO2 C", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo2_ModKnobC, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO2 D
	piParam = new PluginParameter(controlID::lfo2_ModKnobD, "LFO2 D", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo2_ModKnobD, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: AuxEG
	piParam = new PluginParameter(controlID::auxEGCore, "AuxEG", "default 0,user 0,user 1,user 2", "user 0");
	piParam->setBoundVariable(&auxEGCore, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: AuxEG Mode
	piParam = new PluginParameter(controlID::auxEGMode, "AuxEG Mode", "contour0,contour1,contour2,contour3,contour4,contour5,contour6,contour7,contour8,contour9,contour10,contour11,contour12,contour13,contour14,contour15", "contour0");
	piParam->setBoundVariable(&auxEGMode, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: AuxEG Att
	piParam = new PluginParameter(controlID::auxEG_attackTime_mSec, "AuxEG Att", "mSec", controlVariableType::kDouble, 0.100000, 10000.000000, 25.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&auxEG_attackTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: auxEG Dcy
	piParam = new PluginParameter(controlID::auxEG_decayTime_mSec, "auxEG Dcy", "mSec", controlVariableType::kDouble, 0.000000, 10000.000000, 300.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&auxEG_decayTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: AuxEG Sus
	piParam = new PluginParameter(controlID::auxEG_sustainLevel, "AuxEG Sus", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.707000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&auxEG_sustainLevel, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: AuxEG Rel
	piParam = new PluginParameter(controlID::auxEG_releaseTime_mSec, "AuxEG Rel", "mSec", controlVariableType::kDouble, 0.000000, 10000.000000, 1000.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&auxEG_releaseTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: AuxEG A
	piParam = new PluginParameter(controlID::auxEG_ModKnobA, "AuxEG A", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&auxEG_ModKnobA, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: AuxEG B
	piParam = new PluginParameter(controlID::auxEG_ModKnobB, "AuxEG B", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&auxEG_ModKnobB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: AuxEG C
	piParam = new PluginParameter(controlID::auxEG_ModKnobC, "AuxEG C", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&auxEG_ModKnobC, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: AuxEG D
	piParam = new PluginParameter(controlID::auxEG_ModKnobD, "AuxEG D", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&auxEG_ModKnobD, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: Filter2 Core
	piParam = new PluginParameter(controlID::filter2Core, "Filter2 Core", "default 0,user 0,user 1,user 2", "user 0");
	piParam->setBoundVariable(&filter2Core, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Filter2 Type
	piParam = new PluginParameter(controlID::filter2Algorithm, "Filter2 Type", "filter0,filter1,filter2,filter3,filter4,filter5,filter6,filter7,filter8,filter9,filter10,filter11,filter12,filter13,filter14,filter15", "filter0");
	piParam->setBoundVariable(&filter2Algorithm, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: Filter2 fc
	piParam = new PluginParameter(controlID::filter2_fc, "Filter2 fc", "Hz", controlVariableType::kDouble, 20.000000, 20480.000000, 1000.000000, taper::kVoltOctaveTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&filter2_fc, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Filter2 Q
	piParam = new PluginParameter(controlID::filter2_Q, "Filter2 Q", "", controlVariableType::kDouble, 1.000000, 10.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&filter2_Q, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: Filter2 Key Trk
	piParam = new PluginParameter(controlID::enableFilter2KeyTrack, "Filter2 Key Trk", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&enableFilter2KeyTrack, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: Filter2 Out
	piParam = new PluginParameter(controlID::filter2Output_dB, "Filter2 Out", "dB", controlVariableType::kDouble, -60.000000, 20.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&filter2Output_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Filter2 A
	piParam = new PluginParameter(controlID::filter2_ModKnobA, "Filter2 A", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filter2_ModKnobA, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Filter2 B
	piParam = new PluginParameter(controlID::filter2_ModKnobB, "Filter2 B", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filter2_ModKnobB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Filter2 C
	piParam = new PluginParameter(controlID::filter2_ModKnobC, "Filter2 C", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filter2_ModKnobC, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Filter2 D
	piParam = new PluginParameter(controlID::filter2_ModKnobD, "Filter2 D", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filter2_ModKnobD, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Output
	piParam = new PluginParameter(controlID::globalVolume_dB, "Output", "dB", controlVariableType::kDouble, -60.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&globalVolume_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Global Tuning
	piParam = new PluginParameter(controlID::globalTuning, "Global Tuning", "semi", controlVariableType::kDouble, -12.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&globalTuning, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Unison Detune
	piParam = new PluginParameter(controlID::globalUnisonDetune_Cents, "Unison Detune", "cents", controlVariableType::kDouble, 0.000000, 25.000000, 5.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&globalUnisonDetune_Cents, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: PBend Range
	piParam = new PluginParameter(controlID::globalPitchBendSens, "PBend Range", "semi", controlVariableType::kDouble, 0.000000, 48.000000, 12.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&globalPitchBendSens, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: Mode
	piParam = new PluginParameter(controlID::synthMode, "Mode", "Mono,Legato,Unison,UniLegato,Poly", "Mono");
	piParam->setBoundVariable(&synthMode, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: Glide Time
	piParam = new PluginParameter(controlID::glideTime_mSec, "Glide Time", "mSec", controlVariableType::kFloat, 0.000000, 10000.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&glideTime_mSec, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- continuous control: Osc123 fo Int
	piParam = new PluginParameter(controlID::osc123_fo_Int, "Osc123 fo Int", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&osc123_fo_Int, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Osc4 fo Int
	piParam = new PluginParameter(controlID::osc4_fo_Int, "Osc4 fo Int", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&osc4_fo_Int, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Osc123 Mod Int
	piParam = new PluginParameter(controlID::osc123_Mod_Int, "Osc123 Mod Int", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&osc123_Mod_Int, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Osc4 Mod Int
	piParam = new PluginParameter(controlID::osc4_Mod_Int, "Osc4 Mod Int", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&osc4_Mod_Int, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Filter1 fc Int
	piParam = new PluginParameter(controlID::filter1_fc_Int, "Filter1 fc Int", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.750000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filter1_fc_Int, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Filter2 fc Int
	piParam = new PluginParameter(controlID::filter2_fc_Int, "Filter2 fc Int", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.750000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filter2_fc_Int, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO2 fo Int
	piParam = new PluginParameter(controlID::lfo2_fo_Int, "LFO2 fo Int", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo2_fo_Int, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO1 Out
	piParam = new PluginParameter(controlID::lfo1SourceInt, "LFO1 Out", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo1SourceInt, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO2 Out
	piParam = new PluginParameter(controlID::lfo2SourceInt, "LFO2 Out", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo2SourceInt, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: AuxEG Out
	piParam = new PluginParameter(controlID::auxEGSourceInt, "AuxEG Out", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&auxEGSourceInt, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: AuxEG OutB
	piParam = new PluginParameter(controlID::auxEGBiasedSourceInt, "AuxEG OutB", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&auxEGBiasedSourceInt, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: lfo1 lfo2fc
	piParam = new PluginParameter(controlID::lfo1_lfo2_fc, "lfo1 lfo2fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo1_lfo2_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo1_o123_fc
	piParam = new PluginParameter(controlID::lfo1_osc123_fc, "lfo1_o123_fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo1_osc123_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo1_o4_fc
	piParam = new PluginParameter(controlID::lfo1_osc04_fc, "lfo1_o4_fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo1_osc04_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo1_o123_Mod
	piParam = new PluginParameter(controlID::lfo1_osc123_Mod, "lfo1_o123_Mod", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo1_osc123_Mod, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo1_o4_Mod
	piParam = new PluginParameter(controlID::lfo1_osc04_Mod, "lfo1_o4_Mod", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo1_osc04_Mod, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo1_Flt1_Fc
	piParam = new PluginParameter(controlID::lfo1_filter1_fc, "lfo1_Flt1_Fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo1_filter1_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo1_Filt2_Fc
	piParam = new PluginParameter(controlID::lfo1_filter2_fc, "lfo1_Filt2_Fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo1_filter2_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo2 lfo2fc
	piParam = new PluginParameter(controlID::lfo2_lfo2_fc, "lfo2 lfo2fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo2_lfo2_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo2_o123_fc
	piParam = new PluginParameter(controlID::lfo2_osc123_fc, "lfo2_o123_fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo2_osc123_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo2_o4_fc
	piParam = new PluginParameter(controlID::lfo2_osc04_fc, "lfo2_o4_fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo2_osc04_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo2_o123_Mod
	piParam = new PluginParameter(controlID::lfo2_osc123_Mod, "lfo2_o123_Mod", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo2_osc123_Mod, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo2_o4_Mod
	piParam = new PluginParameter(controlID::lfo2_osc04_Mod, "lfo2_o4_Mod", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo2_osc04_Mod, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo2_Flt1_Fc
	piParam = new PluginParameter(controlID::lfo2_filter1_fc, "lfo2_Flt1_Fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo2_filter1_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo2_Filt2_Fc
	piParam = new PluginParameter(controlID::lfo2_filter2_fc, "lfo2_Filt2_Fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo2_filter2_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEG lfo2fc
	piParam = new PluginParameter(controlID::auxEG_lfo2_fc, "auxEG lfo2fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEG_lfo2_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEG_o123_fc
	piParam = new PluginParameter(controlID::auxEG_osc123_fc, "auxEG_o123_fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEG_osc123_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEG_o4_fc
	piParam = new PluginParameter(controlID::auxEG_osc04_fc, "auxEG_o4_fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEG_osc04_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEG_o123_Mod
	piParam = new PluginParameter(controlID::auxEG_osc123_Mod, "auxEG_o123_Mod", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEG_osc123_Mod, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEG_o4_Mod
	piParam = new PluginParameter(controlID::auxEG_osc04_Mod, "auxEG_o4_Mod", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEG_osc04_Mod, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEG_Flt1_Fc
	piParam = new PluginParameter(controlID::auxEG_filter1_fc, "auxEG_Flt1_Fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEG_filter1_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEG_Filt2_Fc
	piParam = new PluginParameter(controlID::auxEG_filter2_fc, "auxEG_Filt2_Fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEG_filter2_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEGB lfo2fc
	piParam = new PluginParameter(controlID::auxEGB_lfo2_fc, "auxEGB lfo2fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEGB_lfo2_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEGB_o123_fc
	piParam = new PluginParameter(controlID::auxEGB_osc123_fc, "auxEGB_o123_fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEGB_osc123_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEGB_o4_fc
	piParam = new PluginParameter(controlID::auxEGB_osc04_fc, "auxEGB_o4_fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEGB_osc04_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEGB_o123_Mod
	piParam = new PluginParameter(controlID::auxEGB_osc123_Mod, "auxEGB_o123_Mod", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEGB_osc123_Mod, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEGB_o4_Mod
	piParam = new PluginParameter(controlID::auxEGB_osc04_Mod, "auxEGB_o4_Mod", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEGB_osc04_Mod, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEGB_Flt1_Fc
	piParam = new PluginParameter(controlID::auxEGB_filter1_fc, "auxEGB_Flt1_Fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEGB_filter1_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEGB_Filt2_Fc
	piParam = new PluginParameter(controlID::auxEGB_filter2_fc, "auxEGB_Filt2_Fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEGB_filter2_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Filter Mode
	piParam = new PluginParameter(controlID::filterModeIndex, "Filter Mode", "series,parallel", "series");
	piParam->setBoundVariable(&filterModeIndex, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Delay FX
	piParam = new PluginParameter(controlID::enableDelayFX, "Delay FX", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&enableDelayFX, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: Delay L
	piParam = new PluginParameter(controlID::leftDelay_mSec, "Delay L", "mSec", controlVariableType::kDouble, 0.000000, 2000.000000, 500.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(2000.00);
	piParam->setBoundVariable(&leftDelay_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Delay R
	piParam = new PluginParameter(controlID::rightDelay_mSec, "Delay R", "mSec", controlVariableType::kDouble, 0.000000, 2000.000000, 500.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(2000.00);
	piParam->setBoundVariable(&rightDelay_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Feedback
	piParam = new PluginParameter(controlID::feedback_Pct, "Feedback", "%", controlVariableType::kDouble, 0.000000, 100.000000, 20.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&feedback_Pct, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Delay Dry
	piParam = new PluginParameter(controlID::dryLevel_dB, "Delay Dry", "dB", controlVariableType::kDouble, -60.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&dryLevel_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Delay Wet
	piParam = new PluginParameter(controlID::wetLevel_dB, "Delay Wet", "dB", controlVariableType::kDouble, -60.000000, 12.000000, -3.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wetLevel_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: DCA EG Mod
	piParam = new PluginParameter(controlID::ampEGIntensity, "DCA EG Mod", "", controlVariableType::kDouble, -1.000000, 1.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ampEGIntensity, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: AmpEG Trig
	piParam = new PluginParameter(controlID::ampEGTrigInt, "AmpEG Trig", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ampEGTrigInt, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: lfo1_AmpEGTrig
	piParam = new PluginParameter(controlID::lfo1_ampEGTrig, "lfo1_AmpEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo1_ampEGTrig, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo2_AmpEGTrig
	piParam = new PluginParameter(controlID::lfo2_ampEGTrig, "lfo2_AmpEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo2_ampEGTrig, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEG_AmpEGTrig
	piParam = new PluginParameter(controlID::auxEG_ampEGTrig, "auxEG_AmpEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEG_ampEGTrig, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEGB_AmpEGTrig
	piParam = new PluginParameter(controlID::auxEGB_ampEGTrig, "auxEGB_AmpEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEGB_ampEGTrig, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: DCA Pan
	piParam = new PluginParameter(controlID::dcaPanInt, "DCA Pan", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&dcaPanInt, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: lfo1 Pan
	piParam = new PluginParameter(controlID::lfo1_dcaPan, "lfo1 Pan", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo1_dcaPan, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo2 Pan
	piParam = new PluginParameter(controlID::lfo2_dcaPan, "lfo2 Pan", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo2_dcaPan, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEG Pan
	piParam = new PluginParameter(controlID::auxEG_dcaPan, "auxEG Pan", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEG_dcaPan, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEGB Pan
	piParam = new PluginParameter(controlID::auxEGB_dcaPan, "auxEGB Pan", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEGB_dcaPan, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: FilterEG Out
	piParam = new PluginParameter(controlID::filterEGSourceInt, "FilterEG Out", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.750000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filterEGSourceInt, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: filterEG lfo2fc
	piParam = new PluginParameter(controlID::filterEG_lfo2_fc, "filterEG lfo2fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&filterEG_lfo2_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: filterEG_o123_fc
	piParam = new PluginParameter(controlID::filterEG_osc123_fc, "filterEG_o123_fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&filterEG_osc123_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: filterEG_o4_fc
	piParam = new PluginParameter(controlID::filterEG_osc04_fc, "filterEG_o4_fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&filterEG_osc04_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: filterEG_o123_Mod
	piParam = new PluginParameter(controlID::filterEG_osc123_Mod, "filterEG_o123_Mod", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&filterEG_osc123_Mod, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: filterEG_o4_Mod
	piParam = new PluginParameter(controlID::filterEG_osc04_Mod, "filterEG_o4_Mod", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&filterEG_osc04_Mod, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: filterEG_Flt1_Fc
	piParam = new PluginParameter(controlID::filterEG_filter1_fc, "filterEG_Flt1_Fc", "SWITCH OFF,SWITCH ON", "SWITCH ON");
	piParam->setBoundVariable(&filterEG_filter1_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: filterEG_Filt2_Fc
	piParam = new PluginParameter(controlID::filterEG_filter2_fc, "filterEG_Filt2_Fc", "SWITCH OFF,SWITCH ON", "SWITCH ON");
	piParam->setBoundVariable(&filterEG_filter2_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: filterEG Pan
	piParam = new PluginParameter(controlID::filterEG_dcaPan, "filterEG Pan", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&filterEG_dcaPan, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: filterEG_AmpEGTrig
	piParam = new PluginParameter(controlID::filterEG_ampEGTrig, "filterEG_AmpEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&filterEG_ampEGTrig, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: FM1 Core
	piParam = new PluginParameter(controlID::osc1Core, "FM1 Core", "default 0,user 0,user 1,user 2", "default 0");
	piParam->setBoundVariable(&osc1Core, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: FM1 Start
	piParam = new PluginParameter(controlID::fmo1_startLevel, "FM1 Start", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo1_startLevel, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM1 Att
	piParam = new PluginParameter(controlID::fmo1_attackTime_mSec, "FM1 Att", "mSec", controlVariableType::kDouble, 1.000000, 1000.000000, 10.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo1_attackTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM1 Dcy
	piParam = new PluginParameter(controlID::fmo1_decayTime_mSec, "FM1 Dcy", "mSec", controlVariableType::kDouble, 1.000000, 5000.000000, 500.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo1_decayTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM1 Sus
	piParam = new PluginParameter(controlID::fmo1_sustainLevel, "FM1 Sus", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.750000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo1_sustainLevel, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM1 Rel
	piParam = new PluginParameter(controlID::fmo1_relaseTime_mSec, "FM1 Rel", "mSec", controlVariableType::kDouble, 1.000000, 10000.000000, 1000.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo1_relaseTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM1 A
	piParam = new PluginParameter(controlID::fmo1_ModKnobA, "FM1 A", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo1_ModKnobA, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM1 B
	piParam = new PluginParameter(controlID::fmo1_ModKnobB, "FM1 B", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo1_ModKnobB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM1 C
	piParam = new PluginParameter(controlID::fmo1_ModKnobC, "FM1 C", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo1_ModKnobC, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM1 D
	piParam = new PluginParameter(controlID::fmo1_ModKnobD, "FM1 D", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo1_ModKnobD, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM1 Fine
	piParam = new PluginParameter(controlID::fmo1_fineDetune, "FM1 Fine", "cents", controlVariableType::kDouble, -50.000000, 50.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo1_fineDetune, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM1 Ratio
	piParam = new PluginParameter(controlID::fmo1_ratio, "FM1 Ratio", "", controlVariableType::kDouble, 0.100000, 10.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&fmo1_ratio, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: t
	piParam = new PluginParameter(controlID::fmo1_phaseModIndex, "t", "", controlVariableType::kDouble, 0.000000, 4.000000, 0.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&fmo1_phaseModIndex, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM1 DcyLvl
	piParam = new PluginParameter(controlID::fmo1_decayLevel, "FM1 DcyLvl", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo1_decayLevel, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM1 Slope
	piParam = new PluginParameter(controlID::fmo1_slopeTime_mSec, "FM1 Slope", "mSec", controlVariableType::kDouble, 1.000000, 10000.000000, 1000.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo1_slopeTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM1 Curve
	piParam = new PluginParameter(controlID::fmo1_egCurvature, "FM1 Curve", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo1_egCurvature, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM1 Pan
	piParam = new PluginParameter(controlID::fmo1_panValue, "FM1 Pan", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo1_panValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: FM2 Core
	piParam = new PluginParameter(controlID::osc2Core, "FM2 Core", "default 0,user 0,user 1,user 2", "default 0");
	piParam->setBoundVariable(&osc2Core, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: FM2 Start
	piParam = new PluginParameter(controlID::fmo2_startLevel, "FM2 Start", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo2_startLevel, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM2 Att
	piParam = new PluginParameter(controlID::fmo2_attackTime_mSec, "FM2 Att", "mSec", controlVariableType::kDouble, 1.000000, 1000.000000, 10.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo2_attackTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM2 Dcy
	piParam = new PluginParameter(controlID::fmo2_decayTime_mSec, "FM2 Dcy", "mSec", controlVariableType::kDouble, 1.000000, 5000.000000, 500.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo2_decayTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM2 Sus
	piParam = new PluginParameter(controlID::fmo2_sustainLevel, "FM2 Sus", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.750000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo2_sustainLevel, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM2 Rel
	piParam = new PluginParameter(controlID::fmo2_relaseTime_mSec, "FM2 Rel", "mSec", controlVariableType::kDouble, 1.000000, 10000.000000, 1000.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo2_relaseTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM2 A
	piParam = new PluginParameter(controlID::fmo2_ModKnobA, "FM2 A", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo2_ModKnobA, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM2 B
	piParam = new PluginParameter(controlID::fmo2_ModKnobB, "FM2 B", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo2_ModKnobB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM2 C
	piParam = new PluginParameter(controlID::fmo2_ModKnobC, "FM2 C", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo2_ModKnobC, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM2 D
	piParam = new PluginParameter(controlID::fmo2_ModKnobD, "FM2 D", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo2_ModKnobD, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM2 Fine
	piParam = new PluginParameter(controlID::fmo2_fineDetune, "FM2 Fine", "cents", controlVariableType::kDouble, -50.000000, 50.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo2_fineDetune, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM2 Ratio
	piParam = new PluginParameter(controlID::fmo2_ratio, "FM2 Ratio", "", controlVariableType::kDouble, 0.100000, 10.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&fmo2_ratio, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM2 Int
	piParam = new PluginParameter(controlID::fmo2_phaseModIndex, "FM2 Int", "", controlVariableType::kDouble, 0.000000, 4.000000, 0.750000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&fmo2_phaseModIndex, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM2 DcyLvl
	piParam = new PluginParameter(controlID::fmo2_decayLevel, "FM2 DcyLvl", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo2_decayLevel, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM2 Slope
	piParam = new PluginParameter(controlID::fmo2_slopeTime_mSec, "FM2 Slope", "mSec", controlVariableType::kDouble, 1.000000, 10000.000000, 1000.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo2_slopeTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM2 Curve
	piParam = new PluginParameter(controlID::fmo2_egCurvature, "FM2 Curve", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo2_egCurvature, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM2 Pan
	piParam = new PluginParameter(controlID::fmo2_panValue, "FM2 Pan", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo2_panValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: FM3 Core
	piParam = new PluginParameter(controlID::osc3Core, "FM3 Core", "default 0,user 0,user 1,user 2", "default 0");
	piParam->setBoundVariable(&osc3Core, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: FM3 Start
	piParam = new PluginParameter(controlID::fmo3_startLevel, "FM3 Start", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo3_startLevel, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM3 Att
	piParam = new PluginParameter(controlID::fmo3_attackTime_mSec, "FM3 Att", "mSec", controlVariableType::kDouble, 1.000000, 1000.000000, 10.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo3_attackTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM3 Dcy
	piParam = new PluginParameter(controlID::fmo3_decayTime_mSec, "FM3 Dcy", "mSec", controlVariableType::kDouble, 1.000000, 5000.000000, 500.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo3_decayTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM3 Sus
	piParam = new PluginParameter(controlID::fmo3_sustainLevel, "FM3 Sus", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.750000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo3_sustainLevel, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM3 Rel
	piParam = new PluginParameter(controlID::fmo3_relaseTime_mSec, "FM3 Rel", "mSec", controlVariableType::kDouble, 1.000000, 10000.000000, 1000.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo3_relaseTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM3 A
	piParam = new PluginParameter(controlID::fmo3_ModKnobA, "FM3 A", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo3_ModKnobA, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM3 B
	piParam = new PluginParameter(controlID::fmo3_ModKnobB, "FM3 B", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo3_ModKnobB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM3 C
	piParam = new PluginParameter(controlID::fmo3_ModKnobC, "FM3 C", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo3_ModKnobC, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM3 D
	piParam = new PluginParameter(controlID::fmo3_ModKnobD, "FM3 D", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo3_ModKnobD, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM3 Fine
	piParam = new PluginParameter(controlID::fmo3_fineDetune, "FM3 Fine", "cents", controlVariableType::kDouble, -50.000000, 50.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo3_fineDetune, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM3 Ratio
	piParam = new PluginParameter(controlID::fmo3_ratio, "FM3 Ratio", "", controlVariableType::kDouble, 0.100000, 10.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&fmo3_ratio, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM3 Int
	piParam = new PluginParameter(controlID::fmo3_phaseModIndex, "FM3 Int", "", controlVariableType::kDouble, 0.000000, 4.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&fmo3_phaseModIndex, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM3 DcyLvl
	piParam = new PluginParameter(controlID::fmo3_decayLevel, "FM3 DcyLvl", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo3_decayLevel, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM3 Slope
	piParam = new PluginParameter(controlID::fmo3_slopeTime_mSec, "FM3 Slope", "mSec", controlVariableType::kDouble, 1.000000, 10000.000000, 1000.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo3_slopeTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM3 Curve
	piParam = new PluginParameter(controlID::fmo3_egCurvature, "FM3 Curve", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo3_egCurvature, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM3 Pan
	piParam = new PluginParameter(controlID::fmo3_panValue, "FM3 Pan", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo3_panValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: FM4 Core
	piParam = new PluginParameter(controlID::osc4Core, "FM4 Core", "default 0,user 0,user 1,user 2", "default 0");
	piParam->setBoundVariable(&osc4Core, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: FM4 Start
	piParam = new PluginParameter(controlID::fmo4_startLevel, "FM4 Start", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo4_startLevel, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM4 Att
	piParam = new PluginParameter(controlID::fmo4_attackTime_mSec, "FM4 Att", "mSec", controlVariableType::kDouble, 1.000000, 1000.000000, 10.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo4_attackTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM4 Dcy
	piParam = new PluginParameter(controlID::fmo4_decayTime_mSec, "FM4 Dcy", "mSec", controlVariableType::kDouble, 1.000000, 5000.000000, 500.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo4_decayTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM4 Sus
	piParam = new PluginParameter(controlID::fmo4_sustainLevel, "FM4 Sus", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.750000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo4_sustainLevel, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM4 Rel
	piParam = new PluginParameter(controlID::fmo4_relaseTime_mSec, "FM4 Rel", "mSec", controlVariableType::kDouble, 1.000000, 10000.000000, 1000.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo4_relaseTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM4 A
	piParam = new PluginParameter(controlID::fmo4_ModKnobA, "FM4 A", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo4_ModKnobA, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM4 B
	piParam = new PluginParameter(controlID::fmo4_ModKnobB, "FM4 B", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo4_ModKnobB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM4 C
	piParam = new PluginParameter(controlID::fmo4_ModKnobC, "FM4 C", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo4_ModKnobC, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM4 D
	piParam = new PluginParameter(controlID::fmo4_ModKnobD, "FM4 D", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo4_ModKnobD, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM4 Fine
	piParam = new PluginParameter(controlID::fmo4_fineDetune, "FM4 Fine", "cents", controlVariableType::kDouble, -50.000000, 50.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo4_fineDetune, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM4 Ratio
	piParam = new PluginParameter(controlID::fmo4_ratio, "FM4 Ratio", "", controlVariableType::kDouble, 0.100000, 10.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&fmo4_ratio, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM4 Int
	piParam = new PluginParameter(controlID::fmo4_phaseModIndex, "FM4 Int", "", controlVariableType::kDouble, 0.000000, 4.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&fmo4_phaseModIndex, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM4 DcyLvl
	piParam = new PluginParameter(controlID::fmo4_decayLevel, "FM4 DcyLvl", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo4_decayLevel, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM4 Slope
	piParam = new PluginParameter(controlID::fmo4_slopeTime_mSec, "FM4 Slope", "mSec", controlVariableType::kDouble, 1.000000, 10000.000000, 1000.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo4_slopeTime_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM4 Curve
	piParam = new PluginParameter(controlID::fmo4_egCurvature, "FM4 Curve", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo4_egCurvature, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FM4 Pan
	piParam = new PluginParameter(controlID::fmo4_panValue, "FM4 Pan", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&fmo4_panValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: FM Algorithm
	piParam = new PluginParameter(controlID::fmAlgorithm, "FM Algorithm", "FM1,FM2,FM3,FM4,FM5,FM6,FM7,FM8", "FM1");
	piParam->setBoundVariable(&fmAlgorithm, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: FM1 Wave
	piParam = new PluginParameter(controlID::osc1_waveform, "FM1 Wave", "wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15", "wave0");
	piParam->setBoundVariable(&osc1_waveform, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: FM2 Wave
	piParam = new PluginParameter(controlID::osc2_waveform, "FM2 Wave", "wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15", "wave0");
	piParam->setBoundVariable(&osc2_waveform, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: FM3 Wave
	piParam = new PluginParameter(controlID::osc3_waveform, "FM3 Wave", "wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15", "wave0");
	piParam->setBoundVariable(&osc3_waveform, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: FM4 Wave
	piParam = new PluginParameter(controlID::osc4_waveform, "FM4 Wave", "wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15", "wave0");
	piParam->setBoundVariable(&osc4_waveform, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- non-GUI-bound variable: MAIN_SWITCH
	piParam = new PluginParameter(controlID::MAIN_SWITCH, "MAIN_SWITCH");
	addPluginParameter(piParam);

	// --- non-GUI-bound variable: OSC_SWITCH
	piParam = new PluginParameter(controlID::OSC_SWITCH, "OSC_SWITCH");
	addPluginParameter(piParam);

	// --- non-GUI-bound variable: LFO_WSITCH
	piParam = new PluginParameter(controlID::LFO_WSITCH, "LFO_WSITCH");
	addPluginParameter(piParam);

	// --- non-GUI-bound variable: EG_SWITCH
	piParam = new PluginParameter(controlID::EG_SWITCH, "EG_SWITCH");
	addPluginParameter(piParam);

	// --- non-GUI-bound variable: FILTER_SWITCH
	piParam = new PluginParameter(controlID::FILTER_SWITCH, "FILTER_SWITCH");
	addPluginParameter(piParam);

	// --- discrete control: Op1 EG
	piParam = new PluginParameter(controlID::fmo1_EG, "Op1 EG", "DX,analog", "DX");
	piParam->setBoundVariable(&fmo1_EG, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Op2 EG
	piParam = new PluginParameter(controlID::fmo2_EG, "Op2 EG", "DX,analog", "DX");
	piParam->setBoundVariable(&fmo2_EG, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Op3 EG
	piParam = new PluginParameter(controlID::fmo3_EG, "Op3 EG", "DX,analog", "DX");
	piParam->setBoundVariable(&fmo3_EG, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Op4 EG
	piParam = new PluginParameter(controlID::fmo4_EG, "Op4 EG", "DX,analog", "DX");
	piParam->setBoundVariable(&fmo4_EG, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- Aux Attributes
	AuxParameterAttribute auxAttribute;

	// --- RAFX GUI attributes
	// --- controlID::lfo1Core
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo1Core, auxAttribute);

	// --- controlID::lfo1Core
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::lfo1Core, auxAttribute);

	// --- controlID::lfo1_waveform
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo1_waveform, auxAttribute);

	// --- controlID::lfo1_waveform
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::lfo1_waveform, auxAttribute);

	// --- controlID::lfo1_mode
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::lfo1_mode, auxAttribute);

	// --- controlID::lfo1_frequency_Hz
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::lfo1_frequency_Hz, auxAttribute);

	// --- controlID::lfo1_outputAmplitude
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::lfo1_outputAmplitude, auxAttribute);

	// --- controlID::lfo1_ModKnobA
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo1_ModKnobA, auxAttribute);

	// --- controlID::lfo1_ModKnobA
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo1_ModKnobA, auxAttribute);

	// --- controlID::lfo1_ModKnobA
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::lfo1_ModKnobA, auxAttribute);

	// --- controlID::lfo1_ModKnobB
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo1_ModKnobB, auxAttribute);

	// --- controlID::lfo1_ModKnobB
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo1_ModKnobB, auxAttribute);

	// --- controlID::lfo1_ModKnobB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::lfo1_ModKnobB, auxAttribute);

	// --- controlID::lfo1_ModKnobC
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo1_ModKnobC, auxAttribute);

	// --- controlID::lfo1_ModKnobC
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo1_ModKnobC, auxAttribute);

	// --- controlID::lfo1_ModKnobC
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::lfo1_ModKnobC, auxAttribute);

	// --- controlID::lfo1_ModKnobD
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo1_ModKnobD, auxAttribute);

	// --- controlID::lfo1_ModKnobD
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo1_ModKnobD, auxAttribute);

	// --- controlID::lfo1_ModKnobD
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::lfo1_ModKnobD, auxAttribute);

	// --- controlID::lfo1_quantize
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::lfo1_quantize, auxAttribute);

	// --- controlID::ampEG_attackTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::ampEG_attackTime_mSec, auxAttribute);

	// --- controlID::ampEG_decayTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::ampEG_decayTime_mSec, auxAttribute);

	// --- controlID::ampEG_sustainLevel
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::ampEG_sustainLevel, auxAttribute);

	// --- controlID::ampEG_releaseTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::ampEG_releaseTime_mSec, auxAttribute);

	// --- controlID::ampEGCore
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::ampEGCore, auxAttribute);

	// --- controlID::ampEGCore
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::ampEGCore, auxAttribute);

	// --- controlID::ampEGMode
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::ampEGMode, auxAttribute);

	// --- controlID::ampEGMode
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::ampEGMode, auxAttribute);

	// --- controlID::ampEG_ModKnobA
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::ampEG_ModKnobA, auxAttribute);

	// --- controlID::ampEG_ModKnobA
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::ampEG_ModKnobA, auxAttribute);

	// --- controlID::ampEG_ModKnobA
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::ampEG_ModKnobA, auxAttribute);

	// --- controlID::ampEG_ModKnobB
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::ampEG_ModKnobB, auxAttribute);

	// --- controlID::ampEG_ModKnobB
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::ampEG_ModKnobB, auxAttribute);

	// --- controlID::ampEG_ModKnobB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::ampEG_ModKnobB, auxAttribute);

	// --- controlID::ampEG_ModKnobC
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::ampEG_ModKnobC, auxAttribute);

	// --- controlID::ampEG_ModKnobC
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::ampEG_ModKnobC, auxAttribute);

	// --- controlID::ampEG_ModKnobC
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::ampEG_ModKnobC, auxAttribute);

	// --- controlID::ampEG_ModKnobD
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::ampEG_ModKnobD, auxAttribute);

	// --- controlID::ampEG_ModKnobD
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::ampEG_ModKnobD, auxAttribute);

	// --- controlID::ampEG_ModKnobD
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::ampEG_ModKnobD, auxAttribute);

	// --- controlID::filter1Core
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter1Core, auxAttribute);

	// --- controlID::filter1Core
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::filter1Core, auxAttribute);

	// --- controlID::filter1Algorithm
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter1Algorithm, auxAttribute);

	// --- controlID::filter1Algorithm
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::filter1Algorithm, auxAttribute);

	// --- controlID::filter1_ModKnobA
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter1_ModKnobA, auxAttribute);

	// --- controlID::filter1_ModKnobA
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter1_ModKnobA, auxAttribute);

	// --- controlID::filter1_ModKnobA
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::filter1_ModKnobA, auxAttribute);

	// --- controlID::filter1_ModKnobB
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter1_ModKnobB, auxAttribute);

	// --- controlID::filter1_ModKnobB
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter1_ModKnobB, auxAttribute);

	// --- controlID::filter1_ModKnobB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::filter1_ModKnobB, auxAttribute);

	// --- controlID::filter1_ModKnobC
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter1_ModKnobC, auxAttribute);

	// --- controlID::filter1_ModKnobC
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter1_ModKnobC, auxAttribute);

	// --- controlID::filter1_ModKnobC
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::filter1_ModKnobC, auxAttribute);

	// --- controlID::filter1_ModKnobD
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter1_ModKnobD, auxAttribute);

	// --- controlID::filter1_ModKnobD
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter1_ModKnobD, auxAttribute);

	// --- controlID::filter1_ModKnobD
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::filter1_ModKnobD, auxAttribute);

	// --- controlID::filter1_fc
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter1_fc, auxAttribute);

	// --- controlID::filter1_fc
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter1_fc, auxAttribute);

	// --- controlID::filter1_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::filter1_fc, auxAttribute);

	// --- controlID::filter1_Q
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter1_Q, auxAttribute);

	// --- controlID::filter1_Q
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter1_Q, auxAttribute);

	// --- controlID::filter1_Q
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::filter1_Q, auxAttribute);

	// --- controlID::filter1Output_dB
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter1Output_dB, auxAttribute);

	// --- controlID::filter1Output_dB
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter1Output_dB, auxAttribute);

	// --- controlID::filter1Output_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::filter1Output_dB, auxAttribute);

	// --- controlID::enableFilter1KeyTrack
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741827);
	setParamAuxAttribute(controlID::enableFilter1KeyTrack, auxAttribute);

	// --- controlID::filterEGCore
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filterEGCore, auxAttribute);

	// --- controlID::filterEGCore
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::filterEGCore, auxAttribute);

	// --- controlID::filterEGMode
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filterEGMode, auxAttribute);

	// --- controlID::filterEGMode
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::filterEGMode, auxAttribute);

	// --- controlID::filterEG_attackTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::filterEG_attackTime_mSec, auxAttribute);

	// --- controlID::filterEG_decayTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::filterEG_decayTime_mSec, auxAttribute);

	// --- controlID::filterEG_sustainLevel
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::filterEG_sustainLevel, auxAttribute);

	// --- controlID::filterEG_releaseTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::filterEG_releaseTime_mSec, auxAttribute);

	// --- controlID::filterEG_ModKnobA
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filterEG_ModKnobA, auxAttribute);

	// --- controlID::filterEG_ModKnobA
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filterEG_ModKnobA, auxAttribute);

	// --- controlID::filterEG_ModKnobA
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::filterEG_ModKnobA, auxAttribute);

	// --- controlID::filterEG_ModKnobB
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filterEG_ModKnobB, auxAttribute);

	// --- controlID::filterEG_ModKnobB
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filterEG_ModKnobB, auxAttribute);

	// --- controlID::filterEG_ModKnobB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::filterEG_ModKnobB, auxAttribute);

	// --- controlID::filterEG_ModKnobC
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filterEG_ModKnobC, auxAttribute);

	// --- controlID::filterEG_ModKnobC
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filterEG_ModKnobC, auxAttribute);

	// --- controlID::filterEG_ModKnobC
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::filterEG_ModKnobC, auxAttribute);

	// --- controlID::filterEG_ModKnobD
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filterEG_ModKnobD, auxAttribute);

	// --- controlID::filterEG_ModKnobD
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filterEG_ModKnobD, auxAttribute);

	// --- controlID::filterEG_ModKnobD
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::filterEG_ModKnobD, auxAttribute);

	// --- controlID::lfo2Core
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo2Core, auxAttribute);

	// --- controlID::lfo2Core
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::lfo2Core, auxAttribute);

	// --- controlID::lfo2_waveform
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo2_waveform, auxAttribute);

	// --- controlID::lfo2_waveform
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::lfo2_waveform, auxAttribute);

	// --- controlID::lfo2_mode
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::lfo2_mode, auxAttribute);

	// --- controlID::lfo2_frequency_Hz
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::lfo2_frequency_Hz, auxAttribute);

	// --- controlID::lfo2_outputAmplitude
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::lfo2_outputAmplitude, auxAttribute);

	// --- controlID::lfo2_quantize
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::lfo2_quantize, auxAttribute);

	// --- controlID::lfo2_ModKnobA
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo2_ModKnobA, auxAttribute);

	// --- controlID::lfo2_ModKnobA
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo2_ModKnobA, auxAttribute);

	// --- controlID::lfo2_ModKnobA
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::lfo2_ModKnobA, auxAttribute);

	// --- controlID::lfo2_ModKnobB
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo2_ModKnobB, auxAttribute);

	// --- controlID::lfo2_ModKnobB
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo2_ModKnobB, auxAttribute);

	// --- controlID::lfo2_ModKnobB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::lfo2_ModKnobB, auxAttribute);

	// --- controlID::lfo2_ModKnobC
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo2_ModKnobC, auxAttribute);

	// --- controlID::lfo2_ModKnobC
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo2_ModKnobC, auxAttribute);

	// --- controlID::lfo2_ModKnobC
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::lfo2_ModKnobC, auxAttribute);

	// --- controlID::lfo2_ModKnobD
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo2_ModKnobD, auxAttribute);

	// --- controlID::lfo2_ModKnobD
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::lfo2_ModKnobD, auxAttribute);

	// --- controlID::lfo2_ModKnobD
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::lfo2_ModKnobD, auxAttribute);

	// --- controlID::auxEGCore
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::auxEGCore, auxAttribute);

	// --- controlID::auxEGCore
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::auxEGCore, auxAttribute);

	// --- controlID::auxEGMode
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::auxEGMode, auxAttribute);

	// --- controlID::auxEGMode
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::auxEGMode, auxAttribute);

	// --- controlID::auxEG_attackTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::auxEG_attackTime_mSec, auxAttribute);

	// --- controlID::auxEG_decayTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::auxEG_decayTime_mSec, auxAttribute);

	// --- controlID::auxEG_sustainLevel
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::auxEG_sustainLevel, auxAttribute);

	// --- controlID::auxEG_releaseTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::auxEG_releaseTime_mSec, auxAttribute);

	// --- controlID::auxEG_ModKnobA
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::auxEG_ModKnobA, auxAttribute);

	// --- controlID::auxEG_ModKnobA
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::auxEG_ModKnobA, auxAttribute);

	// --- controlID::auxEG_ModKnobA
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::auxEG_ModKnobA, auxAttribute);

	// --- controlID::auxEG_ModKnobB
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::auxEG_ModKnobB, auxAttribute);

	// --- controlID::auxEG_ModKnobB
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::auxEG_ModKnobB, auxAttribute);

	// --- controlID::auxEG_ModKnobB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::auxEG_ModKnobB, auxAttribute);

	// --- controlID::auxEG_ModKnobC
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::auxEG_ModKnobC, auxAttribute);

	// --- controlID::auxEG_ModKnobC
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::auxEG_ModKnobC, auxAttribute);

	// --- controlID::auxEG_ModKnobC
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::auxEG_ModKnobC, auxAttribute);

	// --- controlID::auxEG_ModKnobD
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::auxEG_ModKnobD, auxAttribute);

	// --- controlID::auxEG_ModKnobD
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::auxEG_ModKnobD, auxAttribute);

	// --- controlID::auxEG_ModKnobD
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::auxEG_ModKnobD, auxAttribute);

	// --- controlID::filter2Core
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter2Core, auxAttribute);

	// --- controlID::filter2Core
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::filter2Core, auxAttribute);

	// --- controlID::filter2Algorithm
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter2Algorithm, auxAttribute);

	// --- controlID::filter2Algorithm
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::filter2Algorithm, auxAttribute);

	// --- controlID::filter2_fc
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter2_fc, auxAttribute);

	// --- controlID::filter2_fc
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter2_fc, auxAttribute);

	// --- controlID::filter2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::filter2_fc, auxAttribute);

	// --- controlID::filter2_Q
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter2_Q, auxAttribute);

	// --- controlID::filter2_Q
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter2_Q, auxAttribute);

	// --- controlID::filter2_Q
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::filter2_Q, auxAttribute);

	// --- controlID::enableFilter2KeyTrack
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741827);
	setParamAuxAttribute(controlID::enableFilter2KeyTrack, auxAttribute);

	// --- controlID::filter2Output_dB
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter2Output_dB, auxAttribute);

	// --- controlID::filter2Output_dB
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter2Output_dB, auxAttribute);

	// --- controlID::filter2Output_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::filter2Output_dB, auxAttribute);

	// --- controlID::filter2_ModKnobA
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter2_ModKnobA, auxAttribute);

	// --- controlID::filter2_ModKnobA
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter2_ModKnobA, auxAttribute);

	// --- controlID::filter2_ModKnobA
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::filter2_ModKnobA, auxAttribute);

	// --- controlID::filter2_ModKnobB
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter2_ModKnobB, auxAttribute);

	// --- controlID::filter2_ModKnobB
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter2_ModKnobB, auxAttribute);

	// --- controlID::filter2_ModKnobB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::filter2_ModKnobB, auxAttribute);

	// --- controlID::filter2_ModKnobC
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter2_ModKnobC, auxAttribute);

	// --- controlID::filter2_ModKnobC
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter2_ModKnobC, auxAttribute);

	// --- controlID::filter2_ModKnobC
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::filter2_ModKnobC, auxAttribute);

	// --- controlID::filter2_ModKnobD
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter2_ModKnobD, auxAttribute);

	// --- controlID::filter2_ModKnobD
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::filter2_ModKnobD, auxAttribute);

	// --- controlID::filter2_ModKnobD
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::filter2_ModKnobD, auxAttribute);

	// --- controlID::globalVolume_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::globalVolume_dB, auxAttribute);

	// --- controlID::globalTuning
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::globalTuning, auxAttribute);

	// --- controlID::globalUnisonDetune_Cents
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::globalUnisonDetune_Cents, auxAttribute);

	// --- controlID::globalPitchBendSens
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::globalPitchBendSens, auxAttribute);

	// --- controlID::synthMode
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::synthMode, auxAttribute);

	// --- controlID::glideTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483683);
	setParamAuxAttribute(controlID::glideTime_mSec, auxAttribute);

	// --- controlID::osc123_fo_Int
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483719);
	setParamAuxAttribute(controlID::osc123_fo_Int, auxAttribute);

	// --- controlID::osc4_fo_Int
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483719);
	setParamAuxAttribute(controlID::osc4_fo_Int, auxAttribute);

	// --- controlID::osc123_Mod_Int
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483719);
	setParamAuxAttribute(controlID::osc123_Mod_Int, auxAttribute);

	// --- controlID::osc4_Mod_Int
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483719);
	setParamAuxAttribute(controlID::osc4_Mod_Int, auxAttribute);

	// --- controlID::filter1_fc_Int
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483719);
	setParamAuxAttribute(controlID::filter1_fc_Int, auxAttribute);

	// --- controlID::filter2_fc_Int
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483719);
	setParamAuxAttribute(controlID::filter2_fc_Int, auxAttribute);

	// --- controlID::lfo2_fo_Int
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483719);
	setParamAuxAttribute(controlID::lfo2_fo_Int, auxAttribute);

	// --- controlID::lfo1SourceInt
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483717);
	setParamAuxAttribute(controlID::lfo1SourceInt, auxAttribute);

	// --- controlID::lfo2SourceInt
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483717);
	setParamAuxAttribute(controlID::lfo2SourceInt, auxAttribute);

	// --- controlID::auxEGSourceInt
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483717);
	setParamAuxAttribute(controlID::auxEGSourceInt, auxAttribute);

	// --- controlID::auxEGBiasedSourceInt
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483717);
	setParamAuxAttribute(controlID::auxEGBiasedSourceInt, auxAttribute);

	// --- controlID::lfo1_lfo2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo1_lfo2_fc, auxAttribute);

	// --- controlID::lfo1_osc123_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo1_osc123_fc, auxAttribute);

	// --- controlID::lfo1_osc04_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo1_osc04_fc, auxAttribute);

	// --- controlID::lfo1_osc123_Mod
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo1_osc123_Mod, auxAttribute);

	// --- controlID::lfo1_osc04_Mod
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo1_osc04_Mod, auxAttribute);

	// --- controlID::lfo1_filter1_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo1_filter1_fc, auxAttribute);

	// --- controlID::lfo1_filter2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo1_filter2_fc, auxAttribute);

	// --- controlID::lfo2_lfo2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo2_lfo2_fc, auxAttribute);

	// --- controlID::lfo2_osc123_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo2_osc123_fc, auxAttribute);

	// --- controlID::lfo2_osc04_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo2_osc04_fc, auxAttribute);

	// --- controlID::lfo2_osc123_Mod
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo2_osc123_Mod, auxAttribute);

	// --- controlID::lfo2_osc04_Mod
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo2_osc04_Mod, auxAttribute);

	// --- controlID::lfo2_filter1_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo2_filter1_fc, auxAttribute);

	// --- controlID::lfo2_filter2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo2_filter2_fc, auxAttribute);

	// --- controlID::auxEG_lfo2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEG_lfo2_fc, auxAttribute);

	// --- controlID::auxEG_osc123_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEG_osc123_fc, auxAttribute);

	// --- controlID::auxEG_osc04_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEG_osc04_fc, auxAttribute);

	// --- controlID::auxEG_osc123_Mod
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEG_osc123_Mod, auxAttribute);

	// --- controlID::auxEG_osc04_Mod
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEG_osc04_Mod, auxAttribute);

	// --- controlID::auxEG_filter1_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEG_filter1_fc, auxAttribute);

	// --- controlID::auxEG_filter2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEG_filter2_fc, auxAttribute);

	// --- controlID::auxEGB_lfo2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEGB_lfo2_fc, auxAttribute);

	// --- controlID::auxEGB_osc123_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEGB_osc123_fc, auxAttribute);

	// --- controlID::auxEGB_osc04_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEGB_osc04_fc, auxAttribute);

	// --- controlID::auxEGB_osc123_Mod
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEGB_osc123_Mod, auxAttribute);

	// --- controlID::auxEGB_osc04_Mod
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEGB_osc04_Mod, auxAttribute);

	// --- controlID::auxEGB_filter1_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEGB_filter1_fc, auxAttribute);

	// --- controlID::auxEGB_filter2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEGB_filter2_fc, auxAttribute);

	// --- controlID::filterModeIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::filterModeIndex, auxAttribute);

	// --- controlID::enableDelayFX
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::enableDelayFX, auxAttribute);

	// --- controlID::leftDelay_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::leftDelay_mSec, auxAttribute);

	// --- controlID::rightDelay_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::rightDelay_mSec, auxAttribute);

	// --- controlID::feedback_Pct
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::feedback_Pct, auxAttribute);

	// --- controlID::dryLevel_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::dryLevel_dB, auxAttribute);

	// --- controlID::wetLevel_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::wetLevel_dB, auxAttribute);

	// --- controlID::ampEGIntensity
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483683);
	setParamAuxAttribute(controlID::ampEGIntensity, auxAttribute);

	// --- controlID::ampEGTrigInt
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483719);
	setParamAuxAttribute(controlID::ampEGTrigInt, auxAttribute);

	// --- controlID::lfo1_ampEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo1_ampEGTrig, auxAttribute);

	// --- controlID::lfo2_ampEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo2_ampEGTrig, auxAttribute);

	// --- controlID::auxEG_ampEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEG_ampEGTrig, auxAttribute);

	// --- controlID::auxEGB_ampEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEGB_ampEGTrig, auxAttribute);

	// --- controlID::dcaPanInt
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483719);
	setParamAuxAttribute(controlID::dcaPanInt, auxAttribute);

	// --- controlID::lfo1_dcaPan
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo1_dcaPan, auxAttribute);

	// --- controlID::lfo2_dcaPan
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo2_dcaPan, auxAttribute);

	// --- controlID::auxEG_dcaPan
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEG_dcaPan, auxAttribute);

	// --- controlID::auxEGB_dcaPan
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEGB_dcaPan, auxAttribute);

	// --- controlID::filterEGSourceInt
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483717);
	setParamAuxAttribute(controlID::filterEGSourceInt, auxAttribute);

	// --- controlID::filterEG_lfo2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::filterEG_lfo2_fc, auxAttribute);

	// --- controlID::filterEG_osc123_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::filterEG_osc123_fc, auxAttribute);

	// --- controlID::filterEG_osc04_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::filterEG_osc04_fc, auxAttribute);

	// --- controlID::filterEG_osc123_Mod
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::filterEG_osc123_Mod, auxAttribute);

	// --- controlID::filterEG_osc04_Mod
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::filterEG_osc04_Mod, auxAttribute);

	// --- controlID::filterEG_filter1_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::filterEG_filter1_fc, auxAttribute);

	// --- controlID::filterEG_filter2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::filterEG_filter2_fc, auxAttribute);

	// --- controlID::filterEG_dcaPan
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::filterEG_dcaPan, auxAttribute);

	// --- controlID::filterEG_ampEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::filterEG_ampEGTrig, auxAttribute);

	// --- controlID::osc1Core
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::osc1Core, auxAttribute);

	// --- controlID::osc1Core
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::osc1Core, auxAttribute);

	// --- controlID::fmo1_startLevel
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo1_startLevel, auxAttribute);

	// --- controlID::fmo1_attackTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo1_attackTime_mSec, auxAttribute);

	// --- controlID::fmo1_decayTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo1_decayTime_mSec, auxAttribute);

	// --- controlID::fmo1_sustainLevel
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo1_sustainLevel, auxAttribute);

	// --- controlID::fmo1_relaseTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo1_relaseTime_mSec, auxAttribute);

	// --- controlID::fmo1_ModKnobA
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo1_ModKnobA, auxAttribute);

	// --- controlID::fmo1_ModKnobA
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo1_ModKnobA, auxAttribute);

	// --- controlID::fmo1_ModKnobA
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo1_ModKnobA, auxAttribute);

	// --- controlID::fmo1_ModKnobB
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo1_ModKnobB, auxAttribute);

	// --- controlID::fmo1_ModKnobB
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo1_ModKnobB, auxAttribute);

	// --- controlID::fmo1_ModKnobB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo1_ModKnobB, auxAttribute);

	// --- controlID::fmo1_ModKnobC
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo1_ModKnobC, auxAttribute);

	// --- controlID::fmo1_ModKnobC
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo1_ModKnobC, auxAttribute);

	// --- controlID::fmo1_ModKnobC
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo1_ModKnobC, auxAttribute);

	// --- controlID::fmo1_ModKnobD
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo1_ModKnobD, auxAttribute);

	// --- controlID::fmo1_ModKnobD
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo1_ModKnobD, auxAttribute);

	// --- controlID::fmo1_ModKnobD
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo1_ModKnobD, auxAttribute);

	// --- controlID::fmo1_fineDetune
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo1_fineDetune, auxAttribute);

	// --- controlID::fmo1_ratio
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo1_ratio, auxAttribute);

	// --- controlID::fmo1_phaseModIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo1_phaseModIndex, auxAttribute);

	// --- controlID::fmo1_decayLevel
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo1_decayLevel, auxAttribute);

	// --- controlID::fmo1_slopeTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo1_slopeTime_mSec, auxAttribute);

	// --- controlID::fmo1_egCurvature
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo1_egCurvature, auxAttribute);

	// --- controlID::fmo1_panValue
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo1_panValue, auxAttribute);

	// --- controlID::fmo1_panValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo1_panValue, auxAttribute);

	// --- controlID::osc2Core
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::osc2Core, auxAttribute);

	// --- controlID::osc2Core
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::osc2Core, auxAttribute);

	// --- controlID::fmo2_startLevel
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo2_startLevel, auxAttribute);

	// --- controlID::fmo2_attackTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo2_attackTime_mSec, auxAttribute);

	// --- controlID::fmo2_decayTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo2_decayTime_mSec, auxAttribute);

	// --- controlID::fmo2_sustainLevel
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo2_sustainLevel, auxAttribute);

	// --- controlID::fmo2_relaseTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo2_relaseTime_mSec, auxAttribute);

	// --- controlID::fmo2_ModKnobA
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo2_ModKnobA, auxAttribute);

	// --- controlID::fmo2_ModKnobA
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo2_ModKnobA, auxAttribute);

	// --- controlID::fmo2_ModKnobA
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo2_ModKnobA, auxAttribute);

	// --- controlID::fmo2_ModKnobB
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo2_ModKnobB, auxAttribute);

	// --- controlID::fmo2_ModKnobB
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo2_ModKnobB, auxAttribute);

	// --- controlID::fmo2_ModKnobB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo2_ModKnobB, auxAttribute);

	// --- controlID::fmo2_ModKnobC
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo2_ModKnobC, auxAttribute);

	// --- controlID::fmo2_ModKnobC
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo2_ModKnobC, auxAttribute);

	// --- controlID::fmo2_ModKnobC
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo2_ModKnobC, auxAttribute);

	// --- controlID::fmo2_ModKnobD
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo2_ModKnobD, auxAttribute);

	// --- controlID::fmo2_ModKnobD
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo2_ModKnobD, auxAttribute);

	// --- controlID::fmo2_ModKnobD
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo2_ModKnobD, auxAttribute);

	// --- controlID::fmo2_fineDetune
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo2_fineDetune, auxAttribute);

	// --- controlID::fmo2_ratio
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo2_ratio, auxAttribute);

	// --- controlID::fmo2_phaseModIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo2_phaseModIndex, auxAttribute);

	// --- controlID::fmo2_decayLevel
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo2_decayLevel, auxAttribute);

	// --- controlID::fmo2_slopeTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo2_slopeTime_mSec, auxAttribute);

	// --- controlID::fmo2_egCurvature
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo2_egCurvature, auxAttribute);

	// --- controlID::fmo2_panValue
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo2_panValue, auxAttribute);

	// --- controlID::fmo2_panValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo2_panValue, auxAttribute);

	// --- controlID::osc3Core
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::osc3Core, auxAttribute);

	// --- controlID::osc3Core
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::osc3Core, auxAttribute);

	// --- controlID::fmo3_startLevel
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo3_startLevel, auxAttribute);

	// --- controlID::fmo3_attackTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo3_attackTime_mSec, auxAttribute);

	// --- controlID::fmo3_decayTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo3_decayTime_mSec, auxAttribute);

	// --- controlID::fmo3_sustainLevel
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo3_sustainLevel, auxAttribute);

	// --- controlID::fmo3_relaseTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo3_relaseTime_mSec, auxAttribute);

	// --- controlID::fmo3_ModKnobA
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo3_ModKnobA, auxAttribute);

	// --- controlID::fmo3_ModKnobA
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo3_ModKnobA, auxAttribute);

	// --- controlID::fmo3_ModKnobA
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo3_ModKnobA, auxAttribute);

	// --- controlID::fmo3_ModKnobB
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo3_ModKnobB, auxAttribute);

	// --- controlID::fmo3_ModKnobB
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo3_ModKnobB, auxAttribute);

	// --- controlID::fmo3_ModKnobB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo3_ModKnobB, auxAttribute);

	// --- controlID::fmo3_ModKnobC
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo3_ModKnobC, auxAttribute);

	// --- controlID::fmo3_ModKnobC
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo3_ModKnobC, auxAttribute);

	// --- controlID::fmo3_ModKnobC
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo3_ModKnobC, auxAttribute);

	// --- controlID::fmo3_ModKnobD
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo3_ModKnobD, auxAttribute);

	// --- controlID::fmo3_ModKnobD
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo3_ModKnobD, auxAttribute);

	// --- controlID::fmo3_ModKnobD
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo3_ModKnobD, auxAttribute);

	// --- controlID::fmo3_fineDetune
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo3_fineDetune, auxAttribute);

	// --- controlID::fmo3_ratio
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo3_ratio, auxAttribute);

	// --- controlID::fmo3_phaseModIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo3_phaseModIndex, auxAttribute);

	// --- controlID::fmo3_decayLevel
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo3_decayLevel, auxAttribute);

	// --- controlID::fmo3_slopeTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo3_slopeTime_mSec, auxAttribute);

	// --- controlID::fmo3_egCurvature
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo3_egCurvature, auxAttribute);

	// --- controlID::fmo3_panValue
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo3_panValue, auxAttribute);

	// --- controlID::fmo3_panValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo3_panValue, auxAttribute);

	// --- controlID::osc4Core
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::osc4Core, auxAttribute);

	// --- controlID::osc4Core
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::osc4Core, auxAttribute);

	// --- controlID::fmo4_startLevel
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo4_startLevel, auxAttribute);

	// --- controlID::fmo4_attackTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo4_attackTime_mSec, auxAttribute);

	// --- controlID::fmo4_decayTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo4_decayTime_mSec, auxAttribute);

	// --- controlID::fmo4_sustainLevel
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo4_sustainLevel, auxAttribute);

	// --- controlID::fmo4_relaseTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo4_relaseTime_mSec, auxAttribute);

	// --- controlID::fmo4_ModKnobA
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo4_ModKnobA, auxAttribute);

	// --- controlID::fmo4_ModKnobA
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo4_ModKnobA, auxAttribute);

	// --- controlID::fmo4_ModKnobA
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo4_ModKnobA, auxAttribute);

	// --- controlID::fmo4_ModKnobB
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo4_ModKnobB, auxAttribute);

	// --- controlID::fmo4_ModKnobB
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo4_ModKnobB, auxAttribute);

	// --- controlID::fmo4_ModKnobB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo4_ModKnobB, auxAttribute);

	// --- controlID::fmo4_ModKnobC
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo4_ModKnobC, auxAttribute);

	// --- controlID::fmo4_ModKnobC
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo4_ModKnobC, auxAttribute);

	// --- controlID::fmo4_ModKnobC
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo4_ModKnobC, auxAttribute);

	// --- controlID::fmo4_ModKnobD
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo4_ModKnobD, auxAttribute);

	// --- controlID::fmo4_ModKnobD
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo4_ModKnobD, auxAttribute);

	// --- controlID::fmo4_ModKnobD
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo4_ModKnobD, auxAttribute);

	// --- controlID::fmo4_fineDetune
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo4_fineDetune, auxAttribute);

	// --- controlID::fmo4_ratio
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo4_ratio, auxAttribute);

	// --- controlID::fmo4_phaseModIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo4_phaseModIndex, auxAttribute);

	// --- controlID::fmo4_decayLevel
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo4_decayLevel, auxAttribute);

	// --- controlID::fmo4_slopeTime_mSec
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo4_slopeTime_mSec, auxAttribute);

	// --- controlID::fmo4_egCurvature
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo4_egCurvature, auxAttribute);

	// --- controlID::fmo4_panValue
	auxAttribute.reset(65537);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::fmo4_panValue, auxAttribute);

	// --- controlID::fmo4_panValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483689);
	setParamAuxAttribute(controlID::fmo4_panValue, auxAttribute);

	// --- controlID::fmAlgorithm
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::fmAlgorithm, auxAttribute);

	// --- controlID::osc1_waveform
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::osc1_waveform, auxAttribute);

	// --- controlID::osc1_waveform
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::osc1_waveform, auxAttribute);

	// --- controlID::osc2_waveform
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::osc2_waveform, auxAttribute);

	// --- controlID::osc2_waveform
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::osc2_waveform, auxAttribute);

	// --- controlID::osc3_waveform
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::osc3_waveform, auxAttribute);

	// --- controlID::osc3_waveform
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::osc3_waveform, auxAttribute);

	// --- controlID::osc4_waveform
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::osc4_waveform, auxAttribute);

	// --- controlID::osc4_waveform
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::osc4_waveform, auxAttribute);

	// --- controlID::fmo1_EG
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(268435456);
	setParamAuxAttribute(controlID::fmo1_EG, auxAttribute);

	// --- controlID::fmo2_EG
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(268435456);
	setParamAuxAttribute(controlID::fmo2_EG, auxAttribute);

	// --- controlID::fmo3_EG
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(268435456);
	setParamAuxAttribute(controlID::fmo3_EG, auxAttribute);

	// --- controlID::fmo4_EG
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(268435456);
	setParamAuxAttribute(controlID::fmo4_EG, auxAttribute);


	// **--0xEDA5--**
   
    // --- BONUS Parameter
    // --- SCALE_GUI_SIZE
    PluginParameter* piParamBonus = new PluginParameter(SCALE_GUI_SIZE, "Scale GUI", "tiny,small,medium,normal,large,giant", "normal");
    addPluginParameter(piParamBonus);

	// --- create the super fast access array
	initPluginParameterArray();

	// --- DM STUFF --- //
	// --- LFO1
	moduleAuxParamSet lfo1Module(SynthLab::LFO1_SOURCE, SynthLab::LFO1_WAVEFORMS, SynthLab::LFO1_MOD_KNOBS,
		controlID::lfo1Core, controlID::lfo1_waveform,
		controlID::lfo1_ModKnobA, controlID::lfo1_ModKnobB,
		controlID::lfo1_ModKnobC, controlID::lfo1_ModKnobD);

	addModuleParamAtts(lfo1Module);

	// --- LFO2
	moduleAuxParamSet lfo2Module(SynthLab::LFO2_SOURCE, SynthLab::LFO2_WAVEFORMS, SynthLab::LFO2_MOD_KNOBS,
		controlID::lfo2Core, controlID::lfo2_waveform,
		controlID::lfo2_ModKnobA, controlID::lfo2_ModKnobB,
		controlID::lfo2_ModKnobC, controlID::lfo2_ModKnobD);

	addModuleParamAtts(lfo2Module);

	// --- EG1
	moduleAuxParamSet analogEGModule(SynthLab::EG1_SOURCE, SynthLab::EG1_CONTOUR, SynthLab::EG1_MOD_KNOBS,
		controlID::ampEGCore, controlID::ampEGMode,
		controlID::ampEG_ModKnobA, controlID::ampEG_ModKnobB,
		controlID::ampEG_ModKnobC, controlID::ampEG_ModKnobD);

	addModuleParamAtts(analogEGModule);

	// --- EG2
	moduleAuxParamSet filterEGModule(SynthLab::EG2_SOURCE, SynthLab::EG2_CONTOUR, SynthLab::EG2_MOD_KNOBS,
		controlID::filterEGCore, controlID::filterEGMode,
		controlID::filterEG_ModKnobA, controlID::filterEG_ModKnobB,
		controlID::filterEG_ModKnobC, controlID::filterEG_ModKnobD);

	addModuleParamAtts(filterEGModule);

	// --- EG3
	moduleAuxParamSet auxEGModule(SynthLab::EG3_SOURCE, SynthLab::EG3_CONTOUR, SynthLab::EG3_MOD_KNOBS,
		controlID::auxEGCore, controlID::auxEGMode,
		controlID::auxEG_ModKnobA, controlID::auxEG_ModKnobB,
		controlID::auxEG_ModKnobC, controlID::auxEG_ModKnobD);

	addModuleParamAtts(auxEGModule);


	// --- FILTER1 
	moduleAuxParamSet filter1Module(SynthLab::FILTER1_SOURCE, SynthLab::FILTER1_TYPES, SynthLab::FILTER1_MOD_KNOBS,
		controlID::filter1Core, controlID::filter1Algorithm,
		controlID::filter1_ModKnobA, controlID::filter1_ModKnobB,
		controlID::filter1_ModKnobC, controlID::filter1_ModKnobD);

	addModuleParamAtts(filter1Module);

	// --- FILTER2 
	moduleAuxParamSet filter2Module(SynthLab::FILTER2_SOURCE, SynthLab::FILTER2_TYPES, SynthLab::FILTER2_MOD_KNOBS,
		controlID::filter2Core, controlID::filter2Algorithm,
		controlID::filter2_ModKnobA, controlID::filter2_ModKnobB,
		controlID::filter2_ModKnobC, controlID::filter2_ModKnobD);

	addModuleParamAtts(filter2Module);

	// --- OSC1
	moduleAuxParamSet osc1Module(SynthLab::OSC1_SOURCE, SynthLab::OSC1_WAVEFORMS, SynthLab::OSC1_MOD_KNOBS,
		controlID::osc1Core, controlID::osc1_waveform,
		controlID::fmo1_ModKnobA, controlID::fmo1_ModKnobB,
		controlID::fmo1_ModKnobC, controlID::fmo1_ModKnobD);

	addModuleParamAtts(osc1Module);

	// --- OSC2
	moduleAuxParamSet osc2Module(SynthLab::OSC2_SOURCE, SynthLab::OSC2_WAVEFORMS, SynthLab::OSC2_MOD_KNOBS,
		controlID::osc2Core, controlID::osc2_waveform,
		controlID::fmo2_ModKnobA, controlID::fmo2_ModKnobB,
		controlID::fmo2_ModKnobC, controlID::fmo2_ModKnobD);

	addModuleParamAtts(osc2Module);

	// --- OSC3
	moduleAuxParamSet osc3Module(SynthLab::OSC3_SOURCE, SynthLab::OSC3_WAVEFORMS, SynthLab::OSC3_MOD_KNOBS,
		controlID::osc3Core, controlID::osc3_waveform,
		controlID::fmo3_ModKnobA, controlID::fmo3_ModKnobB,
		controlID::fmo3_ModKnobC, controlID::fmo3_ModKnobD);

	addModuleParamAtts(osc3Module);

	// --- OSC4
	moduleAuxParamSet osc4Module(SynthLab::OSC4_SOURCE, SynthLab::OSC4_WAVEFORMS, SynthLab::OSC4_MOD_KNOBS,
		controlID::osc4Core, controlID::osc4_waveform,
		controlID::fmo4_ModKnobA, controlID::fmo4_ModKnobB,
		controlID::fmo4_ModKnobC, controlID::fmo4_ModKnobD);

	addModuleParamAtts(osc4Module);



    return true;
}

/**
\brief initialize object for a new run of audio; called just before audio streams

Operation:
- store sample rate and bit depth on audioProcDescriptor - this information is globally available to all core functions
- reset your member objects here

\param resetInfo structure of information about current audio format

\return true if operation succeeds, false otherwise
*/
bool PluginCore::reset(ResetInfo& resetInfo)
{
    // --- save for audio processing
    audioProcDescriptor.sampleRate = resetInfo.sampleRate;
    audioProcDescriptor.bitDepth = resetInfo.bitDepth;

   	// --- reset engine
	synthEngine->reset(resetInfo.sampleRate);

	// --- other reset inits
    return PluginBase::reset(resetInfo);
}

void PluginCore::enableParamSmoothing(bool enable)
{
	// --- rip through and enable/disable
	for (unsigned int i = 0; i < numPluginParameters; i++)
	{
		if (pluginParameterArray[i])
		{
			pluginParameterArray[i]->setParameterSmoothing(enable);
		}
	}
}

/**
\brief one-time initialize function called after object creation and before the first reset( ) call

Operation:
- saves structure for the plugin to use; you can also load WAV files or state information here
*/
bool PluginCore::initialize(PluginInfo& pluginInfo)
{
	SynthLab::DMConfig config;
	std::string path = pluginInfo.pathToDLL;
	uint32_t count = 0;
	std::string basePath;

	// --- if something is horribly wrong, the synth will revert to normal mode
	//     so this path *can* be null, but it should never be
	if (pluginInfo.pathToDLL)
	{
		// --- format for Mac and Win
		std::string from = "\\";
		std::string to = "/";
		SynthLab::ReplaceSubStrWithStr(path, from, to);

		// --- DM ONLY
		basePath = path;
		dynModuleManager.loadDMConfig(basePath + "/SynthLabModules", config);
	}

	// --- one way, disable only as this rips through all of them
	if (!config.parameterSmoothing)
		enableParamSmoothing(false);

	// --- SYNTH ENGINE CREATION --- //
	//
	// --- prepare output buffers/block size 
	processBlockInfo.blockSize = 64;

	// --- creation mechanism
	synthEngine.reset(new SynthLab::SynthEngine(processBlockInfo.blockSize, &config));

	// --- now try to load the DM modules
	if (pluginInfo.pathToDLL && config.dm_build)
	{
		uint32_t voiceCount = synthEngine->getVoiceCount();
		for (uint32_t i = 0; i < voiceCount; i++)
		{
			count = dynModuleManager.loadAllDynamicModulesInFolder(basePath + "/SynthLabModules");
			// --- load if existing
			if (count > 0 && dynModuleManager.haveDynamicModules())
				synthEngine->setDynamicModules(dynModuleManager.getDynamicModules(), i);
		}
	}

	// --- dynamic string supporting object (this is OPTIONAL and can be omitted for non DM synths)
	dynStringManager.reset(new DynamicStringManager(synthEngine, this));

	// --- these pointers will never change so cache them to save operations
	synthEngine->getParameters(engineParameters);
	voiceParameters = engineParameters->voiceParameters;

	// --- setup audio buffers
	synthBlockProcInfo.init(SynthLab::NO_CHANNELS,			/* num input channels = 0 */
							SynthLab::STEREO_CHANNELS,		/* num output channels = 2 */
							processBlockInfo.blockSize);	/* audio block process size = 64 */

										// --- initializer
	synthEngine->initialize(path.c_str());

	return true;
}

/**
\brief do anything needed prior to arrival of audio buffers

Operation:
- syncInBoundVariables when preProcessAudioBuffers is called, it is *guaranteed* that all GUI control change information
  has been applied to plugin parameters; this binds parameter changes to your underlying variables
- NOTE: postUpdatePluginParameter( ) will be called for all bound variables that are acutally updated; if you need to process
  them individually, do so in that function
- use this function to bulk-transfer the bound variable data into your plugin's member object variables

\param processInfo structure of information about *buffer* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::preProcessAudioBuffers(ProcessBufferInfo& processInfo)
{
    // --- sync internal variables to GUI parameters; you can also do this manually if you don't
    //     want to use the auto-variable-binding
    syncInBoundVariables();

    return true;
}

void PluginCore::updateParameters()
{
	// --- check for new custom waveform strings & mod-knobs
	dynStringManager->setCustomUpdateCodes(voiceParameters->updateCodeDroplists, 
										   voiceParameters->updateCodeKnobs);
	// --- engine
	updateEngineParameters();

	// --- voice
	updateVoiceParameters();
	
	// --- mod matrix 
	updateModMatrixParameters();

	// --- last, set params to do any updates
	synthEngine->setParameters(engineParameters);
}

void PluginCore::updateEngineParameters()
{
	// --- engine level
	engineParameters->globalPitchBendSensCoarse = (unsigned int)globalPitchBendSens; // --- this is pitch bend max range in semitones
	engineParameters->globalPitchBendSensFine = (unsigned int)(100.0*(globalPitchBendSens - engineParameters->globalPitchBendSensCoarse)); // this is pitch bend max range in semitones

	engineParameters->globalTuningCoarse = (unsigned int)globalTuning;
	engineParameters->globalTuningFine = (unsigned int)(100.0*(globalTuning - engineParameters->globalTuningCoarse)); // this is pitch bend max range in semitones

	engineParameters->globalUnisonDetune_Cents = globalUnisonDetune_Cents;
	engineParameters->globalVolume_dB = globalVolume_dB;

	// --- mono/poly, etc...
	engineParameters->synthModeIndex = synthMode;

	// --- delay FX
	engineParameters->enableDelayFX = enableDelayFX == 1;
	engineParameters->audioDelayParameters->leftDelay_mSec = leftDelay_mSec;
	engineParameters->audioDelayParameters->rightDelay_mSec = rightDelay_mSec;
	engineParameters->audioDelayParameters->dryLevel_dB = dryLevel_dB;
	engineParameters->audioDelayParameters->wetLevel_dB = wetLevel_dB;
	engineParameters->audioDelayParameters->feedback_Pct = feedback_Pct;
}

void PluginCore::updateVoiceParameters()
{
	voiceParameters->glideTime_mSec = glideTime_mSec;
	voiceParameters->filterModeIndex = filterModeIndex;

	// --- DM STUFF 
	voiceParameters->lfo1Parameters->moduleIndex = lfo1Core;
	voiceParameters->lfo2Parameters->moduleIndex = lfo2Core;

	voiceParameters->ampEGParameters->moduleIndex = ampEGCore;
	voiceParameters->filterEGParameters->moduleIndex = filterEGCore;
	voiceParameters->auxEGParameters->moduleIndex = auxEGCore;

	voiceParameters->filter1Parameters->moduleIndex = filter1Core;
	voiceParameters->filter2Parameters->moduleIndex = filter2Core;
	
	// --- OSC BLOCK
	voiceParameters->osc1Parameters->moduleIndex = osc1Core;
	voiceParameters->osc2Parameters->moduleIndex = osc2Core;
	voiceParameters->osc3Parameters->moduleIndex = osc3Core;
	voiceParameters->osc4Parameters->moduleIndex = osc4Core;

	// --- the one and only algorithm
	voiceParameters->fmAlgorithmIndex = fmAlgorithm;

	// --- FMO1
	voiceParameters->osc1Parameters->panValue = fmo1_panValue;
	voiceParameters->osc1Parameters->dxEGParameters.startLevel = fmo1_startLevel;
	voiceParameters->osc1Parameters->dxEGParameters.attackTime_mSec = fmo1_attackTime_mSec;
	voiceParameters->osc1Parameters->dxEGParameters.decayTime_mSec = fmo1_decayTime_mSec;
	voiceParameters->osc1Parameters->dxEGParameters.decayLevel = fmo1_decayLevel;
	voiceParameters->osc1Parameters->dxEGParameters.slopeTime_mSec = fmo1_slopeTime_mSec;
	voiceParameters->osc1Parameters->dxEGParameters.sustainLevel = fmo1_sustainLevel;
	voiceParameters->osc1Parameters->dxEGParameters.releaseTime_mSec = fmo1_relaseTime_mSec;
	voiceParameters->osc1Parameters->dxEGParameters.curvature = fmo1_egCurvature;
	voiceParameters->osc1Parameters->phaseModIndex = fmo1_phaseModIndex;
	voiceParameters->osc1Parameters->ratio = fmo1_ratio;
	voiceParameters->osc1Parameters->fineDetune = fmo1_fineDetune;

	voiceParameters->osc1Parameters->modKnobValue[0] = fmo1_ModKnobA;
	voiceParameters->osc1Parameters->modKnobValue[1] = fmo1_ModKnobB;
	voiceParameters->osc1Parameters->modKnobValue[2] = fmo1_ModKnobC;
	voiceParameters->osc1Parameters->modKnobValue[3] = fmo1_ModKnobD;

	// --- FMO2
	voiceParameters->osc2Parameters->panValue = fmo2_panValue;
	voiceParameters->osc2Parameters->dxEGParameters.startLevel = fmo2_startLevel;
	voiceParameters->osc2Parameters->dxEGParameters.attackTime_mSec = fmo2_attackTime_mSec;
	voiceParameters->osc2Parameters->dxEGParameters.decayTime_mSec = fmo2_decayTime_mSec;
	voiceParameters->osc2Parameters->dxEGParameters.decayLevel = fmo2_decayLevel;
	voiceParameters->osc2Parameters->dxEGParameters.slopeTime_mSec = fmo2_slopeTime_mSec;
	voiceParameters->osc2Parameters->dxEGParameters.sustainLevel = fmo2_sustainLevel;
	voiceParameters->osc2Parameters->dxEGParameters.releaseTime_mSec = fmo2_relaseTime_mSec;
	voiceParameters->osc2Parameters->dxEGParameters.curvature = fmo2_egCurvature;
	voiceParameters->osc2Parameters->phaseModIndex = fmo2_phaseModIndex;
	voiceParameters->osc2Parameters->ratio = fmo2_ratio;
	voiceParameters->osc2Parameters->fineDetune = fmo2_fineDetune;

	voiceParameters->osc2Parameters->modKnobValue[0] = fmo2_ModKnobA;
	voiceParameters->osc2Parameters->modKnobValue[1] = fmo2_ModKnobB;
	voiceParameters->osc2Parameters->modKnobValue[2] = fmo2_ModKnobC;
	voiceParameters->osc2Parameters->modKnobValue[3] = fmo2_ModKnobD;

	// --- FMO3
	voiceParameters->osc3Parameters->panValue = fmo3_panValue;
	voiceParameters->osc3Parameters->dxEGParameters.startLevel = fmo3_startLevel;
	voiceParameters->osc3Parameters->dxEGParameters.attackTime_mSec = fmo3_attackTime_mSec;
	voiceParameters->osc3Parameters->dxEGParameters.decayTime_mSec = fmo3_decayTime_mSec;
	voiceParameters->osc3Parameters->dxEGParameters.decayLevel = fmo3_decayLevel;
	voiceParameters->osc3Parameters->dxEGParameters.slopeTime_mSec = fmo3_slopeTime_mSec;
	voiceParameters->osc3Parameters->dxEGParameters.sustainLevel = fmo3_sustainLevel;
	voiceParameters->osc3Parameters->dxEGParameters.releaseTime_mSec = fmo3_relaseTime_mSec;
	voiceParameters->osc3Parameters->dxEGParameters.curvature = fmo3_egCurvature;
	voiceParameters->osc3Parameters->phaseModIndex = fmo3_phaseModIndex;
	voiceParameters->osc3Parameters->ratio = fmo3_ratio;
	voiceParameters->osc3Parameters->fineDetune = fmo3_fineDetune;

	voiceParameters->osc3Parameters->modKnobValue[0] = fmo3_ModKnobA;
	voiceParameters->osc3Parameters->modKnobValue[1] = fmo3_ModKnobB;
	voiceParameters->osc3Parameters->modKnobValue[2] = fmo3_ModKnobC;
	voiceParameters->osc3Parameters->modKnobValue[3] = fmo3_ModKnobD;

	// --- FMO4
	voiceParameters->osc4Parameters->panValue = fmo4_panValue;
	voiceParameters->osc4Parameters->dxEGParameters.startLevel = fmo4_startLevel;
	voiceParameters->osc4Parameters->dxEGParameters.attackTime_mSec = fmo4_attackTime_mSec;
	voiceParameters->osc4Parameters->dxEGParameters.decayTime_mSec = fmo4_decayTime_mSec;
	voiceParameters->osc4Parameters->dxEGParameters.decayLevel = fmo4_decayLevel;
	voiceParameters->osc4Parameters->dxEGParameters.slopeTime_mSec = fmo4_slopeTime_mSec;
	voiceParameters->osc4Parameters->dxEGParameters.sustainLevel = fmo4_sustainLevel;
	voiceParameters->osc4Parameters->dxEGParameters.releaseTime_mSec = fmo4_relaseTime_mSec;
	voiceParameters->osc4Parameters->dxEGParameters.curvature = fmo4_egCurvature;
	voiceParameters->osc4Parameters->phaseModIndex = fmo4_phaseModIndex;
	voiceParameters->osc4Parameters->ratio = fmo4_ratio;
	voiceParameters->osc4Parameters->fineDetune = fmo4_fineDetune;

	voiceParameters->osc4Parameters->modKnobValue[0] = fmo4_ModKnobA;
	voiceParameters->osc4Parameters->modKnobValue[1] = fmo4_ModKnobB;
	voiceParameters->osc4Parameters->modKnobValue[2] = fmo4_ModKnobC;
	voiceParameters->osc4Parameters->modKnobValue[3] = fmo4_ModKnobD;

	// --- LFO1
	voiceParameters->lfo1Parameters->waveformIndex = lfo1_waveform;
	voiceParameters->lfo1Parameters->modeIndex = lfo1_mode;
	voiceParameters->lfo1Parameters->frequency_Hz = lfo1_frequency_Hz;
	voiceParameters->lfo1Parameters->outputAmplitude = lfo1_outputAmplitude;
	voiceParameters->lfo1Parameters->quantize = lfo1_quantize;
	voiceParameters->lfo1Parameters->modKnobValue[0] = lfo1_ModKnobA;
	voiceParameters->lfo1Parameters->modKnobValue[1] = lfo1_ModKnobB;
	voiceParameters->lfo1Parameters->modKnobValue[2] = lfo1_ModKnobC;
	voiceParameters->lfo1Parameters->modKnobValue[3] = lfo1_ModKnobD;

	// --- LFO2
	voiceParameters->lfo2Parameters->waveformIndex = lfo2_waveform;
	voiceParameters->lfo2Parameters->modeIndex = lfo2_mode;
	voiceParameters->lfo2Parameters->frequency_Hz = lfo2_frequency_Hz;
	voiceParameters->lfo2Parameters->outputAmplitude = lfo2_outputAmplitude;
	voiceParameters->lfo2Parameters->quantize = lfo2_quantize;
	voiceParameters->lfo2Parameters->modKnobValue[0] = lfo2_ModKnobA;
	voiceParameters->lfo2Parameters->modKnobValue[1] = lfo2_ModKnobB;
	voiceParameters->lfo2Parameters->modKnobValue[2] = lfo2_ModKnobC;
	voiceParameters->lfo2Parameters->modKnobValue[3] = lfo2_ModKnobD;

	// --- AMP EG
	voiceParameters->ampEGParameters->egContourIndex = ampEGMode;
	voiceParameters->ampEGParameters->attackTime_mSec = ampEG_attackTime_mSec;
	voiceParameters->ampEGParameters->decayTime_mSec = ampEG_decayTime_mSec;
	voiceParameters->ampEGParameters->sustainLevel = ampEG_sustainLevel;
	voiceParameters->ampEGParameters->releaseTime_mSec = ampEG_releaseTime_mSec;
	voiceParameters->ampEGParameters->modKnobValue[0] = ampEG_ModKnobA;
	voiceParameters->ampEGParameters->modKnobValue[1] = ampEG_ModKnobB;
	voiceParameters->ampEGParameters->modKnobValue[2] = ampEG_ModKnobC;
	voiceParameters->ampEGParameters->modKnobValue[3] = ampEG_ModKnobD;

	// --- FILTER EG
	voiceParameters->filterEGParameters->egContourIndex = filterEGMode;
	voiceParameters->filterEGParameters->attackTime_mSec = filterEG_attackTime_mSec;
	voiceParameters->filterEGParameters->decayTime_mSec = filterEG_decayTime_mSec;
	voiceParameters->filterEGParameters->sustainLevel = filterEG_sustainLevel;
	voiceParameters->filterEGParameters->releaseTime_mSec = filterEG_releaseTime_mSec;
	voiceParameters->filterEGParameters->modKnobValue[0] = filterEG_ModKnobA;
	voiceParameters->filterEGParameters->modKnobValue[1] = filterEG_ModKnobB;
	voiceParameters->filterEGParameters->modKnobValue[2] = filterEG_ModKnobC;
	voiceParameters->filterEGParameters->modKnobValue[3] = filterEG_ModKnobD;

	// --- AUX EG
	voiceParameters->auxEGParameters->egContourIndex = auxEGMode;
	voiceParameters->auxEGParameters->attackTime_mSec = auxEG_attackTime_mSec;
	voiceParameters->auxEGParameters->decayTime_mSec = auxEG_decayTime_mSec;
	voiceParameters->auxEGParameters->sustainLevel = auxEG_sustainLevel;
	voiceParameters->auxEGParameters->releaseTime_mSec = auxEG_releaseTime_mSec;
	voiceParameters->auxEGParameters->modKnobValue[0] = auxEG_ModKnobA;
	voiceParameters->auxEGParameters->modKnobValue[1] = auxEG_ModKnobB;
	voiceParameters->auxEGParameters->modKnobValue[2] = auxEG_ModKnobC;
	voiceParameters->auxEGParameters->modKnobValue[3] = auxEG_ModKnobD;

	// --- FILTER 1
	voiceParameters->filter1Parameters->filterIndex = filter1Algorithm;
	voiceParameters->filter1Parameters->fc = filter1_fc;
	voiceParameters->filter1Parameters->Q = filter1_Q;
	voiceParameters->filter1Parameters->enableKeyTrack = enableFilter1KeyTrack == 1;
	voiceParameters->filter1Parameters->filterOutputGain_dB = filter1Output_dB;

	voiceParameters->filter1Parameters->modKnobValue[0] = filter1_ModKnobA;
	voiceParameters->filter1Parameters->modKnobValue[1] = filter1_ModKnobB;
	voiceParameters->filter1Parameters->modKnobValue[2] = filter1_ModKnobC;
	voiceParameters->filter1Parameters->modKnobValue[3] = filter1_ModKnobD;

	// --- FILTER 2
	voiceParameters->filter2Parameters->filterIndex = filter2Algorithm;
	voiceParameters->filter2Parameters->fc = filter2_fc;
	voiceParameters->filter2Parameters->Q = filter2_Q;
	voiceParameters->filter2Parameters->enableKeyTrack = enableFilter2KeyTrack == 1;
	voiceParameters->filter2Parameters->filterOutputGain_dB = filter2Output_dB;

	voiceParameters->filter2Parameters->modKnobValue[0] = filter2_ModKnobA;
	voiceParameters->filter2Parameters->modKnobValue[1] = filter2_ModKnobB;
	voiceParameters->filter2Parameters->modKnobValue[2] = filter2_ModKnobC;
	voiceParameters->filter2Parameters->modKnobValue[3] = filter2_ModKnobD;

	// --- DCA
	voiceParameters->dcaParameters->ampEGIntensity = ampEGIntensity;
}

void PluginCore::updateModMatrixParameters()
{
	// --- MOD MATRIX
	//
	// --- Source Intensities
	voiceParameters->modMatrixParameters->setMM_SourceIntensity(SynthLab::kSourceLFO1_Norm, lfo1SourceInt);
	voiceParameters->modMatrixParameters->setMM_SourceIntensity(SynthLab::kSourceLFO2_Norm, lfo2SourceInt);
	voiceParameters->modMatrixParameters->setMM_SourceIntensity(SynthLab::kSourceFilterEG_Norm, filterEGSourceInt);
	voiceParameters->modMatrixParameters->setMM_SourceIntensity(SynthLab::kSourceAuxEG_Norm, auxEGSourceInt);
	voiceParameters->modMatrixParameters->setMM_SourceIntensity(SynthLab::kSourceAuxEG_Bias, auxEGBiasedSourceInt);

	// --- Destination Intensities
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestLFO2_fo, lfo2_fo_Int);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc1_fo, osc123_fo_Int);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc2_fo, osc123_fo_Int);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc3_fo, osc123_fo_Int);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc4_fo, osc4_fo_Int);

	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc1_Mod, osc123_Mod_Int);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc2_Mod, osc123_Mod_Int);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc3_Mod, osc123_Mod_Int);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc4_Mod, osc4_Mod_Int);

	// --- using intensity for both
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestFilter1_fc_Bipolar, filter1_fc_Int);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestFilter2_fc_Bipolar, filter2_fc_Int);

	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestFilter1_fc_EG, filter1_fc_Int);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestFilter2_fc_EG, filter2_fc_Int);

	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestAmpEGRetrigger, ampEGTrigInt);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestDCA_PanMod, dcaPanInt);


	// --- ROW 1 ------------------------------------------------------------------------------
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestLFO2_fo, (lfo1_lfo2_fc == 1));

	bool enable = (lfo1_osc123_fc == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc1_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc2_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc3_fo, enable);

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc4_fo, (lfo1_osc04_fc == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestAmpEGRetrigger, (lfo1_ampEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestDCA_PanMod, (lfo1_dcaPan == 1));

	enable = (lfo1_osc123_Mod == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc1_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc2_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc3_Mod, enable);

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc4_Mod, (lfo1_osc04_Mod == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestFilter1_fc_Bipolar, (lfo1_filter1_fc == 1));
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestFilter2_fc_Bipolar, (lfo1_filter2_fc == 1));
	// ----------------------------------------------------------------------------------------

	// --- ROW 2 ------------------------------------------------------------------------------
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestLFO2_fo, (lfo2_lfo2_fc == 1));

	enable = (lfo2_osc123_fc == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc1_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc2_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc3_fo, enable);

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc4_fo, (lfo2_osc04_fc == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestAmpEGRetrigger, (lfo2_ampEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestDCA_PanMod, (lfo2_dcaPan == 1));

	enable = (lfo2_osc123_Mod == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc1_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc2_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc3_Mod, enable);

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc4_Mod, (lfo2_osc04_Mod == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestFilter1_fc_Bipolar, (lfo2_filter1_fc == 1));
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestFilter2_fc_Bipolar, (lfo2_filter2_fc == 1));
	// ----------------------------------------------------------------------------------------

	// --- ROW 3 ------------------------------------------------------------------------------
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestLFO2_fo, (filterEG_lfo2_fc == 1));

	enable = (filterEG_osc123_fc == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc1_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc2_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc3_fo, enable);

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc4_fo, filterEG_osc04_fc == 1);

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestDCA_PanMod, (filterEG_dcaPan == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestAmpEGRetrigger, (filterEG_ampEGTrig == 1));

	enable = (filterEG_osc123_Mod == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc1_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc2_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc3_Mod, enable);

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc4_Mod, (filterEG_osc04_Mod == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestFilter1_fc_EG, (filterEG_filter1_fc == 1));
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestFilter2_fc_EG, (filterEG_filter2_fc == 1));
	// ----------------------------------------------------------------------------------------



	// --- ROW 4 ------------------------------------------------------------------------------
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestLFO2_fo, (auxEG_lfo2_fc == 1));

	enable = (auxEG_osc123_fc == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc1_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc2_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc3_fo, enable);

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc4_fo, auxEG_osc04_fc == 1);

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestDCA_PanMod, (auxEG_dcaPan == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestAmpEGRetrigger, (auxEG_ampEGTrig == 1));

	enable = (auxEG_osc123_Mod == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc1_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc2_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc3_Mod, enable);

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc4_Mod, (auxEG_osc04_Mod == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestFilter1_fc_Bipolar, (auxEG_filter1_fc == 1));
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestFilter2_fc_Bipolar, (auxEG_filter2_fc == 1));
	// ----------------------------------------------------------------------------------------

	// --- ROW 5 ------------------------------------------------------------------------------
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestLFO2_fo, (auxEGB_lfo2_fc == 1));

	enable = (auxEGB_osc123_fc == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc1_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc2_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc3_fo, enable);

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc4_fo, auxEGB_osc04_fc == 1);

	//enable = (auxEGB_osc123_Shp == 1);
	//voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
	//	SynthLab::kDestOsc1_Shape, enable);
	//voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
	//	SynthLab::kDestOsc2_Shape, enable);
	//voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
	//	SynthLab::kDestOsc3_Shape, enable);

	//voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
	//	SynthLab::kDestOsc4_Shape, (auxEGB_osc04_Shp == 1));
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestAmpEGRetrigger, (auxEGB_ampEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestDCA_PanMod, (auxEGB_dcaPan == 1));

	enable = (auxEGB_osc123_Mod == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc1_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc2_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc3_Mod, enable);

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc4_Mod, (auxEGB_osc04_Mod == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestFilter1_fc_Bipolar, (auxEGB_filter1_fc == 1));
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestFilter2_fc_Bipolar, (auxEGB_filter2_fc == 1));
	// ----------------------------------------------------------------------------------------
}

// --------------------------------------------
/**
\brief buffer-processing method

Operation:
- this is specialized to break the buffers into blocks
- calculates the number of blocks in a buffer
- uses array pointers and offset values to encode the block
- sets up look to call the block processing code
- see the block processing code for continuation

\param processBufferInfo structure of information about *buffer* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processAudioBuffers(ProcessBufferInfo& processBufferInfo)
{
	double sampleInterval = 1.0 / audioProcDescriptor.sampleRate;

	// --- sync internal bound variables
	preProcessAudioBuffers(processBufferInfo);

	// --- calculate blocks & partial blocks
	div_t blockDiv = div((int)processBufferInfo.numFramesToProcess, processBlockInfo.blockSize);
	int blocksPerBuffer = blockDiv.quot;
	int partialBlockSize = blockDiv.rem;

	processBlockInfo.inputs = processBufferInfo.inputs;
	processBlockInfo.outputs = processBufferInfo.outputs;
	processBlockInfo.auxInputs = processBufferInfo.auxInputs;
	processBlockInfo.auxOutputs = processBufferInfo.auxOutputs;

	processBlockInfo.numAudioInChannels = processBufferInfo.numAudioInChannels;
	processBlockInfo.numAudioOutChannels = processBufferInfo.numAudioOutChannels;
	processBlockInfo.numAuxAudioInChannels = processBufferInfo.numAuxAudioInChannels;
	processBlockInfo.numAuxAudioOutChannels = processBufferInfo.numAuxAudioOutChannels;

	processBlockInfo.hostInfo = processBufferInfo.hostInfo;
	processBlockInfo.midiEventQueue = processBufferInfo.midiEventQueue;

	// --- build blocks one block for each channel
	for (uint32_t block = 0; block < blocksPerBuffer; block++)
	{
		processBlockInfo.currentBlock = block;
		processBlockInfo.blockStartIndex = block * processBlockInfo.blockSize;

		// --- do the block
		processAudioBlock(processBlockInfo);

		// --- update per-frame
		processBlockInfo.hostInfo->uAbsoluteFrameBufferIndex += processBlockInfo.blockSize;
		processBlockInfo.hostInfo->dAbsoluteFrameBufferTime += (processBlockInfo.blockSize * sampleInterval);
	}

	// --- process partial blocks; note downstream objects may need their own buffering method
	if (partialBlockSize > 0)
	{
		processBlockInfo.blockSize = partialBlockSize;
		processBlockInfo.currentBlock = blocksPerBuffer;
		processBlockInfo.blockStartIndex = processBufferInfo.numFramesToProcess - processBlockInfo.blockSize;

		// --- do the block
		processAudioBlock(processBlockInfo);
	}

	// --- generally not used
	postProcessAudioBuffers(processBufferInfo);

	return false; /// processed
}

/**
\brief block-processing method

Operation:
- fire all MIDI events for the block
- do parameter smoothing 
- perform block processing (FX or render synth)

\param processBlockInfo structure of information about *block* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processAudioBlock(ProcessBlockInfo& processBlockInfo)
{
	// --- clear MIDI events at top of buffer
	synthBlockProcInfo.clearMidiEvents();
	synthBlockProcInfo.absoluteBufferTime_Sec = processBlockInfo.hostInfo->dAbsoluteFrameBufferTime;
	synthBlockProcInfo.BPM = processBlockInfo.hostInfo->dBPM;
	synthBlockProcInfo.timeSigNumerator = processBlockInfo.hostInfo->fTimeSigNumerator;
	synthBlockProcInfo.timeSigDenomintor = processBlockInfo.hostInfo->uTimeSigDenomintor;

	// --- fire ALL MIDI events for this block
	for (uint32_t sample = processBlockInfo.blockStartIndex;
		sample < processBlockInfo.blockStartIndex + processBlockInfo.blockSize;
		sample++)
	{
		// --- this is for non-sample accurate MIDI
		processBlockInfo.midiEventQueue->fireMidiEvents(sample);

		// --- do per-frame updates; VST automation and parameter smoothing
		doSampleAccurateParameterUpdates();
	}

	// --- update parameters
	updateParameters();
	
	// --- in case of partial block
	synthBlockProcInfo.setSamplesInBlock(processBlockInfo.blockSize);

	// --- render it
	synthEngine->render(synthBlockProcInfo);

	// --- output 
	float** synthOutputs = synthBlockProcInfo.getOutputBuffers();

	// --- block processing -- write to outputs
	for (uint32_t sample = processBlockInfo.blockStartIndex, i = 0; 
		 sample < processBlockInfo.blockStartIndex + processBlockInfo.blockSize; 
		 sample++, i++)
	{
		// --- copy to outputs
		for (uint32_t channel = 0; channel < processBlockInfo.numAudioOutChannels; channel++)
		{
			processBlockInfo.outputs[channel][sample] = synthOutputs[channel][i];
		}
	}
	
	return true;
}


/**
\brief frame-processing method

Operation:
- decode the plugin type - for synth plugins, fill in the rendering code; for FX plugins, delete the if(synth) portion and add your processing code
- note that MIDI events are fired for each sample interval so that MIDI is tightly sunk with audio
- doSampleAccurateParameterUpdates will perform per-sample interval smoothing

\param processFrameInfo structure of information about *frame* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processAudioFrame(ProcessFrameInfo& processFrameInfo)
{
    // --- fire any MIDI events for this sample interval
    processFrameInfo.midiEventQueue->fireMidiEvents(processFrameInfo.currentFrame);

	// --- do per-frame updates; VST automation and parameter smoothing
	doSampleAccurateParameterUpdates();

    // --- decode the channelIOConfiguration and process accordingly
    //
	// --- Synth Plugin:
	// --- Synth Plugin --- remove for FX plugins
	if (getPluginType() == kSynthPlugin)
	{
		// --- output silence: change this with your signal render code
		processFrameInfo.audioOutputFrame[0] = 0.0;
		if (processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
			processFrameInfo.audioOutputFrame[1] = 0.0;

		return true;	/// processed
	}

    // --- FX Plugin:
    if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFMono &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFMono)
    {
		// --- pass through code: change this with your signal processing
        processFrameInfo.audioOutputFrame[0] = processFrameInfo.audioInputFrame[0];

        return true; /// processed
    }

    // --- Mono-In/Stereo-Out
    else if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFMono &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
    {
		// --- pass through code: change this with your signal processing
        processFrameInfo.audioOutputFrame[0] = processFrameInfo.audioInputFrame[0];
        processFrameInfo.audioOutputFrame[1] = processFrameInfo.audioInputFrame[0];

        return true; /// processed
    }

    // --- Stereo-In/Stereo-Out
    else if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFStereo &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
    {
		// --- pass through code: change this with your signal processing
        processFrameInfo.audioOutputFrame[0] = processFrameInfo.audioInputFrame[0];
        processFrameInfo.audioOutputFrame[1] = processFrameInfo.audioInputFrame[1];

        return true; /// processed
    }

    return false; /// NOT processed
}


/**
\brief do anything needed prior to arrival of audio buffers

Operation:
- updateOutBoundVariables sends metering data to the GUI meters

\param processInfo structure of information about *buffer* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::postProcessAudioBuffers(ProcessBufferInfo& processInfo)
{
	// --- update outbound variables; currently this is meter data only, but could be extended
	//     in the future
	updateOutBoundVariables();

    return true;
}

/**
\brief update the PluginParameter's value based on GUI control, preset, or data smoothing (thread-safe)

Operation:
- update the parameter's value (with smoothing this initiates another smoothing process)
- call postUpdatePluginParameter to do any further processing

\param controlID the control ID value of the parameter being updated
\param controlValue the new control value
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::updatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo)
{
    // --- use base class helper
    setPIParamValue(controlID, controlValue);

    // --- do any post-processing
    postUpdatePluginParameter(controlID, controlValue, paramInfo);

    return true; /// handled
}

/**
\brief update the PluginParameter's value based on *normlaized* GUI control, preset, or data smoothing (thread-safe)

Operation:
- update the parameter's value (with smoothing this initiates another smoothing process)
- call postUpdatePluginParameter to do any further processing

\param controlID the control ID value of the parameter being updated
\param normalizedValue the new control value in normalized form
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::updatePluginParameterNormalized(int32_t controlID, double normalizedValue, ParameterUpdateInfo& paramInfo)
{
	// --- use base class helper, returns actual value
	double controlValue = setPIParamValueNormalized(controlID, normalizedValue, paramInfo.applyTaper);

	// --- do any post-processing
	postUpdatePluginParameter(controlID, controlValue, paramInfo);

	return true; /// handled
}

/**
\brief perform any operations after the plugin parameter has been updated; this is one paradigm for
	   transferring control information into vital plugin variables or member objects. If you use this
	   method you can decode the control ID and then do any cooking that is needed. NOTE: do not
	   overwrite bound variables here - this is ONLY for any extra cooking that is required to convert
	   the GUI data to meaninful coefficients or other specific modifiers.

\param controlID the control ID value of the parameter being updated
\param controlValue the new control value
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::postUpdatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo)
{
    // --- now do any post update cooking; be careful with VST Sample Accurate automation
    //     If enabled, then make sure the cooking functions are short and efficient otherwise disable it
    //     for the Parameter involved
    /*switch(controlID)
    {
        case 0:
        {
            return true;    /// handled
        }

        default:
            return false;   /// not handled
    }*/

    return false;
}

/**
\brief has nothing to do with actual variable or updated variable (binding)

CAUTION:
- DO NOT update underlying variables here - this is only for sending GUI updates or letting you
  know that a parameter was changed; it should not change the state of your plugin.

WARNING:
- THIS IS NOT THE PREFERRED WAY TO LINK OR COMBINE CONTROLS TOGETHER. THE PROPER METHOD IS
  TO USE A CUSTOM SUB-CONTROLLER THAT IS PART OF THE GUI OBJECT AND CODE.
  SEE http://www.willpirkle.com for more information

\param controlID the control ID value of the parameter being updated
\param actualValue the new control value

\return true if operation succeeds, false otherwise
*/
bool PluginCore::guiParameterChanged(int32_t controlID, double actualValue)
{
	/*
	switch (controlID)
	{
		case controlID::<your control here>
		{

			return true; // handled
		}

		default:
			break;
	}*/

	return false; /// not handled
}

/**
\brief For Custom View and Custom Sub-Controller Operations

NOTES:
- this is for advanced users only to implement custom view and custom sub-controllers
- see the SDK for examples of use

\param messageInfo a structure containing information about the incoming message

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processMessage(MessageInfo& messageInfo)
{
	// --- decode message
	switch (messageInfo.message)
	{
		// --- add customization appearance here
		case PLUGINGUI_DIDOPEN:
		{
			// --- enable it
			dynStringManager->enableCustomViewDataQueue(true);

			// --- load up the first set of waveform strings
			synthEngine->setAllCustomUpdateCodes();
		
			return true;
		}

		// --- NULL pointers so that we don't accidentally use them
		case PLUGINGUI_WILLCLOSE:
		{
			dynStringManager->enableCustomViewDataQueue(false);
			return true;
		}

		// --- update view; this will only be called if the GUI is actually open
		case PLUGINGUI_TIMERPING:
		{
			if (dynStringManager->haveCustomUpdates())
			{
				for (uint32_t i = 0; i < TOTAL_CUSTOM_VIEWS; i++)
				{
					dynStringManager->updateCustomView(i);
				}
				dynStringManager->enableCustomUpdates(false);
			}

			return true;
		}

		// --- register the custom view, grab the ICustomView interface
		case PLUGINGUI_REGISTER_CUSTOMVIEW:
		{
			// --- enable the queue
			dynStringManager->enableCustomViewDataQueue(true);

			// --- RackAFX Support --- //
			if (messageInfo.inMessageString.compare("RAFX2_DynamicLabel") == 0)
			{
				uint32_t* controlID = (uint32_t*)(messageInfo.outMessageData);
				return dynStringManager->setModKnobLabelView(*controlID, static_cast<ICustomView*>(messageInfo.inMessageData), true);
			}
			if (messageInfo.inMessageString.compare("RAFX2_DynamicMenu") == 0)
			{
				uint32_t* controlIDPtr = (uint32_t*)(messageInfo.outMessageData);
				if (!controlIDPtr)
					return false;

				if (isSubModuleOptionMenu(*controlIDPtr))
				{
					ICustomView* view = static_cast<ICustomView*>(messageInfo.inMessageData);
					if (!view) return false;

					uint32_t moduleType = getSubModuleType(*controlIDPtr);
					if (moduleType == SynthLab::UNDEFINED_MODULE) return false;

					std::vector<std::string> moduleStrings = dynStringManager->getModuleCoreNames(moduleType);

					VSTGUI::RAFX2CustomViewMessage viewMessage;

					// --- send the view the data as a string
					viewMessage.message = VSTGUI::MESSAGE_SET_STRINGLIST;
					viewMessage.stringCount = moduleStrings.size();

					char** arr = new char*[moduleStrings.size()];
					for (size_t i = 0; i < moduleStrings.size(); i++)
					{
						arr[i] = new char[moduleStrings[i].size() + 1];
						strcpy(arr[i], moduleStrings[i].c_str());
					}

					viewMessage.stringList = arr;

					// --- send the message (same thread)
					view->sendMessage(&viewMessage);

					// --- clean up 
					for (size_t i = 0; i < moduleStrings.size(); i++)
					{
						delete[] arr[i];
					}
					delete[] arr;

					// --- tell view to repaint 
					view->updateView();

					// --- save in database
					dynStringManager->setCustomDroplistView(*controlIDPtr, static_cast<ICustomView*>(messageInfo.inMessageData), true, true);

					return true;
				}
				else // is waveform dropdown
					return dynStringManager->setCustomDroplistView(*controlIDPtr, static_cast<ICustomView*>(messageInfo.inMessageData), true, false);
			}

			if (messageInfo.inMessageString.find("ASPiK_DynamicLabel") != std::string::npos)
			{
				int x = (int)messageInfo.inMessageString.find("_CID");
				int len = (int)messageInfo.inMessageString.length();
				if (x < 0 || len < 0)
					return false;

				std::string strID = messageInfo.inMessageString.substr(x + 4, len - 4 - x);
				uint32_t controlID = stoul(strID, 0, 10);

				return dynStringManager->setModKnobLabelView(controlID, static_cast<ICustomView*>(messageInfo.inMessageData), false);
			}

			if (messageInfo.inMessageString.find("ASPiK_DynamicMenu") != std::string::npos)
			{
				int x = (int)messageInfo.inMessageString.find("_CID");
				int len = (int)messageInfo.inMessageString.length();
				if (x < 0 || len < 0)
					return false;

				std::string strID = messageInfo.inMessageString.substr(x + 4, len - 4 - x);
				uint32_t controlID = stoul(strID, 0, 10);

				if (isSubModuleOptionMenu(controlID))
				{
					ICustomView* view = static_cast<ICustomView*>(messageInfo.inMessageData);
					if (!view) return false;

					uint32_t moduleType = getSubModuleType(controlID);
					if (moduleType == SynthLab::UNDEFINED_MODULE) return false;

					std::vector<std::string> moduleStrings = dynStringManager->getModuleCoreNames(moduleType);

					VSTGUI::TextDisplayViewMessage viewMessage;

					// --- send the view the data as a string
					viewMessage.message = VSTGUI::MESSAGE_SET_STRINGLIST;
					viewMessage.stringList = moduleStrings;
					PluginParameter* piparam = getPluginParameterByControlID(controlID);
					if (!piparam)
						return false;

					viewMessage.controlStringCount = piparam->getStringCount();

					// --- send the message (same thread)
					view->sendMessage(&viewMessage);

					// --- tell view to repaint 
					view->updateView();

					// --- save in database
					dynStringManager->setCustomDroplistView(controlID, static_cast<ICustomView*>(messageInfo.inMessageData), false, true);

					return true;
				}
				else // is waveform dropdown
					return dynStringManager->setCustomDroplistView(controlID, static_cast<ICustomView*>(messageInfo.inMessageData), false, false);
			}

			return true;
		}

		case PLUGINGUI_QUERY_HASUSERCUSTOM:
		{
			if (messageInfo.inMessageString.compare("GUI_PANEL_WILL_CHANGE") == 0)
				dynStringManager->clearCustomViewInfo();

			return true;
		}

		case PLUGINGUI_REGISTER_SUBCONTROLLER:
		case PLUGINGUI_USER_CUSTOMOPEN:
		case PLUGINGUI_USER_CUSTOMCLOSE:
		case PLUGINGUI_EXTERNAL_SET_NORMVALUE:
		case PLUGINGUI_EXTERNAL_SET_ACTUALVALUE:
		{

			return false;
		}

		default:
			break;
	}

	return false; /// not handled
}


/**
\brief process a MIDI event

NOTES:
- MIDI events are 100% sample accurate; this function will be called repeatedly for every MIDI message
- see the SDK for examples of use

\param event a structure containing the MIDI event data

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processMIDIEvent(midiEvent& event)
{	// --- push to queue for block processing
	SynthLab::midiEvent synthEvent(event.midiMessage,
		event.midiChannel, event.midiData1, event.midiData2,
		event.midiSampleOffset);

	// --- push into vector
	synthBlockProcInfo.pushMidiEvent(synthEvent);



	return true;
}

/**
\brief (for future use)

NOTES:
- MIDI events are 100% sample accurate; this function will be called repeatedly for every MIDI message
- see the SDK for examples of use

\param vectorJoysickData a structure containing joystick data

\return true if operation succeeds, false otherwise
*/
bool PluginCore::setVectorJoystickParameters(const VectorJoystickData& vectorJoysickData)
{
	return true;
}

/**
\brief use this method to add new presets to the list

NOTES:
- see the SDK for examples of use
- for non RackAFX users that have large paramter counts, there is a secret GUI control you
  can enable to write C++ code into text files, one per preset. See the SDK or http://www.willpirkle.com for details

\return true if operation succeeds, false otherwise
*/
bool PluginCore::initPluginPresets()
{
	// **--0xFF7A--**

	// --- Plugin Presets 
	int index = 0;
	PresetInfo* preset = nullptr;

	// --- Preset: Init Patch
	preset = new PresetInfo(index++, "Init Patch");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGCore, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Core, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2Core, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_frequency_Hz, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Core, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Algorithm, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter2KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalVolume_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalTuning, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc123_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc123_Mod_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_Mod_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 20.000000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -3.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_attackTime_mSec, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_decayTime_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_relaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_fineDetune, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ratio, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_phaseModIndex, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_decayLevel, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_slopeTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_egCurvature, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_attackTime_mSec, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_decayTime_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_relaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_fineDetune, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ratio, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_phaseModIndex, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_decayLevel, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_slopeTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_egCurvature, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc3Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_attackTime_mSec, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_decayTime_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_relaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_fineDetune, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ratio, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_phaseModIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_decayLevel, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_slopeTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_egCurvature, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_attackTime_mSec, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_decayTime_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_relaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_fineDetune, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ratio, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_phaseModIndex, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_decayLevel, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_slopeTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_egCurvature, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmAlgorithm, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc2_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc3_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::OSC_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFO_WSITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_EG, -0.000000);
	addPreset(preset);

	// --- Preset: FM1
	preset = new PresetInfo(index++, "FM1");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.285000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 12553.343750);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, 3.619999);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_frequency_Hz, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Algorithm, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter2KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalVolume_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalTuning, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc123_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc123_Mod_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_Mod_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 180.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 160.000000);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 30.500000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, 0.839996);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_attackTime_mSec, 309.700012);
	setPresetParameter(preset->presetParameters, controlID::fmo1_decayTime_mSec, 1624.774902);
	setPresetParameter(preset->presetParameters, controlID::fmo1_sustainLevel, 0.803030);
	setPresetParameter(preset->presetParameters, controlID::fmo1_relaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_fineDetune, -5.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ratio, 0.990000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_phaseModIndex, 0.680000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_decayLevel, 0.725000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_slopeTime_mSec, 3349.764893);
	setPresetParameter(preset->presetParameters, controlID::fmo1_egCurvature, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_attackTime_mSec, 434.574982);
	setPresetParameter(preset->presetParameters, controlID::fmo2_decayTime_mSec, 1875.625000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_sustainLevel, 0.863636);
	setPresetParameter(preset->presetParameters, controlID::fmo2_relaseTime_mSec, 6450.354980);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_fineDetune, 2.499996);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ratio, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_phaseModIndex, 0.940000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_decayLevel, 0.765000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_slopeTime_mSec, 5999.499512);
	setPresetParameter(preset->presetParameters, controlID::fmo2_egCurvature, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc3Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_attackTime_mSec, 334.674988);
	setPresetParameter(preset->presetParameters, controlID::fmo3_decayTime_mSec, 3474.404785);
	setPresetParameter(preset->presetParameters, controlID::fmo3_sustainLevel, 0.863636);
	setPresetParameter(preset->presetParameters, controlID::fmo3_relaseTime_mSec, 6650.335449);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_fineDetune, 4.000004);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ratio, 1.999000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_phaseModIndex, 0.260000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_decayLevel, 0.140000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_slopeTime_mSec, 4599.639648);
	setPresetParameter(preset->presetParameters, controlID::fmo3_egCurvature, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_panValue, -0.040000);
	setPresetParameter(preset->presetParameters, controlID::osc4Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_attackTime_mSec, 359.649994);
	setPresetParameter(preset->presetParameters, controlID::fmo4_decayTime_mSec, 5000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_sustainLevel, 0.833333);
	setPresetParameter(preset->presetParameters, controlID::fmo4_relaseTime_mSec, 3600.640137);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_fineDetune, -5.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ratio, 0.999990);
	setPresetParameter(preset->presetParameters, controlID::fmo4_phaseModIndex, 0.290000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_decayLevel, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_slopeTime_mSec, 7249.374512);
	setPresetParameter(preset->presetParameters, controlID::fmo4_egCurvature, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmAlgorithm, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc2_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc3_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::OSC_SWITCH, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::LFO_WSITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_EG, -0.000000);
	addPreset(preset);

	// --- Preset: FM1A
	preset = new PresetInfo(index++, "FM1A");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.095273);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 0.875000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobC, 0.645000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.165000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.385000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 482.968018);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 5.950000);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, 2.568707);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_decayTime_mSec, 1250.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_waveform, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_frequency_Hz, 0.392618);
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.495000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.840000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Algorithm, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter2KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalVolume_dB, 3.239994);
	setPresetParameter(preset->presetParameters, controlID::globalTuning, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc123_fo_Int, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_fo_Int, -1.000000);
	setPresetParameter(preset->presetParameters, controlID::osc123_Mod_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_Mod_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.530000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.680000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.740000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.890000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc123_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc04_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 170.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 130.000015);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 36.500000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, 0.119999);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.830000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_attackTime_mSec, 309.700012);
	setPresetParameter(preset->presetParameters, controlID::fmo1_decayTime_mSec, 1624.774902);
	setPresetParameter(preset->presetParameters, controlID::fmo1_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_relaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_fineDetune, -5.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ratio, 1.980000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_phaseModIndex, 0.540000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_decayLevel, 0.725000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_slopeTime_mSec, 3349.764893);
	setPresetParameter(preset->presetParameters, controlID::fmo1_egCurvature, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_panValue, -0.130000);
	setPresetParameter(preset->presetParameters, controlID::osc2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_attackTime_mSec, 434.574982);
	setPresetParameter(preset->presetParameters, controlID::fmo2_decayTime_mSec, 1875.625000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_relaseTime_mSec, 6450.354980);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_fineDetune, 2.499996);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ratio, 4.010001);
	setPresetParameter(preset->presetParameters, controlID::fmo2_phaseModIndex, 1.240000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_decayLevel, 0.765000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_slopeTime_mSec, 5999.499512);
	setPresetParameter(preset->presetParameters, controlID::fmo2_egCurvature, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_panValue, -0.690000);
	setPresetParameter(preset->presetParameters, controlID::osc3Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_attackTime_mSec, 334.674988);
	setPresetParameter(preset->presetParameters, controlID::fmo3_decayTime_mSec, 4469.802734);
	setPresetParameter(preset->presetParameters, controlID::fmo3_sustainLevel, 0.287879);
	setPresetParameter(preset->presetParameters, controlID::fmo3_relaseTime_mSec, 6650.335449);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_fineDetune, 4.000004);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ratio, 1.990000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_phaseModIndex, 1.260000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_decayLevel, 0.621212);
	setPresetParameter(preset->presetParameters, controlID::fmo3_slopeTime_mSec, 4599.639648);
	setPresetParameter(preset->presetParameters, controlID::fmo3_egCurvature, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_panValue, 0.230000);
	setPresetParameter(preset->presetParameters, controlID::osc4Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_attackTime_mSec, 359.649994);
	setPresetParameter(preset->presetParameters, controlID::fmo4_decayTime_mSec, 5000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_relaseTime_mSec, 3600.640137);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobD, 0.715000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_fineDetune, -5.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ratio, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_phaseModIndex, 1.770000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_decayLevel, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_slopeTime_mSec, 7249.374512);
	setPresetParameter(preset->presetParameters, controlID::fmo4_egCurvature, 0.385000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_panValue, 0.590000);
	setPresetParameter(preset->presetParameters, controlID::fmAlgorithm, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::osc1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc2_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc3_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::OSC_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFO_WSITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SWITCH, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_EG, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_EG, -0.000000);
	addPreset(preset);

	// --- Preset: EvoDigiDoo
	preset = new PresetInfo(index++, "EvoDigiDoo");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 1.068981);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_quantize, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.390000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.450000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 2549.120605);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 4.060000);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, 1.414524);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_decayTime_mSec, 4500.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_sustainLevel, 0.100000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_releaseTime_mSec, 5500.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_frequency_Hz, 0.250594);
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Algorithm, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter2KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalVolume_dB, 0.240002);
	setPresetParameter(preset->presetParameters, controlID::globalTuning, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 200.000000);
	setPresetParameter(preset->presetParameters, controlID::osc123_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc123_Mod_Int, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_Mod_Int, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.880000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 170.000015);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 210.000015);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 52.999996);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, 1.799995);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -8.039997);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_attackTime_mSec, 803.227295);
	setPresetParameter(preset->presetParameters, controlID::fmo1_decayTime_mSec, 4621.288086);
	setPresetParameter(preset->presetParameters, controlID::fmo1_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_relaseTime_mSec, 7649.334961);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_fineDetune, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ratio, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_phaseModIndex, 3.220000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_decayLevel, 0.136364);
	setPresetParameter(preset->presetParameters, controlID::fmo1_slopeTime_mSec, 7121.500488);
	setPresetParameter(preset->presetParameters, controlID::fmo1_egCurvature, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_attackTime_mSec, 379.409088);
	setPresetParameter(preset->presetParameters, controlID::fmo2_decayTime_mSec, 3560.894043);
	setPresetParameter(preset->presetParameters, controlID::fmo2_sustainLevel, 0.893939);
	setPresetParameter(preset->presetParameters, controlID::fmo2_relaseTime_mSec, 4899.609863);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_fineDetune, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ratio, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_phaseModIndex, 3.150000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_decayLevel, 0.106061);
	setPresetParameter(preset->presetParameters, controlID::fmo2_slopeTime_mSec, 7727.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_egCurvature, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_panValue, 0.120000);
	setPresetParameter(preset->presetParameters, controlID::osc3Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_attackTime_mSec, 803.227295);
	setPresetParameter(preset->presetParameters, controlID::fmo3_decayTime_mSec, 4015.348633);
	setPresetParameter(preset->presetParameters, controlID::fmo3_sustainLevel, 0.742424);
	setPresetParameter(preset->presetParameters, controlID::fmo3_relaseTime_mSec, 5149.584961);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_fineDetune, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ratio, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_phaseModIndex, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_decayLevel, 0.196970);
	setPresetParameter(preset->presetParameters, controlID::fmo3_slopeTime_mSec, 8636.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_egCurvature, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_panValue, 0.060000);
	setPresetParameter(preset->presetParameters, controlID::osc4Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_startLevel, 0.595000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_attackTime_mSec, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_decayTime_mSec, 5000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_relaseTime_mSec, 7399.360352);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobD, 0.555000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_fineDetune, -5.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ratio, 2.287000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_phaseModIndex, 0.960000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_decayLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_slopeTime_mSec, 6818.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_egCurvature, 0.455000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_panValue, 0.080000);
	setPresetParameter(preset->presetParameters, controlID::fmAlgorithm, 3.000000);
	setPresetParameter(preset->presetParameters, controlID::osc1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc2_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc3_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::OSC_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFO_WSITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SWITCH, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_EG, -0.000000);
	addPreset(preset);

	// --- Preset: FMSynthi
	preset = new PresetInfo(index++, "FMSynthi");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_attackTime_mSec, 125.087502);
	setPresetParameter(preset->presetParameters, controlID::ampEG_decayTime_mSec, 4500.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_releaseTime_mSec, 6500.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 5464.160156);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_frequency_Hz, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Algorithm, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter2KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalVolume_dB, 6.239998);
	setPresetParameter(preset->presetParameters, controlID::globalTuning, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc123_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc123_Mod_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_Mod_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 280.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 99.999992);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 37.500000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, 1.560001);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_attackTime_mSec, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_decayTime_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_relaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_fineDetune, -4.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ratio, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_phaseModIndex, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_decayLevel, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_slopeTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_egCurvature, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_attackTime_mSec, 470.227295);
	setPresetParameter(preset->presetParameters, controlID::fmo2_decayTime_mSec, 4318.318359);
	setPresetParameter(preset->presetParameters, controlID::fmo2_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_relaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_fineDetune, 5.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ratio, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_phaseModIndex, 2.780000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_decayLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_slopeTime_mSec, 7727.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_egCurvature, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc3Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_attackTime_mSec, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_decayTime_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_relaseTime_mSec, 8939.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_fineDetune, 18.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ratio, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_phaseModIndex, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_decayLevel, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_slopeTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_egCurvature, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_attackTime_mSec, 530.772705);
	setPresetParameter(preset->presetParameters, controlID::fmo4_decayTime_mSec, 4469.802734);
	setPresetParameter(preset->presetParameters, controlID::fmo4_sustainLevel, 0.590909);
	setPresetParameter(preset->presetParameters, controlID::fmo4_relaseTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobD, 0.215000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_fineDetune, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ratio, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_phaseModIndex, 2.100000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_decayLevel, 0.318182);
	setPresetParameter(preset->presetParameters, controlID::fmo4_slopeTime_mSec, 7727.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_egCurvature, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmAlgorithm, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::osc1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc2_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc3_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::OSC_SWITCH, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::LFO_WSITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_EG, -0.000000);
	addPreset(preset);

	// --- Preset: AngryBass
	preset = new PresetInfo(index++, "AngryBass");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_attackTime_mSec, 50.095013);
	setPresetParameter(preset->presetParameters, controlID::ampEG_decayTime_mSec, 1950.000122);
	setPresetParameter(preset->presetParameters, controlID::ampEG_sustainLevel, 0.700000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_releaseTime_mSec, 2250.000244);
	setPresetParameter(preset->presetParameters, controlID::ampEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.095000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_frequency_Hz, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Algorithm, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc, 4924.577637);
	setPresetParameter(preset->presetParameters, controlID::filter2_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter2KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobB, 0.085000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalVolume_dB, 3.600002);
	setPresetParameter(preset->presetParameters, controlID::globalTuning, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc123_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc123_Mod_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_Mod_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 130.000015);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 190.000015);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 31.500000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, 1.200001);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_attackTime_mSec, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_decayTime_mSec, 3863.863525);
	setPresetParameter(preset->presetParameters, controlID::fmo1_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_relaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_fineDetune, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ratio, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_phaseModIndex, 2.280000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_decayLevel, 0.196970);
	setPresetParameter(preset->presetParameters, controlID::fmo1_slopeTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_egCurvature, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_attackTime_mSec, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_decayTime_mSec, 4772.772461);
	setPresetParameter(preset->presetParameters, controlID::fmo2_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_relaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_fineDetune, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ratio, 0.490000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_phaseModIndex, 3.380000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_decayLevel, 0.439394);
	setPresetParameter(preset->presetParameters, controlID::fmo2_slopeTime_mSec, 2576.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_egCurvature, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc3Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_attackTime_mSec, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_decayTime_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_relaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_fineDetune, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ratio, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_phaseModIndex, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_decayLevel, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_slopeTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_egCurvature, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_attackTime_mSec, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_decayTime_mSec, 5000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_relaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobD, 0.420000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_fineDetune, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ratio, 0.250000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_phaseModIndex, 1.680000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_decayLevel, 0.015152);
	setPresetParameter(preset->presetParameters, controlID::fmo4_slopeTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_egCurvature, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmAlgorithm, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::osc1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc2_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc3_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SWITCH, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::OSC_SWITCH, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::LFO_WSITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SWITCH, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_EG, -0.000000);
	addPreset(preset);

	// --- Preset: Cheapnis
	preset = new PresetInfo(index++, "Cheapnis");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_attackTime_mSec, 50.095013);
	setPresetParameter(preset->presetParameters, controlID::ampEG_decayTime_mSec, 4250.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_sustainLevel, 0.525000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_releaseTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_frequency_Hz, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Algorithm, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter2KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalVolume_dB, 5.399994);
	setPresetParameter(preset->presetParameters, controlID::globalTuning, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc123_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc123_Mod_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_Mod_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 490.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 980.000061);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 10.499999);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, 2.279999);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -0.600002);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_attackTime_mSec, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_decayTime_mSec, 4318.318359);
	setPresetParameter(preset->presetParameters, controlID::fmo1_sustainLevel, 0.772727);
	setPresetParameter(preset->presetParameters, controlID::fmo1_relaseTime_mSec, 3182.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_fineDetune, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ratio, 1.414000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_phaseModIndex, 2.280000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_decayLevel, 0.621212);
	setPresetParameter(preset->presetParameters, controlID::fmo1_slopeTime_mSec, 4091.500244);
	setPresetParameter(preset->presetParameters, controlID::fmo1_egCurvature, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_attackTime_mSec, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_decayTime_mSec, 5000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_sustainLevel, 0.712121);
	setPresetParameter(preset->presetParameters, controlID::fmo2_relaseTime_mSec, 4697.500488);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_fineDetune, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ratio, 7.998500);
	setPresetParameter(preset->presetParameters, controlID::fmo2_phaseModIndex, 3.380000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_decayLevel, 0.924242);
	setPresetParameter(preset->presetParameters, controlID::fmo2_slopeTime_mSec, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_egCurvature, 0.825000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc3Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_attackTime_mSec, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_decayTime_mSec, 2954.954590);
	setPresetParameter(preset->presetParameters, controlID::fmo3_sustainLevel, 0.803030);
	setPresetParameter(preset->presetParameters, controlID::fmo3_relaseTime_mSec, 3182.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_fineDetune, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ratio, 1.099000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_phaseModIndex, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_decayLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_slopeTime_mSec, 7121.500488);
	setPresetParameter(preset->presetParameters, controlID::fmo3_egCurvature, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_attackTime_mSec, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_decayTime_mSec, 1440.106201);
	setPresetParameter(preset->presetParameters, controlID::fmo4_sustainLevel, 0.742424);
	setPresetParameter(preset->presetParameters, controlID::fmo4_relaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobD, 0.420000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_fineDetune, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ratio, 0.100000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_phaseModIndex, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_decayLevel, 0.803030);
	setPresetParameter(preset->presetParameters, controlID::fmo4_slopeTime_mSec, 8939.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_egCurvature, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmAlgorithm, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::osc1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc2_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc3_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SWITCH, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::OSC_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFO_WSITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_EG, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_EG, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_EG, 1.000000);
	addPreset(preset);

	// --- Preset: FMBass2
	preset = new PresetInfo(index++, "FMBass2");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, 9.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 20.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_attackTime_mSec, 0.100000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_decayTime_mSec, 3375.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_sustainLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_releaseTime_mSec, 749.999878);
	setPresetParameter(preset->presetParameters, controlID::ampEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.785000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.165000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 6498.017090);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_frequency_Hz, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Algorithm, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc, 11313.704102);
	setPresetParameter(preset->presetParameters, controlID::filter2_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter2KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobB, 0.125000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalVolume_dB, 4.440002);
	setPresetParameter(preset->presetParameters, controlID::globalTuning, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc123_fo_Int, 0.740000);
	setPresetParameter(preset->presetParameters, controlID::osc4_fo_Int, 0.680000);
	setPresetParameter(preset->presetParameters, controlID::osc123_Mod_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_Mod_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc123_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc04_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 180.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 250.000000);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 5.500000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, 2.279999);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_attackTime_mSec, 309.700012);
	setPresetParameter(preset->presetParameters, controlID::fmo1_decayTime_mSec, 1624.774902);
	setPresetParameter(preset->presetParameters, controlID::fmo1_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_relaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_fineDetune, -5.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ratio, 0.990000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_phaseModIndex, 0.680000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_decayLevel, 0.725000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_slopeTime_mSec, 3349.764893);
	setPresetParameter(preset->presetParameters, controlID::fmo1_egCurvature, 0.465000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_attackTime_mSec, 434.574982);
	setPresetParameter(preset->presetParameters, controlID::fmo2_decayTime_mSec, 1875.625000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_relaseTime_mSec, 6450.354980);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_fineDetune, 2.499996);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ratio, 0.490000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_phaseModIndex, 0.940000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_decayLevel, 0.765000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_slopeTime_mSec, 5999.499512);
	setPresetParameter(preset->presetParameters, controlID::fmo2_egCurvature, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc3Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_attackTime_mSec, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_decayTime_mSec, 3474.404785);
	setPresetParameter(preset->presetParameters, controlID::fmo3_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_relaseTime_mSec, 6650.335449);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_fineDetune, 15.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ratio, 1.990000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_phaseModIndex, 0.260000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_decayLevel, 0.140000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_slopeTime_mSec, 1364.499878);
	setPresetParameter(preset->presetParameters, controlID::fmo3_egCurvature, 0.265000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_attackTime_mSec, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_decayTime_mSec, 5000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_relaseTime_mSec, 3600.640137);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobD, 0.410000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_fineDetune, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ratio, 0.991000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_phaseModIndex, 1.920000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_decayLevel, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_slopeTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_egCurvature, 0.420000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmAlgorithm, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::osc1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc2_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc3_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::OSC_SWITCH, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::LFO_WSITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_EG, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_EG, -0.000000);
	addPreset(preset);

	// --- Preset: AnalogKid
	preset = new PresetInfo(index++, "AnalogKid");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.092039);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_releaseTime_mSec, 3500.000244);
	setPresetParameter(preset->presetParameters, controlID::ampEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.465000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.270000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.785000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 98.073021);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 7.930000);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 0.100000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_decayTime_mSec, 5000.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_sustainLevel, 0.300000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_releaseTime_mSec, 6250.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_frequency_Hz, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Algorithm, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter2KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalVolume_dB, 4.320000);
	setPresetParameter(preset->presetParameters, controlID::globalTuning, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc123_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc123_Mod_Int, 0.670000);
	setPresetParameter(preset->presetParameters, controlID::osc4_Mod_Int, 0.760000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.730000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.680000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.840000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc123_Mod, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc04_Mod, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 390.000031);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 210.000031);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 36.500000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, 2.639999);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc123_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc04_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc123_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc04_Mod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_attackTime_mSec, 76.681808);
	setPresetParameter(preset->presetParameters, controlID::fmo1_decayTime_mSec, 4318.318359);
	setPresetParameter(preset->presetParameters, controlID::fmo1_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_relaseTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_fineDetune, -5.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_ratio, 0.990000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_phaseModIndex, 2.960000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_decayLevel, 0.378788);
	setPresetParameter(preset->presetParameters, controlID::fmo1_slopeTime_mSec, 3349.764893);
	setPresetParameter(preset->presetParameters, controlID::fmo1_egCurvature, 0.465000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_panValue, 0.010000);
	setPresetParameter(preset->presetParameters, controlID::osc2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_attackTime_mSec, 16.136349);
	setPresetParameter(preset->presetParameters, controlID::fmo2_decayTime_mSec, 3257.924072);
	setPresetParameter(preset->presetParameters, controlID::fmo2_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_relaseTime_mSec, 6450.354980);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ModKnobD, 0.370000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_fineDetune, -2.499996);
	setPresetParameter(preset->presetParameters, controlID::fmo2_ratio, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_phaseModIndex, 3.220000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_decayLevel, 0.287879);
	setPresetParameter(preset->presetParameters, controlID::fmo2_slopeTime_mSec, 5999.499512);
	setPresetParameter(preset->presetParameters, controlID::fmo2_egCurvature, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc3Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_attackTime_mSec, 167.500015);
	setPresetParameter(preset->presetParameters, controlID::fmo3_decayTime_mSec, 3474.404785);
	setPresetParameter(preset->presetParameters, controlID::fmo3_sustainLevel, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_relaseTime_mSec, 6650.335449);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_fineDetune, 6.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_ratio, 0.490000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_phaseModIndex, 1.980000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_decayLevel, 0.140000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_slopeTime_mSec, 6515.499512);
	setPresetParameter(preset->presetParameters, controlID::fmo3_egCurvature, 0.265000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_startLevel, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_attackTime_mSec, 359.649994);
	setPresetParameter(preset->presetParameters, controlID::fmo4_decayTime_mSec, 5000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_sustainLevel, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_relaseTime_mSec, 3600.640137);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ModKnobD, 0.045000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_fineDetune, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_ratio, 0.991000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_phaseModIndex, 2.700000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_decayLevel, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_slopeTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_egCurvature, 0.420000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmAlgorithm, 3.000000);
	setPresetParameter(preset->presetParameters, controlID::osc1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc2_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc3_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc4_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::OSC_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFO_WSITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SWITCH, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SWITCH, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo1_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo2_EG, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo3_EG, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::fmo4_EG, -0.000000);
	addPreset(preset);


	// **--0xA7FF--**

    return true;
}

/**
\brief setup the plugin description strings, flags and codes; this is ordinarily done through the ASPiKreator or CMake

\return true if operation succeeds, false otherwise
*/
bool PluginCore::initPluginDescriptors()
{
    pluginDescriptor.pluginName = PluginCore::getPluginName();
    pluginDescriptor.shortPluginName = PluginCore::getShortPluginName();
    pluginDescriptor.vendorName = PluginCore::getVendorName();
    pluginDescriptor.pluginTypeCode = PluginCore::getPluginType();

	// --- describe the plugin attributes; set according to your needs
	pluginDescriptor.hasSidechain = kWantSidechain;
	pluginDescriptor.latencyInSamples = kLatencyInSamples;
	pluginDescriptor.tailTimeInMSec = kTailTimeMsec;
	pluginDescriptor.infiniteTailVST3 = kVSTInfiniteTail;

    // --- AAX
    apiSpecificInfo.aaxManufacturerID = kManufacturerID;
    apiSpecificInfo.aaxProductID = kAAXProductID;
    apiSpecificInfo.aaxBundleID = kAAXBundleID;  /* MacOS only: this MUST match the bundle identifier in your info.plist file */
    apiSpecificInfo.aaxEffectID = "aaxDeveloper.";
    apiSpecificInfo.aaxEffectID.append(PluginCore::getPluginName());
    apiSpecificInfo.aaxPluginCategoryCode = kAAXCategory;

    // --- AU
    apiSpecificInfo.auBundleID = kAUBundleID;
	apiSpecificInfo.auBundleName = kAUBundleName;   /* MacOS only: this MUST match the bundle identifier in your info.plist file */
    apiSpecificInfo.auBundleName = kAUBundleName;

    // --- VST3
    apiSpecificInfo.vst3FUID = PluginCore::getVSTFUID(); // OLE string format
    apiSpecificInfo.vst3BundleID = kVST3BundleID;/* MacOS only: this MUST match the bundle identifier in your info.plist file */
	apiSpecificInfo.enableVST3SampleAccurateAutomation = kVSTSAA;
	apiSpecificInfo.vst3SampleAccurateGranularity = kVST3SAAGranularity;

    // --- AU and AAX
    apiSpecificInfo.fourCharCode = PluginCore::getFourCharCode();

    return true;
}

// --- static functions required for VST3/AU only --------------------------------------------- //
const char* PluginCore::getPluginBundleName() { return kAUBundleName; }
const char* PluginCore::getPluginName(){ return kPluginName; }
const char* PluginCore::getShortPluginName(){ return kShortPluginName; }
const char* PluginCore::getVendorName(){ return kVendorName; }
const char* PluginCore::getVendorURL(){ return kVendorURL; }
const char* PluginCore::getVendorEmail(){ return kVendorEmail; }
const char* PluginCore::getAUCocoaViewFactoryName(){ return AU_COCOA_VIEWFACTORY_STRING; }
pluginType PluginCore::getPluginType(){ return kPluginType; }
const char* PluginCore::getVSTFUID(){ return kVSTFUID; }
int32_t PluginCore::getFourCharCode(){ return kFourCharCode; }
