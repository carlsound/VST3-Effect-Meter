if(APPLE)
    set(CMAKE_C_FLAGS "-x objective-c")

    set(plug_includes
        include/meterParameters.h
        #---
        include/meterUIDs.h
        #---
        include/meterVersion.h
        #---
        include/meterProcessorIncludes.h
        include/meterProcessor.h
        #---
        include/meterControllerIncludes.h
        include/meterController.h
        #---
        include/iMeterControllerView.h
        ../Mac_Cocoa/include/meterPlugViewCocoa.h
        #---
        ../Mac_Cocoa/include/meterView.h
        #---
        ../Mac_Cocoa/include/meterViewController.h
        #../Mac_Cocoa/include/meterWindowController.h
        #---
        #include/componentAttribute.h
        #---
        #include/componentAttributeList.h
        #---
        #include/componentMessage.h
        #--
        include/ideConsoleWriteLine.h
        )

    set(plug_sources
        source/meterFactory.cpp
        #../Mac_Cocoa/source/meterFactory.mm
        #---
        source/meterProcessor.cpp
        #../Mac_Cocoa/source/meterProcessor.mm
        #---
        # source/meterController.cpp
        ../Mac_Cocoa/source/meterController.mm
        #---
        ../Mac_Cocoa/source/meterPlugViewCocoa.mm
        #---
        ../Mac_Cocoa/source/meterView.mm
        #---
        ../Mac_Cocoa/source/meterViewController.mm
        #
        #../Mac_Cocoa/source/meterWindowController.mm
        #
        ../Mac_Cocoa/UI/meterViewController.xib
        #
        #../Mac_Cocoa/UI/meterWindowController.xib
        #---
        #source/componentAttribute.cpp
        #---
        #source/componentAttributeList.cpp
        #---
        #source/componentMessage.cpp
        )
#
elseif(WIN32)
    set(plug_includes
        include/stdafx.h
        include/meterParameters.h
        #---
        include/meterUIDs.h
        #---
        include/meterVersion.h
        #---
        include/meterProcessorIncludes.h
        include/meterProcessor.h
        #---
        include/meterControllerIncludes.h
        include/meterController.h
        #--
        include/iMeterControllerView.h
        #../Win_Ultralight/include/meterPlugViewUltralightWin32.h
        ../Win_WPF/Cpp_CLI/include/meterControllerViewWin32WpfHostIncludes.h
	    ../Win_WPF/Cpp_CLI/include/meterControllerViewWin32WpfHost.h
        #../Win_WPF/Cpp_CLI/include/loadMissingDll.h
        #---
        #include/componentAttribute.h
        #---
        #include/componentAttributeList.h
        #---
        #include/componentMessage.h
        #--
        include/ideConsoleWriteLine.h
        )

    set(plug_sources
        source/meterFactory.cpp
        #---
        source/meterProcessor.cpp
        #---
        source/meterController.cpp
        #../Win_Ultralight/source/meterPlugViewUltralightWin32.cpp
		../Win_WPF/Cpp_CLI/source/meterControllerViewWin32WpfHost.cpp
        #../Win_WPF/Cpp_CLI/source/LoadMissingDll.cpp
        #---
        #source/componentAttribute.cpp
        #---
        #source/componentAttributeList.cpp
        #---
        #source/componentMessage.cpp
        )
#
endif()
#
#--- HERE change the target Name for your plug-in (for ex. set(target myDelay))-------
if(APPLE)
    set(target Meter_OSX)
elseif((WIN32) AND (CMAKE_SIZEOF_VOID_P EQUAL "8"))
    set(target Meter_x64)
elseif(WIN32)
    set(target Meter_x86)
