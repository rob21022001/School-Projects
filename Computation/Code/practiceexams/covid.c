#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct person {
    char *name;
    struct person *contacts;
    struct person *next;
};

void add_person(struct person **persons, char *name){
    struct person *new = (struct person *) malloc (sizeof(char)*100);
    struct person *curr = *persons;
    
    new->name = (char *) malloc (sizeof(char)*100);
    strcpy(new->name, name);
    new->contacts = NULL;
    
    if(curr != NULL){
        new->next = curr;
        *persons = new;
        return;
    }
    else{
        *persons = new;
        new->next = NULL;
        return;
    }
}

void print_persons(struct person *persons){
    struct person *curr = persons;
    struct person *temp = persons;
    
    while(curr != NULL){
        printf("Person: %s\n", curr->name);
        temp = curr;
        while(temp->contacts != NULL){
            printf("- %s\n", temp->contacts->name);
            temp = temp->contacts;
        }
        curr = curr->next;
    }
    return;
}

struct person *find_person(struct person *persons, char *name){
    struct person *curr = persons;
    
    while(curr != NULL){
        if(strcmp(curr->name, name) == 0){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void add_contact(struct person *person, char *name)
{
    struct person *new = (struct person *) malloc (sizeof(struct person));
    struct person *curr = person;
    
    new->name = (char *) malloc (sizeof(char)*100);
    strcpy(new->name, name);
    new->contacts = NULL;
    new->next = NULL;
    
    while(curr->contacts != NULL){
        curr = curr->contacts;
    }
    curr->contacts = new;
    return;
}

void remove_contact(struct person *person, char *name){
    struct person *curr = person;
    
    while(curr->contacts != NULL){
        if(strcmp(curr->contacts->name, name) == 0){
            free(curr->contacts->name);
            free(curr->contacts);
            if(curr->contacts->contacts == NULL){
                curr->contacts = NULL;
                return;
            }
            else{
                curr->contacts = curr->contacts->contacts;
                return;
            }
        }
        curr = curr->contacts;
    }
    return;
}

struct person *remove_person(struct person *persons, char *name){
   
    struct person *curr = persons;
    struct person *remove = persons;
    struct person *prev = persons;
    struct person *temp = persons;
    remove = find_person(persons, name);
    struct person *remove1 = remove;
    
    //remove the person you want to remove as a contact of other persons
    while(curr != NULL){
        temp = curr;
        while(temp->contacts != NULL){
            if(strcmp(temp->contacts->name, name) == 0){
                remove_contact(curr, name);
                break;
            }
            temp = temp->contacts;
        }
        curr = curr->next;
    }
    
    //remove all contacts of node remove
    while(remove1->contacts != NULL){
        remove_contact(remove1, remove1->contacts->name);
    }
    curr = persons;
        
    if(curr == remove){
        free(remove->name);
        free(remove);
        persons = curr->next;
    }
    else{
        while(curr != remove){
            prev = curr;
            curr = curr->next;
        }
        free(remove->name);
        free(remove);
        prev->next = remove->next;
    }
    return persons;
}

int main (void){
    
    struct person *persons = NULL;
    struct person *person = NULL;
    char cmd;
    char name[100] = "";
    char A[100] = "";
    char B[100] = "";
    
    do{
        printf("Command? ");
        scanf(" %c", &cmd);
        
        switch(cmd){
            
            case 'R':
                printf("Person? ");
                scanf("%s", name);
                persons = remove_person(persons, name);
                break;
            
            case 'r':
                printf("Person A? ");
                scanf("%s", A);
                printf("Person B? ");
                scanf("%s", B);   
                person = find_person(persons, A);
                remove_contact(person, B);
                break;
            
            case 'c':
                printf("Person A? ");
                scanf("%s", A);
                printf("Person B? ");
                scanf("%s", B);             
                person = find_person(persons, A);
                add_contact(person, B);
                break;
            
            case 'p':
                print_persons(persons);
                break;
            
            case 'a':
                printf("Person? ");
                scanf("%s", name);
                add_person(&persons, name);
                break;
            
            case 'q':
                printf("Bye!\n");
                break;
                
            default:
                if(cmd != 'q'){
                    printf("Unknown command '%c'\n", cmd);
                }
                break;
        }
        
    }while(cmd != 'q');
}

