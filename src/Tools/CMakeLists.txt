# Tools

set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

# Create ToolsLib as a static library
add_library(Tools STATIC
    "${dir}/ErrorDialog.h"
    "${dir}/ErrorDetail.h"
    "${dir}/error_dialog.cpp"
    "${dir}/error_dialog.ui"
    "${dir}/error_detail.cpp"
)

target_link_libraries(Tools PUBLIC
    Qt6::Core
)

target_include_directories(Tools PUBLIC ${dir})
