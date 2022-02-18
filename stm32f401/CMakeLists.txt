add_executable(firmware.elf main.c keyboard.c driver_i2c.c)
target_link_libraries(firmware.elf lathe)
target_include_directories(firmware.elf PUBLIC .)
target_link_libraries(firmware.elf ${CMAKE_SOURCE_DIR}/libopencm3/lib/libopencm3_stm32f4.a)
target_include_directories(firmware.elf PUBLIC ${CMAKE_SOURCE_DIR}/libopencm3/include)

add_custom_target(firmware.bin ALL arm-none-eabi-objcopy -R .eeprom -O binary firmware.elf firmware.bin DEPENDS firmware.elf)
add_custom_target(flash openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg
                    -c \"init\; reset halt\; flash write_image erase firmware.bin 0x08000000 bin\; reset\; exit\" DEPENDS firmware.bin)
