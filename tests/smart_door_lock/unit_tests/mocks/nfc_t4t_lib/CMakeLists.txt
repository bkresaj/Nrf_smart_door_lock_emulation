cmake_minimum_required(VERSION 3.20)
set(INTERNAL_NAME mock_nfc_t4t_lib)

add_library(${INTERNAL_NAME} mock_nfc_t4t_lib.cpp)

target_link_libraries(${INTERNAL_NAME} PUBLIC gmock singleton_template)

target_include_directories(${INTERNAL_NAME}
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
