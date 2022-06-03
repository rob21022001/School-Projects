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

// Client 2.2

int main (void)
{
#if (defined(TEST_CASE_3))
  uint64_t t = read_global_timer();
  xil_printf("%04u/%010u: CAN client %d %d running in TEST_CASE_3\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);

    CAN_FRAME* henk = (CAN_FRAME *)malloc(sizeof(CAN_FRAME));
    henk->ID = PRIO_BUTTON1;
    henk->DLC = 1;
    henk->Data = 0;
    henk->CRC = 1;
    
    int i = 0;
    int pushed = 0;
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
                if(read_button_state(1) == 1){
                    pushed = 1;
                    xil_printf("pushed1 = %d\n", pushed);
                }

            }

            i = 13;
            while(!(RECEIVEDFRAME[i-11] == RECESSIVE && RECEIVEDFRAME[i-1] == RECESSIVE && RECEIVEDFRAME[i-2] == RECESSIVE && RECEIVEDFRAME[i-3] == RECESSIVE && RECEIVEDFRAME[i-4] == RECESSIVE && RECEIVEDFRAME[i-5] == RECESSIVE && RECEIVEDFRAME[i-6] == RECESSIVE && RECEIVEDFRAME[i-7] == RECESSIVE && RECEIVEDFRAME[i-8] == RECESSIVE && RECEIVEDFRAME[i-9] == RECESSIVE && RECEIVEDFRAME[i-10] == RECESSIVE && RECEIVEDFRAME[i-12] == RECESSIVE && RECEIVEDFRAME[i-13] == RECESSIVE)){
                can_phy_rx_symbol(&RECEIVEDFRAME[i]);
                i++;
                if(read_button_state(1) == 1){
                    pushed = 1;
                    xil_printf("pushed1 = %d\n", pushed);

                }
            }
        }

    
    
        if(read_button_state(1) == 1 || pushed == 1){
            can_mac_tx_frame(henk);
            henk->Data = henk->Data+count;
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
    henk->ID = PRIO_BUTTON1;
    henk->DLC = 6;
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
                    if(read_button_state(1) == 1){
                        pushed = 1;
                        xil_printf("pushed1 = %d\n", pushed);
                    }
                }
                
                i = 13;
                while(!(RECEIVEDFRAME[i-11] == RECESSIVE && RECEIVEDFRAME[i-1] == RECESSIVE && RECEIVEDFRAME[i-2] == RECESSIVE && RECEIVEDFRAME[i-3] == RECESSIVE && RECEIVEDFRAME[i-4] == RECESSIVE && RECEIVEDFRAME[i-5] == RECESSIVE && RECEIVEDFRAME[i-6] == RECESSIVE && RECEIVEDFRAME[i-7] == RECESSIVE && RECEIVEDFRAME[i-8] == RECESSIVE && RECEIVEDFRAME[i-9] == RECESSIVE && RECEIVEDFRAME[i-10] == RECESSIVE && RECEIVEDFRAME[i-12] == RECESSIVE && RECEIVEDFRAME[i-13] == RECESSIVE)){
                    can_phy_rx_symbol(&RECEIVEDFRAME[i]);
                    i++;
                    if(read_button_state(1) == 1){
                        pushed = 1;
                        xil_printf("pushed1 = %d\n", pushed);

                    }
                }
            }
    
            if(read_button_state(1) == 1 || pushed == 1){
                t = read_global_timer();
                Dogan = t+ FRAME_LENGTH_CYCLES*0.2; // check how many simbols are sent to make check if there is arbitration loss or a false acknowledge.
                xil_printf("client 2.2 starts sending\n");
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
  
    CAN_FRAME* henk = (CAN_FRAME *)malloc(sizeof(CAN_FRAME));
    henk->ID = PRIO_PERIOD2;
    henk->DLC = 1;
    henk->Data = 0;
    henk->CRC = 1;
        
    uint64_t Dogan = 0;
    uint64_t sendtime = t;
    int Scarpa = 0;
    
    CAN_SYMBOL s;
    int i = 0;
    uint64_t count = 1;
    bool accomplished;
    while(1){
        i = 0;
        accomplished = false;
        while(accomplished == false){            
            t = read_global_timer();
            if(t > sendtime){
                t = read_global_timer();
                xil_printf("client 2.2 starts sending\n");
                accomplished = can_mac_tx_frame(henk);
                if(accomplished == false){
                    Scarpa++;
                    sendtime = sendtime + FRAME_LENGTH_CYCLES;
                    if(Scarpa > (PERIOD2/FRAME_LENGTH_CYCLES)-1){
                        xil_printf("Message lost somewhere in the milkyway:(\n");
                        Scarpa = 0;
                        goto label;
                    }
                }
                else{
                    sendtime = sendtime + PERIOD2 - FRAME_LENGTH_CYCLES*Scarpa;
                    Scarpa = 0;
                }
            }
        }
        label:henk->Data = henk->Data+count;
    }

#else
  /******* CAN Client is disabled in this test case *******/
  uint64_t t = read_global_timer();
  xil_printf("%04u/%010u: CAN client %d %d is idle\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);
  while (1) { asm("wfi"); }
#endif
  return 0;
}
