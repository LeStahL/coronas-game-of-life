cmake_minimum_required(VERSION 3.10)

project(coronas-game-of-life)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Widgets Gui Multimedia)
find_package(Git QUIET)

# Find sources and resources
file(GLOB IMAGE_ASSETS_FILENAMES "${PROJECT_SOURCE_DIR}/assets/images/**.png")
file(GLOB MAP_ASSETS_FILENAMES "${PROJECT_SOURCE_DIR}/assets/maps/**.json")
file(GLOB MUSIC_ASSETS_FILENAMES "${PROJECT_SOURCE_DIR}/assets/music/**.mp3")
file(GLOB STYLE_ASSETS_FILENAMES "${PROJECT_SOURCE_DIR}/assets/styles/**.qss")
aux_source_directory("${PROJECT_SOURCE_DIR}/src" ${PROJECT_NAME}_SOURCES)

# Compile auto-generated resource file
foreach(IMAGE_ASSET ${IMAGE_ASSETS_FILENAMES})
    message("Added image asset: ${IMAGE_ASSET}")
    get_filename_component(RELATIVE_FILENAME "${IMAGE_ASSET}" NAME)
    set(IMAGE_ASSETS "${IMAGE_ASSETS} <file alias=\"${RELATIVE_FILENAME}\">${IMAGE_ASSET}</file>\n\t")
endforeach()
foreach(MAP_ASSET ${MAP_ASSETS_FILENAMES})
    message("Added map asset: ${MAP_ASSET}")
    get_filename_component(RELATIVE_FILENAME "${MAP_ASSET}" NAME)
    set(MAP_ASSETS "${MAP_ASSETS} <file alias=\"${RELATIVE_FILENAME}\">${MAP_ASSET}</file>\n\t")
endforeach()
foreach(MUSIC_ASSET ${MUSIC_ASSETS_FILENAMES})
    message("Added music asset: ${MUSIC_ASSET}")
    get_filename_component(RELATIVE_FILENAME "${MUSIC_ASSET}" NAME)
    set(MUSIC_ASSETS "${MUSIC_ASSETS} <file alias=\"${RELATIVE_FILENAME}\">${MUSIC_ASSET}</file>\n\t")
endforeach()
foreach(STYLE_ASSET ${STYLE_ASSETS_FILENAMES})
    message("Added style asset: ${STYLE_ASSET}")
    get_filename_component(RELATIVE_FILENAME "${STYLE_ASSET}" NAME)
    set(STYLE_ASSETS "${STYLE_ASSETS} <file alias=\"${RELATIVE_FILENAME}\">${STYLE_ASSET}</file>\n\t")
endforeach()
configure_file("${PROJECT_SOURCE_DIR}/assets/Corona.qrc.in" "${PROJECT_SOURCE_DIR}/assets/Corona.qrc")

set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES} "${PROJECT_SOURCE_DIR}/assets/Corona.qrc")
foreach(FILE ${${PROJECT_NAME}_SOURCES})
    if(NOT EXISTS "${FILE}")
        message(FATAL_ERROR "File ${FILE} does not exist.")
    endif()
endforeach()

# Add library
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE 
    "${PROJECT_SOURCE_DIR}/src"
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
)

set(LIBRARIES
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::Multimedia
)
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

if(WIN32)
    get_filename_component(_qt_bin_dir "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
    find_program(WINDEPLOYQT_EXECUTABLE NAMES windeployqt.exe HINTS "${_qt_bin_dir}")
    message("Found windeployqt executable: ${WINDEPLOYQT_EXECUTABLE}")
    message("Binary is in: $<TARGET_FILE_DIR:${PROJECT_NAME}>")
    add_custom_command(TARGET ${PROJECT_NAME} COMMAND ${WINDEPLOYQT_EXECUTABLE} "$<TARGET_FILE:${PROJECT_NAME}>")
endif()