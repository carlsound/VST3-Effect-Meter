#--- https://github.com/bemehiser/cmake_csharp_example

#--- HERE change the target Name for your plug-in (for ex. set(target myDelay))-------
if((WIN32) AND (CMAKE_SIZEOF_VOID_P EQUAL "8"))
  set(target Meter_WPF_UI_x64)
  set_target_properties(${target} PROPERTIES ${SDK_IDE_MYPLUGINS_FOLDER}/Meter_x64)
elseif(WIN32)
	set(target Meter_WPF_UI_x86)
	set_target_properties(${target} PROPERTIES ${SDK_IDE_MYPLUGINS_FOLDER}/Meter_x86)
endif()

project(${target} VERSION 0.1.0 LANGUAGES CSharp)

include(CSharpUtilities)

add_executable(${target}
	#--- UserControl1.config
	UserControl1.xaml
	UserControl1.xaml.cs

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
	UserControl1.xaml
	UserControl1.xaml.cs)



set_property(SOURCE UserControl1.xaml PROPERTY VS_XAML_TYPE "UserControl1licationDefinition")

set_property(TARGET ${target} PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.6.1")
set_property(TARGET ${target} PROPERTY WIN32_EXECUTABLE TRUE)

set_property(TARGET ${target} PROPERTY VS_DOTNET_REFERENCES
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