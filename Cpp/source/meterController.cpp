
#include "../include/meterController.h"
//
#if(SMTG_OS_WINDOWS)
#include "../include/stdafx.h"
#endif // 
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
				//
				/*
				parameters.addParameter
				(
					STR16("Input Level"), // title
					STR16("dB"), // units
					0, // stepCount
					0, // defaultValueNormalized
					Steinberg::Vst::ParameterInfo::kIsReadOnly, //Steinberg::Vst::ParameterInfo::kCanAutomate, // flags
					MeterParameters::kParameterInputLevel, // tag
					0, // unitID
					STR16("Input Level") // shortTitle
				);
				*/
				//
				/*
				parameters.addParameter
				(
					STR16("Color"), // title
					STR16("Color"), // units
					0, // stepCount
					0, // defaultValueNormalized
					Steinberg::Vst::ParameterInfo::kIsReadOnly, // Steinberg::Vst::ParameterInfo::kCanAutomate, // flags
					MeterParameters::kParameterColor, // tag
					0, // unitID
					STR16("Color") // shortTitle
				);
				*/
				//
				parameters.addParameter
				(
					STR16("Bypass"), // title
					0, // units
					1, // stepCount
					0, // defaultValueNormalized
					Steinberg::Vst::ParameterInfo::kCanAutomate | Steinberg::Vst::ParameterInfo::kIsBypass, // flags
					MeterParameters::kParameterBypassId // , // tag
					//0, // unitUD
					//STR16("Bypass") // shortTitle
				);
				//
				parameters.addParameter
				(
					STR16("Threshold Level"), // title
					STR16("dB"), // units
					0, // stepCount
					0, // defaultValueNormalized
					Steinberg::Vst::ParameterInfo::kCanAutomate, // || Steinberg::Vst::ParameterInfo::kIsReadOnly, // flags
					MeterParameters::kParameterThreshold, // tag
					0, // unitID
					STR16("Threshold Level") // shortTitle
				);
				//
				parameters.addParameter
				(
					STR16("Input Level Feedback"), // title
					STR16("dB"), // units
					0, // stepCount
					0, // defaultValueNormalized
					Steinberg::Vst::ParameterInfo::kNoFlags, //Steinberg::Vst::ParameterInfo::kCanAutomate, // flags
					MeterParameters::kParameterInputLevelFeedback, // tag
					0, // unitID
					STR16("Input Level Feedback") // shortTitle
				);
				//
				parameters.addParameter
				(
					STR16("Color Feedback"), // title
					STR16("Color"), // units
					0, // stepCount
					0, // defaultValueNormalized
					Steinberg::Vst::ParameterInfo::kNoFlags, // Steinberg::Vst::ParameterInfo::kCanAutomate, // flags
					MeterParameters::kParameterColorFeedback, // tag
					0, // unitID
					STR16("Color Feedback") // shortTitle
				);
				//
				//---Member Variables------------
				m_view = nullptr;
				m_LevelInput = 0;
				m_LevelThreshold = 0;
				m_LevelColor = 0;
				//
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
			Steinberg::IBStreamer streamer(state, kLittleEndian);
			//
			// read the bypass
			Steinberg::int32 bypassState;
			if (streamer.readInt32(bypassState) == false)
			{
				return Steinberg::kResultFalse;
			}
			setParamNormalized(kParameterBypassId, bypassState ? 1 : 0);
			//
			float savedParam1 = 0.f;
			if (streamer.readFloat(savedParam1) == false)
			{
				return Steinberg::kResultFalse;
			}
			//OutputDebugStringW(L"setComponentState kParamLevel2\n");
			setParamNormalized(MeterParameters::kParameterThreshold, savedParam1);
			//
			/*
			float savedParam1 = 0.f;
			if (streamer.readFloat(savedParam1) == false)
			{
				return Steinberg::kResultFalse;
			}
			//OutputDebugStringW(L"setComponentState kParamLevel2\n");
			setParamNormalized(MeterParameters::kParameterInputLevel, savedParam1);
			*/
			//
			/*
			float savedParam2 = 0.f;
			if (streamer.readFloat(savedParam2) == false)
			{
				return Steinberg::kResultFalse;
			}
			//OutputDebugStringW(L"setComponentState kParamLevel\n");
			setParamNormalized (MeterParameters::kParameterColor, savedParam2);
			*/
			
			//
			float savedParam2 = 0.f;
			if (streamer.readFloat(savedParam2) == false)
			{
				return Steinberg::kResultFalse;
			}
			//OutputDebugStringW(L"setComponentState kParamLevel2\n");
			setParamNormalized(MeterParameters::kParameterInputLevelFeedback, savedParam2);
			//
			float savedParam3 = 0.f;
			if (streamer.readFloat(savedParam3) == false)
			{
				return Steinberg::kResultFalse;
			}
			//OutputDebugStringW(L"setComponentState kParamLevel2\n");
			setParamNormalized(MeterParameters::kParameterColorFeedback, savedParam3);
			//
			return Steinberg::kResultOk;
		}
		//------------------------------------------------------------------------
		/*
		Steinberg::tresult PLUGIN_API MeterController::setParamNormalized(
			Steinberg::Vst::ParamID tag, 
			Steinberg::Vst::ParamValue value)
		{
			Steinberg::Vst::Parameter* parameter = getParameterObject(tag);
			if (parameter)
			{
				//parameter->setNormalized(value);
				//return kResultTrue;
                //
                switch (tag)
                {
					case kParameterInputLevel:
					{
						//Steinberg::Vst::ParamValue levelValue2 = value;
						//m_Level2 = value;
						m_LevelInput = value; //parameter->getNormalized();
						//m_LevelColor = m_LevelInput;
						//m_LevelColor = parameter->getNormalized();
						//
                        //IdeConsoleWriteLine(L"setParamNormalized kParameterInputLevel\n");
                        std::string str = std::to_string(m_LevelInput);
                        std::wstring strw = std::wstring(str.begin(), str.end());
                        //IdeConsoleWriteLine(L"Input Level = ");
                        //IdeConsoleWriteLine(strw.c_str());
                        //IdeConsoleWriteLine(L"\n");
						//
						//m_GuiVuMeter_InputLevel;
						//
						if (componentHandler)
						{
							componentHandler->beginEdit(kParameterInputLevelFeedback);
							componentHandler->performEdit(kParameterInputLevelFeedback, value);
							componentHandler->endEdit(kParameterInputLevelFeedback);
						}
						//
						#if(SMTG_OS_OSX || SMTG_OS_MACOS)
							if (m_view)
							{
								//m_view->setInputLevelFeedback(m_LevelInput);
							}
						#endif

						#if(SMTG_OS_WINDOWS)
							if (m_view)
							{
								m_view->setInputLevelFeedback(m_LevelInput);
							}
						#endif
						//
						break;
					}
					case kParameterThreshold:
					{
						/*
						if (componentHandler)
						{
							componentHandler->beginEdit(tag);
							componentHandler->performEdit(tag, value);
							componentHandler->endEdit(tag);
						}
						*/
						//m_LevelThreshold = value; 
						//parameter->getNormalized();

						/*
						break;
					}
                    case kParameterColor:
                    {
                        //Steinberg::Vst::ParamValue levelValue1 = value;
                        //m_Level1 = value;
						m_LevelColor = value; //parameter->getNormalized();
                        //
						//IdeConsoleWriteLine(L"setParamNormalized kParameterColor\n");
                        std::string str = std::to_string(m_LevelColor);
                        std::wstring strw = std::wstring(str.begin(), str.end());
                        //IdeConsoleWriteLine(L"Color = ");
                        //IdeConsoleWriteLine(strw.c_str());
                        //IdeConsoleWriteLine(L"\n\n");
						//
						if (componentHandler)
						{
							componentHandler->beginEdit(kParameterColorFeedback);
							componentHandler->performEdit(kParameterColorFeedback, value);
							componentHandler->endEdit(kParameterColorFeedback);
						}
						//
						#if(SMTG_OS_OSX || SMTG_OS_MACOS)
							if (m_view)
							{
								//m_view->setInputLevelFeedback(m_LevelInput);
							}
						#endif

						#if(SMTG_OS_WINDOWS)
							if (m_view)
							{
								m_view->setColorFeedback(m_LevelColor);
							}
						#endif
						//
                        break;
                    }
					case kParameterBypassId:
					{
						break;
					}
                }
			}
			//return kResultFalse;
			//
			//normalizedParamToPlain(tag, value);
            //
			return Steinberg::kResultTrue;
		}
		*/
		//------------------------------------------------------------------------
		/*
		Steinberg::Vst::ParamValue PLUGIN_API MeterController::normalizedParamToPlain (
			Steinberg::Vst::ParamID tag,
			Steinberg::Vst::ParamValue value)
		{
			switch (tag)
			{
				case kParameterInputLevel:
				{
					return value;
					break;
				}
				case kParameterInputLevelFeedback:
				{
					return value;
					break;
				}
				case kParameterThreshold:
				{
					return value;
					break;
				}
				case kParameterColor:
				{
					//OutputDebugStringW(L"normalizedParamToPlain");
					//OutputDebugStringW(L"mParamLevelValue = ");
					//OutputDebugStringW((std::to_wstring(abs(mParamLevelValue*100.0)).c_str()));
					//OutputDebugStringW(L"\n");
					return value;
					break;
				}
				case kParameterColorFeedback:
				{
					return value;
					break;
				}
				
				case kParameterBypassId:
				{
					return value;
					break;
				}
			}
			return value;
		}
		*/
		//------------------------------------------------------------------------
		/*
		Steinberg::Vst::ParamValue MeterController::plainParamToNormalized (
			Steinberg::Vst::ParamID tag,
			Steinberg::Vst::ParamValue value)
		{
			switch (tag)
			{
				case kParameterInputLevel:
				{
					return value;
					break;
				}
				case kParameterInputLevelFeedback:
				{
					return value;
					break;
				}
				case kParameterThreshold:
				{
					return value;
					break;
				}
				case kParameterColor:
				{
					//OutputDebugStringW(L"plainParamToNormalized");
					//OutputDebugStringW(L"mParamLevelValue = ");
					//OutputDebugStringW((std::to_wstring(abs(mParamLevelValue*100.0)).c_str()));
					//OutputDebugStringW(L"\n");
					return value;
					break;
				}
				case kParameterColorFeedback:
				{
					return value;
					break;
				}
				case kParameterBypassId:
				{
					return value;
					break;
				}
			}
			return value;
		}
		*/
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
		/*
		Steinberg::tresult MeterController::getParamStringByValue (
			Steinberg::Vst::ParamID tag,
			Steinberg::Vst::ParamValue valueNormalized,
			Steinberg::Vst::String128 string)
		{
			std::string valuePlainAscii;
            char* suffix_char = new char;
            *suffix_char = '\0';
            std::string suffix_str(suffix_char);
			//
			switch (tag)
			{
				case kParameterInputLevel:
				{
					float valuePlain = valueNormalized;
					//
					valuePlainAscii = std::to_string(valuePlain) + suffix_str;
					string128copy(string, valuePlainAscii);
					//
					break;
				}
				case kParameterInputLevelFeedback:
				{
					float valuePlain = valueNormalized;
					//
					valuePlainAscii = std::to_string(valuePlain) + suffix_str;
					string128copy(string, valuePlainAscii);
					//
					break;
				}
				case kParameterThreshold:
				{
					float valuePlain = valueNormalized;
					//
					valuePlainAscii = std::to_string(valuePlain) + suffix_str;
					string128copy(string, valuePlainAscii);
					//
					break;
				}
				case kParameterColor:
				{
					float valuePlain = valueNormalized;
					//
					//valuePlainAscii = std::to_string(valuePlain) + '\0';
					if (valuePlain <= 0.05)
					{
						valuePlainAscii = " light green" + suffix_str;
					}
					else if (valuePlain <= 0.1)
					{
						valuePlainAscii = " green" + suffix_str;
					}
					else if (valuePlain <= 0.25)
					{
                        valuePlainAscii = " dark green" + suffix_str;
					}
					else if (valuePlain <= 0.5)
					{
						valuePlainAscii = " yellow" + suffix_str;
					}
					else if (valuePlain <= 0.75)
					{
						valuePlainAscii = " orange" + suffix_str;
					}
					else
					{
						valuePlainAscii = " red" + suffix_str;
					}
					string128copy(string, valuePlainAscii);
					//
					break;
				}
				case kParameterColorFeedback:
				{
					float valuePlain = valueNormalized;
					//
					//valuePlainAscii = std::to_string(valuePlain) + '\0';
					if (valuePlain <= 0.05)
					{
						valuePlainAscii = " light green" + suffix_str;
					}
					else if (valuePlain <= 0.1)
					{
						valuePlainAscii = " green" + suffix_str;
					}
					else if (valuePlain <= 0.25)
					{
						valuePlainAscii = " dark green" + suffix_str;
					}
					else if (valuePlain <= 0.5)
					{
						valuePlainAscii = " yellow" + suffix_str;
					}
					else if (valuePlain <= 0.75)
					{
						valuePlainAscii = " orange" + suffix_str;
					}
					else
					{
						valuePlainAscii = " red" + suffix_str;
					}
					string128copy(string, valuePlainAscii);
					//
					break;
				}
				case kParameterBypassId:
				{
					if (valueNormalized) // on
					{
						valuePlainAscii.clear();
						valuePlainAscii = "On: Bypassed" + suffix_str;
					}
					else // off
					{
						valuePlainAscii.clear();
						valuePlainAscii = "Off: Active" + suffix_str;
					}
					string128copy(string, valuePlainAscii);
					//
					break;
				}
			}
			return Steinberg::kResultOk;
		}
		*/
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
						id = kParameterBypassId;
						break;
					}
					case Steinberg::Vst::ControllerNumbers::kCtrlGPC2:
					{
						id = kParameterThreshold;
						break;
					}
				}
				return id != 0 ? Steinberg::kResultTrue : Steinberg::kResultFalse;
			}
			return Steinberg::kResultFalse;
		}
		//------------------------------------------------------------------------
		/*
		Steinberg::IPlugView* PLUGIN_API MeterController::createView (const char* name)
		{
			if (name && strcmp(name, "editor") == 0)
			{
				#if(SMTG_OS_OSX || SMTG_OS_MACOS)
                    m_view = new MeterPlugViewCocoa();
				#endif

				#if(SMTG_OS_WINDOWS)
					m_view = new MeterControllerViewWin32WpfHost();
				#endif

				return m_view;
			}
			return nullptr;
		}
		*/
		//------------------------------------------------------------------------
		/*
		Steinberg::tresult PLUGIN_API MeterController::notify (Steinberg::Vst::IMessage* message)
		{
			if (!message)
				return Steinberg::kInvalidArgument;

			//OutputDebugStringW(L"notify()\n");
			m_Message = new Carlsound::Vst::ComponentMessage();
			//m_Message = message;
			m_AttributeList = new Carlsound::Vst::ComponentAttributeList();
			//
			//std::string msg = m_Message->getMessageID();
			std::string msg = message->getMessageID();
			//std::wstring msgw = std::wstring(msg.begin(), msg.end());
			//LPCWSTR str = msgw.c_str();
			//OutputDebugString(str);
			//OutputDebugStringW(L"\n");
			//
			//m_AttributeList = message->getAttributes(); //m_Message->getAttributes();
			Steinberg::Vst::IAttributeList *m_list = message->getAttributes();
			double m_attributeValue = 0.0;
			Steinberg::tresult test = m_list->getFloat("level", m_attributeValue);
			if (test)
			{
				//int i = 1;
			}
			else
			{
				//int i = 0;
			}
			setParamNormalized(kParameterInputLevel, m_attributeValue);
			//
			//std::string str = std::to_string(m_attributeValue);
			//std::wstring strw = std::wstring(str.begin(), str.end());
			//OutputDebugStringW(L"level = ");
			//OutputDebugStringW(strw.c_str());
			//OutputDebugStringW(L"\n");
			//int i = 0;
			// TODO: store to parameter
			//
			//delete m_AttributeList;
			//delete m_Message;
			//
			/*
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
			*/
			/*
			return Steinberg::kResultTrue;
		}
		*/
		//------------------------------------------------------------------------
		/*
		Steinberg::tresult PLUGIN_API MeterController::receiveText(const char* text)
		{
			//OutputDebugStringW(L"receiveText()");
			return Steinberg::kResultTrue;
		}
		*/
	} // namespace Meter
} // namespace Carlsound
