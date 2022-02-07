project(lathe)

add_library(lathe STATIC threads.c encoder.c encoder_multiplicator.c control.c)
target_include_directories(lathe PUBLIC ${PROJECT_SOURCE_DIR})

add_executable(firmware.elf main.c)
target_link_libraries(firmware.elf lathe)
target_include_directories(firmware.elf PUBLIC ${PROJECT_SOURCE_DIR})
