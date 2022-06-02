#include <stdio.h>
#include "libpynq.h"
#define HEIGHT 12
#define WIDTH 24

int main(void) {
    int i,j;
    pixel display[HEIGHT][WIDTH];
    init_display( HEIGHT, WIDTH, 20, display);
    /*set_pixel(HEIGHT/2, WIDTH/2, 255, 255, 0);
    draw_display();*/
    
    for (i = 0; i < 12; i++){
        for (j = 0; j < 25; j++){
            if (i < 4){
                set_pixel(i,j,255,0,0);
                draw_display();
                sleep_msec(100);
            }

            if (i > 3 && i < 8){
                set_pixel(i,j,255,255,255);
                draw_display();
                sleep_msec(100);

            }
            if (i > 7 && i < 12){
                set_pixel(i,j,0,0,255);
                draw_display();
                sleep_msec(100);
            }
        }
    }
    sleep_msec(2000);
    clear_display();
    
    for (j = 0; j < 25; j++){
        for (i = 0; i < 12; i++){
            if (i < 4){
                set_pixel(i,j,255,0,0);
                draw_display();
                sleep_msec(100);
            }

            if (i > 3 && i < 8){
                set_pixel(i,j,255,255,255);
                draw_display();
                sleep_msec(100);

            }
            if (i > 7 && i < 12){
                set_pixel(i,j,0,0,255);
                draw_display();
                sleep_msec(100);
            }
        }
    }
    sleep_msec(2000);
}
    
    
