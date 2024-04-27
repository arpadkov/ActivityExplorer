# StravaClient

set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

# TODO: Make it part of the DataProvider library
target_sources(DataProvider PRIVATE
    "${dir}/StravaClient.h" "${dir}/strava_client.cpp"
    "${dir}/StravaCredentials.h" "${dir}/strava_credentials.cpp"
    "${dir}/StravaActivityConverter.h" "${dir}/strava_activity_converter.cpp"
    "${dir}/StravaSetupWidget.h" "${dir}/strava_setup_widget.cpp" "${dir}/strava_setup_widget.ui"
    "${dir}/StravaActivityReaderThread.h" "${dir}/strava_activity_reader_thread.cpp"
)

add_test_with_linked_libs(test_strava_client DataProvider)