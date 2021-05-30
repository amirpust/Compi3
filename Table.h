#ifndef HW3_TABLE_H
#define HW3_TABLE_H

#include "Exp_t.h"
#include "Enums.h"
#include "Symbol.h"
#include <string>
#include <vector>
using namespace std;

class Scope{
public:
    vector<Symbol> symbols;
    int offset;
    bool isFunc;

    Scope(int _offset, bool _isFunc = false): symbols(), offset(_offset), isFunc(false){};

    void insert(string id, Exp_t exp){
        symbols.emplace_back(id, exp,offset++);
    }

    void insert(string id, SymList declArgs, TYPE ret){
        symbols.emplace_back(id,offset++);
    }

    bool isExist(string id){
        for(int i = 0; i < symbols.size(); i++){
            if(symbols[i].id == id)
                return true;
        }
        return false;
    }

    vector<Symbol> getArgs(string funcName){
        for(int i = 0; i < symbols.size(); i++){
            if(symbols[i].id == funcName){
                return symbols[i].symbolList;
            }
        }
        return vector<Symbol>();
    }
};









class SymbolTable{
public:
    vector<Scope> scopes;
    SymbolTable(): scopes(){};

    void openNewScope(){
        scopes.emplace_back();
    }

    void openLoopScope(){
        scopes.emplace_back();
        //TODO
    }

    void openFuncScope(string id){
        //TODO
    }

    void openSwitchScope(Exp_t e){
        //TODO: remember it's a "switch loop", and check if e is byte/int/bool
        //see openCaseScope and SWITCH/Case rule to get more context
    }

    void openCaseScope(){
        //TODO: Check if inside a Switch Scope
        //TODO: remember it's a case scope
    }

    void callFunc(string funcName, ExpList arguments){
        openFuncScope(funcName, arguments);
    }

    void openFuncScope(string funcName, ExpList arguments){
        //TODO: Make sure this function doesn't open a new scope. Only check if the arguments ok
        //TODO: please move it to "callFunc" (the function above)

        scopes.emplace_back(-(arguments.size()), true);
        vector<Symbol> decArgs = vector<Symbol>();
        int scopeDecl;
        for(scopeDecl = scopes.size() - 1; scopeDecl >= 0; scopeDecl--){
            if(scopes[scopeDecl].isExist(funcName))
                decArgs = scopes[scopeDecl].getArgs(funcName);
            if(scopes[scopeDecl].isFunc)
                break; //TODO: func decl doesn't exists
        }

        if(decArgs.size() != arguments.size()) return; //TODO: throw exception

        for (int i = 0; i < decArgs.size(); ++i) {
            if(decArgs[i].exp.t != arguments[i].t)
                break; // TODO: throw exception types are not the same

            addSymbolWithExp(arguments[i].t, decArgs[i].id, arguments[i]);
        }

    }

    void closeCurrentScope(){
        if(!scopes.empty())
            scopes.pop_back();
    }

    void checkReturnType(TYPE t){
        //TODO
    }

    void triggerBreak(){
        //TODO: check if ok (don't close the scope)
        //trigger an error is not in loop/case (switch scope isn't enough)
    }

    void triggerContinue(){
        //TODO: check if ok (don't close the scope)
        //trigger an error is not in loop (switch scope isn't enough)
    }

    void addFuncSymbol(TYPE returnType, string funcName, SymList funcArgs){
        for(int i = scopes.size() - 1; i >= 0; i--){
            if(scopes[i].isExist(funcName))
                return; // TODO: it exists throw some exception
            if(scopes[i].isFunc)
                break; // TODO: it exists throw some exception
        }
        scopes.back().insert(funcName, funcArgs, returnType);
    }

    void addSymbol(TYPE t, string id){

        for(int i = scopes.size() - 1; i >= 0; i--){
            if(scopes[i].isExist(id)){
                return; // TODO: it exists throw some exception
            }
            if (scopes[i].isFunc)
                break;

        }
        scopes.back().insert(id, Exp_t(t));
    }


    void addSymbolWithExp(TYPE t, string id, Exp_t exp){
        exp.castType(t);

        // checks if the the id was already declared in outer scope
        for(int i = scopes.size() - 1; i >= 0; i--){
            if(scopes[i].isExist(id)){
                return; // TODO: it exists throw some exception
            }
            if (scopes[i].isFunc)
                break;
        }
        scopes.back().insert(id, exp);

    }

    Exp_t getExpByID(string id){
        //TODO: get back the Exp with the closest id name (Should be the only one)
    }

    void updateSymbol(string id, Exp_t exp){
    // TODO: update the symbol with
    }

    Symbol& searchSymbol(string id){
        // TODO: find the closest symbol with name id

    }

    //TODO: make every scope as pair with scope and reason(ENUM)


};

#endif //HW3_TABLE_H
