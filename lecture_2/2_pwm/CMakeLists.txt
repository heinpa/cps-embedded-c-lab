add_executable(pwm)

file(GLOB_RECURSE SRC 
    ${CMAKE_CURRENT_LIST_DIR}/*.c
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)
target_sources(pwm PRIVATE ${SRC})
target_include_directories(pwm PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(pwm pico_stdlib hardware_pwm)

pico_enable_stdio_usb(pwm 1)
pico_enable_stdio_uart(pwm 0)
pico_add_extra_outputs(pwm)