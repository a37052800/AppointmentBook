#include "appointment.h"
#include "timsFunction.h"
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
    while ((command != 'n') && (command != 'v') && (command != 'm') && (command != 's') && (command != 'e'))
    {
        command = getch();
        printf("%c\b", command);
    }
    switch (command)
    {
    case 'n':
        TimsAddForm();
        appointment app;
        if (Add(&app))
        {
            storeToFile(&app);
            main();
            return 0;
        }
        else
        {
            main();
            return 0;
        }
        return 0;
        break;
    case 'v':
        break;
    case 'm':
        break;
    case 's':
        break;
    case 'e':
        TimsCloseForm();
        return 0;
        break;
    }
    return 0;
}