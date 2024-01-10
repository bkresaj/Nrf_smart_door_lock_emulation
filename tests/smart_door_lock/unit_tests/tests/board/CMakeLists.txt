cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME ut_board)

add_executable(
  ${TARGET_NAME} ${PROJECT_DIRECTORY}/smart_door_lock/src/board/board.c
                 ut_board.cpp)

if(DEFINED VALGRIND)
  add_test(
    NAME ${TARGET_NAME}
    COMMAND valgrind --leak-check=full # --show-leak-kinds=all
            $<TARGET_FILE:${TARGET_NAME}>
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
else()
  add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
endif()

target_link_libraries(${TARGET_NAME} PUBLIC gtest gtest_main
                                            mock_dk_buttons_and_leds)

target_include_directories(
  ${TARGET_NAME} PRIVATE ${PROJECT_DIRECTORY}/smart_door_lock/src/board)
