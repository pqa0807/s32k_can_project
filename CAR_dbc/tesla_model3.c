#include "dbc.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : TeslaModel3_Decode
 * Description   : 
 *
 *END**************************************************************************/
void TeslaModel3_Decode(void){
    for(uint8_t mbIdx = 0; mbIdx < 16; mbIdx++)
    {
        if((CAN0->IFLAG1) & (1 << mbIdx))
        {
            standard_frame_t frame;
            FlexCAN_receive_frame (CAN0, &frame, mbIdx );
            switch(frame.ID)
            {
                case TeslaModel3_VEHICLE_SPEED_ID:
                    TeslaModel3_VEHICLE_SPEED(frame);
                    break;
                case TeslaModel3_BMS_SOC_ID:
                    TeslaModel3_BMS_SOC(frame);
                    break;
                case TeslaModel3_PEDAL_GEAR_ID:
                    TeslaModel3_PEDAL_GEAR(frame);
                    break;
                case TeslaModel3_SteeringAngle_ID:
                    TeslaModel3_SteeringAngle(frame);
                    break;
                case TeslaModel3_HVBattAmpVolt_ID:
                    TeslaModel3_HVBattAmpVolt(frame);
                    break;
                case TeslaModel3_RearTorque_ID:
                    TeslaModel3_RearTorque(frame);
                    break;
                case TeslaModel3_Actuator_ID:
                    TeslaModel3_Actuator(frame);
                    break;
                case TeslaModel3_LeftTurnSignal_ID:
                    TeslaModel3_LeftTurnSignal(frame);
                    break;
                case TeslaModel3_RightTurnSignal_ID:
                    TeslaModel3_RightTurnSignal(frame);
                    break;
                case TeslaModel3_HVAC_ID:
                    TeslaModel3_HVAC(frame);
                    break;
                case TeslaModel3_Coolant_ID:
                    TeslaModel3_Coolant(frame);
                    break;
                case TeslaModel3_Wiper_ID:
                    UI_wiperModeHandler(frame);
                    break;
                case TeslaModel3_Odometer_ID:
                    TeslaModel3_Odometer(frame);
                    break;
                case TeslaModel3_FrontSensor_ID:
                    TeslaModel3_FrontSensor(frame);
                    break;
                case TeslaModel3_DIRTorque_ID:
                    TeslaModel3_DIRTorque(frame);
                    break;
                default:
                    break;
            }
        }
    }
}


void TeslaModel3_Config_RxMB(void) {
    FlexCAN_Config_RxMB(CAN0, TeslaModel3_VEHICLE_SPEED_ID, MB0 );
    FlexCAN_Config_RxMB(CAN0, TeslaModel3_BMS_SOC_ID, MB1 );
    FlexCAN_Config_RxMB(CAN0, TeslaModel3_PEDAL_GEAR_ID, MB2 );
    FlexCAN_Config_RxMB(CAN0, TeslaModel3_SteeringAngle_ID, MB3 );
    FlexCAN_Config_RxMB(CAN0, TeslaModel3_HVBattAmpVolt_ID, MB4 );
    FlexCAN_Config_RxMB(CAN0, TeslaModel3_RearTorque_ID, MB5 );
    FlexCAN_Config_RxMB(CAN0, TeslaModel3_Actuator_ID, MB6 );
    FlexCAN_Config_RxMB(CAN0, TeslaModel3_LeftTurnSignal_ID, MB7 );
    FlexCAN_Config_RxMB(CAN0, TeslaModel3_RightTurnSignal_ID, MB8 );
    FlexCAN_Config_RxMB(CAN0, TeslaModel3_HVAC_ID, MB9 );
    FlexCAN_Config_RxMB(CAN0, TeslaModel3_Coolant_ID, MB10 );
    FlexCAN_Config_RxMB(CAN0, TeslaModel3_Wiper_ID, MB11 );
    FlexCAN_Config_RxMB(CAN0, TeslaModel3_Odometer_ID, MB12 );
    FlexCAN_Config_RxMB(CAN0, TeslaModel3_FrontSensor_ID, MB13 );
    FlexCAN_Config_RxMB(CAN0, TeslaModel3_DIRTorque_ID, MB14 );
}


/*FUNCTION**********************************************************************
 *
 * Function Name : TeslaModel3_VEHICLE_SPEED
 * Description   : ID: 0x257
 *
 *END**************************************************************************/
