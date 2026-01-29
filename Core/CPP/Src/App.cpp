#include "App.hpp"
#include "main.h"

#include "SVM.h"
#include "phaseEstimater.h"
#include "tim.h"
#include "Park_u_Clark.h"
#include <math.h>
#include "encoder.h"
#include "uart_debug.h"


#define PI_Control_k 1

int16_t PI_control(int32_t error)
{
  return (error * PI_Control_k) >> 10;
}

uint16_t TIM_PSC = 0;
int32_t phaseshift = 90;
uint16_t setpoint = 20;

extern "C" void App_Init(void)
{
  initSVM(PWM_Frequency);
  init_phase_estimater();

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

extern "C" void App_Process(void)
{
    static uint8_t init_done = 0;

    setpoint = (uint16_t)readEncoder(GPIOA, GPIO_PIN_0,
                                     GPIOA, GPIO_PIN_1, 255, 0);

    if (!init_done)
    {
      init_done = initialize_Hallsensor_phase_estimator(setpoint);
    }
    else
    {

      estimate_rotor_phase(&Motor);

      phaseshift += PI_control(-Motor.MotorCurrents.DQCurrenst[1]);

      if (phaseshift > 100)
        phaseshift = 80;
      if (phaseshift < 80)
        phaseshift = 60;

      setVoltageVector(Motor.rotorphase, phaseshift, setpoint);

      //UART_transmit_buffer();

      TIM_PSC = SectorTIM.Instance->ARR;
    }
}
