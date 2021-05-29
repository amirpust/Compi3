#ifndef HW3_TABLE_H
#define HW3_TABLE_H

#include "u.hpp"
#include <vector>
class Symbol{
public:
    string id;
    Exp_t exp;
    int offset;
    vector<Symbol> symbolList;

    Symbol(string _id, Exp_t _exp, int _offset, vector<Symbol> _symbolList = vector<Symbol>()):
    id(_id), exp(_exp), offset(_offset), symbolList(_symbolList){};

};

class Scope{

public:
    vector<Symbol> symbols;
    int offset;
    bool isFunc;

    Scope(int _offset, bool _isFunc = false): symbols(), offset(_offset), isFunc(false){};

    void insert(string id, Exp_t exp){
        symbols.emplace_back(id, exp,offset++);
    }

    bool isExist(string id){
        for(int i = 0; i < symbols.size(); i++){
            if(symbols[i].id == id)
                return true;
        }
        return false;
    }

};

class SymbolTable{
public:
    vector<Scope> scopes;
    SymbolTable(): scopes(){};

    void openNewScope(){
        scopes.emplace_back();
    }

    void openFuncScope(string funcName, ExpList arguments){

    }

    void closeCurrentScope(){
        if(!scopes.empty())
            scopes.pop_back();
    }

    void addFuncSymbol(TYPE returnType, string funcName, ExpList funcArgs){
        for(int i = scopes.size() - 1; i >= 0; i--){
            if(scopes[i].isExist(funcName))
                return; // TODO: it exists throw some exception
            if(scopes[i].isFunc)
                break;
        }

    }

    void addSymbol(string id, TYPE t, int val, bool isFunc){

        // checks if the the id was already declared in outer scope
        for(int i = scopes.size() - 1; i >= 0; i--){
            if(scopes[i].isExist(id)){
                return; // TODO: it exists throw some exception
            }

        }

        if (!isFunc){
            scopes.back().insert(id,t,val);

        }
    }


};

#endif //HW3_TABLE_H
