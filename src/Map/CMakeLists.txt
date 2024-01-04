# Map

set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

add_qml_files(
   "Map/MapView.qml"
   "Map/MapComponent.qml"
)

target_sources(ActivityExplorer PRIVATE
    "${dir}/MapviewWindow.h"
    "${dir}/mapview_window.cpp"
    "${dir}/mapview_window.ui"
)


