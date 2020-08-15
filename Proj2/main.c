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

static int set_display = 0; //military by default

struct dt
{
	int month;
	int day;
	int year;
	int hour;
	int min;
	int sec;
	int msec;
};

int inc_x_by_num_til_positive(int x, int num)
{
	while (x < 0)
	{
		x+=num;
	}
	return x;
}

int get_num_days_in_month(int month, int year)
{
	int mm = inc_x_by_num_til_positive(month, 12);
	char days_in_mm[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if (mm != 1)
	{
		return days_in_mm[mm];
	}
	else
	{
		if (year % 4 == 0)
		{
			if (year % 100 == 0)
			{
				if (year % 400 == 0)
				{
					return 29;
				}
				return days_in_mm[mm];
			}
			return 29;
		}
		return days_in_mm[mm];
	}
}

void calc_months(struct dt *dt, int c)
{
	
	while (dt->day > get_num_days_in_month(dt->month, dt->year) || dt->day <= 0)
	{
		if (c == 0)
		{
			dt->day -= get_num_days_in_month(dt->month, dt->year);
			dt->month += 1;
		}
		else
		{
			dt->day += get_num_days_in_month(dt->month-1, dt->year);
			dt->month -= 1;
		}	
	}
}

void update_time(struct dt *dt)
{
	int msec = dt->msec/1000;
	if (msec > 0)
	{
		dt->msec %= 1000;
		dt->sec += msec;
	}
	int sec = dt->sec/60;
	if (sec > 0)
	{
		dt->sec %= 60;
		dt->min += sec;
	}
	int min = dt->min / 60;
	if (min > 0)
	{
		dt->min %= 60;
		dt->hour += min;
	}
	int hour = dt->hour / 24;
	if (hour > 0)
	{
		dt->hour %= 24;
		dt->day += hour;
	}
	int day = dt->day - get_num_days_in_month(dt->month, dt->year);
	if (day > 0)
	{
		calc_months(dt, 0);
	}
	int month = dt->month / 12;
	if (month > 0)
	{
		dt->month %= 12;
		dt->month -= 1;
		dt->year += month;
	}
}

void update_dec_time(struct dt *dt)
{
	int sub;
	if (dt->sec < 0)
	{
		sub = abs(dt->sec/60) + 1;
		dt->sec = inc_x_by_num_til_positive(dt->sec, 60);
		dt->min -= sub;
	}
	if (dt->min < 0)
	{
		sub = abs(dt->min/60) + 1;
		dt->min = inc_x_by_num_til_positive(dt->min, 60);
		dt->hour -= sub;
	}
	if (dt->hour < 0)
	{
		sub = abs(dt->hour/24) + 1;
		dt->hour = inc_x_by_num_til_positive(dt->hour, 24);
		dt->day -= sub;
	}
	if (dt->day <= 0)
	{
		calc_months(dt, 1);
	}
	if (dt->month < 0)
	{
		sub = abs(dt->month/12) + 1;
		dt->month = inc_x_by_num_til_positive(dt->month, 12);
		dt->year -= sub;
	}
	if (dt->year < 0)
	{
		dt->year = 0;
	}
}

void inc_time(struct dt *dt, unsigned int msec)
{
	dt->msec += msec;
	update_time(dt);
}


void display_dt(struct dt *dt)
{
	char buffer[17];
	sprintf(buffer, "%02d/%02d/%04d", dt->month+1, dt->day, dt->year);
	lcd_pos(0, 3);
	lcd_puts(buffer);
	
	sprintf(buffer, "%02d:%02d:%02d", dt->hour, dt->min, dt->sec);
	lcd_pos(1, 3);
	lcd_puts(buffer);
	
}

void display_dt_ampm(struct dt *dt)
{
	char buffer[17];
	sprintf(buffer, "%02d/%02d/%04d", dt->month+1, dt->day, dt->year);
	lcd_pos(0, 3);
	lcd_puts(buffer);
	
	if (dt->hour < 12)
	{
		if (dt->hour == 0)
		{
			sprintf(buffer, "%02d:%02d:%02d AM", 12, dt->min, dt->sec);
		}
		else
		{
			sprintf(buffer, "%02d:%02d:%02d AM", dt->hour, dt->min, dt->sec);
		}
		
	}
	else
	{
		if (dt->hour != 12)
		{
			sprintf(buffer, "%02d:%02d:%02d PM", dt->hour-12, dt->min, dt->sec);
		}
		else
		{
			sprintf(buffer, "%02d:%02d:%02d PM", dt->hour, dt->min, dt->sec);
		}
	}
	lcd_pos(1, 3);
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

void handle_keys(int k, struct dt *dt)
{
	switch(k)
	{
		case 1:
			dt->month += 1;
			update_time(dt);
			break;
		case 2:
			dt->day += 1;
			update_time(dt);
			break;
		case 3:
			dt->year += 1;
			update_time(dt);
			break;
		case 5:
			dt->month -= 1;
			update_dec_time(dt);
			break;
		case 6:
			dt->day -= 1;
			update_dec_time(dt);
			break;
		case 7:
			dt->year -= 1;
			update_dec_time(dt);
			break;
		case 9:
			dt->hour += 1;
			update_time(dt);
			break;
		case 10:
			dt->min += 1;
			update_time(dt);
			break;
		case 11:
			dt->sec += 1;
			update_time(dt);
			break;
		case 13:
			dt->hour -= 1;
			update_dec_time(dt);
			break;
		case 14:
			dt->min -= 1;
			update_dec_time(dt);
			break;
		case 15:
			dt->sec -= 1;
			update_dec_time(dt);
			break;
		case 4:
			lcd_clr();
			if (set_display == 0)
			{
				set_display = 1;
			}
			else
			{
				set_display = 0;
			}
			break;
	}
}

int main(void)
{
    /* Replace with your application code */
	//char char_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'};

	int k;
	struct dt startdate = {11, 30, 2020, 11, 59, 50, 0};
	
	SET_BIT(DDRB, 0);
	
	lcd_init();
    while (1) 
    {
		/*
		k = get_key();
		if (!k)
		{
			lcd_clr();
		}
		else
		{
			lcd_pos(1,0);
			lcd_put(char_table[k-1]);
		}
		*/
		k = get_key();
		
		if(k)
		{
			handle_keys(k, &startdate);
		}
		avr_wait(200);
		inc_time(&startdate, 200);
		if (set_display == 0)
		{
			display_dt(&startdate);
		}
		else
		{
			display_dt_ampm(&startdate);
		}
		
		
		
    }
}




