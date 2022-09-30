/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>

int main(void) {
	
    consoleDemoInit();
    printf("\nHello World Did you ever hear the tragedy of darth plageious the wise!?\n");

    while(1)
        swiWaitForVBlank();	
}
