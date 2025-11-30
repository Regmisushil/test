#include <windows.h>
#include <sql.h>
#include <sqlext.h> 
#include <stdio.h>
#include "../header/dbase.h"

//sqltext.h is the ODBC extension header provided by microsoft


// Function to connect to the database
SQLHDBC connectToDB(SQLHENV *hEnv) 

{
    SQLHDBC hDbc;
    SQLRETURN ret;

    //Allocate environment handle

    //SQLAllocHandle: the ODBC Driver manager allocates 
    //an internal memory structures to represent an environment object
    //That enviroment object lives inside the ODBC subsystem(Driver Manager + driver),
    //not in the programs normal heap

    //hEnv doesnot hold the environment  itself, but a pointer to it
    //In other word it holds a handle that let us refer to the environment object managed by ODBC
    
    //with valid henv,SQLSetEnvAttr is used to conigure enviroment
    //below block set the attribute ODBC_version to ODBC3
    //for the environmental object that the handle henv refers to.

    //The attribute is stored inside the internal memory block 
    //that ODBC allocated earlier.


    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, hEnv);
    SQLSetEnvAttr(*hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

    //Allocate connection handle
    SQLAllocHandle(SQL_HANDLE_DBC, *hEnv, &hDbc);

    // Connection string
    SQLCHAR connStr[] =
        "DRIVER={ODBC Driver 18 for SQL Server};"
        "SERVER=DESKTOP-SC6AHI4\\SQLEXPRESS;"
        "DATABASE=SatelliteDB;"
        "Trusted_Connection=Yes;"
        "Encrypt=yes;TrustServerCertificate=yes;";

    // Connect to SQL server
    ret = SQLDriverConnect(hDbc, NULL, connStr, SQL_NTS,
                           NULL, 0, NULL, SQL_DRIVER_COMPLETE);
    if (!SQL_SUCCEEDED(ret)) {
        printf("Connection failed!\n");
        return NULL;
    }
    printf("Connected to SQL Server!\n");
    return hDbc;
}

// Function to execute a SQL statement
void viewStatement(SQLHDBC hDbc, const char *query)
{
    SQLHSTMT hStmt;
    SQLRETURN ret;

    // Allocate statement handle
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        printf("Failed to allocate statement handle\n");
        return;
    }

    // Execute query
    ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
    if (SQL_SUCCEEDED(ret)) 
    {
        SQLCHAR name[128], classVal[128], launchDate[64];
        printf("%-20s %-15s %-20s\n", "Satellite", "Class", "Launch Date");
        printf("---------------------------------------------------------------\n");
        while (SQLFetch(hStmt) == SQL_SUCCESS) {
            SQLGetData(hStmt, 1, SQL_C_CHAR, name, sizeof(name), NULL);
            SQLGetData(hStmt, 2, SQL_C_CHAR, classVal, sizeof(classVal), NULL);
            SQLGetData(hStmt, 3, SQL_C_CHAR, launchDate, sizeof(launchDate), NULL);

            printf("%-20s %-15s %-20s\n", name, classVal, launchDate);

        }
    } 
    else 
    {
        printf("Query execution failed!\n");
    }

    // Free statement handle
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}


//Function to insert Data
SQLRETURN executeStatement(SQLHDBC hDbc, const char *query,SQLLEN *rowCount)
{
    SQLHSTMT hStmt = SQL_NULL_HSTMT; //initialize statement handle
    SQLRETURN ret = SQL_ERROR;//initialize return value

    // Allocate statement handle
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        printf("Failed to allocate statement handle\n");
        return ret;
    }

    // Execute query
    ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
    if (SQL_SUCCEEDED(ret) && rowCount !=NULL) {
        SQLRowCount(hStmt, rowCount);
    }

    // Free statement handle before returning
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return ret;
}



// Function to close the connection
void closeConnection(SQLHENV hEnv, SQLHDBC hDbc) 
{
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
    printf("Connection closed.\n");
}



