#include "driver.h"

#include "tim.h"

void DRIVER_Init()
{
    // priority timer queue
    init_priority_queue();

    // tim3
    HAL_TIM_Base_Start_IT(&htim3);

    
}


