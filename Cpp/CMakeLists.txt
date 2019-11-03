if(APPLE)
    set(CMAKE_C_FLAGS "-x objective-c")

    set(plug_includes
		include/meterController.h
	    include/meterControllerIncludes.h
        #---
        include/meterParameters.h
        #---
        include/meterProcessor.h
        include/meterProcessorIncludes.h
        #---
        include/meterUIDs.h
        #---
        include/meterVersion.h
        #---
        #include/componentAttribute.h
        #---
        #include/componentAttributeList.h
        #---
        #include/componentMessage.h
        #--
        include/ideConsoleWriteLine.h
        #
        ../Mac_Cocoa/include/cocoaPlugView.h
        #
        ../Mac_Cocoa/include/meterView.h
        #
        ../Mac_Cocoa/include/meterViewController.h
        #../Mac_Cocoa/include/meterWindowController.h
        )

    set(plug_sources
        # source/meterController.cpp
        ../Mac_Cocoa/source/meterController.mm
        #---
            source/meterProcessor.cpp
        #../Mac_Cocoa/source/meterProcessor.mm
        #---
            source/meterFactory.cpp
        #../Mac_Cocoa/source/meterFactory.mm
        #---
        #source/componentAttribute.cpp
        #---
        #source/componentAttributeList.cpp
        #---
        #source/componentMessage.cpp
        #
        ../Mac_Cocoa/source/cocoaPlugView.mm
        #
        ../Mac_Cocoa/source/meterView.mm
        #
        ../Mac_Cocoa/source/meterViewController.mm
        #
        #../Mac_Cocoa/source/meterWindowController.mm
        #
        ../Mac_Cocoa/UI/meterViewController.xib
        #
        #../Mac_Cocoa/UI/meterWindowController.xib
        )
#
elseif(WIN32)
    set(plug_includes
        include/meterController.h
	    include/meterControllerIncludes.h
	    ../Win_WPF/Cpp_CLI/include/WpfPlugView.h
        #---
        include/meterParameters.h
        #---
        include/meterProcessor.h
        include/meterProcessorIncludes.h
        #---
        include/meterUIDs.h
        #---
        include/meterVersion.h
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
        source/meterController.cpp
		../Win_WPF/Cpp_CLI/source/WpfPlugView.cpp
        #---
        source/meterProcessor.cpp
        #---
        source/meterFactory.cpp
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
            MACOSX_BUNDLE_GUI_IDENTIFIER "net.carlsound.\${PRODUCT_NAME:identifier}"
            # DEVELOPMENT_TEAM ${DEVELOPMENT_TEAM_ID}
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Mac Developer")
#
elseif((WIN32) AND (CMAKE_SIZEOF_VOID_P EQUAL "8"))
    target_link_libraries(${target} PRIVATE 
    base 
    sdk 
    #vstgui_support 
    Meter_WPF_UI_CppCLI_x64
    )

	target_include_directories(${target} PRIVATE ../Win_WPF/Cpp_CLI)
	#
    #target_sources(${target} PRIVATE resource/plug.rc)
    set_property(TARGET ${target} PROPERTY CXX_STANDARD 17)
#
elseif(WIN32)
    target_link_libraries(${target} PRIVATE 
    base 
    sdk 
    #vstgui_support 
    Meter_WPF_CLI_x86
    )


	#
    #target_sources(${target} PRIVATE resource/plug.rc)
    set_property(TARGET ${target} PROPERTY CXX_STANDARD 17)
#   
endif()
#
# smtg_add_vst3_resource(${target} "resource/plug.uidesc")
# smtg_add_vst3_resource(${target} "resource/background.png")
# smtg_add_vst3_resource(${target} "resource/slider_background.png")
# smtg_add_vst3_resource(${target} "resource/slider_handle.png")
# smtg_add_vst3_resource(${target} "resource/slider_handle_2.0x.png")
# smtg_add_vst3_resource(${target} "resource/vu_on.png")
# smtg_add_vst3_resource(${target} "resource/vu_off.png")