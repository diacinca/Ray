cmake_minimum_required(VERSION 3.16)

project(BoatPerformanceChart VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick OpenGL)

qt_standard_project_setup()

qt_add_executable(BoatPerformanceChart
    src/main.cpp
)

qt_add_qml_module(BoatPerformanceChart
    URI BoatPerformanceChart
    VERSION 1.0
    QML_FILES
        qml/main.qml
        qml/PerformanceChart.qml
    SOURCES
        src/chartdatamodel.h
        src/chartdatamodel.cpp
        src/chartrenderer.h
        src/chartrenderer.cpp
        RESOURCES QML.qrc
)

target_link_libraries(BoatPerformanceChart PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::OpenGL
)

set_target_properties(BoatPerformanceChart PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Set the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT BoatPerformanceChart)
