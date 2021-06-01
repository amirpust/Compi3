#ifndef HW3_TABLE_HPP
#define HW3_TABLE_HPP

#include "Enums.h"
#include "Exp_t.h"
#include "Symbol.h"
#include <string>
#include <vector>
#include "hw3_output.hpp"

extern int yylineno;
using namespace std;

class Scope{
public:

    vector<Symbol> symbols;
    int offset;
    bool isFunc;
    TYPE retType;
    bool isCase;

    explicit Scope(int _offset, bool _isFunc = false, TYPE _retType = E_int): symbols(vector<Symbol>()),
    offset(_offset), isFunc(false), retType(_retType), isCase(false){};


    //  Scope(int _offset, bool _isFunc, SymList funcArgs, TYPE _retType): symbols(funcArgs),
    //  offset(_offset), isFunc(_isFunc, retType(_retType)){};
    //  inserting a symbol to the current scope
    void insert(string id, Exp_t exp){
        symbols.emplace_back(id, exp, offset++);
    }


    // inserting a function declaration to the current scope
    void insert(string id, Exp_t exp ,SymList declArgs){
        symbols.emplace_back(id,offset++,declArgs, exp, true);
    }


    // searches for the a symbol with name id in the current scope
    bool isExist(string id){
        for(auto & symbol : symbols){
            if(symbol.id == id)
                return true;
        }
        return false;
    }


    // searches for the function with name funcName and returns a list of args
    // that this func uses in its declaration (might be empty)
    SymList getArgs(string funcName){
        for(auto & symbol : symbols){
            if(symbol.id == funcName){
                return symbol.symbolList;
            }
        }
        return vector<Symbol>();
    }


    Symbol& getSymbol(string id){
        for (int i = symbols.size() - 1; i >= 0; --i) {
            if(id == symbols[i].id)
                return symbols[i];
        }

        cout << "not suppose to get here getSymbol in Scope class" << endl;
        exit(-1);
    }
};




class SymbolTable{
public:
    vector<pair<Scope, SCOPE_REASON>> scopes;
    bool seenMainFunc;


    // initializes the global scope
    SymbolTable(){
        pair<Scope, SCOPE_REASON > globalScope = make_pair(Scope(0),GLOBAL_SCOPE);
        scopes = vector<pair<Scope, SCOPE_REASON>>();
        scopes.push_back(globalScope);
        seenMainFunc = false;

        SymList printList = SymList();
        printList.emplace_back(E_string);
        scopes.back().first.insert("print",Exp_t(E_void), printList);

        SymList printIList = SymList();
        printList.emplace_back(E_int);
        scopes.back().first.insert("printi",Exp_t(E_void), printList);
    };


    ~SymbolTable(){
        if(!seenMainFunc)
            //TODO: throw an exception
            return;
    }


    // opens regular Scope, with latest offset of the last scope
    void openNewScope(){
        scopes.emplace_back(Scope(scopes.back().first.offset), REGULAR_SCOPE);
    }


    // opens a loo scope with latest offset of last scope
    void openLoopScope(){
        scopes.emplace_back(Scope(scopes.back().first.offset), LOOP_SCOPE);
    }


    // searches the above scopes for shadowing
    bool isShadowSymbolName(string id){
        for(int i = scopes.size() - 1; i >= 0; i--){
            if(scopes.back().first.isExist(id))
                return true;
            if(scopes.back().first.isFunc)
                break;
        }
        return false;
    }


    // the declaration of the func new offset is -args.size
    void openFuncScope(string id, SymList args, TYPE retType){
        if((retType == E_void) && (id == "main")) //TODO: args is empty
            seenMainFunc = true;

        if(isShadowSymbolName(id))
            return; //TODO: throw shadowing error

        // inserts the func to the current scope
        scopes.back().first.insert(id, Exp_t(retType), args);

        scopes.emplace_back(Scope(-args.size(), true, retType), REGULAR_SCOPE);

        for(auto & arg : args){
            scopes.back().first.insert(arg.id, arg.exp);
        }

    }


    // opens a switch scope with
    void openSwitchScope(Exp_t e) {
        if (e.t != E_bool && e.t != E_byte && e.t != E_int) {
            return; // TODO: throw exception e isn't byte/int/bool
        }

        scopes.emplace_back(Scope(scopes.back().first.offset), SWITCH_SCOPE);
    }


    void triggerCase(){
        for (int i = scopes.size() - 1; i >= 0; --i) {
            if(scopes[i].second == SWITCH_SCOPE){
                scopes[i].first.isCase = true;
                return; // it's ok
            }
            if(scopes[i].first.isFunc || scopes[i].second == GLOBAL_SCOPE){

                return; // TODO: throw exception "there isn't a switch scope"
            }

        }
    }


