/* ifndef  is used to prevent multiple inclusion of header file*/
#ifndef satellite_h
#define satellite_h

#include <stdio.h>
#include "datetime.h"

typedef struct sat 
{
    char *class;
    char *name;
    datetime * launch_date;
    char *payload;
    char *space_agency;
    char *identifier_number;
    char *status;
} sat;

#endif
