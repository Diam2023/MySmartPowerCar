#ifndef __CAR_H_
#define __CAR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/**
 * @brief 编码器的状态
 */
typedef enum {
  RUNNING = 0,
  STOPPED = 1,
  MOTOR_ENCODER_STATUS_END = 0xFFFF
} MOTOR_ENCODER_STATUS;

/**
 * @brief 编码器运行方向
 */
typedef enum {
  FORWARD = 0,
  BACKWARD = 1,
  MOTOR_ENCODER_DIRECT_END = 0xFFFF
} MOTOR_ENCODER_DIRECTION;

/**
 * @brief 电机旋转编码器
 */
typedef struct {

  MOTOR_ENCODER_STATUS status;

  MOTOR_ENCODER_DIRECTION direction; // if status is FORWARD

  uint16_t pin_a; // 编码器A极

  uint16_t pin_b; // 编码器B极

} MOTOR_ENCODER;

typedef struct {
  unsigned channel;

  TIM_HandleTypeDef *htim;

  float rate; // pwm占空比

} PWM_SIGNAL;

typedef PWM_SIGNAL MOTOR_SIGNAL;

/**
 * @brief 一个电机
 */
typedef struct {

  MOTOR_ENCODER encoder; // 编码器

  MOTOR_SIGNAL signal_a; // A端

  MOTOR_SIGNAL signal_b; // B端

} MOTOR;

/**
 * @brief 舵机
 */
typedef struct {

  PWM_SIGNAL signal_s;

  uint32_t rate; // 现在旋转到的比率

} SERVO;

/**
 * @brief 提供整个小车前进后退动力电机的结构体
 */
typedef struct {

  SERVO rotate;

  MOTOR motor_a;

  MOTOR motor_b;

} DRIVER;

// typedef enum {
//   DIRECT = 0,
//   LEFT = 0,

// } CAR_FACE;

/**
 * @brief  提供舵机旋转操作函数
 * @param  servo: 储存控制舵机的PWM发生器的结构体
 * @param  angle: 旋转到的角度
 */
void ServoRotate(SERVO *servo, float angle);

/**
 * @brief  提供控制电机一个通道信号功率的操作函数
 * @param  motor_signal: 储存操作电机一个通道的PWM发生器的结构体
 * @param  power: 前进功率百分比,负为反向旋转
 */
void MotorSignalPower(MOTOR_SIGNAL *motor_signal, float power);

/**
 * @brief  提供一个电机的驱动
 * @param  motor: 电机
 * @param  power_a: A通道比率, 输出的功率
 * @param  power_b: B通道比率, 输出的功率
 */
void MotorPower(MOTOR *motor, float power_a, float power_b);

/**
 * @brief  提供整个小车的转向 前进后退的操作函数
 * @param  driver: 两个电机以及一个舵机
 * @param  angle: 旋转角度
 * @param  power_a: A通道比率, 输出的功率
 * @param  power_b: B通道比率, 输出的功率
 */
void DriverPower(DRIVER *driver, float angle, float power_a, float power_b);

#ifdef __cplusplus
}
#endif

#endif // __CAR_H_
