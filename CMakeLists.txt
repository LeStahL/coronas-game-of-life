cmake_minimum_required(VERSION 3.14)

project(coronas-game-of-life)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Widgets Gui)
find_package(Git QUIET)

# Find sources and resources
file(GLOB IMAGE_ASSETS_FILENAMES "${PROJECT_SOURCE_DIR}/assets/images/**.png")
file(GLOB MAP_ASSETS_FILENAMES "${PROJECT_SOURCE_DIR}/assets/maps/**.json")
aux_source_directory("${PROJECT_SOURCE_DIR}/src" ${PROJECT_NAME}_SOURCES)

# Compile auto-generated resource file
foreach(IMAGE_ASSET ${IMAGE_ASSETS_FILENAMES})
    message("Added image asset: ${IMAGE_ASSET}")
    set(IMAGE_ASSETS "${IMAGE_ASSETS} <file>${IMAGE_ASSET}</file>\n\t")
endforeach()
foreach(MAP_ASSET ${MAP_ASSETS_FILENAMES})
    message("Added map asset: ${MAP_ASSET}")
    set(MAP_ASSETS "${MAP_ASSETS} <file>${MAP_ASSET}</file>\n\t")
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
)
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})