
#include <stdio.h> // for printf, scanf, putchar, etc.
#include <string.h> // for strlen
#include <ctype.h> // for tolower
#include "libpynq.h"
void printchar (char c) {
putchar(c);
fflush(NULL);
sleep_msec(100);
}

/*int isconsonant(char c){
    if(c == 'b' || c == 'c' || c == 'd' || c == 'f' || c == 'g' || c == 'h' || c == 'j' || c == 'k' || c == 'l' || c == 'm' || c == 'n' || c == 'p'|| c == 'q' || c == 'r' || c == 's' || c == 't' || c == 'v' || c == 'w' || c == 'x' || c == 'y' || c == 'z'){ 

    }
}

int isvowel(char c){
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
    }
}

int is0to9(char c){
    if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9'){

    }
}
*/
void printstring (char s[]) {
    int i;
    char c;
    for(i = 0;; i++){
        c = s[i];
        printchar(c);
        if ( c == '\0'){
            break;
        }
    }
}
    
void printarray(char s[], int length){
        int i;
    char c;
    for(i = 0; i < length; i++){
        c = s[i];
        printchar(c);
    }
}

void insertChar(char str[], char aChar, int index){
    for(int i = strlen(str); i >= index; i--){
        str[i+1] = str[i];
    }
    str[index] = aChar;
}

void findFirstOccurenceChar(char str[], char aChar){
    int index = 0;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == aChar){
            index = i;
        }
        if(i == strlen(str)){
            index = -1;
        }
    }
    printf("The first occurence of \'%c\' is at index %d\n",aChar, index);
}

void replaceChars(char str[], char sChar[], char rChar){
    for(int i=0; i<strlen(str); i++){
        for(int j=0; j<strlen(sChar); j++){
            if(str[i] == sChar[j]){
                str[i] = rChar;
            }
            
        }
    }
} 

void stringReorder(char str[], int index1, int index2){
    char substring1[96] = "";
    char substring2[96] = "";
    char substring3[96] = "";
    
    strncpy(substring1, str, index1);
    strncpy(substring2, str + index1, (index2) - (index1));
    strncpy(substring3, str + index2, strlen(str) - (index2));

    for(int i = 0; i < strlen(str); i++){
         str[i] = '\0';
    }
    
    strcat(str, substring3);
    strcat(str, substring2);
    strcat(str, substring1);
}

int main (void) {
    char cmd, aChar;
    char myString[200] = "";
    int length, index, index1, index2, g, i, count;
    char c;
    char replace[96] = "";
    char replacing [96] = "aeoui";
    char d = 'a';
    char InsertthisChar1= 'a';
    char InsertthisChar2 = 'y';;
    char lower;
    
    do {
        printf("Command [qsparoRi123]? ");

        scanf(" %c",&cmd);
        switch (cmd) {
            case '1':
                replaceChars(myString, replacing, d);
            break;
            case '2':
                for( g = strlen(myString)-1; g > -1; g--){ 
                    if(myString[g] == ' '){
                        lower = tolower(myString[g+1]);
                        if(lower == 'b' || lower == 'c' || lower == 'd' || lower == 'f' || lower == 'g' || lower == 'h' || lower == 'j' || lower == 'k' || lower == 'l' || lower == 'm' || lower == 'n' || lower == 'p'|| lower == 'q' || lower == 'r' || lower == 's' || lower == 't' || lower == 'v' || lower == 'w' || lower == 'x' || lower == 'y' || lower == 'z'){ 
                            insertChar(myString, InsertthisChar1, g + 1);
                            insertChar(myString, InsertthisChar2, g + 2);
                        }
                    }
                }
            break;
            case '3':
                count = 0;
                myString[strlen(myString)] = ' ';
                for(i = 0; i < strlen(myString); i++){
                    if((myString[i] == ' ')){
                        stringReorder(myString, 0, i+1);
                        count++;
                        if(count >= 2){
                            myString[strlen(myString) - 1] = '\0';
                            break;
                        }
                    }
                }
                        
                    
            break;
            case 'r':
                printf("Please enter two indices? ");
                scanf("%d", &index1);
                scanf("%d", &index2);
                stringReorder(myString, index1, index2);
            break;
            case 'q':
                printf("Bye!\n");
            break;
            case 'p':
                printf("the current string is \"" );
                printstring(myString);
                printf("\"\n");
                
            break;
            case 'a':
                printf("the current array is \"");
                length = strlen(myString);
                printarray(myString, length);
                printf("\"\n");
            break;
            case 's':
                printf("Please enter a string: ");
                scanf(" %[^\n]s", myString);
            break;
            case 'i':
                printf("Insert which (non-space) character? ");
                scanf (" %c", &aChar);
                printf("At what index? ");
                scanf("%d", &index);
                insertChar(myString, aChar, index);
            break;
            case 'o':
                printf("Find occurence of which (non-space) character? ");
                scanf(" %c", &aChar);
                findFirstOccurenceChar(myString, aChar);
            break;
            case 'R':
                printf("Replace which (non-space) characters? ");
                scanf("%s", replace); // read a sequence of non-space characters
                printf("with which (non-space) character? ");
                scanf(" %c",&c); // skip leading spaces
                replaceChars(myString, replace, c);
            break;
            default:
                printf("Unknown command ’%c’\n",cmd);
            break;

        }
    } while (cmd != 'q');
}
