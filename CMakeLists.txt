project(lathe)
cmake_minimum_required(VERSION 3.0)

#set(PLATFORM "atmega328p")
set(PLATFORM "stm32f401")


if (${PLATFORM} STREQUAL "atmega328p")
	set(F_CPU 16000000UL)
	set(MCU atmega328p)
	set(PROGRAM_PORT "/dev/ttyUSB0")

	set(CMAKE_SYSTEM_NAME Generic)
	set(CMAKE_CXX_COMPILER avr-g++)
	set(CMAKE_C_COMPILER avr-gcc)
	set(CMAKE_ASM_COMPILER avr-gcc)

	add_definitions(-DF_CPU=${F_CPU})

	set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})
	SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)

	add_compile_options(-mmcu=${MCU})
elseif(${PLATFORM} STREQUAL "stm32f401")
	set(CMAKE_C_COMPILER arm-none-eabi-gcc)
	set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
	set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
	set(CMAKE_C_FLAGS_DEBUG "-O0 -ggdb")
	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")

	set(ARCH_CFG -march=armv7e-m+fp -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16)

	add_compile_options(-fdata-sections -ffunction-sections ${ARCH_CFG})
	add_link_options(${ARCH_CFG} -T ${CMAKE_SOURCE_DIR}/stm32f401/stm32.ld -Wl,--gc-sections --static -nostartfiles -specs=nano.specs -specs=nosys.specs)
	SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)
else()

endif()


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

add_compile_options(
    -std=gnu99 # C99 standard
#    -Os # optimize
    -Wall # enable warnings
    )

add_subdirectory(core)


add_executable(firmware.elf ${PLATFORM}/main.c)
target_link_libraries(firmware.elf lathe)
target_include_directories(firmware.elf PUBLIC .)

if (${PLATFORM} STREQUAL "atmega328p")
	add_custom_target(firmware.bin ALL avr-objcopy -R .eeprom -O binary firmware.elf firmware.bin DEPENDS firmware.elf)
	add_custom_target(flash avrdude -v -patmega328p -carduino -P${PROGRAM_PORT} -D -Uflash:w:firmware.bin DEPENDS firmware.bin)
elseif(${PLATFORM} STREQUAL "stm32f401")
    target_include_directories(firmware.elf PUBLIC libopencm3/include)
	target_link_libraries(firmware.elf ${CMAKE_SOURCE_DIR}/libopencm3/lib/libopencm3_stm32f4.a)

    add_custom_target(firmware.bin ALL arm-none-eabi-objcopy -R .eeprom -O binary firmware.elf firmware.bin DEPENDS firmware.elf)

    add_custom_target(flash openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg
                    -c \"init\; reset halt\; flash write_image erase firmware.bin 0x08000000 bin\; reset\; exit\" DEPENDS firmware.bin)
else()

endif()

