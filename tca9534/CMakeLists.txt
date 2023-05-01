cmake_minimum_required(VERSION 3.12)

# Create MPC4275 Library
add_library(
    tca9534 
    rp2040_tca9534.h
    rp2040_tca9534.c
)

target_link_libraries(tca9534 pico_stdlib hardware_gpio hardware_i2c)