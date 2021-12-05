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

// Vraci mnozinu s prislusnym id
set *getSet(int id);

// Vraci relace s prislusnym id
relation *getRelation(int id);

// Entry point pro operace
void processOperation(char *input);

// Nacte string libovolne delky
char *readString(FILE* fp, size_t size, int *line);

int readNumber();

void traverseSet();

void traverseRelation();

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

/tiskne doplněk množiny A
void complement(set *a) {
    extern char *univerzium;
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
            if(compl[0] == '\0') {
                strcpy(compl, univerzium[i]);
            } else {
                strcat(compl, univerzium[i]);
            }
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

//tiskne průnik množin A a B
void intersect(set *a,set *b)
{
    for(int i=0;i<a->len;i++)
    {
        for(int j=0;j<b->len;j++)
        {
            if(a->items[i]!=b->items[j])
            {
                for(int k=i;k<a->len-1;k++)
                {
                    a->items[i]=a->items[i+1];
                }
                realloc(a, sizeof(a));
            }            
        }
    }
    for(int l = 0; l < a->len; l++)
    {
        printf("Intersection of sets is : %s",a->items[l]);
    }
}

//tiskne rozdíl množin A \ B
void minus(set *a,set *b)
{
    for(int i=0;i<a->len;i++)
    {
        for(int j=0;j<b->len;j++)
        {
            if(a->items[i]==b->items[j])
            {
                for(int k=i;k<a->len-1;k++)
                {
                    a->items[i]=a->items[i+1];
                }
                realloc(a, sizeof(a));
            }            
        }
    }
    for(int l = 0; l < a->len; l++)
    {
        printf("Difference of sets is : %s",a->items[l]);
    }

}

//tiskne true nebo false podle toho, jestli je množina A podmnožinou množiny B
void subseteq(set *a, set *b){
    bool f = false;
    for(int i = 0; i < a->len; i++){
        for(int j = 0; j < b->len; j++){
            if(a->items[i] == b->items[j])
                f = true;
        }
        if(f == false){
            printf("Set A is subset of B: flase\n");
            return;
        }
        f = false;
    }
    printf("Set A is subset of B: true\n");
}

//tiskne true nebo false, jestli je množina A vlastní podmnožina množiny B
void subset(set *a, set *b){
    if(a->len == b->len){
        printf("Set A is ownsubset of B: false\n");
        return;
    }
    bool f = false;
    for(int i = 0; i < a->len; i++){
        for(int j = 0; j < b->len; j++){
            if(a->items[i] == b->items[j])
                f = true;
        }
        if(f == false){
            printf("Set A is ownsubset of B: flase\n");
            return;
        }
        f = false;
    }
    printf("Set A is ownsubset of B: true\n");
}

//tiskne true nebo false, jestli jsou množiny rovny
bool equals(set *a, set *b)
{
    if(a->len != b->len)
    {
        printf("Sets are equal: false\n");
        return true;
    } 
    for(int i = 0; i < a->len; i++)
    {
        if(a->items[i] != b->items[i])
        {
        printf("Sets are equal: false\n");
        return false;
        }
    }
    printf("Sets are equal: true\n");
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

//tiskne definiční obor funkce R (lze aplikovat i na relace - první prvky dvojic)
void domain(relation *a){
    printf("D(f): {%s", a->cpl[0].first);
    for (int i = 1; i < a->len; i++){
        printf(", %s", a->cpl[i].first);
    }
    printf("}\n");
}

//tiskne obor hodnot funkce R (lze aplikovat i na relace - druhé prvky dvojic)
void codomain(relation *a){
    printf("H(f): {%s", a->cpl[0].second);
    for (int i = 1; i < a->len; i++){
        printf(", %s", a->cpl[i].second);
    }
    printf("}\n");
}

//tiskne true nebo false, jestli je funkce R injektivní. A a B jsou množiny; a∈A, b∈B, (a,b)∈R
bool injective(set *a, set *b, relation *r){

    //kontroluje zda ke kazdemu prvku A je prirazeny alespon jeden prvek B 
    for(int i = 0; i < a->len; i++){
        int count = 0;
        for(int j = 0; j < r->len; j++){
            if(a->items[i] == r->cpl[j].first){
                count = count + 1;
            }
        }
        if(count != a->len){
            printf("Function is injective: false\n");
            return false;
        }
     }
    if(a->len <= b->len){
        int img;
        //Kontroluje zda se nevyskytuje druhy prvek v relacich vice nez jednou
        for(int i = 0; i < b->len; i++){
            img = 0;   
                for (int j = i + 1; j < b->len; j++){
                    if(r->cpl[i].second == r->cpl[j].second){
                        printf("Function is injective: false\n");
                        return false;
                    }
                }
            }
        printf("Function is injective: true\n");
        return true;
    }
    else{
    printf("Function is injective: false\n");
    return false;
    }
}

//tiskne true nebo false, jestli je funkce R surjektivní. A a B jsou množiny; a∈A, b∈B, (a,b)∈R
bool surjective(set *a, set *b, relation *r) {
    for(int i = 0; i < b->len; i++)
    {
        int img = 0;
        for(int j = i + 1; j < b->len; j++){
            if(b->items[i] == r->cpl[j].second){
                img++;
            }
        }
        if(img < 1){
            printf("Relation is surjective: false\n");
            return false;
        }
    }
    printf("Relation is surjective: true\n");
    return true;
}

//tiskne true nebo false, jestli je funkce R bijektivní. A a B jsou množiny; a∈A, b∈B, (a,b)∈R
bool bijective(set *a, set *b, relation *r){
    if(a->len != b->len){
        printf("Function is bijective: false\n");
        return false;
    }
    if(surjective(a, b, r) == true && injective(a, b, r) == true){
        printf("Function is bijective: true\n");
        return true;
    }
    else{
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
        printf("Wrong format for univerzium, exiting\n");
        exit(1);
    }
    univerzium += 2;
    processSet(univerzium, 1);
}

void processSet(char *input, int line) {
    input += 2;
    // Na zacatku zkontrolujeme jestli vsechny prvku jsou v univerziu a zjistime velikost mnoziny
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
        setEntry = strtok(NULL, " ");
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
            exit(1);
        }
        currentSet = currentSet->next;
    }
}

