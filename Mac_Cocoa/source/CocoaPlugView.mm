//
// Created by John Carlson on 10/13/19.
//

#include "../include/cocoaPlugView.h"
#include <string.h>

CocoaPlugView::CocoaPlugView()
{
    //m_rect.left = 0;
    //m_rect.right = 0;
    //m_rect.top = 0;
    //m_rect.bottom = 0;
    //
    //m_view = [[meterView alloc] initWithFrame: NSMakeRect(0, 0, 480, 272)];
    //m_viewController = [[meterViewController alloc] initWithNibName: @"meterViewController" bundle: [NSBundle mainBundle /* bundleWithPath:@"net.carlsound.VST3-Effect-Meter" */]];
}

/** Is Platform UI Type supported
	    \param type : IDString of \ref platformUIType */
Steinberg::tresult CocoaPlugView::isPlatformTypeSupported (Steinberg::FIDString type)
{
    if(Steinberg::kPlatformTypeNSView == type)
    {
        return Steinberg::kResultTrue;
    }
    else
    {
        return Steinberg::kResultFalse;
    }
}

/** The parent window of the view has been created, the (platform) representation of the view
    should now be created as well.
    Note that the parent is owned by the caller and you are not allowed to alter it in any way
    other than adding your own views.
    Note that in this call the Plug-in could call a IPlugFrame::resizeView ()!
    \param parent : platform handle of the parent window or view
    \param type : \ref platformUIType which should be created */
Steinberg::tresult CocoaPlugView::attached (void* parent, Steinberg::FIDString type)
{
    if(NULL != type)
    {
        bool isTypeNSView = false;
        for(int i = 0; i < (sizeof(type)-2); i++)
        {
            if(type[i] == Steinberg::kPlatformTypeNSView[i])
            {
                isTypeNSView = true;
            }
            else
            {
                isTypeNSView = false;
            }
        }
        if(isTypeNSView)
        {
            m_parentView = static_cast<NSView*>(parent);
            //m_parentWindow = static_cast<NSWindow*>(parent); //static_cast<NSView*>(parent);
            //
            //m_view = [[meterView alloc] initWithFrame: NSMakeRect(0, 0, 480, 272)];
            m_viewController = [[meterViewController alloc] initWithNibName: @"meterViewController" bundle: [NSBundle bundleWithIdentifier:@"net.carlsound.VST3-Effect-Meter" /* nil */]];
            //
            //[m_parentView setFrameSize: m_view.frame.size];
            //m_parentView.bounds = m_view.bounds;
            [m_parentView addSubview: m_viewController.view]; //m_view];
            m_parentView.needsDisplay = YES;
            //
            //m_parentWindow.contentView = m_view;
            //m_parentWindow.viewsNeedDisplay = YES;
            //
            m_parentView.layer.backgroundColor = NSColor.yellowColor.CGColor;
            m_viewController.view.layer.backgroundColor = NSColor.blueColor.CGColor;
            //
            return Steinberg::kResultTrue;
        }
    }
    return Steinberg::kResultFalse;
}

/** The parent window of the view is about to be destroyed.
    You have to remove all your own views from the parent window or view. */
Steinberg::tresult CocoaPlugView::removed ()
{
    //[m_view removeFromSuperview];
    [m_viewController.view removeFromSuperview];
    //[m_viewController dealloc];
    //[m_parentView dealloc];
    //[m_view dealloc];
    //
    return Steinberg::kResultTrue;
}

/** Handling of mouse wheel. */
Steinberg::tresult CocoaPlugView::onWheel (float distance)
{
    return Steinberg::kResultTrue;
}

/** Handling of keyboard events : Key Down.
    \param key : unicode code of key
    \param keyCode : virtual keycode for non ascii keys - see \ref VirtualKeyCodes in keycodes.h
    \param modifiers : any combination of modifiers - see \ref KeyModifier in keycodes.h
    \return kResultTrue if the key is handled, otherwise kResultFalse. \n
            <b> Please note that kResultTrue must only be returned if the key has really been
   handled. </b> Otherwise key command handling of the host might be blocked! */
Steinberg::tresult CocoaPlugView::onKeyDown (Steinberg::char16 key, Steinberg::int16 keyCode, Steinberg::int16 modifiers)
{
    return Steinberg::kResultTrue;
}

/** Handling of keyboard events : Key Up.
    \param key : unicode code of key
    \param keyCode : virtual keycode for non ascii keys - see \ref VirtualKeyCodes in keycodes.h
    \param modifiers : any combination of KeyModifier - see \ref KeyModifier in keycodes.h
    \return kResultTrue if the key is handled, otherwise return kResultFalse. */
Steinberg::tresult CocoaPlugView::onKeyUp (Steinberg::char16 key, Steinberg::int16 keyCode, Steinberg::int16 modifiers)
{
    return Steinberg::kResultTrue;
}

/** Returns the size of the platform representation of the view. */
Steinberg::tresult CocoaPlugView::getSize (Steinberg::ViewRect* size)
{
    return Steinberg::kResultTrue;
}

/** Resizes the platform representation of the view to the given rect. Note that if the Plug-in
 *	requests a resize (IPlugFrame::resizeView ()) onSize has to be called afterward. */
Steinberg::tresult CocoaPlugView::onSize (Steinberg::ViewRect* newSize)
{
    return Steinberg::kResultTrue;
}

/** Focus changed message. */
Steinberg::tresult CocoaPlugView::onFocus (Steinberg::TBool state)
{
    return Steinberg::kResultTrue;
}

/** Sets IPlugFrame object to allow the Plug-in to inform the host about resizing. */
Steinberg::tresult CocoaPlugView::setFrame (Steinberg::IPlugFrame* frame)
{
    return Steinberg::kResultTrue;
}

/** Is view sizable by user. */
Steinberg::tresult CocoaPlugView::canResize ()
{
    return Steinberg::kResultTrue;
}

/** On live resize this is called to check if the view can be resized to the given rect, if not
 *	adjust the rect to the allowed size. */
Steinberg::tresult CocoaPlugView::checkSizeConstraint (Steinberg::ViewRect* rect)
{
    return Steinberg::kResultTrue;
}
