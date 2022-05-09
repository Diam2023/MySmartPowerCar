#ifndef __DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"




/**
 * @brief  确认是否在运行
 * @return void*: 
 */
void *CheckRunning();

/**
 * @brief  流程任务初始化
 */
void PROC_Init();


#ifdef __cplusplus
}
#endif

#endif /* __DRIVER_H_ */
