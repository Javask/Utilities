cmake_minimum_required(VERSION 3.18)

project(UtilitiesTests)

include(${CMAKE_CURRENT_LIST_DIR}/../cmake/CPM.cmake)

#add Catch2
CPMAddPackage("gh:catchorg/Catch2@2.13.8")

file(GLOB_RECURSE UTILITIES_TEST_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/*.h"
							   "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

add_executable(UtilitiesTests ${UTILITIES_TEST_FILES})
target_link_libraries(UtilitiesTests $<TARGET_NAME_IF_EXISTS:Catch2::Catch2> Utilities::Utilities)
add_dependencies(UtilitiesTests Utilities::Utilities)
set_target_properties(UtilitiesTests PROPERTIES CXX_STANDARD 20 COMPILE_OPTIONS "${UTILITIES_CXX_FLAGS}")
target_include_directories(UtilitiesTests PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../src" "${CMAKE_CURRENT_LIST_DIR}/../include")


add_test(UtilitiesTests ${EXECUTABLE_OUTPUT_PATH}/UtilitiesTests)