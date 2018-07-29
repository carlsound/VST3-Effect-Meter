
#include "../include/meterController.h"
#include "../include/meterIDs.h"
//
#include "base/source/fstreamer.h"
#include "pluginterfaces/base/ibstream.h"
#include <string>
#include "public.sdk/source/vst/hosting/stringconvert.h"
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
					STR16 ("Bypass"), // title
			        0, // units
			        1, // stepCount
			        0, // defaultValueNormalized
                    Steinberg::Vst::ParameterInfo::kCanAutomate | Steinberg::Vst::ParameterInfo::kIsBypass, // flags
		            MeterParams::kParamBypassId, // tag
			        0, // unitUD
			        STR16("Bypass") // shortTitle
				); 
				//
				parameters.addParameter 
				(
					STR16 ("Speed"), // title
		            STR16 ("sec"), // units
			        99, // stepCount
			        0.1, // defaultValueNormalized
                    Steinberg::Vst::ParameterInfo::kCanAutomate, // flags
					GilbertsParams::kParamSpeedId, // tag
			        0, // unitID
		            STR16 ("Speed") // shortTitle
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
			/*
			setParamNormalized 
			(
				MeterParams::kParamSpeedId, 
				savedParam1
			);
			*/
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
			/*
			if(kParamSpeedId == tag)
			{
				return ((valueNormalized * ((10.0 - 0.1) / 1.0)) + 0.10);
			}
			*/
			if (kParamBypassId == tag)
			{
				return valueNormalized;
			}
		}
		//------------------------------------------------------------------------
		Steinberg::Vst::ParamValue MeterController::plainParamToNormalized
		(
			Steinberg::Vst::ParamID tag,
			Steinberg::Vst::ParamValue value
		)
		{
			/*
			if (kParamSpeedId == tag)
			{
				return (value / 10.0);
			}
			*/
			if (kParamBypassId == tag)
			{
				return value;
			}
		}
		//------------------------------------------------------------------------
		void string128copy(Steinberg::Vst::TChar *str128, std::string &str)
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
			if(MeterParams::kParamBypassId == tag)
			{
				if(valueNormalized) // on
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
			}
			/*
			if (MeterParams::kParamSpeedId == tag)
			{
                float valuePlain = ((valueNormalized * ((10.0 - 0.1) / 1.0)) + 0.10);
                //
                valuePlainAscii = std::to_string(valuePlain) + '\0';
				string128copy(string, valuePlainAscii);
			}
			*/
			return Steinberg::kResultOk;
		}
		//------------------------------------------------------------------------
	} // namespace Meter
} // namespace Carlsound
