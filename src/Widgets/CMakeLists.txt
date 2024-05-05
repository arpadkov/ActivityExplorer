# Widgets

set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

# Create Widgets as a static library
add_library(Widgets STATIC
	"${dir}/ActivityOverviewWidget.h" "${dir}/activity_overview_widget.cpp"  "${dir}/activity_overview_widget.ui" 
	"${dir}/ActivityCollectionChart.h" "${dir}/activity_collection_chart.cpp"
	"${dir}/ActivityFilterWidget.h" "${dir}/activity_filter_widget.cpp"
	"${dir}/ActivityCollectionChartConfig.h" "${dir}/activity_collection_chart_config.cpp"
	"${dir}/ButtonGroupWidget.h" "${dir}/button_group_widget.cpp"
	"${dir}/ActivityOverviewModel.h" "${dir}/activity_overview_model.cpp"
)

target_link_libraries(Widgets PUBLIC
    Qt6::Core
	Qt6::Charts
    Qt6::Widgets
	Tools
	DataProvider
)

add_test_with_linked_libs(test_activity_overview_model Widgets DataProvider)

target_include_directories(Widgets PUBLIC ${dir})
