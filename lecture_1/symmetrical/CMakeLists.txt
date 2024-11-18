add_executable(symmetrical)

file(GLOB_RECURSE SRC 
    ${CMAKE_CURRENT_LIST_DIR}/*.c
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)
target_sources(symmetrical PRIVATE ${SRC})
target_include_directories(symmetrical PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(symmetrical pico_stdlib)

pico_enable_stdio_usb(symmetrical 1)
pico_enable_stdio_uart(symmetrical 0)
pico_add_extra_outputs(symmetrical)
