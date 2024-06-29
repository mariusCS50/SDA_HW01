/* GAIBU Marius - 315CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Structura care reprezintă un vagon al trenului
typedef struct wagon {
    char code;
    struct wagon *prev, *next;
} *Wagon;

// Structura care reprezintă trenul
typedef struct train {
    Wagon locomotive, current_wagon;
} *Train;

// Funcții de creare și distrugere a trenului
Wagon create_wagon(char c);
Train create_train();
void destroy_train(Train* t);

// Operații de tip UPDATE
void move_left(Train t);
void move_right(Train t);
void write(Train t, char c);
void clear_cell(Train t);
void clear_all(Train t);
void insert_left(FILE* fout, Train t, char c);
void insert_right(Train t, char c);

// Operații de tip SEARCH
void search(FILE* fout, Train t, char* s);
void search_left(FILE* fout, Train t, char* s);
void search_right(FILE* fout, Train t, char* s);

// Operații de tip QUERY
void show_current(FILE* fout, Train t);
void show(FILE *fout, Train t);
