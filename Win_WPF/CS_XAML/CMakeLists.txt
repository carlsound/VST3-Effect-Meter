#--- https://github.com/bemehiser/cmake_csharp_example
#--- https://stackoverflow.com/questions/6594796/how-do-i-make-cmake-output-into-a-bin-dir
#--- https://github.com/fsharp/FAKE/issues/869

#--- HERE change the target Name for your plug-in (for ex. set(target myDelay))-------
#if((WIN32) AND (CMAKE_SIZEOF_VOID_P EQUAL "8"))
#	set(ProjectName Meter_WPF_UI_CS_XAML_x64)
#elseif(WIN32)
#	set(ProjectName Meter_WPF_UI_CS_XAML_x86)
#endif()

if(WIN32)
	set(ProjectName Meter_WPF_UI_CS_XAML_AnyCPU)

	project(${ProjectName} VERSION 0.1.0 LANGUAGES CSharp)

	include(CSharpUtilities)

	add_library(${ProjectName} SHARED
		#--- MeterUserControl.config
		MeterUserControl.xaml
		MeterUserControl.xaml.cs
		Properties/AssemblyInfo.cs
		Properties/Resources.Designer.cs
		Properties/Resources.resx
		Properties/Settings.Designer.cs
		Properties/Settings.settings)
	
	csharp_set_designer_cs_properties(
		Properties/AssemblyInfo.cs
		Properties/Resources.Designer.cs
		Properties/Resources.resx
		Properties/Settings.Designer.cs
		Properties/Settings.settings)
		
	csharp_set_xaml_cs_properties(
		MeterUserControl.xaml
		MeterUserControl.xaml.cs)
endif()

if((WIN32) AND (CMAKE_SIZEOF_VOID_P EQUAL "8"))
	set_property(TARGET ${ProjectName} PROPERTY ${SDK_IDE_MYPLUGINS_FOLDER}/Meter_x64)
	set_property(TARGET ${ProjectName} PROPERTY LIBRARY_OUTPUT_DIRECTORY "C:\\Program Files\\Common Files\\VST3")
	#set_property(TARGET ${ProjectName} PROPERTY RUNTIME_OUTPUT_DIRECTORY "C:\\Program Files\\Common Files\\VST3")
	#target_compile_options(${ProjectName} PRIVATE /p:OutDir="C:\\Program Files\\Common Files\\VST3")
elseif(WIN32)
	set_property(TARGET ${ProjectName} PROPERTY ${SDK_IDE_MYPLUGINS_FOLDER}/Meter_x86)
	set_property(TARGET ${ProjectName} PROPERTY LIBRARY_OUTPUT_DIRECTORY "C:\\Program Files (x86)\\Common Files\\VST3")
	#set_property(TARGET ${ProjectName} PROPERTY RUNTIME_OUTPUT_DIRECTORY "C:\\Program Files (x86)\\Common Files\\VST3")
	#target_compile_options(${ProjectName} PRIVATE /p:OutputPath="C:\\Program Files (x86)\\Common Files\\VST3")
endif()

if(WIN32)
	target_compile_options(${ProjectName} PRIVATE /platform:anycpu)
	target_compile_options(${ProjectName} PRIVATE /optimize)

	set_property(SOURCE UserControl1.xaml PROPERTY VS_XAML_TYPE "ApplicationDefinition")

	set_property(TARGET ${ProjectName} PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.8")
	set_property(TARGET ${ProjectName} PROPERTY WIN32_EXECUTABLE TRUE)

	set_property(TARGET ${ProjectName} PROPERTY VS_DOTNET_REFERENCES
	"Microsoft.CSharp"
	"PresentationCore"
	"PresentationFramework"
	"System"
	"System.Core"
	"System.Data"
	"System.Data.DataSetExtensions"
	"System.Net.Http"
	"System.Xaml"
	"System.Xml"
	"System.Xml.Linq"
	"WindowsBase")
endif()