add_executable(rgb_led)

file(GLOB_RECURSE SRC 
    ${CMAKE_CURRENT_LIST_DIR}/*.c
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)
target_sources(rgb_led PRIVATE ${SRC})
target_include_directories(rgb_led PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(rgb_led pico_stdlib hardware_pwm)

pico_enable_stdio_usb(rgb_led 1)
pico_enable_stdio_uart(rgb_led 0)
pico_add_extra_outputs(rgb_led)