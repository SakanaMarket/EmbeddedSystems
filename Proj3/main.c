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

#define A 114
#define As 107
#define B 101
#define C 96
#define Cs 90
#define D 85
#define Ds 80
#define E 76
#define F 72
#define Fs 68
#define G 64
#define Gs 60

#define S 125
#define Ei 250
#define Eis 375
#define Q 500
#define Qs 750
#define H 1000
#define Hs 1500
#define W 2000

#define A1 57
#define As1 54
#define B1 51
#define C1 48
#define Cs1 45
#define D1 43
#define Ds1 40
#define E1 38
#define F1 36
#define Fs1 34
#define G1 32
#define Gs1 30

struct note
{
	int freq;
	int duration;

};

void play_note(int freq, int duration)
{
	
	int k = duration/(freq * 0.00001 * 2 * 1000);
	
	int i;
	for(i=0; i<k; i++)
	{
		SET_BIT(PORTB,3);
		avr_waitp3(freq);
		CLR_BIT(PORTB,3);
		avr_waitp3(freq);
	}

	
}

void play_song(struct note note_list[], int song_length)
{
	int i;
	for (i=0; i<song_length; i++)
	{
		play_note(note_list[i].freq, note_list[i].duration);
	}
	
}


struct note mary[] = {{B,Q},{A,Q},{G,Q},{A,Q},{B,Q},{B,Q},{B,H},{A,Q},{A,Q},{A,H},{B,Q},{B,Q},{B,H},{B,Q},{A,Q},{G,Q},{A,Q},{B,Q},{B,Q},{B,H},{A,Q},{A,Q},{B,Q},{A,Q},{G,W}};
struct note AoT[] = {{F,Ei},{D,Ei},{E,Ei},{C,Ei},{A1,Ei},{F,Ei},{G,Ei},{E,Ei},{F,Ei},{E,Ei},{D,Ei},{C,Ei},{A1,Ei},{F,Ei},{G,Ei},{E,Ei},{F,Ei},{D,Ei},{E,Ei},{C,Ei},{A1,Ei},{F,Ei},{G,Ei},{E,Ei},{F,Ei},{E,Ei},{D,Ei},{C,Ei},{D,Ei},{D,Ei},{D,Ei},{E,Ei},{F,Ei},{G,Ei},{E,Ei},{D,Ei},{C,Ei},{C,Ei},{D,Ei},{E,Ei},{D,Ei},{E,Ei},{F,Ei},{E,Ei},{F,Ei},{G,Ei},{F,Ei},{G,Ei},{A1,Ei},{F,Ei},{F,Ei},{C,Ei},{F,Ei},{E,Ei},{D,Ei},{C,Ei},{D,Ei},{F,Ei},{F,Ei},{C,Ei},{F,Ei},{F,Q},{E,Ei},{D,Ei},{E,Ei},{F,Ei},{E,Ei},{C,Ei},{D,Ei},{E,Ei},{F,Ei},{E,Ei},{C,Ei},{D,Ei},{E,Ei},{F,Ei},{E,Ei},{C,Ei},{A1,Ei},{G,Ei},{F,Ei},{G,Ei},{G,Ei},{D,Ei},{E,Ei},{F,Ei},{E,Ei},{C,Ei},{D,Ei},{E,Ei},{F,Ei},{E,Ei},{C,Ei},{D,Ei},{E,Ei},{F,Ei},{E,Ei},{D,Ei},{C,Ei},{C,Ei},{A1,Ei},{G,Ei},{D,Ei},{E,Ei},{F,Ei},{E,Ei},{C,Ei},{D,Ei},{E,Ei},{F,Ei},{E,Ei},{C,Ei},{D,Ei},{E,Ei},{F,Ei},{E,Ei},{C,Ei},{A1,Ei},{G,Ei},{F,Ei},{G,Ei},{G,Ei},{D,Ei},{E,Ei},{F,Ei},{E,Ei},{C,Ei},{D,Ei},{E,Ei},{F,Ei},{E,Ei},{C,Ei},{D,Ei},{E,Ei},{F,Ei},{E,Ei},{D,Ei},{C,Ei},{D,Q},{A1,Ei},{F,Ei},{G,Ei},{E,Ei},{F,Ei},{E,Ei},{D,Ei},{C,Ei},{A1,Ei},{F,Ei},{G,Ei},{E,Ei},{F,Ei},{E,Ei},{D,Ei},{C,Ei},{A1,Ei},{F,Ei},{G,Ei},{E,Ei},{F,Ei},{E,Ei},{D,Ei},{C,Ei},{A1,Ei},{F,Ei},{G,Ei},{E,Ei},{F,Ei},{E,Ei},{D,Ei},{C,Ei},{A1,Ei},{F,Ei},{G,Ei},{E,Ei},{F,Ei},{E,Ei},{D,Ei},{C,Ei},{A1,Ei},{F,Ei},{G,Ei},{E,Ei},{F,Ei},{E,Ei},{D,Ei},{C,Ei},{A1,Ei},{F,Ei},{G,Ei},{E,Ei},{F,Ei},{E,Ei},{D,Ei},{C,Ei},{A1,Ei},{F,Ei},{G,Ei},{E,Ei},{F,Ei},{F,H}};
struct note renai[] = {{B1,Ei},{C1,Ei},{B1,Ei},{C1,Ei},{D1,Q},{B1,Ei},{C1,Ei},
{B1,Ei},{C1,Ei},{D1,Q},{D,Ei},{C1,Ei},{B1,Ei},{C1,Ei},
{B1,S},{Gs,Ei},{Gs,Ei},{Gs,S},{E,Ei},{B1,S},{Gs,Ei},{Gs,Eis},{Gs,S},{E,Ei},
{Gs,Eis},{Gs,Eis},{Gs,S},{E,Ei},{B1,H},
{B1,Ei},{C1,Ei},{B1,Ei},{C1,Ei},{D1,Q},{B1,Ei},{C1,Ei},
{B1,Ei},{C1,Ei},{D1,Q},{D,Ei},{C1,Ei},{B1,Ei},{C1,Ei},
{B1,S},{Gs,Ei},{Gs,Ei},{Gs,S},{E,Ei},{B1,S},{Gs,Ei},{Gs,Eis},{Gs,S},{A,Ei},
{Gs,S},{Gs,Ei},{Gs,Ei},{Gs,S},{B1,Ei},{Gs,Q},
{D1,Q},{B1,Q},{A1,Q},{B1,Q},
{A1,Ei},{Gs,Ei},{A1,Ei},{B1,Qs},{B1,Ei},
{E1,Q},{B1,Q},{A1,Q},{Gs,Ei},{Gs,Ei},
{Gs,Ei},{A1,Ei},{B1,Ei},{A1,H},
{D1,Q},{B1,Q},{A1,Q},{B1,Q},
{A1,Ei},{Gs,Ei},{A1,Ei},{B1,Qs},{B1,Ei},
{E1,Q},{B1,Q},{Gs,Q},{B1,Q},
{Gs,Hs}};
char *song_list_name[50] = {"Mary Little Lamb","ShingekiNoKyojin", "RenaiCirculation"};

