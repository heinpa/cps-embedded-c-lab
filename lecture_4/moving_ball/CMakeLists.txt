add_executable(moving_ball)

file(GLOB_RECURSE SRC 
    ${CMAKE_CURRENT_LIST_DIR}/*.c
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)
target_sources(moving_ball PRIVATE ${SRC})
target_link_libraries(moving_ball
    pico_stdlib
    hardware_i2c
    ssd1306
)

pico_enable_stdio_usb(moving_ball 1)
pico_enable_stdio_uart(moving_ball 0)
pico_add_extra_outputs(moving_ball)