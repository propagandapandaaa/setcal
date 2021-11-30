#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 30 //Maximum lenght of a string
#define KEY 0 //Position of line commands and specifications
/*

//Structure for relations, will contain two elements
typedef struct
{
    char *first;
    char *second; 
} relation;

//Structure for line data, will contain relations or set elements
typedef struct
{
    unsigned lenght;
    char *relations;
} lineData;

//Function to create relations
void relCreate(relation *r, char *first, char *second)
{
    r->first = malloc(strlen(first)+1);
    r->second = malloc(strlen(second)+1);
    strcpy(r->first, first);
    strcpy(r->second, second);
}

//Creates an empty lineData structure, line size can be later increased
void lineCreate(lineData *line)
{
    line->lenght = 0;
    line->relations = NULL;
}

//Increases lineData lenght
void *lineIncrease(lineData *line)
{
    
}
*/

int main(/*int argc, char *argv[]*/)
{
    /*
    if(argc < 2) 
    {
        fprintf(stderr, "No file selected");
    }
    if(argc > 2) 
    {
        fprintf(stderr, "Too many arguments");
    }
    char fileName = argv[1];
    */
    FILE *file;
    
    //Checks if the file exists
    file = fopen("./testfile", "r");
    if (file == NULL) 
    {
        fprintf(stderr, "File does not exist");
    }



    char charBuffer[30] = {}; //Buffer for words
    char *lineBuffer = NULL; //Buffer for lines from the input file

    size_t size = 0; //Size of line, function getline modifies this variable
    int j = 0;

    //Function getline allocates and reallocates memory according to the line lenght
    //Deallocation has to be done manually 
    while (getline(&lineBuffer, &size, file) != EOF)
    {
        char command = lineBuffer[0]; //For better code readability

        //Checks if command is valid
        if(command != 'U' && command != 'S' && command != 'R')
        {
            fprintf(stderr, "Invalid input command\n");
        }

        //Separate input processing for each command
        if(command == 'U')
        {
            printf("Universe\n");
        }

        if(command == 'S')
        {
            printf("Set\n");
            for(int i = 0; lineBuffer[i] != '\n'; i++)
            {
                if(lineBuffer[i] == '(')
                {

                }
            }
        }

        if(command == 'R')
        {
            printf("Relation\n");
        }
    }
    
  
    fclose(file);
    free(lineBuffer); //Manually freeing the memory allocated by the getline function
}