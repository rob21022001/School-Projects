#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


FILE *ptr;

void read_contents(char *filename, int contents[]){
    ptr = fopen(filename, "r");
    
    for(int i=0; i<10000; i++){
        contents[i]='\0';
    }
    
    if(ptr == NULL){
        printf("Cannot open file %s.\n", filename);
        return;
    }
    int i=0;
    while(!feof(ptr)){
        fscanf(ptr, "%c", &contents[i]);
        i++;
        }
    fclose(ptr);
    return;
}

void cat(int contents[]){
    int i=0;
    while(contents[i] != '\0'){
        printf("%c", contents[i]);
        i++;
    }
}

void rev(int contents[]){
    int size=0;
    int start=0;
    while(contents[size] != '\0'){
        if(contents[size] == '\n'){
            for(int i=size-1; i>=start; i--){
                printf("%c", contents[i]);
            }
            if(contents[size+1] == '\0') return;
            start = size;
            printf("\n");
        }
        size++;
    }
}

void wc(int contents[]){
    int lines=0;
    int words=0;
    int characters=0;
    
    while(contents[characters] != '\0'){
        if(contents[characters] == 32 && contents[characters-1] != 32){
            words++;
        }
        if(contents[characters] == '\n'){
            lines++;
        }
        characters++;
    }
    printf("%d lines, %d words, %d characters.\n", lines, words, characters);
}

void revrule(int contents[]){
    int curr=0;
    int start;;
    int temp=0;
    int i=0;
    
    
    while(1){
        while(contents[curr] != '\0'){
            if(contents[curr] == '\n' && contents[curr+1] != '\0'){
                start=curr+1;
            }
            curr++;
        }
        curr=0;
        temp = start;
        
        while(contents[start] != '\0'){
            printf("%c", contents[start]);
            start++;
        }
        
        for(int j=start-1; j>=temp; j--){
            contents[j]='\0';
            if(contents[0]=='\0') return;
        }
        start=0;
    }
}

void brackets(int contents[]){
    int lines=0;
    int count=0;
    int characters=0;
    int curr=0;
    
    
    while(contents[curr] != '\0'){
        if(contents[curr] == '('){
            count++;
        }
        if(contents[curr] == ')'){
            count--;
            if(count < 0){
                printf("Brackets not matched at line %d character %d.\n", lines, characters);
                return;
            }
        }
        if(contents[curr] == '\n'){
            lines++;
            characters=-1;
        }
        characters++;
        curr++;
    }
    
    if(count != 0){
        printf("Brackets are not matched at end of file.\n");
        return;
    }
    else{
        printf("Brackets are matched at end of file.\n");
        return;
    }
    return;
}

int main (void) {
    char cmd;
    int contents[10000];
    contents[0]=EOF;
    char name[100]="";
    char string[100]="";
    char revstring[100]="";
    int j=0;
    
    do {

    printf("Command? ");
    scanf(" %c",&cmd);
    
    switch(cmd){
        
        case 't':
            revrule(contents);
            break;
        
        case 'b':
            brackets(contents);
            break;
        
        case 'p':
            printf("String? ");
            scanf("%s", string);
            
            for(int i=strlen(string)-1; i>=0; i--){
                revstring[j] = string[i];
                j++;
            }
            
            if(strcmp(string, revstring) == 0){
                printf("Is a palindrome.\n");
            }
            else{
                printf("Is not a palindrome.\n");
            }
            break;
        
        case 'w':
            wc(contents);
            break;
        
        case 'r':
            rev(contents);
            break;
        
        case 'c':
            cat(contents);
            break;
        
        case 'f':
            printf("File name? ");
            scanf("%s", name);
            read_contents(name, contents);
            break;
        
        case 'q':
            printf("Bye!\n");
            break;
 
        default:
            printf("Unknown command '%c'\n",cmd);
            break;
    }

    }while(cmd!='q');   
    
}
