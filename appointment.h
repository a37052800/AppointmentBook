#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct appointment
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    char event[256];
    char name[256];
    char location[256];
} appointment;

int Add(appointment *appTemp)
{
    char buf[256];
    setbuf(stdin, NULL);
    printf("Please enter the date(yyyy/mm/dd):");
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
    if ((appTemp->year == 0) || (appTemp->month == 0) || (appTemp->day == 0))
        return 0;
    setbuf(stdin, NULL);
    printf("Please enter the 24-h time(hh:mm):");
    fgets(buf, sizeof(buf), stdin);
    token = strtok(buf, ":");
    if (token[0] == 'b')
        return 0;
    else
    {
        appTemp->hour = atoi(token);
        token = strtok(NULL, ":");
        appTemp->minute = atoi(token);
    }
    setbuf(stdin, NULL);
    printf("Please enter name:");
    fgets(buf, sizeof(buf), stdin);
    if (buf[strlen(buf) - 1] == '\n')
        buf[strlen(buf) - 1] = '\0';
    strncpy(appTemp->name, buf, sizeof(appTemp->name));
    setbuf(stdin, NULL);
    printf("Please enter loaction:");
    fgets(buf, sizeof(buf), stdin);
    if (buf[strlen(buf) - 1] == '\n')
        buf[strlen(buf) - 1] = '\0';
    strncpy(appTemp->location, buf, sizeof(appTemp->location));
    setbuf(stdin, NULL);
    printf("Please enter event:");
    fgets(buf, sizeof(buf), stdin);
    if (buf[strlen(buf) - 1] == '\n')
        buf[strlen(buf) - 1] = '\0';
    strncpy(appTemp->event, buf, sizeof(appTemp->event));
    
    return 1;
}

int storeToFile(appointment *appTemp)
{
    FILE *store = fopen("database", "a+");
    char *temp = calloc(256, sizeof(char));
    itoa(appTemp->year, temp, 10);
    fputs(temp, store);
    itoa(appTemp->month, temp, 10);
    fputs(temp, store);
    itoa(appTemp->day, temp, 10);
    fputs(temp, store);
    itoa(appTemp->minute, temp, 10);
    fputs(temp, store);
    itoa(appTemp->hour, temp, 10);
    fputs(temp, store);
    fputs(appTemp->name, store);
    fputs(appTemp->location, store);
    fputs(appTemp->event, store);
    fclose(store);
    return 0;
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