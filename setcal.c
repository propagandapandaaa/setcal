#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 30
#define INPUT_LEN 256
#define INFO "[LOG-INFO] "

//////////// DEFENICE STRUKTUR ////////////

// Dvoice pro relace
typedef struct couple {
    char first[MAX_LEN];
    char second[MAX_LEN];
} couple;

// Relace
typedef struct relation {
    int id;
    int len;
    struct couple *cpl;
    struct relation *next;
} relation;

// Mnozina
typedef struct set {
    int id;
    int len;
    char **items;
    struct set *next;
} set;


//////////// DEKLARACE FUNKCI ////////////

// Nacte vsechni prvky do univerziumu ze stringu
void processUniverzium();

// Prida mnozinu do relations[]
void addRelation(struct relation);

// Entry point pro prace z relacmi, mela by zavolat addRelation
void processRelation(char *input, int line);

// Entry point pro prace z mnoziny
void processSet(char *input, int line);

set *getSet(int id);
// Entry point pro operace
void processOperation(char *input);

// Nacte string libovolne delky
char *readString(FILE* fp, size_t size, int *line);

///////////// POMOCNE FUNKCE /////////////

//vrací pole prvků relace ze kterých je složena
char *getElements(relation *a){
    char f[a->len][MAX_LEN];
    int h = 0;
    for(int i = 0; i < a->len; i++){
        for(int j = 0; j <= h; j++){
            if(a->cpl[i].first != f[j]){
                strcpy(f[h], a->cpl[i].first);
                h++;
            }
            if(a->cpl[i].second != f[j]){
                strcpy(f[h], a->cpl[i].second);
                h++;
            }
        }
    }
    return f;
}

////////// PRIKAZY NAD MNOZINAMI//////////

//tiskne true nebo false podle toho, jestli je množina definovaná na řádku A prázdná nebo neprázdná.
void empty(set *a){
    if(a->items[0] == NULL)
        printf("Set is empty: true\n");
    else
        printf("Set is empty: false\n");
}

//tiskne počet prvků v množině A (definované na řádku A).
void card(set *a){
    int i = 0;
    while(a->items[i] == '\0'){
        i++;
    }
    i++;
    printf("Number of elements is: %d\n", i);
}

//tiskne doplněk množiny A
void complement(set *a) {
    char *compl;
    int count = 0;

    for(int i = 0; i < strlen(univerzium); i++) {
        for(int j = 0; j < a->len; j++){
            if(strcmp(a->items[i], univerzium[j]) != 0) {
                count++; 
            } else if(strcmp(a->items[i], univerzium[j])) == 0) {
                count = 0;
                break;
            }
        }
        if(count > 0) {
                strcat(compl, univerzium[i]);
            }
    }
    printf("Complement is: %s\n", compl);
}

//tiskne sjednonecí monžin A a B
void union(set *a, set *b) {
    char *u = getElements(a);
    int count = 0;

    for(int i = 0; i < a->len; i++) {
        for(int j = 0; j < b->len; j++)
            if(strcmp(a->items[j], b->items[i]) !=0) {
                count++;
        } else if(strcmp(a->items[j], b->items[i]) == 0) {
                count = 0;
                break;
        }
    }
    if(count > 0) {
        strcat(u, b->items[i]);
    }
    printf("Union is: %s\n", u)
}

////////// PRIKAZY NAD RELACEMI //////////

//tiskne true nebo false, jestli je relace reflexivní.
bool reflexive(relation *a){
    char *f = getElements(a);
    for(int i = 0; i < a->len; i++){
        if(a->cpl[i].first == a->cpl[i].second){
            for(int j = 0; i < a->len; j++){
                if(f[j] == a->cpl[i].first){
                    f[j] = NULL;
                    break;
                }
            }
        }
    }
    for(int i = 0; i < a->len; i++){
        if(f[i] != NULL || f[i] != '\0')
            printf("Relation is reflexive: false\n");
            return false;
    }
    printf("Relation is reflexive: true\n");
    return true;
}

