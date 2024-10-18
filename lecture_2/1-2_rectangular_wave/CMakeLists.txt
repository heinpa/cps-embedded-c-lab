add_executable(rectangular_wave)

file(GLOB_RECURSE SRC 
    ${CMAKE_CURRENT_LIST_DIR}/*.c
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)
target_sources(rectangular_wave PRIVATE ${SRC})
target_include_directories(rectangular_wave PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(rectangular_wave pico_stdlib)

pico_enable_stdio_usb(rectangular_wave 1)
pico_enable_stdio_uart(rectangular_wave 0)
pico_add_extra_outputs(rectangular_wave)