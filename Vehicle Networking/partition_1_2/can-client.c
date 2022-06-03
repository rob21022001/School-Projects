#include <stdint.h>
#include <timers.h>
#include <xil_printf.h>
#include "can_phy.h"
#include "can_phy.c"
#include "can_mac.h"
#include "settings.h"
#include "io.h"
#include "io.c"
#include <stdlib.h>

// CLIENT 1.2

int main (void)
{

#if (defined(TEST_CASE_1) || defined(TEST_CASE_2))
  uint64_t t = read_global_timer();
  #if (defined(TEST_CASE_1))
  xil_printf("%04u/%010u: CAN client %d %d running in TEST_CASE_1\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);
  #elif (defined(TEST_CASE_2))
  xil_printf("%04u/%010u: CAN client %d %d running in TEST_CASE_2\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);
  #endif

    CAN_FRAME* henk = (CAN_FRAME *)malloc(sizeof(CAN_FRAME));
    henk->ID = 10;//PRIO_BUTTON0;
    henk->DLC = 1;
    henk->Data = 0;
    henk->CRC = 1;
    uint64_t count = 1;

    while(1){
       
    
        if(read_button_state(0) == 1){
            can_mac_tx_frame(henk);
            henk->Data = henk->Data+count;

        }
    }
    

/*
    CAN_SYMBOL s;
    while(1){
        xil_printf("%d\n", read_button_state(0));
        can_phy_tx_symbol(DOMINANT);
        can_phy_rx_symbol(&s);
        can_phy_tx_symbol(RECESSIVE);
        can_phy_rx_symbol(&s); 

  }
*/


#elif (defined(TEST_CASE_3))
  uint64_t t = read_global_timer();
  xil_printf("%04u/%010u: CAN client %d %d running in TEST_CASE_3\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);

    CAN_FRAME* henk = (CAN_FRAME *)malloc(sizeof(CAN_FRAME));
    henk->ID = PRIO_BUTTON0;
    henk->DLC = 1;
    henk->Data = 0;
    henk->CRC = 1;
    int pushed = 0;
    int i = 0;
    uint64_t count = 1;
    while(1){
        pushed = 0;
        i = 0;
        CAN_SYMBOL s;
        can_phy_rx_symbol(&s);
        if(s == DOMINANT){
            CAN_SYMBOL RECEIVEDFRAME[135];
            for(i=0; i<135; i++){
                RECEIVEDFRAME[i] = DOMINANT;
            }
            
            for(i=1; i<13; i++){
                can_phy_rx_symbol(&RECEIVEDFRAME[i]);
                if(read_button_state(0) == 1){
                    pushed = 1;
                    xil_printf("pushed0 = %d\n", pushed);
                }

            }
            i = 13;
            
            while(!(RECEIVEDFRAME[i-11] == RECESSIVE && RECEIVEDFRAME[i-1] == RECESSIVE && RECEIVEDFRAME[i-2] == RECESSIVE && RECEIVEDFRAME[i-3] == RECESSIVE && RECEIVEDFRAME[i-4] == RECESSIVE && RECEIVEDFRAME[i-5] == RECESSIVE && RECEIVEDFRAME[i-6] == RECESSIVE && RECEIVEDFRAME[i-7] == RECESSIVE && RECEIVEDFRAME[i-8] == RECESSIVE && RECEIVEDFRAME[i-9] == RECESSIVE && RECEIVEDFRAME[i-10] == RECESSIVE && RECEIVEDFRAME[i-12] == RECESSIVE && RECEIVEDFRAME[i-13] == RECESSIVE)){
                can_phy_rx_symbol(&RECEIVEDFRAME[i]);
                i++;
                if(read_button_state(0) == 1){
                    pushed = 1;
                    xil_printf("pushed0 = %d\n", pushed);
                }
            }
        }

        
    
        if(read_button_state(0) == 1 || pushed == 1){
            can_mac_tx_frame(henk);
            henk->Data = henk->Data+count;

        }
    }



#elif (defined(TEST_CASE_5))

  uint64_t t = read_global_timer();
  xil_printf("%04u/%010u: CAN client %d %d running in TEST_CASE_5\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);

    CAN_FRAME* Frame1 = (CAN_FRAME *)malloc(sizeof(CAN_FRAME));   

    uint64_t sendtime = t;
    uint64_t deadline;
    while(1){
        t = read_global_timer();
    
        if(t>sendtime){
            deadline = t+FRAME_LENGTH_CYCLES;
            sendtime = t+PERIOD0;
            can_mac_rx_frame(Frame1);
            xil_printf("ID = %d\n", Frame1->ID);
            xil_printf("DLC = %d\n", Frame1->DLC);
            xil_printf("Data = %u%u\n", (uint32_t)(Frame1->Data >> 32), (uint32_t)Frame1->Data);
            xil_printf("CRC = %d\n", Frame1->CRC);

            t = read_global_timer();

            if(t<deadline){
                xil_printf("Message received within deadline.\n");
            }
            else{
                xil_printf("Message NOT received within deadline\n");
            }
        }
    }

#elif (defined(TEST_CASE_6))
    
  uint64_t t = read_global_timer();
  xil_printf("%04u/%010u: CAN client %d %d running in TEST_CASE_6\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);

    CAN_FRAME* Frame1 = (CAN_FRAME *)malloc(sizeof(CAN_FRAME));   
    uint64_t sendtime = t;
    uint64_t deadline = t+FRAME_LENGTH_CYCLES;
    while(1){
        t = read_global_timer();
    
        if(t>sendtime){
            can_mac_rx_frame(Frame1);
            if(Frame1->DLC < 9){
                xil_printf("ID = %d\n", Frame1->ID);
                xil_printf("DLC = %d\n", Frame1->DLC);
                xil_printf("Data = %u%u\n", (uint32_t)(Frame1->Data >> 32), (uint32_t)Frame1->Data);
                xil_printf("CRC = %d\n", Frame1->CRC);
                
                t = read_global_timer();
                
                if(t<deadline){
                    xil_printf("Message received within deadline.\n");
                }
                else{
                    xil_printf("Message NOT received within deadline\n");
                }
            }
            sendtime = deadline;
            deadline = deadline+FRAME_LENGTH_CYCLES;
        }
    }
    
    
    
#elif (defined(TEST_CASE_7)||defined(TEST_CASE_8)||defined(TEST_CASE_9))

  uint64_t t = read_global_timer();
  #if (defined(TEST_CASE_7))
  xil_printf("%04u/%010u: CAN client %d %d running in TEST_CASE_7\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);
  #elif (defined(TEST_CASE_8))
  xil_printf("%04u/%010u: CAN client %d %d running in TEST_CASE_8\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);
  #elif (defined(TEST_CASE_9))
  xil_printf("%04u/%010u: CAN client %d %d running in TEST_CASE_9\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);
  #endif
        
    CAN_FRAME* henk = (CAN_FRAME *)malloc(sizeof(CAN_FRAME));
    henk->ID = PRIO_BUTTON0;
    henk->DLC = 3;
    henk->Data = 0;
    henk->CRC = 1;
    uint64_t Dogan = 0;
    
    CAN_SYMBOL s;
    int i = 0;
    int pushed = 0;
    uint64_t count = 1;
    bool accomplished;
    while(1){
        pushed = 0;
        i = 0;
        accomplished = false;
        while(accomplished == false){
            can_phy_rx_symbol(&s);
            if(s == DOMINANT || t < Dogan){
                CAN_SYMBOL RECEIVEDFRAME[135];
                for(i=0; i<135; i++){
                    RECEIVEDFRAME[i] = DOMINANT;
                }
            
                for(i=1; i<13; i++){
                    can_phy_rx_symbol(&RECEIVEDFRAME[i]);
                    if(read_button_state(0) == 1){
                        pushed = 1;
                        xil_printf("pushed0 = %d\n", pushed);
                    }
                }
                
                i = 13;
                while(!(RECEIVEDFRAME[i-11] == RECESSIVE && RECEIVEDFRAME[i-1] == RECESSIVE && RECEIVEDFRAME[i-2] == RECESSIVE && RECEIVEDFRAME[i-3] == RECESSIVE && RECEIVEDFRAME[i-4] == RECESSIVE && RECEIVEDFRAME[i-5] == RECESSIVE && RECEIVEDFRAME[i-6] == RECESSIVE && RECEIVEDFRAME[i-7] == RECESSIVE && RECEIVEDFRAME[i-8] == RECESSIVE && RECEIVEDFRAME[i-9] == RECESSIVE && RECEIVEDFRAME[i-10] == RECESSIVE && RECEIVEDFRAME[i-12] == RECESSIVE && RECEIVEDFRAME[i-13] == RECESSIVE)){
                    can_phy_rx_symbol(&RECEIVEDFRAME[i]);
                    i++;
                    if(read_button_state(0) == 1){
                        pushed = 1;
                        xil_printf("pushed0 = %d\n", pushed);

                    }
                }
            }
    
            if(read_button_state(0) == 1 || pushed == 1){
                t = read_global_timer();
                Dogan = t+ FRAME_LENGTH_CYCLES*0.2; // check how many simbols are sent to make check if there is arbitration loss or a false acknowledge.
                xil_printf("client 1.2 starts sending\n");
                accomplished = can_mac_tx_frame(henk);
                pushed = 1;
            }
        }
        henk->Data = henk->Data+count;
    }

#elif (defined(TEST_CASE_10)||defined(TEST_CASE_11))

  uint64_t t = read_global_timer();
  #if (defined(TEST_CASE_10))
  xil_printf("%04u/%010u: CAN client %d %d running in TEST_CASE_10\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);
  #elif (defined(TEST_CASE_11))
  xil_printf("%04u/%010u: CAN client %d %d running in TEST_CASE_11\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);
  #endif
  
    CAN_FRAME* Frame1 = (CAN_FRAME *)malloc(sizeof(CAN_FRAME));   

    uint64_t sendtime = t;
    uint64_t deadline = t + FRAME_LENGTH_CYCLES;
    while(1){
        t = read_global_timer();
    
        if(t>sendtime){
            can_mac_rx_frame(Frame1);
            if(Frame1->DLC<9){
                if(Frame1->ID == PRIO_PERIOD0){
                    xil_printf("CAN_FRAME received\n");
                    xil_printf("ID = %d\n", Frame1->ID);
                    xil_printf("DLC = %d\n", Frame1->DLC);
                    xil_printf("Data = %u%u\n", (uint32_t)(Frame1->Data >> 32), (uint32_t)Frame1->Data);
                    xil_printf("CRC = %d\n", Frame1->CRC);
                    if(read_green_led_state(2) == 0){
                        turn_led_on(2);
                    }
                    else{
                        turn_led_off(2);
                    }
                    t = read_global_timer();
                    if(t<deadline){
                        xil_printf("Message received within deadline.\n");
                    }
                    else{
                        xil_printf("Message NOT received within deadline\n");
                    }
                }
            }
            t = read_global_timer();
            sendtime = deadline;
            deadline = deadline+FRAME_LENGTH_CYCLES;
        }
    }



#else
  /******* CAN Client is disabled in this test case *******/
  uint64_t t = read_global_timer();
  xil_printf("%04u/%010u: CAN client %d %d is idle\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);
  while (1) { asm("wfi"); }
#endif
  return 0;
}
