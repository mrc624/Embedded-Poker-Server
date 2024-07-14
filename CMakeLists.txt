cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(mongoose)
pico_sdk_init()
add_executable(mongoose hal.c main.c mongoose.c mongoose_fs.c mongoose_glue.c mongoose_impl.c)
target_include_directories(mongoose PUBLIC .)

target_link_libraries(mongoose pico_stdlib hardware_spi pico_rand)
pico_add_extra_outputs(mongoose)     # create map/bin/hex file etc.

pico_enable_stdio_usb(mongoose 1)    # Route stdio

