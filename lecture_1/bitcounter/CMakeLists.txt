add_executable(bitcounter)

file(GLOB_RECURSE SRC 
    ${CMAKE_CURRENT_LIST_DIR}/*.c
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)
target_sources(bitcounter PRIVATE ${SRC})
target_include_directories(bitcounter PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(bitcounter pico_stdlib)

pico_enable_stdio_usb(bitcounter 1)
pico_enable_stdio_uart(bitcounter 0)
pico_add_extra_outputs(bitcounter)
