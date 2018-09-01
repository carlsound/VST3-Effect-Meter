//------------------------------------------------------------------------
#pragma once
//
#include "public.sdk/source/vst/vstaudioeffect.h"
//
#include "meterController.h"
#include "meterParameters.h"
#include "meterUIDs.h"
//
#include <public.sdk/source/vst/vstparameters.h>
//
#include "base/source/fstreamer.h"
#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "pluginterfaces/vst/vsttypes.h"
#include "public.sdk/source/vst/vstaudioprocessoralgo.h"
//
#define _USE_MATH_DEFINES 
#include <cmath>
//
//
namespace Carlsound
{
	namespace Meter 
	{
		//-----------------------------------------------------------------------------
		class MeterProcessor : public Steinberg::Vst::AudioEffect
		{
		public:
		MeterProcessor ();
		//
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API initialize 
		(
			FUnknown* context
		) 
			SMTG_OVERRIDE;
		//
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API setBusArrangements 
		(
			Steinberg::Vst::SpeakerArrangement* inputs,
			Steinberg::int32 numIns,
			Steinberg::Vst::SpeakerArrangement* outputs,
			Steinberg::int32 numOuts
		) 
			SMTG_OVERRIDE;
		//
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API setActive 
		(
			Steinberg::TBool state
		) 
			SMTG_OVERRIDE;
		//
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API process 
		(
			Steinberg::Vst::ProcessData& data
		) 
			SMTG_OVERRIDE;
		//
		Steinberg::tresult PLUGIN_API processInputParameters
		(
			Steinberg::Vst::ProcessData& data
		);
		//
		Steinberg::tresult PLUGIN_API processAudio
		(
			Steinberg::Vst::ProcessData& data
		);
		//
		
		Steinberg::tresult PLUGIN_API processOutputParameters
		(
			Steinberg::Vst::ProcessData& data
		);
		
		//
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API setState 
		(
			Steinberg::IBStream* state
		) 
			SMTG_OVERRIDE;
		//
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API getState 
		(
			Steinberg::IBStream* state
		) 
			SMTG_OVERRIDE;
		//
		//------------------------------------------------------------------------
		static FUnknown* createInstance (void*)
		{
			return (Steinberg::Vst::IAudioProcessor*)new MeterProcessor ();
		}
		//
		//------------------------------------------------------------------------
		template <class T> void bufferSampleGain
		(
			T inBuffer, 
			T outBuffer, 
			const int sampleLocation
		);
		//
		protected:
		bool m_bypassState = false;
		//
		double m_gainValue[2]
		{ 
			0.0, 
			0.0 
		};
		//
		Steinberg::Vst::ParamValue mParamLevelValue = 0.0;
		Steinberg::int32 mOutputParameterChangesDataIndex = 0;
		Steinberg::int32 mOutputParameterValueQueuePointIndex = 0;
		Steinberg::Vst::IParamValueQueue *mOutputParamValueQueue = 0;
		};
		//------------------------------------------------------------------------
	} // namespace Meter
} // namespace Carlsound