//tiskne true nebo false, jestli je relace symetrická.
bool symmetric(relation *a){
    int f = 0;
    for(int i = 0; i < a->len; i++){
        if(a->cpl[i].first != a->cpl[i].second){
            for(int j = 0; j < a->len; j++){
                if(a->cpl[i].first == a->cpl[j].second && a->cpl[i].second == a->cpl[j].first){
                    f = 1;
                    break;
                }
            }
        }
        if(f == 0){
            printf("Relation is symmetric: false\n");
            return false;
        }
        f = 0;
    }
    printf("Relation is symmetric: true\n");
    return true;
}

//tiskne true nebo false, jestli je relace antisymetrická.
void antisymmetric(relation *a) {
    int t = 0;
    for(int i = 0; i < a->len; i++) {
        if(a->cpl[i].first != a->cpl[i].second) {
            for(int j = 0; j < a->len; j++) {
                if(a->cpl[i].second == a->cpl[j].first && a->cpl[i].first == a->cpl[j].second) {
                    t++;
                    break;
                }
            }
        }
    }
    if(t == 0) {
        printf("Relation is antisymmetric: true\n");
    } else if(t > 0){
        printf("Relation is antisymmetric: false\n");
    }
}

//tiskne true nebo false, jestli je relace tranzitivní.
void transitive() {
    int t = 0;
    for(int i = 0; i < a->len; i++) {
        if(a->cpl[i].first != a->cpl[i].second) {
            for(int j = 1; j < a->len; j++) {
                for(int k = 2; k < a->len; k++) {
                    if(a->cpl[i].second == a->cpl[j].first && 
                       a->cpl[i].first == a->cpl[k].first && 
                       a->cpl[i].second == a->cpl[k].second) {
                        t++;
                        break;
                    }
                }
            }
        } else if(a->cpl[i].first == a->cpl[i].second) {
            for(int j = 1; j < a->len; j++) {
                if(a->cpl[i].second == a->cpl[j].first) {
                    t++;
                    break;
            }
        }
    }
        if(t == 0) {
            printf("Relation is transitive: false\n");
        } else if(t > 0){
            printf("Relation is transitive: true\n");
        }
    }
}

//tiskne true nebo false podle toho zda se mnoziny rovnaji nebo ne
bool equals(set *a, set *b)
{
    if(a->len != b->len)
    {
        printf("Sets are equal: false");
        return true;
    } 
    for(int i = 0; i < a->len; i++)
    {
        if(a->items[i] != b->items[i])
        {
        printf("Sets are equal: false");
        return false;
        }
    }
    printf("Sets are equal: true");
}

//Vrati true jestli ke kazdemu prvku z mnoziny b je mozne priradit prvek z mnoziny a 
bool surjective(set *a, set *b) {

    if(b->len <= a->len)
    {
        printf("Function is surjective: true\n");
        return true;
    }
    else
    {
        printf("Function is surjective: false\n");
        return false;
    }

}

//Vrati true jestli ke kazdemu prvku z mnoziny a je mozne priradit prvek z mnoziny b
bool injective(set *a, set *b)
{
    if(a->len <= b->len)
    {
        printf("Function is surjective: true\n");
        return true;
    }
    else
    {
        printf("Function is surjective: false\n");
        return false;
    }
}


//fce bijektivni
bool bijective(set *a, set *b)
{
    if(surjective(a, b) == true && injective(a, b) == true)
    {
        printf("Function is bijective: true\n");
        return true;
    }
    else
    {
        printf("Function is bijective: false\n");
        return false;
    }
}

//////////// GLOBALNI PROMENNE////////////


char *univerzium;
struct set *firstSet = NULL;
struct set *lastSet = NULL;
struct relation *firstRelation = NULL;
struct relation *lastRelation = NULL;


