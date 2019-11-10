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
namespace Carlsound
{
	namespace Meter
	{
		//------------------------------------------------------------------------
		WpfPlugView::WpfPlugView() :
			m_rect(0, 0, 800, 450),
			m_systemWindow(nullptr),
			m_plugFrame(nullptr)
		{

		}

		//------------------------------------------------------------------------
		WpfPlugView::WpfPlugView(const Steinberg::ViewRect* rect) : 
			m_rect(0, 0, 800, 450),
			m_systemWindow(nullptr),
			m_plugFrame(nullptr)
		{
			if (rect)
			{
				m_rect = *rect;
			}
		}

		//------------------------------------------------------------------------
		WpfPlugView:: ~WpfPlugView()
		{

		}

		//------------------------------------------------------------------------
		/** Returns its current frame rectangle. */
		const Steinberg::ViewRect& WpfPlugView::getRect() const
		{
			return m_rect;
		}

		//------------------------------------------------------------------------
		/** Sets a new frame rectangle. */
		void WpfPlugView::setRect(const Steinberg::ViewRect& r)
		{
			m_rect = r;
		}

		//------------------------------------------------------------------------
		/** Checks if this view is attached to its parent view. */
		bool WpfPlugView::isAttached() const
		{
			return m_systemWindow != nullptr;
		}

		//------------------------------------------------------------------------
		/** Calls when this view will be attached to its parent view. */
		void WpfPlugView::attachedToParent()
		{
			loadChildWindow(m_parentWindow);
		}

		//------------------------------------------------------------------------
		/** Calls when this view will be removed from its parent view. */
		void WpfPlugView::removedFromParent()
		{
			//[m_viewController.view removeFromSuperview] ;
		}

		//------------------------------------------------------------------------
		/** Is Platform UI Type supported
				\param type : IDString of \ref platformUIType */
		Steinberg::tresult WpfPlugView::isPlatformTypeSupported(Steinberg::FIDString type)
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

		//------------------------------------------------------------------------
		/** The parent window of the view has been created, the (platform) representation of the view
			should now be created as well.
			Note that the parent is owned by the caller and you are not allowed to alter it in any way
			other than adding your own views.
			Note that in this call the Plug-in could call a IPlugFrame::resizeView ()!
			\param parent : platform handle of the parent window or view
			\param type : \ref platformUIType which should be created */
		Steinberg::tresult WpfPlugView::attached(void* parent, Steinberg::FIDString type)
		{
			if (strcmp(type, Steinberg::kPlatformTypeHWND) == 0)
			{
				m_systemWindow = parent;
				m_parentWindow = static_cast<HWND*>(m_systemWindow);
				//
				if (m_plugFrame != nullptr)
				{
					m_plugFrame->resizeView(this, &m_rect);
				}
				//
				attachedToParent();
				return Steinberg::kResultOk;
			}
			return Steinberg::kResultFalse;
		}

		//------------------------------------------------------------------------
		/** The parent window of the view is about to be destroyed.
			You have to remove all your own views from the parent window or view. */
		Steinberg::tresult WpfPlugView::removed()
		{
			removedFromParent();
			//
			m_systemWindow = nullptr;
			//
			return Steinberg::kResultOk;
		}

		//------------------------------------------------------------------------
		/** Handling of mouse wheel. */
		Steinberg::tresult WpfPlugView::onWheel(float distance)
		{
			return Steinberg::kResultTrue;
		}

		//------------------------------------------------------------------------
		/** Handling of keyboard events : Key Down.
			\param key : unicode code of key
			\param keyCode : virtual keycode for non ascii keys - see \ref VirtualKeyCodes in keycodes.h
			\param modifiers : any combination of modifiers - see \ref KeyModifier in keycodes.h
			\return kResultTrue if the key is handled, otherwise kResultFalse. \n
					<b> Please note that kResultTrue must only be returned if the key has really been
		   handled. </b> Otherwise key command handling of the host might be blocked! */
		Steinberg::tresult WpfPlugView::onKeyDown(Steinberg::char16 key, Steinberg::int16 keyCode, Steinberg::int16 modifiers)
		{
			return Steinberg::kResultTrue;
		}

		//------------------------------------------------------------------------
		/** Handling of keyboard events : Key Up.
			\param key : unicode code of key
			\param keyCode : virtual keycode for non ascii keys - see \ref VirtualKeyCodes in keycodes.h
			\param modifiers : any combination of KeyModifier - see \ref KeyModifier in keycodes.h
			\return kResultTrue if the key is handled, otherwise return kResultFalse. */
		Steinberg::tresult WpfPlugView::onKeyUp(Steinberg::char16 key, Steinberg::int16 keyCode, Steinberg::int16 modifiers)
		{
			return Steinberg::kResultTrue;
		}

		//------------------------------------------------------------------------
		/** Returns the size of the platform representation of the view. */
		Steinberg::tresult WpfPlugView::getSize(Steinberg::ViewRect* size)
		{
			if (size)
			{
				*size = m_rect;
				return Steinberg::kResultTrue;
			}
			return Steinberg::kInvalidArgument;
		}

		//------------------------------------------------------------------------
		/** Resizes the platform representation of the view to the given rect. Note that if the Plug-in
		 *	requests a resize (IPlugFrame::resizeView ()) onSize has to be called afterward. */
		Steinberg::tresult WpfPlugView::onSize(Steinberg::ViewRect* newSize)
		{
			if ((newSize->right - newSize->left >= 800) && (newSize->bottom - newSize->top >= 450))
				m_rect = *newSize;
			return Steinberg::kResultTrue;
		}

		//------------------------------------------------------------------------
		/** Focus changed message. */
		Steinberg::tresult WpfPlugView::onFocus(Steinberg::TBool state)
		{
			return Steinberg::kResultTrue;
		}

		//------------------------------------------------------------------------
		/** Sets IPlugFrame object to allow the Plug-in to inform the host about resizing. */
		Steinberg::tresult WpfPlugView::setFrame(Steinberg::IPlugFrame* frame)
		{
			m_plugFrame = frame;
			if (m_plugFrame != nullptr)
			{
				return Steinberg::kResultTrue;
			}
			else
			{
				return Steinberg::kResultFalse;
			}
		}

		//------------------------------------------------------------------------
		/** Is view sizable by user. */
		Steinberg::tresult WpfPlugView::canResize()
		{
			return Steinberg::kResultTrue;
		}

		//------------------------------------------------------------------------
		/** On live resize this is called to check if the view can be resized to the given rect, if not
		 *	adjust the rect to the allowed size. */
		Steinberg::tresult WpfPlugView::checkSizeConstraint(Steinberg::ViewRect* rect)
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

		//------------------------------------------------------------------------
		/** Called to inform the host about the resize of a given view.
			 *	Afterwards the host has to call IPlugView::onSize (). */
			 /*
			 Steinberg::tresult WpfPlugView::resizeView(Steinberg::IPlugView* view, Steinberg::ViewRect* newSize)
			 {
				 return view->getSize(newSize);
			 }
			 */
		//
	} // namespace Meter
} // namespace Carlsound