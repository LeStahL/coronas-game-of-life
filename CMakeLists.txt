cmake_minimum_required(VERSION 3.14)

project(coronas-game-of-life)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Widgets Gui)
find_package(Git QUIET)

# # Make sure all source files are present to avoid obscure compiler errors.
set(${PROJECT_NAME}_SOURCES
    "${PROJECT_SOURCE_DIR}/src/corona.cpp"
)
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