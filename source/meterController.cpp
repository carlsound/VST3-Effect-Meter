
#include "../include/meterController.h"
//
namespace Carlsound
{
	namespace Meter 
	{
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterController::initialize 
		(
			FUnknown* context
		)
		{
			Steinberg::tresult result = EditController::initialize (context);
			if (result == Steinberg::kResultTrue)
			{
				//---Create Parameters------------
				parameters.addParameter 
				(
					STR16 ("Level"), // title
		            STR16 (""), // units
			        1000, // stepCount
			        0.0, // defaultValueNormalized
                    Steinberg::Vst::ParameterInfo::kCanAutomate, // flags
					MeterParameters::kParamLevel, // tag
			        0, // unitID
		            STR16 ("Level") // shortTitle
				); 
				//
				parameters.addParameter
				(
					STR16 ("Bypass"), // title
					0, // units
					1, // stepCount
					0, // defaultValueNormalized
					Steinberg::Vst::ParameterInfo::kCanAutomate | Steinberg::Vst::ParameterInfo::kIsBypass, // flags
					MeterParameters::kParamBypassId, // tag
					0, // unitUD
					STR16 ("Bypass") // shortTitle
				);
				/*
				m_speedRangeParameter = std::make_shared<Steinberg::Vst::RangeParameter> 
				(
					STR16("Speed"), // title
			        GilbertsParams::kParamSpeedId, // ParamID
			        STR16("sec"), // units
			        0.1, // minPlain
			        10.0, // maxPlain
			        1.0, // defaultValuePlain
			        99, // stepCount
			        Steinberg::Vst::ParameterInfo::kCanAutomate, // flags
			        0, // unitID
			        STR16("Speed") // shortTitle
				); 
				parameters.addParameter
				(
					m_speedRangeParameter->getInfo()
				);
				*/
			}
			return Steinberg::kResultTrue;
		}
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterController::setComponentState 
		(
			Steinberg::IBStream* state
		)
		{
			// we receive the current state of the component (processor part)
			// we read our parameters and bypass value...
			if (!state)
				return Steinberg::kResultFalse;
			//
			Steinberg::IBStreamer streamer 
			(
				state, 
				kLittleEndian
			);
			//
			float savedParam1 = 0.f;
			if (streamer.readFloat(savedParam1) == false)
			{
				return Steinberg::kResultFalse;
			}
			setParamNormalized 
			(
				MeterParameters::kParamLevel, 
				savedParam1
			);
			//
			// read the bypass
			Steinberg::int32 bypassState;
			if (streamer.readInt32(bypassState) == false)
			{
				return Steinberg::kResultFalse;
			}	
			setParamNormalized 
			(
				kParamBypassId, 
				bypassState ? 1 : 0
			);
			//
			return Steinberg::kResultOk;
		}
		//------------------------------------------------------------------------
		Steinberg::Vst::ParamValue MeterController::normalizedParamToPlain
		(
			Steinberg::Vst::ParamID tag,
			Steinberg::Vst::ParamValue valueNormalized
		)
		{
			switch (tag)
			{
				case kParamLevel:
				{
					return valueNormalized;
					break;
				}
				case kParamBypassId:
				{
					return valueNormalized;
					break;
				}
			}
			return valueNormalized;
		}
		//------------------------------------------------------------------------
		Steinberg::Vst::ParamValue MeterController::plainParamToNormalized
		(
			Steinberg::Vst::ParamID tag,
			Steinberg::Vst::ParamValue value
		)
		{
			switch (tag)
			{
				case kParamLevel:
				{
					return value;
					break;
				}
				case kParamBypassId:
				{
					return value;
					break;
				}
			}
			return value;
		}
		//------------------------------------------------------------------------
		void string128copy
		(
			Steinberg::Vst::TChar *str128, 
			std::string &str
		)
		{
			for (int i = 0; i < str.length(); i++)
			{
				str128[i] = str[i];
			}
			str128[str.length()] = '\0';
		}

		//------------------------------------------------------------------------
		Steinberg::tresult MeterController::getParamStringByValue
		(
			Steinberg::Vst::ParamID tag,
			Steinberg::Vst::ParamValue valueNormalized,
			Steinberg::Vst::String128 string
		)
		{
			std::string valuePlainAscii;
			//
			switch (tag)
			{
				case kParamLevel:
				{
					//float valuePlain = ((valueNormalized * ((10.0 - 0.1) / 1.0)) + 0.10);
					//
					//valuePlainAscii = std::to_string(valuePlain) + '\0';
					//string128copy(string, valuePlainAscii);
					//
					break;
				}
				case kParamBypassId:
				{
					if (valueNormalized) // on
					{
						valuePlainAscii.clear();
						valuePlainAscii = "On: Bypassed\0";
					}
					else // off
					{
						valuePlainAscii.clear();
						valuePlainAscii = "Off: Active\0";
					}
					string128copy(string, valuePlainAscii);
					//
					break;
				}
			}
			return Steinberg::kResultOk;
		}
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterController::getMidiControllerAssignment
		(
			Steinberg::int32 busIndex,
			Steinberg::int16 channel,
			Steinberg::Vst::CtrlNumber midiControllerNumber,
			Steinberg::Vst::ParamID& id
		)
		{
			//throw std::logic_error("The method or operation is not implemented.");
			if (busIndex == 0 && channel == 0)
			{
				id = 0;
				switch (midiControllerNumber)
				{
					//case Steinberg::Vst::ControllerNumbers::kPitchBend: id = kParamMasterTuning; break;
					//case Steinberg::Vst::ControllerNumbers::kCtrlVolume: id = kParamMasterVolume; break;
					//case Steinberg::Vst::ControllerNumbers::kCtrlFilterCutoff: id = kParamFilterFreq; break;
					//case Steinberg::Vst::ControllerNumbers::kCtrlFilterResonance: id = kParamFilterQ; break;
					//
					case Steinberg::Vst::ControllerNumbers::kCtrlVolume:
					{
						id = kParamLevel;
						break;
					}
				}
				return id != 0 ? Steinberg::kResultTrue : Steinberg::kResultFalse;
			}
			return Steinberg::kResultFalse;
		}

		//------------------------------------------------------------------------
		/*
		Steinberg::IPlugView* PLUGIN_API MeterController::createView
		(
			const char* name
		)
		{
			using namespace VSTGUI;
			using namespace Steinberg;
			using namespace Steinberg::Vst;
			if (name && strcmp(name, "editor") == 0)
			{
				VST3Editor* view = new VST3Editor (this, "view", "meter.uidesc");
				return view;
			}
			return nullptr;
		}
		*/

		//------------------------------------------------------------------------
	} // namespace Meter
} // namespace Carlsound
