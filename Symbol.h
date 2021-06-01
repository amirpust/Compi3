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

    Symbol():id(),exp(),offset(0),symbolList(){};

    //c'tor of regular symbol
    Symbol(string _id, Exp_t _exp, int _offset):
            id(_id), exp(_exp), offset(_offset),symbolList(vector<Symbol>()){};


    //created for Jonathan
    Symbol(string _id, TYPE t): id(_id), exp(t){};

    Symbol(TYPE t): exp(t){};
    //creates a symbol of function, which means it holds a argument list that
    // will be used to make sure that when this function is being called
    // all the args that are passed are type valid
    Symbol(string _id, int _offset, vector<Symbol> _symbolList, Exp_t _exp):
    id(_id), exp(_exp), offset(_offset), symbolList(_symbolList){};


};


typedef vector<Symbol> SymList;

#endif //HW3_SYMBOL_H
