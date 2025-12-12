#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "../header/firstlook.h"
#include "../header/datetime.h"
#include "../header/satellite_h.h"
#include "../header/database.h"




void add_satellite ()
{

    system("cls");
    //variables to store satellite details
    int sat_id;
    char sat_name[MAX_LENGTH];
    char sat_class[MAX_LENGTH];
    char sat_payload[MAX_LENGTH];
    char sat_agency[MAX_LENGTH];
    char sat_identifier[MAX_LENGTH];
    char sat_status[MAX_LENGTH];
    

    datetime *launch_Date = NULL; 
    //Test_push
    //userdefined structure data type to stored the consolidated satellite information
    sat satellite_info;
    char launch_Date_str[15];

    //const char * --protects the string from accidental modification
    //const char * --the string is read only 

    const char * enter_sat_detail = "Enter Details of the satellite:\n";
    const char * enter_satellite_name = "Enter name of a satellite name: ";
    const char * enter_satellite_class = "Enter the class of satellite launched: ";
    const char * enter_date_of_launch = "Enter the date of launch (DD-MM-YYYY): ";
    const char * enter_payload = "Enter payload information: ";
    const char * enter_spaceagency = "Enter the space agency name: ";
    const char * enter_identifier = "Enter the agency provided unique identifier: ";
    const char * enter_status = "Enter the current status of satellite: ";

    // Prompt 1
    setCursorPosition(5, 5);
    printf("%s", enter_sat_detail);
    setCursorPosition(5, 7);
    printf("%s", enter_satellite_name);
    setCursorPosition(5, 9);
    printf("%s", enter_satellite_class);
    setCursorPosition(5, 11);
    printf("%s", enter_payload);
    setCursorPosition(5, 13);
    printf("%s", enter_spaceagency);
    setCursorPosition(5, 15);
    printf("%s", enter_identifier);   
    setCursorPosition(5, 17);
    printf("%s", enter_status);
    setCursorPosition(5, 19);
    printf("%s", enter_date_of_launch);


    setCursorPosition(5+strlen(enter_satellite_name), 7);
    int valid = 0;
    while (!valid) 
    {
        setCursorPosition(5+strlen(enter_satellite_name), 7);
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
        setCursorPosition(5+strlen(enter_satellite_class), 9);
        fgets(sat_class, sizeof(sat_class), stdin);
        sat_class[strcspn(sat_class, "\n")] = '\0';

        if (strlen(sat_class) == 0) {
            setCursorPosition(5, 2);
            printf("\nInvalid Data");
        } else {
            valid = 1;
        }
    }

    valid = 0;
    while (!valid) 
    {
        setCursorPosition(5+strlen(enter_payload), 11);
        fgets(sat_payload, sizeof(sat_payload), stdin);
        sat_payload[strcspn(sat_payload, "\n")] = '\0';

        if (strlen(sat_payload) == 0) {
            setCursorPosition(5, 2);
            printf("\nInvalid Data");
        } else 
        {
            valid = 1;
        }
    }

    valid = 0;
    
    while (!valid) 
    {
        setCursorPosition(5+strlen(enter_spaceagency), 13);
        fgets(sat_agency, sizeof(sat_agency), stdin);
        sat_agency[strcspn(sat_agency, "\n")] = '\0';

        if (strlen(sat_agency) == 0) {
            setCursorPosition(5, 2);
            printf("\nInvalid Data");
        } else 
        {
            valid = 1;
        }
    }

    valid = 0;
    while (!valid) 
    {
        setCursorPosition(5+strlen(enter_identifier), 15);
        fgets(sat_identifier, sizeof(sat_identifier), stdin);
        sat_identifier[strcspn(sat_identifier, "\n")] = '\0';

        if (strlen(sat_identifier) == 0) {
            setCursorPosition(5, 2);
            printf("\nInvalid Data");
        } else 
        {
            valid = 1;
        }
    }

    //"Enter the current status of satellite: "

    valid = 0;
    while (!valid) 
    {
        setCursorPosition(5+strlen(enter_status), 17);
        fgets(sat_status, sizeof(sat_status), stdin);
        sat_status[strcspn(sat_status, "\n")] = '\0';

        if (strlen(sat_status) == 0) 
        {
            setCursorPosition(5, 2);
            printf("\nInvalid Data");
        } else 
        {
            valid = 1;
        }
    }

    //Input and Date Validation Loop    
    valid = 0;
    while (!valid) 
    {

       setCursorPosition(5 + strlen(enter_date_of_launch), 19);
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

            //sscanf(launch_Date_str, "%d-%d-%d", &launch_Date->dt_day, &launch_Date->dt_mon, &launch_Date->dt_year);
            sscanf(launch_Date_str, "%d-%d-%d", &launch_Date->dt_year, &launch_Date->dt_mon, &launch_Date->dt_day);
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
            printf("%s %s", enter_payload,sat_payload);
            setCursorPosition(5, 13);
            printf("%s %s", enter_spaceagency, sat_agency);
            setCursorPosition(5, 15);
            printf("%s %s", enter_identifier, sat_identifier);
            setCursorPosition(5, 17);
            printf("%s %s", enter_status,sat_status);
            setCursorPosition(5, 19);
            printf("%s", enter_date_of_launch);

             
            }
        }
    }

    setCursorPosition(5, 2);
            printf("\n                                                       ");


    satellite_info.class = malloc(strlen(sat_class) + 1);
    strcpy(satellite_info.class, sat_class);
    //*(satellite_info.class) = sat_class; -- wrong approach


  
    satellite_info.name = malloc(strlen(sat_name) + 1);
    strcpy(satellite_info.name, sat_name);
    //*(satellite_info.name) = sat_name; -- wrong approach it will store the first character of sat_name on name of a structure 

    satellite_info.payload = malloc(strlen(sat_payload) + 1);
    strcpy(satellite_info.payload, sat_payload);

    satellite_info.space_agency = malloc(strlen(sat_agency) + 1);
    strcpy(satellite_info.space_agency, sat_agency);

    satellite_info.identifier_number = malloc(strlen(sat_identifier) + 1);
    strcpy(satellite_info.identifier_number, sat_identifier);

    satellite_info.status = malloc(strlen(sat_status) + 1);
    strcpy(satellite_info.status, sat_status);


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



  
    setCursorPosition(5, 20);
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
             "INSERT INTO Satellites (Name, Class, Payload, LaunchDate,Agency,IDN,Status) "
             "VALUES ('%s', '%s', '%s', '%04d-%02d-%02d','%s','%s','%s')",
             satellite_info.name,
             satellite_info.class,
             satellite_info.payload,
             satellite_info.launch_date->dt_year,
             satellite_info.launch_date->dt_mon,
             satellite_info.launch_date->dt_day,
             satellite_info.space_agency,
             satellite_info.identifier_number,
             satellite_info.status
            );
            } 
            else 
            {
                snprintf(query, sizeof(query),
                "INSERT INTO Satellites (Name, Class, Payload, LaunchDate,Agency,IDN,Status) ""VALUES ('%s', '%s', '%s', NULL,'%s','%s','%s')",satellite_info.name,satellite_info.class,satellite_info.payload,satellite_info.space_agency,satellite_info.identifier_number,satellite_info.status);
            }
        printf("Executing Query: %s\n", query); // Debugging purpose
        ret = executeStatement(hDbc, query,NULL);

        free(satellite_info.name);
        free(satellite_info.class);
        free(satellite_info.payload);
        free(satellite_info.space_agency);
        free(satellite_info.identifier_number);
        free(satellite_info.status);
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
        free(satellite_info.payload);
        if (satellite_info.launch_date != NULL) {
            free(satellite_info.launch_date);
        }
        printf("Satellite details not saved.\n");
    }


}

    
