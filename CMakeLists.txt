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
target_link_libraries(${target} PRIVATE base sdk)

if(MAC)
    smtg_set_bundle(${target} INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/resource/Info.plist" PREPROCESS)
elseif(WIN)
    target_sources(${target} PRIVATE resource/plug.rc)
endif()