#include "dbc.h"
#include "lpuart.h"
#include "Can.h"


/*FUNCTION**********************************************************************
 *
 * Function Name : HuynhDai_Elantra_Decode
 * Description   : 
 *
 *END**************************************************************************/
void HuynhDai_Elantra_Decode(void) {
    for(uint8_t mbIdx = 0; mbIdx < 1; mbIdx++)
    {
        if((CAN0->IFLAG1) & (1 << mbIdx))
        {
            standard_frame_t frame;
            FlexCAN_receive_frame (CAN0, &frame, mbIdx );
            switch(frame.ID)
            {
                case HuynhDai_Elantra_SIGNAL_ID:
                    HuynhDai_Elantra_Signal(frame);
                    break;
                default:
                    break;
            }
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HuynhDai_Elantra_Config_RxMB
 * Description   : 
 *
 *END**************************************************************************/
void HuynhDai_Elantra_Config_RxMB(void) {
    FlexCAN_Config_RxMB(CAN0, HuynhDai_Elantra_SIGNAL_ID, MB0 );
}


/*FUNCTION**********************************************************************
 *
 * Function Name : HuynhDai_Elantra_signal
 * Description   : ID: 0x541
 *
 *END**************************************************************************/
void HuynhDai_Elantra_Signal(standard_frame_t frame){
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    //Left Turn signal
    char LeftTurnSwitch = (frame.payload[2] & (1 << 3));
    sprintf(buffer, "Left turn switch: %s %s\n", raw_data, LeftTurnSwitch ? "ON" : "OFF");
    LPUART1_transmit_string(buffer);

    //Right Turn signal
    char RightTurnSwitch = (frame.payload[7] & (1 << 6));
    sprintf(buffer, "Right turn switch: %s %s\n", raw_data, RightTurnSwitch ? "ON" : "OFF");
    LPUART1_transmit_string(buffer);

    //Flasher
    char Flasher = (frame.payload[6] & (1 << 3));
    sprintf(buffer, "Flasher: %s %s\n", raw_data, Flasher ? "ON" : "OFF");
    LPUART1_transmit_string(buffer);

    //Hazard
    char Hazard = (frame.payload[5] & (1 << 0));
    sprintf(buffer, "Fog light: %s %s\n", raw_data, Hazard ? "ON" : "OFF");
    LPUART1_transmit_string(buffer);
}