    void callFunc(string funcName, ExpList arguments) {
        //TODO: Make sure this function doesn't open a new scope. Only check if the arguments ok
        //TODO: please move it to "callFunc" (the function above)

        vector<Symbol> decArgs = vector<Symbol>();

        if(!isShadowSymbolName(funcName)){
            output::errorDef(yylineno, funcName);
            exit(-1);
        }

        Symbol func = getSymbolById(funcName);
        auto types = func.getSymListTypes();

        if(arguments.size() != func.symbolList.size()){

        }


        for (int j = 0; j < arguments.size(); ++j) {
            if(arguments[j].t != func.symbolList[j].exp.t){
                output::errorPrototypeMismatch(yylineno, funcName, types);
                exit(-1);
            }
        }
    }


    void closeCurrentScope(){
        if(scopes.back().second == GLOBAL_SCOPE && !seenMainFunc){
            output::errorMainMissing();
            exit(-1);
        }
        output::endScope();
        auto closingScope = scopes.back().first;
        for (int i = 0; i < closingScope.symbols.size(); ++i) {
            string typeForPrinting = printType[closingScope.symbols[i].exp.t];

            if(closingScope.symbols[i].isFunc){
                vector<string> args = closingScope.symbols[i].getSymListTypes();
                typeForPrinting = output::makeFunctionType(typeForPrinting, args);
            }

            output::printID(closingScope.symbols[i].id, closingScope.symbols[i].offset, typeForPrinting);
        }

        scopes.pop_back();
    }


    void checkReturnType(TYPE t){
        for (int i = scopes.size() - 1; i >= 0; --i) {
            if(scopes[i].first.isFunc){
                if(scopes[i].first.retType != t)
                    return; //TODO : type isn't like funcs retType
                return; //TODO: type is ok
            }
        }
    }


    void triggerBreak(){

        if(scopes.back().second == LOOP_SCOPE ||
        (scopes.back().second == SWITCH_SCOPE && scopes.back().first.isCase)){
            scopes.back().first.isCase = false;
            //TODO: it's OK
        }else{
            output::errorUnexpectedBreak(yylineno);
            exit(-1);
        }

    }


    void triggerContinue(){
        if(scopes.back().second != LOOP_SCOPE){
            output::errorUnexpectedContinue(yylineno);
            exit(-1);
        }
    }

    void addSymbol(TYPE t, string id){

        if(isShadowSymbolName(id)) {
            output::errorDef(yylineno, id);
            exit(-1);
        }
        scopes.back().first.insert(id, Exp_t(t));
    }


    void addSymbolWithExp(TYPE t, string id, Exp_t exp){
        exp.castType(t);

        // checks if the id was already declared in outer scope
        if(isShadowSymbolName(id)){
            output::errorDef(yylineno, id);
            exit(-1);
        }
        scopes.back().first.insert(id, exp);
    }


    Exp_t getExpByID(string id){
        //TODO: get back the Exp with the closest id name (Should be the only one)
        if(isShadowSymbolName(id)){
            return getSymbolById(id).exp;
        }
        return Exp_t(); // not suppose to get here
    }


    void updateSymbol(string id, Exp_t exp){
    // TODO: update the symbol with
    }


    Symbol& getSymbolById(string id){
        if(!isShadowSymbolName(id)){
            cout << "getSymbolById not suppose to get here" << endl;
            exit(-1);
        }
        for (int i = scopes.size() - 1; i >= 0 ; --i) {
            if(scopes[i].first.isExist(id)){
                return scopes[i].first.getSymbol(id);
            }
        }
        cout << "getSymbolById not suppose to get here : symbol not found" << endl;
        exit(-1);
    }

    // check if the id was declared earlier
    void checkUndefError(string id){
        if(!isShadowSymbolName(id)){
            output::errorUndef(yylineno, id);
            exit(-1);
        }
        Symbol s = getSymbolById(id);
        if(s.isFunc){
            output::errorUndef(yylineno, id);
            exit(-1);
        }
    }


    void checkUndefFunc(string id){
        if(!isShadowSymbolName(id)){
            output::errorUndefFunc(yylineno, id);
            exit(-1);
        }
        Symbol s = getSymbolById(id);
        if(!s.isFunc){
            output::errorUndefFunc(yylineno, id);
            exit(-1);
        }
    }



};

#endif //HW3_TABLE_HPP
