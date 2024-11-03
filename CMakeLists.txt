cmake_minimum_required(VERSION 3.29.2)

project(BouncingBall C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

include_directories(include)

file(GLOB SOURCES source/*.c)

foreach(SOURCE ${SOURCES})
  if (NOT ${SOURCE} MATCHES main.c)
    get_filename_component(LIBRARY ${SOURCE} NAME_WE)

    add_library(${LIBRARY} SHARED ${SOURCE})
  endif()
endforeach(SOURCE)

add_executable(${PROJECT_NAME} source/main.c ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
