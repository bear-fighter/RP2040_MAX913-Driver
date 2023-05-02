#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "rp2040_tca9534.h"

static uint8_t read(TCA9534* dev, uint8_t cmd_byte, uint8_t* recmsg) {
    if (i2c_write_timeout_us(dev->chan, dev->addr, &cmd_byte, 1, false, TCA9534_I2C_TIMEOUT) < 1) return 0;
    if (i2c_read_timeout_us(dev->chan, dev->addr, recmsg, 1, false, TCA9534_I2C_TIMEOUT) < 1) return 0;

    return 1;
}

static uint8_t write(TCA9534* dev, uint8_t cmd_byte, uint8_t data_byte) {
    uint8_t msg[2] = {cmd_byte, data_byte};

    return (i2c_write_timeout_us(dev->chan, dev->addr, msg, 2, false, TCA9534_I2C_TIMEOUT)  > 0);
}

// Intializes TCA9534 Object
// *DOES NOT* populate register fields; Need to call register read function
TCA9534 tca9534_Init(uint8_t addr, i2c_inst_t* chan) {
    TCA9534 dev = {.addr = addr, .chan = chan};

    return dev;
}

uint8_t tca9534_ReadRegister(TCA9534* dev, eTCA9534Register tca_reg) {
    uint8_t regval;
    
    if (read(dev, (uint8_t) tca_reg, &regval) != 1) return 0;

}

uint8_t tca9534_WriteRegister(TCA9534* dev, eTCA9534Register tca_reg, uint8_t bitmask, uint8_t bitvals) {
    uint8_t regval;
    uint8_t newregval;

    if (read(dev, (uint8_t) tca_reg, &regval) != 1) return 0;

    newregval = regval & ~bitmask;
    newregval |= bitmask & bitvals;

    if (write(dev, (uint8_t) tca_reg, newregval) != 1) return 0;

    if (read(dev, (uint8_t) tca_reg, &regval) != 1) return 0;

    if ( ((uint8_t) regval == newregval) != 1) return 0;

    switch (tca_reg)
    {
    case InputPort:
        dev->input_reg = regval;
        break;

    case OutputPort:
        dev->output_reg = regval;
        break;

    case PolInv:
        dev->polinv_reg = regval;
        break;

    case Config:
        dev->config_reg = regval;
        break;
    
    default:
        return 0;
        break;
    }

    return 1;
}