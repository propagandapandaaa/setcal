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
    struct couple cpl[];
} relation;

// Mnozina
typedef struct set {
    int id;
    char item[][MAX_LEN];
} set;

//////////// DEKLARACE FUNKCI ////////////

// Nacte vsechni prvky do univerziumu ze stringu
void processUniverzium();

// Prida mnozinu do sets[]
void addSet(struct set);

// Prida mnozinu do relations[]
void addRelation(struct relation);

// Entry point pro prace z relacmi, mela by zavolat addRelation
void processRelation(char *input);

// Entry point pro prace z mnoziny, mela by zavolat addSet
void processSet(char *input);

// Nacte string libovolne delky
char *readString(FILE* fp, size_t size);

//////////// GLOBALNI PROMENNE////////////

// Vstupni soubor
FILE *file;

char *univerzium;
struct set *sets;
struct relation *relations;

int main (int argc, char *argv[]) {
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
    univerzium = readString(file, INPUT_LEN);
    processUniverzium();

    // Nacteme mnoziny a relace
    char *string;
    while (true) {
        string = readString(file, INPUT_LEN);
        if (strlen(string) == 0) {
            printf(INFO"Konec souboru\n");
            exit(1);
        } else if ( string[0] != 'S' && string[0] != 'R') {
            printf(INFO"Konec mnozin a relaci");
            break;
        }
        printf(INFO"String: %s\n", string);
    }

    // Provedeme operace


}

char *readString(FILE *fp, size_t size) {
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str) * size);
    if (!str) {
        return NULL;
    }
    while(EOF != (ch = fgetc(fp)) && ch != '\n'){
        str[len++] = ch;
        if (len == size) {
            str = realloc(str, sizeof(*str) * (size += 16));
            if (!str) {
                return NULL;
            }
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(*str)*len);
}

void processUniverzium() {
    if (univerzium[0] != 'U') {
        printf("Spatny format pro univerzium\n");
        exit(1);
    }
    univerzium += 2;
    printf(INFO"Univerzium: {%s}\n", univerzium);
}