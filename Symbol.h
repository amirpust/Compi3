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

    Symbol(string _id, Exp_t _exp, int _offset, vector<Symbol> _symbolList = vector<Symbol>()):
            id(_id), exp(_exp), offset(_offset), symbolList(_symbolList){};

    Symbol(string _id, TYPE t): id(_id), exp(t){};

};

#endif //HW3_SYMBOL_H
