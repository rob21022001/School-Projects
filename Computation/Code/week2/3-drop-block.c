#include <stdio.h>
#include "libpynq.h"
#define HEIGHT 24
#define WIDTH 12

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
    
    
    for (y = 0; y < HEIGHT; y++){
        x = WIDTH/2;
        occupied[y][x] = 1;
        draw_grid (occupied);
        sleep_msec(200);
        occupied[y][x] = 0;
        
    }
    
}
    
    
