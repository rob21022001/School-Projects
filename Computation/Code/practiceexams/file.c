#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CHILDREN 4

typedef struct inode{

    char *name;
    struct inode *parent;
    struct inode *children[MAX_CHILDREN];
    
}inode;


struct inode *addInode(struct inode *fs, char *name){
    struct inode *new = (struct inode*)malloc(sizeof(struct inode));
    if(new == NULL){
        return(fs);
    }
    new->name = malloc(100*sizeof(char));
    strcpy(new->name, name);
    new->parent = fs;
    for(int i = 0; i < MAX_CHILDREN; i++){
        new->children[i] = NULL;
    }
    if(fs != NULL){
        for(int i = 0; i < MAX_CHILDREN; i++){
            if(fs->children[i] != NULL){
                if(strcmp(name, fs->children[i]->name) == 0){
                    printf("File \"%s\" already exists in \"%s\"\n", name, fs->name);
                    return(NULL);
                }
            }
        }
        for(int i = 0; i < MAX_CHILDREN; i++){
            if(fs->children[i] == NULL){
                fs->children[i] = new;
                return(new);
            }
        }
        printf("Directory \"%s\" is full",fs->name);
        return(fs);
    }
    else{
        return(new);
    }
}



int main(void){
    struct inode *fc = addInode(NULL, "/");
    char cmd;
    struct inode *file = NULL;
    struct inode *directory = NULL;
    char name[100] = "";
    do{
        printf("Command? ");
        printf("%p", fc);
        scanf(" %c", &cmd);
        switch(cmd){
            case 'a':
                printf("Give filename: ");
                scanf("%s", name);
                if(name[strlen(name)-1] == '/'){
                    directory = addInode(fc  ,name);
                }
                else{
                    file = addInode(fc, name);
                }
            break;
            case 'q':
                printf("Bye!\n");
            break;
            default:
                printf("Unknown command \'%c\'\n", cmd);
            break;
        }
    }while(cmd != 'q');
}
