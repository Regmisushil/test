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

    printf("Welcome to Satellite Tracker.");
    menu_list();
    getchar();
    printf("do you want to exist the application? (Y/N): ");

}

void menu_list()
{

    system("cls");
    int selection;
    printf("Select Any Option Below \n");
    printf("\n");
    printf("1. Add/Update New Satellite Details");
    printf("\n");
    printf("2. View Satellite Information");
    printf("\n");
    printf("3. Delete the Record Satellite");
    printf("\n");
    scanf("%d",&selection);
    getchar();

    switch(selection)
    {
    case 1:
        add_update_satellite();
       break;
    case 2:
       retrieve_satellites();
       break;

    case 3:
        del_sat();
        break;
    case 4:
        //close_app();
        break;
    default:
    //close_app();
    break;
      
    }
}

void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void add_update_satellite ()
{

    system("cls");
    //variables to store satellite details
    int sat_id;
    char sat_name[MAX_LENGTH];
    char sat_class[MAX_LENGTH];
    

    datetime *launch_Date = NULL; 

    //userdefined structure data type to stored the consolidated satellite information
    sat satellite_info;
    char launch_Date_str[15];

    //const char * --protects the string from accidental modification
    //const char * --the string is read only 

    const char * enter_sat_detail = "Enter Details of the satellite:\n";
    const char * enter_satellite_name = "Enter name of a satellite name: ";
    const char * enter_satellite_class = "Enter the class of satellite launched: ";
    const char * enter_date_of_launch = "Enter the date of launch (DD-MM-YYYY): ";

    // Prompt 1
    setCursorPosition(5, 5);
    printf("%s", enter_sat_detail);
    setCursorPosition(5, 7);
    printf("%s", enter_satellite_name);
    setCursorPosition(5, 9);
    printf("%s", enter_satellite_class);
    setCursorPosition(5, 11);
    printf("%s", enter_date_of_launch);


    setCursorPosition(5+strlen(enter_satellite_name), 7);
    /*
    //fgets(sat_name, sizeof(sat_name), stdin);
    //sat_name[strcspn(sat_name, "\n")] = '\0';
    if (scanf("%[^\n]", sat_name) != 1) {
    sat_name[0] = '\0';  // treat as empty string
    }
    getchar();
    setCursorPosition(5+strlen(enter_satellite_class), 9);
    */
   int valid = 0;
    while (!valid) 
    {
        setCursorPosition(5+strlen("Enter name of a satellite name: "), 7);
        fgets(sat_name, sizeof(sat_name), stdin);
        sat_name[strcspn(sat_name, "\n")] = '\0';

        if (strlen(sat_name) == 0) 
        {
            setCursorPosition(5, 2);
            printf("\nInvalid Data\n");
        } 
        else
        {
            valid = 1;
        }
    }


   valid = 0;
    while (!valid) 
    {
        setCursorPosition(5+strlen("Enter the class of satellite launched: "), 9);
        fgets(sat_class, sizeof(sat_class), stdin);
        sat_class[strcspn(sat_class, "\n")] = '\0';

        if (strlen(sat_class) == 0) {
            setCursorPosition(5, 2);
            printf("\nInvalid Data");
        } else {
            valid = 1;
        }
    }

/*
    fgets(sat_class, sizeof(sat_class), stdin);
    sat_class[strcspn(sat_class, "\n")] = '\0';
    // scanf(" %[^\n]", sat_class);
*/



    //Input and Date Validation Loop    
    valid = 0;
    while (!valid) 
    {

       setCursorPosition(5 + strlen(enter_date_of_launch), 11);
        //scanf("%d-%d-%d", &launch_Date.dt_day, &launch_Date.dt_mon, &launch_Date.dt_year);
        fgets(launch_Date_str, sizeof(launch_Date_str), stdin);
        launch_Date_str[strcspn(launch_Date_str, "\n")] = '\0';
        if (strlen(launch_Date_str) == 0)
        {
            launch_Date = NULL;
            valid = 1;
        }
        else 
        {
            launch_Date = malloc(sizeof(datetime));

            sscanf(launch_Date_str, "%d-%d-%d", &launch_Date->dt_day, &launch_Date->dt_mon, &launch_Date->dt_year);
            if (launch_Date->dt_year > 1957 && launch_Date->dt_mon >= 1 && launch_Date->dt_mon <= 12 &&
            launch_Date->dt_day >= 1 && launch_Date->dt_day <= 31)
            {

            valid = 1;

            }
            else
            {
            free(launch_Date);
           // setCursorPosition(5, 2);;
            //printf("Invalid date! Please press enter to try again.\n");
           // getchar();
            system("cls");
            setCursorPosition(5, 2);
            printf("\nInvalid Date");
            setCursorPosition(5, 5);
            printf("%s", enter_sat_detail);
            setCursorPosition(5, 7);
            printf("%s %s", enter_satellite_name, sat_name);
            setCursorPosition(5, 9);
            printf("%s %s", enter_satellite_class,sat_class);
            setCursorPosition(5, 11);
            printf("%s", enter_date_of_launch);
             
            }
        }
    }

    setCursorPosition(5, 2);
            printf("\n                                                   ");
            

    satellite_info.class = malloc(strlen(sat_class) + 1);
    strcpy(satellite_info.class, sat_class);
    //*(satellite_info.class) = sat_class; -- wrong approach


  
    satellite_info.name = malloc(strlen(sat_name) + 1);
    strcpy(satellite_info.name, sat_name);
    //*(satellite_info.name) = sat_name; -- wrong approach it will store the first character of sat_name on name of a structure 

    if (launch_Date != NULL) 
    {
    satellite_info.launch_date = malloc(sizeof(datetime));
    *(satellite_info.launch_date) = *launch_Date; //deep copy
    //satellite_info.launch_date = launch_Date; --shallow copy
    } 
    else 
    {
    satellite_info.launch_date = NULL;
    } //deep copy

    
   /*
    setCursorPosition(5, 15);
    if (launch_Date != NULL) {
    printf("Captured -> Name: %s | Class: %s | Launch Date: %02d-%02d-%04d\n",
           sat_name, sat_class, launch_Date->dt_day, launch_Date->dt_mon, launch_Date->dt_year);
    } 
    else 
    {
    printf("Captured -> Name: %s | Class: %s | Launch Date: (not provided)\n",
           sat_name, sat_class);
    }
    */

    free(launch_Date);
    setCursorPosition(5, 12);
    printf("Do You want to save the details? (Y/N): ");
    char choice;
    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLRETURN ret;
    if (scanf(" %c", &choice) == 1 && (choice == 'Y' || choice == 'y'))
    {
        // Save the satellite_info to your data store

        hDbc = connectToDB(&hEnv);
        char query[512];
        if(hDbc!=NULL)
        {
            if (satellite_info.launch_date != NULL) 
        {
            //snprintf is C standard library function 
            //used to format a string safely into a buffer
            //sie of query returned by snprintf can be used for preventing buffer overflow.

            snprintf(query, sizeof(query),
             "INSERT INTO Satellites (Name, Class, LaunchDate) "
             "VALUES ('%s', '%s', '%04d-%02d-%02d')",
             satellite_info.name,
             satellite_info.class,
             satellite_info.launch_date->dt_year,
             satellite_info.launch_date->dt_mon,
             satellite_info.launch_date->dt_day);
        } 
            else 
            {
                snprintf(query, sizeof(query),
                "INSERT INTO Satellites (Name, Class, LaunchDate) ""VALUES ('%s', '%s', NULL)",satellite_info.name,satellite_info.class);
            }

        ret = executeStatement(hDbc, query,NULL);

        free(satellite_info.name);
        free(satellite_info.class);
        if (satellite_info.launch_date != NULL) 
            {
                free(satellite_info.launch_date);
            }
        if (SQL_SUCCEEDED(ret)) 
            {
            printf("Satellite details saved successfully.\n");
            }
        else 
            {
        printf("Failed to save satellite details.\n");
            }
        closeConnection(hEnv, hDbc);
        }
    }   
     else 
    {
        // Free allocated memory if not saving
        free(satellite_info.name);
        free(satellite_info.class);
        if (satellite_info.launch_date != NULL) {
            free(satellite_info.launch_date);
        }
        printf("Satellite details not saved.\n");
    }


}

    

