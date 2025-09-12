#ifndef CAR_H_
#define CAR_H_

/* Structura unui nod de lista dublu inlantuita circulara */
typedef struct car_node_t {
    char data;
	struct car_node_t *next;
	struct car_node_t *prev;
} car_node_t;

/* Structura unei santinele pentru o lista dublu inlantuita circulara */
typedef struct clist_t {
	car_node_t *mechanic;
	car_node_t *tail;
	car_node_t *head;
	unsigned int size;
} clist_t;

/* Functie ce creeaza un nod de lista */
car_node_t *c_make_node(void);

/*Functie ce initializeaza trenul*/
clist_t *init(void);

/*Functie ce muta mecanicul la stanga. In cazul in care mecanicul se aflu pe prima pozitie,
 mecanicul se va muta in ultimul vagon al trenului*/
void MOVE_LEFT(clist_t *list);

/*Functie ce muta mecanicul la dreapta. In cazul in care mecanicul se afla in ultimul vagon, 
se va insera un nou vagon*/
void MOVE_RIGHT(clist_t *list);

/*Functie ce scrie in vagonul in care se afla mecanicul un caracter dat*/
void WRITE_CHARACTER(clist_t *list, char *data);

/*Functie ce aduce trenul in starea initiala*/
void CLEAR_ALL(clist_t **list);

/*Functie ce elimina vagonul in care se afla mecanicul si reface legaturile. Dupa eliminarea
vagonului, mecanicul se va muta la stanga*/
void CLEAR_CELL(clist_t **list);

/*Functie ce introduce un nou vagon la stanga mecanicului si muta mecanicul in noul vagon. 
In cazul in care mecanicul se aflu pe prima pozitie, se va afisa mesajul 'ERROR'*/
void INSERT_LEFT_CHARACTER(clist_t *list, char *data, FILE *fo);

/*Functie ce introduce un nou vagon la dreapta mecanicului si muta mecanicul in noul vagon. */
void INSERT_RIGHT_CHARACTER(clist_t *list, char *data);

void SEARCH_STRING(clist_t *list, char *string, FILE *fo);

/*Functie ce cauta un sir de caractere 'string' pe vagoanele trenului(concatenez caracterele
de pe vagoane) la stanga mecanicului, iar apoi va muta mecanicul pe pozitia ultimului caracter
gasit din sir. In caz contrar, daca nu se va regasi sirul 'string, se va afisa mesajul 'ERROR' */
void SEARCH_LEFT(clist_t *list, char *string, FILE *fo);

/*Functie ce cauta un sir de caractere 'string' pe vagoanele trenului(concatenez caracterele
de pe vagoane) la dreapta mecanicului, iar apoi va muta mecanicul pe pozitia ultimului caracter
gasit din sir. In caz contrar, daca nu se va regasi sirul 'string, se va afisa mesajul 'ERROR' */
void SEARCH_RIGHT(clist_t *list, char *string, FILE *fo);

/*Functie ce afiseaza doar vagonul in care se afla mecanicul*/
void SHOW_CURRENT(clist_t *list, FILE *fi);

/*Functie ce afiseaza tot trenul(lista dublu inlantuita circulara)*/
void SHOW(clist_t *list, FILE *fo);

#endif