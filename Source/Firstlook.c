#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "../header/firstlook.h"
#include "../header/datetime.h"
#include "../header/satellite_h.h"
#include "../header/database.h"
void Sat_wc ()
{

    char choice;
    choice ='Y';
    while (choice=='Y')
    {
    system("cls");
    printf("Welcome to Satellite Tracker.");
    menu_list();
    getchar();
    printf("Do you want to return to main window of application? (Y/N): ");
    scanf("%c",&choice);
    }
}

void menu_list()
{

    system("cls");
    int selection;
    printf("Select Any Option Below \n");
    printf("\n");
    printf("1. Add New Satellite Details");
    printf("\n");
    printf("2. Update Satellite Details");
    printf("\n");
    printf("3. View Satellite Information");
    printf("\n");
    printf("4. Delete the Record Satellite");
    printf("\n");
    scanf("%d",&selection);
    getchar();

    switch(selection)
    {
    case 1:
        add_satellite();
        break;
    case 2:
        updateSatellite();
        break;
    case 3:
        retrieve_satellites();
        break;
    case 4:
        del_sat();
        break;
    }
}

void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

