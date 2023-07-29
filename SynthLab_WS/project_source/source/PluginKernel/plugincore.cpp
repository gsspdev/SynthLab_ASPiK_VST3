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
#ifdef SYNTHLAB_WS
	dynModuleManager.addLoadableModule(SynthLab::WTO_MODULE);
	dynModuleManager.setDoubleOscillators(true); // WS has a double set
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
	piParam = new PluginParameter(controlID::lfo1_outputAmplitude, "LFO1 Output", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
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
	piParam = new PluginParameter(controlID::ampEG_decayTime_mSec, "AmpEG Dcy", "mSec", controlVariableType::kDouble, 0.000000, 1000.000000, 300.000000, taper::kLinearTaper);
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
	piParam = new PluginParameter(controlID::ampEGCore, "AmpEG Core", "default 0,user 0,user 1,user 2", "default 0");
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
	piParam = new PluginParameter(controlID::filter1Core, "Filter1 Core", "default 0,user 0,user 1,user 2", "default 0");
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
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filter1_fc, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Filter1 Q
	piParam = new PluginParameter(controlID::filter1_Q, "Filter1 Q", "", controlVariableType::kDouble, 1.000000, 10.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filter1_Q, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Filter1 Out
	piParam = new PluginParameter(controlID::filter1Output_dB, "Filter1 Out", "dB", controlVariableType::kDouble, -60.000000, 20.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filter1Output_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: Filter1 Key Trk
	piParam = new PluginParameter(controlID::enableFilter1KeyTrack, "Filter1 Key Trk", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&enableFilter1KeyTrack, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: FilterEG Core
	piParam = new PluginParameter(controlID::filterEGCore, "FilterEG Core", "default 0,user 0,user 1,user 2", "default 0");
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
	piParam = new PluginParameter(controlID::filterEG_decayTime_mSec, "FilterEG Dcy", "mSec", controlVariableType::kDouble, 0.000000, 1000.000000, 300.000000, taper::kLinearTaper);
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
	piParam = new PluginParameter(controlID::lfo2Core, "LFO2 Core", "default 0,user 0,user 1,user 2", "default 0");
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
	piParam = new PluginParameter(controlID::lfo2_outputAmplitude, "LFO2 Output", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
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
	piParam = new PluginParameter(controlID::auxEGCore, "AuxEG", "default 0,user 0,user 1,user 2", "default 0");
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
	piParam = new PluginParameter(controlID::filter2Core, "Filter2 Core", "default 0,user 0,user 1,user 2", "default 0");
	piParam->setBoundVariable(&filter2Core, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Filter2 Type
	piParam = new PluginParameter(controlID::filter2Algorithm, "Filter2 Type", "kLPF1,kHPF1,kAPF1,kSVF LP,kSVF HP,kSVF BP,kSVF BS,kKorg35 LP,kKorg35 HP,kMoog LP1,kMoog LP2,kMoog LP3,kMoog LP4,kDiode LP4,kBypassFilter", "kLPF1");
	piParam->setBoundVariable(&filter2Algorithm, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: Filter2 fc
	piParam = new PluginParameter(controlID::filter2_fc, "Filter2 fc", "Hz", controlVariableType::kDouble, 20.000000, 20480.000000, 1000.000000, taper::kVoltOctaveTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filter2_fc, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Filter2 Q
	piParam = new PluginParameter(controlID::filter2_Q, "Filter2 Q", "", controlVariableType::kDouble, 1.000000, 10.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filter2_Q, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: Filter2 Key Trk
	piParam = new PluginParameter(controlID::enableFilter2KeyTrack, "Filter2 Key Trk", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&enableFilter2KeyTrack, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: Filter2 Out
	piParam = new PluginParameter(controlID::filter2Output_dB, "Filter2 Out", "dB", controlVariableType::kDouble, -60.000000, 20.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
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
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&globalVolume_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Global Tuning
	piParam = new PluginParameter(controlID::globalTuning, "Global Tuning", "semi", controlVariableType::kDouble, -12.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&globalTuning, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Unison Detune
	piParam = new PluginParameter(controlID::globalUnisonDetune_Cents, "Unison Detune", "cents", controlVariableType::kDouble, 0.000000, 25.000000, 5.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&globalUnisonDetune_Cents, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: PBend Range
	piParam = new PluginParameter(controlID::globalPitchBendSens, "PBend Range", "semi", controlVariableType::kDouble, 0.000000, 48.000000, 0.000000, taper::kLinearTaper);
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

	// --- continuous control: WS1 Amp
	piParam = new PluginParameter(controlID::ws1WaveAmp_dB, "WS1 Amp", "dB", controlVariableType::kDouble, -60.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws1WaveAmp_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: WS1 Step
	piParam = new PluginParameter(controlID::ws1StepLenIndex, "WS1 Step", "n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole", "n32ndTrip");
	piParam->setBoundVariable(&ws1StepLenIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: WS1 XFade
	piParam = new PluginParameter(controlID::ws1XFadeLenIndex, "WS1 XFade", "n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole", "n32ndTrip");
	piParam->setBoundVariable(&ws1XFadeLenIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: WS1 Pitch
	piParam = new PluginParameter(controlID::ws1Pitch_semi, "WS1 Pitch", "", controlVariableType::kInt, -24.000000, 24.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws1Pitch_semi, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: WS1 Pitch Prob
	piParam = new PluginParameter(controlID::ws1PitchProb_pct, "WS1 Pitch Prob", "%", controlVariableType::kDouble, 0.000000, 100.000000, 100.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws1PitchProb_pct, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS1 Mod Val
	piParam = new PluginParameter(controlID::ws1ModValue, "WS1 Mod Val", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws1ModValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS1 Mod Prob
	piParam = new PluginParameter(controlID::ws1ModProb_pct, "WS1 Mod Prob", "%", controlVariableType::kDouble, 0.000000, 100.000000, 100.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws1ModProb_pct, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: WS1 Wave
	piParam = new PluginParameter(controlID::ws1WaveIndex, "WS1 Wave", "wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15,wave16,wave17,wave18,wave19,wave20,wave21,wave22,wave23,wave24,wave25,wave26,wave27,wave28,wave29,wave30,wave31,wave32,wave33,wave34,wave35,wave36,wave37,wave38,wave39,wave40,wave41,wave42,wave43,wave44,wave45,wave46,wave47,wave48,wave49,wave50,wave51,wave52,wave53,wave54,wave55,wave56,wave57,wave58,wave59,wave60,wave61,wave62,wave63", "wave0");
	piParam->setBoundVariable(&ws1WaveIndex, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: WS2 Step
	piParam = new PluginParameter(controlID::ws2StepLenIndex, "WS2 Step", "n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole", "n32ndTrip");
	piParam->setBoundVariable(&ws2StepLenIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: WS2 XFade
	piParam = new PluginParameter(controlID::ws2XFadeLenIndex, "WS2 XFade", "n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole", "n32ndTrip");
	piParam->setBoundVariable(&ws2XFadeLenIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: WS2 Wave
	piParam = new PluginParameter(controlID::ws2WaveIndex, "WS2 Wave", "wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15,wave16,wave17,wave18,wave19,wave20,wave21,wave22,wave23,wave24,wave25,wave26,wave27,wave28,wave29,wave30,wave31,wave32,wave33,wave34,wave35,wave36,wave37,wave38,wave39,wave40,wave41,wave42,wave43,wave44,wave45,wave46,wave47,wave48,wave49,wave50,wave51,wave52,wave53,wave54,wave55,wave56,wave57,wave58,wave59,wave60,wave61,wave62,wave63", "wave0");
	piParam->setBoundVariable(&ws2WaveIndex, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: WS2 Amp
	piParam = new PluginParameter(controlID::ws2WaveAmp_dB, "WS2 Amp", "dB", controlVariableType::kDouble, -60.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws2WaveAmp_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS2 Pitch
	piParam = new PluginParameter(controlID::ws2Pitch_semi, "WS2 Pitch", "", controlVariableType::kInt, -24.000000, 24.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws2Pitch_semi, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: WS2 Pitch Prob
	piParam = new PluginParameter(controlID::ws2PitchProb_pct, "WS2 Pitch Prob", "%", controlVariableType::kDouble, 0.000000, 100.000000, 100.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws2PitchProb_pct, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS2 Mod Val
	piParam = new PluginParameter(controlID::ws2ModValue, "WS2 Mod Val", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws2ModValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS2 Mod Prob
	piParam = new PluginParameter(controlID::ws2ModProb_pct, "WS2 Mod Prob", "%", controlVariableType::kDouble, 0.000000, 100.000000, 100.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws2ModProb_pct, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: WS3 Step
	piParam = new PluginParameter(controlID::ws3StepLenIndex, "WS3 Step", "n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole", "n32ndTrip");
	piParam->setBoundVariable(&ws3StepLenIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: WS3 XFade
	piParam = new PluginParameter(controlID::ws3XFadeLenIndex, "WS3 XFade", "n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole", "n32ndTrip");
	piParam->setBoundVariable(&ws3XFadeLenIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: WS3 Wave
	piParam = new PluginParameter(controlID::ws3WaveIndex, "WS3 Wave", "wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15,wave16,wave17,wave18,wave19,wave20,wave21,wave22,wave23,wave24,wave25,wave26,wave27,wave28,wave29,wave30,wave31,wave32,wave33,wave34,wave35,wave36,wave37,wave38,wave39,wave40,wave41,wave42,wave43,wave44,wave45,wave46,wave47,wave48,wave49,wave50,wave51,wave52,wave53,wave54,wave55,wave56,wave57,wave58,wave59,wave60,wave61,wave62,wave63", "wave0");
	piParam->setBoundVariable(&ws3WaveIndex, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: WS3 Amp
	piParam = new PluginParameter(controlID::ws3WaveAmp_dB, "WS3 Amp", "dB", controlVariableType::kDouble, -60.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws3WaveAmp_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS3 Pitch
	piParam = new PluginParameter(controlID::ws3Pitch_semi, "WS3 Pitch", "", controlVariableType::kInt, -24.000000, 24.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws3Pitch_semi, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: WS3 Pitch Prob
	piParam = new PluginParameter(controlID::ws3PitchProb_pct, "WS3 Pitch Prob", "%", controlVariableType::kDouble, 0.000000, 100.000000, 100.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws3PitchProb_pct, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS3 Mod Val
	piParam = new PluginParameter(controlID::ws3ModValue, "WS3 Mod Val", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws3ModValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS3 Mod Prob
	piParam = new PluginParameter(controlID::ws3ModProb_pct, "WS3 Mod Prob", "%", controlVariableType::kDouble, 0.000000, 100.000000, 100.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws3ModProb_pct, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: WS4 Step
	piParam = new PluginParameter(controlID::ws4StepLenIndex, "WS4 Step", "n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole", "n32ndTrip");
	piParam->setBoundVariable(&ws4StepLenIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: WS4 XFade
	piParam = new PluginParameter(controlID::ws4XFadeLenIndex, "WS4 XFade", "n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole", "n32ndTrip");
	piParam->setBoundVariable(&ws4XFadeLenIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: WS4 Wave
	piParam = new PluginParameter(controlID::ws4WaveIndex, "WS4 Wave", "wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15,wave16,wave17,wave18,wave19,wave20,wave21,wave22,wave23,wave24,wave25,wave26,wave27,wave28,wave29,wave30,wave31,wave32,wave33,wave34,wave35,wave36,wave37,wave38,wave39,wave40,wave41,wave42,wave43,wave44,wave45,wave46,wave47,wave48,wave49,wave50,wave51,wave52,wave53,wave54,wave55,wave56,wave57,wave58,wave59,wave60,wave61,wave62,wave63", "wave0");
	piParam->setBoundVariable(&ws4WaveIndex, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: WS4 Amp
	piParam = new PluginParameter(controlID::ws4WaveAmp_dB, "WS4 Amp", "dB", controlVariableType::kDouble, -60.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws4WaveAmp_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS4 Pitch
	piParam = new PluginParameter(controlID::ws4Pitch_semi, "WS4 Pitch", "", controlVariableType::kInt, -24.000000, 24.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws4Pitch_semi, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: WS4 Pitch Prob
	piParam = new PluginParameter(controlID::ws4PitchProb_pct, "WS4 Pitch Prob", "%", controlVariableType::kDouble, 0.000000, 100.000000, 100.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws4PitchProb_pct, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS4 Mod Val
	piParam = new PluginParameter(controlID::ws4ModValue, "WS4 Mod Val", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws4ModValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS4 Mod Prob
	piParam = new PluginParameter(controlID::ws4ModProb_pct, "WS4 Mod Prob", "%", controlVariableType::kDouble, 0.000000, 100.000000, 100.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws4ModProb_pct, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: WS5 Step
	piParam = new PluginParameter(controlID::ws5StepLenIndex, "WS5 Step", "n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole", "n32ndTrip");
	piParam->setBoundVariable(&ws5StepLenIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: WS5 XFade
	piParam = new PluginParameter(controlID::ws5XFadeLenIndex, "WS5 XFade", "n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole", "n32ndTrip");
	piParam->setBoundVariable(&ws5XFadeLenIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: WS5 Wave
	piParam = new PluginParameter(controlID::ws5WaveIndex, "WS5 Wave", "wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15,wave16,wave17,wave18,wave19,wave20,wave21,wave22,wave23,wave24,wave25,wave26,wave27,wave28,wave29,wave30,wave31,wave32,wave33,wave34,wave35,wave36,wave37,wave38,wave39,wave40,wave41,wave42,wave43,wave44,wave45,wave46,wave47,wave48,wave49,wave50,wave51,wave52,wave53,wave54,wave55,wave56,wave57,wave58,wave59,wave60,wave61,wave62,wave63", "wave0");
	piParam->setBoundVariable(&ws5WaveIndex, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: WS5 Amp
	piParam = new PluginParameter(controlID::ws5WaveAmp_dB, "WS5 Amp", "dB", controlVariableType::kDouble, -60.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws5WaveAmp_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS5 Pitch
	piParam = new PluginParameter(controlID::ws5Pitch_semi, "WS5 Pitch", "", controlVariableType::kInt, -24.000000, 24.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws5Pitch_semi, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: WS5 Pitch Prob
	piParam = new PluginParameter(controlID::ws5PitchProb_pct, "WS5 Pitch Prob", "%", controlVariableType::kDouble, 0.000000, 100.000000, 100.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws5PitchProb_pct, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS5 Mod Val
	piParam = new PluginParameter(controlID::ws5ModValue, "WS5 Mod Val", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws5ModValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS5 Mod Prob
	piParam = new PluginParameter(controlID::ws5ModProb_pct, "WS5 Mod Prob", "%", controlVariableType::kDouble, 0.000000, 100.000000, 100.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws5ModProb_pct, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: WS6 Step
	piParam = new PluginParameter(controlID::ws6StepLenIndex, "WS6 Step", "n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole", "n32ndTrip");
	piParam->setBoundVariable(&ws6StepLenIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: WS6 XFade
	piParam = new PluginParameter(controlID::ws6XFadeLenIndex, "WS6 XFade", "n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole", "n32ndTrip");
	piParam->setBoundVariable(&ws6XFadeLenIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: WS6 Wave
	piParam = new PluginParameter(controlID::ws6WaveIndex, "WS6 Wave", "wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15,wave16,wave17,wave18,wave19,wave20,wave21,wave22,wave23,wave24,wave25,wave26,wave27,wave28,wave29,wave30,wave31,wave32,wave33,wave34,wave35,wave36,wave37,wave38,wave39,wave40,wave41,wave42,wave43,wave44,wave45,wave46,wave47,wave48,wave49,wave50,wave51,wave52,wave53,wave54,wave55,wave56,wave57,wave58,wave59,wave60,wave61,wave62,wave63", "wave0");
	piParam->setBoundVariable(&ws6WaveIndex, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: WS6 Amp
	piParam = new PluginParameter(controlID::ws6WaveAmp_dB, "WS6 Amp", "dB", controlVariableType::kDouble, -60.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws6WaveAmp_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS6 Pitch
	piParam = new PluginParameter(controlID::ws6Pitch_semi, "WS6 Pitch", "", controlVariableType::kInt, -24.000000, 24.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws6Pitch_semi, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: WS6 Pitch Prob
	piParam = new PluginParameter(controlID::ws6PitchProb_pct, "WS6 Pitch Prob", "%", controlVariableType::kDouble, 0.000000, 100.000000, 100.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws6PitchProb_pct, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS6 Mod Val
	piParam = new PluginParameter(controlID::ws6ModValue, "WS6 Mod Val", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws6ModValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS6 Mod Prob
	piParam = new PluginParameter(controlID::ws6ModProb_pct, "WS6 Mod Prob", "%", controlVariableType::kDouble, 0.000000, 100.000000, 100.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws6ModProb_pct, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: WS7 Step
	piParam = new PluginParameter(controlID::ws7StepLenIndex, "WS7 Step", "n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole", "n32ndTrip");
	piParam->setBoundVariable(&ws7StepLenIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: WS7 XFade
	piParam = new PluginParameter(controlID::ws7XFadeLenIndex, "WS7 XFade", "n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole", "n32ndTrip");
	piParam->setBoundVariable(&ws7XFadeLenIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: WS7 Wave
	piParam = new PluginParameter(controlID::ws7WaveIndex, "WS7 Wave", "wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15,wave16,wave17,wave18,wave19,wave20,wave21,wave22,wave23,wave24,wave25,wave26,wave27,wave28,wave29,wave30,wave31,wave32,wave33,wave34,wave35,wave36,wave37,wave38,wave39,wave40,wave41,wave42,wave43,wave44,wave45,wave46,wave47,wave48,wave49,wave50,wave51,wave52,wave53,wave54,wave55,wave56,wave57,wave58,wave59,wave60,wave61,wave62,wave63", "wave0");
	piParam->setBoundVariable(&ws7WaveIndex, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: WS7 Amp
	piParam = new PluginParameter(controlID::ws7WaveAmp_dB, "WS7 Amp", "dB", controlVariableType::kDouble, -60.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws7WaveAmp_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS7 Pitch
	piParam = new PluginParameter(controlID::ws7Pitch_semi, "WS7 Pitch", "", controlVariableType::kInt, -24.000000, 24.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws7Pitch_semi, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: WS7 Pitch Prob
	piParam = new PluginParameter(controlID::ws7PitchProb_pct, "WS7 Pitch Prob", "%", controlVariableType::kDouble, 0.000000, 100.000000, 100.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws7PitchProb_pct, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS7 Mod Val
	piParam = new PluginParameter(controlID::ws7ModValue, "WS7 Mod Val", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws7ModValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS7 Mod Prob
	piParam = new PluginParameter(controlID::ws7ModProb_pct, "WS7 Mod Prob", "%", controlVariableType::kDouble, 0.000000, 100.000000, 100.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws7ModProb_pct, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: WS8 Step
	piParam = new PluginParameter(controlID::ws8StepLenIndex, "WS8 Step", "n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole", "n32ndTrip");
	piParam->setBoundVariable(&ws8StepLenIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: WS8 XFade
	piParam = new PluginParameter(controlID::ws8XFadeLenIndex, "WS8 XFade", "n32ndTrip,n32nd,n16thTrip,nDot32nd,n16th,n8thTrip,nDot16th,n8th,nQuarterTrip,nDot8th,nQuarter,nHalfTrip,nDotQuarter,nHalf,nWholeTrip,nDotHalf,nWhole,nDotWhole", "n32ndTrip");
	piParam->setBoundVariable(&ws8XFadeLenIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: WS8 Wave
	piParam = new PluginParameter(controlID::ws8WaveIndex, "WS8 Wave", "wave0,wave1,wave2,wave3,wave4,wave5,wave6,wave7,wave8,wave9,wave10,wave11,wave12,wave13,wave14,wave15,wave16,wave17,wave18,wave19,wave20,wave21,wave22,wave23,wave24,wave25,wave26,wave27,wave28,wave29,wave30,wave31,wave32,wave33,wave34,wave35,wave36,wave37,wave38,wave39,wave40,wave41,wave42,wave43,wave44,wave45,wave46,wave47,wave48,wave49,wave50,wave51,wave52,wave53,wave54,wave55,wave56,wave57,wave58,wave59,wave60,wave61,wave62,wave63", "wave0");
	piParam->setBoundVariable(&ws8WaveIndex, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: WS8 Amp
	piParam = new PluginParameter(controlID::ws8WaveAmp_dB, "WS8 Amp", "dB", controlVariableType::kDouble, -60.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws8WaveAmp_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS8 Pitch
	piParam = new PluginParameter(controlID::ws8Pitch_semi, "WS8 Pitch", "", controlVariableType::kInt, -24.000000, 24.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws8Pitch_semi, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: WS8 Pitch Prob
	piParam = new PluginParameter(controlID::ws8PitchProb_pct, "WS8 Pitch Prob", "%", controlVariableType::kDouble, 0.000000, 100.000000, 100.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws8PitchProb_pct, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS8 Mod Val
	piParam = new PluginParameter(controlID::ws8ModValue, "WS8 Mod Val", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws8ModValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WS8 Mod Prob
	piParam = new PluginParameter(controlID::ws8ModProb_pct, "WS8 Mod Prob", "%", controlVariableType::kDouble, 0.000000, 100.000000, 100.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ws8ModProb_pct, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Timing Start
	piParam = new PluginParameter(controlID::timingStartIndex, "Timing Start", "", controlVariableType::kInt, 1.000000, 8.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&timingStartIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: Timing End
	piParam = new PluginParameter(controlID::timingEndIndex, "Timing End", "", controlVariableType::kInt, 1.000000, 8.000000, 8.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&timingEndIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: Timing Loop Dir
	piParam = new PluginParameter(controlID::timingLoopDir, "Timing Loop Dir", "forward,backward,fwrd bckwrd", "forward");
	piParam->setBoundVariable(&timingLoopDir, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: Wave Start
	piParam = new PluginParameter(controlID::waveStartIndex, "Wave Start", "", controlVariableType::kInt, 1.000000, 8.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&waveStartIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: Wave End
	piParam = new PluginParameter(controlID::waveEndIndex, "Wave End", "", controlVariableType::kInt, 1.000000, 8.000000, 8.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&waveEndIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: Wave Loop Dir
	piParam = new PluginParameter(controlID::waveLoopDir, "Wave Loop Dir", "forward,backward,fwrd bckwrd", "forward");
	piParam->setBoundVariable(&waveLoopDir, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: Pitch Start
	piParam = new PluginParameter(controlID::pitchStartIndex, "Pitch Start", "", controlVariableType::kInt, 1.000000, 8.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&pitchStartIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: Pitch End
	piParam = new PluginParameter(controlID::pitchEndIndex, "Pitch End", "", controlVariableType::kInt, 1.000000, 8.000000, 8.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&pitchEndIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: Pitch Loop Dir
	piParam = new PluginParameter(controlID::pitchLoopDir, "Pitch Loop Dir", "forward,backward,fwrd bckwrd", "forward");
	piParam->setBoundVariable(&pitchLoopDir, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: SSMod Start
	piParam = new PluginParameter(controlID::stepSeqModStartIndex, "SSMod Start", "", controlVariableType::kInt, 1.000000, 8.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&stepSeqModStartIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: SSMod End
	piParam = new PluginParameter(controlID::stepSeqModEndIndex, "SSMod End", "", controlVariableType::kInt, 1.000000, 8.000000, 8.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&stepSeqModEndIndex, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: SSMod Loop Dir
	piParam = new PluginParameter(controlID::stepSeqModLoopDir, "SSMod Loop Dir", "forward,backward,fwrd bckwrd", "forward");
	piParam->setBoundVariable(&stepSeqModLoopDir, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- meter control: Time1
	piParam = new PluginParameter(controlID::timing1Meter, "Time1", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&timing1Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: Time2
	piParam = new PluginParameter(controlID::timing2Meter, "Time2", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&timing2Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: Time3
	piParam = new PluginParameter(controlID::timing3Meter, "Time3", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&timing3Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: Time4
	piParam = new PluginParameter(controlID::timing4Meter, "Time4", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&timing4Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: Time5
	piParam = new PluginParameter(controlID::timing5Meter, "Time5", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&timing5Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: Time6
	piParam = new PluginParameter(controlID::timing6Meter, "Time6", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&timing6Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: Time7
	piParam = new PluginParameter(controlID::timing7Meter, "Time7", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&timing7Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: Time8
	piParam = new PluginParameter(controlID::timing8Meter, "Time8", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&timing8Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: wave1
	piParam = new PluginParameter(controlID::wave1Meter, "wave1", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&wave1Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: wave2
	piParam = new PluginParameter(controlID::wave2Meter, "wave2", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&wave2Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: wave3
	piParam = new PluginParameter(controlID::wave3Meter, "wave3", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&wave3Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: wave4
	piParam = new PluginParameter(controlID::wave4Meter, "wave4", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&wave4Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: wave5
	piParam = new PluginParameter(controlID::wave5Meter, "wave5", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&wave5Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: wave6
	piParam = new PluginParameter(controlID::wave6Meter, "wave6", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&wave6Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: wave7
	piParam = new PluginParameter(controlID::wave7Meter, "wave7", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&wave7Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: wave8
	piParam = new PluginParameter(controlID::wave8Meter, "wave8", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&wave8Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: pitch1
	piParam = new PluginParameter(controlID::pitch1Meter, "pitch1", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&pitch1Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: pitch2
	piParam = new PluginParameter(controlID::pitch2Meter, "pitch2", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&pitch2Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: pitch3
	piParam = new PluginParameter(controlID::pitch3Meter, "pitch3", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&pitch3Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: pitch4
	piParam = new PluginParameter(controlID::pitch4Meter, "pitch4", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&pitch4Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: pitch5
	piParam = new PluginParameter(controlID::pitch5Meter, "pitch5", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&pitch5Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: pitch6
	piParam = new PluginParameter(controlID::pitch6Meter, "pitch6", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&pitch6Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: pitch7
	piParam = new PluginParameter(controlID::pitch7Meter, "pitch7", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&pitch7Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: pitch8
	piParam = new PluginParameter(controlID::pitch8Meter, "pitch8", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&pitch8Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: ssMod1
	piParam = new PluginParameter(controlID::ssMod1Meter, "ssMod1", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&ssMod1Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: ssMod2
	piParam = new PluginParameter(controlID::ssMod2Meter, "ssMod2", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&ssMod2Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: ssMod3
	piParam = new PluginParameter(controlID::ssMod3Meter, "ssMod3", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&ssMod3Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: ssMod4
	piParam = new PluginParameter(controlID::ssMod4Meter, "ssMod4", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&ssMod4Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: ssMod5
	piParam = new PluginParameter(controlID::ssMod5Meter, "ssMod5", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&ssMod5Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: ssMod6
	piParam = new PluginParameter(controlID::ssMod6Meter, "ssMod6", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&ssMod6Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: ssMod7
	piParam = new PluginParameter(controlID::ssMod7Meter, "ssMod7", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&ssMod7Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: ssMod8
	piParam = new PluginParameter(controlID::ssMod8Meter, "ssMod8", 1.00, 1.00, ENVELOPE_DETECT_MODE_PEAK, meterCal::kLinearMeter);
	piParam->setBoundVariable(&ssMod8Meter, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- continuous control: Time Stretch
	piParam = new PluginParameter(controlID::timeStretch, "Time Stretch", "", controlVariableType::kDouble, -5.000000, 5.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&timeStretch, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: Step1 Type
	piParam = new PluginParameter(controlID::step1Type, "Step1 Type", "note,rest", "note");
	piParam->setBoundVariable(&step1Type, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Step2 Type
	piParam = new PluginParameter(controlID::step2Type, "Step2 Type", "note,rest", "note");
	piParam->setBoundVariable(&step2Type, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Step3 Type
	piParam = new PluginParameter(controlID::step3Type, "Step3 Type", "note,rest", "note");
	piParam->setBoundVariable(&step3Type, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Step4 Type
	piParam = new PluginParameter(controlID::step4Type, "Step4 Type", "note,rest", "note");
	piParam->setBoundVariable(&step4Type, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Step5 Type
	piParam = new PluginParameter(controlID::step5Type, "Step5 Type", "note,rest", "note");
	piParam->setBoundVariable(&step5Type, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Step6 Type
	piParam = new PluginParameter(controlID::step6Type, "Step6 Type", "note,rest", "note");
	piParam->setBoundVariable(&step6Type, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Step7 Type
	piParam = new PluginParameter(controlID::step7Type, "Step7 Type", "note,rest", "note");
	piParam->setBoundVariable(&step7Type, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Step8 Type
	piParam = new PluginParameter(controlID::step8Type, "Step8 Type", "note,rest", "note");
	piParam->setBoundVariable(&step8Type, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Interp Mod
	piParam = new PluginParameter(controlID::interpolateStepSeqMod, "Interp Mod", "SWITCH OFF,SWITCH ON", "SWITCH ON");
	piParam->setBoundVariable(&interpolateStepSeqMod, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Random Step
	piParam = new PluginParameter(controlID::randomizeStepOrder, "Random Step", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&randomizeStepOrder, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Random Pitch
	piParam = new PluginParameter(controlID::randomizePitchOrder, "Random Pitch", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&randomizePitchOrder, boundVariableType::kInt);
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
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&leftDelay_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Delay R
	piParam = new PluginParameter(controlID::rightDelay_mSec, "Delay R", "mSec", controlVariableType::kDouble, 0.000000, 2000.000000, 500.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&rightDelay_mSec, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Feedback
	piParam = new PluginParameter(controlID::feedback_Pct, "Feedback", "%", controlVariableType::kDouble, 0.000000, 100.000000, 20.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&feedback_Pct, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Delay Dry
	piParam = new PluginParameter(controlID::dryLevel_dB, "Delay Dry", "dB", controlVariableType::kDouble, -60.000000, 12.000000, -6.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&dryLevel_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Delay Wet
	piParam = new PluginParameter(controlID::wetLevel_dB, "Delay Wet", "dB", controlVariableType::kDouble, -60.000000, 12.000000, -6.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&wetLevel_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: Random Wave
	piParam = new PluginParameter(controlID::randomizeWaveOrder, "Random Wave", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&randomizeWaveOrder, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Random SSMod
	piParam = new PluginParameter(controlID::randomizeSSModOrder, "Random SSMod", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&randomizeSSModOrder, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: LFO2 fo Int
	piParam = new PluginParameter(controlID::lfo2_fo_Int, "LFO2 fo Int", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo2_fo_Int, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Osc fo Int
	piParam = new PluginParameter(controlID::osc_fo_Int, "Osc fo Int", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&osc_fo_Int, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Osc Unique Int
	piParam = new PluginParameter(controlID::osc_UniqueInt, "Osc Unique Int", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&osc_UniqueInt, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FiltEG Trig
	piParam = new PluginParameter(controlID::filterEGTrigInt, "FiltEG Trig", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&filterEGTrigInt, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: AuxEG Trig
	piParam = new PluginParameter(controlID::auxEGTrigInt, "AuxEG Trig", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&auxEGTrigInt, boundVariableType::kDouble);
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

	// --- continuous control: DCA Pan
	piParam = new PluginParameter(controlID::dcaPanInt, "DCA Pan", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&dcaPanInt, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: AmpEG Trig
	piParam = new PluginParameter(controlID::ampEGTrigInt, "AmpEG Trig", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&ampEGTrigInt, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO1 Out
	piParam = new PluginParameter(controlID::lfo1SourceInt, "LFO1 Out", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo1SourceInt, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: lfo1 lfo2fc
	piParam = new PluginParameter(controlID::lfo1_lfo2_fc, "lfo1 lfo2fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo1_lfo2_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo1_osc_fc
	piParam = new PluginParameter(controlID::lfo1_osc_fc, "lfo1_osc_fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo1_osc_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo1_oscUnique
	piParam = new PluginParameter(controlID::lfo1_oscUnique, "lfo1_oscUnique", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo1_oscUnique, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo1_filterEGTrig
	piParam = new PluginParameter(controlID::lfo1_filterEGTrig, "lfo1_filterEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo1_filterEGTrig, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo1_auxEGTrig
	piParam = new PluginParameter(controlID::lfo1_auxEGTrig, "lfo1_auxEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo1_auxEGTrig, boundVariableType::kInt);
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

	// --- discrete control: lfo1 Pan
	piParam = new PluginParameter(controlID::lfo1_dcaPan, "lfo1 Pan", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo1_dcaPan, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo1_AmpEGTrig
	piParam = new PluginParameter(controlID::lfo1_ampEGTrig, "lfo1_AmpEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo1_ampEGTrig, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: LFO2 Out
	piParam = new PluginParameter(controlID::lfo2SourceInt, "LFO2 Out", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&lfo2SourceInt, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: lfo2 lfo2fc
	piParam = new PluginParameter(controlID::lfo2_lfo2_fc, "lfo2 lfo2fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo2_lfo2_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo2_osc_fc
	piParam = new PluginParameter(controlID::lfo2_osc_fc, "lfo2_osc_fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo2_osc_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo2_oscUnique
	piParam = new PluginParameter(controlID::lfo2_oscUnique, "lfo2_oscUnique", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo2_oscUnique, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo2_filterEGTrig
	piParam = new PluginParameter(controlID::lfo2_filterEGTrig, "lfo2_filterEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo2_filterEGTrig, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo2_auxEGTrig
	piParam = new PluginParameter(controlID::lfo2_auxEGTrig, "lfo2_auxEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo2_auxEGTrig, boundVariableType::kInt);
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

	// --- discrete control: lfo2 Pan
	piParam = new PluginParameter(controlID::lfo2_dcaPan, "lfo2 Pan", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo2_dcaPan, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: lfo2_AmpEGTrig
	piParam = new PluginParameter(controlID::lfo2_ampEGTrig, "lfo2_AmpEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&lfo2_ampEGTrig, boundVariableType::kInt);
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

	// --- discrete control: filterEG_osc_fc
	piParam = new PluginParameter(controlID::filterEG_osc_fc, "filterEG_osc_fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&filterEG_osc_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: filterEG_oscUnique
	piParam = new PluginParameter(controlID::filterEG_oscUnique, "filterEG_oscUnique", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&filterEG_oscUnique, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: filterEG_filterEGTrig
	piParam = new PluginParameter(controlID::filterEG_filterEGTrig, "filterEG_filterEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&filterEG_filterEGTrig, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: filterEG_auxEGTrig
	piParam = new PluginParameter(controlID::filterEG_auxEGTrig, "filterEG_auxEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&filterEG_auxEGTrig, boundVariableType::kInt);
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

	// --- continuous control: AuxEG Out
	piParam = new PluginParameter(controlID::auxEGSourceInt, "AuxEG Out", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&auxEGSourceInt, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: auxEG lfo2fc
	piParam = new PluginParameter(controlID::auxEG_lfo2_fc, "auxEG lfo2fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEG_lfo2_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEG_osc_fc
	piParam = new PluginParameter(controlID::auxEG_osc_fc, "auxEG_osc_fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEG_osc_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEG_oscUnique
	piParam = new PluginParameter(controlID::auxEG_oscUnique, "auxEG_oscUnique", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEG_oscUnique, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEG_filterEGTrig
	piParam = new PluginParameter(controlID::auxEG_filterEGTrig, "auxEG_filterEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEG_filterEGTrig, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEG_auxEGTrig
	piParam = new PluginParameter(controlID::auxEG_auxEGTrig, "auxEG_auxEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEG_auxEGTrig, boundVariableType::kInt);
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

	// --- discrete control: auxEG Pan
	piParam = new PluginParameter(controlID::auxEG_dcaPan, "auxEG Pan", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEG_dcaPan, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEG_AmpEGTrig
	piParam = new PluginParameter(controlID::auxEG_ampEGTrig, "auxEG_AmpEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEG_ampEGTrig, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: AuxEG OutB
	piParam = new PluginParameter(controlID::auxEGBiasedSourceInt, "AuxEG OutB", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&auxEGBiasedSourceInt, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: auxEGB lfo2fc
	piParam = new PluginParameter(controlID::auxEGB_lfo2_fc, "auxEGB lfo2fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEGB_lfo2_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEGB_osc_fc
	piParam = new PluginParameter(controlID::auxEGB_osc_fc, "auxEGB_osc_fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEGB_osc_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEGB_filterEGTrig
	piParam = new PluginParameter(controlID::auxEGB_filterEGTrig, "auxEGB_filterEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEGB_filterEGTrig, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEGB_oscUnique
	piParam = new PluginParameter(controlID::auxEGB_oscUnique, "auxEGB_oscUnique", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEGB_oscUnique, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEGB_auxEGTrig
	piParam = new PluginParameter(controlID::auxEGB_auxEGTrig, "auxEGB_auxEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEGB_auxEGTrig, boundVariableType::kInt);
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

	// --- discrete control: auxEGB Pan
	piParam = new PluginParameter(controlID::auxEGB_dcaPan, "auxEGB Pan", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEGB_dcaPan, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: auxEGB_AmpEGTrig
	piParam = new PluginParameter(controlID::auxEGB_ampEGTrig, "auxEGB_AmpEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&auxEGB_ampEGTrig, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: WSeqMod Out
	piParam = new PluginParameter(controlID::waveSeqModSourceInt, "WSeqMod Out", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&waveSeqModSourceInt, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: waveSeqMod lfo2fc
	piParam = new PluginParameter(controlID::waveSeqMod_lfo2_fc, "waveSeqMod lfo2fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&waveSeqMod_lfo2_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: waveSeqMod_osc_fo
	piParam = new PluginParameter(controlID::waveSeqMod_osc_fo, "waveSeqMod_osc_fo", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&waveSeqMod_osc_fo, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: waveSeqMod_Unique
	piParam = new PluginParameter(controlID::waveSeqMod_oscUnique, "waveSeqMod_Unique", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&waveSeqMod_oscUnique, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: waveSeqMod_filterEGTrig
	piParam = new PluginParameter(controlID::waveSeqMod_filterEGTrig, "waveSeqMod_filterEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&waveSeqMod_filterEGTrig, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: waveSeqMod_auxrEGTrig
	piParam = new PluginParameter(controlID::waveSeqMod_auxEGTrig, "waveSeqMod_auxrEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&waveSeqMod_auxEGTrig, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: waveSeqMod_Flt1_Fc
	piParam = new PluginParameter(controlID::waveSeqMod_filter1_fc, "waveSeqMod_Flt1_Fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&waveSeqMod_filter1_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: waveSeqMod_Filt2_Fc
	piParam = new PluginParameter(controlID::waveSeqMod_filter2_fc, "waveSeqMod_Filt2_Fc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&waveSeqMod_filter2_fc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: waveSeqMod Pan
	piParam = new PluginParameter(controlID::waveSeqMod_dcaPan, "waveSeqMod Pan", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&waveSeqMod_dcaPan, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: waveSeqMod_AmpEGTrig
	piParam = new PluginParameter(controlID::waveSeqMod_ampEGTrig, "waveSeqMod_AmpEGTrig", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&waveSeqMod_ampEGTrig, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: DCA EG Mod
	piParam = new PluginParameter(controlID::ampEGIntensity, "DCA EG Mod", "", controlVariableType::kDouble, -1.000000, 1.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&ampEGIntensity, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WSeq1 Pan
	piParam = new PluginParameter(controlID::wseq1_panValue, "WSeq1 Pan", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&wseq1_panValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WSeq2 Pan
	piParam = new PluginParameter(controlID::wseq2_panValue, "WSeq2 Pan", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&wseq2_panValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WSeq3 Pan
	piParam = new PluginParameter(controlID::wseq3_panValue, "WSeq3 Pan", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&wseq3_panValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WSeq4 Pan
	piParam = new PluginParameter(controlID::wseq4_panValue, "WSeq4 Pan", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&wseq4_panValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WSeq5 Pan
	piParam = new PluginParameter(controlID::wseq5_panValue, "WSeq5 Pan", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&wseq5_panValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WSeq6 Pan
	piParam = new PluginParameter(controlID::wseq6_panValue, "WSeq6 Pan", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&wseq6_panValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WSeq7 Pan
	piParam = new PluginParameter(controlID::wseq7_panValue, "WSeq7 Pan", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&wseq7_panValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WSeq8 Pan
	piParam = new PluginParameter(controlID::wseq8_panValue, "WSeq8 Pan", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&wseq8_panValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: HSync1
	piParam = new PluginParameter(controlID::wseq1HardSync, "HSync1", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq1HardSync, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Morph1
	piParam = new PluginParameter(controlID::wseq1Morph, "Morph1", "", controlVariableType::kDouble, 0.000000, 1.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq1Morph, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: HSync2
	piParam = new PluginParameter(controlID::wseq2HardSync, "HSync2", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq2HardSync, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Morph2
	piParam = new PluginParameter(controlID::wseq2Morph, "Morph2", "", controlVariableType::kDouble, 0.000000, 1.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq2Morph, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: HSync3
	piParam = new PluginParameter(controlID::wseq3HardSync, "HSync3", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq3HardSync, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Morph3
	piParam = new PluginParameter(controlID::wseq3Morph, "Morph3", "", controlVariableType::kDouble, 0.000000, 1.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq3Morph, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: HSync4
	piParam = new PluginParameter(controlID::wseq4HardSync, "HSync4", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq4HardSync, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Morph4
	piParam = new PluginParameter(controlID::wseq4Morph, "Morph4", "", controlVariableType::kDouble, 0.000000, 1.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq4Morph, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: HSync5
	piParam = new PluginParameter(controlID::wseq5HardSync, "HSync5", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq5HardSync, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Morph5
	piParam = new PluginParameter(controlID::wseq5Morph, "Morph5", "", controlVariableType::kDouble, 0.000000, 1.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq5Morph, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: HSync6
	piParam = new PluginParameter(controlID::wseq6HardSync, "HSync6", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq6HardSync, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Morph6
	piParam = new PluginParameter(controlID::wseq6Morph, "Morph6", "", controlVariableType::kDouble, 0.000000, 1.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq6Morph, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: HSync7
	piParam = new PluginParameter(controlID::wseq7HardSync, "HSync7", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq7HardSync, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Morph7
	piParam = new PluginParameter(controlID::wseq7Morph, "Morph7", "", controlVariableType::kDouble, 0.000000, 1.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq7Morph, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: HSync8
	piParam = new PluginParameter(controlID::wseq8HardSync, "HSync8", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq8HardSync, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Morph8
	piParam = new PluginParameter(controlID::wseq8Morph, "Morph8", "", controlVariableType::kDouble, 0.000000, 1.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq8Morph, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WSeq1 Coarse
	piParam = new PluginParameter(controlID::wseq1DetuneSemis, "WSeq1 Coarse", "", controlVariableType::kInt, -12.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq1DetuneSemis, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: WSeq1 Fine
	piParam = new PluginParameter(controlID::wseq1DetuneCents, "WSeq1 Fine", "cents", controlVariableType::kDouble, -50.000000, 50.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq1DetuneCents, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WSeq2 Coarse
	piParam = new PluginParameter(controlID::wseq2DetuneSemis, "WSeq2 Coarse", "", controlVariableType::kInt, -12.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq2DetuneSemis, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: WSeq2 Fine
	piParam = new PluginParameter(controlID::wseq2DetuneCents, "WSeq2 Fine", "cents", controlVariableType::kDouble, -50.000000, 50.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq2DetuneCents, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WSeq3 Coarse
	piParam = new PluginParameter(controlID::wseq3DetuneSemis, "WSeq3 Coarse", "", controlVariableType::kInt, -12.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq3DetuneSemis, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: WSeq3 Fine
	piParam = new PluginParameter(controlID::wseq3DetuneCents, "WSeq3 Fine", "cents", controlVariableType::kDouble, -50.000000, 50.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq3DetuneCents, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WSeq4 Coarse
	piParam = new PluginParameter(controlID::wseq4DetuneSemis, "WSeq4 Coarse", "", controlVariableType::kInt, -12.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq4DetuneSemis, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: WSeq4 Fine
	piParam = new PluginParameter(controlID::wseq4DetuneCents, "WSeq4 Fine", "cents", controlVariableType::kDouble, -50.000000, 50.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq4DetuneCents, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WSeq5 Coarse
	piParam = new PluginParameter(controlID::wseq5DetuneSemis, "WSeq5 Coarse", "", controlVariableType::kInt, -12.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq5DetuneSemis, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: WSeq5 Fine
	piParam = new PluginParameter(controlID::wseq5DetuneCents, "WSeq5 Fine", "cents", controlVariableType::kDouble, -50.000000, 50.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq5DetuneCents, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WSeq6 Coarse
	piParam = new PluginParameter(controlID::wseq6DetuneSemis, "WSeq6 Coarse", "", controlVariableType::kInt, -12.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq6DetuneSemis, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: WSeq6 Fine
	piParam = new PluginParameter(controlID::wseq6DetuneCents, "WSeq6 Fine", "cents", controlVariableType::kDouble, -50.000000, 50.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq6DetuneCents, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WSeq7 Coarse
	piParam = new PluginParameter(controlID::wseq7DetuneSemis, "WSeq7 Coarse", "", controlVariableType::kInt, -12.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq7DetuneSemis, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: WSeq7 Fine
	piParam = new PluginParameter(controlID::wseq7DetuneCents, "WSeq7 Fine", "cents", controlVariableType::kDouble, -50.000000, 50.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq7DetuneCents, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: WSeq8 Coarse
	piParam = new PluginParameter(controlID::wseq8DetuneSemis, "WSeq8 Coarse", "", controlVariableType::kInt, -12.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq8DetuneSemis, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: WSeq8 Fine
	piParam = new PluginParameter(controlID::wseq8DetuneCents, "WSeq8 Fine", "cents", controlVariableType::kDouble, -50.000000, 50.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wseq8DetuneCents, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- non-GUI-bound variable: LFO_SW
	piParam = new PluginParameter(controlID::LFO_SW, "LFO_SW");
	addPluginParameter(piParam);

	// --- non-GUI-bound variable: EG_SW
	piParam = new PluginParameter(controlID::EG_SW, "EG_SW");
	addPluginParameter(piParam);

	// --- non-GUI-bound variable: FILTER_SW
	piParam = new PluginParameter(controlID::FILTER_SW, "FILTER_SW");
	addPluginParameter(piParam);

	// --- non-GUI-bound variable: MAIN_SW
	piParam = new PluginParameter(controlID::MAIN_SW, "MAIN_SW");
	addPluginParameter(piParam);

	// --- discrete control: Solo Wave
	piParam = new PluginParameter(controlID::soloWaveLane, "Solo Wave", "OFF,Wave WS1,Wave WS2,Wave WS3,Wave WS4,Wave WS5,Wave WS6,Wave WS7,Wave WS8", "OFF");
	piParam->setBoundVariable(&soloWaveLane, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Run/Pause
	piParam = new PluginParameter(controlID::runStopWS, "Run/Pause", "RUN,PAUSE", "RUN");
	piParam->setBoundVariable(&runStopWS, boundVariableType::kInt);
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

	// --- controlID::ws1WaveAmp_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::ws1WaveAmp_dB, auxAttribute);

	// --- controlID::ws1StepLenIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483654);
	setParamAuxAttribute(controlID::ws1StepLenIndex, auxAttribute);

	// --- controlID::ws1XFadeLenIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483658);
	setParamAuxAttribute(controlID::ws1XFadeLenIndex, auxAttribute);

	// --- controlID::ws1Pitch_semi
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483660);
	setParamAuxAttribute(controlID::ws1Pitch_semi, auxAttribute);

	// --- controlID::ws1PitchProb_pct
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483652);
	setParamAuxAttribute(controlID::ws1PitchProb_pct, auxAttribute);

	// --- controlID::ws1ModValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483662);
	setParamAuxAttribute(controlID::ws1ModValue, auxAttribute);

	// --- controlID::ws1ModProb_pct
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483652);
	setParamAuxAttribute(controlID::ws1ModProb_pct, auxAttribute);

	// --- controlID::ws1WaveIndex
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::ws1WaveIndex, auxAttribute);

	// --- controlID::ws1WaveIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::ws1WaveIndex, auxAttribute);

	// --- controlID::ws2StepLenIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483654);
	setParamAuxAttribute(controlID::ws2StepLenIndex, auxAttribute);

	// --- controlID::ws2XFadeLenIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483658);
	setParamAuxAttribute(controlID::ws2XFadeLenIndex, auxAttribute);

	// --- controlID::ws2WaveIndex
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::ws2WaveIndex, auxAttribute);

	// --- controlID::ws2WaveIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::ws2WaveIndex, auxAttribute);

	// --- controlID::ws2WaveAmp_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::ws2WaveAmp_dB, auxAttribute);

	// --- controlID::ws2Pitch_semi
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483660);
	setParamAuxAttribute(controlID::ws2Pitch_semi, auxAttribute);

	// --- controlID::ws2PitchProb_pct
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483652);
	setParamAuxAttribute(controlID::ws2PitchProb_pct, auxAttribute);

	// --- controlID::ws2ModValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483662);
	setParamAuxAttribute(controlID::ws2ModValue, auxAttribute);

	// --- controlID::ws2ModProb_pct
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483652);
	setParamAuxAttribute(controlID::ws2ModProb_pct, auxAttribute);

	// --- controlID::ws3StepLenIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483654);
	setParamAuxAttribute(controlID::ws3StepLenIndex, auxAttribute);

	// --- controlID::ws3XFadeLenIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483658);
	setParamAuxAttribute(controlID::ws3XFadeLenIndex, auxAttribute);

	// --- controlID::ws3WaveIndex
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::ws3WaveIndex, auxAttribute);

	// --- controlID::ws3WaveIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::ws3WaveIndex, auxAttribute);

	// --- controlID::ws3WaveAmp_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::ws3WaveAmp_dB, auxAttribute);

	// --- controlID::ws3Pitch_semi
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483660);
	setParamAuxAttribute(controlID::ws3Pitch_semi, auxAttribute);

	// --- controlID::ws3PitchProb_pct
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483652);
	setParamAuxAttribute(controlID::ws3PitchProb_pct, auxAttribute);

	// --- controlID::ws3ModValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483662);
	setParamAuxAttribute(controlID::ws3ModValue, auxAttribute);

	// --- controlID::ws3ModProb_pct
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483652);
	setParamAuxAttribute(controlID::ws3ModProb_pct, auxAttribute);

	// --- controlID::ws4StepLenIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483654);
	setParamAuxAttribute(controlID::ws4StepLenIndex, auxAttribute);

	// --- controlID::ws4XFadeLenIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483658);
	setParamAuxAttribute(controlID::ws4XFadeLenIndex, auxAttribute);

	// --- controlID::ws4WaveIndex
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::ws4WaveIndex, auxAttribute);

	// --- controlID::ws4WaveIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::ws4WaveIndex, auxAttribute);

	// --- controlID::ws4WaveAmp_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::ws4WaveAmp_dB, auxAttribute);

	// --- controlID::ws4Pitch_semi
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483660);
	setParamAuxAttribute(controlID::ws4Pitch_semi, auxAttribute);

	// --- controlID::ws4PitchProb_pct
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483652);
	setParamAuxAttribute(controlID::ws4PitchProb_pct, auxAttribute);

	// --- controlID::ws4ModValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483662);
	setParamAuxAttribute(controlID::ws4ModValue, auxAttribute);

	// --- controlID::ws4ModProb_pct
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483652);
	setParamAuxAttribute(controlID::ws4ModProb_pct, auxAttribute);

	// --- controlID::ws5StepLenIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483654);
	setParamAuxAttribute(controlID::ws5StepLenIndex, auxAttribute);

	// --- controlID::ws5XFadeLenIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483658);
	setParamAuxAttribute(controlID::ws5XFadeLenIndex, auxAttribute);

	// --- controlID::ws5WaveIndex
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::ws5WaveIndex, auxAttribute);

	// --- controlID::ws5WaveIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::ws5WaveIndex, auxAttribute);

	// --- controlID::ws5WaveAmp_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::ws5WaveAmp_dB, auxAttribute);

	// --- controlID::ws5Pitch_semi
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483660);
	setParamAuxAttribute(controlID::ws5Pitch_semi, auxAttribute);

	// --- controlID::ws5PitchProb_pct
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483652);
	setParamAuxAttribute(controlID::ws5PitchProb_pct, auxAttribute);

	// --- controlID::ws5ModValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483662);
	setParamAuxAttribute(controlID::ws5ModValue, auxAttribute);

	// --- controlID::ws5ModProb_pct
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483652);
	setParamAuxAttribute(controlID::ws5ModProb_pct, auxAttribute);

	// --- controlID::ws6StepLenIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483654);
	setParamAuxAttribute(controlID::ws6StepLenIndex, auxAttribute);

	// --- controlID::ws6XFadeLenIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483658);
	setParamAuxAttribute(controlID::ws6XFadeLenIndex, auxAttribute);

	// --- controlID::ws6WaveIndex
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::ws6WaveIndex, auxAttribute);

	// --- controlID::ws6WaveIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::ws6WaveIndex, auxAttribute);

	// --- controlID::ws6WaveAmp_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::ws6WaveAmp_dB, auxAttribute);

	// --- controlID::ws6Pitch_semi
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483660);
	setParamAuxAttribute(controlID::ws6Pitch_semi, auxAttribute);

	// --- controlID::ws6PitchProb_pct
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483652);
	setParamAuxAttribute(controlID::ws6PitchProb_pct, auxAttribute);

	// --- controlID::ws6ModValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483662);
	setParamAuxAttribute(controlID::ws6ModValue, auxAttribute);

	// --- controlID::ws6ModProb_pct
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483652);
	setParamAuxAttribute(controlID::ws6ModProb_pct, auxAttribute);

	// --- controlID::ws7StepLenIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483654);
	setParamAuxAttribute(controlID::ws7StepLenIndex, auxAttribute);

	// --- controlID::ws7XFadeLenIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483658);
	setParamAuxAttribute(controlID::ws7XFadeLenIndex, auxAttribute);

	// --- controlID::ws7WaveIndex
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::ws7WaveIndex, auxAttribute);

	// --- controlID::ws7WaveIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::ws7WaveIndex, auxAttribute);

	// --- controlID::ws7WaveAmp_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::ws7WaveAmp_dB, auxAttribute);

	// --- controlID::ws7Pitch_semi
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483660);
	setParamAuxAttribute(controlID::ws7Pitch_semi, auxAttribute);

	// --- controlID::ws7PitchProb_pct
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483652);
	setParamAuxAttribute(controlID::ws7PitchProb_pct, auxAttribute);

	// --- controlID::ws7ModValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483662);
	setParamAuxAttribute(controlID::ws7ModValue, auxAttribute);

	// --- controlID::ws7ModProb_pct
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483652);
	setParamAuxAttribute(controlID::ws7ModProb_pct, auxAttribute);

	// --- controlID::ws8StepLenIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483654);
	setParamAuxAttribute(controlID::ws8StepLenIndex, auxAttribute);

	// --- controlID::ws8XFadeLenIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483658);
	setParamAuxAttribute(controlID::ws8XFadeLenIndex, auxAttribute);

	// --- controlID::ws8WaveIndex
	auxAttribute.reset(65536);
	auxAttribute.setBoolAttribute(true);
	setParamAuxAttribute(controlID::ws8WaveIndex, auxAttribute);

	// --- controlID::ws8WaveIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::ws8WaveIndex, auxAttribute);

	// --- controlID::ws8WaveAmp_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::ws8WaveAmp_dB, auxAttribute);

	// --- controlID::ws8Pitch_semi
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483660);
	setParamAuxAttribute(controlID::ws8Pitch_semi, auxAttribute);

	// --- controlID::ws8PitchProb_pct
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483652);
	setParamAuxAttribute(controlID::ws8PitchProb_pct, auxAttribute);

	// --- controlID::ws8ModValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483662);
	setParamAuxAttribute(controlID::ws8ModValue, auxAttribute);

	// --- controlID::ws8ModProb_pct
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483652);
	setParamAuxAttribute(controlID::ws8ModProb_pct, auxAttribute);

	// --- controlID::timingStartIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::timingStartIndex, auxAttribute);

	// --- controlID::timingEndIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::timingEndIndex, auxAttribute);

	// --- controlID::timingLoopDir
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::timingLoopDir, auxAttribute);

	// --- controlID::waveStartIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::waveStartIndex, auxAttribute);

	// --- controlID::waveEndIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::waveEndIndex, auxAttribute);

	// --- controlID::waveLoopDir
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::waveLoopDir, auxAttribute);

	// --- controlID::pitchStartIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::pitchStartIndex, auxAttribute);

	// --- controlID::pitchEndIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::pitchEndIndex, auxAttribute);

	// --- controlID::pitchLoopDir
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::pitchLoopDir, auxAttribute);

	// --- controlID::stepSeqModStartIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::stepSeqModStartIndex, auxAttribute);

	// --- controlID::stepSeqModEndIndex
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::stepSeqModEndIndex, auxAttribute);

	// --- controlID::stepSeqModLoopDir
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::stepSeqModLoopDir, auxAttribute);

	// --- controlID::timing1Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::timing1Meter, auxAttribute);

	// --- controlID::timing2Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::timing2Meter, auxAttribute);

	// --- controlID::timing3Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::timing3Meter, auxAttribute);

	// --- controlID::timing4Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::timing4Meter, auxAttribute);

	// --- controlID::timing5Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::timing5Meter, auxAttribute);

	// --- controlID::timing6Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::timing6Meter, auxAttribute);

	// --- controlID::timing7Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::timing7Meter, auxAttribute);

	// --- controlID::timing8Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::timing8Meter, auxAttribute);

	// --- controlID::wave1Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::wave1Meter, auxAttribute);

	// --- controlID::wave2Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::wave2Meter, auxAttribute);

	// --- controlID::wave3Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::wave3Meter, auxAttribute);

	// --- controlID::wave4Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::wave4Meter, auxAttribute);

	// --- controlID::wave5Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::wave5Meter, auxAttribute);

	// --- controlID::wave6Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::wave6Meter, auxAttribute);

	// --- controlID::wave7Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::wave7Meter, auxAttribute);

	// --- controlID::wave8Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::wave8Meter, auxAttribute);

	// --- controlID::pitch1Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::pitch1Meter, auxAttribute);

	// --- controlID::pitch2Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::pitch2Meter, auxAttribute);

	// --- controlID::pitch3Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::pitch3Meter, auxAttribute);

	// --- controlID::pitch4Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::pitch4Meter, auxAttribute);

	// --- controlID::pitch5Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::pitch5Meter, auxAttribute);

	// --- controlID::pitch6Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::pitch6Meter, auxAttribute);

	// --- controlID::pitch7Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::pitch7Meter, auxAttribute);

	// --- controlID::pitch8Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::pitch8Meter, auxAttribute);

	// --- controlID::ssMod1Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::ssMod1Meter, auxAttribute);

	// --- controlID::ssMod2Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::ssMod2Meter, auxAttribute);

	// --- controlID::ssMod3Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::ssMod3Meter, auxAttribute);

	// --- controlID::ssMod4Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::ssMod4Meter, auxAttribute);

	// --- controlID::ssMod5Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::ssMod5Meter, auxAttribute);

	// --- controlID::ssMod6Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::ssMod6Meter, auxAttribute);

	// --- controlID::ssMod7Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::ssMod7Meter, auxAttribute);

	// --- controlID::ssMod8Meter
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::ssMod8Meter, auxAttribute);

	// --- controlID::timeStretch
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::timeStretch, auxAttribute);

	// --- controlID::step1Type
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::step1Type, auxAttribute);

	// --- controlID::step2Type
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::step2Type, auxAttribute);

	// --- controlID::step3Type
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::step3Type, auxAttribute);

	// --- controlID::step4Type
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::step4Type, auxAttribute);

	// --- controlID::step5Type
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::step5Type, auxAttribute);

	// --- controlID::step6Type
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::step6Type, auxAttribute);

	// --- controlID::step7Type
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::step7Type, auxAttribute);

	// --- controlID::step8Type
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::step8Type, auxAttribute);

	// --- controlID::interpolateStepSeqMod
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::interpolateStepSeqMod, auxAttribute);

	// --- controlID::randomizeStepOrder
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::randomizeStepOrder, auxAttribute);

	// --- controlID::randomizePitchOrder
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::randomizePitchOrder, auxAttribute);

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

	// --- controlID::randomizeWaveOrder
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::randomizeWaveOrder, auxAttribute);

	// --- controlID::randomizeSSModOrder
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::randomizeSSModOrder, auxAttribute);

	// --- controlID::lfo2_fo_Int
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483719);
	setParamAuxAttribute(controlID::lfo2_fo_Int, auxAttribute);

	// --- controlID::osc_fo_Int
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483719);
	setParamAuxAttribute(controlID::osc_fo_Int, auxAttribute);

	// --- controlID::osc_UniqueInt
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483719);
	setParamAuxAttribute(controlID::osc_UniqueInt, auxAttribute);

	// --- controlID::filterEGTrigInt
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483719);
	setParamAuxAttribute(controlID::filterEGTrigInt, auxAttribute);

	// --- controlID::auxEGTrigInt
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483719);
	setParamAuxAttribute(controlID::auxEGTrigInt, auxAttribute);

	// --- controlID::filter1_fc_Int
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483719);
	setParamAuxAttribute(controlID::filter1_fc_Int, auxAttribute);

	// --- controlID::filter2_fc_Int
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483719);
	setParamAuxAttribute(controlID::filter2_fc_Int, auxAttribute);

	// --- controlID::dcaPanInt
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483719);
	setParamAuxAttribute(controlID::dcaPanInt, auxAttribute);

	// --- controlID::ampEGTrigInt
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483719);
	setParamAuxAttribute(controlID::ampEGTrigInt, auxAttribute);

	// --- controlID::lfo1SourceInt
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483717);
	setParamAuxAttribute(controlID::lfo1SourceInt, auxAttribute);

	// --- controlID::lfo1_lfo2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo1_lfo2_fc, auxAttribute);

	// --- controlID::lfo1_osc_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo1_osc_fc, auxAttribute);

	// --- controlID::lfo1_oscUnique
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo1_oscUnique, auxAttribute);

	// --- controlID::lfo1_filterEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo1_filterEGTrig, auxAttribute);

	// --- controlID::lfo1_auxEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo1_auxEGTrig, auxAttribute);

	// --- controlID::lfo1_filter1_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo1_filter1_fc, auxAttribute);

	// --- controlID::lfo1_filter2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo1_filter2_fc, auxAttribute);

	// --- controlID::lfo1_dcaPan
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo1_dcaPan, auxAttribute);

	// --- controlID::lfo1_ampEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo1_ampEGTrig, auxAttribute);

	// --- controlID::lfo2SourceInt
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483717);
	setParamAuxAttribute(controlID::lfo2SourceInt, auxAttribute);

	// --- controlID::lfo2_lfo2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo2_lfo2_fc, auxAttribute);

	// --- controlID::lfo2_osc_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo2_osc_fc, auxAttribute);

	// --- controlID::lfo2_oscUnique
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo2_oscUnique, auxAttribute);

	// --- controlID::lfo2_filterEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo2_filterEGTrig, auxAttribute);

	// --- controlID::lfo2_auxEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo2_auxEGTrig, auxAttribute);

	// --- controlID::lfo2_filter1_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo2_filter1_fc, auxAttribute);

	// --- controlID::lfo2_filter2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo2_filter2_fc, auxAttribute);

	// --- controlID::lfo2_dcaPan
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo2_dcaPan, auxAttribute);

	// --- controlID::lfo2_ampEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::lfo2_ampEGTrig, auxAttribute);

	// --- controlID::filterEGSourceInt
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483717);
	setParamAuxAttribute(controlID::filterEGSourceInt, auxAttribute);

	// --- controlID::filterEG_lfo2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::filterEG_lfo2_fc, auxAttribute);

	// --- controlID::filterEG_osc_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::filterEG_osc_fc, auxAttribute);

	// --- controlID::filterEG_oscUnique
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::filterEG_oscUnique, auxAttribute);

	// --- controlID::filterEG_filterEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::filterEG_filterEGTrig, auxAttribute);

	// --- controlID::filterEG_auxEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::filterEG_auxEGTrig, auxAttribute);

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

	// --- controlID::auxEGSourceInt
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483717);
	setParamAuxAttribute(controlID::auxEGSourceInt, auxAttribute);

	// --- controlID::auxEG_lfo2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEG_lfo2_fc, auxAttribute);

	// --- controlID::auxEG_osc_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEG_osc_fc, auxAttribute);

	// --- controlID::auxEG_oscUnique
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEG_oscUnique, auxAttribute);

	// --- controlID::auxEG_filterEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEG_filterEGTrig, auxAttribute);

	// --- controlID::auxEG_auxEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEG_auxEGTrig, auxAttribute);

	// --- controlID::auxEG_filter1_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEG_filter1_fc, auxAttribute);

	// --- controlID::auxEG_filter2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEG_filter2_fc, auxAttribute);

	// --- controlID::auxEG_dcaPan
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEG_dcaPan, auxAttribute);

	// --- controlID::auxEG_ampEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEG_ampEGTrig, auxAttribute);

	// --- controlID::auxEGBiasedSourceInt
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483717);
	setParamAuxAttribute(controlID::auxEGBiasedSourceInt, auxAttribute);

	// --- controlID::auxEGB_lfo2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEGB_lfo2_fc, auxAttribute);

	// --- controlID::auxEGB_osc_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEGB_osc_fc, auxAttribute);

	// --- controlID::auxEGB_filterEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEGB_filterEGTrig, auxAttribute);

	// --- controlID::auxEGB_oscUnique
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEGB_oscUnique, auxAttribute);

	// --- controlID::auxEGB_auxEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEGB_auxEGTrig, auxAttribute);

	// --- controlID::auxEGB_filter1_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEGB_filter1_fc, auxAttribute);

	// --- controlID::auxEGB_filter2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEGB_filter2_fc, auxAttribute);

	// --- controlID::auxEGB_dcaPan
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEGB_dcaPan, auxAttribute);

	// --- controlID::auxEGB_ampEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::auxEGB_ampEGTrig, auxAttribute);

	// --- controlID::waveSeqModSourceInt
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483717);
	setParamAuxAttribute(controlID::waveSeqModSourceInt, auxAttribute);

	// --- controlID::waveSeqMod_lfo2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::waveSeqMod_lfo2_fc, auxAttribute);

	// --- controlID::waveSeqMod_osc_fo
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::waveSeqMod_osc_fo, auxAttribute);

	// --- controlID::waveSeqMod_oscUnique
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::waveSeqMod_oscUnique, auxAttribute);

	// --- controlID::waveSeqMod_filterEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::waveSeqMod_filterEGTrig, auxAttribute);

	// --- controlID::waveSeqMod_auxEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::waveSeqMod_auxEGTrig, auxAttribute);

	// --- controlID::waveSeqMod_filter1_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::waveSeqMod_filter1_fc, auxAttribute);

	// --- controlID::waveSeqMod_filter2_fc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::waveSeqMod_filter2_fc, auxAttribute);

	// --- controlID::waveSeqMod_dcaPan
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::waveSeqMod_dcaPan, auxAttribute);

	// --- controlID::waveSeqMod_ampEGTrig
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::waveSeqMod_ampEGTrig, auxAttribute);

	// --- controlID::ampEGIntensity
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483683);
	setParamAuxAttribute(controlID::ampEGIntensity, auxAttribute);

	// --- controlID::wseq1_panValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq1_panValue, auxAttribute);

	// --- controlID::wseq2_panValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq2_panValue, auxAttribute);

	// --- controlID::wseq3_panValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq3_panValue, auxAttribute);

	// --- controlID::wseq4_panValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq4_panValue, auxAttribute);

	// --- controlID::wseq5_panValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq5_panValue, auxAttribute);

	// --- controlID::wseq6_panValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq6_panValue, auxAttribute);

	// --- controlID::wseq7_panValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq7_panValue, auxAttribute);

	// --- controlID::wseq8_panValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq8_panValue, auxAttribute);

	// --- controlID::wseq1HardSync
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq1HardSync, auxAttribute);

	// --- controlID::wseq1Morph
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq1Morph, auxAttribute);

	// --- controlID::wseq2HardSync
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq2HardSync, auxAttribute);

	// --- controlID::wseq2Morph
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq2Morph, auxAttribute);

	// --- controlID::wseq3HardSync
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq3HardSync, auxAttribute);

	// --- controlID::wseq3Morph
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq3Morph, auxAttribute);

	// --- controlID::wseq4HardSync
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq4HardSync, auxAttribute);

	// --- controlID::wseq4Morph
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq4Morph, auxAttribute);

	// --- controlID::wseq5HardSync
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq5HardSync, auxAttribute);

	// --- controlID::wseq5Morph
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq5Morph, auxAttribute);

	// --- controlID::wseq6HardSync
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq6HardSync, auxAttribute);

	// --- controlID::wseq6Morph
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq6Morph, auxAttribute);

	// --- controlID::wseq7HardSync
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq7HardSync, auxAttribute);

	// --- controlID::wseq7Morph
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq7Morph, auxAttribute);

	// --- controlID::wseq8HardSync
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq8HardSync, auxAttribute);

	// --- controlID::wseq8Morph
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483691);
	setParamAuxAttribute(controlID::wseq8Morph, auxAttribute);

	// --- controlID::wseq1DetuneSemis
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::wseq1DetuneSemis, auxAttribute);

	// --- controlID::wseq1DetuneCents
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::wseq1DetuneCents, auxAttribute);

	// --- controlID::wseq2DetuneSemis
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::wseq2DetuneSemis, auxAttribute);

	// --- controlID::wseq2DetuneCents
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::wseq2DetuneCents, auxAttribute);

	// --- controlID::wseq3DetuneSemis
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::wseq3DetuneSemis, auxAttribute);

	// --- controlID::wseq3DetuneCents
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::wseq3DetuneCents, auxAttribute);

	// --- controlID::wseq4DetuneSemis
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::wseq4DetuneSemis, auxAttribute);

	// --- controlID::wseq4DetuneCents
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::wseq4DetuneCents, auxAttribute);

	// --- controlID::wseq5DetuneSemis
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::wseq5DetuneSemis, auxAttribute);

	// --- controlID::wseq5DetuneCents
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::wseq5DetuneCents, auxAttribute);

	// --- controlID::wseq6DetuneSemis
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::wseq6DetuneSemis, auxAttribute);

	// --- controlID::wseq6DetuneCents
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::wseq6DetuneCents, auxAttribute);

	// --- controlID::wseq7DetuneSemis
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::wseq7DetuneSemis, auxAttribute);

	// --- controlID::wseq7DetuneCents
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::wseq7DetuneCents, auxAttribute);

	// --- controlID::wseq8DetuneSemis
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483685);
	setParamAuxAttribute(controlID::wseq8DetuneSemis, auxAttribute);

	// --- controlID::wseq8DetuneCents
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483687);
	setParamAuxAttribute(controlID::wseq8DetuneCents, auxAttribute);

	// --- controlID::soloWaveLane
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::soloWaveLane, auxAttribute);

	// --- controlID::runStopWS
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(268435456);
	setParamAuxAttribute(controlID::runStopWS, auxAttribute);


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


	// --- wave sequencer
	addAuxParamAtt(CUSTOM_OPTION_MENU, SynthLab::WAVE_SEQ_WAVES_1, controlID::ws1WaveIndex);
	addAuxParamAtt(CUSTOM_OPTION_MENU, SynthLab::WAVE_SEQ_WAVES_2, controlID::ws2WaveIndex);
	addAuxParamAtt(CUSTOM_OPTION_MENU, SynthLab::WAVE_SEQ_WAVES_3, controlID::ws3WaveIndex);
	addAuxParamAtt(CUSTOM_OPTION_MENU, SynthLab::WAVE_SEQ_WAVES_4, controlID::ws4WaveIndex);
	addAuxParamAtt(CUSTOM_OPTION_MENU, SynthLab::WAVE_SEQ_WAVES_5, controlID::ws5WaveIndex);
	addAuxParamAtt(CUSTOM_OPTION_MENU, SynthLab::WAVE_SEQ_WAVES_6, controlID::ws6WaveIndex);
	addAuxParamAtt(CUSTOM_OPTION_MENU, SynthLab::WAVE_SEQ_WAVES_7, controlID::ws7WaveIndex);
	addAuxParamAtt(CUSTOM_OPTION_MENU, SynthLab::WAVE_SEQ_WAVES_8, controlID::ws8WaveIndex);


	//// --- OSC1
	//moduleAuxParamSet wto1Module(SynthLab::OSC1_SOURCE, SynthLab::OSC1_WAVEFORMS, SynthLab::OSC1_MOD_KNOBS,
	//	controlID::osc1Core, controlID::osc1_waveform,
	//	controlID::osc1_ModKnobA, controlID::osc1_ModKnobB,
	//	controlID::osc1_ModKnobC, controlID::osc1_ModKnobD);

	//addModuleParamAtts(wto1Module);

	//// --- WTO2
	//moduleAuxParamSet wto2Module(SynthLab::OSC2_SOURCE, SynthLab::OSC2_WAVEFORMS, SynthLab::OSC2_MOD_KNOBS,
	//	controlID::osc2Core, controlID::osc2_waveform,
	//	controlID::osc2_ModKnobA, controlID::osc2_ModKnobB,
	//	controlID::osc2_ModKnobC, controlID::osc2_ModKnobD);

	//addModuleParamAtts(wto2Module);

	//// --- WTO3
	//moduleAuxParamSet wto3Module(SynthLab::OSC3_SOURCE, SynthLab::OSC3_WAVEFORMS, SynthLab::OSC3_MOD_KNOBS,
	//	controlID::osc3Core, controlID::osc3_waveform,
	//	controlID::osc3_ModKnobA, controlID::osc3_ModKnobB,
	//	controlID::osc3_ModKnobC, controlID::osc3_ModKnobD);

	//addModuleParamAtts(wto3Module);

	//// --- WTO4
	//moduleAuxParamSet wto4Module(SynthLab::OSC4_SOURCE, SynthLab::OSC4_WAVEFORMS, SynthLab::OSC4_MOD_KNOBS,
	//	controlID::osc4Core, controlID::osc4_waveform,
	//	controlID::osc4_ModKnobA, controlID::osc4_ModKnobB,
	//	controlID::osc4_ModKnobC, controlID::osc4_ModKnobD);

	//addModuleParamAtts(wto4Module);

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


PluginCore::~PluginCore()
{
	dynModuleManager.getDynamicModules();
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
	
	if (true)
	{
		uint32_t index = 0;

		// --- 1
		voiceParameters->wsOsc1Parameters->panValue[index] = wseq1_panValue;
		voiceParameters->wsOsc1Parameters->hardSyncRatio[index] = wseq1HardSync;
		voiceParameters->wsOsc1Parameters->morphIntensity[index] = wseq1Morph;
		voiceParameters->wsOsc1Parameters->detuneSemis[index] = 0.0;
		voiceParameters->wsOsc1Parameters->detuneCents[index] = 0.0;
		//
		voiceParameters->wsOsc2Parameters->panValue[index] = wseq1_panValue;
		voiceParameters->wsOsc2Parameters->hardSyncRatio[index] = wseq1HardSync;
		voiceParameters->wsOsc2Parameters->morphIntensity[index] = wseq1Morph;
		voiceParameters->wsOsc2Parameters->detuneSemis[index] = wseq1DetuneSemis;
		voiceParameters->wsOsc2Parameters->detuneCents[index] = wseq1DetuneCents;

		// ---2
		index++;
		voiceParameters->wsOsc1Parameters->panValue[index] = wseq2_panValue;
		voiceParameters->wsOsc1Parameters->hardSyncRatio[index] = wseq2HardSync;
		voiceParameters->wsOsc1Parameters->morphIntensity[index] = wseq2Morph;
		voiceParameters->wsOsc1Parameters->detuneSemis[index] = 0.0;
		voiceParameters->wsOsc1Parameters->detuneCents[index] = 0.0;
		//
		voiceParameters->wsOsc2Parameters->panValue[index] = wseq2_panValue;
		voiceParameters->wsOsc2Parameters->hardSyncRatio[index] = wseq2HardSync;
		voiceParameters->wsOsc2Parameters->morphIntensity[index] = wseq2Morph;
		voiceParameters->wsOsc2Parameters->detuneSemis[index] = wseq2DetuneSemis;
		voiceParameters->wsOsc2Parameters->detuneCents[index] = wseq2DetuneCents;

		// ---3
		index++;
		voiceParameters->wsOsc1Parameters->panValue[index] = wseq3_panValue;
		voiceParameters->wsOsc1Parameters->hardSyncRatio[index] = wseq3HardSync;
		voiceParameters->wsOsc1Parameters->morphIntensity[index] = wseq3Morph;
		voiceParameters->wsOsc1Parameters->detuneSemis[index] = 0.0;
		voiceParameters->wsOsc1Parameters->detuneCents[index] = 0.0;
		//
		voiceParameters->wsOsc2Parameters->panValue[index] = wseq3_panValue;
		voiceParameters->wsOsc2Parameters->hardSyncRatio[index] = wseq3HardSync;
		voiceParameters->wsOsc2Parameters->morphIntensity[index] = wseq3Morph;
		voiceParameters->wsOsc2Parameters->detuneSemis[index] = wseq3DetuneSemis;
		voiceParameters->wsOsc2Parameters->detuneCents[index] = wseq3DetuneCents;

		// ---4
		index++;
		voiceParameters->wsOsc1Parameters->panValue[index] = wseq4_panValue;
		voiceParameters->wsOsc1Parameters->hardSyncRatio[index] = wseq4HardSync;
		voiceParameters->wsOsc1Parameters->morphIntensity[index] = wseq4Morph;
		voiceParameters->wsOsc1Parameters->detuneSemis[index] = 0.0;
		voiceParameters->wsOsc1Parameters->detuneCents[index] = 0.0;
		//
		voiceParameters->wsOsc2Parameters->panValue[index] = wseq4_panValue;
		voiceParameters->wsOsc2Parameters->hardSyncRatio[index] = wseq4HardSync;
		voiceParameters->wsOsc2Parameters->morphIntensity[index] = wseq4Morph;
		voiceParameters->wsOsc2Parameters->detuneSemis[index] = wseq4DetuneSemis;
		voiceParameters->wsOsc2Parameters->detuneCents[index] = wseq4DetuneCents;

		// ---5
		index++;
		voiceParameters->wsOsc1Parameters->panValue[index] = wseq5_panValue;
		voiceParameters->wsOsc1Parameters->hardSyncRatio[index] = wseq5HardSync;
		voiceParameters->wsOsc1Parameters->morphIntensity[index] = wseq5Morph;
		voiceParameters->wsOsc1Parameters->detuneSemis[index] = 0.0;
		voiceParameters->wsOsc1Parameters->detuneCents[index] = 0.0;
		//
		voiceParameters->wsOsc2Parameters->panValue[index] = wseq5_panValue;
		voiceParameters->wsOsc2Parameters->hardSyncRatio[index] = wseq5HardSync;
		voiceParameters->wsOsc2Parameters->morphIntensity[index] = wseq5Morph;
		voiceParameters->wsOsc2Parameters->detuneSemis[index] = wseq5DetuneSemis;
		voiceParameters->wsOsc2Parameters->detuneCents[index] = wseq5DetuneCents;

		// ---6
		index++;
		voiceParameters->wsOsc1Parameters->panValue[index] = wseq6_panValue;
		voiceParameters->wsOsc1Parameters->hardSyncRatio[index] = wseq6HardSync;
		voiceParameters->wsOsc1Parameters->morphIntensity[index] = wseq6Morph;
		voiceParameters->wsOsc1Parameters->detuneSemis[index] = 0.0;
		voiceParameters->wsOsc1Parameters->detuneCents[index] = 0.0;
		//
		voiceParameters->wsOsc2Parameters->panValue[index] = wseq6_panValue;
		voiceParameters->wsOsc2Parameters->hardSyncRatio[index] = wseq6HardSync;
		voiceParameters->wsOsc2Parameters->morphIntensity[index] = wseq6Morph;
		voiceParameters->wsOsc2Parameters->detuneSemis[index] = wseq6DetuneSemis;
		voiceParameters->wsOsc2Parameters->detuneCents[index] = wseq6DetuneCents;

		// ---7
		index++;
		voiceParameters->wsOsc1Parameters->panValue[index] = wseq7_panValue;
		voiceParameters->wsOsc1Parameters->hardSyncRatio[index] = wseq7HardSync;
		voiceParameters->wsOsc1Parameters->morphIntensity[index] = wseq7Morph;
		voiceParameters->wsOsc1Parameters->detuneSemis[index] = 0.0;
		voiceParameters->wsOsc1Parameters->detuneCents[index] = 0.0;
		//
		voiceParameters->wsOsc2Parameters->panValue[index] = wseq7_panValue;
		voiceParameters->wsOsc2Parameters->hardSyncRatio[index] = wseq7HardSync;
		voiceParameters->wsOsc2Parameters->morphIntensity[index] = wseq7Morph;
		voiceParameters->wsOsc2Parameters->detuneSemis[index] = wseq7DetuneSemis;
		voiceParameters->wsOsc2Parameters->detuneCents[index] = wseq7DetuneCents;

		// ---8
		index++;
		voiceParameters->wsOsc1Parameters->panValue[index] = wseq8_panValue;
		voiceParameters->wsOsc1Parameters->hardSyncRatio[index] = wseq8HardSync;
		voiceParameters->wsOsc1Parameters->morphIntensity[index] = wseq8Morph;
		voiceParameters->wsOsc1Parameters->detuneSemis[index] = 0.0;
		voiceParameters->wsOsc1Parameters->detuneCents[index] = 0.0;
		//
		voiceParameters->wsOsc2Parameters->panValue[index] = wseq8_panValue;
		voiceParameters->wsOsc2Parameters->hardSyncRatio[index] = wseq8HardSync;
		voiceParameters->wsOsc2Parameters->morphIntensity[index] = wseq8Morph;
		voiceParameters->wsOsc2Parameters->detuneSemis[index] = wseq8DetuneSemis;
		voiceParameters->wsOsc2Parameters->detuneCents[index] = wseq8DetuneCents;
	}


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

	// --- wave sequencer
	if (true)
	{
		voiceParameters->waveSequencerParameters->stepDurationNoteIndex[0] = ws1StepLenIndex;
		voiceParameters->waveSequencerParameters->xfadeDurationNoteIndex[0] = ws1XFadeLenIndex;
		voiceParameters->waveSequencerParameters->waveLaneValue[0] = ws1WaveIndex;
		voiceParameters->waveSequencerParameters->waveLaneAmp_dB[0] = ws1WaveAmp_dB;
		voiceParameters->waveSequencerParameters->pitchLaneValue[0] = ws1Pitch_semi;
		voiceParameters->waveSequencerParameters->pitchLaneProbability_pct[0] = ws1PitchProb_pct;
		voiceParameters->waveSequencerParameters->stepSeqValue[0] = ws1ModValue;
		voiceParameters->waveSequencerParameters->stepSeqProbability_pct[0] = ws1ModProb_pct;

		voiceParameters->waveSequencerParameters->stepDurationNoteIndex[1] = ws2StepLenIndex;
		voiceParameters->waveSequencerParameters->xfadeDurationNoteIndex[1] = ws2XFadeLenIndex;
		voiceParameters->waveSequencerParameters->waveLaneValue[1] = ws2WaveIndex;
		voiceParameters->waveSequencerParameters->waveLaneAmp_dB[1] = ws2WaveAmp_dB;
		voiceParameters->waveSequencerParameters->pitchLaneValue[1] = ws2Pitch_semi;
		voiceParameters->waveSequencerParameters->pitchLaneProbability_pct[1] = ws2PitchProb_pct;
		voiceParameters->waveSequencerParameters->stepSeqValue[1] = ws2ModValue;
		voiceParameters->waveSequencerParameters->stepSeqProbability_pct[1] = ws2ModProb_pct;

		voiceParameters->waveSequencerParameters->stepDurationNoteIndex[2] = ws3StepLenIndex;
		voiceParameters->waveSequencerParameters->xfadeDurationNoteIndex[2] = ws3XFadeLenIndex;
		voiceParameters->waveSequencerParameters->waveLaneValue[2] = ws3WaveIndex;
		voiceParameters->waveSequencerParameters->waveLaneAmp_dB[2] = ws3WaveAmp_dB;
		voiceParameters->waveSequencerParameters->pitchLaneValue[2] = ws3Pitch_semi;
		voiceParameters->waveSequencerParameters->pitchLaneProbability_pct[2] = ws3PitchProb_pct;
		voiceParameters->waveSequencerParameters->stepSeqValue[2] = ws3ModValue;
		voiceParameters->waveSequencerParameters->stepSeqProbability_pct[2] = ws3ModProb_pct;

		voiceParameters->waveSequencerParameters->stepDurationNoteIndex[3] = ws4StepLenIndex;
		voiceParameters->waveSequencerParameters->xfadeDurationNoteIndex[3] = ws4XFadeLenIndex;
		voiceParameters->waveSequencerParameters->waveLaneValue[3] = ws4WaveIndex;
		voiceParameters->waveSequencerParameters->waveLaneAmp_dB[3] = ws4WaveAmp_dB;
		voiceParameters->waveSequencerParameters->pitchLaneValue[3] = ws4Pitch_semi;
		voiceParameters->waveSequencerParameters->pitchLaneProbability_pct[3] = ws4PitchProb_pct;
		voiceParameters->waveSequencerParameters->stepSeqValue[3] = ws4ModValue;
		voiceParameters->waveSequencerParameters->stepSeqProbability_pct[3] = ws4ModProb_pct;

		voiceParameters->waveSequencerParameters->stepDurationNoteIndex[4] = ws5StepLenIndex;
		voiceParameters->waveSequencerParameters->xfadeDurationNoteIndex[4] = ws5XFadeLenIndex;
		voiceParameters->waveSequencerParameters->waveLaneValue[4] = ws5WaveIndex;
		voiceParameters->waveSequencerParameters->waveLaneAmp_dB[4] = ws5WaveAmp_dB;
		voiceParameters->waveSequencerParameters->pitchLaneValue[4] = ws5Pitch_semi;
		voiceParameters->waveSequencerParameters->pitchLaneProbability_pct[4] = ws5PitchProb_pct;
		voiceParameters->waveSequencerParameters->stepSeqValue[4] = ws5ModValue;
		voiceParameters->waveSequencerParameters->stepSeqProbability_pct[4] = ws5ModProb_pct;

		voiceParameters->waveSequencerParameters->stepDurationNoteIndex[5] = ws6StepLenIndex;
		voiceParameters->waveSequencerParameters->xfadeDurationNoteIndex[5] = ws6XFadeLenIndex;
		voiceParameters->waveSequencerParameters->waveLaneValue[5] = ws6WaveIndex;
		voiceParameters->waveSequencerParameters->waveLaneAmp_dB[5] = ws6WaveAmp_dB;
		voiceParameters->waveSequencerParameters->pitchLaneValue[5] = ws6Pitch_semi;
		voiceParameters->waveSequencerParameters->pitchLaneProbability_pct[5] = ws6PitchProb_pct;
		voiceParameters->waveSequencerParameters->stepSeqValue[5] = ws6ModValue;
		voiceParameters->waveSequencerParameters->stepSeqProbability_pct[5] = ws6ModProb_pct;

		voiceParameters->waveSequencerParameters->stepDurationNoteIndex[6] = ws7StepLenIndex;
		voiceParameters->waveSequencerParameters->xfadeDurationNoteIndex[6] = ws7XFadeLenIndex;
		voiceParameters->waveSequencerParameters->waveLaneValue[6] = ws7WaveIndex;
		voiceParameters->waveSequencerParameters->waveLaneAmp_dB[6] = ws7WaveAmp_dB;
		voiceParameters->waveSequencerParameters->pitchLaneValue[6] = ws7Pitch_semi;
		voiceParameters->waveSequencerParameters->pitchLaneProbability_pct[6] = ws7PitchProb_pct;
		voiceParameters->waveSequencerParameters->stepSeqValue[6] = ws7ModValue;
		voiceParameters->waveSequencerParameters->stepSeqProbability_pct[6] = ws7ModProb_pct;

		voiceParameters->waveSequencerParameters->stepDurationNoteIndex[7] = ws8StepLenIndex;
		voiceParameters->waveSequencerParameters->xfadeDurationNoteIndex[7] = ws8XFadeLenIndex;
		voiceParameters->waveSequencerParameters->waveLaneValue[7] = ws8WaveIndex;
		voiceParameters->waveSequencerParameters->waveLaneAmp_dB[7] = ws8WaveAmp_dB;
		voiceParameters->waveSequencerParameters->pitchLaneValue[7] = ws8Pitch_semi;
		voiceParameters->waveSequencerParameters->pitchLaneProbability_pct[7] = ws8PitchProb_pct;
		voiceParameters->waveSequencerParameters->stepSeqValue[7] = ws8ModValue;
		voiceParameters->waveSequencerParameters->stepSeqProbability_pct[7] = ws8ModProb_pct;

		if (soloWaveLane > 0)
		{
			voiceParameters->wsOsc1Parameters->soloWaveWSIndex = voiceParameters->waveSequencerParameters->waveLaneValue[soloWaveLane - 1];
			voiceParameters->wsOsc2Parameters->soloWaveWSIndex = voiceParameters->waveSequencerParameters->waveLaneValue[soloWaveLane - 1];
		}
		else
		{
			voiceParameters->wsOsc1Parameters->soloWaveWSIndex = -1;
			voiceParameters->wsOsc2Parameters->soloWaveWSIndex = -1;
		}

		voiceParameters->waveSequencerParameters->haltSequencer = (runStopWS != 0);

		voiceParameters->waveSequencerParameters->timingLoopStart = timingStartIndex;
		voiceParameters->waveSequencerParameters->timingLoopEnd = timingEndIndex;
		voiceParameters->waveSequencerParameters->timingLoopDirIndex = timingLoopDir;

		voiceParameters->waveSequencerParameters->modLoopStart[SynthLab::WAVE_LANE] = waveStartIndex;
		voiceParameters->waveSequencerParameters->modLoopEnd[SynthLab::WAVE_LANE] = waveEndIndex;
		voiceParameters->waveSequencerParameters->modLoopDirIndex[SynthLab::WAVE_LANE] = waveLoopDir;

		voiceParameters->waveSequencerParameters->modLoopStart[SynthLab::PITCH_LANE] = pitchStartIndex;
		voiceParameters->waveSequencerParameters->modLoopEnd[SynthLab::PITCH_LANE] = pitchEndIndex;
		voiceParameters->waveSequencerParameters->modLoopDirIndex[SynthLab::PITCH_LANE] = pitchLoopDir;

		voiceParameters->waveSequencerParameters->modLoopStart[SynthLab::STEP_SEQ_LANE] = stepSeqModStartIndex;
		voiceParameters->waveSequencerParameters->modLoopEnd[SynthLab::STEP_SEQ_LANE] = stepSeqModEndIndex;
		voiceParameters->waveSequencerParameters->modLoopDirIndex[SynthLab::STEP_SEQ_LANE] = stepSeqModLoopDir;

		voiceParameters->waveSequencerParameters->stepType[0] = step1Type;
		voiceParameters->waveSequencerParameters->stepType[1] = step2Type;
		voiceParameters->waveSequencerParameters->stepType[2] = step3Type;
		voiceParameters->waveSequencerParameters->stepType[3] = step4Type;
		voiceParameters->waveSequencerParameters->stepType[4] = step5Type;
		voiceParameters->waveSequencerParameters->stepType[5] = step6Type;
		voiceParameters->waveSequencerParameters->stepType[6] = step7Type;
		voiceParameters->waveSequencerParameters->stepType[7] = step8Type;

		voiceParameters->waveSequencerParameters->timeStretch = timeStretch;
		voiceParameters->waveSequencerParameters->interpolateStepSeqMod = interpolateStepSeqMod;
		voiceParameters->waveSequencerParameters->randomizeStepOrder = randomizeStepOrder;
		voiceParameters->waveSequencerParameters->randomizePitchOrder = randomizePitchOrder;
		voiceParameters->waveSequencerParameters->randomizeWaveOrder = randomizeWaveOrder;
		voiceParameters->waveSequencerParameters->randomizeSSModOrder = randomizeSSModOrder;
	}
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
	voiceParameters->modMatrixParameters->setMM_SourceIntensity(SynthLab::kSourceWStepSeqMod, waveSeqModSourceInt);

	// --- Destination Intensities
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestLFO2_fo, lfo2_fo_Int);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc1_fo, osc_fo_Int);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc2_fo, osc_fo_Int);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc3_fo, osc_fo_Int);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc4_fo, osc_fo_Int);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc5_fo, osc_fo_Int);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc6_fo, osc_fo_Int);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc7_fo, osc_fo_Int);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc8_fo, osc_fo_Int);

	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc1_Mod, osc_UniqueInt);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc2_Mod, osc_UniqueInt);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc3_Mod, osc_UniqueInt);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc4_Mod, osc_UniqueInt);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc5_Mod, osc_UniqueInt);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc6_Mod, osc_UniqueInt);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc7_Mod, osc_UniqueInt);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestOsc8_Mod, osc_UniqueInt);
	
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestFilterEGRetrigger, filterEGTrigInt);
	voiceParameters->modMatrixParameters->setMM_DestIntensity(SynthLab::kDestAuxEGRetrigger, auxEGTrigInt);

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

	bool enable = (lfo1_osc_fc == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc1_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc2_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc3_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc4_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc5_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc6_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc7_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc8_fo, enable);

	// --- WT and morphing WT have HSync as unique mod
	enable = (lfo1_oscUnique == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc1_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc2_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc3_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc4_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc5_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc6_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc7_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestOsc8_Mod, enable);

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestAmpEGRetrigger, (lfo1_ampEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestDCA_PanMod, (lfo1_dcaPan == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestFilterEGRetrigger, (lfo1_filterEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestAuxEGRetrigger, (lfo1_auxEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestFilter1_fc_Bipolar, (lfo1_filter1_fc == 1));
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO1_Norm,
		SynthLab::kDestFilter2_fc_Bipolar, (lfo1_filter2_fc == 1));
	// ----------------------------------------------------------------------------------------

	// --- ROW 2 ------------------------------------------------------------------------------
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestLFO2_fo, (lfo2_lfo2_fc == 1));

	enable = (lfo2_osc_fc == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc1_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc2_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc3_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc4_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc5_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc6_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc7_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc8_fo, enable);

	// --- WT and morphing WT have HSync as unique mod
	enable = (lfo2_oscUnique == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc1_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc2_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc3_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc4_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc5_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc6_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc7_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestOsc8_Mod, enable);

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestAmpEGRetrigger, (lfo2_ampEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestDCA_PanMod, (lfo2_dcaPan == 1));
	
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestAmpEGRetrigger, (lfo2_filterEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestAuxEGRetrigger, (lfo2_auxEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestFilter1_fc_Bipolar, (lfo2_filter1_fc == 1));
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceLFO2_Norm,
		SynthLab::kDestFilter2_fc_Bipolar, (lfo2_filter2_fc == 1));
	// ----------------------------------------------------------------------------------------

	// --- ROW 3 ------------------------------------------------------------------------------
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestLFO2_fo, (filterEG_lfo2_fc == 1));

	enable = (filterEG_osc_fc == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc1_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc2_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc3_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc4_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc5_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc6_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc7_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc8_fo, enable);

	// --- WT and morphing WT have HSync as unique mod
	enable = (filterEG_oscUnique == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc1_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc2_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc3_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc4_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc5_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc6_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc7_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestOsc8_Mod, enable);

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestDCA_PanMod, (filterEG_dcaPan == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestAmpEGRetrigger, (filterEG_ampEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestFilterEGRetrigger, (filterEG_filterEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestAuxEGRetrigger, (filterEG_auxEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestFilter1_fc_EG, (filterEG_filter1_fc == 1));
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceFilterEG_Norm,
		SynthLab::kDestFilter2_fc_EG, (filterEG_filter2_fc == 1));
	// ----------------------------------------------------------------------------------------



	// --- ROW 4 ------------------------------------------------------------------------------
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestLFO2_fo, (auxEG_lfo2_fc == 1));

	enable = (auxEG_osc_fc == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc1_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc2_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc3_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc4_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc5_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc6_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc7_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc8_fo, enable);

	// --- WT and morphing WT have HSync as unique mod
	enable = (auxEG_oscUnique == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc1_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc2_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc3_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc4_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc5_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc6_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc7_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestOsc8_Mod, enable);

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestDCA_PanMod, (auxEG_dcaPan == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestAmpEGRetrigger, (auxEG_ampEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestFilterEGRetrigger, (auxEG_filterEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestAuxEGRetrigger, (auxEG_auxEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestFilter1_fc_Bipolar, (auxEG_filter1_fc == 1));
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Norm,
		SynthLab::kDestFilter2_fc_Bipolar, (auxEG_filter2_fc == 1));
	// ----------------------------------------------------------------------------------------

	// --- ROW 5 ------------------------------------------------------------------------------
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestLFO2_fo, (auxEGB_lfo2_fc == 1));

	enable = (auxEGB_osc_fc == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc1_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc2_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc3_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc4_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc5_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc6_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc7_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc8_fo, enable);

	// --- WT and morphing WT have HSync as unique mod
	enable = (auxEGB_oscUnique == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc1_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc2_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc3_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc4_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc5_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc6_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc7_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestOsc8_Mod, enable);

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestAmpEGRetrigger, (auxEGB_ampEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestDCA_PanMod, (auxEGB_dcaPan == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestFilterEGRetrigger, (auxEGB_filterEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestAuxEGRetrigger, (auxEGB_auxEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestFilter1_fc_Bipolar, (auxEGB_filter1_fc == 1));
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceAuxEG_Bias,
		SynthLab::kDestFilter2_fc_Bipolar, (auxEGB_filter2_fc == 1));
	// ----------------------------------------------------------------------------------------

	// --- ROW 6 ------------------------------------------------------------------------------
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestLFO2_fo, (waveSeqMod_lfo2_fc == 1));

	enable = (waveSeqMod_osc_fo == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestOsc1_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestOsc2_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestOsc3_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestOsc4_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestOsc5_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestOsc6_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestOsc7_fo, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestOsc8_fo, enable);

	enable = (waveSeqMod_oscUnique == 1);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestOsc1_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestOsc2_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestOsc3_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestOsc4_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestOsc5_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestOsc6_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestOsc7_Mod, enable);
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestOsc8_Mod, enable);

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestAmpEGRetrigger, (waveSeqMod_ampEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestDCA_PanMod, (waveSeqMod_dcaPan == 1));
	
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestFilterEGRetrigger, (waveSeqMod_filterEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestAuxEGRetrigger, (waveSeqMod_auxEGTrig == 1));

	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestFilter1_fc_Bipolar, (waveSeqMod_filter1_fc == 1));
	
	voiceParameters->modMatrixParameters->setMM_ChannelEnable(SynthLab::kSourceWStepSeqMod,
		SynthLab::kDestFilter2_fc_Bipolar, (waveSeqMod_filter2_fc == 1));
	// ----------------------------------------------------------------------------------------

}

void PluginCore::updateSequencerLEDs()
{
	uint32_t meter = 0;
	timing1Meter = engineParameters->wsStatusMeters.timingLaneMeter[meter++];
	timing2Meter = engineParameters->wsStatusMeters.timingLaneMeter[meter++];
	timing3Meter = engineParameters->wsStatusMeters.timingLaneMeter[meter++];
	timing4Meter = engineParameters->wsStatusMeters.timingLaneMeter[meter++];
	timing5Meter = engineParameters->wsStatusMeters.timingLaneMeter[meter++];
	timing6Meter = engineParameters->wsStatusMeters.timingLaneMeter[meter++];
	timing7Meter = engineParameters->wsStatusMeters.timingLaneMeter[meter++];
	timing8Meter = engineParameters->wsStatusMeters.timingLaneMeter[meter];

	meter = 0;
	wave1Meter = engineParameters->wsStatusMeters.waveLaneMeter[meter++];
	wave2Meter = engineParameters->wsStatusMeters.waveLaneMeter[meter++];
	wave3Meter = engineParameters->wsStatusMeters.waveLaneMeter[meter++];
	wave4Meter = engineParameters->wsStatusMeters.waveLaneMeter[meter++];
	wave5Meter = engineParameters->wsStatusMeters.waveLaneMeter[meter++];
	wave6Meter = engineParameters->wsStatusMeters.waveLaneMeter[meter++];
	wave7Meter = engineParameters->wsStatusMeters.waveLaneMeter[meter++];
	wave8Meter = engineParameters->wsStatusMeters.waveLaneMeter[meter];

	meter = 0;
	pitch1Meter = engineParameters->wsStatusMeters.pitchLaneMeter[meter++];
	pitch2Meter = engineParameters->wsStatusMeters.pitchLaneMeter[meter++];
	pitch3Meter = engineParameters->wsStatusMeters.pitchLaneMeter[meter++];
	pitch4Meter = engineParameters->wsStatusMeters.pitchLaneMeter[meter++];
	pitch5Meter = engineParameters->wsStatusMeters.pitchLaneMeter[meter++];
	pitch6Meter = engineParameters->wsStatusMeters.pitchLaneMeter[meter++];
	pitch7Meter = engineParameters->wsStatusMeters.pitchLaneMeter[meter++];
	pitch8Meter = engineParameters->wsStatusMeters.pitchLaneMeter[meter];

	meter = 0;
	ssMod1Meter = engineParameters->wsStatusMeters.stepSeqLaneMeter[meter++];
	ssMod2Meter = engineParameters->wsStatusMeters.stepSeqLaneMeter[meter++];
	ssMod3Meter = engineParameters->wsStatusMeters.stepSeqLaneMeter[meter++];
	ssMod4Meter = engineParameters->wsStatusMeters.stepSeqLaneMeter[meter++];
	ssMod5Meter = engineParameters->wsStatusMeters.stepSeqLaneMeter[meter++];
	ssMod6Meter = engineParameters->wsStatusMeters.stepSeqLaneMeter[meter++];
	ssMod7Meter = engineParameters->wsStatusMeters.stepSeqLaneMeter[meter++];
	ssMod8Meter = engineParameters->wsStatusMeters.stepSeqLaneMeter[meter];

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

	// --- status LEDs; WS only
	updateSequencerLEDs();

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

					// --- note this is count (fixed) for the param
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
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 0.000000);
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
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 0.000000);
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
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1StepLenIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1XFadeLenIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2StepLenIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2XFadeLenIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3StepLenIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3XFadeLenIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4StepLenIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4XFadeLenIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5StepLenIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5XFadeLenIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6StepLenIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6XFadeLenIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7StepLenIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7XFadeLenIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8StepLenIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8XFadeLenIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::timingStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::timingEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::timingLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::waveLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::timeStretch, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::step1Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step2Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step3Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step4Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step5Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step6Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step7Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step8Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::interpolateStepSeqMod, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeStepOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizePitchOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 20.000000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeWaveOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeSSModOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_UniqueInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqModSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_osc_fo, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneCents, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneCents, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneCents, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneCents, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneCents, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneCents, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneCents, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneCents, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFO_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::soloWaveLane, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::runStopWS, -0.000000);
	addPreset(preset);

	// --- Preset: UnderTheBed
	preset = new PresetInfo(index++, "UnderTheBed");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.406415);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 0.925000);
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
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.270000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.790000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.705000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 435.274994);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 8.110001);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 1000.000000);
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
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 8250.017578);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.375000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 1.000000);
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
	setPresetParameter(preset->presetParameters, controlID::globalTuning, -0.360000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1StepLenIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1XFadeLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1PitchProb_pct, 74.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModValue, -0.640000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2XFadeLenIndex, 16.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveIndex, 15.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2Pitch_semi, -2.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2PitchProb_pct, 16.000002);
	setPresetParameter(preset->presetParameters, controlID::ws2ModValue, -0.600000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3StepLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveIndex, 23.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3Pitch_semi, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3PitchProb_pct, 75.500000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModValue, -0.300000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModValue, 0.180000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5StepLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5XFadeLenIndex, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveIndex, 35.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5Pitch_semi, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5PitchProb_pct, 38.000004);
	setPresetParameter(preset->presetParameters, controlID::ws5ModValue, 0.590000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6StepLenIndex, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6XFadeLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveIndex, 29.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6Pitch_semi, -9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModValue, 0.710000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7StepLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveIndex, 34.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7Pitch_semi, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7PitchProb_pct, 78.500000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModValue, -0.800000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8StepLenIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveIndex, 16.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8Pitch_semi, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8PitchProb_pct, 29.500002);
	setPresetParameter(preset->presetParameters, controlID::ws8ModValue, 0.390000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::timingStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::timingEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::timingLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::waveLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchLoopDir, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::timeStretch, 0.100000);
	setPresetParameter(preset->presetParameters, controlID::step1Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step2Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step3Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step4Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step5Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step6Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step7Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step8Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::interpolateStepSeqMod, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeStepOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizePitchOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 760.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 20.000000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, 1.200001);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -2.399998);
	setPresetParameter(preset->presetParameters, controlID::randomizeWaveOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeSSModOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_fo_Int, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_UniqueInt, 0.720000);
	setPresetParameter(preset->presetParameters, controlID::filterEGTrigInt, 0.700000);
	setPresetParameter(preset->presetParameters, controlID::auxEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.480000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.490000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.050000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.690000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.610000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.600000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqModSourceInt, 0.730000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_osc_fo, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_oscUnique, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1_panValue, -0.540000);
	setPresetParameter(preset->presetParameters, controlID::wseq2_panValue, 0.360000);
	setPresetParameter(preset->presetParameters, controlID::wseq3_panValue, -0.690000);
	setPresetParameter(preset->presetParameters, controlID::wseq4_panValue, -0.770000);
	setPresetParameter(preset->presetParameters, controlID::wseq5_panValue, 0.530000);
	setPresetParameter(preset->presetParameters, controlID::wseq6_panValue, 0.290000);
	setPresetParameter(preset->presetParameters, controlID::wseq7_panValue, 0.330000);
	setPresetParameter(preset->presetParameters, controlID::wseq8_panValue, -0.600000);
	setPresetParameter(preset->presetParameters, controlID::wseq1HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2HardSync, 0.120000);
	setPresetParameter(preset->presetParameters, controlID::wseq2Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3HardSync, 0.050000);
	setPresetParameter(preset->presetParameters, controlID::wseq3Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8HardSync, 0.150000);
	setPresetParameter(preset->presetParameters, controlID::wseq8Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneCents, 31.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneCents, -44.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneCents, 19.500008);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneCents, -11.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneCents, -3.000004);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneCents, -7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneCents, 12.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneCents, -26.500000);
	setPresetParameter(preset->presetParameters, controlID::LFO_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SW, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SW, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::soloWaveLane, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::runStopWS, -0.000000);
	addPreset(preset);

	// --- Preset: Aliens
	preset = new PresetInfo(index++, "Aliens");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 0.475000);
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
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.270000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.630000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.705000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 1515.715698);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 5.725000);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 1000.000000);
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
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 8250.017578);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.375000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 1.000000);
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
	setPresetParameter(preset->presetParameters, controlID::globalVolume_dB, -3.240002);
	setPresetParameter(preset->presetParameters, controlID::globalTuning, -0.360000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveAmp_dB, 5.759995);
	setPresetParameter(preset->presetParameters, controlID::ws1StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1XFadeLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1PitchProb_pct, 35.500000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModValue, 0.530000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModProb_pct, 78.500000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveIndex, 15.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveAmp_dB, -6.840000);
	setPresetParameter(preset->presetParameters, controlID::ws2Pitch_semi, -2.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2PitchProb_pct, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModValue, 0.350000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModProb_pct, 49.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3StepLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveIndex, 23.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveAmp_dB, -5.040001);
	setPresetParameter(preset->presetParameters, controlID::ws3Pitch_semi, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3PitchProb_pct, 55.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModValue, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModProb_pct, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4StepLenIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveAmp_dB, -16.920002);
	setPresetParameter(preset->presetParameters, controlID::ws4Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModValue, -0.360000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModProb_pct, 50.500000);
	setPresetParameter(preset->presetParameters, controlID::ws5StepLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5XFadeLenIndex, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveIndex, 35.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveAmp_dB, 4.680000);
	setPresetParameter(preset->presetParameters, controlID::ws5Pitch_semi, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5PitchProb_pct, 69.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModValue, -0.630000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModProb_pct, 54.000004);
	setPresetParameter(preset->presetParameters, controlID::ws6StepLenIndex, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6XFadeLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveIndex, 29.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveAmp_dB, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6Pitch_semi, -9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6PitchProb_pct, 15.500002);
	setPresetParameter(preset->presetParameters, controlID::ws6ModValue, -0.340000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModProb_pct, 42.500000);
	setPresetParameter(preset->presetParameters, controlID::ws7StepLenIndex, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7XFadeLenIndex, 9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveIndex, 34.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveAmp_dB, 3.959999);
	setPresetParameter(preset->presetParameters, controlID::ws7Pitch_semi, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModValue, 0.440000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModProb_pct, 71.500000);
	setPresetParameter(preset->presetParameters, controlID::ws8StepLenIndex, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8XFadeLenIndex, 9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveIndex, 16.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveAmp_dB, 2.520000);
	setPresetParameter(preset->presetParameters, controlID::ws8Pitch_semi, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8PitchProb_pct, 54.500000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModValue, 0.990000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::timingStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::timingEndIndex, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::timingLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveEndIndex, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::waveLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchLoopDir, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::timeStretch, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::step1Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step2Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step3Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step4Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step5Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step6Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step7Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step8Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::interpolateStepSeqMod, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeStepOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizePitchOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 760.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 20.000000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, 1.200001);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -2.399998);
	setPresetParameter(preset->presetParameters, controlID::randomizeWaveOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeSSModOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_UniqueInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.480000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.490000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.690000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.610000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.600000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqModSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_osc_fo, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1_panValue, -0.540000);
	setPresetParameter(preset->presetParameters, controlID::wseq2_panValue, 0.360000);
	setPresetParameter(preset->presetParameters, controlID::wseq3_panValue, -0.690000);
	setPresetParameter(preset->presetParameters, controlID::wseq4_panValue, -0.770000);
	setPresetParameter(preset->presetParameters, controlID::wseq5_panValue, 0.530000);
	setPresetParameter(preset->presetParameters, controlID::wseq6_panValue, 0.290000);
	setPresetParameter(preset->presetParameters, controlID::wseq7_panValue, 0.330000);
	setPresetParameter(preset->presetParameters, controlID::wseq8_panValue, -0.600000);
	setPresetParameter(preset->presetParameters, controlID::wseq1HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2HardSync, 0.120000);
	setPresetParameter(preset->presetParameters, controlID::wseq2Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3HardSync, 0.050000);
	setPresetParameter(preset->presetParameters, controlID::wseq3Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8HardSync, 0.150000);
	setPresetParameter(preset->presetParameters, controlID::wseq8Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneCents, 31.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneCents, -44.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneCents, 19.500008);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneCents, -11.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneCents, -3.000004);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneCents, -7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneCents, 12.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneCents, -26.500000);
	setPresetParameter(preset->presetParameters, controlID::LFO_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SW, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::soloWaveLane, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::runStopWS, -0.000000);
	addPreset(preset);

	// --- Preset: UnderTheBed2
	preset = new PresetInfo(index++, "UnderTheBed2");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.406415);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 0.925000);
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
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.270000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.790000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.705000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 435.274994);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 8.110001);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 1000.000000);
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
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 8250.017578);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.375000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 1.000000);
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
	setPresetParameter(preset->presetParameters, controlID::globalTuning, -0.360000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1StepLenIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1XFadeLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1PitchProb_pct, 74.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModValue, -0.640000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2XFadeLenIndex, 16.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveIndex, 15.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2Pitch_semi, -2.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2PitchProb_pct, 16.000002);
	setPresetParameter(preset->presetParameters, controlID::ws2ModValue, -0.600000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3StepLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveIndex, 23.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3Pitch_semi, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3PitchProb_pct, 75.500000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModValue, -0.300000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModValue, 0.180000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5StepLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5XFadeLenIndex, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveIndex, 35.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5Pitch_semi, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5PitchProb_pct, 38.000004);
	setPresetParameter(preset->presetParameters, controlID::ws5ModValue, 0.590000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6StepLenIndex, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6XFadeLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveIndex, 29.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6Pitch_semi, -9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModValue, 0.710000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7StepLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveIndex, 34.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7Pitch_semi, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7PitchProb_pct, 78.500000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModValue, -0.800000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8StepLenIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveIndex, 16.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8Pitch_semi, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8PitchProb_pct, 29.500002);
	setPresetParameter(preset->presetParameters, controlID::ws8ModValue, 0.390000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::timingStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::timingEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::timingLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::waveLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchLoopDir, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::timeStretch, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::step1Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step2Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step3Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step4Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step5Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step6Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step7Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step8Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::interpolateStepSeqMod, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeStepOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizePitchOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 760.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 20.000000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, 1.200001);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -2.399998);
	setPresetParameter(preset->presetParameters, controlID::randomizeWaveOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeSSModOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_fo_Int, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_UniqueInt, 0.720000);
	setPresetParameter(preset->presetParameters, controlID::filterEGTrigInt, 0.700000);
	setPresetParameter(preset->presetParameters, controlID::auxEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.480000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.490000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.050000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.690000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.610000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.600000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqModSourceInt, 0.730000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_osc_fo, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_oscUnique, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1_panValue, -0.540000);
	setPresetParameter(preset->presetParameters, controlID::wseq2_panValue, 0.360000);
	setPresetParameter(preset->presetParameters, controlID::wseq3_panValue, -0.690000);
	setPresetParameter(preset->presetParameters, controlID::wseq4_panValue, -0.770000);
	setPresetParameter(preset->presetParameters, controlID::wseq5_panValue, 0.530000);
	setPresetParameter(preset->presetParameters, controlID::wseq6_panValue, 0.290000);
	setPresetParameter(preset->presetParameters, controlID::wseq7_panValue, 0.330000);
	setPresetParameter(preset->presetParameters, controlID::wseq8_panValue, -0.600000);
	setPresetParameter(preset->presetParameters, controlID::wseq1HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2HardSync, 0.120000);
	setPresetParameter(preset->presetParameters, controlID::wseq2Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3HardSync, 0.050000);
	setPresetParameter(preset->presetParameters, controlID::wseq3Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8HardSync, 0.150000);
	setPresetParameter(preset->presetParameters, controlID::wseq8Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneCents, 31.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneCents, -44.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneCents, 19.500008);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneCents, -11.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneCents, -3.000004);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneCents, -7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneCents, 12.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneCents, -26.500000);
	setPresetParameter(preset->presetParameters, controlID::LFO_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SW, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::soloWaveLane, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::runStopWS, -0.000000);
	addPreset(preset);

	// --- Preset: UnderTheBedSLO
	preset = new PresetInfo(index++, "UnderTheBedSLO");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.406415);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 0.225000);
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
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.270000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.790000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.705000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 435.274994);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 8.110001);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, -4.700005);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 1000.000000);
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
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 8250.017578);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.375000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 1.000000);
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
	setPresetParameter(preset->presetParameters, controlID::globalVolume_dB, 9.000000);
	setPresetParameter(preset->presetParameters, controlID::globalTuning, -0.360000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1StepLenIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1XFadeLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1PitchProb_pct, 74.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModValue, -0.640000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2XFadeLenIndex, 16.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveIndex, 3.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2Pitch_semi, -2.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2PitchProb_pct, 16.000002);
	setPresetParameter(preset->presetParameters, controlID::ws2ModValue, -0.600000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3StepLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveIndex, 23.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3Pitch_semi, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3PitchProb_pct, 75.500000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModValue, -0.300000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModValue, 0.180000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5StepLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5XFadeLenIndex, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveIndex, 35.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5Pitch_semi, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5PitchProb_pct, 38.000004);
	setPresetParameter(preset->presetParameters, controlID::ws5ModValue, 0.590000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6StepLenIndex, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6XFadeLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveIndex, 29.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6Pitch_semi, -9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModValue, 0.710000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7StepLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveIndex, 19.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7Pitch_semi, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7PitchProb_pct, 78.500000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModValue, -0.800000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8StepLenIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveIndex, 16.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8Pitch_semi, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8PitchProb_pct, 29.500002);
	setPresetParameter(preset->presetParameters, controlID::ws8ModValue, 0.390000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::timingStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::timingEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::timingLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::waveLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchLoopDir, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::timeStretch, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::step1Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step2Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step3Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step4Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step5Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step6Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step7Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step8Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::interpolateStepSeqMod, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeStepOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizePitchOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 760.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 20.000000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, 1.200001);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -2.399998);
	setPresetParameter(preset->presetParameters, controlID::randomizeWaveOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeSSModOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_fo_Int, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_UniqueInt, 0.720000);
	setPresetParameter(preset->presetParameters, controlID::filterEGTrigInt, 0.700000);
	setPresetParameter(preset->presetParameters, controlID::auxEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.480000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.490000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.050000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.690000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.610000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.600000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqModSourceInt, 0.730000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_osc_fo, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_oscUnique, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1_panValue, -0.540000);
	setPresetParameter(preset->presetParameters, controlID::wseq2_panValue, 0.360000);
	setPresetParameter(preset->presetParameters, controlID::wseq3_panValue, -0.690000);
	setPresetParameter(preset->presetParameters, controlID::wseq4_panValue, -0.770000);
	setPresetParameter(preset->presetParameters, controlID::wseq5_panValue, 0.530000);
	setPresetParameter(preset->presetParameters, controlID::wseq6_panValue, 0.290000);
	setPresetParameter(preset->presetParameters, controlID::wseq7_panValue, 0.330000);
	setPresetParameter(preset->presetParameters, controlID::wseq8_panValue, -0.600000);
	setPresetParameter(preset->presetParameters, controlID::wseq1HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2HardSync, 0.120000);
	setPresetParameter(preset->presetParameters, controlID::wseq2Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3HardSync, 0.050000);
	setPresetParameter(preset->presetParameters, controlID::wseq3Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8HardSync, 0.150000);
	setPresetParameter(preset->presetParameters, controlID::wseq8Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneCents, 31.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneCents, -44.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneCents, 19.500008);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneCents, -11.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneCents, -3.000004);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneCents, -7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneCents, 12.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneCents, -26.500000);
	setPresetParameter(preset->presetParameters, controlID::LFO_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SW, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::soloWaveLane, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::runStopWS, -0.000000);
	addPreset(preset);

	// --- Preset: JazzFH_SLO1
	preset = new PresetInfo(index++, "JazzFH_SLO1");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.406415);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 0.825000);
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
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.270000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.790000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.705000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 435.274994);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 8.110001);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 1000.000000);
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
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 8250.017578);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.375000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Algorithm, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter2KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Output_dB, -36.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalVolume_dB, 6.479996);
	setPresetParameter(preset->presetParameters, controlID::globalTuning, -0.360000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveAmp_dB, 0.359997);
	setPresetParameter(preset->presetParameters, controlID::ws1StepLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1XFadeLenIndex, 13.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1PitchProb_pct, 74.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModValue, -0.640000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2StepLenIndex, 16.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2XFadeLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveIndex, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2Pitch_semi, -2.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2PitchProb_pct, 16.000002);
	setPresetParameter(preset->presetParameters, controlID::ws2ModValue, -0.600000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3StepLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3XFadeLenIndex, 13.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveIndex, 19.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3Pitch_semi, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3PitchProb_pct, 75.500000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModValue, -0.300000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4StepLenIndex, 15.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4XFadeLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModValue, 0.180000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5StepLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5XFadeLenIndex, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5Pitch_semi, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5PitchProb_pct, 38.000004);
	setPresetParameter(preset->presetParameters, controlID::ws5ModValue, 0.590000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6StepLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6XFadeLenIndex, 9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveIndex, 20.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6Pitch_semi, -9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModValue, 0.710000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7StepLenIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveIndex, 24.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7Pitch_semi, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7PitchProb_pct, 78.500000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModValue, -0.800000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveIndex, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8Pitch_semi, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8PitchProb_pct, 82.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModValue, 0.390000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::timingStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::timingEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::timingLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::waveStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::waveLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchLoopDir, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::timeStretch, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::step1Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step2Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step3Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step4Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step5Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step6Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step7Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step8Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::interpolateStepSeqMod, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeStepOrder, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizePitchOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 760.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 280.000000);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 66.000000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, -0.959999);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -11.400002);
	setPresetParameter(preset->presetParameters, controlID::randomizeWaveOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeSSModOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_fo_Int, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_UniqueInt, 0.720000);
	setPresetParameter(preset->presetParameters, controlID::filterEGTrigInt, 0.700000);
	setPresetParameter(preset->presetParameters, controlID::auxEGTrigInt, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, -0.350000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.470000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.050000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.690000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_auxEGTrig, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.610000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.600000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqModSourceInt, 0.730000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_osc_fo, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1_panValue, -0.080000);
	setPresetParameter(preset->presetParameters, controlID::wseq2_panValue, 0.230000);
	setPresetParameter(preset->presetParameters, controlID::wseq3_panValue, -0.140000);
	setPresetParameter(preset->presetParameters, controlID::wseq4_panValue, -0.140000);
	setPresetParameter(preset->presetParameters, controlID::wseq5_panValue, 0.370000);
	setPresetParameter(preset->presetParameters, controlID::wseq6_panValue, 0.050000);
	setPresetParameter(preset->presetParameters, controlID::wseq7_panValue, -0.130000);
	setPresetParameter(preset->presetParameters, controlID::wseq8_panValue, 0.250000);
	setPresetParameter(preset->presetParameters, controlID::wseq1HardSync, 0.245000);
	setPresetParameter(preset->presetParameters, controlID::wseq1Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2HardSync, 0.120000);
	setPresetParameter(preset->presetParameters, controlID::wseq2Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3HardSync, 0.050000);
	setPresetParameter(preset->presetParameters, controlID::wseq3Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8HardSync, 0.150000);
	setPresetParameter(preset->presetParameters, controlID::wseq8Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneSemis, -3.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneCents, 31.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneSemis, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneCents, -37.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneSemis, 3.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneCents, 19.500008);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneSemis, -5.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneCents, 26.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneCents, -18.500004);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneCents, -16.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneSemis, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneCents, 29.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneSemis, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneCents, -26.500000);
	setPresetParameter(preset->presetParameters, controlID::LFO_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SW, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SW, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::soloWaveLane, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::runStopWS, -0.000000);
	addPreset(preset);

	// --- Preset: JazzFH_F1
	preset = new PresetInfo(index++, "JazzFH_F1");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.406415);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 0.825000);
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
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.270000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.790000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.705000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 435.274994);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 8.110001);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 1000.000000);
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
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 8250.017578);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.375000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Algorithm, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter2KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Output_dB, -36.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalVolume_dB, 6.479996);
	setPresetParameter(preset->presetParameters, controlID::globalTuning, -0.360000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveAmp_dB, 0.359997);
	setPresetParameter(preset->presetParameters, controlID::ws1StepLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1XFadeLenIndex, 13.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1PitchProb_pct, 74.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModValue, -0.640000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2StepLenIndex, 16.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2XFadeLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2Pitch_semi, -2.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2PitchProb_pct, 33.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModValue, -0.600000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3StepLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3XFadeLenIndex, 13.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveIndex, 19.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3Pitch_semi, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3PitchProb_pct, 75.500000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModValue, -0.300000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4StepLenIndex, 15.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4XFadeLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModValue, 0.180000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5StepLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5XFadeLenIndex, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5Pitch_semi, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5PitchProb_pct, 38.000004);
	setPresetParameter(preset->presetParameters, controlID::ws5ModValue, 0.590000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6StepLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6XFadeLenIndex, 9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveIndex, 20.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6Pitch_semi, -9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModValue, 0.710000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7StepLenIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveIndex, 24.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7Pitch_semi, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7PitchProb_pct, 78.500000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModValue, -0.800000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveIndex, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8Pitch_semi, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8PitchProb_pct, 82.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModValue, 0.390000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::timingStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::timingEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::timingLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::waveStartIndex, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::waveEndIndex, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::waveLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchLoopDir, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::timeStretch, -2.300000);
	setPresetParameter(preset->presetParameters, controlID::step1Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step2Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step3Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step4Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step5Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step6Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step7Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step8Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::interpolateStepSeqMod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeStepOrder, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizePitchOrder, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 1280.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 1510.000000);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 44.000008);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, -0.599998);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, 1.559998);
	setPresetParameter(preset->presetParameters, controlID::randomizeWaveOrder, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeSSModOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_fo_Int, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_UniqueInt, 0.720000);
	setPresetParameter(preset->presetParameters, controlID::filterEGTrigInt, 0.700000);
	setPresetParameter(preset->presetParameters, controlID::auxEGTrigInt, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, -0.350000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.470000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.050000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.690000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_auxEGTrig, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.610000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.600000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqModSourceInt, 0.730000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_osc_fo, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1_panValue, 0.190000);
	setPresetParameter(preset->presetParameters, controlID::wseq2_panValue, -0.220000);
	setPresetParameter(preset->presetParameters, controlID::wseq3_panValue, 0.390000);
	setPresetParameter(preset->presetParameters, controlID::wseq4_panValue, -0.460000);
	setPresetParameter(preset->presetParameters, controlID::wseq5_panValue, -0.230000);
	setPresetParameter(preset->presetParameters, controlID::wseq6_panValue, 0.340000);
	setPresetParameter(preset->presetParameters, controlID::wseq7_panValue, -0.300000);
	setPresetParameter(preset->presetParameters, controlID::wseq8_panValue, 0.270000);
	setPresetParameter(preset->presetParameters, controlID::wseq1HardSync, 0.245000);
	setPresetParameter(preset->presetParameters, controlID::wseq1Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2HardSync, 0.120000);
	setPresetParameter(preset->presetParameters, controlID::wseq2Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3HardSync, 0.050000);
	setPresetParameter(preset->presetParameters, controlID::wseq3Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8HardSync, 0.150000);
	setPresetParameter(preset->presetParameters, controlID::wseq8Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneSemis, -3.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneCents, 31.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneSemis, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneCents, -37.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneSemis, 3.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneCents, 19.500008);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneSemis, -5.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneCents, 26.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneCents, -18.500004);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneCents, -16.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneSemis, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneCents, 29.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneSemis, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneCents, -26.500000);
	setPresetParameter(preset->presetParameters, controlID::LFO_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SW, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SW, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::soloWaveLane, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::runStopWS, -0.000000);
	addPreset(preset);

	// --- Preset: ForeverVai
	preset = new PresetInfo(index++, "ForeverVai");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.130008);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 0.825000);
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
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.270000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.790000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.705000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 3999.997314);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 6.715001);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 1000.000000);
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
	setPresetParameter(preset->presetParameters, controlID::lfo2_frequency_Hz, 0.117211);
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 0.775000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 8250.017578);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.375000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Algorithm, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter2KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Output_dB, -36.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalVolume_dB, 7.919998);
	setPresetParameter(preset->presetParameters, controlID::globalTuning, -0.360000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveAmp_dB, 0.359997);
	setPresetParameter(preset->presetParameters, controlID::ws1StepLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1XFadeLenIndex, 13.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1Pitch_semi, -12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1PitchProb_pct, 74.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModValue, -0.640000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2StepLenIndex, 16.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2XFadeLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2Pitch_semi, -7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModValue, -0.600000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3StepLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3XFadeLenIndex, 13.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveIndex, 19.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3Pitch_semi, -4.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3PitchProb_pct, 75.500000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModValue, -0.300000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4StepLenIndex, 15.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4XFadeLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4Pitch_semi, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModValue, 0.180000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5StepLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5XFadeLenIndex, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5Pitch_semi, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5PitchProb_pct, 66.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModValue, 0.590000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6StepLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6XFadeLenIndex, 9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveIndex, 20.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6Pitch_semi, 3.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModValue, 0.710000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7StepLenIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveIndex, 24.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7Pitch_semi, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7PitchProb_pct, 78.500000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModValue, -0.800000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveIndex, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8Pitch_semi, -5.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8PitchProb_pct, 82.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModValue, 0.390000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::timingStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::timingEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::timingLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::waveStartIndex, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::waveEndIndex, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::waveLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::timeStretch, -1.000000);
	setPresetParameter(preset->presetParameters, controlID::step1Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step2Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step3Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step4Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step5Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step6Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step7Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step8Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::interpolateStepSeqMod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeStepOrder, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizePitchOrder, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 760.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 280.000000);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 66.000000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, 0.840004);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -17.880001);
	setPresetParameter(preset->presetParameters, controlID::randomizeWaveOrder, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeSSModOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_fo_Int, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_UniqueInt, 0.720000);
	setPresetParameter(preset->presetParameters, controlID::filterEGTrigInt, 0.700000);
	setPresetParameter(preset->presetParameters, controlID::auxEGTrigInt, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, -0.350000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.470000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.050000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.690000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_auxEGTrig, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.610000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.600000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqModSourceInt, 0.730000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_osc_fo, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1_panValue, -0.540000);
	setPresetParameter(preset->presetParameters, controlID::wseq2_panValue, 0.360000);
	setPresetParameter(preset->presetParameters, controlID::wseq3_panValue, -0.690000);
	setPresetParameter(preset->presetParameters, controlID::wseq4_panValue, -0.770000);
	setPresetParameter(preset->presetParameters, controlID::wseq5_panValue, 0.530000);
	setPresetParameter(preset->presetParameters, controlID::wseq6_panValue, 0.710000);
	setPresetParameter(preset->presetParameters, controlID::wseq7_panValue, -0.570000);
	setPresetParameter(preset->presetParameters, controlID::wseq8_panValue, 0.540000);
	setPresetParameter(preset->presetParameters, controlID::wseq1HardSync, 0.245000);
	setPresetParameter(preset->presetParameters, controlID::wseq1Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2HardSync, 0.120000);
	setPresetParameter(preset->presetParameters, controlID::wseq2Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3HardSync, 0.050000);
	setPresetParameter(preset->presetParameters, controlID::wseq3Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8HardSync, 0.150000);
	setPresetParameter(preset->presetParameters, controlID::wseq8Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneCents, 31.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneCents, -37.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneCents, 19.500008);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneCents, 26.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneCents, -18.500004);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneCents, -16.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneCents, 29.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneCents, -26.500000);
	setPresetParameter(preset->presetParameters, controlID::LFO_SW, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SW, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::soloWaveLane, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::runStopWS, -0.000000);
	addPreset(preset);

	// --- Preset: ForeverVai5ths
	preset = new PresetInfo(index++, "ForeverVai5ths");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.130008);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 0.825000);
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
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.270000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.790000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.705000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 3999.997314);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 6.715001);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_decayTime_mSec, 700.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_releaseTime_mSec, 4750.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_frequency_Hz, 0.117211);
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 0.775000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 8250.017578);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.375000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Algorithm, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_Q, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter2KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2Output_dB, -36.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::globalVolume_dB, 9.000000);
	setPresetParameter(preset->presetParameters, controlID::globalTuning, -0.360000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveAmp_dB, 0.359997);
	setPresetParameter(preset->presetParameters, controlID::ws1StepLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1XFadeLenIndex, 13.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1Pitch_semi, -12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1PitchProb_pct, 74.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModValue, -0.640000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2StepLenIndex, 16.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2XFadeLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2Pitch_semi, -7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModValue, -0.600000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3StepLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3XFadeLenIndex, 13.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveIndex, 19.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3Pitch_semi, -4.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3PitchProb_pct, 75.500000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModValue, -0.300000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4StepLenIndex, 15.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4XFadeLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4Pitch_semi, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModValue, 0.180000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5StepLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5XFadeLenIndex, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5Pitch_semi, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5PitchProb_pct, 66.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModValue, 0.590000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6StepLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6XFadeLenIndex, 9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveIndex, 20.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6Pitch_semi, 3.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModValue, 0.710000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7StepLenIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveIndex, 24.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7Pitch_semi, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7PitchProb_pct, 78.500000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModValue, -0.800000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveIndex, 25.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8Pitch_semi, -5.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8PitchProb_pct, 82.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModValue, 0.390000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::timingStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::timingEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::timingLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::waveStartIndex, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::waveEndIndex, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::waveLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchLoopDir, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::timeStretch, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::step1Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step2Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step3Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step4Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step5Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step6Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step7Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step8Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::interpolateStepSeqMod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeStepOrder, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizePitchOrder, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 1699.999878);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 280.000000);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 41.500004);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, -0.600002);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -10.320000);
	setPresetParameter(preset->presetParameters, controlID::randomizeWaveOrder, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeSSModOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_fo_Int, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_UniqueInt, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGTrigInt, 0.700000);
	setPresetParameter(preset->presetParameters, controlID::auxEGTrigInt, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, -0.350000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.470000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.050000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.690000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_auxEGTrig, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.870000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_oscUnique, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.600000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqModSourceInt, 0.820000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_osc_fo, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1_panValue, -0.540000);
	setPresetParameter(preset->presetParameters, controlID::wseq2_panValue, 0.360000);
	setPresetParameter(preset->presetParameters, controlID::wseq3_panValue, -0.690000);
	setPresetParameter(preset->presetParameters, controlID::wseq4_panValue, -0.770000);
	setPresetParameter(preset->presetParameters, controlID::wseq5_panValue, 0.530000);
	setPresetParameter(preset->presetParameters, controlID::wseq6_panValue, 0.710000);
	setPresetParameter(preset->presetParameters, controlID::wseq7_panValue, -0.570000);
	setPresetParameter(preset->presetParameters, controlID::wseq8_panValue, 0.540000);
	setPresetParameter(preset->presetParameters, controlID::wseq1HardSync, 0.105000);
	setPresetParameter(preset->presetParameters, controlID::wseq1Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2HardSync, 0.010000);
	setPresetParameter(preset->presetParameters, controlID::wseq2Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3HardSync, 0.050000);
	setPresetParameter(preset->presetParameters, controlID::wseq3Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8HardSync, 0.150000);
	setPresetParameter(preset->presetParameters, controlID::wseq8Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneSemis, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneCents, 31.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneSemis, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneCents, -37.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneSemis, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneCents, 19.500008);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneSemis, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneCents, 26.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneSemis, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneCents, -18.500004);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneSemis, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneCents, -16.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneSemis, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneCents, 16.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneSemis, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneCents, -9.500000);
	setPresetParameter(preset->presetParameters, controlID::LFO_SW, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SW, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::soloWaveLane, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::runStopWS, -0.000000);
	addPreset(preset);

	// --- Preset: Plan9
	preset = new PresetInfo(index++, "Plan9");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.210848);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_quantize, 4.000000);
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
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.270000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.630000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.850000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 233.258148);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 5.725000);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 1000.000000);
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
	setPresetParameter(preset->presetParameters, controlID::lfo2_frequency_Hz, 11.586972);
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 8250.017578);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.375000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 1.000000);
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
	setPresetParameter(preset->presetParameters, controlID::globalVolume_dB, -8.639999);
	setPresetParameter(preset->presetParameters, controlID::globalTuning, -0.360000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1StepLenIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1XFadeLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModValue, -0.830000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2XFadeLenIndex, 16.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveIndex, 15.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2Pitch_semi, -2.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModValue, -0.580000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3StepLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveIndex, 23.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3Pitch_semi, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModValue, -0.280000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5StepLenIndex, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5XFadeLenIndex, 9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveIndex, 35.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5Pitch_semi, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModValue, 0.400000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6StepLenIndex, 15.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6XFadeLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveIndex, 29.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6Pitch_semi, -9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModValue, 0.680000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7StepLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveIndex, 34.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7Pitch_semi, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModValue, 0.710000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8StepLenIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveIndex, 16.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8Pitch_semi, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModValue, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::timingStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::timingEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::timingLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::waveStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::waveLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchLoopDir, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::timeStretch, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::step1Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step2Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step3Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step4Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step5Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step6Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step7Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step8Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::interpolateStepSeqMod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeStepOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizePitchOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 760.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 20.000000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, 1.200001);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -2.399998);
	setPresetParameter(preset->presetParameters, controlID::randomizeWaveOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeSSModOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_fo_Int, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_UniqueInt, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.480000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.490000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_oscUnique, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.610000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.600000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqModSourceInt, 0.720000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_osc_fo, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1_panValue, -0.540000);
	setPresetParameter(preset->presetParameters, controlID::wseq2_panValue, 0.360000);
	setPresetParameter(preset->presetParameters, controlID::wseq3_panValue, -0.690000);
	setPresetParameter(preset->presetParameters, controlID::wseq4_panValue, -0.770000);
	setPresetParameter(preset->presetParameters, controlID::wseq5_panValue, 0.530000);
	setPresetParameter(preset->presetParameters, controlID::wseq6_panValue, 0.290000);
	setPresetParameter(preset->presetParameters, controlID::wseq7_panValue, 0.330000);
	setPresetParameter(preset->presetParameters, controlID::wseq8_panValue, -0.600000);
	setPresetParameter(preset->presetParameters, controlID::wseq1HardSync, 0.245000);
	setPresetParameter(preset->presetParameters, controlID::wseq1Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2HardSync, 0.120000);
	setPresetParameter(preset->presetParameters, controlID::wseq2Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3HardSync, 0.050000);
	setPresetParameter(preset->presetParameters, controlID::wseq3Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8HardSync, 0.150000);
	setPresetParameter(preset->presetParameters, controlID::wseq8Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneCents, 31.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneCents, -44.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneCents, 19.500008);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneCents, -11.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneCents, -3.000004);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneCents, -7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneCents, 12.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneCents, -26.500000);
	setPresetParameter(preset->presetParameters, controlID::LFO_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SW, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::soloWaveLane, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::runStopWS, -0.000000);
	addPreset(preset);

	// --- Preset: JonnyCaged
	preset = new PresetInfo(index++, "JonnyCaged");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.139306);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 0.775000);
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
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, 13.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.670000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.490000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 183.010712);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 7.885000);
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
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 8250.017578);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 6750.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 3000.000000);
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
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1StepLenIndex, 9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2StepLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveIndex, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2Pitch_semi, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3XFadeLenIndex, 9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3Pitch_semi, -10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3PitchProb_pct, 34.500004);
	setPresetParameter(preset->presetParameters, controlID::ws3ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4StepLenIndex, 15.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4XFadeLenIndex, 17.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveIndex, 21.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4Pitch_semi, -7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5StepLenIndex, 13.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5XFadeLenIndex, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveIndex, 19.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5Pitch_semi, 15.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6StepLenIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6XFadeLenIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveIndex, 39.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6Pitch_semi, -12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6PitchProb_pct, 34.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7StepLenIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7XFadeLenIndex, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveIndex, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7Pitch_semi, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8StepLenIndex, 9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveIndex, 23.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8Pitch_semi, 9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8PitchProb_pct, 67.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::timingStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::timingEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::timingLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::waveStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::waveLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::timeStretch, 2.450000);
	setPresetParameter(preset->presetParameters, controlID::step1Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step2Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step3Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step4Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step5Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step6Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step7Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step8Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::interpolateStepSeqMod, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeStepOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizePitchOrder, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 1290.000000);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 62.000000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, -0.959999);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -7.439999);
	setPresetParameter(preset->presetParameters, controlID::randomizeWaveOrder, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeSSModOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_UniqueInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGTrigInt, 0.810000);
	setPresetParameter(preset->presetParameters, controlID::auxEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.420000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.830000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filterEGTrig, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_auxEGTrig, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqModSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_osc_fo, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1_panValue, -0.460000);
	setPresetParameter(preset->presetParameters, controlID::wseq2_panValue, 0.430000);
	setPresetParameter(preset->presetParameters, controlID::wseq3_panValue, 0.650000);
	setPresetParameter(preset->presetParameters, controlID::wseq4_panValue, -0.330000);
	setPresetParameter(preset->presetParameters, controlID::wseq5_panValue, -0.350000);
	setPresetParameter(preset->presetParameters, controlID::wseq6_panValue, -0.560000);
	setPresetParameter(preset->presetParameters, controlID::wseq7_panValue, 0.650000);
	setPresetParameter(preset->presetParameters, controlID::wseq8_panValue, 0.090000);
	setPresetParameter(preset->presetParameters, controlID::wseq1HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneSemis, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneCents, 10.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneSemis, -3.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneCents, -11.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneSemis, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneCents, -12.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneSemis, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneCents, 25.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneSemis, -8.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneCents, -9.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneSemis, -9.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneCents, -8.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneSemis, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneCents, 21.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneSemis, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneCents, 20.500000);
	setPresetParameter(preset->presetParameters, controlID::LFO_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SW, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::soloWaveLane, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::runStopWS, -0.000000);
	addPreset(preset);

	// --- Preset: CirclesOfFear
	preset = new PresetInfo(index++, "CirclesOfFear");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 0.000000);
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
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.270000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.630000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.705000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 1515.715698);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 5.725000);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 1000.000000);
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
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 8250.017578);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.375000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ModKnobA, 1.000000);
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
	setPresetParameter(preset->presetParameters, controlID::globalTuning, -0.360000);
	setPresetParameter(preset->presetParameters, controlID::globalUnisonDetune_Cents, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1StepLenIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1XFadeLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2XFadeLenIndex, 16.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveIndex, 15.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2Pitch_semi, -2.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3StepLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveIndex, 23.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3Pitch_semi, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5StepLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5XFadeLenIndex, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveIndex, 35.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5Pitch_semi, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6StepLenIndex, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6XFadeLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveIndex, 29.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6Pitch_semi, -9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7StepLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveIndex, 34.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7Pitch_semi, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8StepLenIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8XFadeLenIndex, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveIndex, 16.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8Pitch_semi, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::timingStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::timingEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::timingLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::waveLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchLoopDir, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::timeStretch, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::step1Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step2Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step3Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step4Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step5Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step6Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step7Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step8Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::interpolateStepSeqMod, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeStepOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizePitchOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 760.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 20.000000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, 1.200001);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -2.399998);
	setPresetParameter(preset->presetParameters, controlID::randomizeWaveOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeSSModOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_UniqueInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.480000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.490000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.690000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.610000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.600000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqModSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_osc_fo, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1_panValue, -0.540000);
	setPresetParameter(preset->presetParameters, controlID::wseq2_panValue, 0.360000);
	setPresetParameter(preset->presetParameters, controlID::wseq3_panValue, -0.690000);
	setPresetParameter(preset->presetParameters, controlID::wseq4_panValue, -0.770000);
	setPresetParameter(preset->presetParameters, controlID::wseq5_panValue, 0.530000);
	setPresetParameter(preset->presetParameters, controlID::wseq6_panValue, 0.290000);
	setPresetParameter(preset->presetParameters, controlID::wseq7_panValue, 0.330000);
	setPresetParameter(preset->presetParameters, controlID::wseq8_panValue, -0.600000);
	setPresetParameter(preset->presetParameters, controlID::wseq1HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2HardSync, 0.120000);
	setPresetParameter(preset->presetParameters, controlID::wseq2Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3HardSync, 0.050000);
	setPresetParameter(preset->presetParameters, controlID::wseq3Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8HardSync, 0.150000);
	setPresetParameter(preset->presetParameters, controlID::wseq8Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneCents, 31.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneCents, -44.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneCents, 19.500008);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneCents, -11.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneCents, -3.000004);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneCents, -7.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneCents, 12.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneCents, -26.500000);
	setPresetParameter(preset->presetParameters, controlID::LFO_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SW, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::soloWaveLane, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::runStopWS, -0.000000);
	addPreset(preset);

	// --- Preset: majorscale
	preset = new PresetInfo(index++, "majorscale");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_outputAmplitude, 0.000000);
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
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 0.000000);
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
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1XFadeLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2StepLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2Pitch_semi, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3StepLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveIndex, 3.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3Pitch_semi, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4StepLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4XFadeLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveIndex, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4Pitch_semi, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5StepLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5XFadeLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveIndex, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5Pitch_semi, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6StepLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveIndex, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6Pitch_semi, 9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7StepLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7XFadeLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7Pitch_semi, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8XFadeLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveIndex, 17.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8Pitch_semi, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::timingStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::timingEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::timingLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::waveLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::timeStretch, -3.000000);
	setPresetParameter(preset->presetParameters, controlID::step1Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step2Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step3Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step4Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step5Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step6Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step7Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step8Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::interpolateStepSeqMod, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeStepOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizePitchOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 20.000000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeWaveOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeSSModOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_UniqueInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqModSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_osc_fo, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneCents, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneCents, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneCents, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneCents, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneCents, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneCents, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneCents, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneSemis, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneCents, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFO_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::soloWaveLane, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::runStopWS, -0.000000);
	addPreset(preset);

	// --- Preset: majorscaleFreak
	preset = new PresetInfo(index++, "majorscaleFreak");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::lfo1Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_waveform, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_frequency_Hz, 0.101398);
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
	setPresetParameter(preset->presetParameters, controlID::filter1Algorithm, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobC, 0.935000);
	setPresetParameter(preset->presetParameters, controlID::filter1_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc, 1231.144409);
	setPresetParameter(preset->presetParameters, controlID::filter1_Q, 6.175000);
	setPresetParameter(preset->presetParameters, controlID::filter1Output_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableFilter1KeyTrack, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_attackTime_mSec, 400.059967);
	setPresetParameter(preset->presetParameters, controlID::filterEG_decayTime_mSec, 725.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_sustainLevel, 0.125000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_releaseTime_mSec, 3999.999756);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobA, 0.475000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2Core, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_waveform, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_mode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_frequency_Hz, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_outputAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_quantize, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobA, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobC, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ModKnobD, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGCore, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_attackTime_mSec, 4000.059814);
	setPresetParameter(preset->presetParameters, controlID::auxEG_decayTime_mSec, 9250.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_sustainLevel, 0.675000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_releaseTime_mSec, 8750.000000);
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
	setPresetParameter(preset->presetParameters, controlID::globalPitchBendSens, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::synthMode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::glideTime_mSec, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1XFadeLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1Pitch_semi, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModValue, -0.790000);
	setPresetParameter(preset->presetParameters, controlID::ws1ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws1WaveIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2StepLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2Pitch_semi, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModValue, -0.550000);
	setPresetParameter(preset->presetParameters, controlID::ws2ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3StepLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveIndex, 18.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3Pitch_semi, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModValue, -0.360000);
	setPresetParameter(preset->presetParameters, controlID::ws3ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4StepLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4XFadeLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveIndex, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4Pitch_semi, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModValue, -0.120000);
	setPresetParameter(preset->presetParameters, controlID::ws4ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5StepLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5XFadeLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveIndex, 4.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5Pitch_semi, 7.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws5ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6StepLenIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6XFadeLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveIndex, 17.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6WaveAmp_dB, -3.240002);
	setPresetParameter(preset->presetParameters, controlID::ws6Pitch_semi, 9.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModValue, 0.200000);
	setPresetParameter(preset->presetParameters, controlID::ws6ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7StepLenIndex, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7XFadeLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveIndex, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7Pitch_semi, 11.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModValue, 0.610000);
	setPresetParameter(preset->presetParameters, controlID::ws7ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8StepLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8XFadeLenIndex, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveIndex, 17.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8WaveAmp_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8Pitch_semi, 12.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8PitchProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModValue, 0.950000);
	setPresetParameter(preset->presetParameters, controlID::ws8ModProb_pct, 100.000000);
	setPresetParameter(preset->presetParameters, controlID::timingStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::timingEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::timingLoopDir, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::waveLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::pitchLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModStartIndex, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModEndIndex, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::stepSeqModLoopDir, 2.000000);
	setPresetParameter(preset->presetParameters, controlID::timeStretch, -3.000000);
	setPresetParameter(preset->presetParameters, controlID::step1Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step2Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step3Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step4Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step5Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step6Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step7Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::step8Type, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::interpolateStepSeqMod, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeStepOrder, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizePitchOrder, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterModeIndex, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableDelayFX, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::leftDelay_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::rightDelay_mSec, 500.000000);
	setPresetParameter(preset->presetParameters, controlID::feedback_Pct, 20.000000);
	setPresetParameter(preset->presetParameters, controlID::dryLevel_dB, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::wetLevel_dB, -6.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeWaveOrder, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::randomizeSSModOrder, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_fo_Int, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_fo_Int, 0.780000);
	setPresetParameter(preset->presetParameters, controlID::osc_UniqueInt, 0.700000);
	setPresetParameter(preset->presetParameters, controlID::filterEGTrigInt, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGTrigInt, 0.680000);
	setPresetParameter(preset->presetParameters, controlID::filter1_fc_Int, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filter2_fc_Int, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::dcaPanInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGTrigInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1SourceInt, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filterEGTrig, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2SourceInt, 0.820000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_auxEGTrig, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEGSourceInt, 0.750000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter1_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_filter2_fc, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::filterEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEG_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGBiasedSourceInt, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_osc_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_oscUnique, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::auxEGB_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqModSourceInt, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_lfo2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_osc_fo, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_oscUnique, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filterEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_auxEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter1_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_filter2_fc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_dcaPan, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::waveSeqMod_ampEGTrig, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::ampEGIntensity, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8_panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8HardSync, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8Morph, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneSemis, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq1DetuneCents, 8.999996);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneSemis, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq2DetuneCents, -5.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneSemis, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq3DetuneCents, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneSemis, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq4DetuneCents, -16.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneSemis, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq5DetuneCents, 15.500000);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneSemis, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq6DetuneCents, -17.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneSemis, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq7DetuneCents, 13.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneSemis, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::wseq8DetuneCents, -17.000000);
	setPresetParameter(preset->presetParameters, controlID::LFO_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::EG_SW, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::FILTER_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::MAIN_SW, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::soloWaveLane, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::runStopWS, -0.000000);
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
    apiSpecificInfo.auBundleID = kAUBundleID;   /* MacOS only: this MUST match the bundle identifier in your info.plist file */
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
