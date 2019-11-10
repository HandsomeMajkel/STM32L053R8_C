/*
 * ds18b20.c
 *
 *  Created on: 26 paŸ 2015
 *      Author: Micha³
 */
#include "include/ds18b20.h"


void set_baud(uint32_t baud) // ustawienie baudrate
{
	USART1->CR1 &= ~USART_CR1_UE;
	USART1->BRR = (FREQUENCY + baud / 2) / baud;
	USART1->CR1 |= USART_CR1_UE;
}
// po co ta funkcja? RESET PULSE i PRESENCE PULSE s¹ sygna³ami o stosunkowo d³ugim czasie trwania
// dlatego te¿ UART prze³¹czany jest w wolniejszy tryb. Powoduje to wyd³u¿enie próbkowania magistrali...
// do 1000us

void ow_init(void) // u¿ywam
{
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // w³¹czenie taktowania
	// configure GPIO TU JESZCZE ZMIANY DROBNE
	gpio_config(GPIO_OW_PORT, GPIO_OW_TX_pin, GPIO_MODER_ALTERNATE_FUNCTION, GPIO_OTYPE_OD, GPIO_SPEED_2MHz, GPIO_PUPDR_NO_PULL, GPIO_AF0);
	gpio_config(GPIO_OW_PORT, GPIO_OW_RX_pin, GPIO_MODER_ALTERNATE_FUNCTION, GPIO_OTYPE_OD, GPIO_SPEED_2MHz, GPIO_PUPDR_NO_PULL, GPIO_AF0);

	USART1->CR1 = USART_CR1_TE | USART_CR1_RE; // w³¹czenie linii s³u¿¹cych do nadawania i odbierania
	USART1->BRR = (FREQUENCY + 9600 / 2) / 9600;
	// wynik = ( a + b/2 ) / b
	// kwarce "przyjazne" i "nieprzyjazne" dla rs232
	//http://mirekk36.blogspot.com/2013/01/rs232-ubrr-jak-prawidowo-obliczac-trick.html

	USART1->CR1 |= USART_CR1_UE; // w³¹czenie uartu
}

uint8_t uart_txrx(uint8_t data)
{
	while(!(USART1->ISR & USART_ISR_TXE));
	USART1->TDR = data; // wpisanie wartoœci do rejestru

	while(!(USART1->ISR & USART_ISR_RXNE));

	return USART1->RDR; // odczytanie informacji zwrotnej z bufora UART(dziêki temu mogê okreœlic stan magistrali)

	/*
	 *  Jakikolwiek zapis do rejestru nadajnika interfejsu UART powoduje wygenerowanie bitu startu o wartoœci
	 *  zero, co powoduje wygenerowanie krótkiego impulsu ujemnego na 1-wire, który PORZEDZA WSZYSTKIE OPERACJE
	 *  ZAPISU I ODCZYTU
	 *
	 *  OD TEGO MOMENTU MO¯NA ZACZ¥C PRÓBKOWAC MAGISTRALÊ UART(w odstêpach czasowych okreœlonych przez zegar taktuj¹cy
	 *  UART)
	 *
	 *  Stan magistrali mo¿na okreœlic , odczytuj¹c zawartoœc z rejestru odbiornika
	 */
}

uint8_t ow_reset_pulse(void) // tutaj u¿yty set_baud bo jest RESET PULSE
{
	uint8_t temp;
	set_baud(9600); // dlaczego zmiana baudrate? RESET i PRESENCE PULSE s¹ sygna³ami o stosunkowo d³ugim czasie
	// trwania dlatego ustawiany jest w wolniejszy tryb 9600 bodów(dziêki temu wyd³u¿a siê czas próbkowania magistrali o 1000 us)

	temp = uart_txrx(0xF0); // wpisanie 0xF0 powoduje wygenerowanie RESET PULSE czyli sekwencjê inicjalizacyjn¹
	if(temp == 0xF0) return DS_ERROR;
	// o odebraniu sygna³u PRESENCE PULSE œwiadczy wartoœc rejestru ró¿na od 0xF0
	// gdy wartoœc rejsetru równa 0xF0 œwiadczy to o braku urz¹dzeñ na magistrali
	else return DS_OK;
}

