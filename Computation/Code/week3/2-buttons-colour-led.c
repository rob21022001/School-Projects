#include <stdio.h>
#include "libpynq.h"


int main(void){
    while(1==1){
        for(int button=0;button<3;button++){
            led_colour(0,button,button_state(button));
        }
    }
}
