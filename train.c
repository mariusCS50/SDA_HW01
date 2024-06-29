/* GAIBU Marius - 315CB */
#include "train.h"

// Crează și inițializează un nou vagon
Wagon create_wagon(char c) {
    Wagon new_wagon = (Wagon)malloc(sizeof(struct wagon));
    if (!new_wagon) return NULL;

    new_wagon->code = c;
    new_wagon->next = new_wagon->prev = NULL;

    return new_wagon;
}

// Crează și inițializează trenul cu locomotiva și primul vagon
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

// Distruge și eliberează trenul
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

// Mută mecanicul în vagonul din stânga
void move_left(Train t) {
    t->current_wagon = t->current_wagon->prev;
    if (t->current_wagon == t->locomotive) {
        t->current_wagon = t->current_wagon->prev;
    }
}

// Mută mecanicul în vagonul din dreapta
void move_right(Train t) {
    if (t->current_wagon->next != t->locomotive) {
        t->current_wagon = t->current_wagon->next;
    } else {
        insert_right(t, '#');
    }
}

// Modifică inscripția vagonului curent în care se află mecanicul
void write(Train t, char c) {
    t->current_wagon->code = c;
}

// Elimină vagonul curent din tren
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

// Elimină toate vagoanele și aduce trenul la starea inițială
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

// Inserează un vagon la stânga vagonului curent unde se află mecanicul
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

// Inserează un vagon la dreapta vagonului curent unde se află mecanicul
void insert_right(Train t, char c) {
    Wagon aux = create_wagon(c);

    aux->next = t->current_wagon->next;
    aux->prev = t->current_wagon;
    t->current_wagon->next->prev = aux;
    t->current_wagon->next = aux;

    move_right(t);
}

/*
    Caută o serie de vagoane vecine ale căror inscripție formează un anumit șir
    Căutarea se face circular, începând de la vagonul curent și continuând
    până la întoarcerea la vagonul curent.
*/
void search(FILE* fout, Train t, char *pattern) {
    int idx = 0;
    char* target = NULL;
    Wagon aux = t->current_wagon;

    /*
        Construiește șirul "target" parcurgând câte un vagon și adăugând
        inscripția pe poziția curentă din "target"
    */
    do {
        if (aux != t->locomotive) {
            target = (char*)realloc(target, (idx + 2) * sizeof(char));
            target[idx++] = aux->code;
        }
        aux = aux->next;
    } while (aux != t->current_wagon);
    target[idx] = '\0';

    // Verifică dacă există în șirul "target" șirul căutat "pattern"
    char* found = strstr(target, pattern);

    // În caz afirmativ, se mută mecanicul la poziția indicată
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
    Caută o serie de vagoane vecine ale căror inscripție formează un anumit șir
    Căutarea se face liniar, de la dreapta la stânga, începând de la vagonul
    curent și continuând până la întâlnirea santinelei.
*/
void search_left(FILE* fout, Train t, char *pattern) {
    int idx = 0;
    char* target = NULL;
    Wagon aux = t->current_wagon;

    /*
        Construiește șirul "target" parcurgând câte un vagon și adăugând
        inscripția pe poziția curentă din "target"
    */
    while (aux != t->locomotive) {
        target = (char*)realloc(target, (idx + 2) * sizeof(char));
        target[idx++] = aux->code;
        aux = aux->prev;
    }
    target[idx] = '\0';

    // Verifică dacă există în șirul "target" șirul căutat "pattern"
    char* found = strstr(target, pattern);

    // În caz afirmativ, se mută mecanicul la poziția indicată
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
    Caută o serie de vagoane vecine ale căror inscripție formează un anumit șir
    Căutarea se face liniar, de la stânga la dreapta, începând de la vagonul
    curent și continuând până la întâlnirea santinelei.
*/
void search_right(FILE* fout, Train t, char *pattern) {
    int idx = 0;
    char* target = NULL;
    Wagon aux = t->current_wagon;

    /*
        Construiește șirul "target" parcurgând câte un vagon și adăugând
        inscripția pe poziția curentă din "target"
    */
    while (aux != t->locomotive) {
        target = (char*)realloc(target, (idx + 2) * sizeof(char));
        target[idx++] = aux->code;
        aux = aux->next;
    }
    target[idx] = '\0';

    // Verifică dacă există în șirul "target" șirul căutat "pattern"
    char* found = strstr(target, pattern);

    // În caz afirmativ, se mută mecanicul la poziția indicată
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

// Afișează inscripția vagonului curent în care se află mecanicul
void show_current(FILE *fout, Train t) {
    fprintf(fout, "%c\n", t->current_wagon->code);
}

/*
    Afișează conținutul curent al trenului, evidențiind vagonul curent
    în care se află mecanicul
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
