/* GAIBU Marius - 315CB */
#include "train.h"

// Structura care reprezintă o celulă din coadă
typedef struct cell {
    char* cmd;
    struct cell *prev, *next;
} TCell, *TList;

// Structura care reprezintă coada
typedef struct queue {
    TList head, tail;
} Queue, *TQueue;

// Funcții de creare și distrugere a cozii de comenzi
TQueue create_cmd_queue();
void destroy_cmd_queue(TQueue* cmdQ);

// Funcția de inserare a unei comenzi în coadă
void add_command(TQueue cmdQ, char* cmd);

// Operație de tip QUERY
void switch_queue(TQueue* cmdQ);

// Operația EXECUTE
void execute_command(FILE* fout, TQueue* cmdQ, Train t);
