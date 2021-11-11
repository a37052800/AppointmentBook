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

int Verify(appointment *appTemp);
int Delete(appointment *appTemp);
int Modify(appointment *appTemp);
int Ceate(appointment *appTemp);
int searchFromFile(appointment result[], appointment *key);
int storeToFile(appointment *appTemp);
char *toString(appointment *appTemp);

int Verify(appointment *appTemp)
{
    if ((appTemp->year == 0) || (appTemp->month == 0) || (appTemp->day == 0))
        return -1;
    if ((appTemp->hour < 0) || (appTemp->hour > 59) || (appTemp->minute < 0) || (appTemp->minute > 59))
        return -1;
    if ((strlen(appTemp->name) > 0) || (strlen(appTemp->location) > 0) || (strlen(appTemp->event) > 0))
        return -1;
    return 1;
}

int Delete(appointment *appTemp)
{
    FILE *store = fopen("database", "r");
    FILE *delete = fopen("delete", "w");
    if (store == NULL)
    {
        printf("File is NULL");
        return -1;
    }
    char temp[784];
    while (fgets(temp, 784, store) != NULL)
    {
        int yearTemp, monthTemp, dayTemp, hourTemp, minuteTemp;
        sscanf(temp, "%4d%2d%2d%2d%2d", &yearTemp, &monthTemp, &dayTemp, &hourTemp, &minuteTemp);
        if ((appTemp->year != yearTemp) || (appTemp->month != monthTemp) || (appTemp->day != dayTemp) || (appTemp->hour != hourTemp) || (appTemp->minute != minuteTemp))
        {
            fputs(temp, delete);
        }
    }
    fclose(store);
    fclose(delete);
    remove("database");
    rename("delete", "database");
    return 0;
}

int Modify(appointment *appTemp)
{
    Delete(appTemp);
    printf("Original date:%04d/%02d/%02d\n", appTemp->year, appTemp->month, appTemp->day);
    printf("Modify date(yyyy/mm/dd):");
    char buf[256];
    setbuf(stdin, NULL);
    fgets(buf, sizeof(buf), stdin);
    char *token = strtok(buf, "/");
    if (token[0] == 'b')
        return 0;
    else if (token[0] != 's')
    {
        appTemp->year = atoi(token);
        token = strtok(NULL, "/");
        appTemp->month = atoi(token);
        token = strtok(NULL, "/");
        appTemp->day = atoi(token);
    }
    printf("Original time:%02d:%02d\n", appTemp->hour, appTemp->minute);
    printf("Modify time(hh:mm):");
    setbuf(stdin, NULL);
    fgets(buf, sizeof(buf), stdin);
    token = strtok(buf, ":");
    if (token[0] == 'b')
        return 0;
    else if (token[0] != 's')
    {
        appTemp->hour = atoi(token);
        token = strtok(NULL, ":");
        appTemp->minute = atoi(token);
    }
    printf("Original name:%s\n", appTemp->name);
    printf("Modify name:");
    setbuf(stdin, NULL);
    fgets(buf, sizeof(buf), stdin);
    if (buf[strlen(buf) - 1] == '\n')
        buf[strlen(buf) - 1] = '\0';
    if ((strlen(buf) == 1) && (buf[0] == 'b'))
        return 0;
    else if ((strlen(buf) != 1) || (buf[0] != 's'))
        strncpy(appTemp->name, buf, sizeof(appTemp->name));
    printf("Original location:%s\n", appTemp->location);
    printf("Modify location:");
    setbuf(stdin, NULL);
    fgets(buf, sizeof(buf), stdin);
    if (buf[strlen(buf) - 1] == '\n')
        buf[strlen(buf) - 1] = '\0';
    if ((strlen(buf) == 1) && (buf[0] == 'b'))
        return 0;
    else if ((strlen(buf) != 1) || (buf[0] != 's'))
        strncpy(appTemp->location, buf, sizeof(appTemp->location));
    printf("Original event:%s\n", appTemp->event);
    printf("Modify event:");
    setbuf(stdin, NULL);
    fgets(buf, sizeof(buf), stdin);
    if (buf[strlen(buf) - 1] == '\n')
        buf[strlen(buf) - 1] = '\0';
    if ((strlen(buf) == 1) && (buf[0] == 'b'))
        return 0;
    else if ((strlen(buf) != 1) || (buf[0] != 's'))
        strncpy(appTemp->event, buf, sizeof(appTemp->event));
    storeToFile(appTemp);
    return 0;
}

int Ceate(appointment *appTemp)
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
    if ((strlen(buf) == 1) && (buf[0] == 'b'))
        return 0;
    strncpy(appTemp->name, buf, sizeof(appTemp->name));
    setbuf(stdin, NULL);
    printf("Please enter location:");
    fgets(buf, sizeof(buf), stdin);
    if (buf[strlen(buf) - 1] == '\n')
        buf[strlen(buf) - 1] = '\0';
    if ((strlen(buf) == 1) && (buf[0] == 'b'))
        return 0;
    strncpy(appTemp->location, buf, sizeof(appTemp->location));
    setbuf(stdin, NULL);
    printf("Please enter event:");
    fgets(buf, sizeof(buf), stdin);
    if (buf[strlen(buf) - 1] == '\n')
        buf[strlen(buf) - 1] = '\0';
    if ((strlen(buf) == 1) && (buf[0] == 'b'))
        return 0;
    strncpy(appTemp->event, buf, sizeof(appTemp->event));

    return Verify(appTemp);
}

int searchFromFile(appointment result[], appointment *key)
{
    int dataCount = 0;
    FILE *store = fopen("database", "r");
    if (store == NULL)
    {
        printf("File is NULL");
        return -1;
    }
    char temp[784];
    appointment appTemp;
    while ((fgets(temp, 784, store) != NULL) && (dataCount < 255))
    {
        char *token = calloc(772, sizeof(char));
        sscanf(temp, "%4d%2d%2d%2d%2d%[^\n]", &appTemp.year, &appTemp.month, &appTemp.day, &appTemp.hour, &appTemp.minute, token);
        token = strtok(token, "|");
        strncpy(appTemp.name, token, sizeof(appTemp.name));
        token = strtok(NULL, "|");
        strncpy(appTemp.location, token, sizeof(appTemp.location));
        token = strtok(NULL, "|");
        strncpy(appTemp.event, token, sizeof(appTemp.event));
        if ((key->year != -1) && (key->year != appTemp.year))
            continue;
        if ((key->month != -1) && (key->month != appTemp.month))
            continue;
        if ((key->day != -1) && (key->day != appTemp.day))
            continue;
        if ((key->hour != -1) && (key->hour != appTemp.hour))
            continue;
        if ((key->minute != -1) && (key->minute != appTemp.minute))
            continue;
        if ((strstr(key->event, "-1") == NULL) && (strstr(appTemp.event, key->event) == NULL))
            continue;
        if ((strstr(key->name, "-1") == NULL) && (strstr(appTemp.name, key->name) == NULL))
            continue;
        if ((strstr(key->location, "-1") == NULL) && (strstr(appTemp.location, key->location) == NULL))
            continue;
        result[dataCount] = appTemp;
        dataCount++;
    }
    fclose(store);
    return dataCount;
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
    char *reply = calloc(785, sizeof(char));
    sprintf(reply, "%04d/%02d/%02d %02d:%02d %s %s %s\n", appTemp->year, appTemp->month, appTemp->day, appTemp->hour, appTemp->minute, appTemp->name, appTemp->location, appTemp->event);
    return reply;
}