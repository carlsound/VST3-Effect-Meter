set(plug_includes
    include/meterController.h
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
    include/IdeConsoleWriteLine.h
)

if(APPLE)
    set(plug_sources
        ../Mac_Cocoa/source/meterController.mm
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
elseif(WIN32)
    set(plug_sources
        source/meterController.cpp
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
    target_link_libraries(${target} PRIVATE 
    base 
    sdk 
    #vstgui_support 
    Meter_Cocoa_UI
    "-framework Cocoa"
    "-framework AppKit"
    "-framework CoreData"
    "-framework Foundation"
            objc
    )

    smtg_set_bundle(${target} INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/resource/Info.plist" PREPROCESS)
#
elseif((WIN32) AND (CMAKE_SIZEOF_VOID_P EQUAL "8"))
    target_link_libraries(${target} PRIVATE 
    base 
    sdk 
    #vstgui_support 
    Meter_WPF_UI_x64
    )

    target_sources(${target} PRIVATE resource/plug.rc)
    set_property(TARGET ${target} PROPERTY CXX_STANDARD 17)
    set_property(TARGET ${target} PROPERTY COMMON_LANGUAGE_RUNTIME "")
    set_property(TARGET ${target} PROPERTY VS_GLOBAL_CLRSupport "true")
    target_compile_options(${target} PRIVATE /fp:precise) #/fp:strict is incompatible with /clr
#
elseif(WIN32)
    target_link_libraries(${target} PRIVATE 
    base 
    sdk 
    #vstgui_support 
    Meter_WPF_UI_x86
    )

    target_sources(${target} PRIVATE resource/plug.rc)
    set_property(TARGET ${target} PROPERTY CXX_STANDARD 17)
    set_property(TARGET ${target} PROPERTY COMMON_LANGUAGE_RUNTIME "")
    set_property(TARGET ${target} PROPERTY VS_GLOBAL_CLRSupport "true")
    target_compile_options(${target} PRIVATE /fp:precise) #/fp:strict is incompatible with /clr
endif()
#
# smtg_add_vst3_resource(${target} "resource/plug.uidesc")
# smtg_add_vst3_resource(${target} "resource/background.png")
# smtg_add_vst3_resource(${target} "resource/slider_background.png")
# smtg_add_vst3_resource(${target} "resource/slider_handle.png")
# smtg_add_vst3_resource(${target} "resource/slider_handle_2.0x.png")
# smtg_add_vst3_resource(${target} "resource/vu_on.png")
# smtg_add_vst3_resource(${target} "resource/vu_off.png")