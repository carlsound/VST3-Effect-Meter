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
			static FUnknown* createInstance(void*) {
				return (Steinberg::Vst::IAudioProcessor*) new MeterProcessor(); }
			//------------------------------------------------------------------------
			Steinberg::tresult PLUGIN_API initialize (FUnknown* context) SMTG_OVERRIDE;
			//------------------------------------------------------------------------
			Steinberg::tresult PLUGIN_API setBusArrangements (
				Steinberg::Vst::SpeakerArrangement* inputs,
				Steinberg::int32 numIns,
				Steinberg::Vst::SpeakerArrangement* outputs,
				Steinberg::int32 numOuts) SMTG_OVERRIDE;
			//------------------------------------------------------------------------
			Steinberg::tresult PLUGIN_API setActive (Steinberg::TBool state) SMTG_OVERRIDE;
			//------------------------------------------------------------------------
			template <class T> void bufferSampleGain(
				T inBuffer,
				T outBuffer,
				const int sampleLocation);
			//------------------------------------------------------------------------
			Steinberg::tresult PLUGIN_API processInputParameters (Steinberg::Vst::ProcessData& data);
			Steinberg::tresult PLUGIN_API processAudio (Steinberg::Vst::ProcessData& data);
			Steinberg::tresult PLUGIN_API processOutputParameters (Steinberg::Vst::ProcessData& data);
			Steinberg::tresult PLUGIN_API processMidiOutputEvents (Steinberg::Vst::ProcessData& data);
			Steinberg::tresult PLUGIN_API process (Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
			//------------------------------------------------------------------------
			Steinberg::tresult PLUGIN_API setState (Steinberg::IBStream* state) SMTG_OVERRIDE;
			//------------------------------------------------------------------------
			Steinberg::tresult PLUGIN_API getState (Steinberg::IBStream* state) SMTG_OVERRIDE;
			//------------------------------------------------------------------------
			//---from IVstMessage-----
			Steinberg::tresult PLUGIN_API connect (IConnectionPoint* other) SMTG_OVERRIDE;
			Steinberg::tresult PLUGIN_API notify (Steinberg::Vst::IMessage* message) SMTG_OVERRIDE;
			//------------------------------------------------------------------------
			//---from ComponentBase-----
			Steinberg::tresult receiveText(const char* text)SMTG_OVERRIDE;
			//------------------------------------------------------------------------
		protected:
			bool mBypassState = false;
			//
			double mGainValue[2]{ 0.0, 0.0 };
			//
			Steinberg::Vst::ParamValue mParamLevelValue = 0.0;
			Steinberg::int32 mOutputParameterChangesDataIndex = 0;
			Steinberg::int32 mOutputParameterValueQueuePointIndex = 0;
			Steinberg::Vst::IParamValueQueue *mOutputParamValueQueue = 0;
			//
			Steinberg::Vst::Event mEvent[8]{ 0 };
		};
		//------------------------------------------------------------------------
	} // namespace Meter
} // namespace Carlsound
