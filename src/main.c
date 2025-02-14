/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "lpuart.h"
#include "Can.h"
#include "clocks_and_modes.h"
#include "nvic.h"
#include "port.h"
#include "pcc.h"
#include <stdio.h>
#include "dbc.h"

#define Honda '1'
#define Mazda '2'
#define Tesla '3'
#define Huynhdai '4'

char car_model; 


void CAN0_ORed_0_15_MB_IRQHandler(void)
{   switch(car_model)
    {
        case Honda:
            HondaCivic_Decode();
            break;
        case Mazda:
            MazdaCX5_Decode();
            break;
        case Tesla:
            TeslaModel3_Decode();
            break;
        case Huynhdai:
            HuynhDai_Elantra_Decode();
            break;
    }
    
}



int main(void) {
    /* Init the System*/
    SOSC_init_8MHz ();
    SPLL_init_160MHz ();
    NormalRUNmode_80MHz ();
    PCC->PCC_FlexCAN0 = (1 << 30); /* Enable clock for FlexCAN0 */
    PORT_init ();
    LPUART1_init();
    NVIC_EnableIRQ(CAN0_ORed_0_15_MB_IRQn);

    /**/
    flexcan_user_config_t flexcanConfig;

    FLEXCAN_DRV_GetDefaultConfig(&flexcanConfig);

    FLEXCAN_DRV_Init(CAN0, &flexcanConfig);

    while(1) 
    {

        car_model = LPUART1_receive_char();

        switch (car_model)
        {
            case Honda:
                HondaCivic_Config_RxMB();
                break;
            case Mazda:
                MazdaCX5_Config_RxMB();
                break;
            case Tesla:
                TeslaModel3_Config_RxMB();
                break;
            case Huynhdai:
                HuynhDai_Elantra_Config_RxMB();
                break;
        }
    }
    return 0;
}

