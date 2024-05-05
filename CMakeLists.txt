# ActivityExplorer

cmake_minimum_required(VERSION 3.5)

project(ActivityExplorer VERSION 0.1 LANGUAGES CXX)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

# Enable C++ exception handling
add_compile_options(/EHsc)

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts WebEngineWidgets LinguistTools Core Gui Qml Network Quick Positioning Location)


# Setup GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
enable_testing()

# define macro to add tests
macro(add_test_with_linked_libs TEST_NAME)
    add_executable(${TEST_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/tests/${TEST_NAME}.cpp)
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${TEST_NAME}
    GTest::gtest_main
    GTest::gtest
    GTest::gmock_main
    GTest::gmock
    Qt6::Widgets
    ${ARGN}
    )
    gtest_discover_tests(${TEST_NAME} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tests")
endmacro()

include_directories(src)

add_subdirectory(
    src
)

set(TS_FILES
    ActivityExplorer_en_US.ts
)

qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

set_target_properties(ActivityExplorer PROPERTIES
    WIN32_EXECUTABLE TRUE
)


include(GNUInstallDirs)
install(TARGETS ActivityExplorer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ActivityExplorer)
endif()
