//
// Created by John Carlson on 10/13/19.
//
//#include "../../../Cpp/include/stdafx.h"
#include "../include/meterControllerViewWin32WpfHost.h"
//
//extern void* moduleHandle;
//
using namespace Meter_WPF_UI_CS_XAML_AnyCPU;
//
namespace Carlsound
{
	namespace Meter
	{
		//------------------------------------------------------------------------
		//[System::STAThread]
		MeterControllerViewWin32WpfHost::MeterControllerViewWin32WpfHost() :
			m_rect(0, 0, 800, 450),
			m_systemWindow(nullptr),
			m_plugFrame(nullptr),
			//m_UIptr(gcnew MeterUserControl())
			m_hr(S_OK)
		{
			//LoadMissingDll^ loadmgr = gcnew LoadMissingDll();
			

			if (SMTG_PLATFORM_64)
			{
				//SetDllDirectoryA("C:\\Program Files\\Common Files\\VST3");
				//LoadLibraryA("C:\\Program Files\\Common Files\\VST3\\Meter_WPF_UI_CppCLI_x64.dll");
				//LoadLibraryA("C:\\Program Files\\Common Files\\VST3\\Meter_WPF_UI_CS_XAML_x64.dll");
				//System::Reflection::Assembly::LoadFile("C:\\Program Files\\Common Files\\VST3\\Meter_WPF_UI_CS_XAML_AnyCPU.dll");
			}
			else
			{
				//SetDllDirectoryA("C:\\Program Files (x86)\\Common Files\\VST3");
				//LoadLibraryA("C:\\Program Files (x86)\\Common Files\\VST3\\Meter_WPF_UI_CppCLI_x86.dll");
				//LoadLibraryA("C:\\Program Files (x86)\\Common Files\\VST3\\Meter_WPF_UI_CS_XAML_x86.dll");
				//System::Reflection::Assembly::LoadFile("C:\\Program Files (x86)\\Common Files\\VST3\\Meter_WPF_UI_CS_XAML_AnyCPU.dll");
			}

			m_hr = CoInitialize(NULL);
			m_hr = m_UIptr.CreateInstance(__uuidof(Meter_WPF_UI_CS_XAML_AnyCPU::MeterUserControl), NULL, CLSCTX_ALL);
			int i = 0;
		}

		//------------------------------------------------------------------------
		//[System::STAThread]
		MeterControllerViewWin32WpfHost::MeterControllerViewWin32WpfHost(const Steinberg::ViewRect* rect) :
			m_rect(0, 0, 800, 450),
			m_systemWindow(nullptr),
			m_plugFrame(nullptr),
			//m_UIptr(gcnew MeterUserControl())
			m_hr(S_OK)
		{
			if (rect)
			{
				m_rect = *rect;
			}
			//LoadMissingDll^ loadmgr = gcnew LoadMissingDll();
			
			m_hr = CoInitialize(NULL);
			m_hr = m_UIptr.CreateInstance(__uuidof(Meter_WPF_UI_CS_XAML_AnyCPU::MeterUserControl), NULL, CLSCTX_ALL);
			int i = 0;
		}

		//------------------------------------------------------------------------
		MeterControllerViewWin32WpfHost::~MeterControllerViewWin32WpfHost()
		{
			//m_UIptr.~_com_ptr_t();
		}

		//------------------------------------------------------------------------
		/** Returns its current frame rectangle. */
		const Steinberg::ViewRect& MeterControllerViewWin32WpfHost::getRect() const
		{
			return m_rect;
		}

		//------------------------------------------------------------------------
		/** Sets a new frame rectangle. */
		void MeterControllerViewWin32WpfHost::setRect(const Steinberg::ViewRect& r)
		{
			m_rect = r;
		}

		//------------------------------------------------------------------------
		/** Checks if this view is attached to its parent view. */
		bool MeterControllerViewWin32WpfHost::isAttached() const
		{
			return m_systemWindow != nullptr;
		}

		//------------------------------------------------------------------------
		/** Calls when this view will be attached to its parent view. */
		void MeterControllerViewWin32WpfHost::attachedToParent()
		{
			// Create the window.

			//m_UIptr->show((long)m_systemWindow);

			//m_rect(0, 0, m_UIptr->, m_UIptr->);
			//
			/*
			if (m_plugFrame != nullptr)
			{
				m_plugFrame->resizeView((Steinberg::IPlugView*)this, &m_rect);
			}
			*/

			/*
			MeterUserControl ^m_userControl = gcnew MeterUserControl(); 
			
			System::Windows::Interop::HwndSourceParameters^ sourceParams = gcnew System::Windows::Interop::HwndSourceParameters("Meter");
			sourceParams->PositionX = 0;
			sourceParams->PositionY = 0;
			sourceParams->Height = m_rect.getHeight(); //m_userControl->Height;
			sourceParams->Width = m_rect.getWidth(); // m_userControl->Width;
			sourceParams->ParentWindow = System::IntPtr(m_systemWindow);
			sourceParams->WindowStyle = WS_VISIBLE | WS_CHILD;
			//
			System::Windows::Interop::HwndSource^ m_hwndSource = gcnew System::Windows::Interop::HwndSource(*sourceParams);
			//
			m_hwndSource->RootVisual = m_userControl;
			*/

			//const wchar_t CLASS_NAME[] = L"Sample Window Class";

			/*
			HWND hwnd = CreateWindowEx(
				0,                              // Optional window styles.
				TEXT("ComboBox"),                     // Window class
				TEXT("Learn to Program Windows"),    // Window text
				WS_VISIBLE | WS_CHILD, //WS_OVERLAPPEDWINDOW,            // Window style

				// Size and position
				0, 0, 100, 100,

				static_cast<HWND>(m_systemWindow),       // Parent window    
				NULL,       // Menu
				NULL,  // Instance handle
				NULL        // Additional application data
			);
			*/

			/*
			HWND hwndButton = CreateWindowEx(
				0,						// Optional window styles.
				TEXT("Button"),			// lpClassName,
				TEXT("Meter x64"),			// lpWindowName,
				WS_VISIBLE | WS_CHILD,	// dwStyle,
				200,						// X,
				200,						// Y,
				100,					// nWidth,
				100,					// nHeight,
				static_cast<HWND>(m_systemWindow),      // hWndParent,
				nullptr,				// hMenu,
				nullptr,				// hInstance,
				nullptr					// lpParam
			);
			*/
		}

