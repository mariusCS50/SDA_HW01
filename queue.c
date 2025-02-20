/* GAIBU Marius - 315CB */
#include "queue.h"

// Creates the command queue
TQueue create_cmd_queue() {
    TQueue cmdQ = (TQueue)malloc(sizeof(Queue));
    if (!cmdQ) return NULL;
    cmdQ->head = cmdQ->tail = NULL;
    return cmdQ;
}

// Destroys and frees the command queue
void destroy_cmd_queue(TQueue* cmdQ) {
    TList p = (*cmdQ)->head, aux = NULL;
    (*cmdQ)->head = (*cmdQ)->tail = NULL;

    while (p) {
        aux = p;
        p = p->next;
        free(aux->cmd);
        free(aux);
    }

    free(*cmdQ);
}

// Adds a command to the queue
void add_command(TQueue cmdQ, char* cmd) {
    TList aux = (TList)malloc(sizeof(TCell));
    if (!aux) return;

    aux->cmd = (char*)malloc((strlen(cmd) + 1) * sizeof(char));
    if (!aux->cmd) return;

    snprintf(aux->cmd, (strlen(cmd) + 1), "%s", cmd);

    if (!cmdQ->tail) {
        aux->next = aux->prev = NULL;
        cmdQ->head = cmdQ->tail = aux;
    } else {
        aux->prev = cmdQ->tail;
        aux->next = NULL;
        cmdQ->tail->next = aux;
        cmdQ->tail = aux;
    }
}

// Executes the first command from the queue
void execute_command(FILE* fout, TQueue* cmdQ, Train t) {
    if ((*cmdQ)->head == NULL) return;
    TList aux = (*cmdQ)->head;

    if (strcmp(aux->cmd, "MOVE_LEFT") == 0) {
        move_left(t);
    }
    if (strcmp(aux->cmd, "MOVE_RIGHT") == 0) {
        move_right(t);
    }
    if (strstr(aux->cmd, "WRITE")) {
        write(t, 0[aux->cmd + strlen("WRITE ")]);
    }
    if (strcmp(aux->cmd, "CLEAR_CELL") == 0) {
        clear_cell(t);
    }
    if (strcmp(aux->cmd, "CLEAR_ALL") == 0) {
        clear_all(t);
    }
    if (strstr(aux->cmd, "INSERT_LEFT")) {
        insert_left(fout, t, 0[aux->cmd + strlen("INSERT_LEFT ")]);
    }
    if (strstr(aux->cmd, "INSERT_RIGHT")) {
        insert_right(t, 0[aux->cmd + strlen("INSERT_RIGHT ")]);
    }
    if (strstr(aux->cmd, "SEARCH ")) {
        search(fout, t, aux->cmd + strlen("SEARCH "));
    }
    if (strstr(aux->cmd, "SEARCH_LEFT")) {
        search_left(fout, t, aux->cmd + strlen("SEARCH_LEFT "));
    }
    if (strstr(aux->cmd, "SEARCH_RIGHT")) {
        search_right(fout, t, aux->cmd + strlen("SEARCH_RIGHT "));
    }

    if ((*cmdQ)->head == (*cmdQ)->tail) {
        (*cmdQ)->head = (*cmdQ)->tail = NULL;

    } else {
       (*cmdQ)->head = (*cmdQ)->head->next;
       (*cmdQ)->head->prev = NULL;
    }
    free(aux->cmd);
    free(aux);
}

// Reverses the order of commands in the queue
void switch_queue(TQueue* cmdQ) {
    TList L = (*cmdQ)->head, aux = NULL;

    while (L != NULL) {
        aux = L->next;
        L->next = L->prev;
        L->prev = aux;
        L = aux;
    }

    aux = (*cmdQ)->head;
    (*cmdQ)->head = (*cmdQ)->tail;
    (*cmdQ)->tail = aux;
}
