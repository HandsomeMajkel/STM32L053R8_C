/*
 * config.c
 *
 *  Created on: 5 wrz 2015
 *      Author: Micha³
 */
#include <stdint.h>
#include "../inc/stm32l053xx.h"
#include "include/config.h"
//#include "include/gpio.h"
#include "../hdr/hdr_syscon.h"

volatile int time_ms = 0;
volatile uint16_t Timer1,Timer2;
void rcc_config (void){ // 6MHz

	// HSE:
	RCC->CR |= RCC_CR_HSEON; // 1.krok RCC-CR, chcê uruchomic
	while(!(RCC->CR & RCC_CR_HSERDY )); //2. flaga, 1 krok wykonany

	// HSI 16(dzia³a):
	//RCC->CR |= RCC_CR_HSION; // 1.krok RCC-CR, chcê uruchomic
	//while(!(RCC->CR & RCC_CR_HSIRDY )); //2. flaga, 1 krok wykonany



	FLASH->ACR |= FLASH_ACR_LATENCY;
	FLASH->ACR |= FLASH_ACR_PRFTEN;
	// tuataj dodac tzrzeba mno¿nik PLL,prekslery szyn,¿ród³o taktowania PLL:
	// do przeanalizowania :
	//RCC->CFGR |= RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMUL3 | RCC_CFGR_PLLDIV4 | RCC_CFGR_PPRE1_DIV1| RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_HPRE_DIV1; // HSE 6MHz na wyj
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMUL3 | RCC_CFGR_PLLDIV3 | RCC_CFGR_PPRE1_DIV1| RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_HPRE_DIV1; // HSE 8MHz na wyj
	//RCC->CFGR |= RCC_CFGR_PLLSRC_HSI | RCC_CFGR_PLLMUL3 | RCC_CFGR_PLLDIV3 | RCC_CFGR_PPRE1_DIV1| RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_HPRE_DIV1; // HSI 16MHz
	//RCC_CFGR_PLLSRC - HSE on
	//RCC_CFGR_PLLMUL3 - mno¿nik pll x3
	//RCC_CFGR_PLLDIV2 - /2
	//RCC_CFGR_PPRE1_DIV1 APB1 prescaler
	//RCC_CFGR_PPRE2_DIV1 APB2 prescaler
	//RCC_CFGR_HPRE_DIV1 - AHB prescaler
	RCC->CR |= RCC_CR_PLLON;  //3. w³¹czenie PLL
	while(!(RCC->CR & RCC_CR_PLLRDY)); //4. flaga, 3 krok wykonany
	//FLASH->ACR |= FLASH_ACR_LATENCY; // 5. waitstate, 4 krok wykonany
	//FLASH->ACR |= FLASH_ACR_PRFTEN;
	RCC->CFGR |= RCC_CFGR_SW_PLL; // tak w dokumentacji: PLL used as a system clock, 5 krok wykonany
	while (((RCC->CFGR) & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); // Bits set by hardware dlatego pêtla i oczekiwanie ustawienie PLL jako SYSCLK


	// Ustawienie MSI
	// rejestr str. 161 manual disrange, domyœlnie 2,1Mhz
	//RCC->ICSCR |= RCC_ICSCR_MSIRANGE_5; // tak siê ustawia 2,1 Mhz chocia¿ i tak ta czêstotliwoœc z automatu jest ustawiona

}


void delay_ms(int ms) // ok, funkcja generujaca dokladne opoznienia w ms
{
	time_ms = ms;
	//TIM6 -> CNT = 0;// Zerowanie licznika
	while(time_ms!=0); //Oczekiwanie na koniec odliczania
}


void tim6_init(void) // 1ms
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	TIM6->PSC = 9; // 0,001ms
	TIM6->ARR = 9; // 0,01ms czyli 10us
	TIM6->CR1 |= TIM_CR1_CEN;
	TIM6 -> DIER |= TIM_DIER_UIE;

	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	//TIM6 -> CR1 |= TIM_CR1_OPM;
}
void tim2_init(void) // PWM
{

	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE0) | GPIO_MODER_MODE0_1;
	GPIOA->AFR[0] = (GPIOA->AFR[0] & ~GPIO_AFRL_AFRL0) | (2<<0);

	TIM2->PSC = 8; // preskaler ... czêstotliwoœc taktowania
	TIM2->ARR = 1000; // zliczanie do ... Auto-Reload Register // 500-1 (0.5Hz) 250-1(1Hz)

	//do PWM:
	TIM2->CCR1=0; // wartoœc porownania licznika?
	TIM2->CCER |= TIM_CCER_CC1E; //aktywujê dan¹ koñcówkê OCx
	//TIM2->CCMR1 = TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1; // wybieram tryb pracy i kierunek portów OCx "toggle" 011
	TIM2->CCMR1 = TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // pwm mode 1
	TIM2->CR1 |= TIM_CR1_CEN; //OKOKOKOKOK
	TIM2->BDTR |= TIM_BDTR_MOE;
	//TIM2->CR1 |= TIM_CR1_ARPE;
	//TIM2 wymaga ustawienia bitu MOE w rejestrze BDTR w celu uaktywnienia wyjœæ PWM
	TIM2->EGR |= TIM_EGR_UG; // jest napisane ¿e trzeba ustawic bit UG
	//TIM2->CR1 |= TIM_CR1_DIR;
	TIM2->DIER |= TIM_DIER_UIE;

	NVIC_EnableIRQ(TIM2_IRQn);
	//TIM2->BDTR |= TIM_BDTR_MOE;
	//TIM2 wymaga ustawienia bitu MOE w rejestrze BDTR w celu uaktywnienia wyjœæ PWM
	//DMA1_Channel5->CCR &= ~DMA_CCR_CIRC

	//TIM2->CR1 |= TIM_CR1_DIR; // zliczanie w górê
	//TIM2->CR1 |= TIM_CR1_ARPE;

	    /*
		    CCMR1 - wybierasz tryb pracy i kierunek portów OCx
			CCER - aktywujesz dan¹ koñcówkê OCx
			CR1 - kilka podstawowych parametrow pracy oraz wlasciwa aktywacja zliczania

		 */
}
void system_init(void)
{

	RCC->IOPENR |= RCC_IOPENR_GPIOAEN | RCC_IOPENR_GPIOBEN | RCC_IOPENR_GPIOCEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	//RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // do przerwañ zewnêtrznych chyba konieczne
	//SysTick konfiguracja
	SysTick->VAL =  0;
	SysTick->LOAD = FREQUENCY / 1000UL -1; //przerwanie co 1ms
	SysTick->CTRL =  SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk |  SysTick_CTRL_ENABLE_Msk;
}


