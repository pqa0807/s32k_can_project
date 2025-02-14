#include "dbc.h"


/*FUNCTION**********************************************************************
 *
 * Function Name : HondaCRV_WHEEL_SPEEDS
 * Description   : ID: 0x1D0
 *
 *END**************************************************************************/
void HondaCRV_WHEEL_SPEEDS(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract and calculate Front Left (FL) Wheel Speed
    float WheelSpeed_FL = ((((frame.payload[1] & 0xFE) >> 1) | (frame.payload[0] << 7)) * 0.01) - 100;
    sprintf(buffer, "Wheel speed (FL): %s %.2f\n", raw_data, WheelSpeed_FL);
    LPUART1_transmit_string(buffer);

    // Extract and calculate Front Right (FR) Wheel Speed
    float WheelSpeed_FR = ((((frame.payload[1] & 0x01) << 14) | (frame.payload[2] << 6) | ((frame.payload[3] & 0xFC) >> 2)) * 0.01) - 100;
    sprintf(buffer, "Wheel speed (FR): %s %.2f\n", raw_data, WheelSpeed_FR);
    LPUART1_transmit_string(buffer);

    // Extract and calculate Rear Left (RL) Wheel Speed
    float WheelSpeed_RL = ((((frame.payload[3] & 0x03) << 13) | (frame.payload[4] << 5) | ((frame.payload[5] & 0xF8) >> 3)) * 0.01) - 100;
    sprintf(buffer, "Wheel speed (RL): %s %.2f\n", raw_data, WheelSpeed_RL);
    LPUART1_transmit_string(buffer);

    // Extract and calculate Rear Right (RR) Wheel Speed
    float WheelSpeed_RR = ((((frame.payload[5] & 0x07) << 12) | (frame.payload[6] << 4) | ((frame.payload[7] & 0xF0) >> 4)) * 0.01) - 100;
    sprintf(buffer, "Wheel speed (RR): %s %.2f\n", raw_data, WheelSpeed_RR);
    LPUART1_transmit_string(buffer);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : HondaCRV_ENGINE_DATA
 * Description   : ID: 0x158
 *
 *END**************************************************************************/
void HondaCRV_ENGINE_DATA(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract and calculate Engine RPM
    int raw_RPM = (frame.payload[2] << 8) | frame.payload[3];
    sprintf(buffer, "Engine speed: %s %d\n", raw_data, raw_RPM);
    LPUART1_transmit_string(buffer);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : HondaCRV_POWERTRAIN_DATA
 * Description   : ID: 0x17C
 *
 *END**************************************************************************/
void HondaCRV_POWERTRAIN_DATA(standard_frame_t frame)
{
    // char pedal_gas_percentage = (frame.payload[0] * 100) / 255;
    // char pedalGasString[10];
    // sprintf(pedalGasString, "%d", pedal_gas_percentage);
    
    // LPUART1_transmit_string("Pedal Gas: ");
    // LPUART1_transmit_string(pedalGasString);   
    // LPUART1_transmit_char('%'); 
    // LPUART1_transmit_string("\n\r");

    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract and calculate Engine RPM
    float raw_RPM = ((frame.payload[2] << 8) | frame.payload[3]);
    sprintf(buffer, "Engine speed: %s %.2f\n", raw_data, raw_RPM);
    LPUART1_transmit_string(buffer);
}










