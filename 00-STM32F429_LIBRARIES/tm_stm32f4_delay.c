#include "tm_stm32f4_delay.h"

static __IO uint32_t TM_TimingDelay;
static __IO uint32_t TM_TimingDelay = 0;

inline void Delay(__IO uint32_t nTime) {
	TM_TimingDelay = nTime;

	while (TM_TimingDelay != 0);
}

inline void Delayms(__IO uint32_t nTime) {
	TM_TimingDelay = 1000 * nTime;

	while (TM_TimingDelay != 0);
}

void SysTick_Handler(void) {
	if (TM_TimingDelay != 0x00) {
		TM_TimingDelay--;
	}

	TM_Time++;
}

void TM_DELAY_Init(void) {
	//Set Systick interrupt every 1us
	if (SysTick_Config(SystemCoreClock / 1000000)) {
		/* Capture error */
		while (1);
	}
}