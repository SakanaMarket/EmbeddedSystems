/*
 * Proj1.c
 *
 * Created: 4/13/2020 9:05:00 PM
 * Author : Matthew Tran & Leon Luo
 */ 

#include <avr/io.h>
#include "avr.h"
#include "avr.c"
#include "lcd.h"
#include "lcd.c"
#include <stdio.h>
#include <stdlib.h>

struct reading{
	int current;
	int min;
	int max;
	long sum;
	int cnt;
	int sampling;
	};

struct reading stat = {0, 999, 0, 0, 0, 0};

void update_stats(int s)
{
	stat.current = s;
	if (stat.sampling == 0)
	{
		if (stat.min > s)
		{
			stat.min = s;
		}
		if (stat.max < s)
		{
			stat.max = s;
		}
		stat.sum += s;
		stat.cnt += 1;
	}
	
}

int get_sample()
{
	CLR_BIT(ADMUX, 7);
	SET_BIT(ADMUX, 6);
	
	CLR_BIT(ADMUX, 4);
	CLR_BIT(ADMUX, 3);
	CLR_BIT(ADMUX, 2);
	CLR_BIT(ADMUX, 1);
	CLR_BIT(ADMUX, 0);
	
	SET_BIT(ADCSRA, 7);
	SET_BIT(ADCSRA, 6);
	
	while(GET_BIT(ADCSRA, 6));
	
	return ADC;
}

void stop_reading()
{
	stat.max = 0;
	stat.min = 999;
	stat.sum = 0;
	stat.cnt = 0;
	stat.sampling = 1;
}

void start_reading()
{
	
	stat.sampling = 0;
}

void display()
{
	char buffer[17];
	
	float curry = stat.current/1024.0 * 5.0;
	
	float avg = (stat.sum/stat.cnt)/1024.0 * 5.0;
	float max = stat.max/1024.0 * 5.0;
	float min = stat.min/1024.0 * 5.0;
	
	if (stat.sampling == 0 || stat.min != 999)
	{
		sprintf(buffer, "C:%4.2fV A:%4.2fV", curry, avg);
		lcd_pos(0,0);
		lcd_puts(buffer);
		
		sprintf(buffer, "Mn:%4.2fVMx:%4.2fV", min, max);
		lcd_pos(1,0);
		lcd_puts(buffer);
	}
	else
	{
		sprintf(buffer, "C:%4.2fV A:----V", curry);
		lcd_pos(0,0);
		lcd_puts(buffer);
		
		sprintf(buffer, "Mn:----VMx:----V");
		lcd_pos(1,0);
		lcd_puts(buffer);
	}
	
}

void empty_display()
{
	lcd_clr();
	char buffer[17];
	lcd_pos(0,0);
	sprintf(buffer, "C:----V A:----V");
	lcd_puts(buffer);
	lcd_pos(1,0);
	sprintf(buffer, "Mn:----VMx:----V");
	lcd_puts(buffer);
}

int is_pressed(int r, int c)
{
	DDRC = 0;
	PORTC = 0;
	SET_BIT(DDRC,r);
	CLR_BIT(PORTC,r);
	SET_BIT(PORTC, c+4);
	avr_wait(1);
	if (GET_BIT(PINC, c+4)==0)
	{
		return 0;
	}
	return 1;
	
}

int get_key(void)
{
	int r,c;
	for (r=0; r < 4; r++)
	{
		for (c=0; c<4; c++)
		{
			if (is_pressed(r,c)==0)
			{
				return r*4+c+1;
			}
			
		}
	}
	return 0;
}



int main(void)
{
	lcd_init();
	//char buf[17];
	
	int k;
	int s;
	empty_display();
	while(1)
	{
		k = get_key();
		s = get_sample();
		lcd_clr();
		switch(k)
		{
			case 1: // start
				start_reading();
				break;
			case 2: // reset -----
				stop_reading();
				break;
		}
		update_stats(s);
		display();
		avr_wait(500);
		
	}
}




