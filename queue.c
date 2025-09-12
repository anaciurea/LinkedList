#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "car.h"

queue_node_t *q_make_node(char *command) {
    queue_node_t *new_node = malloc(sizeof(queue_node_t));
    new_node->command = malloc(strlen(command) + 1);
    strcpy(new_node->command, command);
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

queue_t *q_create(void) {
    queue_t *q = malloc(sizeof(queue_t));
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

void ad_queue_node(queue_t *q, char *command) {
    queue_node_t *new_node = q_make_node(command);
    if (new_node == NULL) 
        return;
    if(q->size == 0) {
        q->head = new_node;
        q->tail = new_node;
        q->head->next = NULL;
        q->head->prev = NULL;
    }
    else {
        new_node->next = NULL;
        new_node->prev = q->tail;
        q->tail->next = new_node;
        q->tail = new_node;
    }
    q->size++;
}


void dequeue(queue_t *q, clist_t **list, FILE *fo) {
    queue_node_t *p = q->head; 
    if (q->size == 0)
        return;
    else {
        q->head = q->head->next;
        if (q->head )
            q->head->prev = NULL;
        if (strncmp("MOVE_LEFT", p->command, 9) == 0) 
            MOVE_LEFT(*list);

        else if(strncmp("MOVE_RIGHT", p->command, 10) == 0) 
            MOVE_RIGHT(*list);

        else if(strncmp("WRITE", p->command, 5) == 0) 
            WRITE_CHARACTER(*list, p->command);

        else if(strncmp("CLEAR_CELL", p->command, 10) == 0)
            CLEAR_CELL(list);

        else if(strncmp("CLEAR_ALL", p->command, 9) == 0)
            CLEAR_ALL(list);

        else if(strncmp("INSERT_LEFT", p->command, 11) == 0)
            INSERT_LEFT_CHARACTER(*list, p->command, fo);

        else if(strncmp("INSERT_RIGHT", p->command, 12) == 0)
            INSERT_RIGHT_CHARACTER(*list, p->command);

        else if(strncmp("SEARCH_RIGHT", p->command, 12) == 0)
            SEARCH_RIGHT(*list, p->command, fo);

        else if(strncmp("SEARCH_LEFT", p->command, 11) == 0)
            SEARCH_LEFT(*list, p->command, fo);

        else if (strncmp("SEARCH", p->command, 6) == 0)
            SEARCH_STRING(*list, p->command, fo);

        free(p->command);
        free(p);
    }

    q->size--;
    if (q->size == 0) {
        q->head = NULL;
        q->tail = NULL;
    }
}

void q_switch(queue_t *q) {
    if (q->size < 2) {
        return;
    }
    /* În timpul parcurgerii, se face schimbarea legăturilor next și prev ale fiecărui nod.*/
    queue_node_t *current = q->head;
    queue_node_t *after = q->head->next;
    while (current != q->tail) {
        current->next = current->prev;
        current->prev = after;
        current = after;
        after = after->next;
    }
    /*După ce s-au inversat legăturile pentru toate nodurile din coadă, este necesară încă o schimbare a legăturilor pentru nodul final (q->tail). 
    Aceasta este o etapă suplimentară, deoarece în bucla anterioară nodul q->tail nu a fost tratat în mod explicit.*/
    current->next = current->prev;
    current->prev = after;

    /*Se face schimbarea pozițiilor pointer-ului q->head cu q->tail, astfel încât capul cozii devine coada și viceversa
     Aceasta asigură că după operația de inversare, ordinea elementelor din coadă este schimbată.*/
    queue_node_t *tmp = q->head;
    q->head = q->tail;
    q->tail = tmp;
}

