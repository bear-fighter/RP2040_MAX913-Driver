#include <stdint.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "tca9534/rp2040_tca9534.h"

#define I2C_BAUD 50000

void main(void) {

    TCA9534 dev1;
    volatile uint8_t stat = 0;
    
    stdio_init_all();

    i2c_init(i2c1, I2C_BAUD);

     // Setup I2C GPIO Pins
    gpio_set_function(2, GPIO_FUNC_I2C);
    gpio_set_function(3, GPIO_FUNC_I2C);
    gpio_pull_up(2);
    gpio_pull_up(3);

    dev1 = tca9534_Init(TCA9534_ADDR, i2c1);

    stat = tca9534_WriteRegister(&dev1, Config, 0b11111111, 0b00000110);
    stat = tca9534_WriteRegister(&dev1, OutputPort, 0b1, 0b1);  // Reset Latch
    stat = tca9534_WriteRegister(&dev1, OutputPort, 0b1, 0b0);  // Clear Reset Bit
    stat = tca9534_ReadRegister(&dev1, InputPort);

    printf("OC Reset: &i", dev1.config_reg);

    while(1) {

    }
}