#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//when what who where
typedef struct appointment
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    char *event;
    char *name;
    char *location;
} appointment;

int Add(appointment *appTemp)
{
    char buf[10];
    fgets(buf, sizeof(buf), stdin);
    char *token = strtok(buf, "/");
    if (token[0] == 'b')
        return 0;
    else
    {
        appTemp->year = atoi(token);
    }
    return 1;
}