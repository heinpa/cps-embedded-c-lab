add_executable(button_states_advanced)

file(GLOB_RECURSE SRC 
    ${CMAKE_CURRENT_LIST_DIR}/*.c
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)
target_sources(button_states_advanced PRIVATE ${SRC})
target_include_directories(button_states_advanced PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(button_states_advanced pico_stdlib)

pico_enable_stdio_usb(button_states_advanced 1)
pico_enable_stdio_uart(button_states_advanced 0)
pico_add_extra_outputs(button_states_advanced)