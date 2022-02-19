add_library(display STATIC display.c font.c)
target_link_libraries(display ssd1306)
target_include_directories(display PUBLIC .)
