#include <stdio.h>
#include "libpynq.h"
#define HEIGHT 12
#define WIDTH 24

void draw_grid(int occupied[HEIGHT][WIDTH]) {
    int x,y;
    for (y = 0; y < HEIGHT; y++){
        for (x=0; x < WIDTH; x++){
            if (occupied[y][x] == 0){
                set_pixel(y,x,0,0,0);
            }
            if (occupied[y][x] == 1){
                set_pixel(y,x,255,0,0);
            }
        }
    }
    draw_display();
}
                

int main(void) {
    int x,y;
    pixel display[HEIGHT][WIDTH];
    init_display( HEIGHT, WIDTH, 20, display);
    int occupied[HEIGHT][WIDTH] = {};
    do {
        y = 0;
        x = WIDTH/2;
        set_pixel(x,y,255,0,0);
        while (y < HEIGHT-1 && occupied[y+1][x] == 0 ) {
            occupied[y][x] = 0;
            y++;
            occupied[y][x] = 1;
            draw_grid (occupied);
            sleep_msec_buttons_pushed(100);
            if (button_states[0] > 0){
                occupied[y][x] = 0;
                x++;
            }
            if (button_states[3] > 0){
                occupied[y][x] = 0;
                x--;
            }
            sleep_msec(100);
        }
    } while (y>1);
    sleep_msec(2000);
}
    
