cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME ut_nvs_file_system)

add_executable(
  ${TARGET_NAME}
  ${PROJECT_DIRECTORY}/smart_door_lock/src/nvs_file_system/nvs_file_system.c
  ut_nvs_file_system.cpp)

if(DEFINED VALGRIND)
  add_test(
    NAME ${TARGET_NAME}
    COMMAND valgrind --leak-check=full # --show-leak-kinds=all
            $<TARGET_FILE:${TARGET_NAME}>
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
else()
  add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
endif()

target_link_libraries(
  ${TARGET_NAME}
  PUBLIC gtest
         gtest_main
         zephyr_headers
         mock_subsys
         mock_fs
         mock_zephyr_kernel
         mock_nfc)

target_include_directories(
  ${TARGET_NAME}
  PRIVATE ${PROJECT_DIRECTORY}/smart_door_lock/src/nvs_file_system)
