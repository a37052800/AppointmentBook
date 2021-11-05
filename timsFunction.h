#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int storeToFile(char* content);

int storeToFile(char* content)
{
    FILE *store = fopen("database", "a+");
    fputs(content, store);
    fclose(store);
    return 0;
}