#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//#include "libpynq.h"
#define MAX(a,b) ((a)<(b)?(b):(a))
#define MIN(a,b) ((a)>(b)?(b):(a))
#define HEIGHT 50
#define WIDTH 50


typedef struct node_t {
float re, im;
struct node_t *next;
}node_t;

struct node_t *insert_tail (struct node_t *head, float re, float im){
    struct node_t *current = head;
    struct node_t *new = (struct node_t*)malloc(sizeof(struct node_t));
    if(current != NULL){
        while(current->next != NULL){
            current = current->next;
        }
        current->next = new;
        new->re = re;
        new->im = im;
        new->next = NULL;
        return(head);
    }
    else{
        new->re = re;
        new->im = im;
        new->next = NULL;
        return(new);
    }
}

void print_list (struct node_t *head) {
    printf("[");
    struct node_t *current = head;
    while(current != NULL){
        printf("%.2f+%.2fi", current->re, current->im);
        if(current->next != NULL){
            printf(",");
        }
        current = current->next;
    }
    printf("]\n");
}

void insert_head (struct node_t **head, float re, float im){
    struct node_t *current = *head;
    struct node_t *new = (struct node_t*)malloc(sizeof(struct node_t));
    if(new == NULL){
        printf("No space available to malloc");
    }
    else{
        new->re = re;
        new->im = im;
        new->next = current ;
        current = new;
        *head = current;
    }
}

float distance (float re1, float im1, float re2, float im2){
    float distance;
    distance = sqrt(pow(re1 - re2, 2) + pow(im1 - im2, 2));
    return(distance);
}

struct node_t *insert_after_closest (struct node_t *head, float re, float im){
    float re1, im1;
    float smallestdistance, currentdistance;
    struct node_t *current = head;
    struct node_t *temp = NULL;
    struct node_t *temp2 = NULL;
    if(current == NULL){
        current = (struct node_t*)malloc(sizeof(struct node_t));
        current->re = re;
        current->im = im;
        current->next = NULL;
        return(current);
        }
    else{
        smallestdistance = 100000000000000000;
        while(current != NULL){
            re1 =current->re;
            im1= current->im;
            currentdistance = distance(re1, im1, re, im);
            if(currentdistance < smallestdistance){
                smallestdistance = currentdistance;
                temp = current;
                temp2 = current->next;
            }
            current = current->next;
        }
        struct node_t *new = (struct node_t*)malloc(sizeof(struct node_t));
        temp->next = new;
        new->re = re;
        new->im = im;
        new->next = temp2;
        return(head);
    }
}

void insert_before_closest (struct node_t **head, float re, float im) {
    int count = 0;
    struct node_t *current = *head;
    struct node_t *temp = NULL;
    struct node_t *temp2 = NULL;
    float re1, im1;
    float smallestdistance, currentdistance;
    struct node_t *new = (struct node_t*)malloc(sizeof(struct node_t));
    if(current == NULL){
        new->re = re;
        new->im = im;
        new->next = *head;
        *head = new;
        
    }
    else if(current->next != NULL){
        smallestdistance = 100000000000000000;
        re1 = current->re;
        im1 = current->im;
        currentdistance = distance(re1, im1, re, im);
        if(currentdistance < smallestdistance){
            smallestdistance = currentdistance;
            temp = current;
            temp2 = current->next;
        }
        while(current->next != NULL){
            re1 =current->next->re;
            im1= current->next->im;
            currentdistance = distance(re1, im1, re, im);
            if(currentdistance < smallestdistance){
                smallestdistance = currentdistance;
                temp = current;
                temp2 = current->next;
                count++;
            }
            current = current->next;
        
        }
        if(count > 0){
            temp->next = new;
            new->re = re;
            new->im = im;
            new->next = temp2;
        }
        else{
            new->re = re;
            new->im = im;
            new->next = *head;
            *head = new;
        }
    }
    else{
        new->re = re;
        new->im = im;
        new->next = *head;
        *head = new;
    }
}

void print_list_reverse (struct node_t *head){
    struct node_t *current;
    current = head;
    if(current == NULL){
    }
    else{
        if(current->next != NULL){
            current = current->next;
            print_list_reverse(current);
            printf("%.2f+%.2fi,", current->re, current->im);
        }
    }
}

