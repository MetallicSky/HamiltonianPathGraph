cmake_minimum_required(VERSION 3.5)

project(HamiltonianPathGraph VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Add include directory
include_directories(include)

# Explicitly organize sources and headers
set(SRC_FILES
    src/main.cpp
    src/mainwindow.cpp
    src/graph.cpp
    src/coordgraph.cpp
    src/coordgraphbuilder.cpp
    src/graphscene.cpp
)

set(HEADER_FILES
    include/mainwindow.h
    include/graph.h
    include/coordgraph.h
    include/coordgraphbuilder.h
    include/graphscene.h
)

set(UI_FILES
    ui/mainwindow.ui
)

# Add all files to the executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(HamiltonianPathGraph
        MANUAL_FINALIZATION
        ${SRC_FILES}
        ${HEADER_FILES}
        ${UI_FILES}
    )
else()
    add_executable(HamiltonianPathGraph
        ${SRC_FILES}
        ${HEADER_FILES}
        ${UI_FILES}
    )
endif()

# Link Qt libraries
target_link_libraries(HamiltonianPathGraph PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Add logical groups (hide folder structure in IDE)
source_group("Sources" FILES ${SRC_FILES})
source_group("Headers" FILES ${HEADER_FILES})
source_group("UI" FILES ${UI_FILES})

# Set properties
set_target_properties(HamiltonianPathGraph PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(HamiltonianPathGraph)
endif()
