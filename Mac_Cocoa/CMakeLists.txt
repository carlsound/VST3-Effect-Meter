# https://stackoverflow.com/questions/20962869/cmakelists-txt-for-an-objective-c-project
# https://stackoverflow.com/questions/53129648/how-to-have-info-plist-bundled-in-a-macosx-application-with-cmake


if(APPLE)
    set(ProjectName MeterUI)
    
    set(CMAKE_C_FLAGS "-x objective-c")

    set(HEADER 
        #./include/CocoaPlugView.h
        ./include/MeterViewController.h
            ./include/MeterUI.h
            #./Info.plist
        # ./include/MeterWindowController.h
    )
    set(SOURCE 
        #./source/CocoaPlugView.mm
        ./source/MeterViewController.mm
        # ./source/MeterWindowController.mm
    )
    set(XIB
        ./UI/MeterViewController.xib
        # ./UI/MeterWindowController.xib
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

    set_target_properties(${ProjectName} PROPERTIES
            FRAMEWORK TRUE
            FRAMEWORK_VERSION C
            MACOSX_FRAMEWORK_IDENTIFIER net.carlsound.meterUI
            #MACOSX_FRAMEWORK_INFO_PLIST Info.plist
            # "current version" in semantic format in Mach-O binary file
            VERSION 16.4.0
            # "compatibility version" in semantic format in Mach-O binary file
            SOVERSION 1.0.0
            PUBLIC_HEADER dynamicFramework.h
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "MacOS Developer"
            )

    target_link_libraries(${ProjectName}
            base
            sdk
        "-framework Cocoa"
        "-framework AppKit"
        "-framework CoreData"
        "-framework Foundation"
            objc
    )
endif()