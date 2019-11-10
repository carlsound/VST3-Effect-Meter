#--- https://github.com/bemehiser/cmake_csharp_example

#--- HERE change the target Name for your plug-in (for ex. set(target myDelay))-------
if((WIN32) AND (CMAKE_SIZEOF_VOID_P EQUAL "8"))
	set(ProjectName Meter_WPF_UI_CS_XAML_x64)
elseif(WIN32)
	set(ProjectName Meter_WPF_UI_CS_XAML_x86)
endif()

if(WIN32)
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
elseif(WIN32)
	set_property(TARGET ${ProjectName} PROPERTY ${SDK_IDE_MYPLUGINS_FOLDER}/Meter_x86)
endif()

if(WIN32)
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