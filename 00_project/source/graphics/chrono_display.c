#include "chrono_display.h"


void printDigit(u16* map, int number, int x, int y)
{
	int i,j;

	if(number >= 0 && number < 10)
		for(i = 0; i<8;i++)
			for(j = 0; j<4; j++)
				if(number >= 0)
					map[(i + y)*32+j+x] = (u16)(i*4+j)+32*number;
				else
					map[(i + y)*32+j+x] = 32;
}


void updateChronoDisp(u16* map,int min, int sec, int msec)
{
	int x = 0, y = 0;
	int number;
	int tile, i, j;

	//Clear the map
	for(tile = 0; tile <1024; tile++)
		map[tile] = 32;


	/*****MINUTES******/
	number = min;
	if(min > 59) min = number = -1;
	//First digit
	x = 0; y = 8;
	if(min>=0) number = min/10;
	printDigit(map, number, x,y);
	//Second digit
	x = 4; y = 8;
	if(min>=0) number = min %10;
	printDigit(map, number, x,y);

	/*****COLON******/
	x = 8; y = 8;
	for(i = 0; i<8;i++)
		for(j = 0; j<2; j++)
			map[(i + y)*32+j+x] = (u16)(i*4+j)+32*10+2;

	/*****SECONDS******/
	number = sec;
	if(sec > 59) sec = number = -1;
	//First digit
	x = 10; y = 8;
	if(sec>=0) number = sec / 10;
	printDigit(map, number, x,y);
	//Second digit
	x = 14; y = 8;
	if(sec>=0) number = sec % 10;
	printDigit(map, number, x,y);

	/*****POINT MSEC******/
	x = 18; y = 8;
	for(i = 0; i<8;i++)
		for(j = 0; j<2; j++)
			map[(i + y)*32+j+x] = (u16)(i*4+j)+32*10;

	/*****M.SECONDS******/
	number = msec;
	if(msec > 999) msec = number = -1;
	//First digit
	x = 20; y = 8;
	if(msec>=0) number = msec / 100;
	printDigit(map, number, x,y);

	//Second digit
	x = 24; y = 8;
	if(msec>=0) number = (msec % 100) / 10;
	printDigit(map, number, x,y);

	//Third digit
	x = 28; y = 8;
	if(msec>=0) number = (msec % 10) % 10;
	printDigit(map, number, x,y);
}


void changeColorDisp(uint16 b, uint16 c)
{
	//The olors are stored in the components 0 and 255 of the palette
	BG_PALETTE_SUB[0] = c;
	BG_PALETTE_SUB[255] = b;
}



