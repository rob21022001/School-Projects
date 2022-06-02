#include <stdio.h>
#include <string.h>
#define MAXWORDS  10
#define MAXLENGTH  30
void numberOfWordsInDict(char dict[MAXWORDS][MAXLENGTH]){
    int i, count = 0 ;
    for(i=0;i<MAXWORDS;i++){
        if (dict[i][0] != '\0'){
            count++;
        }
    }
    printf("The dictionary contains %d words\n", count);
}

void addWord(char dict[MAXWORDS][MAXLENGTH], char word[MAXLENGTH]){
    int y = 0,i;
    if(dict[MAXWORDS -1][0] == '\0'){
        for(y=0; y<MAXWORDS;y++){
            if (dict[y][0] == '\0'){
                for(i=0;i<MAXLENGTH;i++){
                    
                    dict[y][i] = word[i];
                }
                break;
            }
        }
    }
    else{
        printf("The array is full\n");
    }
}

void printdict(char dict[MAXWORDS][MAXLENGTH]){
    int i, count = 0 ;
    for(i=0;i<MAXWORDS;i++){
        if (dict[i][0] != '\0'){
            count++;
        }
    }
    if(dict[0][0] == '\0'){
        printf("The dictionary is empty.\n");
    }
    else{
        
        for(int y = 0; y < count; y++){
            printf("%s\n", dict[y]);
        }
    }
}

void removeWord(char dict[MAXWORDS][MAXLENGTH], char word[MAXLENGTH]){
    int i, count = 0 ;
    for(i=0;i<MAXWORDS;i++){
        if (dict[i][0] != '\0'){
            count++;
        }
    }
        
    for(int i=0; i< count; i++){
        if(strcmp(word, dict[i]) == 0){
            for(int j=0; j<MAXLENGTH; j++){
                dict[i][j] = '\0';
            }
            
            strcpy(dict[i], dict[count-1]);
           
            for(int k=0; k<MAXLENGTH; k++){
                    
                    dict[count-1][k] = '\0';
                    
            }
        return;
        } 
    }
    
    printf("The word \"%s\" is not in the dictionary.\n", word);
}    

void swapWords(char dict[MAXWORDS][MAXLENGTH], char word1[MAXLENGTH], char word2[MAXLENGTH]){
    int count1 = 0;
    int count2 = 0;
    int i= -1,j, k = -1;
    for(i = 0; i < MAXWORDS; i++){
        if(strcmp(word1, dict[i]) == 0){
            count1++;
        }
        if(strcmp(dict[i], word1) == 0){
            count2++;
        }
    }
    if(count1 < 1 || count2 < 1){
        printf("Cannot swap words. At least one word is missing in the dictionary.\n");
    }
    else{
        for(i = 0; i < MAXWORDS; i++){
            if(strcmp(word1, dict[i]) == 0){
                for(j = 0; j< MAXLENGTH; j++){
                    dict[i][j] = '\0';
                }
                for(j = 0; j < MAXLENGTH; j++){
                    dict[i][j] = word2[j];
                }
                break;
            }
        }
        for(k = 0; k < MAXWORDS; k++){
            if(k != i){
                printf("%d\n",k);
                printf("%s\n",word2);
                printf("%s\n",dict[k]);
                if(strcmp(word2, dict[k]) == 0){
                    printf("%d\n",k);
                    printf("%d\n",i);
                    for(j = 0; j< MAXLENGTH; j++){
                        dict[k][j] = '\0';
                    }
                    for(j = 0; j < MAXLENGTH; j++){
                        dict[k][j] = word1[j];
                    }
                    break;
                }
            }
        }
    }
}

