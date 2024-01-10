cmake_minimum_required(VERSION 3.20)

project(unit_tests)

enable_testing()

set(PROJECT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../")
set(OUTPUT_TEST_BUILD_DIRECTORY
    "${PROJECT_DIRECTORY}smart_door_lock/build/tests/")

if(DEFINED VALGRIND AND (DEFINED COVERAGE OR DEFINED HTML_COVERAGE))
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g --coverage")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g --coverage")
elseif(DEFINED VALGRIND)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
elseif(DEFINED COVERAGE OR DEFINED HTML_COVERAGE)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# build google test together with the project
execute_process(COMMAND ${CMAKE_COMMAND} .
                WORKING_DIRECTORY /root/gtest/googletest)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                WORKING_DIRECTORY /root/gtest/googletest)
add_subdirectory(/root/gtest/googletest /root/gtest/googletest/build
                 EXCLUDE_FROM_ALL)

add_subdirectory(unit_tests)

if(DEFINED COVERAGE OR DEFINED HTML_COVERAGE)

  if(DEFINED HTML_COVERAGE)
    set(COVERAGE_OUTPUT_DIRECTORY "${OUTPUT_TEST_BUILD_DIRECTORY}/coverage")

    file(MAKE_DIRECTORY ${COVERAGE_OUTPUT_DIRECTORY})

    set(GCOVR_ARGUMENTS
        --root=${PROJECT_DIRECTORY}
        --exclude='.*.*
        \.h'
        --exclude-directories=unit_tests/mocks/
        --html
        --html-details
        -o
        ${COVERAGE_OUTPUT_DIRECTORY}/coverage.html
        --print-summary
        |
        tail
        -4
        |
        head
        -3)
  else()
    set(GCOVR_ARGUMENTS
        --root=${PROJECT_DIRECTORY}
        --exclude='.*.*
        \.h'
        --exclude-directories=unit_tests/mocks/
        --print-summary
        |
        tail
        -4
        |
        head
        -3)
  endif()

  add_custom_target(
    coverage
    COMMAND gcovr ${GCOVR_ARGUMENTS}
    DEPENDS unit_tests)

endif()
