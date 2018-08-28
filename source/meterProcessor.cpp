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
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterProcessor::initialize 
		(
			FUnknown* context
		)
		{
			//---always initialize the parent-------
			Steinberg::tresult result = AudioEffect::initialize (context);
			if (result != Steinberg::kResultTrue)
			return Steinberg::kResultFalse;
			//---create Audio In/Out buses------
			// we want a stereo Input and a Stereo Output
			addAudioInput (STR16 ("AudioInput"), Steinberg::Vst::SpeakerArr::kStereo);
			addAudioOutput (STR16 ("AudioOutput"), Steinberg::Vst::SpeakerArr::kStereo);
			//
			/*
			m_speedRangeParameter = std::make_shared<Steinberg::Vst::RangeParameter>
			(
				STR16("Speed"), // title
				MeterParams::kParamSpeedId, // ParamID
				STR16("sec"), // units
				0.1, // minPlain
				10.0, // maxPlain
				1.0, // defaultValuePlain
				99, // stepCount
				Steinberg::Vst::ParameterInfo::kCanAutomate, // flags
				0, // unitID
				STR16("Speed") // shortTitle
			); 
			*/
			return Steinberg::kResultTrue;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterProcessor::setBusArrangements 
		(
			Steinberg::Vst::SpeakerArrangement* inputs,
            Steinberg::int32 numIns,
            Steinberg::Vst::SpeakerArrangement* outputs,
            Steinberg::int32 numOuts
		)
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
		inline void Carlsound::Meter::MeterProcessor::bufferSampleGain
		(
			T inBuffer, 
			T outBuffer, 
			const int sampleLocation
		)
		{
			inBuffer = inBuffer + sampleLocation;  // pointer arithmetic
			outBuffer = outBuffer + sampleLocation; // pointer arithmetic
			//
			*outBuffer = *inBuffer * gainValue;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterProcessor::processInputParameters
		(
			Steinberg::Vst::ProcessData& data
		)
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

						case MeterParameters::kParamLevel:
						{
							if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
								Steinberg::kResultTrue)
							{
								//m_speedNormalizedValue = value;
								break;
							}
						}

						case MeterParameters::kParamBypassId:
						{
							if (paramQueue->getPoint
							(
								numPoints - 1,
								sampleOffset,
								value
							) ==
								Steinberg::kResultTrue)
							{
								m_bypassState = (value > 0.5f);
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
		Steinberg::tresult PLUGIN_API MeterProcessor::processAudio
		(
			Steinberg::Vst::ProcessData& data
		)
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
							memset(out[i], 0, sampleFramesSize);
						}
					}
					// nothing to do at this point
					return Steinberg::kResultOk;
				}
				// mark our outputs has not silent
				data.outputs[0].silenceFlags = 0;
				//
				if (!m_bypassState)
				{
					m_gainValue[0] = 1.0;
					m_gainValue[1] = 1.0;
					for (int sample = 0; sample < data.numSamples; sample++)
					{
						for (int channel = 0; channel < data.outputs->numChannels; channel++)
						{
							if (data.symbolicSampleSize == Steinberg::Vst::kSample32) //32-Bit
							{
								bufferSampleGain
								(
									static_cast<Steinberg::Vst::Sample32*>(in[channel]),
									static_cast<Steinberg::Vst::Sample32*>(out[channel]),
									sample
								);
							}
							else // 64-Bit
							{
								bufferSampleGain
								(
									static_cast<Steinberg::Vst::Sample64*>(in[channel]),
									static_cast<Steinberg::Vst::Sample64*>(out[channel]),
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
		Steinberg::tresult PLUGIN_API MeterProcessor::processOutputParameters
		(
			Steinberg::Vst::ProcessData& data
		)
		{
			// Write outputs parameter changes-----------
			Steinberg::Vst::IParameterChanges* outParamChanges = data.outputParameterChanges;
			Steinberg::int32 Id = outParamChanges->getParameterCount() + 1; //
			outParamChanges->addParameterData(kParamLevel, Id);
			//
			return Steinberg::kResultTrue;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterProcessor::process
		(
			Steinberg::Vst::ProcessData& data
		)
		{
			processInputParameters(data);
			processAudio(data);
			processOutputParameters(data);
			//
			return Steinberg::kResultOk;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterProcessor::setState 
		(
			Steinberg::IBStream* state
		)
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
			if (streamer.readFloat(savedParam1) == false)
			{
				return Steinberg::kResultFalse;
			}
			Steinberg::int32 savedBypass = 0;
			if (streamer.readInt32 (savedBypass) == false)
			{
				return Steinberg::kResultFalse;
			}	
			//m_speedNormalizedValue = savedParam1;
			m_bypassState = savedBypass > 0;
			//
			return Steinberg::kResultOk;
		}
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API MeterProcessor::getState 
		(
			Steinberg::IBStream* state
		)
		{
			// here we need to save the model (preset or project)
			//
			//float toSaveParam1 = m_speedNormalizedValue;
			Steinberg::int32 toSaveBypass = m_bypassState ? 1 : 0;
			//
			Steinberg::IBStreamer streamer 
			(
				state, 
				kLittleEndian
			);
			/*
			streamer.writeFloat 
			(
				toSaveParam1
			);
			*/
			streamer.writeInt32 
			(
				toSaveBypass
			);
			//
			return Steinberg::kResultOk;
		}
		//------------------------------------------------------------------------
	} // namespace Meter
} // namespace Carlsound