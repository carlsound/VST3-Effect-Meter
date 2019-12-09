// https://stackoverflow.com/questions/1373100/how-to-add-folder-to-assembly-search-path-at-runtime-in-net
//
#pragma once

namespace Carlsound
{
	namespace Meter
	{
		public ref class LoadMissingDll : System::Object
		{
		public:
			/** Constructor */
			LoadMissingDll();

		private:
			/** Resolves the location of the Meter_WPF_UI_CS_XAML DLL at Runtime */
			static System::Reflection::Assembly^ LoadFromVst3Folder(System::Object^ sender, System::ResolveEventArgs^ args);
		};
	}
}