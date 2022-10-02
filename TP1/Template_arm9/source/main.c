/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>


int array[] = {0,1,2,3,4,5,6,7,8,9};


int main(void) {
	
    consoleDemoInit();
    for (int i = 0; i < 10; i++)
    {
        printf("Number %d", array[ i ] );
    }


    while(1)
        swiWaitForVBlank();	
}
