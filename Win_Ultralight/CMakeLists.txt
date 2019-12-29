if(WIN32)
    set(library_includes
        include/meterUltralightPlugViewWin32.h
        )

    set(library_sources
        source/meterUltralightPlugViewWin32.cpp
        )
endif()
#
#--- HERE change the target Name for your plug-in (for ex. set(target myDelay))-------
if((WIN32) AND (CMAKE_SIZEOF_VOID_P EQUAL "8"))
    set(ProjectName Meter_Ultralight_UI_x64)
elseif(WIN32)
    set(ProjectName Meter_Ultralight_UI_x86)
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
	target_link_libraries(${ProjectName} PRIVATE "C:/Users/john_/Downloads/ultralight-sdk-1.0-win/lib/win/x64/AppCore.lib")
	target_link_libraries(${ProjectName} PRIVATE "C:/Users/john_/Downloads/ultralight-sdk-1.0-win/lib/win/x64/Ultralight.lib")
	target_link_libraries(${ProjectName} PRIVATE "C:/Users/john_/Downloads/ultralight-sdk-1.0-win/lib/win/x64/UltralightCore.lib")
	target_link_libraries(${ProjectName} PRIVATE "C:/Users/john_/Downloads/ultralight-sdk-1.0-win/lib/win/x64/WebCore.lib")
elseif(WIN32)
	set_property(TARGET ${ProjectName} PROPERTY ${SDK_IDE_MYPLUGINS_FOLDER}/Meter_x86)
	target_link_libraries(${ProjectName} PRIVATE "C:/Users/john_/Downloads/ultralight-sdk-1.0-win/lib/win/x86/AppCore.lib")
	target_link_libraries(${ProjectName} PRIVATE "C:/Users/john_/Downloads/ultralight-sdk-1.0-win/lib/win/x86/Ultralight.lib")
	target_link_libraries(${ProjectName} PRIVATE "C:/Users/john_/Downloads/ultralight-sdk-1.0-win/lib/win/x86/UltralightCore.lib")
	target_link_libraries(${ProjectName} PRIVATE "C:/Users/john_/Downloads/ultralight-sdk-1.0-win/lib/win/x86/WebCore.lib")
endif()
#
#
#
if(WIN32)
	target_include_directories(${ProjectName} PRIVATE "C:/Users/john_/Downloads/ultralight-sdk-1.0-win/")
	#
	set_property(TARGET ${ProjectName} PROPERTY CXX_STANDARD 17)
    
endif()