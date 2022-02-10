add_library(lathe STATIC threads.c encoder.c encoder_multiplicator.c control.c interface.c)
target_include_directories(lathe PUBLIC .)

