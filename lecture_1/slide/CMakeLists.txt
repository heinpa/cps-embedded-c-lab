add_executable(slide)

file(GLOB_RECURSE SRC 
    ${CMAKE_CURRENT_LIST_DIR}/*.c
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)
target_sources(slide PRIVATE ${SRC})
target_include_directories(slide PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(slide pico_stdlib)

pico_enable_stdio_usb(slide 1)
pico_enable_stdio_uart(slide 0)
pico_add_extra_outputs(slide)
