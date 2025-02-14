#include "dbc.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : Honda_Decode
 * Description   : 
 *
 *END**************************************************************************/
void HondaCivic_Decode(void){
    for(uint8_t mbIdx = 0; mbIdx < 16; mbIdx++)
    {
        if((CAN0->IFLAG1) & (1 << mbIdx))
        {
            standard_frame_t frame;
            FlexCAN_receive_frame (CAN0, &frame, mbIdx );
            switch(frame.ID)
            {
                case HondaCivic_POWERTRAIN_DATA_ID:
                    HondaCivic_POWERTRAIN_DATA(frame);
                    break;
                case HondaCivic_CARSPEED_ID:
                    HondaCivic_CARSPEED(frame);
                    break;
                case HondaCRV_WHEEL_SPEEDS_ID:
                    HondaCRV_WHEEL_SPEEDS(frame);
                    break;
                case HondaCivic_SCM_FEEDBACK_ID:
                    HondaCivic_SCM_FEEDBACK(frame);
                    break;
                case HondaCivic_GEARBOX_ID:
                    HondaCivic_GEARBOX(frame);
                    break;
                case HondaCivic_LIGHT_ID:
                    HondaCivic_LIGHT(frame);
                    break;
                default:
                    break;
            }
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HondaCivic_Config_RxMB
 * Description   : 
 *
 *END**************************************************************************/
void HondaCivic_Config_RxMB(void) {
    FlexCAN_Config_RxMB(CAN0, HondaCivic_POWERTRAIN_DATA_ID, MB0 );
    FlexCAN_Config_RxMB(CAN0, HondaCivic_CARSPEED_ID, MB1 );
    FlexCAN_Config_RxMB(CAN0, HondaCRV_WHEEL_SPEEDS_ID, MB2 );
    FlexCAN_Config_RxMB(CAN0, HondaCivic_SCM_FEEDBACK_ID, MB3 );
    FlexCAN_Config_RxMB(CAN0, HondaCivic_GEARBOX_ID, MB4 );
    FlexCAN_Config_RxMB(CAN0, HondaCivic_LIGHT_ID, MB5 );
}


/*FUNCTION**********************************************************************
 *
 * Function Name : HondaCivic_POWERTRAIN_DATA
 * Description   : ID: 0x17C
 *
 *END**************************************************************************/
void HondaCivic_POWERTRAIN_DATA(standard_frame_t frame)
{
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


/*FUNCTION**********************************************************************
 *
 * Function Name : HondaCivic_CARSPEED
 * Description   : ID: 0x309
 *
 *END**************************************************************************/
void HondaCivic_CARSPEED(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract and calculate vehicle speed
    int raw_speed = (frame.payload[0] << 8) | frame.payload[1];
    
    if (raw_speed) {
        // Separate integer and fractional parts
        int whole_part = raw_speed / 100;   // Integer part
        int decimal_part = raw_speed % 100; // Two decimal places

        // Format the speed with a decimal point
        sprintf(buffer, "Vehicle speed: %s %d.%02d\n", raw_data, whole_part, decimal_part);
    } else {
        // Handle case where speed is 0
        sprintf(buffer, "Vehicle speed: %s 0.00\n", raw_data);
    }

    // Transmit the formatted string
    LPUART1_transmit_string(buffer);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : HondaCivic_GEARBOX
 * Description   : ID: 0x188
 *
 *END**************************************************************************/
void HondaCivic_GEARBOX(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract GEAR_SHIFTER value (bits 29–34)
    int raw_gear = (frame.payload[3]) ;

    // Decode GEAR_SHIFTER value
    const char *gear_state;
    switch (raw_gear) {
        case 0x80:  gear_state = "1";  break;  // 1st gear
        case 0x20:  gear_state = "D3"; break;  // 3rd gear
        case 8:     gear_state = "D";  break;  // Drive
        case 4:     gear_state = "N";  break;  // Neutral
        case 2:     gear_state = "R";  break;  // Reverse
        case 1:     gear_state = "P";  break;  // Park
        default:    gear_state = "INVALID"; break;  // Undefined
    }

    // Format and transmit gear state
    sprintf(buffer, "Gear: %s %s\n", raw_data, gear_state);
    LPUART1_transmit_string(buffer);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : HondaCivic_LIGHT
 * Description   : ID: 0x164
 *
 *END**************************************************************************/
void HondaCivic_LIGHT(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    int raw_light = (frame.payload[0]);
    const char *light_state;
    switch (raw_light) {
        case 0: light_state = "OFF"; break;
        case 1: light_state = "Low_Beam"; break;
        case 2: light_state = "High_Beam"; break;
        case 3: light_state = "Flashing"; break;
        default: light_state = "UNKNOWN"; break;
    }

    // Format and transmit light state
    sprintf(buffer, "Light: %s %s\n", raw_data, light_state);
    LPUART1_transmit_string(buffer);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : HondaCivic_SCM_FEEDBACK
 * Description   : ID: 0x294
 *
 *END**************************************************************************/
void HondaCivic_SCM_FEEDBACK(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract RIGHT_BLINKER state (bit 6)
    char right_blinker = (frame.payload[0] >> 6) & 0x01;

    // Extract LEFT_BLINKER state (bit 5)
    char left_blinker = (frame.payload[0] >> 5) & 0x01;

    // Extract WIPERS_SPEED state (bits 4-3)
    char wipers_speed = (frame.payload[0] >> 3) & 0x03;

    // Decode WIPERS_SPEED value
    const char *wiper_state;
    switch (wipers_speed) {
        case 0: wiper_state = "Off"; break;
        case 1: wiper_state = "INT"; break;
        case 2: wiper_state = "Low"; break;
        case 3: wiper_state = "High"; break;
        default: wiper_state = "Unknown"; break;
    }

    // Transmit RIGHT_BLINKER state
    sprintf(buffer, "Right turn switch: %s %s\n", raw_data, right_blinker ? "ON" : "OFF");
    LPUART1_transmit_string(buffer);

    // Transmit LEFT_BLINKER state
    sprintf(buffer, "Left turn switch: %s %s\n", raw_data, left_blinker ? "ON" : "OFF");
    LPUART1_transmit_string(buffer);

    // Transmit WIPERS_SPEED state
    sprintf(buffer, "Wiper speed: %s %s\n", raw_data, wiper_state);
    LPUART1_transmit_string(buffer);
}


