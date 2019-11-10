#include "include/config.h"
#include "include/lcd.h"
#include "include/itoa.h"
#include "include/printf.h"
//#include"include/vt100.h"
#include "include/uart.h"
//#include "Klawiatura/Klawiatura.h"
#include "include/ds18b20.h"
//volatile int time_ms = 0; // wykorzystujê
//volatile int time_us = 0; // nie wykorzystujê
static uint8_t interruptFlag;
volatile uint32_t count=0, count_max = 1000;
volatile uint8_t tick_750ms=0;
//void rysuj_menu(void);


int main(void)
{

	uint8_t znak, temp, reszta;
	char buffer[20];

	system_init();
	rcc_config();
	tim6_init();
	tim2_init();
	usart_init();

	LCD_inicjalizacja();
	ow_init();
	char wynik[] = "              ";
	//ButtonGpio_init();
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE5) | GPIO_MODER_MODE5_0; // jako wyjœcie
	//GPIOA->ODR |= (1<<5); // linia DE stan wysoki -> nadawanie
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE6) | GPIO_MODER_MODE6_0; // jako wyjœcie
	GPIOA->ODR &= ~(1<<6); // linia DE/RE stan niski odbior
	// ds jest na pb6 i pb7 uart rs485 jest na pa2 i pa3
	while (1)
	{

		//ButtonPress(0x0020,3);// powinno byc nA pb5
		LCD_pozycjonowanie_kursora(0,0);
		//uart_ciag_znakow("Michal");
		if(tick_750ms){
		//uart_ciag_znakow("test");
			//GPIOB->ODR ^= (1<<8);
			GPIOA->ODR ^= (1<<5);
			tick_750ms=0;
			ds18b20_read_temperature(&znak, &temp, &reszta);
			sprintf_(buffer, ((znak == DS_ZNAK_MINUS) ? "-%d.%d\x7f""C":"T: %d.%d"), temp, (reszta*10)/16);
			LCD_pozycjonowanie_kursora(1,0);
			LCD_string(buffer);
			ds18b20_convert();

		}

		//tutaj ds
		/*tick_750ms = 0;
		ds18b20_read_temperature(&znak, &temp, &reszta);
		sprintf_(buffer, ((znak == DS_ZNAK_MINUS) ? "-%d.%d\x7f""C":"Temp: %d.%d\x7f""C"), temp, (reszta*10)/16);
		LCD_pozycjonowanie_kursora(3,2);
		LCD_string(buffer);
		ds18b20_convert();*/




		//LCD_pozycjonowanie_kursora(1,0);
		//LCD_string("T:     ");


	}


}


/*void delay_ms(int ms) // ok, funkcja generujaca dokladne opoznienia w ms
{
	time_ms = ms;
	//TIM6 -> CNT = 0;// Zerowanie licznika
	while(time_ms!=0); //Oczekiwanie na koniec odliczania
}*/
/**/

// Dwa przerwania

/*void TIM6_DAC_IRQHandler(void){ // co 1ms
		if((TIM6 -> SR & TIM_SR_UIF) != 0)
			{
				TIM6 -> SR &= ~TIM_SR_UIF; // cleared by software
			}
			if(time_ms!=0) time_ms--; //
	}*/

void SysTick_Handler(void)
{
	//uint32_t n;

	count++;
	if (count == count_max) // every 1s
	{
		count = 0;
		tick_750ms=1;
		//GPIOA->ODR ^= (1<<5);
		//GPIOA->ODR ^= (1<<6);
	}

}


/*void rysuj_menu(void)
	{
		tr_wylacz_atrybuty_kursor_on_off(0);
		// kolory
		kolor_czcionki(5); // yellow
		kolor_tla(0); // green
		// pozycjonowanie kursora i napis

		pozycjonowanie_kursora(2,5);
		uart_ciag_znakow("****STM32****");
		uart_ciag_znakow("**Cortex M0+**");


		kolor_tla(0);
		kolor_czcionki(4);
		pozycjonowanie_kursora(4,5);
		uart_ciag_znakow("1. Wkrótce coœ tu bêdzie");
		pozycjonowanie_kursora(5,5);
		uart_ciag_znakow("2. Wkrótce coœ tu bêdzie");
		pozycjonowanie_kursora(6,5);
		uart_ciag_znakow("3. Wkrótce coœ tu bêdzie");



		pozycjonowanie_kursora(8,5);
		uart_ciag_znakow("Wybierz opcje (1-3)");





	}*/

/*int sprintf_(char *buffer, const char *format, ...)
	 * char *buffer - wskaznik na bufor znaków do którego ma zostac zapisany tekst sformatowany
	 * const char *format - tekst sformatowany
	 * ... - opcjonalne argumenty, mo¿e byc wiêcej ni¿ jeden
	 */
	//sprintf_(bufor,"U=%d",liczba);

	/*char* itoa(int value, char* buffer, int base)
	 * int value - Liczba ca³kowita, która ma zostaæ przekonwertowanapp
	 * Miejsce w którym ma zostaæ zapisany wynik konwersji
	 * Podstawa systemu liczbowego w którym bêdzie zapisany wynik. Wartoœæ tego argumentu musi mieœciæ siê w przedziale od 2 do 36
	 */
