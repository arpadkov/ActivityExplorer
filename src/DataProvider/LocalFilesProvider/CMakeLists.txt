# LocalFilesProvider

set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

target_sources(DataProvider PRIVATE
    "${dir}/LocalFilesProvider.h"
    "${dir}/local_files_provider.cpp"
)