void TeslaModel3_VEHICLE_SPEED(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract raw value for DI_vehicleSpeed
    int raw_speed = ((frame.payload[1] & 0xF0) >> 4) | (frame.payload[2] << 4);

    // Convert raw value to physical value using scaling factor and offset
    float vehicleSpeed = raw_speed * 0.08 - 40;

    // Format and transmit the vehicle speed with raw data
    sprintf(buffer, "Vehicle Speed: %s %.2f\n", raw_data, vehicleSpeed);
    LPUART1_transmit_string(buffer);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : TeslaModel3_BMS_SOC
 * Description   : ID: 0x292
 *
 *END**************************************************************************/
void TeslaModel3_BMS_SOC(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract raw value for SOCUI292
    int raw_soc = ((frame.payload[1] & 0xFC) >> 2) | ((frame.payload[2] & 0x0F) << 6);

    // Convert raw value to physical value using scaling factor and offset
    float soc = raw_soc * 0.1;

    // Format and transmit the SOC with raw data
    sprintf(buffer, "State of Charge: %s %.1f\n", raw_data, soc);
    LPUART1_transmit_string(buffer);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : TeslaModel3_PEDAL_GEAR
 * Description   : ID: 0x118
 *
 *END**************************************************************************/
void TeslaModel3_PEDAL_GEAR(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract and calculate DI_accelPedalPos
    int raw_pedal = frame.payload[4];  // DI_accelPedalPos is 8 bits at bit 32
    float accelPedalPos = raw_pedal * 0.4;  // Apply scaling factor

    // Extract DI_gear
    int raw_gear = (frame.payload[2] >> 5) & 0x07;  // DI_gear is 3 bits starting at bit 21
    const char *gear_state;
    switch (raw_gear) {
        case 0: gear_state = "INVALID"; break;
        case 1: gear_state = "P"; break;
        case 2: gear_state = "R"; break;
        case 3: gear_state = "N"; break;
        case 4: gear_state = "D"; break;
        case 5: gear_state = "SNA"; break;
        default: gear_state = "UNKNOWN"; break;
    }

    // Format and transmit accelerator pedal position
    sprintf(buffer, "Pedal Position: %s %.1f\n", raw_data, accelPedalPos);
    LPUART1_transmit_string(buffer);

    // Format and transmit gear state
    sprintf(buffer, "Gear: %s %s\n", raw_data, gear_state);
    LPUART1_transmit_string(buffer);
}



/*FUNCTION**********************************************************************
 *
 * Function Name : TeslaModel3_SteeringAngle
 * Description   : ID: 0x129
 *
 *END**************************************************************************/
void TeslaModel3_SteeringAngle(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract raw SteeringAngle129 value (bits 16-29)
    int raw_steering_angle = ((frame.payload[2] & 0xFF)) | ((frame.payload[3] & 0x3F) << 8);
    float steering_angle = raw_steering_angle * 0.1 - 819.2;  // Apply scaling and offset

    // Extract raw SteeringSpeed129 value (bits 32-45)
    int raw_steering_speed = ((frame.payload[4] & 0xFF)) | ((frame.payload[5] & 0x3F) << 8);
    float steering_speed = raw_steering_speed * 0.5 - 4096;  // Apply scaling and offset

    // Transmit SteeringAngle129
    sprintf(buffer, "Steering Angle: %s %.1f\n", raw_data, steering_angle);
    LPUART1_transmit_string(buffer);

    // Transmit SteeringSpeed129
    sprintf(buffer, "Steering Speed: %s %.1f\n", raw_data, steering_speed);
    LPUART1_transmit_string(buffer);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : TeslaModel3_HVBattAmpVolt
 * Description   : ID: 0x132
 *
 *END**************************************************************************/
void TeslaModel3_HVBattAmpVolt(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract raw BattVoltage132 value (bits 0-15)
    int raw_voltage = (frame.payload[0]) | (frame.payload[1] << 8);
    float batt_voltage = raw_voltage * 0.01;  // Apply scaling

    // Extract raw SmoothBattCurrent132 value (bits 16-31)
    int raw_current = (frame.payload[2]) | (frame.payload[3] << 8);
    if (raw_current & 0x8000) {  // Handle sign extension for 16-bit signed value
        raw_current |= 0xFFFF0000;
    }
    float batt_current = raw_current * -0.1;  // Apply scaling and offset

    // Transmit BattVoltage132
    sprintf(buffer, "HV Battery Voltage: %s %.2f\n", raw_data, batt_voltage);
    LPUART1_transmit_string(buffer);

    // Transmit SmoothBattCurrent132
    sprintf(buffer, "HV Battery Current: %s %.2f\n", raw_data, batt_current);
    LPUART1_transmit_string(buffer);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : TeslaModel3_RearTorque
 * Description   : ID: 0x1D8
 *
 *END**************************************************************************/
void TeslaModel3_RearTorque(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract raw RearTorque1D8 value (bits 21-33)
    int raw_torque = ((frame.payload[2] >> 5) & 0x07) | (frame.payload[3] << 3) | ((frame.payload[4] & 0x01) << 11);
    if (raw_torque & 0x1000) {  // Handle sign extension for 13-bit signed value
        raw_torque |= 0xFFFFE000;
    }
    float rear_torque = raw_torque * 0.222;  // Apply scaling

    // Transmit BattVoltage132
    sprintf(buffer, "Rear Motor Torque: %s %.2f\n", raw_data, rear_torque);
    LPUART1_transmit_string(buffer);

}


/*FUNCTION**********************************************************************
 *
 * Function Name : TeslaModel3_Actuator
 * Description   : ID: 0x201
 *
 *END**************************************************************************/
void TeslaModel3_Actuator(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract VCFRONT_pumpBatteryRPMActual m0 (bits 3-12)
    int raw_battery_rpm = ((frame.payload[0] >> 3) & 0x1F) | ((frame.payload[1] & 0x03) << 5);
    float pumpBatteryRPM = raw_battery_rpm * 10;  // Apply scaling

    // Extract VCFRONT_pumpPowertrainRPMActual m0 (bits 13-22)
    int raw_powertrain_rpm = ((frame.payload[1] >> 3) & 0x1F) | ((frame.payload[2] & 0x3F) << 5);
    float pumpPowertrainRPM = raw_powertrain_rpm * 10;  // Apply scaling

    // Extract VCFRONT_tempSuperheatActual m0 (bits 34-43)
    int raw_temp_superheat = ((frame.payload[4] >> 2) & 0x3F) | ((frame.payload[5] & 0x03) << 6);
    float tempSuperheat = raw_temp_superheat * 0.1 - 20;  // Apply scaling and offset

    // Transmit VCFRONT_pumpBatteryRPMActual m0
    sprintf(buffer, "Battery Pump Actual RPM: %s %.0f\n", raw_data, pumpBatteryRPM);
    LPUART1_transmit_string(buffer);

    // Transmit VCFRONT_pumpPowertrainRPMActual m0
    sprintf(buffer, "Powertrain Pump Actual RPM: %s %.0f\n", raw_data, pumpPowertrainRPM);
    LPUART1_transmit_string(buffer);

    // Transmit VCFRONT_tempSuperheatActual m0
    sprintf(buffer, "Superheat Actual Temperature: %s %.1f\n", raw_data, tempSuperheat);
    LPUART1_transmit_string(buffer);
}



/*FUNCTION**********************************************************************
 *
 * Function Name : TeslaModel3_RightTurnSignal
 * Description   : ID: 0x3E3
 *
 *END**************************************************************************/
void TeslaModel3_RightTurnSignal(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[10]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X ", frame.payload[0], frame.payload[1]);

    // Extract VCRIGHT_turnSignalStatus value (bits 4-5)
    int turn_signal_status = (frame.payload[0] >> 4) & 0x03;

    // Decode the turn signal status
    const char *signal_status;
    switch (turn_signal_status) {
        case 0: signal_status = "OFF"; break;
        case 1: signal_status = "ON"; break;
        case 2: signal_status = "FAULT"; break;
        case 3: signal_status = "SNA"; break;
        default: signal_status = "UNKNOWN"; break;
    }

    // Format and transmit the turn signal status
    sprintf(buffer, "Right Signal Light: %s %s\n", raw_data, signal_status);
    LPUART1_transmit_string(buffer);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : TeslaModel3_LeftTurnSignal
 * Description   : ID: 0x3E2
 *
 *END**************************************************************************/
void TeslaModel3_LeftTurnSignal(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[10]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X",
        frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
        frame.payload[4], frame.payload[5], frame.payload[6]);

    // Extract VCRIGHT_turnSignalStatus value (bits 4-5)
    int turn_signal_status = (frame.payload[0] >> 4) & 0x03;

    // Decode the turn signal status
    const char *signal_status;
    switch (turn_signal_status) {
        case 0: signal_status = "OFF"; break;
        case 1: signal_status = "ON"; break;
        case 2: signal_status = "FAULT"; break;
        case 3: signal_status = "SNA"; break;
        default: signal_status = "UNKNOWN"; break;
    }

    // Format and transmit the turn signal status
    sprintf(buffer, "Left Signal Light: %s %s\n", raw_data, signal_status);
    LPUART1_transmit_string(buffer);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : TeslaModel3_HVAC
 * Description   : ID: 0x20C
 *
 *END**************************************************************************/
void TeslaModel3_HVAC(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract Evaporator Power (bits 0-10)
    int raw_watts = ((frame.payload[0]) | ((frame.payload[1] & 0x07) << 8));
    float wattsDemandEvap = raw_watts * 5;  // Apply scaling

    // Extract Evaporator Temperature (bits 13-23)
    int raw_temp = ((frame.payload[1] >> 5) | (frame.payload[2] << 3));
    float tempEvaporator = raw_temp * 0.1 - 40;  // Apply scaling and offset

    // Extract HVAC Blower Speed (bits 32-41)
    int raw_blower_rpm = ((frame.payload[4]) | ((frame.payload[5] & 0x03) << 8));
    float blowerSpeedRPM = raw_blower_rpm * 5;  // Apply scaling

    // Transmit VCRIGHT_wattsDemandEvap
    sprintf(buffer, "Evaporator Power: %s %.0f\n", raw_data, wattsDemandEvap);
    LPUART1_transmit_string(buffer);

    // Transmit VCRIGHT_tempEvaporator
    sprintf(buffer, "Evaporator Temperature: %s %.1f\n", raw_data, tempEvaporator);
    LPUART1_transmit_string(buffer);

    // Transmit VCRIGHT_hvacBlowerSpeedRPMReq
    sprintf(buffer, "HVAC Blower Speed: %s %.0f\n", raw_data, blowerSpeedRPM);
    LPUART1_transmit_string(buffer);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : TeslaModel3_Coolant
 * Description   : ID: 0x241
 *
 *END**************************************************************************/
void TeslaModel3_Coolant(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract Battery Coolant Flow (bits 0-8)
    int raw_coolant_bat = (frame.payload[0]) | ((frame.payload[1] & 0x01) << 8);
    float coolantFlowBatActual = raw_coolant_bat * 0.1;  // Apply scaling

    // Extract Powertrain Coolant Flow (bits 22-30)
    int raw_coolant_pt = ((frame.payload[2] >> 6) & 0x03) | (frame.payload[3] << 2);
    float coolantFlowPTActual = raw_coolant_pt * 0.1;  // Apply scaling

    // Transmit VCFRONT_coolantFlowBatActual
    sprintf(buffer, "Battery Coolant Flow: %s %.1f\n", raw_data, coolantFlowBatActual);
    LPUART1_transmit_string(buffer);

    // Transmit VCFRONT_coolantFlowPTActual
    sprintf(buffer, "Powertrain Coolant Flow: %s %.1f\n", raw_data, coolantFlowPTActual);
    LPUART1_transmit_string(buffer);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : TeslaModel3_Wiper
 * Description   : ID: 0x273
 *
 *END**************************************************************************/
void UI_wiperModeHandler(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6]);

    // Extract UI_wiperMode value (bits 6-7)
    int wiper_mode = (frame.payload[0] >> 6) & 0x03;

    // Decode the wiper mode
    const char *mode_desc;
    switch (wiper_mode) {
        case 0: mode_desc = "OFF"; break;
        case 1: mode_desc = "LOW"; break;
        case 2: mode_desc = "HIGH"; break;
        case 3: mode_desc = "AUTO"; break;
        default: mode_desc = "UNKNOWN"; break;
    }

    // Format and transmit the wiper mode
    sprintf(buffer, "Wiper: %s %s\n", raw_data, mode_desc);
    LPUART1_transmit_string(buffer);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : TeslaModel3_Odometer
 * Description   : ID: 0x3B6
 *
 *END**************************************************************************/
void TeslaModel3_Odometer(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[20]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3]);

    // Extract Odometer value (bits 0–31)
    unsigned int raw_odometer = (frame.payload[0]) |
                                (frame.payload[1] << 8) |
                                (frame.payload[2] << 16) |
                                (frame.payload[3] << 24);
    float odometer = raw_odometer * 0.001;  // Apply scaling

    // Format and transmit the odometer reading
    sprintf(buffer, "Odometer: %s %.3f\n", raw_data, odometer);
    LPUART1_transmit_string(buffer);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : TeslaModel3_FrontSensor
 * Description   : ID: 0x321
 *
 *END**************************************************************************/
void TeslaModel3_FrontSensor(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract Battery Coolant Temperature (bits 0-9)
    int raw_coolant_bat_inlet = (frame.payload[0]) | ((frame.payload[1] & 0x03) << 8);
    float tempCoolantBatInlet = raw_coolant_bat_inlet * 0.125 - 40;  // Apply scaling and offset

    // Extract Powertrain Coolant Temperature (bits 10-20)
    int raw_ptCoolantTemp = ((frame.payload[1] >> 2) & 0x3F) | ((frame.payload[2] & 0x1F) << 6);
    float ptCoolantTemp = raw_ptCoolantTemp * 0.125 - 40;  // Apply scaling and offset

    // Extract Outside Temperature (bits 40-47)
    int raw_outsideTemp = frame.payload[5];
    float outsideTemp = raw_outsideTemp * 0.5 - 40;  // Apply scaling and offset

    // Transmit Battery Coolant Temperature
    sprintf(buffer, "Battery Coolant Temperature: %s %.2f\n", raw_data, tempCoolantBatInlet);
    LPUART1_transmit_string(buffer);

    // Transmit Powertrain Coolant Temperature
    sprintf(buffer, "Powertrain Coolant Temperature: %s %.2f\n", raw_data, ptCoolantTemp);
    LPUART1_transmit_string(buffer);

    // Transmit Outside Temperature
    sprintf(buffer, "Outside Temperature: %s %.2f\n", raw_data, outsideTemp);
    LPUART1_transmit_string(buffer);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : TeslaModel3_DIRTorque
 * Description   : ID: 0x108
 *
 *END**************************************************************************/
void TeslaModel3_DIRTorque(standard_frame_t frame) {
    char buffer[50];   // Buffer for formatted output
    char raw_data[30]; // Buffer to store raw payload data as hex

    // Format the raw data bytes as hex string
    sprintf(raw_data, "%02X %02X %02X %02X %02X %02X %02X %02X",
            frame.payload[0], frame.payload[1], frame.payload[2], frame.payload[3],
            frame.payload[4], frame.payload[5], frame.payload[6], frame.payload[7]);

    // Extract Rear Axle Speed (bits 40–55)
    int raw_axle_speed = (frame.payload[5]) | (frame.payload[6] << 8);
    float axleSpeed = raw_axle_speed * 0.1;  // Apply scaling

    // Handle Rear Axle Speed signed value
    if (raw_axle_speed & 0x8000) { // Check if negative (highest bit is set)
        raw_axle_speed -= 0x10000; // Convert to signed value
        axleSpeed = raw_axle_speed * 0.1;
    }

    // Extract Rear Axle Torque (bits 27–39)
    int raw_torque_actual = ((frame.payload[3] >> 3) & 0x1F) | (frame.payload[4] << 5);
    float torqueActual = raw_torque_actual * 2;  // Apply scaling

    // Handle Rear Axle Torque signed value
    if (raw_torque_actual & 0x1000) { // Check if negative (highest bit is set)
        raw_torque_actual -= 0x2000; // Convert to signed value
        torqueActual = raw_torque_actual * 2;
    }

    // Transmit Rear Axle Speed
    sprintf(buffer, "Rear Axle Speed: %s %.1f\n", raw_data, axleSpeed);
    LPUART1_transmit_string(buffer);

    // Transmit Rear Axle Torque
    sprintf(buffer, "Rear Axle Torque: %s %.1f\n", raw_data, torqueActual);
    LPUART1_transmit_string(buffer);
}
