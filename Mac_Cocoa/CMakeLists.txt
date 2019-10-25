# https://stackoverflow.com/questions/20962869/cmakelists-txt-for-an-objective-c-project
# https://stackoverflow.com/questions/53129648/how-to-have-info-plist-bundled-in-a-macosx-application-with-cmake


if(APPLE)
    set(ProjectName MeterUI)
    
    set(CMAKE_C_FLAGS "-x objective-c")

    set(HEADER 
        #./include/cocoaPlugView.h
            #../Mac_Cocoa/include/meterView.h
        ./include/meterViewController.h
            ./include/meterUI.h
            #./Info.plist
        # ./include/meterWindowController.h
    )
    set(SOURCE 
        #./source/cocoaPlugView.mm
            # ../Mac_Cocoa/source/meterView.mm
        ./source/meterViewController.mm
        # ./source/meterWindowController.mm
    )
    set(XIB
        ./UI/meterViewController.xib
        # ./UI/meterWindowController.xib
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