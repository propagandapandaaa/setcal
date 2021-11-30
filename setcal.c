#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 30

/*
typedef struct
{
    char *elements;
    int cardinality;
} universe; //Data type for universe (maybe merge it with set data type, its the same)
*/

typedef struct {
    int size;
    char line;
} lineData;

char[] univerzium;

// Dvoice pro relace
typedef struct couple {
    char[MAX_LEN] first;
    char[MAX_LEN] second;
};

// Relace
typedef struct relation {
    int id;
    struct couple[] cpl;
};

// Mnozina
typedef struct set {
    int id;
    char[][MAX_LEN] item;
};

struct sets[999];
struct relations[999];

// Nacte vsechni prvky do univerziumu ze str
void readUniverzium(char *str);

// Prida mnozinu do sets[]
void addSet(struct set);

// Prida mnozinu do relations[]
void addRelation(struct relation);

// Entry point pro prace z relacmi, mela by zavolat addRelation
void processRelation(char *input);

// Entry point pro prace z mnoziny, mela by zavolat addSet
void processSet(char *input);


void lineConstruct(lineData *line, char *buffer, int size) {
      line->size = size;
      line->line = malloc(strlen(*buffer));
      strcpy(line->line, *buffer);
}

int main (int argc, char *argv[]) {
    if(argc < 2) {
        fprintf(stderr, "No file selected");
    }
    if(argc > 2) {
        fprintf(stderr, "Too many arguments");
    }
    char fileName = argv[1];

    FILE *file;
    file = fopen("./fileName", "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist");
    }


    char *buffer;
    int size = 0;
    int i = 0;

    // Nacist univerzium

    // Nacteme relace
    while(getline(&buffer, &size, file) != EOF) {
        lineData line[];
        lineConstruct(&line[], &buffer, size);

    }

    // Provedeme operace
    while(getline(&buffer, &size, file) != EOF) {
        lineData line[];
        lineConstruct(&line[], &buffer, size);

    }

}
//cdghxdfyxdfgh