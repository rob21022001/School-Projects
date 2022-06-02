#include <stdio.h>
#include "libpynq.h" 
int main (void) {
    int waited;
    printf("please press button 0\n");
    while (button_state (0) == released) {
    }
    led_onoff(0,on);
    while(button_state(0) == pushed) {

        waited = wait_until_button_released(0);
        printf("we waited %d miliseconds\n", waited);
    }
    led_onoff(0,off);
}