int n = 3;

int song_length[3] = {sizeof(mary)/sizeof(mary[0]), sizeof(AoT)/sizeof(AoT[0]), sizeof(renai)/sizeof(renai[0])};
	

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
/*
int main(void)
{
    
	//char char_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'};
	extern int set_display;
	int k;
	struct dt startdate = {11, 30, 2020, 11, 59, 50, 0};
	
	SET_BIT(DDRB, 0);
	
	lcd_init();
    while (1) 
    {
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
}*/

void display_song_name(int index)
{
	char buffer[17];
	sprintf(buffer, "%s", song_list_name[index]);
	//sprintf(buffer, "%d", index);
	lcd_pos(0,0);
	lcd_puts(buffer);
	
	if(index != n-1)
	{
		sprintf(buffer, "%s", song_list_name[index+1]);
		//sprintf(buffer, "%d", index);
		lcd_pos(1,0);
		lcd_puts(buffer);
	}
	
}

int main(void)
{
	lcd_init();
	SET_BIT(DDRB,3);
	
	int k;
	
	struct note *song_list[3] = {mary,AoT, renai};
	
	
	//play_song(song_list[1], song_length[1]);
	
	int song_index = 0;
	int note_index = 0;
	
	int playing = 0;
	
	display_song_name(song_index);
	
	while(1)
	{
		
		k = get_key();
		
		switch(k)
		{
			case 1:
				playing = 0;
				break;
			case 2:
				playing = 1;
				break;
			case 3: // prev
				if(song_index > 0)
				{
					song_index--;
					note_index = 0;
				}
				lcd_clr();
				display_song_name(song_index);
				avr_wait(200);
				break;
			case 4: //next
				if(song_index<n-1)
				{
					song_index++;
					note_index = 0;
				}
				lcd_clr();
				display_song_name(song_index);
				avr_wait(200);
				break;
		}
		
		if (playing == 0)
		{
			if (note_index == song_length[song_index])
			{
				note_index = 0;
				avr_wait(200);
			}
			play_note(song_list[song_index][note_index].freq, song_list[song_index][note_index].duration);
			note_index++;
		}
		
	}
}




