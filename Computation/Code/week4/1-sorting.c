#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "libpynq.h"
#define MAXLEN 30
struct person_t{
    char *name;
    float height;
};

int initialise(struct person_t database[], int size){
}

int main(void){
    char database[MAXLEN] = {0};
    char cmd;
    int size;
    do{
        printf("Command: ");
        scanf(" %c", &cmd);
        switch(cmd){
            case 'q':
                printf("Bye!\n");
            break;
            case 'i':
                printf("size? ");
                scanf(" %d", &size);
                if(size >= 1 && size <= MAXLEN){
                }
                else{
                    printf("Array size must be from 1 to %d.\n", MAXLEN);
                }
                initialise(database, size);
            break;
            default:
                printf("Unknown command!\n");
        }
    }while(cmd != 'q');
    
    
    
}
