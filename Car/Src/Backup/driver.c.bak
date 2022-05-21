#include "driver.h"

#include "tim.h"

extern DRIVER *driver;

void DRIVER_Init() {
  // priority timer queue
  init_priority_queue();
  // tim3
  HAL_TIM_Base_Start_IT(&htim3);

  driver = (DRIVER *)calloc(1, sizeof(DRIVER));

  driver->servo.servo.htim = &htim1;
  driver->servo.servo.channel = TIM_CHANNEL_2;

  driver->motor_a.encoder.GPIOx = GPIOA;
  driver->motor_a.encoder.pin_a = GPIO_PIN_3;
  driver->motor_a.encoder.pin_b = GPIO_PIN_2;
  driver->motor_a.signal_a.htim = &htim2;
  driver->motor_a.signal_a.channel = TIM_CHANNEL_4;
  driver->motor_a.signal_b.htim = &htim2;
  driver->motor_a.signal_b.channel = TIM_CHANNEL_3;

  driver->motor_b.encoder.GPIOx = GPIOA;
  driver->motor_b.encoder.pin_a = GPIO_PIN_1;
  driver->motor_b.encoder.pin_b = GPIO_PIN_0;
  driver->motor_b.signal_a.htim = &htim2;
  driver->motor_b.signal_a.channel = TIM_CHANNEL_2;
  driver->motor_b.signal_b.htim = &htim2;
  driver->motor_b.signal_b.channel = TIM_CHANNEL_1;

  TIM2->CCR1 = 0;
  TIM2->CCR2 = 0;
  TIM2->CCR3 = 0;
  TIM2->CCR4 = 0;

  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);

  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
}
