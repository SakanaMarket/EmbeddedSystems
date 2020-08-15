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

char * x;
char buffer[17] = {'\0'};
int myindex = 0;
int change = 0;
double prev = 0;

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


double parseNumber()
{
	double num = 0;
	while (*x >= '0' && *x <= '9')
	{
		num = num*10;
		num = (*x++ - '0') + num;
		
	}
	
	if (*x == '.')
	{
		++x;
		double weight = 10;
		double dec;
		while (*x >= '0' && *x <= '9')
		{
			dec = (*x++ - '0')/weight;
			num += dec;
			weight *= 10;
		}
	}
	
	return num;
}

double parseMod(double * before_result)
{
	double result;
	
	if (before_result == NULL)
	{
		result = parseNumber();
	}
	else
	{
		result = *before_result;
	}
	
	while (*x == '%')
	{
		int temp = (int) result;
		++x;
		double sec_num = parseNumber();
		temp %= (int) sec_num;
		result = (double) temp;
	}
	return result;
}

double parseExp(double * before_result)
{
	double result;
	
	if (before_result == NULL)
	{
		result = parseNumber();
	}
	else
	{
		result = *before_result;
	}
	
	while (*x == 'e')
	{
		++x;
		double sec_num = parseNumber();
		int i;
		for (i=0; i < sec_num; i++)
		{
			result *= 10;
		}
	}
	
	return result;
}

double parsePow(double * before_result)
{
	double result;
	
	if (before_result == NULL)
	{
		result = parseNumber();
	}
	else
	{
		result = *before_result;
	}
	
	while (*x == '^')
	{
		++x;
		int sec_num = parseNumber();
		
		int i;
		int temp = 1;
		for (i=0; i < sec_num; i++)
		{
			temp *= result;
			
		}
		result = temp;
	}
	
	return result;
}

double handle_special()
{
	double result = parseMod(NULL);
	while (*x != '+' && *x != '-' && *x != '\0' && *x != '*' && *x != '/')
	{
		result = parseExp(&result);
		result = parsePow(&result);
		result = parseMod(&result);
	}
	return result;
}

double parseMultiply(double * before_result)
{
	double result;
	
	if (before_result == NULL)
	{
		result = handle_special();
	}
	else
	{
		result = *before_result;
	}
	while (*x == '*')
	{
		++x;
		double sec_num = handle_special();
		result *= sec_num;
	}
	
	return result;
}

double parseDiv(double * before_result)
{
	double result;
	
	if (before_result == NULL)
	{
		result = handle_special();
	}
	else
	{
		result = *before_result;
	}
	while (*x == '/')
	{
		++x;
		double sec_num = handle_special();
		result /= sec_num;
	}
	
	return result;
}

double handle_mult_div()
{
	double result = parseMultiply(NULL);
	while (*x != '+' && *x != '-' && *x != '\0')
	{
		result = parseDiv(&result);
		result = parseMultiply(&result);
	}
	
	return result;
}

double parseSum()
{
	double result = handle_mult_div();
	while (*x == '+')
	{
		++x;
		double sec_num = handle_mult_div();
		result += sec_num;
	}
	
	return result;
}

double parseSub()
{
	double result = handle_mult_div();
	while (*x == '-')
	{
		++x;
		double sec_num = handle_mult_div();
		result -= sec_num;
	}
	
	return result;
}

double handle_sum_sub()
{
	double result = parseSum();
	while (*x != '\0')
	{
		result += parseSub();
		result += parseSum();
	}
	
	return result;
}

void clear_buffer()
{
	int i;
	for (i = 0; i < 17; i++)
	{
		buffer[i] = '\0';
	}
}

void update_buffer(int k)
{
	if (change == 0 && myindex < 17)
	{
		switch (k)
		{
			case 1:
				buffer[myindex] = '1';
				break;
			case 2:
				buffer[myindex] = '2';
				break;
			case 3:
				buffer[myindex] = '3';
				break;
			case 5:
				buffer[myindex] = '4';
				break;
			case 6:
				buffer[myindex] = '5';
				break;
			case 7:
				buffer[myindex] = '6';
				break;
			case 9:
				buffer[myindex] = '7';
				break;
			case 10:
				buffer[myindex] = '8';
				break;
			case 11:
				buffer[myindex] = '9';
				break;
			case 14:
				buffer[myindex] = '0';
				break;
			case 4:
				buffer[myindex] = '+';
				break;
			case 8:
				buffer[myindex] = '-';
				break;
			case 12:
				buffer[myindex] = '*';
				break;
			case 16:
				buffer[myindex] = '/';
				break;
			case 15: // switch operators
				change = 1;
				myindex -= 1;
				break;
			case 13:
				clear_buffer();
				lcd_clr();
				myindex = -1;
				break;
			default:
				myindex -= 1;
				break;
			
		}
	}
	else if (change == 1 && myindex < 17)
	{
		switch (k)
		{
			case 1:
				buffer[myindex] = '%';
				break;
			case 2:
				buffer[myindex] = 'e';
				break;
			case 3:
				buffer[myindex] = '^';
				break;
			case 4:
				buffer[myindex] = '.';
				break;
			case 15: // switch operators
				change = 0;
				myindex -= 1;
				break;
			case 13:
				clear_buffer();
				lcd_clr();
				myindex = -1;
				break;
			default:
				myindex -= 1;
				break;
		}
		
	}
	myindex++;
	
}

int main(void)
{
	int k;
	lcd_init();
	lcd_clr();
	while (1)
	{
		k = get_key();
		update_buffer(k);
		
		lcd_pos(0,0);
		lcd_puts(buffer);
		avr_wait(200);
		
		x = buffer;
	
		double result = handle_sum_sub();
		
		char buf[17];
		
		sprintf(buf, "%.3f", result);
		
		
		lcd_pos(1,0);
		lcd_puts(buf);
		
	}
	
}




