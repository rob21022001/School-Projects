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

// Client 2.3

int main (void)
{
#if (defined(TEST_CASE_3))
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
    
        if(Frame1->ID == PRIO_BUTTON1){
            if(read_green_led_state(1) == 0){
                turn_led_on(1);
            }
            else{
            turn_led_off(1);
            }
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

    CAN_FRAME* Frame1 = (CAN_FRAME *)malloc(sizeof(CAN_FRAME));   
    
    while(1){
        can_mac_rx_frame(Frame1);
    
        if(Frame1->ID == PRIO_BUTTON1){
            xil_printf("CAN_FRAME received\n");
            xil_printf("ID = %d\n", Frame1->ID);
            xil_printf("DLC = %d\n", Frame1->DLC);
            xil_printf("Data = %u%u\n", (uint32_t)(Frame1->Data >> 32), (uint32_t)Frame1->Data);
            xil_printf("CRC = %d\n", Frame1->CRC);

            if(read_green_led_state(1) == 0){
                turn_led_on(1);
            }
            else{
            turn_led_off(1);
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
  
    CAN_FRAME* Frame1 = (CAN_FRAME *)malloc(sizeof(CAN_FRAME));   

    uint64_t sendtime = t;
    uint64_t deadline = t + FRAME_LENGTH_CYCLES;
    while(1){
        t = read_global_timer();
    
        if(t>sendtime){
            can_mac_rx_frame(Frame1);
            if(Frame1->DLC<9){
                if(Frame1->ID == PRIO_PERIOD1){
                    xil_printf("CAN_FRAME received\n");
                    xil_printf("ID = %d\n", Frame1->ID);
                    xil_printf("DLC = %d\n", Frame1->DLC);
                    xil_printf("Data = %u%u\n", (uint32_t)(Frame1->Data >> 32), (uint32_t)Frame1->Data);
                    xil_printf("CRC = %d\n", Frame1->CRC);
                    if(read_green_led_state(1) == 0){
                        turn_led_on(1);
                    }
                    else{
                        turn_led_off(1);
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
