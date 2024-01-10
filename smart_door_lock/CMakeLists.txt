cmake_minimum_required(VERSION 3.20)

set(BOARD nrf52840dk_nrf52840)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(smart_door_lock)

target_sources(app PRIVATE src/main.c)

zephyr_library_include_directories(
  src/board src/custom_bluetooth src/file_system src/littlefs_file_system
  src/nfc src/nvs_file_system)

add_subdirectory(src/board)
add_subdirectory(src/custom_bluetooth)
add_subdirectory(src/file_system)
add_subdirectory(src/littlefs_file_system)
add_subdirectory(src/nfc)
add_subdirectory(src/nvs_file_system)
