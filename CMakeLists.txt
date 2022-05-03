cmake_minimum_required(VERSION 3.18)

project(Utilities VERSION 1.0.0 LANGUAGES CXX)

if(MSVC)
  set(UTILITIES_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /EHsc")
else()
  set(UTILITIES_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic)
endif()

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

if(UNIX)
    add_definitions(-DUTILITIES_PLATFORM_LINUX)
elseif(WIN32)
    add_definitions(-DUTILITIES_PLATFORM_WINDOWS)
endif()

file(GLOB_RECURSE UTILITIES_SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
add_library(Utilities OBJECT ${UTILITIES_SOURCE_FILES})
set_target_properties(Utilities PROPERTIES CXX_STANDARD 20 COMPILE_OPTIONS "${CONSOLEUTILS_CXX_FLAGS}")

target_include_directories(Utilities
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(Utilities::Utilities ALIAS Utilities)

option(UTILITIES_BUILD_TESTS "Build Utilities Tests" ON)
if(UTILITIES_BUILD_TESTS)
  enable_testing()
  add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/test/")
endif()

