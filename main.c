#include "appointment.h"
#include "timsGUI.h"
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mainForm();
appointment original[256];
int dataCount;

int main()
{
    dataCount = readFile(original);
    mainForm();
}

int mainForm()
{
    TimsMainForm();
    char command;
    command = getch();
    while ((command != 'n') && (command != 'v') && (command != 'm') && (command != 's') && (command != 'e'))
        command = getch();
    switch (command)
    {
    case 'n':
    {
        TimsAddForm();
        appointment app;
        switch (Ceate(&app))
        {
        case 1:
            storeToFile(&app);
            TimsResultForm(1);
            break;
        case -1:
            TimsResultForm(0);
            break;
        }
        break;
    }
    case 'v':
    {
        appointment key;
        char buf[256];
        setbuf(stdin, NULL);
        system("cls");
        printf("Please enter the date(yyyy/mm/dd):");
        fgets(buf, sizeof(buf), stdin);
        char *token = strtok(buf, "/");
        if (token[0] == 'b')
            break;
        else
        {
            key.year = atoi(token);
            token = strtok(NULL, "/");
            key.month = atoi(token);
            token = strtok(NULL, "/");
            key.day = atoi(token);
        }
        key.hour = -1;
        key.minute = -1;
        strncpy(key.name, "-1", sizeof(key.name));
        strncpy(key.location, "-1", sizeof(key.location));
        strncpy(key.event, "-1", sizeof(key.event));
        TimsViewForm();
        char viewCommand;
        viewCommand = getch();
        while ((viewCommand != 'd') && (viewCommand != 'w') && (viewCommand != 'b'))
        {
            viewCommand = getch();
            printf("%c\b", command);
        }

        switch (viewCommand)
        {
        case 'd':
        {
            appointment result[256];
            int n = searchFromFile(result, &key);
            if (n > 0)
            {
                system("cls");
                printf("=======================================================\n");
                printf("%02d/%02d:\n", key.month, key.day);
                for (int i = 0; i < n; i++)
                {
                    printf("    %02d:%02d %s %s %s\n", result[i].hour, result[i].minute, result[i].name, result[i].location, result[i].event);
                }
            }
            break;
        }
        case 'w':
        {
            int d = key.day, m = (key.month <= 2) ? 10 + key.month : key.month - 2, y = (key.month == 1) || (key.month == 2) ? key.year % 100 - 1 : key.year % 100, c = key.year / 100 - 1;
            int w = (int)(d + (2.6 * m - 0.2) + 5 * (y % 4) + 3 * y + 5 * (c % 4)) % 7;
            key.day += 1 - w;
            system("cls");
            printf("=======================================================\n");
            for (int i = 1; i <= 7; i++)
            {
                printf("%02d/%02d %s:\n\n", key.month, key.day, weekIntToStr(i));
                appointment result[256];
                int n = searchFromFile(result, &key);
                if (n == 0)
                    printf("    nothing\n");
                for (int i = 0; i < n; i++)
                {
                    printf("    %02d:%02d %s %s %s\n", result[i].hour, result[i].minute, result[i].name, result[i].location, result[i].event);
                }
                printf("\n");
                key.day++;
            }
            break;
        }
        }
        printf("Press any key...");
        getch();
        break;
    }
    case 'm':
    {
        system("cls");
        appointment key;
        char buf[256];
        setbuf(stdin, NULL);
        printf("Please enter the date(yyyy/mm/dd):");
        fgets(buf, sizeof(buf), stdin);
        char *token = strtok(buf, "/");
        if (token[0] == 'b')
            break;
        else
        {
            key.year = atoi(token);
            token = strtok(NULL, "/");
            key.month = atoi(token);
            token = strtok(NULL, "/");
            key.day = atoi(token);
        }
        setbuf(stdin, NULL);
        printf("Please enter the 24-h time(hh:mm):");
        fgets(buf, sizeof(buf), stdin);
        token = strtok(buf, ":");
        if (token[0] == 'b')
            break;
        else
        {
            key.hour = atoi(token);
            token = strtok(NULL, ":");
            key.minute = atoi(token);
        }
        appointment result[1];
        int n = searchFromFile(result, &key);
        if (n == 0)
        {
            printf("Not fond data\n");
            printf("Press any key...");
            getch();
            break;
        }
        TimsModDelForm();
        char modifyCommand;
        modifyCommand = getch();
        while ((modifyCommand != 'd') && (modifyCommand != 'm') && (modifyCommand != 'b'))
        {
            modifyCommand = getch();
            printf("%c\b", command);
        }
        switch (modifyCommand)
        {
        case 'd':
        {
            Delete(&result[0]);
            TimsResultForm(1);
            break;
        }
        case 'm':
        {
            TimsModifyForm();
            switch (Modify(&result[0]))
            {
            case 1:
                storeToFile(&result[0]);
                TimsResultForm(1);
                break;
            case -1:
                TimsResultForm(0);
                break;
            }
            break;
        }
        }
        break;
    }
    case 's':
    {
        TimsSearchForm();
        appointment key;
        if (Ceate(&key))
        {
            appointment result[256];
            int n = searchFromFile(result, &key);
            system("cls");
            printf("=======================================================\n");
            if (n == 0)
                printf("Not found\n");
            for (int i = 0; i < n; i++)
            {
                printf("%s", toString(&result[i]));
            }
        }
        printf("Press any key...");
        getch();
        break;
    }
    case 'e':
    {
        switch (TimsCloseForm())
        {
        case 'y':
            return 0;
        case 'n':
            remove("database");
            for (int i = 0; i < dataCount; i++)
                storeToFile(&original[i]);
            return 0;
        }
        return 0;
    }
    }
    mainForm();
    return 0;
}