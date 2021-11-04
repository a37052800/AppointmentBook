#include "appointment.h"
#include "timsGUI.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    TimsMainForm();
    char command;
    command = getch();
    while ((command != 'a') && (command != 'v') && (command != 'm') && (command != 's'))
    {
        TimsMainForm();
        command = getch();
        printf("%c\b", command);
    }
    switch (command)
    {
    case 'a':
    {
        TimsAddForm();
        appointment app;
        if(Add(&app))
        {
            printf("%d", app.year);
        }
        else
            TimsMainForm();
        break;
    }
    case 'v':
        break;
    case 'm':
        break;
    case 's':
        break;
    }
    return 0;
}