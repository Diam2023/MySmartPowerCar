#ifndef CAR_INC_HANDLER_H_
#define CAR_INC_HANDLER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/**
 * @brief  接收数据的处理函数
 * @param  recivedData: RecivedStruct_t结构体
 */
void ReceivedMessageHandler(void *recivedData);

/**
 * @brief  处理错误
 */
void ErrorHandler();

#ifdef __cplusplus
}
#endif

#endif // CAR_INC_HANDLER_H_
