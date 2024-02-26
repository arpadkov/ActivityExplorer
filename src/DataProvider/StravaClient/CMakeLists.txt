# StravaClient

set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

target_sources(ActivityExplorer PRIVATE
    "${dir}/StravaClient.h" "${dir}/strava_client.cpp"
    "${dir}/StravaSetupWidget.h" "${dir}/strava_setup_widget.cpp" "${dir}/strava_setup_widget.ui"
)