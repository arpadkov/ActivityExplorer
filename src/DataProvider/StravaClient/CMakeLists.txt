# StravaClient

set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

target_sources(ActivityExplorer PRIVATE
    "${dir}/StravaClient.h" "${dir}/strava_client.cpp"
    "${dir}/StravaCredentials.h" "${dir}/strava_credentials.cpp"
    "${dir}/StravaSetupWidget.h" "${dir}/strava_setup_widget.cpp" "${dir}/strava_setup_widget.ui"
)

add_test(test_strava_client ${dir})