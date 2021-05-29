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

    Symbol(string _id,TYPE _t, bool _val, int _offset): id(_id), t(_t), boolVal(_val), offset(_offset){};
    Symbol(string _id,TYPE _t, int _val, int _offset): id(_id), t(_t), intVal(_val), offset(_offset){};
    Symbol(string _id,TYPE _t, string _val, int _offset): id(_id), t(_t), strVal(_val), offset(_offset){};
};

class Scope{

public:
    vector<Symbol> symbols;
    int offset;
    bool isFunc;

    Scope(int _offset): symbols(), offset(_offset){};

    void insert(string id, TYPE t, bool val){
        symbols.emplace_back(id, t, val, offset++);
    }
    void insert(string id, TYPE t, int val){
        symbols.emplace_back(id, t, val, offset++);
    }
    void insert(string id, TYPE t, string val){
        symbols.emplace_back(id, t, val, offset++);
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
