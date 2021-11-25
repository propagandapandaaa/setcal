#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


/*
typedef struct
{
    char *elements;
    int cardinality;
} universe; //Data type for universe (maybe merge it with set data type, its the same)
*/

typedef struct
{
    int size;
    char line;
} lineData;


void lineConstruct(lineData *line, char *buffer, int size, int count)
{
      line->size = size;
      line->line = malloc(strlen(*buffer));
      strcpy(line->line, *buffer);   

}

int main (int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "No file selected");
    }
    if(argc > 2)
    {
        fprintf(stderr, "Too many arguments");
    }
    char fileName = argv[1];

    FILE *file;
    file = fopen("./fileName", "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist");
    }


    char *buffer;
    int size = 0;
    int i = 0;

    while(getline(&buffer, &size, file) != EOF)
    {
        lineData line[i];
        lineConstruct(&line[i], &buffer, size, i);

    }

}
