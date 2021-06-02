#ifndef HW3_BASEOBJ_HPP
#define HW3_BASEOBJ_HPP

#include <string>
#include "Enums.hpp"
#include <vector>
#include <utility>

using namespace std;

class BaseObj{
public:
    BaseObj() = default;
};

class ID : public BaseObj{
public:
    string id;
    ID(string _id) : id(_id) {};
};

class Type: public BaseObj {
public:
    TYPE t;
    Type(TYPE t);

    string getStr() const;

    bool operator==(const Type rhs) const;
    bool operator==(const TYPE rhs) const;
    bool operator!=(const Type rhs) const;
    bool operator!=(const TYPE rhs) const;
};

class Symbol : public BaseObj {
public:
    ID id;
    Type t;

    Symbol(const ID id, const Type t);

    Symbol(const Symbol& _sym);
};

class SymList : public BaseObj {
public:
    vector<Symbol> symList;

    SymList(const vector<Symbol> &symList);
    SymList();

    void insert(Symbol sym);

    typedef vector<Symbol>::iterator iterator;
};

class FuncSymbol : public BaseObj {
public:
    Type retType;
    ID id;
    SymList symList;

    FuncSymbol(Type _retType, ID _id, SymList _symList);;
};

class FuncList : public BaseObj {
public:
    vector<FuncSymbol> funcList;

    FuncList(vector<FuncSymbol> & _funcList);
    FuncList();;

    void insert(FuncSymbol func);

    typedef vector<FuncSymbol>::iterator iterator;
};

#define YYSTYPE BaseObj*
#endif //HW3_BASEOBJ_HPP
