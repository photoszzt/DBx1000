cmake_minimum_required(VERSION 2.8)
project(Dbx1000)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET (CMAKE_CXX_FLAGS "-Wno-deprecated-declarations" CACHE INTERNAL "compiler options" FORCE)
SET (CMAKE_CXX_FLAGS_DEBUG "-O0 -g" CACHE INTERNAL "compiler options" FORCE)
SET (CMAKE_CXX_FLAGS_RELEASE "-O3" CACHE INTERNAL "compiler options" FORCE)

add_definitions(-DNOGRAPHITE=1)

# include header files
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/benchmarks/ ${PROJECT_SOURCE_DIR}/concurrency_control/ ${PROJECT_SOURCE_DIR}/storage/ ${PROJECT_SOURCE_DIR}/system/)
# lib files
#LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs)
file(GLOB_RECURSE SRC_FILES benchmarks/*.cpp concurrency_control/*.cpp storage/*.cpp system/*.cpp config.cpp)
add_executable(rundb ${SRC_FILES})
find_package(PkgConfig REQUIRED)
pkg_check_modules (JEMALLOC jemalloc)

pkg_search_module(JEMALLOC REQUIRED jemalloc)
include_directories(${JEMALLOC_INCLUDE_DIRS})
target_link_libraries(rundb ${JEMALLOC_LIBRARIES})
