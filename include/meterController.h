#pragma once
//
#include "meterControllerIncludes.h"
//
namespace Carlsound
{
	namespace Meter 
	{
	//-----------------------------------------------------------------------------
	class MeterController : public Steinberg::Vst::EditController,
		                    public Steinberg::Vst::IMidiMapping//,
		                    //public VSTGUI::VST3EditorDelegate
	{
	public:	
		OBJ_METHODS(MeterController, EditController)
		DEFINE_INTERFACES
		//DEF_INTERFACE(INoteExpressionController)
		DEF_INTERFACE(IMidiMapping)
		END_DEFINE_INTERFACES(EditController)
		REFCOUNT_METHODS(EditController)
		//------------------------------------------------------------------------
		// create function required for Plug-in factory,
		// it will be called to create new instances of this controller
		//------------------------------------------------------------------------
		static FUnknown* createInstance (void*) {
			return (Steinberg::Vst::IEditController*) new MeterController (); }
		//-----------------------------------------------------------------------------
		//---from IPluginBase--------
		Steinberg::tresult PLUGIN_API initialize (FUnknown* context) SMTG_OVERRIDE;
		//-----------------------------------------------------------------------------
		//---from EditController-----
		Steinberg::tresult PLUGIN_API setComponentState (Steinberg::IBStream* state) SMTG_OVERRIDE;
		//-----------------------------------------------------------------------------
		Steinberg::Vst::ParamValue PLUGIN_API normalizedParamToPlain(
			Steinberg::Vst::ParamID tag, 
			Steinberg::Vst::ParamValue value) SMTG_OVERRIDE;
		//-----------------------------------------------------------------------------
		Steinberg::Vst::ParamValue PLUGIN_API plainParamToNormalized(
			Steinberg::Vst::ParamID tag,
			Steinberg::Vst::ParamValue value) SMTG_OVERRIDE;
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API getParamStringByValue(
			Steinberg::Vst::ParamID tag,
			Steinberg::Vst::ParamValue valueNormalized,
			Steinberg::Vst::String128 string) SMTG_OVERRIDE;
		//-----------------------------------------------------------------------------
		//---from IMidiMapping---
		virtual Steinberg::tresult PLUGIN_API getMidiControllerAssignment(
			Steinberg::int32 busIndex,
			Steinberg::int16 channel,
			Steinberg::Vst::CtrlNumber midiControllerNumber,
			Steinberg::Vst::ParamID& id) SMTG_OVERRIDE;
		//-----------------------------------------------------------------------------
		//---from EditController-----
		//Steinberg::IPlugView* PLUGIN_API createView(const char* name) SMTG_OVERRIDE;
		//-----------------------------------------------------------------------------
		//---from ComponentBase-----
		Steinberg::tresult receiveText(const char* text) SMTG_OVERRIDE;
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API notify(Steinberg::Vst::IMessage* message)SMTG_OVERRIDE;
		//-----------------------------------------------------------------------------
		//---member variables----
		//std::shared_ptr<Steinberg::Vst::RangeParameter> m_speedRangeParameter;
		//Steinberg::Vst::String128 defaultMessageText;
		};
	} // namespace Meter
} // namespace Carlsound
