# HttpClient

set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

target_sources(ActivityExplorer PRIVATE
    "${dir}/HttpClient.h" "${dir}/http_client.cpp"
)