#include <stdio.h>
#include "libpynq.h"
#define HEIGHT 15
#define WIDTH 10

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
    int level, delay, score = 0;
    char again; 
    do{
        printf("Would you like an easy (3), moderate (2) or hard (1) game? ");
        scanf("%d", &level);
        if (level == 1){
        delay = 100;
        }
        if (level == 2){
            delay = 200;
        }
        if (level == 3){
        delay = 300;
        }
        printf("Game stats in 1 second\n");
        sleep_msec(1000);
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
                sleep_msec_buttons_pushed(30);
                if (button_states[0] > 0){
                    if (occupied[y][x+1] == 0){
                        occupied[y][x] = 0;
                        x++;
                        occupied[y][x] = 1;
                    }
                }
                if (button_states[3] > 0){
                    if (occupied[y][x-1] == 0){
                        occupied[y][x] = 0;
                        x--;
                        occupied[y][x] = 1;
                    }
                }
                sleep_msec(delay);
            }
        score++;
        int count, a, b, c, d;
            for (b = 0; b < HEIGHT; b++){
                count = 0;
                for (a = 0; a < WIDTH; a++){
                    if(occupied[b][a] == 1){
                        if(occupied[b][a] == occupied[b][a+1]){
                            count++;
                        }
                    }
                }
                if(count == WIDTH - 1){
                    for (d = HEIGHT-2; d > -1; d--){
                        for (c = 0; c < WIDTH; c++){
                            occupied[d+1][c] = occupied[d][c];
                        }
                    }
                }
            }

        } while (y>1);
        sleep_msec(2000);
        printf("Your score is %d blocks!\n", score);
        printf("Would you like to play again [yn]? ");
        scanf(" %c", &again);
    }while(again == 'y');
    printf("Bye!\n");
}
