#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "car.h"
#include "queue.h"

int main()
{
    /*Deschid fisieruele de intrafre si iesire, iar apoi verific
     daca s-au deschis cu succes*/
    FILE *fi = fopen("tema1.in", "r");

    FILE *fo = fopen("tema1.out", "w");

    if (fi == NULL)
    {
        printf("ERROR");
        exit(1);
    }

    if (fo == NULL)
    {
        printf("ERROR");
        exit(1);
    }

    /*Citesc numarul de comezni din fisier, iar apoi initializez lista si coada*/
    int nr_of_commands;
    fscanf(fi, "%d", &nr_of_commands);
    fgetc(fi);

    clist_t *list = init();

    queue_t *q = q_create();

    /*Verific fiecare comanda pe care trebuie sa o implementez cu functia care se afla in fisierul de intrare. 
    Daca strcmp(f, buffer) == 0, atunci adaug comanda la finalul cozii. Daca nu voi verifica si celalate functii.
    Numai atunci cand gasesc comanda 'EXECUTE' apelez functia si o elimin din coada*/
    char buffer[50];
    int i;
    for (i = 0; i < nr_of_commands; i++)
    {
        fgets(buffer, 50, fi);
        buffer[strlen(buffer) - 1] = '\0';

        if (strncmp("MOVE_LEFT", buffer, 9) == 0)
            ad_queue_node(q, buffer);

        else if (strncmp("MOVE_RIGHT", buffer, 10) == 0)
            ad_queue_node(q, buffer);

        else if (strncmp("WRITE", buffer, 5) == 0)
            ad_queue_node(q, buffer);

        else if (strncmp("CLEAR_ALL", buffer, 9) == 0)
            ad_queue_node(q, buffer);

        else if (strncmp("INSERT_LEFT", buffer, 11) == 0)
            ad_queue_node(q, buffer);

        else if (strncmp("INSERT_RIGHT", buffer, 12) == 0)
            ad_queue_node(q, buffer);

        else if (strncmp("CLEAR_ALL", buffer, 9) == 0) 
            ad_queue_node(q, buffer);
        
        else if (strncmp("CLEAR_CELL", buffer, 10) == 0) 
            ad_queue_node(q, buffer);

        else if (strncmp("SEARCH_RIGHT", buffer, 12) == 0) 
            ad_queue_node(q, buffer);

        else if (strncmp("SEARCH_LEFT", buffer, 11) == 0) 
             ad_queue_node(q, buffer);

        else if (strncmp("SEARCH", buffer, 6) == 0)
            ad_queue_node(q, buffer);

        else if (strncmp("SHOW_CURRENT", buffer, 12) == 0)
            SHOW_CURRENT(list, fo);

        else if (strncmp("SHOW", buffer, 4) == 0)
            SHOW(list, fo);

        else if (strncmp("EXECUTE", buffer, 7) == 0)
            dequeue(q, &list, fo);

        else if(strncmp("SWITCH", buffer, 6) == 0) {
            q_switch(q);
        }
    }

    car_node_t *current = list->head;
    while (current != NULL) {
        car_node_t *next = current->next;
        if (current == list->tail) {
            free(current);
            break;
        }
 
        free(current);
        current = next;
 
        list->size--;
    }
 
    queue_node_t *queue_current = q->head;
    while (queue_current != NULL) {
        queue_node_t *next = queue_current->next;
 
        free(queue_current->command);
        free(queue_current);
        queue_current = next;
 
        q->size--;
    }

    free(q);
    fclose(fi);
    fclose(fo);
    free(list);
    return 0;
}