void ow_write_1b(uint8_t data) // ta funkcja umo¿liwia nadawanie btów o wartoœci 0 lub 1
{
	// tutaj ju¿ zainicjalizowana magistrala wiêc mo¿na przejœc w tryb 115200 bodów
	if((data & 0x01)==1)//nam³odszy bit jest tym który wysy³amy, bo tak sobie przyj¹³em
	{
		set_baud(115200);
		uart_txrx(0xFF); // generowany impuls ujemny o czasie trwania ok 8,6us
		// oxFF to jeden bit
	}
	else
	{
		set_baud(115200);
		uart_txrx(0x00); // generowany impuls usjemny o czsie trwania ok 86 us
	}
}

uint8_t ow_read_1b(void) //odbiera jeden bit z magistrali
{
	set_baud(115200);
	uint8_t temp = uart_txrx(0xFF); // wpisanie do rejestru nadajnika 0xFF wi¹¿e siê z wygenerowaniem
	// krótkiego impulsu ujemnego(bitu startu). Jest to pocz¹tek procesu odczytu bitu z magistrali
	// przypisujê do zmiennej temp bo odczytujê temperaturê.

	if(temp == 0xFF)// u francuza w ksi¹¿ce jest tak napisane. Ma tak byc
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


// "WYSOKOPOZIOMOWE FUNKCJE:"

void ow_write(uint8_t data) // wysy³am bajt na magistralê
{
	uint8_t i;
	for(i=0;i<8;++i) // u¿ywam pêtli i niskopoziomowej funkcji do przes³ania 1 bitu i w ten sposób przys³am bajt
	{
		ow_write_1b(data); // tutaj u¿yta funkcja do przes³ania 1 bitu
		data= data>>1; //  przesuniêcie bitowe o jeden
	}
}

uint8_t ow_read(void) // odczyt bajtu z magistrali
{
	uint8_t i, temp, dat=0;
	for(i=0;i<8;++i)
	{
		temp = ow_read_1b();
		dat |= (0x01 & temp)<<i; // do ogarniêcia ta linijka
	}
	return dat; // to jak result u francuza
}

uint8_t ds18b20_convert(void)
{
	uint8_t error;
	error = ow_reset_pulse(); // tutaj zostaje przypisane to co zwróci funkcja
	if(error==DS_OK) // je¿eli zostanie wykryte urz¹dznie na magistrali to warunek spe³niony
	{
		ow_write(DS_SKIP_ROM); //  ma byc
		ow_write(DS_CONVERT_T); // pojedyñcza konwersja
		return DS_OK;
	}
	else return DS_ERROR;
}

uint8_t ds18b20_read_temperature(uint8_t *znak, uint8_t *temperatur, uint8_t *reszta)
{
	uint8_t ok, crc_temp=0, th, tl, temp_reszta, temperatura;//crc_temp, temp,
	uint32_t  t=0;
	//odczyt temp z ds
	ok = ow_reset_pulse();
	if(ok==DS_ERROR) return DS_ERROR;
	ow_write(DS_SKIP_ROM); // wczytujê komendê
	ow_write(DS_READ_SCRATCHPAD);
	tl = ow_read(); // tl
	th = ow_read(); // th


	//konwersja temp opisane na mikrokontrolery.blogspot
    //http://mikrokontrolery.blogspot.com/2011/04/temperatura-wyswietlacz-konwersja.html

	t = (((uint32_t)(th))<<8) + tl; // th to MSB tl to LSB ,  dlatego te¿ rzutowanie
	if(t>0x8FFF) // tabelka z digital output 0x8fff to -0,5 stopnia, wiêksze wartoœci to dalej temp ujemna
	{// z kolei mniejsze wartoœci to temperatura dodatnia
		//temperatura ujemna
		*znak = DS_ZNAK_MINUS; // wykorzystywane w mainie w wyra¿eniu warunkowym
		t = 0xFFFF-t+1; // +1 bo minus i ca³oœc zanegowana
		temp_reszta = (uint8_t)(0x000F & t); // na pierwszych czterech bitach czêœc u³amkowa
		// dlatego jest maska na tych bitach bo tylko t¹ czêœc chce miec
		temperatura = (uint8_t)(t>>4);
		*temperatur = temperatura;
		*reszta = temp_reszta;
	}
	else
	{
		//temperatura dodatnia
		*znak = DS_ZNAK_PLUS;
		temp_reszta = (uint8_t)(0x000F & t);
		temperatura = (uint8_t)(t>>4);
		*temperatur = temperatura;
		*reszta = temp_reszta;
	}
	if(crc_temp == 0) return DS_OK;
	return DS_CRC_ERROR;
}



