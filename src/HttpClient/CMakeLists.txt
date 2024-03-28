# HttpClient


set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

# Create HttpClientLib as a static library
add_library(HttpClient STATIC
    "${dir}/HttpClient.h" "${dir}/http_client.cpp"
    "${dir}/NetworkReply.h" "${dir}/network_reply.cpp"
    "${dir}/NetworkRequest.h" "${dir}/network_request.cpp"
)

target_link_libraries(HttpClient PUBLIC
    Qt6::Core
    Qt6::Network
    Tools
)

target_include_directories(HttpClient PUBLIC ${dir})

add_test_with_linked_libs(test_http_client HttpClient)

