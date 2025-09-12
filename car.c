#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "car.h"

car_node_t *c_make_node(void) {
    car_node_t *new_node = malloc(sizeof(car_node_t));
    new_node->data = '#';
    new_node->next = NULL;
    new_node->prev= NULL;
    return new_node;
}

clist_t *init(void) {
   clist_t *list = malloc(sizeof(clist_t));
   car_node_t *new_node = c_make_node();
   list->head = new_node;
   list->tail = new_node;
   list->mechanic = new_node;
   list->head->next = list->tail;
   list->head->prev = list->tail;
   list->mechanic->data = '#';
   list->size = 1;
   return list;
}

void MOVE_LEFT(clist_t *list) {
    if (list->mechanic == list->head) 
        list->mechanic = list->head->prev;
    else 
        list->mechanic = list->mechanic->prev;
}

void MOVE_RIGHT(clist_t *list) {
    if (list->mechanic == list->tail) {
        car_node_t *new_node = c_make_node();
        new_node->next = list->head;
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->head->prev = new_node;
        list->tail = new_node;
        list->size++;
        list->mechanic = new_node;
    }
    else 
        list->mechanic = list->mechanic->next;
}

void WRITE_CHARACTER(clist_t *list, char *data) {
    list->mechanic->data = data[6];
}

void CLEAR_ALL(clist_t **list) {
    car_node_t *p = (*list)->head, *tmp;
    if ((*list)->head == NULL) {
        return;
    }
    while (p->next != (*list)->head) {
        tmp = p;
        p = p->next;
        free(tmp);
    }
    free(p);
    free(*list);
    *list = init();
}

void CLEAR_CELL(clist_t **list) {
    car_node_t *p = (*list)->mechanic->prev, *q = (*list)->mechanic->next;
    if ((*list)->size == 1) 
        CLEAR_ALL(list);
    else {
        if ((*list)->mechanic == (*list)->head)
            (*list)->head = q;
        else if((*list)->mechanic == (*list)->tail)
            (*list)->tail = p;
        p->next = q;
        q->prev = p;
        free((*list)->mechanic);
        (*list)->mechanic = p;
        (*list)->size--;
    }
}

void INSERT_LEFT_CHARACTER(clist_t *list, char *data, FILE *fo) {
    car_node_t *new_node = c_make_node();
    if (list->mechanic == list->head) {
        fprintf(fo, "ERROR\n");
        free(new_node);
        return;
    }
    else {
        new_node->next = list->mechanic;
        new_node->prev = list->mechanic->prev;
        list->mechanic->prev->next = new_node;
        list->mechanic->prev = new_node;
        list->mechanic = new_node;
        list->mechanic->data = data[12];
        list->size++;
    }
}

void INSERT_RIGHT_CHARACTER(clist_t *list, char *data) {
    car_node_t *new_node = c_make_node();
    if (list->mechanic == list->tail) {
        new_node->next = list->head;
        new_node->prev = list->tail;
        list->head->prev = new_node;
        list->tail->next = new_node;
        list->mechanic = new_node;
        list->tail = new_node;
    }
    else {
        new_node->prev = list->mechanic;
        new_node->next = list->mechanic->next;
        list->mechanic->next->prev = new_node;
        list->mechanic->next = new_node;
        list->mechanic = new_node;
    }
    list->mechanic->data = data[13];
    list->size++;
}

void SEARCH_LEFT(clist_t *list, char *string, FILE *fo) {
    car_node_t *aux = list->mechanic;
    char tmp[100];
    int i;
    for (i = 0; aux != list->head; i++) {
        tmp[i] = aux->data;
        aux = aux->prev; 
    }
    tmp[i++] = aux->data;
    tmp[i] = '\0';
    char *pos = strstr(tmp, string + 12);
    int idx;
    int steps;
    if (pos != NULL) {
        idx = pos - tmp;
        steps = idx + strlen(string + 12) - 1;
        while (steps != 0) {
            list->mechanic = list->mechanic->prev;
            steps--;
        }
    }
    
    else 
        fprintf(fo, "ERROR\n");
}

void SEARCH_RIGHT(clist_t *list, char *string, FILE *fo) {
    car_node_t *aux = list->mechanic;
    char tmp[100];
    int i;
    for (i = 0; aux->next != list->head; i++) {
        tmp[i] = aux->data;
        aux = aux->next; 
    }
    tmp[i++] = aux->data;
    tmp[i] = '\0';
    char *pos = strstr(tmp, string + 13);
    int idx;
    int steps;
    if (pos != NULL) {
        idx = pos - tmp;
        steps = idx + strlen(string + 13) - 1;
        while (steps != 0) {
            list->mechanic = list->mechanic->next;
            steps--;
        }
    }
    
    else 
        fprintf(fo, "ERROR\n");
}


void SEARCH_STRING(clist_t *list, char *string, FILE* fo) {
    car_node_t *aux = list->mechanic;
    char tmp[100];
    int i;
    for (i = 0; aux->next != list->mechanic; i++) {
        tmp[i] = aux->data;
        aux = aux->next; 
    }
    tmp[i++] = aux->data;
    tmp[i] = '\0';
    char *pos = strstr(tmp, string + 7);
    int idx;
    int steps;
    if (pos != NULL) {
        idx = pos - tmp;
        steps = idx;
        while (steps != 0) {
            list->mechanic = list->mechanic->next;
            steps--;
        }
    }
    
    else 
        fprintf(fo, "ERROR\n");
}

void SHOW_CURRENT(clist_t *list, FILE *fo) {
    fprintf(fo, "%c\n", list->mechanic->data);
}

void SHOW(clist_t *list, FILE *fo) {
    car_node_t *p = list->head;
    int count = 0;
    while (count < list->size) {
        if(p == list->mechanic) 
            fprintf(fo, "|%c|", p->data);
        else 
            fprintf(fo, "%c", p->data);
        p = p->next;
        count++;
    }
    fprintf(fo,"\n");
}

