# TEMA 1 - SDA

Am mers pe un schelet incluziv, librăriile necesare le-am inclus în train.h, care este inclus în queue.h, care este la rândul său inclus în tema1.c.

Am vrut ca codul să fie ușor de înțeles și ușor de prelucrat, de acceea am creat funcții pentru toate tipurile de operații.

La început am făcut trenul și toate funcțiile legate de tren, apoi am făcut coada și toate funcțiile legate de coadă, în afară de execute_command().

După ce m-am asigurat că toate funcțiile funcționează separat, am realizat legătura dintre coadă și tren prin funcția execute_command(), care în funcție de comanda din coadă realizează operația respectivă pe tren.

După ce m-am asigurat că și asta funcționează, am adăugat citirea din fișiere și prelucrarea comenzilor, cele care trebuie să se realizeze instantaneu la citire, iar restul sunt adăugate în coadă și executate la apelul comenzii "EXECUTE".

Pe parcursul acestei teme nu am folosit bucăți de cod din cursurile de SDA, de pe internet, sau de tool-uri de inteligență artificială, am realizat totul de la 0 din cunoștințele mele de la cursuri și laboratoare. Tema nu a fost foarte complicată, totul a fost bine structurat, ceea ce a ușurat scrierea codului, citirea, prelucrarea comenzilor, etc...

Pentru a corecta unele erori de conding style am folosit clang-tidy și cpplint.
## Header Files
Am folosit câte un header file separat pentru tren (train.h) și pentru coada de comenzi (queue.h) pentru a organiza mai bine structurile și funcțiile care țin de tren, respectiv, de coadă.

### train.h
```c
typedef struct wagon {
    char code;
    struct wagon *prev, *next;
} *Wagon;
```
este asemănătoare cu declarați celulei unei liste dublu înlănțuite.

```c
typedef struct train {
    Wagon locomotive, current_wagon;
} *Train;
```
reprezintă trenul care conține lista dublu înlănțuită începând de la santinelă (locomotivă) și adresa vagonului curent unde se află mecanicul.

Am creat câte o funcție pentru fiecare tip de operație care afectează trenul, și le-am separat după tipul de operație.

### queue.h

```c
typedef struct cell {
    char* cmd;
    struct cell *prev, *next;
} TCell, *TList;
```
este o declarație clasică a unei celule, respectiv liste dublu înlănțuite.

```c
typedef struct queue {
    TList head, tail;
} Queue, *TQueue;
```
reprezintă coada de comenzi cu pointeri la începutul, respectiv, sfârșitul listei de comenzi.

Precum în train.h, am creat câte o funcție pentru fiecare operație referitor la coadă, și le-am separat după tip.

## C files

### train.c

Conține implementarea tuturor funcțiilor declarate în train.h, fiecare având un nume sugestiv și un comentariu care descrie pe scurt ce realizează funcția (a se vedea în train.c). Funcțiile au ca parametru trenul, fiindcă am nevoide și de adresa locomotivei pentru realizarea unor condiții. Funcțiile care pot afișa ceva primesc ca parametru și fișierul de ieșire. Unele funcții mai au un parametru necesar executării comenzii respective.

Consider că funcțiile sunt destul de "straightforward", de aceea nu voi intra în amănunte la majoritatea dintre ele.

În ceea ce privește funcțiile
```c
search()
search_left()
search_right()
```
toate funcționează pe acelaș principiu, singurele diferențe sunt direcția de parcurgere a vagoanelor și punctul de oprire. Am vrut să fac un algoritm nu foarte complicat, însă să fie și cât de cât optim, așa că am ales să merg cu idea de a parcurge fiecare vagon și de a salva inscripția într-un șir "target", care cu ajutorul unei variabile "idx" se realocă dinamic pentru fiecare caracter, și la final adaug un terminator '\0'.

La realloc folosesc (idx + 2) fiindcă am nevoie de spațiu și pentru caracterul curent, și pentru terminatorul care îl voi adăuga la finalul parcurgerii.

Apoi verific dacă șirul "pattern" se află în "target", iar, în caz afirmativ, calculez numărul de pași necesari pentru a muta mecanicul pe poziția cerută la fiecare tip de operație search și execut de atâtea ori mutarea în stânga sau dreapta.

Pentru search() am ales să folosesc tot move_left(), fiindcă are deja implementată verificarea pentru santinelă, pe când la move_right ar adăuga un nou vagon dacă ar ajunge la final, ceea ce nu este de dorit.

De exemplu, pentru conținului trenului "Ana_a|r|e_mere":

target = "re_mereAna_a"

pattern = "na"

found va găsi incluziunea și va returna pointer la "na_a" din target

Printr-o simplă relație matematică calculez numărul de pași la stânga ca diferența dintre lungimea șirului și poziția primului caracter din "pattern" în "target" (este egal cu diferența dintre adrese):

steps = strlen(target) - (found - target) = 12 - 8 = 4

Mutând mecanicul 4 pași la stânga ajungem la "A|n|a_are_mere".

### queue.c

Conține implementarea tutoror funcțiilor declarate în queue.h, fiecare având câte un nume sugestiv și și un comentariu care descrie pe scurt ce realizează funcția (a se vedea în queue.c).

Din nou, funcțiile nu sunt complicate, funcționează pe principii standard de lucru cu o coadă, precum alocare de element, adăugare de element, extragere de element, etc...

Funcția switch_queue() pur și simplu parcurge coada interschimbând legăturile next și prev, după care interschimbă adresele la head și tail.

Funcția execute_command() extrage primul element din coadă, identifică comanda și o execută, apoi actualizează coada și eliberează comanda deja executată. Am folosit strcmp() pentru comenzi fără parametru, și strstr() pentru cele cu parametru. Funcția execute_command() primeste ca parametri trenul și fișierul de ieșire pentru a satisface necesitățile tuturor operațiilor pentru tren.

În ceea ce privește comenzile cu parametru un șir, am identificat care este indexul de unde începe parametrul efectiv după comandă și am transmis funcțiilor respective adresa de început a parametrului.

Pentru funcțiile ce primesc un char ca parametru, de asemenea am identificat poziția, după care am încadrat-o între 0[...] pentru a lua caracterul dorit. Am ales notația
```c
0[aux->cmd + strlen("...")]
```
în loc de
```c
(aux->cmd + strlen("..."))[0]
```
doar din preferință personală.

### tema1.C

Este împărțit pe câteva secțiuni care se ocupă de deschiderea fișierelor I/O, inițializarea structurilor, citirea datelor de intrare, prelucrarea și executarea comenzilor cu ajutorul funcțiilor din queue.c și train.c, eliberarea memoriei rămase și închiderea fișierelor I/O.