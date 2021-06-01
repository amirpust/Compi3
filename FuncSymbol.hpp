
#ifndef HW3_FUNCSYMBOL_H
#define HW3_FUNCSYMBOL_H

#endif //HW3_FUNCSYMBOL_H

#include "Enums.hpp"
#include "Exp_t.hpp"
#include "Symbol.hpp"
#include <string>
#include <vector>

using namespace std;

class FuncSymbol{
public:
    TYPE retType;
    string id;
    SymList symList;

    FuncSymbol(TYPE _retType, string& _id, SymList& _symList) :   retType(_retType),
                                                                id(_id),
                                                                symList(_symList)
                                                                {};
};

typedef vector<FuncSymbol> FuncList;