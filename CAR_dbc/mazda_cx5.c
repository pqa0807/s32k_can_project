#include "dbc.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : MazdaCX5_Decode
 * Description   : 
 *
 *END**************************************************************************/
void MazdaCX5_Decode(void) {
    for(uint8_t mbIdx = 0; mbIdx < 16; mbIdx++)
    {
        if((CAN0->IFLAG1) & (1 << mbIdx))
        {
            standard_frame_t frame;
            FlexCAN_receive_frame (CAN0, &frame, mbIdx );
            switch(frame.ID)
            {
                case MazdaCX5_ENGINE_DATA_ID:
                    MazdaCX5_ENGINE_DATA(frame);
                    break;
                case MazdaCX5_WHEEL_SPEED_ID:
                    MazdaCX5_WHEEL_SPEED(frame);
                    break;
                case MazdaCX5_TURN_SWITCH_ID:
                    MazdaCX5_TURN_SWITCH(frame);
                    break;
                default:
                    LPUART1_transmit_string("Invalid frame ID\n");
                    break;
            }
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MazdaCX5_Config_RxMB
 * Description   : 
 *
 *END**************************************************************************/
void MazdaCX5_Config_RxMB(void) {
    FlexCAN_Config_RxMB(CAN0, MazdaCX5_ENGINE_DATA_ID, MB0 );
    FlexCAN_Config_RxMB(CAN0, MazdaCX5_WHEEL_SPEED_ID, MB1 );
    FlexCAN_Config_RxMB(CAN0, MazdaCX5_TURN_SWITCH_ID, MB2 );
}


/*FUNCTION**********************************************************************
 *
 * Function Name : MazdaCX5_ENGINE_DATA
 * Description   : ID: 0x202
 *
 *END**************************************************************************/
void MazdaCX5_ENGINE_DATA(standard_frame_t frame) {
    char buffer[50]; // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract and calculate Engine RPM
    int raw_RPM = (frame.payload[0] << 8) | frame.payload[1];
    float RPM = raw_RPM * 0.25;  // Apply scaling factor (0.25)
    sprintf(buffer, "Engine speed: %s %.2f\n", raw_data, RPM);
    LPUART1_transmit_string(buffer);

    // Extract and calculate Vehicle Speed
    int raw_SPEED = (frame.payload[2] << 8) | frame.payload[3];
    float SPEED = raw_SPEED * 0.01;  // Apply scaling factor (0.01)
    sprintf(buffer, "Vehicle speed: %s %.2f\n", raw_data, SPEED);
    LPUART1_transmit_string(buffer);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : MazdaCX5_WHEEL_SPEED
 * Description   : ID: 0x215
 *
 *END**************************************************************************/
void MazdaCX5_WHEEL_SPEED(standard_frame_t frame) {
    char speedBuffer[50];  // Buffer for formatted output
    char raw_data[30];     // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract and calculate Front Left (FL) Wheel Speed
    int raw_FL = (frame.payload[0] << 8) + frame.payload[1];
    float FL_speed = raw_FL * 0.01 - 100;
    sprintf(speedBuffer, "Wheel speed (FL): %s %.2f\n", raw_data, FL_speed);
    LPUART1_transmit_string(speedBuffer);

    // Extract and calculate Front Right (FR) Wheel Speed
    int raw_FR = (frame.payload[2] << 8) + frame.payload[3];
    float FR_speed = raw_FR * 0.01 - 100;
    sprintf(speedBuffer, "Wheel speed (FR): %s %.2f\n", raw_data, FR_speed);
    LPUART1_transmit_string(speedBuffer);

    // Extract and calculate Rear Left (RL) Wheel Speed
    int raw_RL = (frame.payload[4] << 8) + frame.payload[5];
    float RL_speed = raw_RL * 0.01 - 100;
    sprintf(speedBuffer, "Wheel speed (RL): %s %.2f\n", raw_data, RL_speed);
    LPUART1_transmit_string(speedBuffer);

    // Extract and calculate Rear Right (RR) Wheel Speed
    int raw_RR = (frame.payload[6] << 8) + frame.payload[7];
    float RR_speed = raw_RR * 0.01 - 100;
    sprintf(speedBuffer, "Wheel speed (RR): %s %.2f\n", raw_data, RR_speed);
    LPUART1_transmit_string(speedBuffer);
}




/*FUNCTION**********************************************************************
 *
 * Function Name : MazdaCX5_TURN_SWITCH
 * Description   : ID: 0x91
 *
 *END**************************************************************************/
void MazdaCX5_TURN_SWITCH(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as a hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract and check Hazard Switch state
    char HazardSwitch = (frame.payload[1] & (1 << 2));
    sprintf(buffer, "Hazard : %s %s\n", raw_data, HazardSwitch ? "ON" : "OFF");
    LPUART1_transmit_string(buffer);

    // Extract and check Right Turn Switch state
    char RightTurnSwitch = (frame.payload[1] & (1 << 4));
    sprintf(buffer, "Right turn switch: %s %s\n", raw_data, RightTurnSwitch ? "ON" : "OFF");
    LPUART1_transmit_string(buffer);

    // Extract and check Left Turn Switch state
    char LeftTurnSwitch = (frame.payload[1] & (1 << 5));
    sprintf(buffer, "Left turn switch: %s %s\n", raw_data, LeftTurnSwitch ? "ON" : "OFF");
    LPUART1_transmit_string(buffer);
}


