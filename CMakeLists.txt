cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE stm32-toolchain.cmake)
project(Car)
enable_language(ASM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE C_SOURCES CONFIGURE_DEPENDS
  Src/*.c
  Core/*.c
  priority-timer-queue/src/*c
  Core/*.cpp
  Drivers/*.c)

add_executable(${CMAKE_PROJECT_NAME}.elf ${C_SOURCES} startup_stm32f103xb.s)

target_include_directories(${CMAKE_PROJECT_NAME}.elf PRIVATE
  Inc
  Drivers/STM32F1xx_HAL_Driver/Inc
  Drivers/STM32F1xx_HAL_Driver/Inc/Legacy
  Drivers/CMSIS/Device/ST/STM32F1xx/Include
  priority-timer-queue/inc
  Drivers/CMSIS/Include)

target_compile_definitions(${CMAKE_PROJECT_NAME}.elf PRIVATE
  USE_HAL_DRIVER
  STM32F103xB)

set(MCU_FLAGS -mcpu=cortex-m3 -mthumb)

target_compile_options(${CMAKE_PROJECT_NAME}.elf PRIVATE ${MCU_FLAGS})
target_link_options(${CMAKE_PROJECT_NAME}.elf PRIVATE ${MCU_FLAGS}
  -T ${PROJECT_SOURCE_DIR}/STM32F103C8Tx_FLASH.ld)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -Oihex ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.hex
  COMMAND ${CMAKE_OBJCOPY} -Obinary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin)
