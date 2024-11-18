add_executable(increase)

file(GLOB_RECURSE SRC 
    ${CMAKE_CURRENT_LIST_DIR}/*.c
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)
target_sources(increase PRIVATE ${SRC})
target_include_directories(increase PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(increase pico_stdlib)

pico_enable_stdio_usb(increase 1)
pico_enable_stdio_uart(increase 0)
pico_add_extra_outputs(increase)
