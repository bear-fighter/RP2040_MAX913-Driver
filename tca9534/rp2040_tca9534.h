#ifndef RP2040_TCA9534_H
#define RP2040_TCA9534_H

#define TCA9534_ADDR 0b0100000 // A0, A1, A2 pulled low

#define TCA9534_INPUT_CMD   0b00
#define TCA9534_OUTPUT_CMD  0b01
#define TCA9534_POLINV_CMD  0b10
#define TCA9534_CONFIG_CMD  0b11
#define TCA9534_I2C_TIMEOUT 10000

#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"

typedef struct TCA9534 {
    uint8_t addr;
    i2c_inst_t* chan;
    uint8_t input_reg;
    uint8_t output_reg;
    uint8_t polinv_reg;
    uint8_t config_reg;
} TCA9534;

typedef enum eTCA9534Register {
    InputPort = TCA9534_INPUT_CMD,
    OutputPort = TCA9534_OUTPUT_CMD,
    PolInv = TCA9534_POLINV_CMD,
    Config = TCA9534_CONFIG_CMD
} eTCA9534Register;

// Performs I2C Read Operation for TCA9534
static uint8_t read(TCA9534* dev, uint8_t cmd_byte, uint8_t* recmsg);

// Performs I2C Write Operation for TCA9534
static uint8_t write(TCA9534* dev, uint8_t cmd_byte, uint8_t data_byte);

// Read Input Port Register (Table 4)
// Reads All Inputs, Regardless of Input/Output Configuration
// Updates input_reg field in tca9534 object
// Returns 1 for Sucessful Read; Returns 0 Otherwise
uint8_t tca9534_ReadRegister(TCA9534* dev, eTCA9534Register tca_reg);

// Writes to Specific TCA9534 Register and Updates the corresponding tca9534 Object Field
// Validates write operation by performing subsequent "read" operation to ensure values match
// ^ Ensures write operation has "stuck"
// Returns 1 if read operation matches requested write operation; Returns 0 otherwise
uint8_t tca9534_WriteRegister(TCA9534* dev, eTCA9534Register tca_reg, uint8_t bitmask, uint8_t bitvals);

TCA9534 tca9534_Init(uint8_t addr, i2c_inst_t* chan);

#endif