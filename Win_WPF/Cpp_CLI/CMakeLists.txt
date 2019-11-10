if(WIN32)
    set(library_includes
        include/meterCppClrClassLibrary.h
	    include/nativeInterface.h
        )

    set(library_sources
        source/meterCppClrClassLibrary.cpp
        )
endif()
#
#--- HERE change the target Name for your plug-in (for ex. set(target myDelay))-------
if((WIN32) AND (CMAKE_SIZEOF_VOID_P EQUAL "8"))
    set(ProjectName Meter_WPF_UI_CppCLI_x64)
elseif(WIN32)
    set(ProjectName Meter_WPF_UI_CppCLI_x86)
endif()
#
if(WIN32)
	project(${ProjectName} VERSION 0.1.0)
	#
	add_library(${ProjectName} SHARED
	${library_includes}
	${library_sources}
	)
endif()
#
#
#
if((WIN32) AND (CMAKE_SIZEOF_VOID_P EQUAL "8"))
	set_property(TARGET ${ProjectName} PROPERTY ${SDK_IDE_MYPLUGINS_FOLDER}/Meter_x64)
	target_link_libraries(${ProjectName} PRIVATE Meter_WPF_UI_CS_XAML_x64)
elseif(WIN32)
	set_property(TARGET ${ProjectName} PROPERTY ${SDK_IDE_MYPLUGINS_FOLDER}/Meter_x86)
	target_link_libraries(${ProjectName} PRIVATE Meter_WPF_UI_CS_XAML_x86)
endif()
#
#
#
if(WIN32)
	target_include_directories(${ProjectName} PRIVATE ../CS_XAML)
	#
	set_property(TARGET ${ProjectName} PROPERTY CXX_STANDARD 17)
    set_property(TARGET ${ProjectName} PROPERTY COMMON_LANGUAGE_RUNTIME "")
    set_property(TARGET ${ProjectName} PROPERTY VS_GLOBAL_CLRSupport "true")
    set_property(TARGET ${ProjectName} PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.8")
    target_compile_options(${ProjectName} PRIVATE /fp:precise) #/fp:strict is incompatible with /clr
    target_compile_options(${ProjectName} PRIVATE /Zi) #/ZI is incompatible with /clr
	#
	#target_sources(${ProjectName} PRIVATE resource/plug.rc)
	#
	#set_property(SOURCE UserControl1.xaml PROPERTY VS_XAML_TYPE "ApplicationDefinition")
	#
	#set_property(TARGET ${ProjectName} PROPERTY WIN32_EXECUTABLE TRUE)
	#
	set_property(TARGET ${ProjectName} PROPERTY VS_DOTNET_REFERENCES
	"mscorlib"
	"PresentationCore"
	"PresentationFramework"
	"System"
	#"System.Core"
	"System.Data"
	#"System.Data.DataSetExtensions"
	#"System.Net.Http"
	"System.Xaml"
	"System.Xml"
	#"System.Xml.Linq"
	"WindowsBase")
endif()