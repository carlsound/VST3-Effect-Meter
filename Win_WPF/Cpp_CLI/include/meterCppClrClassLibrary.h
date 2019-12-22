// https://code.msdn.microsoft.com/windowsdesktop/Consuming-C-Library-in-937458e5

#pragma once

using namespace System;

using namespace System::Runtime::InteropServices;

#if _WIN64
	#using "C:\\Program Files\\Common Files\\VST3\\Meter_WPF_UI_CS_XAML_x64.dll"
#else
	#using "C:\\Program Files (x86)\\Common Files\\VST3\\Meter_WPF_UI_CS_XAML_x86.dll"
#endif

//using namespace WpfUserControlLibrary1;

namespace Carlsound
{
	namespace Meter
	{
		public ref class Meter_WPF_UI_CppCLI
		{
			// TODO: Add your methods for this class here.

		public:
			static MeterUserControl^ usrCtrlObj;

			static Meter_WPF_UI_CppCLI^ Instance = gcnew Meter_WPF_UI_CppCLI();

			void managed();
		};
	}
}
