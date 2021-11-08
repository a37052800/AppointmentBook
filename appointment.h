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

int searchFromFile(appointment appTemp[])
{
    int dataCount = 0;
    FILE *store = fopen("database", "r");
    if (store == NULL)
    {
        printf("File is NULL");
        return -1;
    }
    char temp[784];
    while ((fgets(temp, 784, store) != NULL) && (dataCount < 255))
    {
        dataCount++;
        char *token = calloc(772, sizeof(char));
        sscanf(temp, "%4d%2d%2d%2d%2d%[^\n]", &appTemp[dataCount - 1].year, &appTemp[dataCount - 1].month, &appTemp[dataCount - 1].day, &appTemp[dataCount - 1].hour, &appTemp[dataCount - 1].minute, token);
        token = strtok(token, "|");
        strncpy(appTemp[dataCount - 1].name, token, sizeof(appTemp[dataCount - 1].name));
        token = strtok(NULL, "|");
        strncpy(appTemp[dataCount - 1].location, token, sizeof(appTemp[dataCount - 1].location));
        token = strtok(NULL, "|");
        strncpy(appTemp[dataCount - 1].event, token, sizeof(appTemp[dataCount - 1].event));
    }
    fclose(store);
    return 0;
}

int storeToFile(appointment *appTemp)
{
    FILE *store = fopen("database", "a+");
    fprintf(store, "%04d", appTemp->year);
    fprintf(store, "%02d", appTemp->month);
    fprintf(store, "%02d", appTemp->day);
    fprintf(store, "%02d", appTemp->hour);
    fprintf(store, "%02d", appTemp->minute);
    fprintf(store, "%s|", appTemp->name);
    fprintf(store, "%s|", appTemp->location);
    fprintf(store, "%s\n", appTemp->event);
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