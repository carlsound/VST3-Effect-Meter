// https://www.youtube.com/watch?v=Ms5hhdRFRvc
//
// Created by John Carlson on 10/13/19.
//

// public.sdk/source/common/pluginview.h
//
#pragma once
//
#include "base/source/fobject.h"
//
#include "pluginterfaces/gui/iplugview.h"
//
#include "meterView.h"
#include "meterViewController.h"
//
class CocoaPlugView: public Steinberg::FObject,
                     public Steinberg::IPlugView
{
public:
    CocoaPlugView ();
    //~CocoaPlugView ();
    
    //---from IPlugView-------
    /** Is Platform UI Type supported
	    \param type : IDString of \ref platformUIType */
    Steinberg::tresult PLUGIN_API isPlatformTypeSupported (Steinberg::FIDString type) SMTG_OVERRIDE;

    /** The parent window of the view has been created, the (platform) representation of the view
        should now be created as well.
        Note that the parent is owned by the caller and you are not allowed to alter it in any way
        other than adding your own views.
        Note that in this call the Plug-in could call a IPlugFrame::resizeView ()!
        \param parent : platform handle of the parent window or view
        \param type : \ref platformUIType which should be created */
    Steinberg::tresult PLUGIN_API attached (void* parent, Steinberg::FIDString type) SMTG_OVERRIDE;

    /** The parent window of the view is about to be destroyed.
        You have to remove all your own views from the parent window or view. */
    Steinberg::tresult PLUGIN_API removed () SMTG_OVERRIDE;

    /** Handling of mouse wheel. */
    Steinberg::tresult PLUGIN_API onWheel (float distance) SMTG_OVERRIDE;

    /** Handling of keyboard events : Key Down.
        \param key : unicode code of key
        \param keyCode : virtual keycode for non ascii keys - see \ref VirtualKeyCodes in keycodes.h
        \param modifiers : any combination of modifiers - see \ref KeyModifier in keycodes.h
        \return kResultTrue if the key is handled, otherwise kResultFalse. \n
                <b> Please note that kResultTrue must only be returned if the key has really been
       handled. </b> Otherwise key command handling of the host might be blocked! */
    Steinberg::tresult PLUGIN_API onKeyDown (Steinberg::char16 key, Steinberg::int16 keyCode, Steinberg::int16 modifiers) SMTG_OVERRIDE;

    /** Handling of keyboard events : Key Up.
        \param key : unicode code of key
        \param keyCode : virtual keycode for non ascii keys - see \ref VirtualKeyCodes in keycodes.h
        \param modifiers : any combination of KeyModifier - see \ref KeyModifier in keycodes.h
        \return kResultTrue if the key is handled, otherwise return kResultFalse. */
    Steinberg::tresult PLUGIN_API onKeyUp (Steinberg::char16 key, Steinberg::int16 keyCode, Steinberg::int16 modifiers) SMTG_OVERRIDE;

    /** Returns the size of the platform representation of the view. */
    Steinberg::tresult PLUGIN_API getSize (Steinberg::ViewRect* size) SMTG_OVERRIDE;

    /** Resizes the platform representation of the view to the given rect. Note that if the Plug-in
     *	requests a resize (IPlugFrame::resizeView ()) onSize has to be called afterward. */
    Steinberg::tresult PLUGIN_API onSize (Steinberg::ViewRect* newSize) SMTG_OVERRIDE;

    /** Focus changed message. */
    Steinberg::tresult PLUGIN_API onFocus (Steinberg::TBool state) SMTG_OVERRIDE;

    /** Sets IPlugFrame object to allow the Plug-in to inform the host about resizing. */
    Steinberg::tresult PLUGIN_API setFrame (Steinberg::IPlugFrame* frame) SMTG_OVERRIDE;

    /** Is view sizable by user. */
    Steinberg::tresult PLUGIN_API canResize () SMTG_OVERRIDE;

    /** On live resize this is called to check if the view can be resized to the given rect, if not
     *	adjust the rect to the allowed size. */
    Steinberg::tresult PLUGIN_API checkSizeConstraint (Steinberg::ViewRect* rect) SMTG_OVERRIDE;
    //
    //---Interface------
    OBJ_METHODS (CocoaPlugView, Steinberg::FObject)
    DEFINE_INTERFACES
        DEF_INTERFACE (Steinberg::IPlugView)
    END_DEFINE_INTERFACES (Steinberg::FObject)
    REFCOUNT_METHODS(Steinberg::FObject)
    //
protected:
    Steinberg::ViewRect m_rect;
    void* systemWindow;
    Steinberg::IPlugFrame* plugFrame;
    //
    NSView *m_parentView;
    //NSWindow* m_parentWindow;
    meterView* m_view;
    meterViewController *m_viewController;
};
