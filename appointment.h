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
    char buf[256];
    setbuf(stdin, NULL);
    fgets(buf, sizeof(buf), stdin);
    char *token = strtok(buf, "/");
    if (token[0] == 'b')
        return 0;
    else
    {
        appTemp->year = atoi(token);
        token = strtok(NULL, "/");
        appTemp->month = atoi(token);
        token = strtok(NULL, "/");
        appTemp->day = atoi(token);
    }
    return 1;
}

char *toString(appointment *appTemp)
{
    char *reply = calloc(9, sizeof(char));
    reply[8] = '\n';
    reply[7] = (char)(appTemp->day % 10 + 48);
    reply[6] = (char)(appTemp->day / 10 % 10 + 48);
    reply[5] = (char)(appTemp->month % 10 + 48);
    reply[4] = (char)(appTemp->month / 10 % 10 + 48);
    reply[3] = (char)(appTemp->year % 10 + 48);
    reply[2] = (char)((appTemp->year / 10) % 10 + 48);
    reply[1] = (char)((appTemp->year / 100) % 10 + 48);
    reply[0] = (char)((appTemp->year / 1000) % 100 + 48);
    return reply;
}