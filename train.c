/* GAIBU Marius - 315CB */
#include "train.h"

// Creates and initializes a new wagon
Wagon create_wagon(char c) {
    Wagon new_wagon = (Wagon)malloc(sizeof(struct wagon));
    if (!new_wagon) return NULL;

    new_wagon->code = c;
    new_wagon->next = new_wagon->prev = NULL;

    return new_wagon;
}

// Creates and initializes the train with its locomotive and first wagon
Train create_train() {
    Train t = (Train)malloc(sizeof(struct train));
    if (!t) return NULL;

    Wagon locomotive = create_wagon('0');
    Wagon first_wagon = create_wagon('#');

    locomotive->next = locomotive->prev = first_wagon;
    first_wagon->next = first_wagon->prev = locomotive;

    t->locomotive = locomotive;
    t->current_wagon = first_wagon;

    return t;
}

// Destroys and frees the train
void destroy_train(Train* t) {
    Wagon w = (*t)->locomotive, aux = NULL;
    (*t)->locomotive->prev->next = NULL;
    (*t)->current_wagon = NULL;
    while (w) {
        aux = w;
        w = w->next;
        free(aux);
    }
    free(*t);
}

// Moves the mechanic to the wagon on the left
void move_left(Train t) {
    t->current_wagon = t->current_wagon->prev;
    if (t->current_wagon == t->locomotive) {
        t->current_wagon = t->current_wagon->prev;
    }
}

// Moves the mechanic to the wagon on the right
void move_right(Train t) {
    if (t->current_wagon->next != t->locomotive) {
        t->current_wagon = t->current_wagon->next;
    } else {
        insert_right(t, '#');
    }
}

// Modifies the code of the current wagon where the mechanic is located
void write(Train t, char c) {
    t->current_wagon->code = c;
}

// Removes the current wagon from the train
void clear_cell(Train t) {
    if (t->locomotive->next == t->locomotive->prev) {
        write(t, '#');
    } else {
        Wagon aux = t->current_wagon;

        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;

        move_left(t);
        free(aux);
    }
}

// Removes all wagons and resets the train to its initial state
void clear_all(Train t) {
    t->current_wagon = t->locomotive->next;
    t->current_wagon->code = '#';

    Wagon w = t->current_wagon->next, aux = NULL;
    while (w != t->locomotive) {
        aux = w;
        w = w->next;
        free(aux);
    }

    t->locomotive->prev = t->current_wagon;
    t->current_wagon->next = t->locomotive;
}

// Inserts a wagon to the left of the current wagon where the mechanic is located
void insert_left(FILE* fout, Train t, char c) {
    if (t->current_wagon->prev == t->locomotive) {
        fprintf(fout, "ERROR\n");
    } else {
        Wagon aux = create_wagon(c);

        aux->next = t->current_wagon;
        aux->prev = t->current_wagon->prev;
        t->current_wagon->prev->next = aux;
        t->current_wagon->prev = aux;

        move_left(t);
    }
}

// Inserts a wagon to the right of the current wagon where the mechanic is located
void insert_right(Train t, char c) {
    Wagon aux = create_wagon(c);

    aux->next = t->current_wagon->next;
    aux->prev = t->current_wagon;
    t->current_wagon->next->prev = aux;
    t->current_wagon->next = aux;

    move_right(t);
}

/*
    Constructs the "target" string by iterating through each wagon and appending
    the wagon's code at the current position in "target"
*/
void search(FILE* fout, Train t, char *pattern) {
    int idx = 0;
    char* target = NULL;
    Wagon aux = t->current_wagon;

    /*
        Constructs the "target" string by iterating through each wagon and appending
        the wagon's code at the current position in "target"
    */
    do {
        if (aux != t->locomotive) {
            target = (char*)realloc(target, (idx + 2) * sizeof(char));
            target[idx++] = aux->code;
        }
        aux = aux->next;
    } while (aux != t->current_wagon);
    target[idx] = '\0';

    // Checks if the searched pattern exists in the target string
    // If found, moves the mechanic to the indicated position
    char* found = strstr(target, pattern);

    if (found) {
        int steps = (int)(strlen(target) - (found - target));
        while (steps--)  {
            move_left(t);
        }
    } else {
        fprintf(fout, "ERROR\n");
    }

    free(target);
}

/*
    Constructs the "target" string by iterating through each wagon and appending
    the wagon's code at the current position in "target"
*/
void search_left(FILE* fout, Train t, char *pattern) {
    int idx = 0;
    char* target = NULL;
    Wagon aux = t->current_wagon;

    /*
        Constructs the "target" string by iterating through each wagon and appending
        the wagon's code at the current position in "target"
    */
    while (aux != t->locomotive) {
        target = (char*)realloc(target, (idx + 2) * sizeof(char));
        target[idx++] = aux->code;
        aux = aux->prev;
    }
    target[idx] = '\0';

    // Checks if the searched pattern exists in the target string
    // If found, moves the mechanic to the indicated position
    char* found = strstr(target, pattern);

    if (found) {
        int steps = (int)((found - target) + strlen(pattern) - 1);
        while (steps--)  {
            move_left(t);
        }
    } else {
        fprintf(fout, "ERROR\n");
    }

    free(target);
}

/*
    Constructs the "target" string by iterating through each wagon and appending
    the wagon's code at the current position in "target"
*/
void search_right(FILE* fout, Train t, char *pattern) {
    int idx = 0;
    char* target = NULL;
    Wagon aux = t->current_wagon;

    /*
        Constructs the "target" string by iterating through each wagon and appending
        the wagon's code at the current position in "target"
    */
    while (aux != t->locomotive) {
        target = (char*)realloc(target, (idx + 2) * sizeof(char));
        target[idx++] = aux->code;
        aux = aux->next;
    }
    target[idx] = '\0';

    // Checks if the searched pattern exists in the target string
    // If found, moves the mechanic to the indicated position
    char* found = strstr(target, pattern);

    if (found) {
        int steps = (int)((found - target) + strlen(pattern) - 1);
        while (steps--)  {
            move_right(t);
        }
    } else {
        fprintf(fout, "ERROR\n");
    }

    free(target);
}

// Displays the code of the current wagon where the mechanic is located
void show_current(FILE *fout, Train t) {
    fprintf(fout, "%c\n", t->current_wagon->code);
}

/*
    Displays the current content of the train, highlighting the current wagon
    where the mechanic is located
*/
void show(FILE *fout, Train t) {
    Wagon aux = t->locomotive->next;

    while (aux != t->locomotive) {
        if (aux == t->current_wagon) {
            fprintf(fout, "|%c|", aux->code);
        } else {
            fprintf(fout, "%c", aux->code);
        }
        aux = aux->next;
    }

    fprintf(fout, "\n");
}
