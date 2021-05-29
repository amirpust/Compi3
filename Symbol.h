//
// Created by Amir on 29/05/2021.
//

#ifndef HW3_SYMBOL_H
#define HW3_SYMBOL_H


#include "Exp_t.h"
#include "Enums.h"
#include <string>
#include <vector>
using namespace std;

class Symbol{
public:
    string id;
    Exp_t exp;
    int offset;
    vector<Symbol> symbolList;
    TYPE returnType;

    Symbol(string _id, Exp_t _exp, int _offset):
            id(_id), exp(_exp), offset(_offset){};

    Symbol(string _id, TYPE t): id(_id), exp(t){};

    Symbol(string _id, int _offset, vector<Symbol> _symbolList, TYPE _returnType):
    id(_id), offset(_offset), symbolList(_symbolList), returnType(_returnType){};
};


typedef vector<Symbol> SymList;

#endif //HW3_SYMBOL_H
