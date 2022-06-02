#include <stdio.h> // for printf, scanf, putchar, etc.
#include <string.h> // for strlen
#include <ctype.h> // for tolower
#include "libpynq.h"
void printchar (char c) {
putchar(c);
fflush(NULL);
sleep_msec(100);
}

int isconsonant(char c){
    if(c == 'b' || c == 'c' || c == 'd' || c == 'f' || c == 'g' || c == 'h' || c == 'j' || c == 'k' || c == 'l' || c == 'm' || c == 'n' || c == 'p'|| c == 'q' || c == 'r' || c == 's' || c == 't' || c == 'v' || c == 'w' || c == 'x' || c == 'y' || c == 'z'){ 
        led_colour(0,red,on);
        sleep_msec(500);
        led_colour(0,red,off);

    }
}
int isvowel(char c){
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
        led_colour(0,blue,on);
        sleep_msec(500);
        led_colour(0,blue,off);
    }
}
int is0to9(char c){
    if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9'){
        led_colour(0,green,on);
        sleep_msec(500);
        led_colour(0,green,off);
    }
}

void printstring (char s[]) {
    int d, i, d3, d2, d1, d0;
    char c;
    for(i = 0;; i++){
        c = s[i];
        printchar(c);
        c = tolower(c);
        d = c%16;
        d0 = 0;
        d1 = 0;
        d2 = 0;
        d3 = 0;
        if(d > 7){
            d3 = 1;
            if ((d-8) >3){
                d2 = 1;
                if ((d-12) > 1){
                    d1 = 1;
                    if ((d-14) > 0){
                        d0 = 1;
                    }
                }
            }
        }
        else if(d >3){
            d2 = 1;
            if ((d-4) > 1){
                d1 = 1;
                if ((d-6) > 0){
                    d0 = 1;
                }
            }
        }
        else if(d > 1){
            d1 = 1;
            if ((d-3) > 0){
                d0 = 1;
            }
        }
        else if(d > 0){
            d0 = 1;
        }
        else{
        }
        led_onoff(0,d0);
        led_onoff(1,d1);
        led_onoff(2,d2);
        led_onoff(3,d3);
        isconsonant(c);
        isvowel(c);
        is0to9(c);
        if(s[i] == '\0'){
            led_colour(0,red,on);
            led_colour(0,green,on);
            led_colour(0,blue,on);
            sleep_msec(500);
            led_colour(0,red,off);
            led_colour(0,green,off);
            led_colour(0,blue,off);

            break;
        }
        if(c == '\n' || c == ' ' || c == '-' || c == ',' || c == '?' || c == '.'){
            sleep_msec(500);
        }
    }
}
    
        
            

int main (void) {
    char string1[] = "Oooooooh, 0a0a0a0a0a0a0a, --x--x--x--, what is happening now?\n";
    char string2[] = "D.I.S.C.O. D.I.S.C.O. D.I.S.C.O. D.I.S.C.O.\n";
    printstring(string1);
    printstring(string2);
}
