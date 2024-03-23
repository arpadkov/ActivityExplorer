# Tools

set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

target_sources(ActivityExplorer PRIVATE
    "${dir}/ErrorDialog.h"
    "${dir}/ErrorDetail.h"
    "${dir}/error_dialog.cpp"
    "${dir}/error_dialog.ui"
    "${dir}/error_detail.cpp"
)