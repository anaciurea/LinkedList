#ifndef QUEUE_H
#define QUEUE_H
#include "car.h"

/* Structura unui nod de lista dublu inlantuita, a cozii */
typedef struct queue_node_t {
   struct queue_node_t  *next, *prev;
   char *command;
} queue_node_t;

/* Structura unei santinele pentru o lista dublu inlantuita */
typedef struct queue_t {
    queue_node_t  *head, *tail;
    unsigned int size;
}queue_t; 

/*Functie ce creeaza un nod de coada pe baza unei valori date*/
queue_node_t  *q_make_node(char *command);

/* Functie ce aloca memorie pentru o coada cu santinela si intoarce adresa acesteia*/
queue_t *q_create(void);

/*Functie ca adauga in coada un nou nod la final*/
void ad_queue_node(queue_t *q, char *command);

/*Functie ce apeleaza anumite functii(de exemplu 'MOVE_RIGHT) si apoi elimina nodul 
pe care se afla comanda( mai precis primul nod)*/
void dequeue(queue_t *q, clist_t **list, FILE *fi);

/*Functia schimba ordinea comenzilor din coada in ordine inversa*/
void q_switch(queue_t *q);

#endif