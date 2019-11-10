/*
 * ds18b20.h
 *
 *  Created on: 26 pa� 2015
 *      Author: Micha�
 */
#include "config.h"
#include "gpio.h"

#ifndef DS18B20_DS18B20_H_
#define DS18B20_DS18B20_H_


	//komendy ds18b20

	#define DS_SKIP_ROM 0xCC // u�ywam
	#define DS_CONVERT_T 0x44 // inicjalizuje pojedy�cz� konwersj� temperatury
	// Po zako�czeniu konwersji, jej rezulatat jest przechowywany w dwu-bajtowym rejestrze w pami�ci scrathpada

	#define DS_READ_SCRATCHPAD 0xBE // komenda ta pozwala odczytac uk�adowi master dane umieszczone w pami�ci scratchpada
	// transmisja rozpoczyna si� od najm�odszego bitu, od bajtu nr.0 i kontynuowana jest a� do dziewi�tego bajtu
	// Uk�ad mo�e wys�ac ��danie reset aby zako�czyc odczyt w dowolnym momencie

	//inne
	#define DS_ZNAK_PLUS 1 //u�ywam
	#define DS_ZNAK_MINUS 0 // u�ywam
	#define DS_ERROR 0 // u�ywam
	#define DS_OK 1 // u�ywam
	#define DS_CRC_ERROR 2 // u�ywam


	void ow_init(void);
	uint8_t uart_txrx(uint8_t data);

	//deklaracje funkcji
	void ow_write_1b(uint8_t data);
	uint8_t ow_read_1b(void);

	uint8_t ow_reset_pulse(void);
	void ow_write(uint8_t data);
	uint8_t ow_read(void);

	uint8_t ds18b20_read_temperature(uint8_t *znak, uint8_t *temperatur, uint8_t *reszta);
	uint8_t ds18b20_convert(void);



#endif /* DS18B20_DS18B20_H_ */
