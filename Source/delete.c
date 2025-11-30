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


void del_sat()
{
 
    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLHSTMT hStmt;
    SQLRETURN ret;
    SQLLEN rowCount;
    char del_id[20];


    // Ask user to delete the record
    printf("Enter the ID you want to delete ");
    fgets(del_id, sizeof(del_id), stdin);
    del_id[strcspn(del_id, "\n")] = 0;


    char query[256];



    //printf("Generated SQL Query: %s\n", query); --debugging purpose


    if(del_id[0] =='\0')
    {
        printf("Invalid ID. Deletion aborted.\n");
    }
    else
    {
        // Connect to DB
        hDbc = connectToDB(&hEnv);
        if (hDbc == NULL) 
        {
        printf("Failed to connect to database.\n");
        return;
        }
        else
        {  
    
    
            // build delete statement
            snprintf(query, sizeof(query),"DELETE FROM Satellites WHERE SatID = '%s'",del_id);

    

            //Execute delete statement
            ret = executeStatement(hDbc, query, &rowCount);
            if (SQL_SUCCEEDED(ret)) 
            {
                if (rowCount == 0) 
                {
                printf("No satellite found with the given ID.\n");
                } 
                else
                {
                printf("Satellite details deleted successfully.\n");
                }
            } else
            {
                printf("Failed to execute delete statement.\n");
            }
            closeConnection(hEnv, hDbc);
        } 
    }
}  

