cmake_minimum_required(VERSION 3.20)
set(INTERNAL_NAME mock_dk_buttons_and_leds)

add_library(${INTERNAL_NAME} mock_dk_buttons_and_leds.cpp)

target_link_libraries(${INTERNAL_NAME} PUBLIC gmock singleton_template
                                              zephyr_headers)

target_include_directories(${INTERNAL_NAME}
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
