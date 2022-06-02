#include <stdio.h>
#include "libpynq.h" 
int main (void) {
    
    if (button_state(0) == 1) {
        printf("button 0 is pushed\n" );
    }
    else{
        printf("button 0 is released\n");
    }
}
    
    
