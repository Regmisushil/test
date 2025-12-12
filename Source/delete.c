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
    SQLRETURN ret,sel_ret;
    SQLLEN rowCount;
    char del_id[20];


    // Ask user to delete the record
    printf("Enter the IDN of stellite you want to delete ");
    fgets(del_id, sizeof(del_id), stdin);
    del_id[strcspn(del_id, "\n")] = 0;


    char query[256];
    char select_query[256];



    //printf("Generated SQL Query: %s\n", query); --debugging purpose


    if(del_id[0] =='\0')
        {
        printf("Invalid IDN. Deletion aborted.\n");
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

            snprintf(select_query, sizeof(select_query),"select count(*)  FROM Satellites WHERE IDN = '%s'",del_id);

            snprintf(query, sizeof(query),"DELETE FROM Satellites WHERE IDN = '%s'",del_id);

            printf("Executing Query: %s\n", query); // Debugging purpose
    
            sel_ret  = executeStatement(hDbc, select_query, &rowCount);
            //Execute delete statement

            if (SQL_SUCCEEDED(sel_ret)) 
            {
                if (rowCount == 0) 
                {
                printf("No satellite found with the given ID.\n");
                } 
                else
                {
                ret = executeStatement(hDbc, query, NULL);
                if (SQL_SUCCEEDED(ret))
                    {
                    printf("Satellite details deleted successfully.\n");
                    }
                else
                    {
                    printf("Failed to execute delete statement.\n");
                    }
                closeConnection(hEnv, hDbc);
                } 
            }
        } 
    }
} 

