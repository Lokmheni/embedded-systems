/*
 * Random Number Generation Nintendo DS
 * Nov 2020
 */

#include <nds.h>
#include <stdio.h>
#include <time.h>

int main(void) {
	
    consoleDemoInit();
    srand(time(NULL));
    printf("Random number is %d\n", rand());
    while(1)
        swiWaitForVBlank();	
}
