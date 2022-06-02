#include <stdio.h>
#include "libpynq.h"


int main(void){
    while(1==1){
        led_colour(0,red,on);
        sleep_msec(500);
        led_colour(0,red,off);
        led_colour(0,green,on);
        sleep_msec(500);
        led_colour(0,green,off);
        led_colour(0,blue,on);
        sleep_msec(500);
        led_colour(0,blue,off);
    }
}
        
    
