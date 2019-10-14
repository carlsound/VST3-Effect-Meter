# https://stackoverflow.com/questions/20962869/cmakelists-txt-for-an-objective-c-project
# https://stackoverflow.com/questions/53129648/how-to-have-info-plist-bundled-in-a-macosx-application-with-cmake


if(APPLE)
    set(ProjectName Meter_Cocoa_UI)
    
    set(CMAKE_C_FLAGS "-x objective-c")

    set(HEADER 
        ./include/CocoaPlugView.h    
        ./include/MeterViewController.h
        ./include/MeterWindowController.h
    )
    set(SOURCE 
        ./source/CocoaPlugView.mm
        ./source/MeterViewController.mm
        ./source/MeterWindowController.mm
    )
    set(XIB
        ./UI/MeterViewController.xib
        ./UI/MeterWindowController.xib
    )

    add_library(${ProjectName} SHARED
        ${NAME}
        ${HEADER}
        ${SOURCE}
        ${XIB}
        )

    set_property(TARGET ${ProjectName} PROPERTY ${SDK_IDE_MYPLUGINS_FOLDER}/Meter_OSX)

    set_source_files_properties(
        ${XIB}
        PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources
    )

    # set_target_properties(
    #    ${ProjectName}
    #    PROPERTIES
    #    MACOSX_BUNDLE TRUE
    #    MACOSX_BUNDLE_INFO_PLIST Info.plist
    # )

    target_link_libraries(${ProjectName}
        "-framework Cocoa"
        "-framework AppKit"
        "-framework CoreData"
        "-framework Foundation"
    )
endif()