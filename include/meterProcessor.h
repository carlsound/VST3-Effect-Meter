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
			OBJ_METHODS(MeterProcessor, AudioEffect)
				DEFINE_INTERFACES
				//DEF_INTERFACE(INoteExpressionController)
				//DEF_INTERFACE(IMidiMapping)
			END_DEFINE_INTERFACES(AudioEffect)
			REFCOUNT_METHODS(AudioEffect)
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
			//---from IConnectionPoint-----
			//Steinberg::tresult PLUGIN_API connect (IConnectionPoint* other) SMTG_OVERRIDE;
			//Steinberg::tresult PLUGIN_API notify (Steinberg::Vst::IMessage* message) SMTG_OVERRIDE;
			//------------------------------------------------------------------------
			//---from ComponentBase-----
			//Steinberg::tresult receiveText(const char* text)SMTG_OVERRIDE;
			//Steinberg::tresult sendMessage(Steinberg::Vst::IMessage* message);
			//------------------------------------------------------------------------
		protected:
			bool mBypassState = false;
			//
			double mGainValue[2]{ 0.0, 0.0 };
			//
			Steinberg::Vst::IParameterChanges* m_OutputParameterChanges = NULL;
			Steinberg::Vst::ParamValue m_ParamLevelValue = 0.0;
			Steinberg::int32 m_OutputParameterChangesDataIndex = 0;
			Steinberg::int32 m_OutputParameterValueQueuePointIndex = 0;
			Steinberg::Vst::IParamValueQueue *m_OutputParamValueQueue = 0;
			//
			Steinberg::Vst::Event mEvent[8]{ 0 };
			//
			//std::shared_ptr<Steinberg::Vst::IConnectionPoint> m_ConnectionPoint;
			//std::shared_ptr<Steinberg::Vst::IMessage> m_Message;
			Carlsound::Vst::ComponentMessage *m_Message;
			//std::shared_ptr<Steinberg::Vst::IMessage*> m_pMessage;
			Carlsound::Vst::ComponentAttribute *m_Attribute;
			Carlsound::Vst::ComponentAttributeList *m_AttributeList;
		};
		//------------------------------------------------------------------------
	} // namespace Meter
} // namespace Carlsound
