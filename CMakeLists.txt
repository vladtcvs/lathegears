project(lathe)
cmake_minimum_required(VERSION 3.0)

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

add_compile_options(
    -mmcu=${MCU} # MCU
    -std=gnu99 # C99 standard
    -Os # optimize
    -Wall # enable warnings
    )

add_library(lathe STATIC threads.c encoder.c encoder_multiplicator.c control.c)
target_include_directories(lathe PUBLIC ${PROJECT_SOURCE_DIR})

add_executable(firmware.elf main.c)
target_link_libraries(firmware.elf lathe)
target_include_directories(firmware.elf PUBLIC ${PROJECT_SOURCE_DIR})


#add_custom_target(strip ALL avr-strip firmware.elf DEPENDS firmware.elf)
add_custom_target(firmware.bin ALL avr-objcopy -R .eeprom -O binary firmware.elf firmware.bin DEPENDS firmware.elf)

add_custom_target(flash avrdude -v -pm328p -cwiring -P${PROGRAM_PORT} -b115200 -D -Uflash:w:firmware.bin DEPENDS firmware.bin)
