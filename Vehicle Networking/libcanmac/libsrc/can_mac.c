#include <stdlib.h>
#include <stdint.h>
#include <xil_printf.h>
#include <timers.h>
#include "can_phy.h"
#include "can_mac.h"

//send
bool can_mac_tx_frame(CAN_FRAME* txFrame)
{   
    CAN_SYMBOL s;
    bool accomplished;
    int i;
    int j;
// SOF. 
    
    CAN_SYMBOL SOF = DOMINANT;

    can_phy_tx_symbol(SOF);
    can_phy_rx_symbol(&s);
    
// ID
    
    // define array for binary number
    uint32_t n = txFrame->ID;
    uint32_t binaryNumID[32];
    // set binary value to 0
    for(i = 0; i<32;i++){
        binaryNumID[i]=0;
    }
    
    // counter for binary array
    i = 0;
    while (n > 0) {
 
        // storing remainder in binary array
        binaryNumID[31-i] = n % 2;
        n = n / 2;
        i++;
    }
    
    CAN_SYMBOL ID[11];    
    for(i = 31; i >20; i--){
        ID[i-21] = (CAN_SYMBOL)binaryNumID[i];
    }
 
// RTR
    
    CAN_SYMBOL RTR = DOMINANT;
    
// IDE

    CAN_SYMBOL IDE = DOMINANT;
    
// R0 

    CAN_SYMBOL R0 = DOMINANT;
    
// DLC
    
    // define array for binary number
    n = txFrame->DLC;
    uint32_t binaryNumDLC[32];
    // set binary value to 0
    for(i=0; i<32; i++){
    binaryNumDLC[i]=0;
    }
    
    // counter for binary array
    i = 0;
    while (n > 0) {
 
        // storing remainder in binary array
        binaryNumDLC[31-i] = n % 2;
        n = n / 2;
        i++;
    }
    
    CAN_SYMBOL DLC[4];
    for(i = 31; i >27; i--){
        DLC[i-28] = (CAN_SYMBOL)binaryNumDLC[i];
    }
    
// DATA
    
    // define array for binary number
    uint64_t m = txFrame->Data;
    uint64_t binaryNumData[64];
    // set binary value to 0
    for(i = 0; i<64;i++){
    binaryNumData[i]=0;
    }
    
    // counter for binary array
    i = 0;
    while (m > 0) {
 
        // storing remainder in binary array
        binaryNumData[63-i] = m % 2;
        m = m / 2;
        i++;
    }
    
    CAN_SYMBOL Data[txFrame->DLC*8];
    for(i = 63; i>63-txFrame->DLC*8; i--){
        Data[i-(8-txFrame->DLC)*8] = (CAN_SYMBOL)binaryNumData[i];
    }

// CRC
            
//CRC DELIMITER

    CAN_SYMBOL CRCDE = RECESSIVE;

//ACK

    CAN_SYMBOL ACK[2];
    ACK[0] = RECESSIVE;
    ACK[1] = RECESSIVE;
    
// EOF
    
    CAN_SYMBOL EOF[7];
    for(i = 0; i<7; i++){
        EOF[i] = RECESSIVE;
    }
    
// IFS

    CAN_SYMBOL IFS[3];
    for(i = 0; i<3; i++){
        IFS[i] = RECESSIVE;
    }

// Total frame length without bitstuffing

    CAN_SYMBOL TOTALFRAME[8*txFrame->DLC+47];
    for(i = 0; i<8*txFrame->DLC+47;i++){
        TOTALFRAME[i]=RECESSIVE;
    }
    TOTALFRAME[0] = SOF;
    for(i=0; i<11; i++){
        TOTALFRAME[i+1] = ID[i];
    }
    TOTALFRAME[12] = RTR;
    TOTALFRAME[13] = IDE;
    TOTALFRAME[14] = R0;
    for(i=0; i<4; i++){
        TOTALFRAME[i+15] = DLC[i];
    }
    for(i=0; i<8*txFrame->DLC; i++){
        TOTALFRAME[i+19] = Data[i];
    }    
    TOTALFRAME[34+txFrame->DLC*8] = CRCDE;
   
    TOTALFRAME[35+txFrame->DLC*8] = ACK[0];
    TOTALFRAME[36+txFrame->DLC*8] = ACK[1];
    for(i=0; i<7; i++){
        TOTALFRAME[i+37+txFrame->DLC*8] = EOF[i];
    }
    for(i=0; i<3; i++){
        TOTALFRAME[i+44+txFrame->DLC*8] = IFS[i];
    }

// CRC calculations

    can_phy_tx_symbol(TOTALFRAME[1]);
    can_phy_rx_symbol(&s);
    
    
    

    CAN_SYMBOL CRCpoly[16];
    CRCpoly[0] = 1;
    CRCpoly[1] = 1;
    CRCpoly[2] = 0;
    CRCpoly[3] = 0;
    CRCpoly[4] = 0;
    CRCpoly[5] = 1;
    CRCpoly[6] = 0;
    CRCpoly[7] = 1;
    CRCpoly[8] = 1;
    CRCpoly[9] = 0;
    CRCpoly[10] = 0;
    CRCpoly[11] = 1;
    CRCpoly[12] = 1;
    CRCpoly[13] = 0;
    CRCpoly[14] = 0;
    CRCpoly[15] = 1;
    
    CAN_SYMBOL CRCpoly0[16]; 
    for(i = 0; i < 16; i++){
        CRCpoly0[i] = DOMINANT;
    }
    
    //data
    CAN_SYMBOL CRCarray[19+txFrame->DLC*8+15];
    for(i = 0; i < 19+txFrame->DLC*8; i++){
        CRCarray[i] = TOTALFRAME[i];
    }
    //filler
    for(i = 19+txFrame->DLC*8; i < 19+txFrame->DLC*8+15; i++){
        CRCarray[i] = DOMINANT;
    }
   
    //calculations.
    for(i = 0; i < 19+txFrame->DLC*8; i++){
        if(CRCarray[i] == 1){
            for(j = 0; j < 16; j++){
                CRCarray[i+j] = CRCarray[i+j]^CRCpoly[j];
            }
        }
        if(CRCarray[i] == 0){
            for(j = 0; j < 16; j++){
                CRCarray[i+j] = CRCarray[i+j]^CRCpoly0[j];
            }
        }
    }
    
    CAN_SYMBOL CRC[15];
    for(i = 0; i<15; i++){
        CRC[i] = CRCarray[19+txFrame->DLC*8+i];
    }

    for(i=0; i<15; i++){
        TOTALFRAME[i+19+txFrame->DLC*8] = CRC[i];
    }
    
    can_phy_tx_symbol(TOTALFRAME[2]);
    can_phy_rx_symbol(&s);


// Bitstuffing
    
    int temp=0;
    int count=0;
    for(i=0; i<34+8*txFrame->DLC-1; i++){
        if(TOTALFRAME[i] == TOTALFRAME[i+1]){
            temp++;
        }
        else{
            temp = 0;
        }
        
        if(temp == 4){
            
            if(TOTALFRAME[i+1] != TOTALFRAME[i+2]){
                temp =1;
            }
            else{
                temp = 0;
            }
            count++;
            i++;
        }
    }
    
// Insert actual bits

    temp = 0;
    CAN_SYMBOL TOTALSTUFFEDFRAME[47+8*txFrame->DLC+count];
    for(i=0; i<47+8*txFrame->DLC; i++){
        TOTALSTUFFEDFRAME[i] = TOTALFRAME[i];
    }
    for(i=47+8*txFrame->DLC; i<47+8*txFrame->DLC+count; i++){
        TOTALSTUFFEDFRAME[i] = RECESSIVE;
    }
    
    for(i=0; i<34+8*txFrame->DLC+count; i++){
        if(TOTALSTUFFEDFRAME[i] == TOTALSTUFFEDFRAME[i+1]){
            temp++;
        }
        else{
            temp = 0;
        }
        if(temp == 4){
            temp = 0;
            for(int j = 47+8*txFrame->DLC+count-2; j>i+1; j--){
                TOTALSTUFFEDFRAME[j+1] = TOTALSTUFFEDFRAME[j];
            }
            
            if(TOTALSTUFFEDFRAME[i+1] == DOMINANT){
                TOTALSTUFFEDFRAME[i+2] = RECESSIVE;
            }
            if(TOTALSTUFFEDFRAME[i+1] == RECESSIVE){
                TOTALSTUFFEDFRAME[i+2] = DOMINANT;
            }

        }
    }
    

    
    
//SEND SYMBOLS
    for(i=3; i<14; i++){
        can_phy_tx_symbol(TOTALSTUFFEDFRAME[i]);
        can_phy_rx_symbol(&s);
        if(s != TOTALSTUFFEDFRAME[i]){
            xil_printf("Arbitration lost :(\n");
            return(0);
        }
    } 

    for(i=14; i<35+8*txFrame->DLC+count; i++){
        can_phy_tx_symbol(TOTALSTUFFEDFRAME[i]);
        can_phy_rx_symbol(&s);
    }
    

    can_phy_tx_symbol(TOTALSTUFFEDFRAME[35+8*txFrame->DLC+count]);
    can_phy_rx_symbol(&s);
    if(s == 1){
        accomplished = false;
    }
    if(s == 0){
        accomplished = true;
    }
    
    for(i=36+8*txFrame->DLC+count; i<47+8*txFrame->DLC+count; i++){
        can_phy_tx_symbol(TOTALSTUFFEDFRAME[i]);
        can_phy_rx_symbol(&s);
    } 
    
    return(accomplished);

}



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//receive
void can_mac_rx_frame(CAN_FRAME* rxFrame)
{   
    xil_printf("start listening to bus\n");
    int tempt = 0;
    CAN_SYMBOL s=1;
    while(s == 1){
        can_phy_rx_symbol(&s);
        tempt++;
        if(tempt >= 60){
            rxFrame->DLC = 15;
            xil_printf("exit listening function\n");
            return;
        }
    }
    
    
//Receive frame and debitstuffing
    int i;
    int j;
    int count = 0;
    CAN_SYMBOL RECEIVEDFRAME[135];
    for(i=0; i<135; i++){
        RECEIVEDFRAME[i] = DOMINANT;
    }
    
    for(i=1; i<4; i++){
        can_phy_rx_symbol(&RECEIVEDFRAME[i]);
    }
    int temp = 4;
    for(i=4; i<34; i++){
        can_phy_rx_symbol(&RECEIVEDFRAME[i]);
        temp++;
        if(temp > 4 && (RECEIVEDFRAME[i] == RECEIVEDFRAME[i-1] && RECEIVEDFRAME[i-1] == RECEIVEDFRAME[i-2] && RECEIVEDFRAME[i-2] == RECEIVEDFRAME[i-3] && RECEIVEDFRAME[i-3] == RECEIVEDFRAME[i-4]) ){
            can_phy_rx_symbol(&s);
            temp = 0;
        }
    }
    
//DLC
    uint32_t rxFrameDLC[4];
    uint32_t rxFrameDLCNum = 0;

    for(i=0; i<4; i++){
        rxFrameDLC[i] = (uint32_t)RECEIVEDFRAME[15+i];
    }
    
    for(int i = 0; i<4; i++){
        if(rxFrameDLC[i] == 1){
            count = 1;
            int j = 3;
            for(j-i; (j-i)>0; j--){
                count = count*2;
            }
            rxFrameDLCNum = rxFrameDLCNum + count;
            
        }
    }
    
// Continue debitstuffing and receiving frame    
    
    for(i=34; i<34+rxFrameDLCNum*8; i++){
        can_phy_rx_symbol(&RECEIVEDFRAME[i]);
        temp++;
        if(temp > 4 && (RECEIVEDFRAME[i] == RECEIVEDFRAME[i-1] && RECEIVEDFRAME[i-1] == RECEIVEDFRAME[i-2] && RECEIVEDFRAME[i-2] == RECEIVEDFRAME[i-3] && RECEIVEDFRAME[i-3] == RECEIVEDFRAME[i-4]) ){
            can_phy_rx_symbol(&s);
            temp = 0;
        }
    }
    
//CRCDE
     can_phy_rx_symbol(&RECEIVEDFRAME[34+rxFrameDLCNum*8]);
    
// CRC calculations    
    
    uint32_t rxFrameCRCcalculated[15];
    uint32_t rxFrameCRCread[15];
    uint32_t CRCread = 0;
    uint32_t CRCcalculated = 0;

    CAN_SYMBOL CRCpoly[16];
    CRCpoly[0] = 1;
    CRCpoly[1] = 1;
    CRCpoly[2] = 0;
    CRCpoly[3] = 0;
    CRCpoly[4] = 0;
    CRCpoly[5] = 1;
    CRCpoly[6] = 0;
    CRCpoly[7] = 1;
    CRCpoly[8] = 1;
    CRCpoly[9] = 0;
    CRCpoly[10] = 0;
    CRCpoly[11] = 1;
    CRCpoly[12] = 1;
    CRCpoly[13] = 0;
    CRCpoly[14] = 0;
    CRCpoly[15] = 1;
    
    CAN_SYMBOL CRCpoly0[16]; 
    for(i = 0; i < 16; i++){
        CRCpoly0[i] = DOMINANT;
    }
    
    //data
    CAN_SYMBOL CRCarray[19+rxFrameDLCNum*8+15];
    for(i = 0; i < 19+rxFrameDLCNum*8; i++){
        CRCarray[i] = RECEIVEDFRAME[i];
    }
    //filler
    for(i = 19+rxFrameDLCNum*8; i < 19+rxFrameDLCNum*8+15; i++){
        CRCarray[i] = DOMINANT;
    }
   
    //calculations.
    for(i = 0; i < 19+rxFrameDLCNum*8; i++){
        if(CRCarray[i] == 1){
            for(j = 0; j < 16; j++){
                CRCarray[i+j] = CRCarray[i+j]^CRCpoly[j];
            }
        }
        if(CRCarray[i] == 0){
            for(j = 0; j < 16; j++){
                CRCarray[i+j] = CRCarray[i+j]^CRCpoly0[j];
            }
        }
    }
    
    for(i=0; i<15; i++){
        rxFrameCRCcalculated[i] = CRCarray[19+rxFrameDLCNum*8+i];
    }
    
    for(int i = 0; i<15; i++){
        if(rxFrameCRCcalculated[i] == 1){
            count = 1;
            int j = 14;
            for(j-i; (j-i)>0; j--){
                count = count*2;
            }
            CRCcalculated = CRCcalculated + count;
                  
        }
    }
    
    
// CRC received
    
    for(i=0; i<15; i++){
        rxFrameCRCread[i] = RECEIVEDFRAME[19+rxFrameDLCNum*8+i];
    }
    
    for(int i = 0; i<15; i++){
        if(rxFrameCRCread[i] == 1){
            count = 1;
            int j = 14;
            for(j-i; (j-i)>0; j--){
                count = count*2;
            }
            CRCread = CRCread + count;
                  
        }
    }      

    
    
// Acknowledge
    

    
    if(CRCread == CRCcalculated){
        can_phy_tx_symbol(DOMINANT);
        can_phy_rx_symbol(&RECEIVEDFRAME[35+rxFrameDLCNum*8]);
    }
    else{
        can_phy_rx_symbol(&RECEIVEDFRAME[35+rxFrameDLCNum*8]);
        xil_printf("CRC transmitted and calculated at receive do not match\n");
    }
    can_phy_rx_symbol(&RECEIVEDFRAME[36+rxFrameDLCNum*8]);
    
    
// Read rest of frame
    for(i=37+rxFrameDLCNum*8; i<47+rxFrameDLCNum*8; i++){
        can_phy_rx_symbol(&RECEIVEDFRAME[i]);
    }
    
    uint32_t rxFrameID[11];
    uint64_t rxFrameData[rxFrameDLCNum*8];
    
    uint32_t rxFrameIDNum = 0;
    uint64_t rxFrameDataNum = 0;
    
//ID    

    for(i=0; i<11; i++){
        rxFrameID[i] = RECEIVEDFRAME[1+i];
    }
    
    for(int i = 0; i<11; i++){
        if(rxFrameID[i] == 1){
            count = 1;
            int j = 10;
            for(j-i; (j-i)>0; j--){
                count = count*2;
            }
            rxFrameIDNum = rxFrameIDNum + count;
                  
        }
    }
    


//Data


    for(i=0; i<rxFrameDLCNum*8; i++){
        rxFrameData[i] = RECEIVEDFRAME[19+i];
    }
    
    for(int i = 0; i<rxFrameDLCNum*8; i++){
        if(rxFrameData[i] == 1){
            count = 1;
            int j = rxFrameDLCNum*8-1;
            for(j-i; (j-i)>0; j--){
                count = count*2;
            }
            rxFrameDataNum = rxFrameDataNum + count;
                  
        }
    }
          
    rxFrame->ID = rxFrameIDNum;
    rxFrame->DLC = rxFrameDLCNum;
    rxFrame->CRC = CRCread;
    rxFrame->Data = rxFrameDataNum;    
    xil_printf("End listening to bus\n"); 
}
    
/*  bepaal crc
    controleer of die klopt
    send dominant if crc is correct.
    receive rest of frame
  */  
            






















