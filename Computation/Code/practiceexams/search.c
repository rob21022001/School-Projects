#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXLINKS 10

typedef struct page{

    char *url;
    int visited;
    struct page *links[MAXLINKS];
    struct page *next;

}page;

struct page *add_page (struct page *web, char *url){
    struct page *current = web;
    struct page *prev = NULL;
    
    while(current != NULL){
        if(strcmp(current->url, url) == 0){
            printf("URL \"%s\" is already on the web\n", url);
            return(web);
        }
        else{
            current = current->next;
        }
    }
    current = web;
    struct page *new = (struct page*)malloc(sizeof(struct page));
    new->url = malloc(sizeof(char)*100);
    strcpy(new->url, url);
    new->visited = -1;
    for(int i = 0;i < 9; i++){
        new->links[i] = NULL;
    }
    if(web == NULL){
        new->next = NULL;
        return(new);
    }
    else{
        while(current != NULL){
            if(strcmp(current->url, url) < 0){
                prev = current;
                current = current->next;
            }
            else{
                if(prev != NULL){
                    prev->next = new;
                    new->next = current;
                    return(web);
                }
                else{
                    new->next = current;
                    return(new);
                }
            }
        }
        prev->next = new;
        new->next = NULL;
        return(web);
    }
}

void print_web (struct page *web){
    int i = 0;
    struct page *current = web;
    while(current != NULL){
        i = 0;
        printf("{URL=\"%s\",visited=%d} -> ", current->url, current->visited);
        while(i < 10){
            if(current->links[i] != NULL){
                printf("\"%s\" ", (current->links[i])->url);
            }
            i++;
        }
        printf("\n");
        current = current->next;
    }
}

struct page *find_page (struct page *web, char *url){
    struct page *current = web;
    while(current != NULL){
        if(strcmp(current->url, url) == 0){
            return(current);
        }
        else{
            current = current->next;
        }
    }
    return(NULL);
}

void reset_visited (struct page *web){
    struct page *current = web;
    while(current != NULL){
        current->visited = 0;
        current = current->next;
    }
}

void add_link (struct page *web, char *source_url, char *dest_url){
    struct page *source = find_page(web, source_url);
    struct page *destination = find_page(web, dest_url);
    int i = 0;
    if(source == NULL){
        printf("Source URL \"%s\" is not on the web\n", source_url);
        return;
    }
    if(destination == NULL){
        printf("Destination URL \"%s\" is not on the web\n", dest_url);
        return;
    }
    if(strcmp(source_url, dest_url) == 0){
        printf("Source and destination URL cannot be the same\n");
        return;
    }
    while(source->links[i] != NULL){
        if(strcmp(source->links[i]->url, dest_url) == 0){
            printf("\"%s\" is already a destination for \"%s\"\n", dest_url, source_url);
            return;
        }
        i++;
        if(i == 10){
            printf("Maximum number of links reached\n");
            return;
        }
    }
    source->links[i] = destination;
    return;
}

void remove_page (struct page **web, char *url){
    struct page *current = *web;
    struct page *prev = NULL;
    int count = 0;
    int i = 0;
    while(current != NULL){
        while(current->links[i] != NULL){
            if(strcmp(current->links[i]->url, url) == 0){
                current->links[i] = NULL;
            }
            i++;
        }
        current = current->next;
    }
    current = *web;
    while(current != NULL){
        if(strcmp(current->url, url) != 0){
            prev = current;
            current = current->next;
        }
        else{
            if(prev != NULL){
                free(current->url);
                free(current);
                prev->next = current->next;
                current = NULL;
            }
            else{
                *web = current->next;
                free(current->url);
                free(current);
                current = NULL;
            }
            count++;
        }
    }
    if(count == 0){
        printf("URL \"%s\" is not on the web\n", url);
    }
    return;
}


int main(void){
    char cmd;
    char url[100] = "";
    char source_url[100] = "";
    char dest_url[100] = "";
    struct page *web = NULL;
    struct page *compare = NULL;
    do{
        printf("command? ");
        scanf(" %c", &cmd);
        switch(cmd){
            case 'P':
                printf("Page URL? ");
                scanf("%s", url);
                remove_page(&web, url);
            break;
            case 'l':
                printf("Source & destination URL? ");
                scanf("%s %s", source_url, dest_url);
                add_link(web, source_url, dest_url);
            break;
            case 'v':
                reset_visited(web);
            break;
            case 'f':
                printf("page URL? ");
                scanf("%s", url);
                compare = find_page(web, url);
                if(compare != NULL){
                    printf("URL \"%s\" is on the web\n", url);
                }
                else{
                    printf("URL \"%s\" is not on the web\n", url);
                }
            break;
            case 'w':
                print_web(web);
            break;
            case 'p':
                printf("Page URL? ");
                scanf("%s", url);
                web = add_page(web, url);
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
