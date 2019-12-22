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

	[System::STAThreadAttribute]
	__declspec(dllexport)  void loadChildWindow(void* hWnd)
	{
		if (_WIN64)
		{
			//SetDllDirectoryA("C:\\Program Files\\Common Files\\VST3");
			//LoadLibraryA("C:\\Program Files\\Common Files\\VST3\\Meter_WPF_UI_CS_XAML_x64.dll");
			System::Reflection::Assembly::LoadFile("C:\\Program Files\\Common Files\\VST3\\Meter_WPF_UI_CS_XAML_x64.dll");
		}
		else
		{
			//SetDllDirectoryA("C:\\Program Files (x86)\\Common Files\\VST3");
			//LoadLibraryA("C:\\Program Files (x86)\\Common Files\\VST3\\Meter_WPF_UI_CS_XAML_x86.dll");
			System::Reflection::Assembly::LoadFile("C:\\Program Files (x86)\\Common Files\\VST3\\Meter_WPF_UI_CS_XAML_x86.dll");
		}
		
		Carlsound::Meter::Meter_WPF_UI_CppCLI^ inst = gcnew Carlsound::Meter::Meter_WPF_UI_CppCLI();
		
		//Carlsound::Meter::Class1::Instance->usrCtrlObj;

		Carlsound::Meter::MeterUserControl^ m_userControl = gcnew Carlsound::Meter::MeterUserControl(); 
		//inst->usrCtrlObj = gcnew Carlsound::Meter::MeterUserControl();

		System::Windows::Interop::HwndSourceParameters^ sourceParams = gcnew System::Windows::Interop::HwndSourceParameters("Meter");
		sourceParams->PositionX = 0;
		sourceParams->PositionY = 0;
		sourceParams->Height = 450; // m_userControl->Height; //inst->usrCtrlObj->Height; //450;
		sourceParams->Width = 800; // m_userControl->Width; //inst->usrCtrlObj->Width; //800;
		sourceParams->ParentWindow = System::IntPtr(hWnd);
		sourceParams->WindowStyle = WS_VISIBLE | WS_CHILD;
		//
		System::Windows::Interop::HwndSource^ m_hwndSource = gcnew System::Windows::Interop::HwndSource(*sourceParams);
		//
		m_hwndSource->RootVisual = m_userControl;
		//m_hwndSource->RootVisual = Carlsound::Meter::Class1::Instance->usrCtrlObj;
		//m_hwndSource->RootVisual = inst->usrCtrlObj;
		//
		//int i = 0;
		//
		//Carlsound::Meter::Meter_WPF_UI_CppCLI::Instance->managed();
	}
#ifdef __cplusplus 
}
#endif

#pragma managed
void Carlsound::Meter::Meter_WPF_UI_CppCLI::managed()
{
	//Carlsound::Meter::MeterUserControl^ m_userControl = gcnew Carlsound::Meter::MeterUserControl();
	int i = 0;
}