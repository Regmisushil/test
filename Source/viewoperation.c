#include <stdio.h>
#include <windows.h>
#include "../header/firstlook.h"
#include "../header/datetime.h"
#include "../header/satellite_h.h"
#include "../header/database.h"
#include <stdlib.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>

// Function to retrieve satellite information using stored procedure GetSatellites
void retrieve_satellites()
{
 
    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLHSTMT hStmt;
    SQLRETURN ret;
    

    char sat_name[100] = "";
    char sat_class[100] = "";
    char launch_date[20] = "";
    char sort_column[50] = "";
    char sort_order[10] = "";

    int applyFilter = 0, applySort = 0;

    // Ask user if they want to apply filters
    printf("Do you want to apply filters? (1 = Yes, 0 = No): ");
    scanf("%d", &applyFilter);
    getchar(); // consume newline

    if (applyFilter) {
        printf("Enter satellite name filter (or press Enter to skip): ");
        fgets(sat_name, sizeof(sat_name), stdin);
        sat_name[strcspn(sat_name, "\n")] = 0;

        printf("Enter satellite class filter (or press Enter to skip): ");
        fgets(sat_class, sizeof(sat_class), stdin);
        sat_class[strcspn(sat_class, "\n")] = 0;

        printf("Enter launch date filter (YYYY-MM-DD or press Enter to skip): ");
        fgets(launch_date, sizeof(launch_date), stdin);
        launch_date[strcspn(launch_date, "\n")] = 0;
    }

    // Ask user if they want to apply sorting
    printf("Do you want to apply sorting? (1 = Yes, 0 = No): ");
    scanf("%d", &applySort);
    getchar();

    if (applySort) {
        printf("Enter sorting column (e.g., Name, Class, LaunchDate): ");
        fgets(sort_column, sizeof(sort_column), stdin);
        sort_column[strcspn(sort_column, "\n")] = 0;

        printf("Enter sorting order (ASC or DESC): ");
        fgets(sort_order, sizeof(sort_order), stdin);
        sort_order[strcspn(sort_order, "\n")] = 0;
    }
    
    // Connect to DB
    hDbc = connectToDB(&hEnv);
    if (hDbc == NULL) 
    {
        printf("Failed to connect to database.\n");
        return;
    }

    // Allocate statement handle
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    // Build stored procedure call
    char query[512];
    snprintf(query, sizeof(query),
             "EXEC GetSatellites '%s', '%s', '%s', '%s', '%s'",
             applyFilter ? sat_name : "",
             applyFilter ? sat_class : "",
             applyFilter ? launch_date : "",
             applySort ? sort_column : "",
             applySort ? sort_order : "");

    // Execute stored procedure
    ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) 
    {
        printf("Failed to execute stored procedure.\n");
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        closeConnection(hEnv, hDbc);
        return;
    }

    // Fetch and display results
    SQLCHAR col1[100], col2[100], col3[100], col4[100];

    // Print table header
    printf("---------------------------------------------------------------------------------------------\n");
    printf("| %-5s | %-20s | %-15s | %-15s\n",
       "ID", "Name", "Class", "Launch Date");
    printf("---------------------------------------------------------------------------------------------\n");

    // Fetch and print rows
    while (SQLFetch(hStmt) == SQL_SUCCESS) {
    SQLGetData(hStmt, 1, SQL_C_CHAR, col1, sizeof(col1), NULL);
    SQLGetData(hStmt, 2, SQL_C_CHAR, col2, sizeof(col2), NULL);
    SQLGetData(hStmt, 3, SQL_C_CHAR, col3, sizeof(col3), NULL);
    SQLGetData(hStmt, 4, SQL_C_CHAR, col4, sizeof(col4), NULL);

    printf("| %-5s | %-20s | %-15s | %-15s\n",
           col1, col2, col3, col4);
}

printf("---------------------------------------------------------------------------------------------\n");

    // Cleanup
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    closeConnection(hEnv, hDbc);

} 