int main (int argc, char *argv[]) {
    FILE *file;
    int lineNumber = 0;
    char operation;
// Odkomentovane, pro testovani pouzita hard-coded cesta
//    if(argc < 2) {
//        fprintf(stderr, "No file selected");
//    }
//    if(argc > 2) {
//        fprintf(stderr, "Too many arguments");
//    }
//    char fileName = argv[1];
    file = fopen("./samples/basic.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist");
    }
    // Nacist univerzium
    univerzium = readString(file, INPUT_LEN, &lineNumber);
    processUniverzium();

    // Nacteme mnoziny a relace
    char *inputString;
    while (true) {
        inputString = readString(file, INPUT_LEN, &lineNumber);
        // Jestli radek je prazdny, to je konec souboru
        if (strlen(inputString) == 0) {
            exit(0);
        }
        // Ulozim operace a zbavim se z ni v stringu
        operation = inputString[0];
        inputString += 2;
        // Jestli to neni mnozina ani relace, pokracujeme na provedeni operaci
        if (operation != 'S' && operation != 'R') {
            break;
        }
        // Provedeme nacteni mnoziny nebo relace
        if (operation == 'S') {
            processSet(inputString, lineNumber);
        } else {
            processRelation(inputString, lineNumber);
        }
    }

    // Provedeme operace
    while (strlen(inputString) == 0) {
        processOperation(inputString);
        readString(file, INPUT_LEN, &lineNumber);
    }
}

char *readString(FILE *fp, size_t size, int *line) {
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str) * size);
    if (!str) {
        printf("Error allocating memory, exiting program\n");
        exit(1);
    }
    while(EOF != (ch = fgetc(fp)) && ch != '\n'){
        str[len++] = ch;
        if (len == size) {
            str = realloc(str, sizeof(*str) * (size += 16));
            if (!str) {
                printf("Error allocating memory, exiting program\n");
                exit(1);
            }
        }
    }
    str[len++]='\0';
    char operation = str[0];
    switch (operation) {
        case 'U':
        case 'S':
        case 'R':
        case 'C':
            break;
        default:
            printf("Unknown operation: operation {%c} is not supported, exiting program\n", operation);
            exit(1);
    }
    *line += 1;
    return realloc(str, sizeof(*str)*len);
}


void processUniverzium() {
    if (univerzium[0] != 'U') {
        printf("Spatny format pro univerzium\n");
        exit(1);
    }
    processSet(univerzium, 1);
    univerzium += 2;
}

void processSet(char *input, int line) {
    // Na zacatku zkontrolujeme jestli vsechny prvku jsou v univerziu,i a zjistime velikost mnoziny
    int setSize = 0;
    // Potrebujeme kopii inputu, protoze strtok zmeni puvodni string
    char *inputCopy = malloc(strlen(input) * sizeof(char));
    strcpy(inputCopy, input);
    char *setEntry = strtok(inputCopy, " ");
    while(setEntry != NULL) {
        if (strlen(setEntry) > MAX_LEN) {
            printf("Set entry exceeds length of 30 characters, exiting\n");
            exit(1);
        }
        if ((strstr(univerzium, setEntry) == NULL) && line != 1) {
            printf("Set entry {%s} does not exist in univerzium, exiting\n", setEntry);
            exit(1);
        }
        setSize++;
        setEntry = strtok(NULL, " ");
    }
    // Alokujeme pamet pro prvky mnoziny a vlzozime tyto prvky
    char **setEntries = malloc(setSize * sizeof(char *));
    strcpy(inputCopy, input);
    setEntry = strtok(inputCopy, " ");
    for (int i = 0; i < setSize; ++i) {
        setEntries[i] = (char *) malloc (MAX_LEN);
        strcpy(setEntries[i], setEntry);
    }
    // Vytvorime novy set
    set *currentSet;
    currentSet = malloc(sizeof(set));
    currentSet->id = line;
    currentSet->len = setSize;
    currentSet->items = setEntries;
    currentSet->next = NULL;
    // Jestli firstSet == NULL, jedna se o prvni set v programu, v opacnem pripade potrebujeme zmenit odkazy
    if (firstSet == NULL) {
        firstSet = currentSet;
        lastSet = currentSet;
    } else {
        lastSet->next = currentSet;
        lastSet = currentSet;
    }
    free(inputCopy);
}

set *getSet(int id) {
    if (firstSet == NULL) {
        printf("Get set was called when no set was read, exiting\n");
        exit(1);
    }
    struct set *currentSet = firstSet;
    while (true) {
        if (currentSet->id == id) {
            return currentSet;
        }
        if (currentSet->next == NULL) {
            printf("Set with id {%d} does not exist, exiting\n");
        }
        currentSet = currentSet->next;
    }
}

void processRelation(char *input, int line) {

}

void processOperation(char *input) {

}