void processRelation(char *input, int line) {
    input += 2;
    // Na zacatku zkontrolujeme jestli vsechny prvku jsou v univerziu a zjistime kolik je dvojic v relaci
    int totalEntries = 0;
    // Potrebujeme kopii inputu, protoze strtok zmeni puvodni string
    char *inputCopy = malloc(strlen(input) * sizeof(char));
    strcpy(inputCopy, input);
    char *relationEntry = strtok(inputCopy, " ");
    while(relationEntry != NULL) {
        if (strlen(relationEntry) > MAX_LEN + 1) {
            printf("Set entry exceeds length of 30 characters, exiting\n");
            exit(1);
        }
        // Nasledujici blok kodu se zbavi ze zavorek a vypise chybu kdyz zavorky nejsou
        if ((totalEntries % 2 == 0) && relationEntry[0] == '(') {
            relationEntry++;
        } else if ((totalEntries % 2 == 1) && relationEntry[strlen(relationEntry) - 1] == ')') {
            relationEntry[strlen(relationEntry) - 1] = '\0';
        } else {
            printf("Wrong format for relation, exiting\n");
            exit(1);
        }
        if ((strstr(univerzium, relationEntry) == NULL) && line != 1) {
            exit(1);
        }
        totalEntries++;
        relationEntry = strtok(NULL, " ");
    }
    if (totalEntries % 2) {
        printf("Wrong format for relation, exiting\n");
        exit(1);
    }
    // Alokujeme pamet pro dvojici relaci a vlzozime tyto dvojici
    couple *couples = malloc(totalEntries / 2 * sizeof(couple));
    strcpy(inputCopy, input);
    relationEntry = strtok(inputCopy, " ");
    for (int i = 0; i < totalEntries; i++) {
        if (i % 2 == 0) {
            relationEntry++;
            strcpy(couples[i / 2].first, relationEntry);
        } else {
            relationEntry[strlen(relationEntry) - 1] = '\0';
            strcpy(couples[i / 2].second, relationEntry);
        }
        relationEntry = strtok(NULL, " ");
    }
    // Vytvorime novou relace
    relation *currentRelation;
    currentRelation = malloc(sizeof(relation));
    currentRelation->id = line;
    currentRelation->len = totalEntries / 2;
    currentRelation->cpl = couples;
    currentRelation->next = NULL;
    // Jestli firstRelation == NULL, jedna se o prvni relace v programu, v opacnem pripade potrebujeme zmenit odkazy
    if (firstRelation == NULL) {
        firstRelation = currentRelation;
        lastRelation = currentRelation;
    } else {
        lastRelation->next = currentRelation;
        lastRelation = currentRelation;
    }
    free(inputCopy);
}

