# src

qt6_add_executable(ActivityExplorer
    MANUAL_FINALIZATION
    ${TS_FILES}
    main.cpp
    main_window.cpp
    MainWindow.h
    main_window.ui
)

set (QML_SOURCES "")

# This sucks.. works for only level of subdirectory
macro (add_qml_files)
foreach (_qml ${ARGN})
  list(APPEND QML_SOURCES "${_qml}")
  set (QML_SOURCES ${QML_SOURCES} PARENT_SCOPE)
  message("ADDING: ${_qml}")
endforeach()
endmacro()

add_subdirectory(DataProvider)
add_subdirectory(Map)

qt_add_qml_module(ActivityExplorer
    URI QmlForms
    VERSION 1.0
    QML_FILES
      ${QML_SOURCES}
)


target_link_libraries(ActivityExplorer PUBLIC
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
    Qt6::Location
    Qt6::Network
    Qt6::Positioning
    Qt6::Qml
    Qt6::Quick
    #MapView
)






