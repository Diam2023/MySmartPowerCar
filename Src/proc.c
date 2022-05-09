#include "proc.h"

#include "main.h"
#include "tim.h"

extern DRIVER *driver;

void *CheckRunningProccess() {
  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
//   HAL_TIM_PWM_Start(hto)
  return NULL;
}

void PROC_Init() {
  /**
   * @brief 确认程序是否正确运行的进程
   */
  queue_node_type *checkRunningProccessNode;

  checkRunningProccessNode = set_loop(
      UINT8_MAX,
      create_timer_node((node_func_type)(&CheckRunningProccess), 1, 10000, NULL));
  push_node_release(checkRunningProccessNode);
}
