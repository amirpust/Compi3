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

    Symbol(string _id, TYPE t): id(_id), exp(t){};

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

    ExpList getArgs(string funcName){
        for(int i = 0; i < symbols.size(); i++){
            if(symbols[i].id == funcName){
                return symbols[i].symbolList;
            }
        }
        return ExpList();
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
        scopes.emplace_back(-arguments.size(), true);
        ExpList decArgs = ExpList();
        int scopeDecl;
        for(scopeDecl = scopes.size() - 1; scopeDecl >= 0; scopeDecl--){
            if(scopes[scopeDecl].isExist(funcName))
                decArgs = scopes[scopeDecl].getArgs(funcName);
            if(scopes[scopeDecl].isFunc)
                break; //TODO: func decl doesn't exists
        }

        if(decArgs.size() != arguments.size()) return; //TODO: throw exception

        for (int i = 0; i < decArgs.size(); ++i) {
            if(decArgs[i].t != arguments[i].t)
                break; // TODO: throw exception types are not the same

            addSymbol(decArgs[i].id, arguments[i])
        }

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

    void addSymbol(string id, Exp_t exp){

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
