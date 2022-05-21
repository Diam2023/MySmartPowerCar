#include "proc.h"

#include "main.h"
#include "tim.h"

#include "handler.h"
#include "nrf24l01.h"

extern DRIVER *driver;
extern uint8_t recivedDataStruct[32];

void *CheckRunningProccess()
{
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    return NULL;
}

void *CheckReciveProccess()
{
    if (NRF24L01_IRQ_PIN_READ() == 0)
    {
        uint8_t dt = NRF24L01_RxPacket(recivedDataStruct);
        if (dt != 0)
        {
            return NULL;
        }
        for (size_t i = 0; i < 4; i++)
        {
            if (kMasterHeader[i] != recivedDataStruct[i])
            {
                return NULL;
            }
        }

        RecivedStruct_t *received = (RecivedStruct_t *)calloc(1, sizeof(RecivedStruct_t));
        received->rotate          = recivedDataStruct[5];
        received->straight        = recivedDataStruct[6];

        return received;
    }
    return NULL;
}

void PROC_Init()
{
    /**
     * @brief 确认程序是否正确运行的进程
     */
    queue_node_type *checkRunningProccessNode;
    queue_node_type *checkReciveProccessNode;

    checkReciveProccessNode =
        set_loop(UINT8_MAX, create_timer_node((node_func_type)(&CheckReciveProccess), 1, 10, NULL));

    register_result_performance((node_func_type)(&ReceivedMessageHandler), checkReciveProccessNode);

    checkRunningProccessNode =
        set_loop(UINT8_MAX, create_timer_node((node_func_type)(&CheckRunningProccess), 1, 10000, NULL));

    push_node_release(checkRunningProccessNode);
    push_node_release(checkReciveProccessNode);
}