void TIM6_DAC_IRQHandler(void){ // co 1ms
		if((TIM6 -> SR & TIM_SR_UIF) != 0)
			{
				TIM6 -> SR &= ~TIM_SR_UIF; // cleared by software

			}
			if(time_ms!=0) time_ms--; //



	}

void TIM2_IRQHandler(void){
	if(TIM2->SR & TIM_SR_UIF){ // TIM_SR_UIF -> flaga przerwania
		TIM2->SR = ~TIM_SR_UIF; //  kasuje flagê przerwania
		TIM2->CCR1 +=1;
		if(TIM2->CCR1==750) // tutaj wspó³czynnik wype³nienia?
		{
			TIM2->CCR1 =0;
		}
		//GPIOA->ODR ^= (1<<5);
		uint32_t n;
		n = Timer1;  /* 1000Hz Timer1 */
		if (Timer1) Timer1 = --n;
		n = Timer2;  /* 1000Hz Timer1 */
		if (Timer2) Timer2 = --n;

	}}

//void delay_us(int us)																/*funkcja generujaca dokladne opoznienie w us*/
//{
	/*time_us = us;
	TIM3 -> CNT = 0;
  while(time_us!=0);*/
//}
/*void delay_ms(uint16_t time) // GUT
{
  while(time--)
  {
	  TIM6->CR1 |= TIM_CR1_CEN;
	  while((TIM6->CR1 & TIM_CR1_CEN));

  }
}*/
// - SysTick->LOAD - wartoœæ "prze³adowania"
// - SysTick->CTRL - dla takiego dzia³ania jak chcesz ustawiasz tam bity SysTick_CTRL_ENABLE (w³¹cz liczenie), SysTick_CTRL_TICKINT (w³¹cz przerwanie) i SysTick_CTRL_CLKSOURCE (Ÿród³em zegara jest zegar rdzenia).
