# StravaClient

set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

target_sources(ActivityExplorer PRIVATE
    "${dir}/stravaclient.h"
    "${dir}/stravaclient.cpp"
)
