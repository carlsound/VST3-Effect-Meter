#pragma once
//
#include "meterProcessorIncludes.h"
//
namespace Carlsound
{
	namespace Meter 
	{
		//-----------------------------------------------------------------------------
		class MeterProcessor : public Steinberg::Vst::AudioEffect
		{
		public:
			//------------------------------------------------------------------------
			MeterProcessor ();
			//------------------------------------------------------------------------
			static FUnknown* createInstance(void*) { return (Steinberg::Vst::IAudioProcessor*) new MeterProcessor(); }
			//------------------------------------------------------------------------
			Steinberg::tresult PLUGIN_API initialize (FUnknown* context) SMTG_OVERRIDE;
			//------------------------------------------------------------------------
			Steinberg::tresult PLUGIN_API setBusArrangements (Steinberg::Vst::SpeakerArrangement* inputs, Steinberg::int32 numIns, Steinberg::Vst::SpeakerArrangement* outputs, Steinberg::int32 numOuts) SMTG_OVERRIDE;
			//------------------------------------------------------------------------
			Steinberg::tresult PLUGIN_API setupProcessing(Steinberg::Vst::ProcessSetup& setup) SMTG_OVERRIDE;
			//------------------------------------------------------------------------
			Steinberg::tresult PLUGIN_API setActive (Steinberg::TBool state) SMTG_OVERRIDE;
			//------------------------------------------------------------------------
			Steinberg::tresult canProcessSampleSize (Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;
			//------------------------------------------------------------------------
			template <class T> void bufferSampleGain(T inBuffer, T outBuffer, const int sampleLocation);
			//------------------------------------------------------------------------
			Steinberg::tresult PLUGIN_API process (Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
			//------------------------------------------------------------------------
			Steinberg::tresult PLUGIN_API setState (Steinberg::IBStream* state) SMTG_OVERRIDE;
			//------------------------------------------------------------------------
			Steinberg::tresult PLUGIN_API getState (Steinberg::IBStream* state) SMTG_OVERRIDE;
			//------------------------------------------------------------------------
		protected:
			bool m_BypassState = false;
			//
			Steinberg::Vst::ParamValue m_ParameterInputLevelValue = 0.0;
			Steinberg::Vst::ParamValue m_ParameterThresholdlValue = 0.0;
			Steinberg::Vst::ParamValue m_ParameterColorValue = 0.0;
			//
			Steinberg::Vst::ProcessSetup m_processSetup = {0};
			//Steinberg::int32 m_processMode = 0;
			//Steinberg::int32 m_symbolicSampleSize = 2;
			//Steinberg::int32 m_maxSamplesPerBlock = 0;
			//Steinberg::Vst::SampleRate m_sampleRate = 0;
			//
			//Steinberg::int32 m_qtyChannels = 0;
			Steinberg::int32 m_qtySamples = 0;
			Steinberg::uint32 m_sampleFramesSize;
			//
			Steinberg::Vst::AudioBusBuffers* m_inputsAudioBusBuffers;
			Steinberg::Vst::AudioBusBuffers* m_outputsAudioBusBuffers;
			//
			Steinberg::int32 m_OutputParameterChangesDataIndex = 0;
			Steinberg::int32 m_OutputParameterValueQueuePointIndex = 0;
			//
			Steinberg::Vst::IParameterChanges* m_InputParameterChanges = NULL;
			Steinberg::Vst::IParameterChanges* m_OutputParameterChanges = NULL;
			//
			Steinberg::int32 m_numParamsChanged = 0;
			Steinberg::Vst::IParamValueQueue *m_ParameterInputLevelValueQueue = 0;
			Steinberg::Vst::IParamValueQueue* m_ParameterColorValueQueue = 0;
			Steinberg::int32 m_addPointIndex = 0;
			//
            Steinberg::Vst::Event mEvent{ 0 };
		};
		//------------------------------------------------------------------------
	} // namespace Meter
} // namespace Carlsound
