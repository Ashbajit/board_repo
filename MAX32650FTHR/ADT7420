/**
 * @file        main.c
 * @brief     Example code for reading temperature from the ADT7420 sensor over I2C
 * @details     This example uses the I2C Master to read temperature data from the
 *              ADT7420 sensor connected to the I2C bus. The sensor is expected
 *              to be at address 0x48.
 */

/***** Includes *****/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "mxc_device.h"
#include "mxc_delay.h"
#include "nvic_table.h"
#include "i2c_regs.h"
#include "i2c.h"

/***** Definitions *****/
#define I2C_MASTER MXC_I2C1 // SDA P2_17; SCL P2_18
#define I2C_FREQ 100000 // 100kHZ
#define ADT7420_ADDR 0x48 // ADT7420 I2C address
#define TEMP_REG 0x00 // Temperature register of ADT7420
#define READ_INTERVAL_MS 1000 // Interval between reads in milliseconds

/***** Globals *****/

// *****************************************************************************
int main()
{
    int error;
    uint8_t temp_data[2];
    int16_t temp_raw;
    float temperature;

    printf("\n******** ADT7420 TEMPERATURE READER *********\n");
    printf("\nThis example continuously reads the temperature from the ADT7420 sensor connected to");
    printf("\nthe I2C bus at address 0x48.\n");

    // Setup the I2C Master
    error = MXC_I2C_Init(I2C_MASTER, 1, 0);
    if (error != E_NO_ERROR) {
        printf("-->Failed master, err:%d\n", error);
        return -1;
    } else {
        printf("\n-->I2C Master Initialization Complete\n");
    }

    MXC_I2C_SetFrequency(I2C_MASTER, I2C_FREQ);

    while (1) {
        // Read temperature from ADT7420
        printf("-->Reading temperature...\n");

        // Set up the request to write the register address
        uint8_t reg_addr = TEMP_REG; // Use an array to hold the register address
        mxc_i2c_req_t reqMaster;
        reqMaster.i2c = I2C_MASTER;
        reqMaster.addr = ADT7420_ADDR;
        reqMaster.tx_buf = &reg_addr;
        reqMaster.tx_len = 1;
        reqMaster.rx_buf = NULL;
        reqMaster.rx_len = 0;
        reqMaster.restart = 1; // Restart to read from the same address
        reqMaster.callback = NULL;

        if (MXC_I2C_MasterTransaction(&reqMaster) != 0) {
            printf("-->Failed to write register address\n");
            return -1;
        }

        // Set up the request to read the temperature data
        reqMaster.tx_buf = NULL;
        reqMaster.tx_len = 0;
        reqMaster.rx_buf = temp_data;
        reqMaster.rx_len = 2;
        reqMaster.restart = 0; // No restart needed

        if (MXC_I2C_MasterTransaction(&reqMaster) != 0) {
            printf("-->Failed to read temperature data\n");
            return -1;
        }

        // Convert raw data to temperature in Celsius
        // ADT7420 uses 13-bit signed data.
        temp_raw = (temp_data[0] << 8) | temp_data[1];
        if (temp_raw & 0x8000) { // Check if negative
            temp_raw |= 0xFFFF0000; // Sign-extend to 32 bits
        }
        temperature = temp_raw * 0.0078125; // ADT7420 conversion factor

        printf("Temperature: %.2f degree C\n", temperature);

        // Wait before the next read
        MXC_Delay(MXC_DELAY_MSEC(READ_INTERVAL_MS));
    }

    return 0;
}
