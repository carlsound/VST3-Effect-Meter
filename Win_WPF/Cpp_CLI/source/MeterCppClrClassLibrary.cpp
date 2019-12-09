#pragma once

//#include "pch.h"

#include <windows.h>
#include <WinUser.h>

#include "../include/meterCppClrClassLibrary.h"
#include "../include/nativeInterface.h"
//#include <MeterUserControl.xaml>
//
//#using <Meter_WPF_UI_CS_XAML_x64.dll>

#ifdef __cplusplus
extern "C"
{
#endif

	[System::STAThread]
	__declspec(dllexport)  void loadChildWindow(void* hWnd)
	{
		
		//Carlsound::Meter::MeterUserControl^ m_userControl = gcnew Carlsound::Meter::MeterUserControl(); //CppClrClassLibrary1::Class1::Instance->usrCtrlObj;
		/*
		System::Windows::Interop::HwndSourceParameters^ sourceParams = gcnew System::Windows::Interop::HwndSourceParameters("Meter");
		sourceParams->PositionX = 0;
		sourceParams->PositionY = 0;
		sourceParams->Height = 450; //m_userControl->Height;
		sourceParams->Width = 800; // m_userControl->Width;
		sourceParams->ParentWindow = System::IntPtr(hWnd);
		sourceParams->WindowStyle = WS_VISIBLE | WS_CHILD;
		//
		System::Windows::Interop::HwndSource^ m_hwndSource = gcnew System::Windows::Interop::HwndSource(*sourceParams);
		//
		m_hwndSource->RootVisual = m_userControl;
		//
		*/
		int i = 0;
	}
#ifdef __cplusplus 
}
#endif 