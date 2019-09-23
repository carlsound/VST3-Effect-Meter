set(plug_sources
    include/meterController.h
	include/meterControllerIncludes.h
    source/meterController.cpp
    #---
    include/meterParameters.h
    #---
    include/meterProcessor.h
	include/meterProcessorIncludes.h
    source/meterProcessor.cpp
    #---
    include/meterUIDs.h
    #---
    include/meterVersion.h
    #---
    source/meterFactory.cpp
    #---
    include/componentAttribute.h
    source/componentAttribute.cpp
    #---
    include/componentAttributeList.h
    source/componentAttributeList.cpp
    #---
    include/componentMessage.h
    source/componentMessage.cpp
)

#--- HERE change the target Name for your plug-in (for ex. set(target myDelay))-------
if(APPLE)
	set(target Meter)
elseif((WIN32) AND (CMAKE_SIZEOF_VOID_P EQUAL "8"))
    set(target Meter_x64)
elseif(WIN32)
	set(target Meter_x86)
endif()

smtg_add_vst3plugin(${target} ${SDK_ROOT} ${plug_sources})
set_target_properties(${target} PROPERTIES ${SDK_IDE_MYPLUGINS_FOLDER})
target_include_directories(${target} PUBLIC ${VSTGUI_ROOT}/vstgui4)
target_link_libraries(${target} PRIVATE base sdk vstgui_support)

 smtg_add_vst3_resource(${target} "resource/meter.uidesc")
 smtg_add_vst3_resource(${target} "resource/background.png")
 smtg_add_vst3_resource(${target} "resource/slider_background.png")
 smtg_add_vst3_resource(${target} "resource/slider_handle.png")
 smtg_add_vst3_resource(${target} "resource/slider_handle_2.0x.png")
 smtg_add_vst3_resource(${target} "resource/vu_on.png")
 smtg_add_vst3_resource(${target} "resource/vu_off.png")

if(MAC)
    smtg_set_bundle(${target} INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/resource/Info.plist" PREPROCESS)
elseif(WIN)
    target_sources(${target} PRIVATE resource/plug.rc)
endif()