/*
 * uart.h
 *
 *  Created on: 5 paü 2015
 *      Author: Micha≥
 */
#include "config.h"
#include "itoa.h"

#ifndef USART_UART_H_
#define USART_UART_H_

extern volatile uint8_t infoCO;

void usart_init(void);
void uart_pojedynczy_znak(uint16_t ch);
void uart_ciag_znakow(char * str);
void uart_wyswietlanie_liczby(uint32_t liczba, uint8_t rodzaj);

#endif /* USART_UART_H_ */
