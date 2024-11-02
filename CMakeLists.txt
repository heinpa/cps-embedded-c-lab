cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_FETCH_FROM_GIT Off)
set(PICO_SDK_PATH ${CMAKE_SOURCE_DIR}/lib/pico-sdk)
set(PICO_PLATFORM rp2040)
# set(PICO_PLATFORM rp2350-arm-s)

include(pico_sdk_import.cmake)

project(cps-embedded-c-labs CXX C ASM)
pico_sdk_init()

add_subdirectory(lib)
add_subdirectory(lecture_1)
add_subdirectory(lecture_2)
add_subdirectory(lecture_3)
add_subdirectory(lecture_4)