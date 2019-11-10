/*
 * lcd.h
 *
 *  Created on: 31 sie 2015
 *      Author: Micha³
 */
#include "config.h"
//#include "ITOA/itoa.h"

#ifndef LCD_H_
#define LCD_H_

#ifdef __cplusplus
extern "C" {
#endif
//extern void delay_ms(int ms);														/*funkcja generujaca dokladne opoznienia w ms*/
//extern void delay_us(int us);														/*funkcja generujaca dokladne opoznienia w us*/

void gpio_inicjalizacja(void);
void LCD_wystlanie_bajtu_na_raty(uint8_t bajt);
void LCD_inicjalizacja(void);
void LCD_wczytywanie_komendy(uint8_t komenda);
void LCD_wystlanie_znaku_na_raty(uint8_t ASCII);
void LCD_string(char* Napis);
void LCD_pozycjonowanie_kursora(uint8_t y, uint8_t x);
void LCD_wyswietlanie_liczby(uint8_t liczba, uint8_t rodzaj);

#ifdef __cplusplus
}
#endif

#endif /* LCD_H_ */
