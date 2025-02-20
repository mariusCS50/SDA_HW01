/* GAIBU Marius - 315CB */
#include "train.h"

// Structure representing a cell in the queue
typedef struct cell {
    char* cmd;
    struct cell *prev, *next;
} TCell, *TList;

// Structure representing the queue
typedef struct queue {
    TList head, tail;
} Queue, *TQueue;

// Functions for creating and destroying the command queue
TQueue create_cmd_queue();
void destroy_cmd_queue(TQueue* cmdQ);

// Function for inserting a command into the queue
void add_command(TQueue cmdQ, char* cmd);

// QUERY operation
void switch_queue(TQueue* cmdQ);

// EXECUTE operation
void execute_command(FILE* fout, TQueue* cmdQ, Train t);
