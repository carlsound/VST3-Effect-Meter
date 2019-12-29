#include "../include/loadMissingDll.h"

namespace Carlsound
{
	namespace Meter
	{
		//-----------------------------------------------------------------------
		/** Constructor */
		LoadMissingDll::LoadMissingDll()
		{
			System::AppDomain^ currentDomain = System::AppDomain::CurrentDomain;
			currentDomain->AssemblyResolve += gcnew System::ResolveEventHandler(&LoadMissingDll::LoadFromVst3Folder);
			System::Reflection::Assembly^ assembly = System::Reflection::Assembly::LoadFrom("C:/Program Files/Common Files/VST3/Meter_WPF_UI_CS_XAML_x64.dll");
		}

		//-----------------------------------------------------------------------
		/** Resolves the location of the Meter_WPF_UI_CS_XAML DLL at Runtime */
		System::Reflection::Assembly^ LoadMissingDll::LoadFromVst3Folder(System::Object^ sender, System::ResolveEventArgs^ args)
		{
			//System::String^ folderPath = System::IO::Path::GetDirectoryName(System::Reflection::Assembly::GetExecutingAssembly()->Location);
			//System::String^ assemblyPath = System::IO::Path::Combine(folderPath, (gcnew System::Reflection::AssemblyName(args->Name))->Name + ".dll");
			System::String^ assemblyPath = "C:/Program Fies/Common Files/VST3/Meter_WPF_UI_CS_XAML_x64.dll";
			if (System::IO::File::Exists(assemblyPath) == false) return nullptr;
			System::Reflection::Assembly^ assembly = System::Reflection::Assembly::LoadFrom(assemblyPath);
			return assembly;
		}
	}
}