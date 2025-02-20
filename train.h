/* GAIBU Marius - 315CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Structure representing a train wagon
typedef struct wagon {
    char code;
    struct wagon *prev, *next;
} *Wagon;

// Structure representing the train
typedef struct train {
    Wagon locomotive, current_wagon;
} *Train;

// Functions for creating and destroying the train
Wagon create_wagon(char c);
Train create_train();
void destroy_train(Train* t);

// UPDATE operations
void move_left(Train t);
void move_right(Train t);
void write(Train t, char c);
void clear_cell(Train t);
void clear_all(Train t);
void insert_left(FILE* fout, Train t, char c);
void insert_right(Train t, char c);

// SEARCH operations
void search(FILE* fout, Train t, char* s);
void search_left(FILE* fout, Train t, char* s);
void search_right(FILE* fout, Train t, char* s);

// QUERY operations
void show_current(FILE* fout, Train t);
void show(FILE *fout, Train t);
