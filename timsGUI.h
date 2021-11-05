#include <stdio.h>
#include <stdlib.h>
void TimsMainForm();
void TimsAddForm();
void TimsCloseForm();

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
    printf("Please enter the date(yyyy/mm/dd): ");
}

void TimsCloseForm()
{
    system("cls");
    printf("=======================================================\n");
    printf("Program Close\n");
    printf("=======================================================");
}