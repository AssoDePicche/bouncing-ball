cmake_minimum_required(VERSION 3.29.2)

project(BouncingBall C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(DOWNLOAD_EXTRACT_TIMESTAMP TRUE)

set(BUILD_EXAMPLES OFF CACHE BOOL "Don't build raylib examples")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build raylib as a static library")

cmake_policy(SET CMP0135 NEW)

include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 4.5.0
  SOURCE_DIR ./third_party/raylib
)

FetchContent_MakeAvailable(raylib)

file(GLOB SOURCES ./source/*.c)

list(REMOVE_ITEM SOURCES ./source/main.c)

add_executable(${PROJECT_NAME} ./source/main.c ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ./include)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror -fPIC -DALLOWLOGS)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
