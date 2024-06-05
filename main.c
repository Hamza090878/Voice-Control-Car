#include "TM4C123.h"
#include <stdint.h>
#include <stdlib.h>
void SystemInit(){}
void Delay(unsigned long counter);        // Used to add delay
void HC05_init(void);                     // Initialize UART5 module for HC-05
char Bluetooth_Read(void);                // Read data from Rx5 pin of TM4C123
void Bluetooth_Write(unsigned char data); // Transmit a character to HC-05 over Tx5 pin 
void Bluetooth_Write_String(char *str);   // Transmit a string to HC-05 over Tx5 pin 
int main(void)
	{
		HC05_init(); // call HC05_init() to initialze UART5 of TM4C123GH6PM
		

		
					SYSCTL->RCGCGPIO |= 0x21;   /* enable clock to GPIOA*/
					GPIOA->DIR |= 0x5C;   // set PA2,PA3 , PA4 And PA6 as digital output pin
					GPIOA->DEN |= 0x5C;   // CON PA2,PA3 ,PA4 And PA6 as digital GPIO pins
					GPIOF->DIR |= 0x0E;   // set PF1,PF2 , PF3  as digital output pin
					GPIOF->DEN |= 0x0E;   // CON PF1,PF2 , PF3  as digital GPIO pins
						
		Delay(10); 
		
		while(1)
			{	
				char str[10];
				int j;
				int x;
				
				x = strlen(Bluetooth_Read);
				
				for(j=0;j<x;j++)       /* get a character from UART5 */
					{
						str[j] = Bluetooth_Read(); 
					}			
				
					
				if( str[0]=='F' || str[0]=='f')
					{
						GPIOA->DATA |=((1<<4)| (1<<3));
						GPIOF->DATA |= (1<<3);
						Bluetooth_Write_String("Car Move Forward\n");
						
					}
					
				else if( str[0]=='B'|| str[0]=='b')
					{
						GPIOA->DATA |= ((1<<2)| (1<<6));
						GPIOF->DATA |= ((1<<1) |(1<<2) |(1<<3));
						Bluetooth_Write_String("Car Moves Back\n");
					}
					
				else if( str[0]=='R'|| str[0]=='r')
					{
						GPIOA->DATA |=(1<<3);
						GPIOF->DATA |= ((1<<1) | (1<<3));
						Delay(1000000);	
						GPIOF->DATA &=~((1<<1) | (1<<3));			  
						GPIOA->DATA &=~((1<<2)| (1<<3) | (1<<4) | (1<<6));
						GPIOF->DATA |=(1<<1);
						Delay(1000000);
						GPIOF->DATA &=~(1<<1);
						GPIOA->DATA =((1<<3) | (1<<4));
						GPIOF->DATA |=(1<<2);
						Bluetooth_Write_String("Car Move Right\n");
					}
					
				else if (str[0]=='L'|| str[0]=='l')
					{
						GPIOA->DATA |=(1<<4);
						GPIOF->DATA |= ((1<<1) | (1<<2));
						
						Delay(1000000);	
						GPIOF->DATA &=~((1<<1) | (1<<2));
						GPIOA->DATA &=~((1<<2)| (1<<3) | (1<<4) | (1<<6));
						GPIOF->DATA |=(1<<1);
						Delay(1000000);
						GPIOF->DATA &=~(1<<1);
						GPIOA->DATA =((1<<3) | (1<<4));
						GPIOF->DATA |=(1<<2);
						Bluetooth_Write_String("BLUE LED OFF\n");
					}
					
				else if (str[0] =='S'|| str[0]=='s')
					{
						GPIOA->DATA &=~((1<<2)| (1<<3) | (1<<4) | (1<<6));
						GPIOF->DATA &= ~((1<<3)|(1<<2)|(1<<1));
						GPIOF->DATA |= (1<<1);
						Bluetooth_Write_String("Car Stops Completely\n");
				  } 
		}
	}

void HC05_init(void)
	{
		SYSCTL->RCGCUART |= 0x20;  /* enable clock to UART5 */
		SYSCTL->RCGCGPIO |= 0x10;  /* enable clock to PORTE for PE4/Rx and PE5/Tx */
		
		Delay(1);
		
		/* UART5 initialization */
		
		UART5->CTL = 0;           /* UART5 module disbable */
		UART5->IBRD = 104;        /* for 9600 baud rate, integer = 104 */
		UART5->FBRD = 11;         /* for 9600 baud rate, fractional = 11*/
		UART5->CC = 0;            /* select system clock*/
		UART5->LCRH = 0x60;       /* data lenght 8-bit, not parity bit, no FIFO */
		UART5->CTL = 0x301;       /* Enable UART5 module, Rx and Tx */

		/* UART5 TX5 and RX5 use PE4 and PE5. Configure them digital and enable alternate function */
		
		GPIOE->DEN = 0x30;        /* set PE4 and PE5 as digital */
		GPIOE->AFSEL = 0x30;      /* Use PE4,PE5 alternate function */
		GPIOE->AMSEL = 0;         /* Turn off analog function of UART5*/
		GPIOE->PCTL = 0x00110000;  /* configure PE4 and PE5 for UART */
	}
	
char Bluetooth_Read(void)  
	{
		int i;
		char data[10];
		
		while((UART5->FR & (1<<4)) != 0); /* wait until Rx buffer is not full */
		
		for(i=0;i<10;i++)
			{
				data[i] = UART5->DR ;
				return (unsigned char) data[i];	
			}			/* before giving it another byte */ 
	}

void Bluetooth_Write(unsigned char data)  
	{
		while((UART5->FR & (1<<5)) != 0); /* wait until Tx buffer not full */
		UART5->DR = data;                 /* before giving it another byte */
	}

void Bluetooth_Write_String(char *str)
	{
		while(*str)
		{
			Bluetooth_Write(*(str++));
		}
	}

void Delay(unsigned long counter)
	{
		unsigned long i = 0;
		
		for(i=0; i< counter; i++);
	}