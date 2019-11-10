/*
 * uart.c
 *
 *  Created on: 5 paŸ 2015
 *      Author: Micha³
 */

#include "include/uart.h"


uint8_t text [] = "Michal";
volatile uint8_t infoCO;

void usart_init(void)
{

	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	//RX:(jako input bez rezystorów podci¹gaj¹cych,chyba nie trzeba)
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE3)) | GPIO_MODER_MODE3_1; // funkcja alternatywna na pinie 3
	GPIOA->AFR[0] = (GPIOA->AFR[0] & ~GPIO_AFRL_AFRL3) | (4<<12); // pin 3 AF4(0100)
	//GPIOA->PUPDR = (GPIOA->PUPDR & ~GPIO_PUPDR_PUPD3) | GPIO_PUPDR_PUPD3_1; // pull-down
	//TX(jako wyjœcie i chyba rezystory podci¹gaj¹ce, chyba nie trzeba stan wysoki jest domyœlnie):
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE2)) | GPIO_MODER_MODE2_1; // funkcja alternatywna na pinie 2
	GPIOA->AFR[0] = (GPIOA->AFR[0] & ~GPIO_AFRL_AFRL2) | (4<<8); // pin 2 AF4(0100)
	//GPIOA->PUPDR = (GPIOA->PUPDR & ~GPIO_PUPDR_PUPD2) | GPIO_PUPDR_PUPD2_0; // pull-up



	USART2->CR1 = 0;
	USART2->BRR = (FREQUENCY + 9600 / 2) / 9600;
	//USART2->BRR = FREQUENCY/9600;
	USART2->CR1 =  USART_CR1_TE  | USART_CR1_UE | USART_CR1_RE | USART_CR1_RXNEIE;

	//while((USART2->ISR & USART_ISR_TC) != USART_ISR_TC)
	  //{
	    //add time out here for a robust application
	 // }
	  //USART2->ICR |= USART_ICR_TCCF; /* clear TC flag
	  //USART2->CR1 |= USART_CR1_TCIE; /* enable TC interrupt

	NVIC_EnableIRQ(USART2_IRQn);


}

void uart_pojedynczy_znak(uint16_t ch)
{
	//GPIOA->ODR = (GPIOA->ODR & ~GPIO_ODR_OD5) | GPIO_ODR_OD5;
	while(!(USART2->ISR & USART_ISR_TXE));
	USART2->TDR = ch;
	//GPIOA->BRR = (1<<5);
	//GPIOA->ODR = (GPIOA->ODR & ~GPIO_ODR_OD5) | ~GPIO_ODR_OD5;
	//USART2->TDR
}

void uart_ciag_znakow(char * str)
{
	while(*str != 0)
	{
		uart_pojedynczy_znak(*str);
		str++;
	}
}
void uart_wyswietlanie_liczby(uint32_t liczba, uint8_t rodzaj)
{
	char bufor[17];
	itoa(liczba,bufor,rodzaj);
	uart_ciag_znakow(bufor);
}
void USART2_IRQHandler(void)
{
	//uint8_t chartoreceive = 0;

	  if((USART2->ISR & USART_ISR_RXNE) == USART_ISR_RXNE)
	  {
	    infoCO = (uint8_t)(USART2->RDR);
	  }
	  else
	  {
	    NVIC_DisableIRQ(USART2_IRQn);
	  }
}


/*void USART2_IRQHandler(void)
{
	uint8_t chartoreceive = 0;

	  if((USART2->ISR & USART_ISR_RXNE) == USART_ISR_RXNE)
	  {
	    chartoreceive = (uint8_t)(USART2->RDR);

	    switch(chartoreceive)
	    {

	    case 'g': GPIOA->ODR ^= (1<<5);
	              break;
	    default: break;
	    }
	  }
	  else
	  {
	    NVIC_DisableIRQ(USART2_IRQn);
	  }
}*/
