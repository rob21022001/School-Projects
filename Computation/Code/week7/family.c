#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct person {
    char name[100];
    int birthyear;
    struct person *mother;
    struct person *father;
    struct person *nextperson;
}person;

struct person *findperson (struct person *families, char *person){
    struct person *current = families;
    while(current != NULL){
        if(strcmp(current->name, person) == 0){
            return(current);
        }
        current = current->nextperson;
    }
    return(NULL);
}

void print (struct person *families) {
    struct person *current = families;
    char mother[100] = "";
    char father[100] = "";
    if(current == NULL){
        return;
    }
    if(families->nextperson != NULL){
        current = current->nextperson;
        if(current->mother == NULL){
            strcpy(mother, "unknown");
        }
        else{
            strcpy(mother, current->mother->name);
        }
        if(current->father == NULL){
            strcpy(father, "unknown");
        }
        else{
            strcpy(father, current->father->name);
        }
        print(current);
        printf("name=%s birthyear=%d mother=%s father=%s\n" ,current->name, current->birthyear, mother, father);
    }
    return;
}

void addperson (struct person **families, char *name, int birthyear) {
    struct person *current = NULL;
    struct person *value = NULL;
    current = *families;
    if(strcmp(name, "unknown") == 0){
        printf("A person cannot be called unknown.\n");
        return;
    }
    else{
        value = findperson(*families, name);
        if(value != NULL){
            printf("Person %s already exists\n", name);
        }
        else{
            struct person *new = (struct person*)malloc(sizeof(struct person));
            if(current == NULL){
                new->birthyear = birthyear;
                strcpy(new->name, name);
                new->nextperson = NULL;
                *families = new;
                return;
            }
            else{
                while(current->nextperson != NULL){
                    current = current->nextperson;
                }
                new->birthyear = birthyear;
                strcpy(new->name, name);
                new->nextperson = NULL;
                current->nextperson = new;
                return;
            }
        }
    }
}

void addparents (struct person *families, char *person, char *mother, char *father){
    struct person *stperson = NULL;
    struct person *stmother = NULL;
    struct person *stfather = NULL; 
    stperson = findperson(families, person);
    stmother = findperson(families, mother); 
    stfather = findperson(families, father); 
    if(stperson == NULL){
        printf("Person %s not found.\n", person);
        return;
    }
    if(stmother == NULL){
        printf("Mother %s not found.\n", mother);
    }
    else if(stperson->mother != NULL){
        printf("Person %s already has a mother %s.\n", person, stperson->mother->name);
    }
    else{
        stperson->mother = stmother;
    }
    if(stfather == NULL){
        printf("Father %s not found.\n", father);
    }
    else if(stperson->father != NULL){
        printf("Person %s already has a father %s.\n", person, stperson->father->name);
    }
    else{
    stperson->father = stfather;
    return;
    }
}

int ancestor(struct person *young, struct person *old, int level){
    int m, f;
    if(young == NULL || old == NULL){
        return -1;
    }
    else if(young == old){
        return level;
    }
    else{
        level++;
        printf("%d,\n", level);
        m= ancestor(young->mother, old, level);
        f = ancestor(young->father, old, level);
        
        if(m == -1 || f == -1){
            if(m > f){
                return m;
            }
            else{
                return f;
            }
        }
        else{
            if(m < f){
                return m;
            }
            else{
                return f;
            }
        }
    }
}
        
        
        
int main(void){
    char mother[100] = "";
    char father[100] = "";
    char ancestors[100] = "";
    int birthyear = 0;
    char cmd;
    char name[100] = "";
    struct person *families = NULL;
    struct person *young = NULL;
    struct person *old = NULL;
    int value;
    do{
        printf("Command? ");
        scanf(" %c", &cmd);
        switch(cmd){
            case 'a':
                printf("Person? ");
                scanf(" %s", name);
                printf("Possible ancestor? ");
                scanf(" %s", ancestors);
                young = findperson(families, name);
                old = findperson(families, ancestors); 
                value = ancestor(young, old, 0);
                switch(value){
                    case -1:
                        printf("%s is not an ancestor of %s.\n", ancestors, name);
                    break;
                    case 0:
                        printf("%s is the same person as %s.\n", ancestors, name);
                    break;
                    case '1':
                        printf("%s is a parent of %s\n", ancestors, name);
                    default:
                        printf("%s is a ", ancestors);
                        for(int i = 0; i < value-2; i++){
                            printf("great ");
                        }
                        printf("grandparent of %s.\n", name);
                    break;
                }
            break;
            case 'p':
                printf("Person? ");
                scanf(" %s", name);
                printf("Mother? ");
                scanf(" %s", mother);
                printf("Father? ");
                scanf(" %s", father);
                addparents(families, name, mother, father);
            break;
            case 't':
                print(families);
                if(families == NULL){
                }
                else{
                    if(families->mother == NULL){
                        strcpy(mother, "unknown");
                    }
                    else{
                        strcpy(mother, families->mother->name);
                    }
                    if(families->father == NULL){
                        strcpy(father, "unknown");
                    }
                    else{
                        strcpy(father, families->father->name);
                    }
                    printf("name=%s birthyear=%d mother=%s father=%s\n" ,families->name, families->birthyear, mother, father);
                }
            break;
            case 'i':
                printf("Name? ");
                scanf("%s", name);
                printf("Birth year? ");
                scanf("%d", &birthyear);
                addperson(&families, name, birthyear);
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
