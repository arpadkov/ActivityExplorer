# DataProvider

set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

# Create DataProvider as a static library
add_library(DataProvider STATIC
    "${dir}/DataProvider.h"
    "${dir}/data_provider.cpp"
    "${dir}/DlgSetupDataProvider.h"
    "${dir}/dlg_setup_data_provider.cpp"
    "${dir}/setup_data_provider.ui"
)

target_link_libraries(DataProvider PUBLIC
    Qt6::Core
    Tools
)

target_include_directories(DataProvider PUBLIC ${dir})

add_subdirectory(StravaClient)
add_subdirectory(LocalFilesProvider)