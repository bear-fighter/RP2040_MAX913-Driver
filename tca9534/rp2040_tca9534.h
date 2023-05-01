#ifndef RP2040_TCA9534_H
#define RP2040_TCA9534_H

#define TCA9534_ADDR 0b00100000 // A0, A1, A2 pulled low

#define TCA9534_INPUT_CMD   0b00
#define TCA9534_OUTPUT_CMD  0b01
#define TCA9534_POLINV_CMD  0b10
#define TCA9534_CONFIG_CMD  0b11

typedef struct tca9534 {
    uint8_t addr;
    uint8_t input_reg;
    uint8_t output_reg;
    uint8_t polinv_reg;
    uint8_t config_reg;
} tca9534;


#endif