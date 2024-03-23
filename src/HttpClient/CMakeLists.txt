# HttpClient

set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

target_sources(ActivityExplorer PRIVATE
    "${dir}/HttpClient.h" "${dir}/http_client.cpp"
    "${dir}/NetworkReply.h" "${dir}/network_reply.cpp"
    "${dir}/NetworkRequest.h" "${dir}/network_request.cpp"
)