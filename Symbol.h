//
// Created by Amir on 29/05/2021.
//

#ifndef HW3_SYMBOL_H
#define HW3_SYMBOL_H


#include "Enums.h"
#include "Exp_t.h"
#include <string>
#include <vector>

using namespace std;

class Symbol{
public:
    string id;
    Exp_t exp;
    int offset;
    vector<Symbol> symbolList;
    bool isFunc;

    Symbol():id(),exp(),offset(0),symbolList(){};

    //c'tor of regular symbol
    Symbol(string _id, Exp_t _exp, int _offset):
            id(_id), exp(_exp), offset(_offset),isFunc(false){};


    //created for Jonathan
    Symbol(string _id, TYPE t): id(_id), exp(t),isFunc(false){};

    Symbol(TYPE t): exp(t), isFunc(false){};

    //creates a symbol of function, which means it holds a argument list that
    // will be used to make sure that when this function is being called
    // all the args that are passed are type valid
    Symbol(string _id, int _offset, vector<Symbol> _symbolList, Exp_t _exp, bool _isFunc):
    id(_id), exp(_exp), offset(_offset), symbolList(_symbolList), isFunc(_isFunc){};

    vector<string> getSymListTypes(){
        vector<string> types = vector<string>();
        for (int i = 0; i < symbolList.size(); ++i) {
            types.emplace_back(printType[symbolList[i].exp.t]);
        }
        return types;
    }

    Symbol(const Symbol& s):exp(s.exp.t){
        id = s.id;
        offset = s.offset;
        symbolList = s.symbolList;
        isFunc = s.isFunc;
    }

    Symbol operator=(Symbol& s){
        id = s.id;
        exp = s.exp;
        offset = s.offset;
        symbolList = s.symbolList;
        isFunc = s.isFunc;

        return (*this);
    }
};



typedef vector<Symbol> SymList;

#endif //HW3_SYMBOL_H
