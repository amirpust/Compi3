#ifndef HW3_TABLE_HPP
#define HW3_TABLE_HPP

#include "Enums.hpp"
#include "Exp_t.hpp"
#include "Symbol.hpp"
#include "FuncSymbol.hpp"
#include <string>
#include <vector>
#include "hw3_output.hpp"
#include <stack>

extern int yylineno;

using namespace std;

class Scope{
public:
    SymList symList;
    int offest;
    SCOPE_REASON type;

    Scope(int _offest, SCOPE_REASON _type) :
            symList(),
            offest(_offest),
            type(_type) {};
};

typedef vector<Scope> ScopeList;

class SymbolTable{
public:
    ScopeList scopeList;
    FuncList funcList;
    bool seenMainFunc;
    stack<int> offsets;
    int cases;

    SymbolTable() : scopeList(), funcList(), seenMainFunc(false) , offsets() , cases(0){
        scopeList.emplace_back(0, GLOBAL_SCOPE);
        funcList.emplace_back(E_void, string("print"), SymList(1, Symbol(string("mockId"), E_string)));
        funcList.emplace_back(E_void, "printi", SymList(1, Symbol("mockId", E_int)));
        offsets.push(0);
    };

    void checkMain(){
        if(!seenMainFunc)
            output::errorMainMissing();
        exit(1);
    }

    // open scopes
    void openNewScope(SCOPE_REASON type = REGULAR_SCOPE){
        scopeList.emplace_back(offsets.top(), type);
        offsets.push(offsets.top());
    }
    void openLoopScope(){
        openNewScope(LOOP_SCOPE);
    }
    void openSwitchScope(Exp_t e) {
        if (e.t != E_byte && e.t != E_int) {
            output::errorMismatch(lineno);
            exit(1);
        }

        openNewScope( SWITCH_SCOPE);
    }
    void openFuncScope(string id, SymList args, TYPE retType) {
        if ((retType == E_void) && (id == "main") && args.empty()){
            seenMainFunc = true;
        }

        if (findFunc(id) != funcList.end()){
            output::errorDef(lineno, id);
            exit(1);
        }

        funcList.emplace_back(retType, id, args);
        offsets.push(0);
    }

    // triggers
    void triggerCase(){
        cases++ ;
    }
    void triggerBreak(){
        for(ScopeList::iterator i = scopeList.begin(); i != scopeList.end(); i++){
            if ((*i).type == LOOP_SCOPE || (*i).type == SWITCH_SCOPE){
                cases = 0;
                return;
            }
        }

        output::errorUnexpectedBreak(yylineno);
        exit(-1);
    }
    void triggerContinue(){
        for(ScopeList::iterator i = scopeList.begin(); i != scopeList.end(); i++){
            if ((*i).type == LOOP_SCOPE){
                return;
            }
        }
        output::errorUnexpectedContinue(yylineno);
        exit(-1);
    }

    Exp_t callFunc(string funcName, ExpList arguments) {
        if(findFunc(funcName) == funcList.end()){
            output::errorUndefFunc(lineno, funcName);
            exit(1);
        }

        SymList sArgs = SymList();
        for (ExpList::iterator a = arguments.begin(); a != arguments.end(); a++){
            sArgs.emplace_back("mockId", (*a).t);
        }

        FuncSymbol func = *findFunc(funcName);
        std::vector<string> strTypes = std::vector<string>();
        for (SymList::iterator i = func.symList.begin(); i != func.symList.end(); i++){
            strTypes.push_back(typeStr[(int)((*i).second)]);
        }

        if(sArgs.size() != func.symList.size()){
            output::errorPrototypeMismatch(yylineno, funcName, strTypes);
            exit(-1);
        }


        for (int i = 0; i < sArgs.size(); ++i) {
            if(sArgs[i].second != func.symList[i].second){
                output::errorPrototypeMismatch(yylineno, funcName, strTypes);
                exit(-1);
            }
        }

        return Exp_t(func.retType);
    }
    void closeCurrentScope(){
        if(scopeList.size() <= 1 && !seenMainFunc){
            output::errorMainMissing();
            exit(-1);
        }

        output::endScope();
        Scope closingScope = scopeList.back();

        for (int i = 0; i < closingScope.symList.size(); ++i) {
            string typeForPrinting = typeStr[(int)(closingScope.symList[i].second)];
            output::printID(closingScope.symList[i].first, offsets.top()--, typeForPrinting);
        }

        scopeList.pop_back();
    }
    void checkReturnType(Exp_t exp){
        if(!exp.castType(funcList.back().retType)){
            output::errorMismatch(yylineno);
            exit(1);
        }
    }
    void addSymbol(TYPE t, string& id){
        if(isId(id)) {
            output::errorDef(yylineno, id);
            exit(-1);
        }

        scopeList.back().symList.emplace_back(id, t);
        offsets.top()++;
    }

    TYPE getTypeByID(string& _id){
        Symbol* sym = findSym(_id);
        if(!sym){
            output::errorUndef(lineno, _id);
            exit(-46);
        }
        return sym->second;
    }
    Exp_t getExpByID(string& _id){
        return Exp_t(getTypeByID(_id));
    }
    void assign(string& _id, Exp_t e){
        Symbol* sym = findSym(_id);
        if(!sym){
            output::errorUndef(lineno, _id);
            exit(-463);
        }
        Exp_t newE = Exp_t(sym->second);
        newE = e;
    }

private:
    FuncList::iterator findFunc(string& _id){
        for (FuncList::iterator f = funcList.begin(); f != funcList.end(); f++){
            if (f->id == _id){
                return f;
            }
        }
        return funcList.end();
    }
    Symbol* findSym(string& _id){
        for(ScopeList::iterator scope = scopeList.begin(); scope != scopeList.end(); scope++){
            for(SymList::iterator sym = (*scope).symList.begin(); sym != (*scope).symList.end() ; sym++){
                if ((*sym).first == _id){
                    return &(*sym);
                }
            }
        }

        return NULL;
    }
    bool isId(string _id){
        return findSym(_id) || findFunc(_id) != funcList.end();
    }
};

#endif //HW3_TABLE_HPP
