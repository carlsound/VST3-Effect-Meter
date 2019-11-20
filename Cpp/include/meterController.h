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
		//
		Steinberg::tresult PLUGIN_API setParamNormalized(Steinberg::Vst::ParamID tag, 
			                                             Steinberg::Vst::ParamValue value) SMTG_OVERRIDE;
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
		Steinberg::IPlugView* PLUGIN_API createView(const char* name) SMTG_OVERRIDE;
		//
		/*
		Steinberg::tresult PLUGIN_API performEdit(Steinberg::Vst::ParamID tag, 
			                                      Steinberg::Vst::ParamValue valueNormalized);
		*/
		//
		//-----------------------------------------------------------------------------
		//---from IConnectionPoint-----
		//Steinberg::tresult PLUGIN_API connect (IConnectionPoint* other) SMTG_OVERRIDE;
		//Steinberg::tresult PLUGIN_API notify(Steinberg::Vst::IMessage* message) SMTG_OVERRIDE;
		//------------------------------------------------------------------------
		//---from ComponentBase-----
		//Steinberg::tresult PLUGIN_API receiveText(const char* text) SMTG_OVERRIDE;
		//Steinberg::tresult sendMessage(Steinberg::Vst::IMessage* message);
		//-----------------------------------------------------------------------------
		//---member variables----
		//std::shared_ptr<Steinberg::Vst::RangeParameter> m_speedRangeParameter;
		Steinberg::Vst::ParamValue m_LevelInput;
		Steinberg::Vst::ParamValue m_LevelThreshold;
		Steinberg::Vst::ParamValue m_LevelColor;
        //
		//Steinberg::Vst::String128 defaultMessageText;
		//std::shared_ptr<Steinberg::Vst::IConnectionPoint> m_ConnectionPoint;
		//std::shared_ptr<Carlsound::Vst::ComponentMessage> m_Message;
		//Carlsound::Vst::ComponentMessage *m_Message;
		//Carlsound::Vst::ComponentAttribute *m_Attribute;
		//Carlsound::Vst::ComponentAttributeList *m_AttributeList;
		//
		//VSTGUI::CFrame *m_GuiFrame;
		//VSTGUI::CView *m_GuiView_InputLevel_VuMeter;
		//VSTGUI::CView *m_GuiView_InputLevel_TextLabel;
		//VSTGUI::CVuMeter *m_GuiVuMeter_InputLevel;
		//VSTGUI::CTextLabel* m_GuiTextLabel_InputLevel;
		//
		Steinberg::IPlugView* m_view;
		};
	} // namespace Meter
} // namespace Carlsound
