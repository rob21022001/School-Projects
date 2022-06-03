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

// Client 1.3

int main (void)
{

#if (defined(TEST_CASE_2))
  uint64_t t = read_global_timer();
  xil_printf("%04u/%010u: CAN client %d %d running in TEST_CASE_2\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);

    CAN_FRAME* Frame1 = (CAN_FRAME *)malloc(sizeof(CAN_FRAME));   
    
    while(1){
        can_mac_rx_frame(Frame1);

        xil_printf("CAN_FRAME received\n");
        xil_printf("ID = %d\n", Frame1->ID);
        xil_printf("DLC = %d\n", Frame1->DLC);
        xil_printf("Data = %u%u\n", (uint32_t)(Frame1->Data >> 32), (uint32_t)Frame1->Data);
        xil_printf("CRC = %d\n", Frame1->CRC);
    
        if(Frame1->ID == PRIO_BUTTON0){
            if(read_green_led_state(0) == 0);
                turn_led_on(0);
            }
            else{
            turn_led_off(0);
        }
    }

#elif (defined(TEST_CASE_3))

  uint64_t t = read_global_timer();
  xil_printf("%04u/%010u: CAN client %d %d running in TEST_CASE_3\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);

    CAN_FRAME* Frame1 = (CAN_FRAME *)malloc(sizeof(CAN_FRAME));   

    while(1){
    
        can_mac_rx_frame(Frame1);
        
        xil_printf("CAN_FRAME received\n");
        xil_printf("ID = %d\n", Frame1->ID);
        xil_printf("DLC = %d\n", Frame1->DLC);
        xil_printf("Data = %u%u\n", (uint32_t)(Frame1->Data >> 32), (uint32_t)Frame1->Data);
        xil_printf("CRC = %d\n", Frame1->CRC);
        
        if(Frame1->ID == PRIO_BUTTON0){
            if(read_green_led_state(0) == 0){
                turn_led_on(0);
            }
            else{
                turn_led_off(0);
            }
        }
    }

#elif (defined(TEST_CASE_4) || defined(TEST_CASE_5 ))
  uint64_t t = read_global_timer();
  #if (defined(TEST_CASE_4))
  xil_printf("%04u/%010u: CAN client %d %d running in TEST_CASE_4\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);
  #elif (defined(TEST_CASE_5))
  xil_printf("%04u/%010u: CAN client %d %d running in TEST_CASE_5\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);
  #endif

    CAN_FRAME* henk = (CAN_FRAME *)malloc(sizeof(CAN_FRAME));
    henk->ID = PRIO_PERIOD0;
    henk->DLC = 1;
    henk->Data = 0;
    henk->CRC = 1;

    uint64_t sendtime = t;
    uint64_t count = 1;


    while(1){
        t = read_global_timer();
    
        if(t>sendtime){
            sendtime = sendtime+PERIOD0;
            can_mac_tx_frame(henk);
            henk->Data = henk->Data+count;
        }
    }

#elif (defined(TEST_CASE_6))

  uint64_t t = read_global_timer();
  xil_printf("%04u/%010u: CAN client %d %d running in TEST_CASE_6\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);



    CAN_FRAME* henk = (CAN_FRAME *)malloc(sizeof(CAN_FRAME));
    henk->ID = PRIO_PERIOD0;
    henk->DLC = 1;
    henk->Data = 0;
    henk->CRC = 1;
    uint64_t sendtime = t;
    int temp;
    bool accomplished;
    int temp2;
    
    while(1){
        accomplished = false;
        temp = 0;
        while(accomplished == false){
            t = read_global_timer();
            if(t>sendtime){
                sendtime = t+PERIOD0-FRAME_LENGTH_CYCLES*temp;
                accomplished = can_mac_tx_frame(henk);
                temp2 == accomplished;
            }
            if(accomplished == 1){
                xil_printf("Message received succesfully\n");
            }
            else if(temp2 == 0){
                xil_printf("Message NOT received correctly\n");
                temp++;
                temp2 = 1;
            }
            if(temp >= PERIOD0/FRAME_LENGTH_CYCLES){
                accomplished = true;
                xil_printf("Message is lost :-( Start sending next frame...\n");
            }
        }
        henk->Data++;
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

    CAN_FRAME* Frame1 = (CAN_FRAME *)malloc(sizeof(CAN_FRAME));   

    while(1){
    
        can_mac_rx_frame(Frame1);
        
        
        if(Frame1->ID == PRIO_BUTTON0){
            xil_printf("CAN_FRAME received\n");
            xil_printf("ID = %d\n", Frame1->ID);
            xil_printf("DLC = %d\n", Frame1->DLC);
            xil_printf("Data = %u%u\n", (uint32_t)(Frame1->Data >> 32), (uint32_t)Frame1->Data);
            xil_printf("CRC = %d\n", Frame1->CRC);

            if(read_green_led_state(0) == 0){
                turn_led_on(0);
            }
            else{
                turn_led_off(0);
            }
        }
    }
    

#elif (defined(TEST_CASE_10)||defined(TEST_CASE_11))

  uint64_t t = read_global_timer();
  #if (defined(TEST_CASE_10))
  xil_printf("%04u/%010u: CAN client %d %d running in TEST_CASE_10\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);
  #elif (defined(TEST_CASE_11))
  xil_printf("%04u/%010u: CAN client %d %d running in TEST_CASE_11\n", (uint32_t)(t >> 32), (uint32_t)t, TILE_ID, PARTITION_ID);
  #endif
  
    CAN_FRAME* henk = (CAN_FRAME *)malloc(sizeof(CAN_FRAME));
    henk->ID = PRIO_PERIOD0;
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
                xil_printf("client 1.3 starts sending\n");
                accomplished = can_mac_tx_frame(henk);
                if(accomplished == false){
                    Scarpa++;
                    sendtime = sendtime + FRAME_LENGTH_CYCLES;
                    if(Scarpa > (PERIOD0/FRAME_LENGTH_CYCLES)-1){
                        xil_printf("Message lost somewhere in the milkyway:(\n");
                        Scarpa = 0;
                        goto label;
                    }
                }
                else{
                    sendtime = sendtime + PERIOD0 - FRAME_LENGTH_CYCLES*Scarpa;
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