relation *getRelation(int id) {
    if (firstRelation == NULL) {
        printf("Get relation was called when no relation was read, exiting\n");
        exit(1);
    }
    struct relation *currentRelation = firstRelation;
    while (true) {
        if (currentRelation->id == id) {
            return currentRelation;
        }
        if (currentRelation->next == NULL) {
            printf("Relation with id {%d} does not exist, exiting\n");
            exit(1);
        }
        currentRelation = currentRelation->next;
    }
}

void traverseSet() {
    if (firstSet == NULL) {
        printf("Get relation was called when no relation was read, exiting\n");
        exit(1);
    }
    struct set *currentSet = firstSet;
    while (true) {
        printf("Current set: {%d}, len {%d}\n", currentSet->id, currentSet->len);
        printf("\tSet entries:\n");
        for (int i = 0; i < currentSet->len; ++i) {
            printf("\t\t{%s}\n", currentSet->items[i]);
        }
        if (currentSet->next == NULL) {
            break;
        }
        currentSet = currentSet->next;
    }
}

void traverseRelation() {
    if (firstSet == NULL) {
        printf("Get relation was called when no relation was read, exiting\n");
        exit(1);
    }
    struct relation *currentRelation = firstRelation;
    while (true) {
        printf("Current Relation: {%d}, len {%d}\n", currentRelation->id, currentRelation->len);
        printf("\tRelation entries:\n");
        for (int i = 0; i < currentRelation->len; ++i) {
            printf("\t\t({%s} {%s})\n", currentRelation->cpl[i].first, currentRelation->cpl[i].second);
        }
        if (currentRelation->next == NULL) {
            break;
        }
        currentRelation = currentRelation->next;
    }
}

void processOperation(char *input) {
    set *A;
    set *B;
    relation *R;
    if (input[0] != 'C') {
        printf("Every command must start with \"C\", exiting\n");
        exit(1);
    }
    input += 2;
    char *command = strtok(input, " ");
    if (strcmp(command, "empty") == 0) {
        A = getSet(readNumber());
        empty(A);
    } else if (strcmp(command, "card") == 0) {
        A = getSet(readNumber());
        card(A);
    } else if (strcmp(command,  "complement") == 0) {
        A = getSet(readNumber());
        // complement(A);
    } else if (strcmp(command,  "union") == 0) {
        A = getSet(readNumber());
        B = getSet(readNumber());
        // union(A,B);
    } else if (strcmp(command,  "intersect") == 0) {
        A = getSet(readNumber());
        B = getSet(readNumber());
//      intersect(A, B);
    } else if (strcmp(command,  "minus") == 0) {
        A = getSet(readNumber());
        B = getSet(readNumber());
//      minus(A, B);
    } else if (strcmp(command,  "subseteq") == 0) {
        A = getSet(readNumber());
        B = getSet(readNumber());
        subseteq(A, B);
    } else if (strcmp(command,  "subset") == 0) {
        A = getSet(readNumber());
        B = getSet(readNumber());
        subset(A, B);
    } else if (strcmp(command,  "equals") == 0) {
        A = getSet(readNumber());
        B = getSet(readNumber());
        equals(A, B);
    } else if (strcmp(command,  "reflexive") == 0) {
        R = getRelation(readNumber());
        reflexive(R);
    } else if (strcmp(command,  "symmetric") == 0) {
        R = getRelation(readNumber());
        symmetric(R);
    } else if (strcmp(command,  "antisymmetric") == 0) {
        R = getRelation(readNumber());
//      antisymmetric(R);
    } else if (strcmp(command,  "transitive") == 0) {
        R = getRelation(readNumber());
//      transitive(R);
    } else if (strcmp(command,  "function") == 0) {
        R = getRelation(readNumber());
//      function(R);
    } else if (strcmp(command,  "domain") == 0) {
        R = getRelation(readNumber());
//      domain(R);
    } else if (strcmp(command,  "codomain") == 0) {
        R = getRelation(readNumber());
//      codomain(R);
    } else if (strcmp(command,  "injective") == 0) {
        R = getRelation(readNumber());
        A = getSet(readNumber());
        B = getSet(readNumber());
        injective(A, B, R);
    } else if (strcmp(command,  "surjective") == 0) {
        R = getRelation(readNumber());
        A = getSet(readNumber());
        B = getSet(readNumber());
        surjective(A, B, R);
    } else if (strcmp(command,  "bijective") == 0) {
        R = getRelation(readNumber());
        A = getSet(readNumber());
        B = getSet(readNumber());
        bijective(A, B, R);
    } else {
        printf("Operation {$s} is undefined, exiting\n");
        exit(1);
    }
}

int readNumber() {
    char *number = strtok(NULL, " ");
    if (number == NULL) {
        printf("Operation argument is missing, exiting\n");
        exit(1);
    }
    return atoi(number);
}
