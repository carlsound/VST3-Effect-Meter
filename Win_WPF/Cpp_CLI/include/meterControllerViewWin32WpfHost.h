// https://weblogs.thinktecture.com/cnagel/2010/04/mfc-and-wpf-interop.html
// https://www.abhishekshukla.com/wpf/advanced-wpf-part-5-of-5-interop-in-windows-presentation-foundation/
// https://stackoverflow.com/questions/1373100/how-to-add-folder-to-assembly-search-path-at-runtime-in-net
// https://docs.microsoft.com/en-us/cpp/dotnet/auto-gcroot-class?view=vs-2019
// http://forums.codeguru.com/showthread.php?364152-use-CreateInstance(__uuidof(-))
//
// public.sdk/source/common/pluginview.h
//
#pragma once
//#include "../../../Cpp/include/stdafx.h"
#include "meterControllerViewWin32WpfHostIncludes.h"
//
//
using namespace Meter_WPF_UI_CS_XAML_AnyCPU;
//
//
namespace Carlsound
{
	namespace Meter
	{
		class MeterControllerViewWin32WpfHost : public Steinberg::CPluginView //Vst::EditorView,
				   //public Steinberg::FObject //,
				   //public Steinberg::IPlugFrame
		{
		public:
			//------------------------------------------------------------------------
			//---Interface------
			//OBJ_METHODS(WpfPlugView, Steinberg::FObject)
				//DEFINE_INTERFACES
					//DEF_INTERFACE(Steinberg::IPlugView)
					//DEF_INTERFACE(Steinberg::IPlugFrame)
				//END_DEFINE_INTERFACES(Steinberg::Vst::EditorView)
			//REFCOUNT_METHODS(Steinberg::Vst::EditorViewS)
			//
			MeterControllerViewWin32WpfHost();
			MeterControllerViewWin32WpfHost(const Steinberg::ViewRect* rect);
			~MeterControllerViewWin32WpfHost();

			//------------------------------------------------------------------------
			//---from CPluginView-------
					/** Returns its current frame rectangle. */
			const Steinberg::ViewRect& getRect() const;

			/** Sets a new frame rectangle. */
			void setRect(const Steinberg::ViewRect& r);

			/** Checks if this view is attached to its parent view. */
			bool isAttached() const;

			/** Calls when this view will be attached to its parent view. */
			void attachedToParent() SMTG_OVERRIDE;

			/** Calls when this view will be removed from its parent view. */
			void removedFromParent() SMTG_OVERRIDE;

			//------------------------------------------------------------------------
			//---from IPlugView-------
			/** Is Platform UI Type supported
				\param type : IDString of \ref platformUIType */
			Steinberg::tresult PLUGIN_API isPlatformTypeSupported(Steinberg::FIDString type) SMTG_OVERRIDE;

			/** The parent window of the view has been created, the (platform) representation of the view
				should now be created as well.
				Note that the parent is owned by the caller and you are not allowed to alter it in any way
				other than adding your own views.
				Note that in this call the Plug-in could call a IPlugFrame::resizeView ()!
				\param parent : platform handle of the parent window or view
				\param type : \ref platformUIType which should be created */
			Steinberg::tresult PLUGIN_API attached(void* parent, Steinberg::FIDString type) SMTG_OVERRIDE;

			/** The parent window of the view is about to be destroyed.
				You have to remove all your own views from the parent window or view. */
			Steinberg::tresult PLUGIN_API removed() SMTG_OVERRIDE;

			/** Handling of mouse wheel. */
			Steinberg::tresult PLUGIN_API onWheel(float distance) SMTG_OVERRIDE;

			/** Handling of keyboard events : Key Down.
				\param key : unicode code of key
				\param keyCode : virtual keycode for non ascii keys - see \ref VirtualKeyCodes in keycodes.h
				\param modifiers : any combination of modifiers - see \ref KeyModifier in keycodes.h
				\return kResultTrue if the key is handled, otherwise kResultFalse. \n
						<b> Please note that kResultTrue must only be returned if the key has really been
			   handled. </b> Otherwise key command handling of the host might be blocked! */
			Steinberg::tresult PLUGIN_API onKeyDown(Steinberg::char16 key, Steinberg::int16 keyCode, Steinberg::int16 modifiers) SMTG_OVERRIDE;

			/** Handling of keyboard events : Key Up.
				\param key : unicode code of key
				\param keyCode : virtual keycode for non ascii keys - see \ref VirtualKeyCodes in keycodes.h
				\param modifiers : any combination of KeyModifier - see \ref KeyModifier in keycodes.h
				\return kResultTrue if the key is handled, otherwise return kResultFalse. */
			Steinberg::tresult PLUGIN_API onKeyUp(Steinberg::char16 key, Steinberg::int16 keyCode, Steinberg::int16 modifiers) SMTG_OVERRIDE;

			/** Returns the size of the platform representation of the view. */
			Steinberg::tresult PLUGIN_API getSize(Steinberg::ViewRect* size) SMTG_OVERRIDE;

			/** Resizes the platform representation of the view to the given rect. Note that if the Plug-in
			 *	requests a resize (IPlugFrame::resizeView ()) onSize has to be called afterward. */
			Steinberg::tresult PLUGIN_API onSize(Steinberg::ViewRect* newSize) SMTG_OVERRIDE;

			/** Focus changed message. */
			Steinberg::tresult PLUGIN_API onFocus(Steinberg::TBool state) SMTG_OVERRIDE;

			/** Sets IPlugFrame object to allow the Plug-in to inform the host about resizing. */
			Steinberg::tresult PLUGIN_API setFrame(Steinberg::IPlugFrame* frame) SMTG_OVERRIDE;

			/** Is view sizable by user. */
			Steinberg::tresult PLUGIN_API canResize() SMTG_OVERRIDE;

			/** On live resize this is called to check if the view can be resized to the given rect, if not
			 *	adjust the rect to the allowed size. */
			Steinberg::tresult PLUGIN_API checkSizeConstraint(Steinberg::ViewRect* rect) SMTG_OVERRIDE;
			
			//------------------------------------------------------------------------
			// Plug-In Specific
			Steinberg::tresult PLUGIN_API setInputLevelFeedback(Steinberg::Vst::ParamValue newLevel);

		protected:
			Steinberg::ViewRect m_rect;
			void* m_systemWindow;
			Steinberg::IPlugFrame* m_plugFrame;
			//
			//Steinberg::Vst::ParamValue m_inputLevelFeedback;
			//
			//HWND m_parentWindow;
			//
			//MeterUserControl ^m_meterUserControl;
			//msclr::auto_gcroot<MeterUserControl^> m_UIptr;
			IMeterControllerViewUserControlPtr m_UIptr;
			HRESULT m_hr;
		};
	} // namespace Meter
} // namespace Carlsound