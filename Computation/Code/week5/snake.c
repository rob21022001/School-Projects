#include <stdio.h>
#include "libpynq.h"
#include <stdlib.h>
#include <string.h>
#define HEIGHT 30
#define WIDTH 40

typedef struct pos{
    int x;
    int y;
    struct pos *next;
}pos;

void print_pos (struct pos *head){
    struct pos *current;
    current = head;
    
    printf("[");
    while(current != NULL){
        printf("(%d,%d)",current->x, current->y);
        if(current->next != NULL){
            printf(",");
        }
        current = current->next;  
    }
    printf("]\n");
}


struct pos *lookup_pos (struct pos *head, int x, int y){
    struct pos *current = NULL;
    current = head;
    if(current == NULL){
        return(NULL);
    }
    while(current != NULL){
        if(current->x == x && current->y == y){
            return(current);
        }
        else{
        }
        current = current->next;
    }
    return(NULL);
}


struct pos *add_new_pos (struct pos *head, int x, int y){
    struct pos *new = (struct pos*)malloc(sizeof(struct pos));
    if(new == NULL){
        printf("No space available to malloc.\n");
        return(head);
    }
    else if(lookup_pos(head, x, y) != NULL){
        printf("The value (%d,%d) is already in the list\n", x, y);
        return(head);
    }
    else{
        new->next = head;
        new->x = x;
        new->y = y;
        head = new;
        return(head);
    }
}

struct pos *remove_last_pos (struct pos *head){
    struct pos *current;
    current = head;
    if(current == NULL){
        printf("List is empty so no value can be removed\n");
        return(head);
    }
    else if(current->next == NULL){
        free(current);
        head = NULL;
        return(head);
    }
    else{
        while(current->next->next != NULL){
        current = current->next;
        }
    free(current->next);
    current->next = NULL; 
    return(head);
    }
}

void play(void){
    pixel displaybuffer[HEIGHT][WIDTH];
    init_display(HEIGHT, WIDTH, 10, displaybuffer);
    int y = HEIGHT/2, x = WIDTH/2, ydir = 0, xdir = 1;
    do {
        set_pixel(y,x,0,255,0);
        draw_display();
        y += ydir;
        x += xdir;
        sleep_msec_buttons_pushed(200); // sets button_states[]
        // update xdir, ydir depending on the buttons
        // multiple buttons may be pushed, take the one pushed longest
        // do you want to allow diagonals?
    }while (1);
    sleep_msec(5000);
}




int main(void){
    char cmd;
    int x = 0, y = 0;
    struct pos *head = NULL;
    struct pos *value = NULL;
    do{
        printf("command? ");
        scanf(" %c", &cmd);
    switch(cmd){
        case 'p':
            play();
        break;
        case 's':
            print_pos(head);
        break;
        case 'l':
            printf("Position (x y)? ");
            scanf("%d %d", &x, &y);
            value = lookup_pos(head, x, y);
            if(value != NULL){
                printf("Position (%d,%d) is in the list\n", x, y);
            }
            else{
                printf("Position (%d,%d) is not in the list\n", x, y);
            }
        break;
        case 'f':
            printf("Position (x y)? ");
            scanf("%d %d", &x, &y);
            head = add_new_pos(head, x , y);
        break;
        case 't':
            head = remove_last_pos(head);
        break;
        case 'q':
            printf("Bye!\n");
        break;
        default:
        printf("Unknown command \'%c\'.\n", cmd);
        break;
            
        
    }
        
        
        
    }while(cmd != 'q');
    
    
}