		//------------------------------------------------------------------------
		/** Calls when this view will be removed from its parent view. */
		void MeterControllerViewWin32WpfHost::removedFromParent()
		{
			//m_UIptr->hide();
			//
			m_systemWindow = nullptr;
		}

		//------------------------------------------------------------------------
		/** Is Platform UI Type supported
				\param type : IDString of \ref platformUIType */
		Steinberg::tresult MeterControllerViewWin32WpfHost::isPlatformTypeSupported(Steinberg::FIDString type)
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
		Steinberg::tresult MeterControllerViewWin32WpfHost::attached(void* parent, Steinberg::FIDString type)
		{
			if (strcmp(type, Steinberg::kPlatformTypeHWND) == 0)
			{
				m_systemWindow = parent;
				//
				if (m_plugFrame != nullptr)
				{
					m_plugFrame->resizeView((Steinberg::IPlugView*)this, &m_rect);
				}
				//
				attachedToParent();
				//
				return Steinberg::kResultOk;
			}
			return Steinberg::kResultFalse;
		}

		//------------------------------------------------------------------------
		/** The parent window of the view is about to be destroyed.
			You have to remove all your own views from the parent window or view. */
		Steinberg::tresult MeterControllerViewWin32WpfHost::removed()
		{
			removedFromParent();
			//
			return Steinberg::kResultOk;
		}

		//------------------------------------------------------------------------
		/** Handling of mouse wheel. */
		Steinberg::tresult MeterControllerViewWin32WpfHost::onWheel(float distance)
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
		Steinberg::tresult MeterControllerViewWin32WpfHost::onKeyDown(Steinberg::char16 key, Steinberg::int16 keyCode, Steinberg::int16 modifiers)
		{
			return Steinberg::kResultTrue;
		}

		//------------------------------------------------------------------------
		/** Handling of keyboard events : Key Up.
			\param key : unicode code of key
			\param keyCode : virtual keycode for non ascii keys - see \ref VirtualKeyCodes in keycodes.h
			\param modifiers : any combination of KeyModifier - see \ref KeyModifier in keycodes.h
			\return kResultTrue if the key is handled, otherwise return kResultFalse. */
		Steinberg::tresult MeterControllerViewWin32WpfHost::onKeyUp(Steinberg::char16 key, Steinberg::int16 keyCode, Steinberg::int16 modifiers)
		{
			return Steinberg::kResultTrue;
		}

		//------------------------------------------------------------------------
		/** Returns the size of the platform representation of the view. */
		Steinberg::tresult MeterControllerViewWin32WpfHost::getSize(Steinberg::ViewRect* size)
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
		Steinberg::tresult MeterControllerViewWin32WpfHost::onSize(Steinberg::ViewRect* newSize)
		{
			if ((newSize->right - newSize->left >= 800) && (newSize->bottom - newSize->top >= 450))
			{
				m_rect = *newSize;
				return Steinberg::kResultTrue;
			}
			return Steinberg::kResultFalse;
		}

		//------------------------------------------------------------------------
		/** Focus changed message. */
		Steinberg::tresult MeterControllerViewWin32WpfHost::onFocus(Steinberg::TBool state)
		{
			return Steinberg::kResultTrue;
		}

		//------------------------------------------------------------------------
		/** Sets IPlugFrame object to allow the Plug-in to inform the host about resizing. */
		Steinberg::tresult MeterControllerViewWin32WpfHost::setFrame(Steinberg::IPlugFrame* frame)
		{
			m_plugFrame = frame;
			if (m_plugFrame != nullptr)
			{
				return Steinberg::kResultTrue;
			}
			return Steinberg::kResultFalse;
		}

		//------------------------------------------------------------------------
		/** Is view sizable by user. */
		Steinberg::tresult MeterControllerViewWin32WpfHost::canResize()
		{
			return Steinberg::kResultTrue;
		}

		//------------------------------------------------------------------------
		/** On live resize this is called to check if the view can be resized to the given rect, if not
		 *	adjust the rect to the allowed size. */
		Steinberg::tresult MeterControllerViewWin32WpfHost::checkSizeConstraint(Steinberg::ViewRect* rect)
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
		/**  */
		Steinberg::tresult MeterControllerViewWin32WpfHost::setInputLevelFeedback(Steinberg::Vst::ParamValue newLevel)
		{
			m_UIptr->setInputLevelFeedback(newLevel);
			//
			return Steinberg::kResultTrue;
		}

		//------------------------------------------------------------------------
		/**  */
		Steinberg::tresult PLUGIN_API MeterControllerViewWin32WpfHost::setColorFeedback(Steinberg::Vst::ParamValue newColor)
		{
			m_UIptr->setColorFeedback(newColor);
			//
			return Steinberg::kResultTrue;
		}
		//
	} // namespace Meter
} // namespace Carlsound