#include <stdio.h>
#include "libpynq.h" 
int main (void) {
    int waited;
    while (1==1) {
        printf("Waiting for 0 to be pressed\n");
        waited = wait_until_button_pushed(0);
        printf("we waited %d miliseconds\n", waited);
    }
}
