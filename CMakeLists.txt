cmake_minimum_required(VERSION 3.16)

# bundle assets for macOS and iOS builds
if (APPLE)
    # get a list of all of the files in the data-folder.
    file(GLOB_RECURSE RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/assets/*")

    # individually set the file's path properties.
    foreach (FILE ${RESOURCES})
        # get the relative path from the data-folder to the particular file.
        file(RELATIVE_PATH NEW_FILE "${CMAKE_CURRENT_SOURCE_DIR}/assets" ${FILE})

        # get the relative path to the file.
        get_filename_component(NEW_FILE_PATH ${NEW_FILE} DIRECTORY)

        # set it's location inside the app package (under Resources).
        set_property(SOURCE ${FILE} PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${NEW_FILE_PATH}")

        # optional: add the file to the 'Resources' folder group in Xcode.
        #           this also preserves folder structure.
        source_group("Resources/${NEW_FILE_PATH}" FILES "${FILE}")
    endforeach ()
endif ()

# Declare the project
project(ios-test-project)

# Set the name of the executable
set(EXECUTABLE_NAME ${PROJECT_NAME})

add_executable(${EXECUTABLE_NAME} ${RESOURCES})

target_compile_features(${EXECUTABLE_NAME} PUBLIC cxx_std_17)

target_sources(${EXECUTABLE_NAME} 
PRIVATE 
    src/main.cpp
)

target_include_directories(${EXECUTABLE_NAME}
PRIVATE 
    third-party
    third-party/SDL/include
)

# build SDL
set(SDL_STATIC ON)
set(SDL_SHARED OFF)
set(SDL_HIDAPI ON) # enable usb/bluetooth controllers
set(SDL_CAMERA OFF) # disable camera
add_subdirectory(third-party/SDL EXCLUDE_FROM_ALL)
target_link_libraries(${EXECUTABLE_NAME} PUBLIC SDL3::SDL3)

# set apple attributes
# build iOS: cmake .. -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT='/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk'
set_target_properties(${EXECUTABLE_NAME} PROPERTIES 
    # On macOS, make a proper .app bundle instead of a bare executable
    MACOSX_BUNDLE               TRUE

    # Set the Info.plist file for Apple Mobile platforms. Without this file, your app will not launch. 
    MACOSX_BUNDLE_INFO_PLIST    "${CMAKE_CURRENT_SOURCE_DIR}/src/Info.plist.in"

    # 1 is iphone/ipad, 2 is ipad
    XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
)
