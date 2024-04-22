# Widgets

set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

# Create ToolsLib as a static library
target_sources(ActivityExplorer PRIVATE
	"${dir}/ActivityOverviewWidget.h" "${dir}/activity_overview_widget.cpp"  "${dir}/activity_overview_widget.ui" 
)

target_include_directories(ActivityExplorer PUBLIC ${dir})
