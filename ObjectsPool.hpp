#ifndef U_HPP
#define U_HPP

#include <iostream>
#include <string>
#include "hw3_output.hpp"
#include "Enums.h"
#include "RelopAUX.h"
#include "Exp_t.h"
#include "Table.hpp"

using namespace std;
extern int lineno;

typedef struct objects_pool_t{
    Exp_t expVal;
    string idVal;

    int intVal;
    bool boolVal;
    string stringVal;
    ExpList expList;
    RelopAUX relopAUX;
    TYPE typeVal;
    Symbol symbol;
    SymList symList;
    objects_pool_t(){

    }
}objects_pool;

#define YYSTYPE objects_pool

#endif
