#include "intrpt.h"

#include "port/sys/sys_tick.h"
#include "lx/log.h"

#include "stm32f4xx_hal.h"

/*
void Reset_Handler(void)
{
}

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
}

void MemManage_Handler(void)
{
}

void BusFault_Handler(void)
{
}

void UsageFault_Handler(void)
{
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}
*/

void SysTick_Handler(void)
{
    static int i = 0;
    HAL_IncTick();

    sys_systicks_update();

    if ((++i) % 1000 == 0) {
        LOGI("\tSystick Handle!!! Systicks: %d\n", g_systicks.ticks_32);
    }
}
