add_executable(square_wave)

file(GLOB_RECURSE SRC 
    ${CMAKE_CURRENT_LIST_DIR}/*.c
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)
target_sources(square_wave PRIVATE ${SRC})
target_include_directories(square_wave PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(square_wave pico_stdlib)

pico_enable_stdio_usb(square_wave 1)
pico_enable_stdio_uart(square_wave 0)
pico_add_extra_outputs(square_wave)