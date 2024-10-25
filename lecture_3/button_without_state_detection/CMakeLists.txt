add_executable(button_without_state_detection)

file(GLOB_RECURSE SRC 
    ${CMAKE_CURRENT_LIST_DIR}/*.c
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)
target_sources(button_without_state_detection PRIVATE ${SRC})
target_include_directories(button_without_state_detection PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(button_without_state_detection pico_stdlib)

pico_enable_stdio_usb(button_without_state_detection 1)
pico_enable_stdio_uart(button_without_state_detection 0)
pico_add_extra_outputs(button_without_state_detection)