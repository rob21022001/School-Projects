#include <stdio.h>
#include "libpynq.h" 
int main(void){
    char c3, c2, c1, c0; 
    int d3 ,d2, d1, d0, final_number;
    printf("please enter a binary number of 4 digits?\n");
    scanf(" %c%c%c%c",&c3,&c2,&c1,&c0);
    if ( (c3 != '0' && c3 != '1') || (c2 != '0' && c2 != '1') || (c1 != '0' && c1 != '1') || (c0 != '0' && c0 != '1') ){
        printf("binary didgits must be 0 or 1\n");
        return(-1);
    }
    else{
        if (c0 == '0') d0 = 0; else d0 = 1;
        if (c1 == '0') d1 = 0; else d1 = 1;
        if (c2 == '0') d2 = 0; else d2 = 1;
        if (c3 == '0') d3 = 0; else d3 = 1;
    } 
    
    if (d0 == 1) led_onoff(0,on); else;
    if (d1 == 1) led_onoff(1,on); else;
    if (d2 == 1) led_onoff(2,on); else;
    if (d3 == 1) led_onoff(3,on); else;

    
    
    while (1==1){
        final_number = d3*8+d2*4+d1*2+d0*1.;
        printf("the decimal value of the binary number %d%d%d%d is %d\n", d3, d2, d1, d0, final_number);
        
        wait_until_button_pushed(0);
        wait_until_button_released(0);
    
        int carry = 1;
        d0 = d0 + carry;
        if (d0 > 1){
            d0 = 0;
            d1= d1+carry;
        }
        if (d1 > 1){
            d1 = 0;
            d2= d2+carry;
        }
        if (d2 > 1){
            d2 = 0;
            d3= d3+carry;
        }
        if (d3 > 1){
            d3 = 0;
            printf("overflow!\n");
        }

    }     
}
