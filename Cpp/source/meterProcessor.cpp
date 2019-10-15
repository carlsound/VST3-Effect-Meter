#include <cstring>
#include "../include/meterProcessor.h"
//
namespace Carlsound
{
	namespace Meter
	{
		//-----------------------------------------------------------------------------
		MeterProcessor::MeterProcessor ()
		{
			// register its editor class
			setControllerClass (MeterControllerUID);
			//
			//m_Message = std::make_shared<Steinberg::Vst::IMessage*>();
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterProcessor::initialize 
		(
			FUnknown* context
		)
		{
			//---always initialize the parent-------
			Steinberg::tresult result = AudioEffect::initialize (context);
			if (result != Steinberg::kResultTrue) { return Steinberg::kResultFalse; }
			//
			//---create Audio In/Out buses------
			// we want a stereo Input and a Stereo Output
			addAudioInput (STR16 ("AudioInput"), Steinberg::Vst::SpeakerArr::kStereo);
			addAudioOutput (STR16 ("AudioOutput"), Steinberg::Vst::SpeakerArr::kStereo);
			//
			//---create Event In/Out buses------
			addEventInput(STR16("MidiInput"), 1);
			addEventOutput(STR16("MidiOutput"), 1);
			//
			return Steinberg::kResultTrue;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterProcessor::setBusArrangements (
			Steinberg::Vst::SpeakerArrangement* inputs,
            Steinberg::int32 numIns,
            Steinberg::Vst::SpeakerArrangement* outputs,
            Steinberg::int32 numOuts)
		{
			// we only support one in and output bus and these buses must have the same number of channels
			if (numIns == 1 && numOuts == 1 && inputs[0] == outputs[0])
			{
				return AudioEffect::setBusArrangements (inputs, numIns, outputs, numOuts);
			}
			return Steinberg::kResultFalse;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterProcessor::setActive (Steinberg::TBool state)
		{
			if (state) // Initialize
			{
				// Allocate Memory Here
				// Ex: algo.create ();
			}
			else // Release
			{
				// Free Memory if still allocated
				// Ex: if(algo.isCreated ()) { algo.destroy (); }
			}
			return AudioEffect::setActive (state);
		}
		//-----------------------------------------------------------------------------
		template<class T>
		inline void Carlsound::Meter::MeterProcessor::bufferSampleGain (
			T inBuffer, 
			T outBuffer, 
			const int sampleLocation)
		{
			inBuffer = inBuffer + sampleLocation;  // pointer arithmetic
			outBuffer = outBuffer + sampleLocation; // pointer arithmetic
			//
			*outBuffer = *inBuffer;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterProcessor::processInputParameters (Steinberg::Vst::ProcessData& data)
		{
			//--- Read inputs parameter changes-----------
			if (data.inputParameterChanges)
			{
				Steinberg::int32 numParamsChanged = data.inputParameterChanges->getParameterCount();
				for (Steinberg::int32 index = 0; index < numParamsChanged; index++)
				{
					Steinberg::Vst::IParamValueQueue* paramQueue =
						data.inputParameterChanges->getParameterData(index);
					if (paramQueue)
					{
						Steinberg::Vst::ParamValue value;
						Steinberg::int32 sampleOffset;
						Steinberg::int32 numPoints = paramQueue->getPointCount();
						switch (paramQueue->getParameterId())
						{
							/*
							case MeterParameters::kParamLevel:
							{
								if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
									Steinberg::kResultTrue)
								{
									//m_speedNormalizedValue = value;
									break;
								}
							}
							*/
							case MeterParameters::kParameterInputLevel:
							{
							if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
								Steinberg::kResultTrue)
								{
									m_ParameterInputLevelValue = value;
									break;
								}
							}

							case MeterParameters::kParameterThreshold:
							{
								if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
									Steinberg::kResultTrue)
								{
									m_ParameterThresholdlValue = value;
									break;
								}
							}
			
							case MeterParameters::kParameterBypassId:
							{
								if (paramQueue->getPoint
								(
									numPoints - 1,
									sampleOffset,
									value
								) ==
									Steinberg::kResultTrue)
								{
									m_BypassState = (value > 0.5f);
									break;
								}
							}
						}
					}
				}
			}
			return Steinberg::kResultTrue;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterProcessor::processAudio (Steinberg::Vst::ProcessData& data)
		{
			//--- Process Audio---------------------
			//--- ----------------------------------
			if (data.numInputs == 0 || data.numOutputs == 0)
			{
				// nothing to do
				return Steinberg::kResultOk;
			}
			//
			if (data.numSamples > 0)
			{
				// Process Algorithm
				// Ex: algo.process (data.inputs[0].channelBuffers32, data.outputs[0].channelBuffers32,
				// data.numSamples);
				//
				//
				// assume the same input channel count as the output
				Steinberg::int32 numChannels = data.inputs[0].numChannels;
				//
				//---get audio buffers----------------
				Steinberg::uint32 sampleFramesSize = getSampleFramesSizeInBytes
				(
					processSetup,
					data.numSamples
				);
				void** in = getChannelBuffersPointer
				(
					processSetup,
					data.inputs[0]
				);
				void** out = getChannelBuffersPointer
				(
					processSetup,
					data.outputs[0]
				);
				//
				//---check if silence---------------
				// normally we have to check each channel (simplification)
				if (data.inputs[0].silenceFlags != 0)
				{
					// mark output silence too
					data.outputs[0].silenceFlags = data.inputs[0].silenceFlags;
					//
					// the Plug-in has to be sure that if it sets the flags silence that the output buffer are clear
					for (Steinberg::int32 i = 0; i < numChannels; i++)
					{
						// do not need to be cleared if the buffers are the same (in this case input buffer are already cleared by the host)
						if (in[i] != out[i])
						{
							std::memset(out[i], 0, sampleFramesSize);
						}
					}
					// nothing to do at this point
					return Steinberg::kResultOk;
				}
				// mark our outputs has not silent
				data.outputs[0].silenceFlags = 0;
				//
				if (!m_BypassState)
				{
					m_GainValue[0] = 1.0;
					m_GainValue[1] = 1.0;
					//
					if (data.symbolicSampleSize == Steinberg::Vst::kSample64) //64-Bit
					{
						m_ParameterInputLevelValue = static_cast<Steinberg::Vst::Sample64*>(in[0])[0];
						//m_ParameterLightsValue = m_ParameterInputLevelValue;
                        //m_ParameterLightsValue = static_cast<Steinberg::Vst::Sample64*>(in[0])[0];
						if (static_cast<Steinberg::Vst::Sample64*>(in[0])[0] >= m_ParameterThresholdlValue)
						{
							m_ParameterColorValue = 1.0;
						}
						else
						{
							m_ParameterColorValue = 0.0;
						}
						//TODO: add notify message here for a callback to the controller
						//sendMessage()
						//sendTextMessage("Level");
					}
					else // 32-bit
					{
						m_ParameterInputLevelValue = static_cast<Steinberg::Vst::Sample32*>(in[0])[0];
                        //m_ParameterLightsValue = m_ParameterInputLevelValue;
                        //m_ParameterLightsValue = static_cast<Steinberg::Vst::Sample32*>(in[0])[0];
						if (static_cast<Steinberg::Vst::Sample32*>(in[0])[0] >= m_ParameterThresholdlValue)
						{
							m_ParameterColorValue = 1.0;
						}
						else
						{
							m_ParameterColorValue = 0.0;
						}
                        //TODO: add notify message here for a callback to the controller
					}
					//
					for (int sample = 0; sample < data.numSamples; sample++)
					{
						/*
						if (data.symbolicSampleSize == Steinberg::Vst::kSample64) //64-Bit
						{
							m_ParamLevelValue = static_cast<Steinberg::Vst::Sample64*>(in[0])[sample];
						}
						else // 32-bit
						{
							m_ParamLevelValue = static_cast<Steinberg::Vst::Sample32*>(in[0])[sample];
						}
						*/
						//
						//
						//
						/*
						Steinberg::Vst::IParameterChanges* paramChanges = data.outputParameterChanges;
						if (paramChanges)
						{
							mOutputParamValueQueue = paramChanges->addParameterData(kParamLevel,
								mOutputParameterChangesDataIndex);
							if (mOutputParamValueQueue)
							{
								mOutputParamValueQueue->addPoint(0,
									abs(mParamLevelValue*100.0),
									mOutputParameterValueQueuePointIndex);
								//mOutputParameterChangesDataIndex);
								OutputDebugStringW(L"mParamLevelValue = ");
								OutputDebugStringW((std::to_wstring(abs(mParamLevelValue*100.0)).c_str()));
								OutputDebugStringW(L"\n");
								//return Steinberg::kResultTrue;
								
							}
						}
						*/
						//
						//
						//
						for (int channel = 0; channel < data.outputs->numChannels; channel++)
						{
							if (data.symbolicSampleSize == Steinberg::Vst::kSample64) //64-Bit
							{
								bufferSampleGain
								(
									static_cast<Steinberg::Vst::Sample64*>(in[channel]),
									static_cast<Steinberg::Vst::Sample64*>(out[channel]),
									sample
								);
							}
							else // 32-Bit
							{
								bufferSampleGain
								(
									static_cast<Steinberg::Vst::Sample32*>(in[channel]),
									static_cast<Steinberg::Vst::Sample32*>(out[channel]),
									sample
								);
							}
						}
					}
				}
			}
			return Steinberg::kResultTrue;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterProcessor::processOutputParameters(Steinberg::Vst::ProcessData& data)
		{
			// Write outputs parameter changes-----------
			m_OutputParameterChanges = data.outputParameterChanges;
			//if (m_OutputParameterChanges)
			//{
				m_ParameterInputLevelValueQueue = m_OutputParameterChanges->addParameterData(kParameterInputLevel,
					m_OutputParameterChangesDataIndex);
				if (m_ParameterInputLevelValueQueue)
				{
					if (m_ParameterInputLevelValue > 1.0)
					{
						m_ParameterInputLevelValue = 1.0;
					}
                    Steinberg::int32 index2 = 0;
					Steinberg::tresult test = m_ParameterInputLevelValueQueue->addPoint(0,
						abs(m_ParameterInputLevelValue),
						//0.5,
						//m_ParamLevelValue2,
						//m_OutputParameterValueQueuePointIndex);
                        index2);
					//mOutputParameterChangesDataIndex);
					//Steinberg::Vst::IEditController->setParamNormalized(kParameterInputLevel, abs(m_ParameterInputLevelValue));
					//
					if (test == Steinberg::kResultOk)
					{
						//int i = 0;
						//OutputDebugStringW(L"mParamLevelValue = ");
						//OutputDebugStringW((std::to_wstring(abs(m_ParamLevelValue*100.0)).c_str()));
						//OutputDebugStringW(L"\n");
						//
						//m_Message = new Steinberg::Vst::HostMessage();
						//m_Message->setMessageID("a");
						//m_Message->setMessageID(std::to_string(abs(m_ParamLevelValue*10.0)).c_str());
						//sendMessage(m_Message);
						//delete m_Message;
						//
						//return Steinberg::kResultTrue;
					}
				}
				//
				//
				//
				m_ParameterColorValueQueue = m_OutputParameterChanges->addParameterData(kParameterColor,
					m_OutputParameterChangesDataIndex);
				if (m_ParameterColorValueQueue)
				{
					if (m_ParameterColorValue > 1.0)
					{
						m_ParameterColorValue = 1.0;
					}
					Steinberg::int32 index2 = 0;
					Steinberg::tresult test = m_ParameterColorValueQueue->addPoint(0,
						abs(m_ParameterColorValue),
						//m_OutputParameterValueQueuePointIndex);
						index2);
					//mOutputParameterChangesDataIndex);
					if (test == Steinberg::kResultOk)
					{
						return Steinberg::kResultTrue;
					}
				}
			//}
			return Steinberg::kResultFalse;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterProcessor::processMidiOutputEvents (Steinberg::Vst::ProcessData& data)
		{
			// Write outputs parameter changes-----------
			if (data.outputEvents)
			{
				//
				if (m_ParameterInputLevelValue <= m_ParameterThresholdlValue)
				{
					m_ParameterColorValue = 0.0;
					//
					mEvent.type = Steinberg::Vst::Event::kNoteOffEvent;
					mEvent.noteOff.pitch = 24;
					/*
					mEvent[1].type = Steinberg::Vst::Event::kNoteOffEvent;
					mEvent[1].noteOff.pitch = 25;
					mEvent[2].type = Steinberg::Vst::Event::kNoteOffEvent;
					mEvent[2].noteOff.pitch = 26;
					mEvent[3].type = Steinberg::Vst::Event::kNoteOffEvent;
					mEvent[3].noteOff.pitch = 27;
					mEvent[4].type = Steinberg::Vst::Event::kNoteOffEvent;
					mEvent[4].noteOff.pitch = 28;
					*/
				}
				else
				{
					m_ParameterColorValue = 1.0;
					//
					mEvent.type = Steinberg::Vst::Event::kNoteOnEvent;
					mEvent.noteOn.pitch = 24;
					mEvent.noteOn.velocity = 127;
					/*
					mEvent[1].type = Steinberg::Vst::Event::kNoteOnEvent;
					mEvent[1].noteOn.pitch = 25;
					mEvent[1].noteOn.velocity = 127;
					mEvent[2].type = Steinberg::Vst::Event::kNoteOnEvent;
					mEvent[2].noteOn.pitch = 26;
					mEvent[2].noteOn.velocity = 127;
					mEvent[3].type = Steinberg::Vst::Event::kNoteOnEvent;
					mEvent[3].noteOn.pitch = 27;
					mEvent[3].noteOn.velocity = 127;
					mEvent[4].type = Steinberg::Vst::Event::kNoteOnEvent;
					mEvent[4].noteOn.pitch = 28;
					mEvent[4].noteOn.velocity = 127;
					*/
				}
				//
				data.outputEvents->addEvent(mEvent);
				/*
				Steinberg::Vst::IEventList* outputEvents = data.outputEvents;
				for (int i = 0; i < 5; i++)
				{
					outputEvents->addEvent(mEvent[i]);
				}
				*/
			}
			return Steinberg::kResultTrue;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterProcessor::process(Steinberg::Vst::ProcessData& data)
		{
			processInputParameters(data);
			processAudio(data);
			processOutputParameters(data);
			processMidiOutputEvents(data);
			//
			return Steinberg::kResultTrue;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterProcessor::setState (Steinberg::IBStream* state)
		{
			if (!state)
			{
				return Steinberg::kResultFalse;
			}
			//
			// called when we load a preset or project, the model has to be reloaded
			//
			Steinberg::IBStreamer streamer 
			(
				state, 
				kLittleEndian
			);
			//
			float savedParam1 = 0.f;
			if (false == streamer.readFloat(savedParam1))
			{
				return Steinberg::kResultFalse;
			}
			else
			{
				m_ParameterInputLevelValue = savedParam1;
			}
			//
			float savedParam2 = 0.f;
			if (false == streamer.readFloat(savedParam2))
			{
				return Steinberg::kResultFalse;
			}
			else
			{
				m_ParameterThresholdlValue = savedParam2;
			}
			//
			float savedParam3 = 0.f;
			if (false == streamer.readFloat(savedParam3))
			{
				return Steinberg::kResultFalse;
			}
			else
			{
				m_ParameterColorValue = savedParam3;
			}
			//
			Steinberg::int32 savedBypass = 0;
			if (false == streamer.readInt32 (savedBypass))
			{
				return Steinberg::kResultFalse;
			}	
			else
			{
				m_BypassState = savedBypass > 0;
			}
			return Steinberg::kResultOk;
		}
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterProcessor::getState (Steinberg::IBStream* state)
		{
			// here we need to save the model (preset or project)
			//
			Steinberg::IBStreamer streamer 
			(
				state, 
				kLittleEndian
			);
			//
			streamer.writeFloat
			(
					static_cast<float> (m_ParameterInputLevelValue)
					);
			//
			streamer.writeFloat
			(
				static_cast<float> (m_ParameterThresholdlValue)
			);
			//
			streamer.writeFloat
			(
				static_cast<float> (m_ParameterColorValue)
			);
			//
			Steinberg::int32 toSaveBypass = m_BypassState ? 1 : 0;
			streamer.writeInt32 
			(
				toSaveBypass
			);
			//
			return Steinberg::kResultOk;
		}
		//------------------------------------------------------------------------
		/*
		Steinberg::tresult PLUGIN_API MeterProcessor::sendTextMessage (const Steinberg::char8* text)
		{
			return Steinberg::kResultTrue;
		}
		 */
		//------------------------------------------------------------------------
	} // namespace Meter
} // namespace Carlsound