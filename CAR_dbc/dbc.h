#ifndef DBC_H_
#define DBC_H_

#include <stdlib.h>
#include "lpuart.h"
#include "Can.h"

/************************************************************************************
 *                                  Definitions
 ************************************************************************************/
/* Honda Civic */
#define HondaCivic_POWERTRAIN_DATA_ID       0x17C
#define HondaCivic_CARSPEED_ID              0x309
#define HondaCivic_ENGINE_DATA_ID           0x158
#define HondaCivic_SCM_FEEDBACK_ID          0x294
#define HondaCivic_GEARBOX_ID               0x188
#define HondaCivic_LIGHT_ID                 0x164

/**/
#define HondaCRV_POWERTRAIN_DATA_ID         0x17C
#define HondaCRV_WHEEL_SPEEDS_ID            0x1D0

/* HuynhDai Elantra */
#define HuynhDai_Elantra_SIGNAL_ID          0x541

/* Mazda CX-5 */
#define MazdaCX5_ENGINE_DATA_ID        0x202
#define MazdaCX5_WHEEL_SPEED_ID        0x215
#define MazdaCX5_TURN_SWITCH_ID        0x91

/* Tesla Model 3 */
#define TeslaModel3_VEHICLE_SPEED_ID   0x257
#define TeslaModel3_BMS_SOC_ID         0x292
#define TeslaModel3_PEDAL_GEAR_ID      0x118
#define TeslaModel3_SteeringAngle_ID   0x129
#define TeslaModel3_HVBattAmpVolt_ID   0x132
#define TeslaModel3_RearTorque_ID      0x1D8
#define TeslaModel3_Actuator_ID        0x201
#define TeslaModel3_LeftTurnSignal_ID  0x3E2
#define TeslaModel3_RightTurnSignal_ID 0x3E3
#define TeslaModel3_HVAC_ID            0x20C
#define TeslaModel3_Coolant_ID         0x241
#define TeslaModel3_Wiper_ID           0x273
#define TeslaModel3_Odometer_ID        0x3B6
#define TeslaModel3_FrontSensor_ID     0x321
#define TeslaModel3_DIRTorque_ID       0x108


/*******************************************************************************
 *                          HONDA CIVIC
 ******************************************************************************/
void HondaCivic_CARSPEED(standard_frame_t frame);
void HondaCivic_POWERTRAIN_DATA(standard_frame_t frame);
void HondaCivic_SCM_FEEDBACK(standard_frame_t frame);
void HondaCivic_GEARBOX(standard_frame_t frame);
void HondaCivic_Decode(void);
void HondaCivic_Config_RxMB(void);

/*******************************************************************************
 *                          HONDA CRV
 ******************************************************************************/
void HondaCRV_POWERTRAIN_DATA(standard_frame_t frame);
void HondaCRV_WHEEL_SPEEDS(standard_frame_t frame);
void HondaCRV_ENGINE_DATA(standard_frame_t frame);
void HondaCRV_Decode(void);

/*******************************************************************************
 *                          HUYNHDAI ELANTRA
 ******************************************************************************/
void HuynhDai_Elantra_Signal(standard_frame_t frame);

/*******************************************************************************
 *                          MAZDA
 ******************************************************************************/
void MazdaCX5_ENGINE_DATA( standard_frame_t frame );
void MazdaCX5_WHEEL_SPEED( standard_frame_t frame );
void MazdaCX5_TURN_SWITCH( standard_frame_t frame );
void MazdaCX5_Decode(void);
void MazdaCX5_Config_RxMB(void);

/*******************************************************************************
 *                          TESLA
 ******************************************************************************/
void TeslaModel3_VEHICLE_SPEED(standard_frame_t frame);
void TeslaModel3_BMS_SOC(standard_frame_t frame);
void TeslaModel3_PEDAL_GEAR(standard_frame_t frame);
void TeslaModel3_SteeringAngle(standard_frame_t frame);
void TeslaModel3_HVBattAmpVolt(standard_frame_t frame);
void TeslaModel3_RearTorque(standard_frame_t frame);
void TeslaModel3_Actuator(standard_frame_t frame);
void TeslaModel3_LeftTurnSignal(standard_frame_t frame);
void TeslaModel3_RightTurnSignal(standard_frame_t frame);
void TeslaModel3_HVAC(standard_frame_t frame);
void TeslaModel3_Coolant(standard_frame_t frame);
void TeslaModel3_Wiper(standard_frame_t frame);
void TeslaModel3_Odometer(standard_frame_t frame);
void TeslaModel3_FrontSensor(standard_frame_t frame);
void TeslaModel3_DIRTorque(standard_frame_t frame);
void TeslaModel3_Decode(void);
void TeslaModel3_Config_RxMB(void);

#endif /*DBC_H_*/