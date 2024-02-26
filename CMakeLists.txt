# ActivityExplorer

cmake_minimum_required(VERSION 3.5)

project(ActivityExplorer VERSION 0.1 LANGUAGES CXX)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets WebEngineWidgets LinguistTools Core Gui Qml Network Quick Positioning Location)

add_subdirectory(
    src
)

set(TS_FILES
    ActivityExplorer_en_US.ts
)

qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

set_target_properties(ActivityExplorer PROPERTIES
    WIN32_EXECUTABLE TRUE
)


include(GNUInstallDirs)
install(TARGETS ActivityExplorer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ActivityExplorer)
endif()
