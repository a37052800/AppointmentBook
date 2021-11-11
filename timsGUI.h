#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

void TimsMainForm();
void TimsAddForm();
void TimsViewForm();
void TimsModifyForm();
void TimsModDelForm();
void TimsSearchForm();
void TimsCloseForm();
char *weekIntToStr(int week);
void TimsResultForm(int bool);

void TimsMainForm()
{
    system("cls");
    printf("=======================================================\n");
    printf("Wellcome Tims AppointmentBook\n");
    printf("(n:New, v:View, m:Modify, s:Search, e:Exit)\n");
    printf("Please enter the command:");
}

void TimsAddForm()
{
    system("cls");
    printf("=======================================================\n");
    printf("(Prass b for back)\n");
}

void TimsViewForm()
{
    system("cls");
    printf("=======================================================\n");
    printf("(d:View Day, w:View Week, b:Back)\n");
    printf("Please enter the command:");
}

void TimsModifyForm()
{
    system("cls");
    printf("=======================================================\n");
    printf("(s:Skip, b:Back)\n");
}

void TimsModDelForm()
{
    system("cls");
    printf("=======================================================\n");
    printf("(d:Delete, m:Modify, b:Back)\n");
}

void TimsSearchForm()
{
    system("cls");
    printf("=======================================================\n");
    printf("(Enter '-1' to query, 'b' for back)\n");
}

void TimsCloseForm()
{
    system("cls");
    printf("=======================================================\n");
    printf("Program Close\n");
    printf("Press any key...");
    getch();
}

void TimsResultForm(int bool)
{
    system("cls");
    printf("=======================================================\n");
    if (bool == 1)
        printf("Success\n");
    else
        printf("Failed. please try again\n");
    printf("Press any key...");
    getch();
}

char *weekIntToStr(int week)
{
    switch (week)
    {
    case 1:
        return "Monday";
        break;
    case 2:
        return "Tuesday";
        break;
    case 3:
        return "Wednesday";
        break;
    case 4:
        return "Thursday";
        break;
    case 5:
        return "Friday";
        break;
    case 6:
        return "Saturday";
        break;
    case 7:
        return "Sunday";
        break;
    }
    return 0;
}