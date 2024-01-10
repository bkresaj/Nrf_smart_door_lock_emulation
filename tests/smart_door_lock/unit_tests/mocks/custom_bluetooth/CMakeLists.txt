cmake_minimum_required(VERSION 3.20)
set(INTERNAL_NAME mock_custom_bluetooth)

add_library(${INTERNAL_NAME} custom_bluetooth.cpp)

target_include_directories(${INTERNAL_NAME}
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