void largestWord(char dict[MAXWORDS][MAXLENGTH]){
    char longestword[MAXLENGTH] = {""};
    int lword = 0;
    for(int i = 0; i < MAXWORDS; i++){    
        if(lword < strlen(dict[i])){
            lword = strlen(dict[i]);
            strcpy(longestword, dict[i]);
        }
    }
    if(longestword[0] == '\0'){
    }
    else{
        printf("The largest word in the dictionary is \'%s\'\n", longestword);
    }
}
void swapWords2(char dict[MAXWORDS][MAXLENGTH], char word1[MAXLENGTH], char word2[MAXLENGTH]){
    int count1 = 0;
    int count2 = 0;
    printf("%s....\n", word1);
    printf("%s...\n", word2);
    printdict(dict);
    int i= -1,j, k = -1;
    for(i = 0; i < MAXWORDS; i++){
        if(strcmp(word1, dict[i]) == 0){
            count1++;
        }
        if(strcmp(dict[i], word1) == 0){
            count2++;
        }
    }
    if(count1 < 1 || count2 < 1){
        printf("Cannot swap words. At least one word is missing in the dictionary.\n");
    }
    else{
        for(i = 0; i < MAXWORDS; i++){
            if(strcmp(word1, dict[i]) == 0){
                for(j = 0; j< MAXLENGTH; j++){
                    dict[i][j] = '\0';
                }
                for(j = 0; j < MAXLENGTH; j++){
                    dict[i][j] = word2[j];
                }
                break;
            }
        }
        printdict(dict);
        for(k = 0;k < MAXWORDS; k++){
            if(k > i){
                printf("%s.\n",dict[k]);
                printf("%s.\n",word2);
                printf("%s..\n",word1);
                if(strcmp(word2, dict[k]) == 0){
                    
                    for(j = 0; j< MAXLENGTH; j++){
                        dict[k][j] = '\0';
                    }
                    for(j = 0; j < MAXLENGTH; j++){
                        dict[k][j] = word1[j];
                    }
                    break;
                }
            }
        }
    }
    printdict(dict);
}


void sortDict(char dict[MAXWORDS][MAXLENGTH]){  
    int i, count = 0 ;
    char word1[MAXLENGTH] = {""};
    char word2[MAXLENGTH] = {""};
    for(i=0;i<MAXWORDS;i++){
        if (dict[i][0] != '\0'){
            count++;
        }
    }
    for(int i = 0; i <= count-2; i++){
        if(dict[i][0] > dict[i+1][0]){
            strcpy(word1,dict[i]);
            strcpy(word2,dict[i+1]);
            swapWords2(dict, word1, word2);
            i = -1;
        }
        else if(dict[i][0] == dict[i+1][0]){
            for(int j = 1; j < MAXLENGTH; j++){
                if(dict[i][j] > dict[i+1][j]){
                    strcpy(word1,dict[i]);
                    strcpy(word2,dict[i+1]);
                    swapWords2(dict, word1, word2);
                    i = -1;
                    break;
                }
            }
        }
    }
}

int main(void){
    char cmd, dict[MAXWORDS][MAXLENGTH] = {{""}}, word[MAXLENGTH];
    char remove[MAXLENGTH] = {""};
    char word1[MAXLENGTH] = {""};
    char word2[MAXLENGTH] = {""};
    do{
        printf("Command [qnaprslo]? ");
        scanf(" %c", &cmd); 
        if(cmd == 'p'){
            printdict(dict);
        }
        if(cmd == 'o'){
            sortDict(dict);
        }
        if(cmd == 'l'){
            largestWord(dict);
        }
        if(cmd == 's'){
            printf("Swap two words: ");
            scanf("%s%s", word1, word2);
            swapWords(dict, word1, word2);
        }
        if(cmd == 'q'){
            printf("Bye!\n");
        }
        if(cmd != 'q' && cmd != 'n' && cmd != 'a' && cmd != 'p' && cmd != 'r' && cmd != 's' && cmd != 'l' && cmd != 'o'){
            printf("Unknown command \'%c\'\n", cmd);
        }
        if(cmd == 'r'){
            printf("Remove a word: ");
            scanf("%s", remove);
            removeWord(dict, remove);
        }
        if(cmd == 'n'){
            numberOfWordsInDict(dict);
        }
        if(cmd == 'a'){
            printf("Add a word: ");
            scanf(" %s", word);
            addWord(dict, word);
        }
    }while(cmd != 'q');
     
    
}
