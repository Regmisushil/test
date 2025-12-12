#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "../header/firstlook.h"
#include "../header/datetime.h"
#include "../header/satellite_h.h"
#include "../header/database.h"


void updateSatellite() 
{
    system("cls");

    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLRETURN ret;
    SQLLEN rowCount;
    SQLHSTMT hStmt;


    const char * update_sat_detail = "Enter the updated details of  satellite:\n";
    const char * update_satellite_name = "Enter name of a satellite name: ";
    const char * update_satellite_class = "Enter the class of satellite launched: ";
    const char * update_date_of_launch = "Enter the date of launch (YYYY-MM-DD): ";
    const char * update_payload = "Enter payload information: ";
    const char * udpate_spaceagency = "Enter the space agency name: ";
    const char * update_identifier = "Enter the agency provided unique identifier: ";
    const char * update_status = "Enter the current status of satellite: ";
    datetime *new_date = NULL;

    char sat_identifier[MAX_LENGTH];
    printf("Enter the agency provided unique identifier of the satellite to update: ");
    fgets(sat_identifier, sizeof(sat_identifier), stdin);
    sat_identifier[strcspn(sat_identifier, "\n")] = '\0';

    // Connect to DB
    hDbc = connectToDB(&hEnv);
    if (hDbc == NULL) 
    {
        printf("Database connection failed.\n");
        return;
    }

    // Step 1: Fetch existing record
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    
    char selectQuery[256];
    snprintf(selectQuery, sizeof(selectQuery),
             "SELECT Name, Class, Payload, LaunchDate, Agency, Status "
             "FROM Satellites WHERE IDN='%s'", sat_identifier);

    ret = SQLExecDirect(hStmt, (SQLCHAR*)selectQuery, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) 
        {
    // Bind columns
        char oldName[MAX_LENGTH], oldClass[MAX_LENGTH], oldPayload[MAX_LENGTH];
        char oldAgency[MAX_LENGTH], oldStatus[MAX_LENGTH];
        char oldDate[20]; // YYYY-MM-DD

        SQLBindCol(hStmt, 1, SQL_C_CHAR, oldName, sizeof(oldName), NULL);
        SQLBindCol(hStmt, 2, SQL_C_CHAR, oldClass, sizeof(oldClass), NULL);
        SQLBindCol(hStmt, 3, SQL_C_CHAR, oldPayload, sizeof(oldPayload), NULL);
        SQLBindCol(hStmt, 4, SQL_C_CHAR, oldDate, sizeof(oldDate), NULL);
        SQLBindCol(hStmt, 5, SQL_C_CHAR, oldAgency, sizeof(oldAgency), NULL);
        SQLBindCol(hStmt, 6, SQL_C_CHAR, oldStatus, sizeof(oldStatus), NULL);

        if (SQLFetch(hStmt) != SQL_SUCCESS) 
        {
        printf("No record found.\n");
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        closeConnection(hEnv, hDbc);
        return;
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    // Step 2: Prompt user for new values
        char buffer[MAX_LENGTH];
        char newName[MAX_LENGTH], newClass[MAX_LENGTH], newPayload[MAX_LENGTH];
        char newAgency[MAX_LENGTH], newStatus[MAX_LENGTH], newDate[20];
        system("cls");
        printf("%s", update_sat_detail);
        setCursorPosition(5, 5);
        printf("%s", update_satellite_name);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(newName, strlen(buffer) ? buffer : oldName);

        setCursorPosition(5, 7);
        printf("%s", update_satellite_class);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(newClass, strlen(buffer) ? buffer : oldClass);

        setCursorPosition(5, 9);
        printf("%s", update_payload);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(newPayload, strlen(buffer) ? buffer : oldPayload);

        setCursorPosition(5, 11);
        printf("%s",udpate_spaceagency);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(newAgency, strlen(buffer) ? buffer : oldAgency);

        setCursorPosition(5, 13);
        printf("%s", update_status);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(newStatus, strlen(buffer) ? buffer : oldStatus);

        setCursorPosition(5, 15);
        printf("%s", update_date_of_launch);

        new_date =malloc(sizeof(datetime));

        int valid = 0;
        while (!valid)
        {
        setCursorPosition(5 + strlen(update_date_of_launch), 15);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if(strlen(buffer)==0)
        {
        strcpy(newDate,oldDate);
        valid = 1;
        setCursorPosition(0, 3);
        printf("                                                                 ");
        setCursorPosition(5, 17);
        }
        else
        {
        sscanf(buffer,"%d-%d-%d",&new_date->dt_year,&new_date->dt_mon,&new_date->dt_day);
        if (new_date->dt_year > 1957 && new_date->dt_mon >= 1 && new_date->dt_mon <= 12 &&
            new_date->dt_day >= 1 && new_date->dt_day <= 31)
        {
            strcpy(newDate,buffer);
            valid = 1;
            setCursorPosition(0, 3);
            printf("                                                               ");
            setCursorPosition(5, 17);
        }
        else
        {
            setCursorPosition(0, 3);
            printf("Invalid date entered. Pleaes re-enter the date.");
            valid = 0;
            setCursorPosition(5 + strlen(update_date_of_launch), 15);
            printf("                                                ");
        } 
        }
        }
    free(new_date);

    // Step 3: Confirm update
    printf("Do you want to update the details? (Y/N): ");
    char choice;
    scanf(" %c", &choice);
    getchar(); // consume newline

    if (choice != 'Y' && choice != 'y') 
    {
        printf("Update cancelled.\n");
        closeConnection(hEnv, hDbc);
        return;
    }

    // Step 4: Build UPDATE query
    char updateQuery[512];
    snprintf(updateQuery, sizeof(updateQuery),
             "UPDATE Satellites SET Name='%s', Class='%s', Payload='%s', "
             "LaunchDate='%s', Agency='%s', Status='%s' "
             "WHERE IDN='%s'",
             newName, newClass, newPayload, newDate,
             newAgency, newStatus, sat_identifier);

    printf("Executing Query: %s\n", updateQuery); // Debug

    ret = executeStatement(hDbc, updateQuery, NULL);
    if (SQL_SUCCEEDED(ret)) {
        printf("Satellite details updated successfully.\n");
    } else {
        printf("Failed to update satellite details.\n");
    }
    }

closeConnection(hEnv, hDbc);
}
