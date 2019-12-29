add_subdirectory(Cpp)

if(APPLE)
    add_subdirectory(Mac_Cocoa)
elseif(WIN32)
    #add_subdirectory(Win_WPF)
    #add_subdirectory(Win_Ultralight)
endif()