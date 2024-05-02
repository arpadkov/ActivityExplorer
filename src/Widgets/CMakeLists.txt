# Widgets

set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

# Sources for Widgets
target_sources(ActivityExplorer PRIVATE
	"${dir}/ActivityOverviewWidget.h" "${dir}/activity_overview_widget.cpp"  "${dir}/activity_overview_widget.ui" 
	"${dir}/ActivityCollectionChart.h" "${dir}/activity_collection_chart.cpp"
	"${dir}/ActivityFilterWidget.h" "${dir}/activity_filter_widget.cpp"
	"${dir}/ActivityCollectionChartConfig.h" "${dir}/activity_collection_chart_config.cpp"
	"${dir}/ButtonGroupWidget.h" "${dir}/button_group_widget.cpp"
)

target_include_directories(ActivityExplorer PUBLIC ${dir})
