add_executable(denoised_button)

file(GLOB_RECURSE SRC 
    ${CMAKE_CURRENT_LIST_DIR}/*.c
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)
target_sources(denoised_button PRIVATE ${SRC})
target_include_directories(denoised_button PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(denoised_button pico_stdlib)

pico_enable_stdio_usb(denoised_button 1)
pico_enable_stdio_uart(denoised_button 0)
pico_add_extra_outputs(denoised_button)