endif()
#
smtg_add_vst3plugin(${target} ${SDK_ROOT} ${plug_includes} ${plug_sources})
#
set_target_properties(${target} PROPERTIES ${SDK_IDE_MYPLUGINS_FOLDER}/${target})
#target_include_directories(${target} PUBLIC ${VSTGUI_ROOT}/vstgui4)
#
if(APPLE)
    #find_library(UI MeterUI)

    target_link_libraries(${target} PRIVATE 
    base 
    sdk 
    #vstgui_support 
    #Meter_Cocoa_UI
    "-framework Cocoa"
    "-framework AppKit"
    "-framework CoreData"
    "-framework Foundation"
            objc
            #${UI}
    )

    smtg_set_bundle(${target} INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/resource/Info.plist" PREPROCESS)

    set_source_files_properties(
            ../Mac_Cocoa/UI/meterViewController.xib
            PROPERTIES
            MACOSX_PACKAGE_LOCATION Resources
    )

    set_target_properties(${target} PROPERTIES
            MACOSX_BUNDLE_BUNDLE_NAME "VST3-Effect-Meter"
            MACOSX_BUNDLE_GUI_IDENTIFIER "net.carlsound.VST3-Effect-Meter"
            # DEVELOPMENT_TEAM ${DEVELOPMENT_TEAM_ID}
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Mac Developer")
#
elseif((WIN32) AND (CMAKE_SIZEOF_VOID_P EQUAL "8"))
    target_link_libraries(${target} PRIVATE 
    base 
    sdk 
    #vstgui_support 
    #Meter_WPF_UI_CppCLI_x64
    Meter_WPF_UI_CS_XAML_AnyCPU
    #"C:/Users/john_/Downloads/ultralight-sdk-1.0-win/lib/win/x64/AppCore.lib"
    #"C:/Users/john_/Downloads/ultralight-sdk-1.0-win/lib/win/x64/Ultralight.lib"
    #"C:/Users/john_/Downloads/ultralight-sdk-1.0-win/lib/win/x64/UltralightCore.lib"
    #"C:/Users/john_/Downloads/ultralight-sdk-1.0-win/lib/win/x64/WebCore.lib"
    )
#
elseif(WIN32)
    target_link_libraries(${target} PRIVATE 
    base 
    sdk 
    #vstgui_support 
    #Meter_WPF_UI_CLI_x86
    Meter_WPF_UI_CS_XAML_AnyCPU
    #"C:/Users/john_/Downloads/ultralight-sdk-1.0-win/lib/win/x86/AppCore.lib"
    #"C:/Users/john_/Downloads/ultralight-sdk-1.0-win/lib/win/x86/Ultralight.lib"
    #"C:/Users/john_/Downloads/ultralight-sdk-1.0-win/lib/win/x86/UltralightCore.lib"
    #"C:/Users/john_/Downloads/ultralight-sdk-1.0-win/lib/win/x86/WebCore.lib"
    )
#   
endif()

if(WIN32)
    target_compile_options(${target} PRIVATE /fp:precise) #/fp:strict is incompatible with /clr
    target_compile_options(${target} PRIVATE /Zi) #/ZI is incompatible with /clr
    #
    string(REPLACE "/MP" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    #
    target_include_directories(${target} PRIVATE 
    ..Win_WPF/CS_XAML
    #"C:/Users/john_/Downloads/ultralight-sdk-1.0-win/"
    )
    #
    set_property(TARGET ${target} PROPERTY CXX_STANDARD 17)
    set_property(TARGET ${target} PROPERTY COMMON_LANGUAGE_RUNTIME "")
    set_property(TARGET ${target} PROPERTY VS_GLOBAL_CLRSupport "true")
    set_property(TARGET ${target} PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.8")
    set_property(TARGET ${target} PROPERTY VS_DOTNET_REFERENCES
	"mscorlib"
	"PresentationCore"
	"PresentationFramework"
	"System"
	"System.Core"
	"System.Data"
	"System.Data.DataSetExtensions"
	"System.Net.Http"
	"System.Xaml"
	"System.Xml"
	#"System.Xml.Linq"
    "WindowsBase")
    #
    #target_include_directories(${target} PRIVATE ../Win_WPF/Cpp_CLI)
	#
    #target_sources(${target} PRIVATE resource/plug.rc)
endif()
#
# VSTGUI
# smtg_add_vst3_resource(${target} "resource/plug.uidesc")
# smtg_add_vst3_resource(${target} "resource/background.png")
# smtg_add_vst3_resource(${target} "resource/slider_background.png")
# smtg_add_vst3_resource(${target} "resource/slider_handle.png")
# smtg_add_vst3_resource(${target} "resource/slider_handle_2.0x.png")
# smtg_add_vst3_resource(${target} "resource/vu_on.png")
# smtg_add_vst3_resource(${target} "resource/vu_off.png")