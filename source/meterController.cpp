
#include "../include/meterController.h"
//
namespace Carlsound
{
	namespace Meter 
	{
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterController::initialize (FUnknown* context)
		{
			Steinberg::tresult result = EditController::initialize (context);
			if (result == Steinberg::kResultTrue)
			{
				//---Create Parameters------------
				/*
				m_speedRangeParameter = std::make_shared<Steinberg::Vst::RangeParameter>
				(
					STR16("Level"), // title
					kParamLevel, // ParamID
					STR16("dB"), // units
					0.0001, // minPlain
					1.0000, // maxPlain
					0.0000, // defaultValuePlain
					100, // stepCount
					Steinberg::Vst::ParameterInfo::kCanAutomate, // flags
					0, // unitID
					STR16("Level") // shortTitle
				);
				parameters.addParameter
				(
					m_speedRangeParameter->getInfo()
				);
				*/
				parameters.addParameter 
				(
					STR16 ("Level"), // title
		            STR16 ("dB"), // units
			        100, // stepCount
			        0, // defaultValueNormalized
                    Steinberg::Vst::ParameterInfo::kIsReadOnly, // flags
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
			}
			return Steinberg::kResultTrue;
		}
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterController::setComponentState (Steinberg::IBStream* state)
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
		Steinberg::Vst::ParamValue PLUGIN_API MeterController::normalizedParamToPlain (
			Steinberg::Vst::ParamID tag,
			Steinberg::Vst::ParamValue value)
		{
			switch (tag)
			{
				case kParamLevel:
				{
					OutputDebugStringW(L"normalizedParamToPlain");
					//OutputDebugStringW(L"mParamLevelValue = ");
					//OutputDebugStringW((std::to_wstring(abs(mParamLevelValue*100.0)).c_str()));
					//OutputDebugStringW(L"\n");
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
		Steinberg::Vst::ParamValue MeterController::plainParamToNormalized (
			Steinberg::Vst::ParamID tag,
			Steinberg::Vst::ParamValue value)
		{
			switch (tag)
			{
				case kParamLevel:
				{
					OutputDebugStringW(L"plainParamToNormalized");
					//OutputDebugStringW(L"mParamLevelValue = ");
					//OutputDebugStringW((std::to_wstring(abs(mParamLevelValue*100.0)).c_str()));
					//OutputDebugStringW(L"\n");
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
		void string128copy (
			Steinberg::Vst::TChar *str128, 
			std::string &str)
		{
			for (int i = 0; i < str.length(); i++)
			{
				str128[i] = str[i];
			}
			str128[str.length()] = '\0';
		}
		//------------------------------------------------------------------------
		Steinberg::tresult MeterController::getParamStringByValue (
			Steinberg::Vst::ParamID tag,
			Steinberg::Vst::ParamValue valueNormalized,
			Steinberg::Vst::String128 string)
		{
			std::string valuePlainAscii;
			//
			switch (tag)
			{
				case kParamLevel:
				{
					float valuePlain = valueNormalized;
					//
					valuePlainAscii = std::to_string(valuePlain) + '\0';
					string128copy(string, valuePlainAscii);
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
		Steinberg::tresult PLUGIN_API MeterController::getMidiControllerAssignment(
			Steinberg::int32 busIndex,
			Steinberg::int16 channel,
			Steinberg::Vst::CtrlNumber midiControllerNumber,
			Steinberg::Vst::ParamID& id)
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
					case Steinberg::Vst::ControllerNumbers::kCtrlGPC1:
					{
						id = kParamLevel;
						break;
					}
					case Steinberg::Vst::ControllerNumbers::kCtrlGPC2:
					{
						id = kParamBypassId;
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
		Steinberg::tresult PLUGIN_API MeterController::notify (Steinberg::Vst::IMessage* message)
		{
			if (!message)
				return Steinberg::kInvalidArgument;

			//OutputDebugStringW(L"notify()");

			if (!strcmp(message->getMessageID(), "BinaryMessage"))
			{
				const void* data;
				Steinberg::uint32 size;
				if (message->getAttributes()->getBinary("MyData", data, size) == Steinberg::kResultOk)
				{
					// we are in UI thread
					// size should be 100
					if (size == 100 && ((char*)data)[1] == 1) // yeah...
					{
						fprintf(stderr, "[AGain] received the binary message!\n");
					}
					return Steinberg::kResultOk;
				}
			}

			return Steinberg::kResultFalse;
		}

		Steinberg::tresult PLUGIN_API MeterController::receiveText(const char* text)
		{
			OutputDebugStringW(L"receiveText()");
			int i = 1;
			return Steinberg::kResultTrue;
		}
	} // namespace Meter
} // namespace Carlsound
