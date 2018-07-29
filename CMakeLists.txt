set(plug_sources
    include/meterController.h
    source/meterController.cpp
    #---
    include/meterIDs.h
    #---
    include/meterProcessor.h
    source/meterProcessor.cpp
    #---
    include/meterVersion.h
    #---
    source/meterFactory.cpp
)

#--- HERE change the target Name for your plug-in (for ex. set(target myDelay))-------
if(MAC)
	set(target Meter)
elseif((WIN) AND (CMAKE_SIZEOF_VOID_P EQUAL "8"))
    set(target Meter_x64)
elseif(WIN)
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