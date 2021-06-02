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
};

class Symbol : public BaseObj {
public:
    ID id;
    Type t;

    Symbol(const ID &id, const Type &t);

    Symbol(const Symbol& _sym);
};

class SymList : public BaseObj {
public:
    vector<Symbol> symList;

    SymList(const vector<Symbol> &symList);
    SymList();

    void insert(Symbol sym){
        symList.push_back(sym);
    }
};

#define YYSTYPE BaseObj*
#endif //HW3_BASEOBJ_HPP
