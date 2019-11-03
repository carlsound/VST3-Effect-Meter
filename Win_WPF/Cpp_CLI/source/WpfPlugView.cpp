//
// Created by John Carlson on 10/13/19.
//
#include "../Cpp_CLI/include/WpfPlugView.h"
//
extern void* moduleHandle;
/*
WpfPlugView::WpfPlugView()
{
	m_parentWindow = nullptr;
    //m_rect.left = 0;
    //m_rect.right = 0;
    //m_rect.top = 0;
    //m_rect.bottom = 0;
}
*/

WpfPlugView::WpfPlugView(void* controller, Steinberg::ViewRect* size = nullptr) : EditorView (static_cast<Steinberg::Vst::EditController*> (controller), size)
{

}

/** Is Platform UI Type supported
	    \param type : IDString of \ref platformUIType */
Steinberg::tresult WpfPlugView::isPlatformTypeSupported (Steinberg::FIDString type)
{
	if (strcmp(type, Steinberg::kPlatformTypeHWND) == 0)
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
Steinberg::tresult WpfPlugView::attached (void* parent, Steinberg::FIDString type)
{
    if(nullptr != type)
    {
		/*
        bool isTypeHWND = false;
        for(int i = 0; i < (sizeof(type)-2); i++)
        {
            if(type[i] == Steinberg::kPlatformTypeHWND[i])
            {
                isTypeHWND = true;
            }
            else
            {
                isTypeHWND = false;
            }
        }
        if(isTypeHWND)
	    */
		if (strcmp(type, Steinberg::kPlatformTypeHWND) == 0)
        {
			//Steinberg::ViewRect *rect = new Steinberg::ViewRect(0, 0, 800, 450);
			//this->resizeView(this, rect);
			//
			//m_parentWindow = static_cast<HWND>(parent);
			//loadChildWindow(m_parentWindow);
            //
            //int i = 0;
            //
			Steinberg::ViewRect vr(0, 0, 800, 450);
			setRect(vr);
			if (plugFrame)
				plugFrame->resizeView(this, &vr);
			//
            //return Steinberg::kResultTrue;
        }
    }
    return Steinberg::kResultFalse;
}

/** The parent window of the view is about to be destroyed.
    You have to remove all your own views from the parent window or view. */
Steinberg::tresult WpfPlugView::removed ()
{
    //m_userControl.delete();
    return Steinberg::kResultTrue;
}

/** Handling of mouse wheel. */
Steinberg::tresult WpfPlugView::onWheel (float distance)
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
Steinberg::tresult WpfPlugView::onKeyDown (Steinberg::char16 key, Steinberg::int16 keyCode, Steinberg::int16 modifiers)
{
    return Steinberg::kResultTrue;
}

/** Handling of keyboard events : Key Up.
    \param key : unicode code of key
    \param keyCode : virtual keycode for non ascii keys - see \ref VirtualKeyCodes in keycodes.h
    \param modifiers : any combination of KeyModifier - see \ref KeyModifier in keycodes.h
    \return kResultTrue if the key is handled, otherwise return kResultFalse. */
Steinberg::tresult WpfPlugView::onKeyUp (Steinberg::char16 key, Steinberg::int16 keyCode, Steinberg::int16 modifiers)
{
    return Steinberg::kResultTrue;
}

/** Returns the size of the platform representation of the view. */
Steinberg::tresult WpfPlugView::getSize (Steinberg::ViewRect* size)
{
    return Steinberg::kResultTrue;
}

/** Resizes the platform representation of the view to the given rect. Note that if the Plug-in
 *	requests a resize (IPlugFrame::resizeView ()) onSize has to be called afterward. */
Steinberg::tresult WpfPlugView::onSize (Steinberg::ViewRect* newSize)
{
    return Steinberg::kResultTrue;
}

/** Focus changed message. */
Steinberg::tresult WpfPlugView::onFocus (Steinberg::TBool state)
{
    return Steinberg::kResultTrue;
}

/** Sets IPlugFrame object to allow the Plug-in to inform the host about resizing. */
Steinberg::tresult WpfPlugView::setFrame (Steinberg::IPlugFrame* frame)
{
	//Steinberg::ViewRect *rect = new Steinberg::ViewRect(0, 0, 800, 450);
	//frame->resizeView(this, rect);
    //return Steinberg::kResultTrue;
	return EditorView::setFrame(frame);
}

/** Is view sizable by user. */
Steinberg::tresult WpfPlugView::canResize ()
{
    return Steinberg::kResultTrue;
}

/** On live resize this is called to check if the view can be resized to the given rect, if not
 *	adjust the rect to the allowed size. */
Steinberg::tresult WpfPlugView::checkSizeConstraint (Steinberg::ViewRect* rect)
{
	Steinberg::int32 rectHeight = rect->getHeight();
	Steinberg::int32 rectWidth = rect->getWidth();
	//
	const Steinberg::int32 minHeight = 450;
	const Steinberg::int32 minWidth = 800;
	//
	if ((rectHeight >= minHeight) && (rectWidth >= minWidth))
	{
		return Steinberg::kResultTrue;
	}
	else
	{
		return Steinberg::kResultFalse;
	}
}

/** Called to inform the host about the resize of a given view.
	 *	Afterwards the host has to call IPlugView::onSize (). */
/*
Steinberg::tresult WpfPlugView::resizeView(Steinberg::IPlugView* view, Steinberg::ViewRect* newSize)
{
	return view->getSize(newSize);
}
*/