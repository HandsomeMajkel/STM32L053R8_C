/** \file vectors.c
 * \brief LPC11xx vector table and __Default_Handler()
 * \details LPC11xx vector table and __Default_Handler()
 * \author Freddie Chopin, http://www.freddiechopin.info/
 * \date 2012-01-08
 */

/******************************************************************************
* chip: LPC11xx
* compiler: arm-none-eabi-gcc (Sourcery CodeBench Lite 2011.09-69) 4.6.1
******************************************************************************/

/*------------------------------------------------------------------------*//**
* \brief Default interrupt handler.
* \details Default interrupt handler, used for interrupts that don't have their
* own handler defined.
*//*-------------------------------------------------------------------------*/

static void __Default_Handler(void) __attribute__ ((interrupt));
static void __Default_Handler(void)
{
	while (1);
}

/*
+=============================================================================+
| assign all unhandled interrupts to the default handler
+=============================================================================+
*/

// Non-maskable interrupt (RCC clock security system)
void NMI_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// All class of fault
void HardFault_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Memory management
void MemManage_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Pre-fetch fault, memory access fault
void BusFault_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Undefined instruction or illegal state
void UsageFault_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x1C
void __Reserved_0x1C_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x20
void __Reserved_0x20_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x24
void __Reserved_0x24_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x28
void __Reserved_0x28_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// System service call via SWI instruction
void SVC_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Debug monitor
void DebugMon_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x34
void __Reserved_0x34_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Pendable request for system service
void PendSV_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// System tick timer
void SysTick_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Window watchdog interrupt
void WWDG_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// PVD through EXTI line detection interrupt
void PVD_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// RTC global interrupt
void RTC_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Flash global interrupt
void FLASH_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// RCC global interrupt
void RCC_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));


void EXTI0_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// EXTI Line1 interrupt
void EXTI2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// EXTI Line2 interrupt
void EXTI4_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// EXTI Line2 interrupt
void TSC_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA1 Channel1 global interrupt
void DMA1_Channel1_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA1 Channel2 global interrupt
void DMA1_Channel2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA1 Channel3 global interrupt
void DMA1_Channel4_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Start logic wake-up from PIO0_11 interrupt
void ADC_COMP_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Start logic wake-up from PIO1_0 interrupt
void LPTIM1_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// C_CAN interrupt (LPC11C12/C14 only)
void __Reserved_0x78_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// SPI/SSP1 interrupt
void TIM2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// I2C interrupt
void __Reserved_0x80_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// CT16B0 (16-bit Timer0) interrupt
void TIM6_DAC_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// CT16B1 (16-bit Timer1) interrupt
void __Reserved_0x88_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// CT32B0 (32-bit Timer0) interrupt
void __Reserved_0x8C_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// CT32B1 (32-bit Timer1) interrupt
void TIM21_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));


void TIM22_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x94
void __Reserved_0x94_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// SPI/SSP0 interrupt
void I2C1_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// UART interrupt
void I2C2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x98
void SPI1_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x9C
void SPI2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// A/D Converter interrupt
void USART1_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Watchdog timer interrupt
void USART2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Brown Out Detect interrupt
void LPUART1_AES_RNG_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0xAC
void LCD_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// PIO INT3 interrupt
void USB_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));


/*
+=============================================================================+
| Vector table
+=============================================================================+
*/

extern const char __main_stack_end;			// imported main stack end (from linker script)

void Reset_Handler(void);					// import the address of Reset_Handler()

void (* const vectors[])(void) __attribute__ ((section(".vectors"))) = {
		(void (*)(void))&__main_stack_end,	// Main stack end address
		Reset_Handler,						// Reset
		NMI_Handler,						// Reserved 0x08
		HardFault_Handler,					// All class of fault
		MemManage_Handler,			// Reserved 0x10
		BusFault_Handler,			// Reserved 0x14
		UsageFault_Handler,			// Reserved 0x18
		__Reserved_0x1C_Handler,			// Reserved 0x1C
		__Reserved_0x20_Handler,			// Reserved 0x20
		__Reserved_0x24_Handler,			// Reserved 0x24
		__Reserved_0x28_Handler,			// Reserved 0x28
		SVC_Handler,						// System service call via SWI instruction
		DebugMon_Handler,			// Reserved 0x30
		__Reserved_0x34_Handler,			// Reserved 0x34
		PendSV_Handler,						// Pendable request for system service
		SysTick_Handler,					// System tick timer
		WWDG_IRQHandler,			// Start logic wake-up from PIO0_0 interrupt
		PVD_IRQHandler,			// Start logic wake-up from PIO0_1 interrupt
		RTC_IRQHandler,			// Start logic wake-up from PIO0_2 interrupt
		FLASH_IRQHandler,			// Start logic wake-up from PIO0_3 interrupt
		RCC_IRQHandler,			// Start logic wake-up from PIO0_4 interrupt
		EXTI0_IRQHandler,					// EXTI Line0 interrupt
		EXTI2_IRQHandler,					// EXTI Line1 interrupt
		EXTI4_IRQHandler,// EXTI Line2 interrupt
		TSC_IRQHandler,
		DMA1_Channel1_IRQHandler,			// DMA1 Channel1 global interrupt
		DMA1_Channel2_IRQHandler,			// DMA1 Channel2 global interrupt
		DMA1_Channel4_IRQHandler,			// DMA1 Channel3 global interrupt
		ADC_COMP_IRQHandler,			// Start logic wake-up from PIO0_11 interrupt
		LPTIM1_IRQHandler,			// Start logic wake-up from PIO1_0 interrupt
		__Reserved_0x78_Handler,						// C_CAN interrupt (LPC11C12/C14 only)
		TIM2_IRQHandler,					// SPI/SSP1 interrupt
		__Reserved_0x80_Handler,						// I2C interrupt
		TIM6_DAC_IRQHandler,				// CT16B0 (16-bit Timer0) interrupt
		__Reserved_0x88_Handler,				// CT16B1 (16-bit Timer1) interrupt
		__Reserved_0x8C_Handler,				// CT32B0 (32-bit Timer0) interrupt
		TIM21_IRQHandler,				// CT32B1 (32-bit Timer1) interrupt
		__Reserved_0x94_Handler,
		TIM22_IRQHandler,
		I2C1_IRQHandler,					// SPI/SSP0 interrupt
		I2C2_IRQHandler,					// UART interrupt
		SPI1_IRQHandler,			// Reserved 0x98
		SPI2_IRQHandler,			// Reserved 0x9C
		USART1_IRQHandler,						// A/D Converter interrupt
		USART2_IRQHandler,						// Watchdog timer interrupt
		LPUART1_AES_RNG_IRQHandler,						// Brown Out Detect interrupt
		LCD_IRQHandler,			// Reserved 0xAC
		USB_IRQHandler,					// PIO INT3 interrupt

};

/******************************************************************************
* END OF FILE
******************************************************************************/
