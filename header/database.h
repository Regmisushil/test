#ifndef database_h
#define database_h

#include <sql.h>
#include <sqlext.h>

SQLHDBC connectToDB(SQLHENV *hEnv);
void viewStatement(SQLHDBC hDbc, const char *query);
SQLRETURN executeStatement(SQLHDBC hDbc, const char *query, SQLLEN *rowCount);
void closeConnection(SQLHENV hEnv, SQLHDBC hDbc);
void del_sat();


#endif