struct node_t *remove_front (struct node_t *head) {
    struct node_t *current = head;
    if(current == NULL){
        return(head);
    }
    else{
        head = current->next;
        free(current);
        current = NULL;
        return(head);
    }
}

void remove_end (struct node_t **head){
    struct node_t *current = *head;
    if(current != NULL){
        if(current->next == NULL){
            free(current);
            current = NULL;
            *head = NULL;
            return;
        }
        else{
            while(current->next->next != NULL){
                current = current->next;
            }
            free(current->next);
            current->next = NULL;
            return;
        }
    }
    else{
        return;
    }
}

struct node_t *remove_closest (struct node_t *head, float re, float im){
    struct node_t *current = head;
    struct node_t *temp = NULL;
    struct node_t *temp2 = NULL;
    int count = 0;
    float re1, im1;
    float smallestdistance, currentdistance;
    if(current == NULL){
        return(head);
    }
    else if(current->next != NULL){
        smallestdistance = 100000000000000000;
        re1 = current->re;
        im1 = current->im;
        currentdistance = distance(re1, im1, re, im);
            if(currentdistance < smallestdistance){
                smallestdistance = currentdistance;
                temp = current;
                temp2 = current->next;
            }
        while(current->next != NULL){
            re1 =current->next->re;
            im1= current->next->im;
            currentdistance = distance(re1, im1, re, im);
            if(currentdistance < smallestdistance){
                smallestdistance = currentdistance;
                temp = current;
                temp2 = current->next;
                count++;
            }
            current = current->next;
        }
        if(count == 0){
            temp = head;
            head = head->next;
            free(temp);
            temp = NULL;
            return(head);
        }
        else{
            temp->next = temp->next->next;
            free(temp2);
            temp2 = NULL;
            return(head);
        }
    }
    else{
        free(current);
        current = NULL;
        head = current;
        return(head);
    }
}


int main(void){
    char cmd;
    float re, im, currentdistance, smallestdistance, rec ,imc, re1, im1, re2, im2;
    struct node_t *head = NULL;
    do{
        printf("Command: ");
        scanf(" %c", &cmd);
        switch(cmd){
            case 'q':
                printf("Bye!\n");
            break;
            case 'p':
                print_list(head);
            break;
            case 'v':
                printf("[");
                print_list_reverse(head);
                if(head != NULL){
                    printf("%.2f+%.2fi", head->re, head->im);
                }
                printf("]\n");
            break;
            case 'd':
                //display is made later or not. right now it is not for the exam so not made
            break;
            case 'h':
                printf("re, im? ");
                scanf("%f%f", &re, &im);
                insert_head(&head, re, im);
                
            break;
            case 't':
                printf("re, im? ");
                scanf("%f%f", &re, &im);
                head = insert_tail(head, re, im);
            break;
            case 'c':
                printf("re, im? ");
                scanf("%f%f", &re1, &im1);
                struct node_t *current = head;
                if(current == NULL){
                    printf("No closest node found\n");
                }
                else{
                    smallestdistance = 100000000000000000;
                    while(current != NULL){
                        re2 = current->re;
                        im2 = current->im;
                        currentdistance = distance(re1, im1, re2, im2);
                        if(currentdistance < smallestdistance){
                            smallestdistance = currentdistance;
                            rec = re2;
                            imc = im2;
                        }
                        current = current->next;
                    }
                    printf("Closest node is %.2f+%.2fi\n", rec, imc);
                }
            break;
            case 'a':
                printf("re, im? ");
                scanf("%f%f", &re, &im);
                head = insert_after_closest(head, re, im);
            break;
            case 'b':
                printf("re, im? ");
                scanf("%f%f", &re, &im);
                insert_before_closest(&head, re, im);
            break;
            case 'f':
                head = remove_front(head);
            break;
            case 'e':
                remove_end(&head);
            break;
            case 'r':
                printf("re, im? ");
                scanf("%f%f", &re, &im);
                head = remove_closest(head, re, im);
            break;
            default:
                printf("Unknown command \'%c\'\n", cmd);
            break;
        }
    }while(cmd != 'q');
}
