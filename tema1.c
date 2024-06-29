/* GAIBU Marius - 315CB */
#include "queue.h"

#define MAX_COMMAND_LEN 100

int main() {
    // Deschiderea fișierelor pentru I/O
    FILE* fin = fopen("tema1.in", "rt");
    FILE* fout = fopen("tema1.out", "wt");

    // Crearea și inițializarea trenului și a cozii de comenzi
    Train train = create_train();
    TQueue cmdQ = create_cmd_queue();

    int cmd_count = 0;
    fscanf(fin, "%d\n", &cmd_count);

    char* command = (char*)malloc(MAX_COMMAND_LEN * sizeof(char));

    // Citirea comenzilor și prelucrarea acestora
    while (cmd_count--) {
        fgets(command, MAX_COMMAND_LEN, fin);
        command = strtok(command, "\n");

        if (strcmp(command, "SHOW_CURRENT") == 0) {
            show_current(fout, train);
        } else if (strcmp(command, "SHOW") == 0) {
            show(fout, train);
        } else if (strcmp(command, "SWITCH") == 0) {
            switch_queue(&cmdQ);
        } else if (strcmp(command, "EXECUTE") == 0) {
            execute_command(fout, &cmdQ, train);
        } else {
            add_command(cmdQ, command);
        }
    }

    // Distrugerea structurilor utilizate și eliberarea memoriei
    destroy_train(&train);
    destroy_cmd_queue(&cmdQ);
    free(command);

    // Închiderea fișierelor pentru I/O
    fclose(fin);
    fclose(fout);

    return 0;
}
