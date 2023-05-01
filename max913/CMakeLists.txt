cmake_minimum_required(VERSION 3.12)

# Create MPC4275 Library
add_library(
    max913 
    rp2040_max913.h
    rp2040_max913.c
)

target_link_libraries(max913 pico_stdlib hardware_gpio hardware_i2c)