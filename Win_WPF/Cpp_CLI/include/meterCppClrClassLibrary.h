// https://code.msdn.microsoft.com/windowsdesktop/Consuming-C-Library-in-937458e5

#pragma once

using namespace System;

using namespace System::Runtime::InteropServices;

//using namespace WpfUserControlLibrary1;

namespace Carlsound
{
	namespace Meter
	{
		public ref class Class1
		{
			// TODO: Add your methods for this class here.

		public:
			MeterUserControl^ usrCtrlObj;

			static Class1^ Instance = gcnew Class1();
		};
	}
}
