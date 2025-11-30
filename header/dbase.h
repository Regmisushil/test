#ifndef DBASE_H
#define DBASE_H

#include <sql.h>
#include <sqlext.h>

SQLHDBC connectToDB(SQLHENV *hEnv);
void viewStatement(SQLHDBC hDbc, const char *query);
SQLRETURN insertStatement(SQLHDBC hDbc, const char *query);
void closeConnection(SQLHENV hEnv, SQLHDBC hDbc);

#endif /* DBASE_H */
