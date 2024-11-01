add_library(ssd1306 STATIC)

target_sources(ssd1306 PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/ssd1306.c
    ${CMAKE_CURRENT_LIST_DIR}/ssd1306_drawing.c
)
target_include_directories(ssd1306 PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(ssd1306 pico_stdlib hardware_i2c)
