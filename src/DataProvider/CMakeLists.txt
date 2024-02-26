# DataProvider

set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

target_sources(ActivityExplorer PRIVATE
    "${dir}/DataProvider.h"
    "${dir}/data_provider.cpp"
    "${dir}/DlgSetupDataProvider.h"
    "${dir}/dlg_setup_data_provider.cpp"
    "${dir}/setup_data_provider.ui"
)

add_subdirectory(StravaClient)
add_subdirectory(LocalFilesProvider)