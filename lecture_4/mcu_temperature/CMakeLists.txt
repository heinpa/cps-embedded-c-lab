add_executable(mcu_temperature)

file(GLOB_RECURSE SRC 
    ${CMAKE_CURRENT_LIST_DIR}/*.c
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)
target_sources(mcu_temperature PRIVATE ${SRC})
target_link_libraries(mcu_temperature
    pico_stdlib
    hardware_i2c
    hardware_adc
    ssd1306
)

pico_enable_stdio_usb(mcu_temperature 1)
pico_enable_stdio_uart(mcu_temperature 0)
pico_add_extra_outputs(mcu_temperature)