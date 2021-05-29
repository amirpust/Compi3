#ifndef U_HPP
#define U_HPP

#include <iostream>
using namespace std;

enum TYPE {
    E_bool,
    E_byte,
    E_int,
    E_string
};

class Exp_t{
public:
    TYPE t;

    Exp_t(TYPE _t) : t(_t) {};
    virtual void* getVal() = 0;
};

class Integer_t : public Exp_t{
public:
    int val;

    Integer_t(int _val) : Exp_t(E_int), val(_val);
    Integer_t(char * val) {
        cout << "Integer_t c'tor" << val << endl;
    }
    void* getVal() { return &val; }
};

class Bool_t : public Exp_t{
public:
    bool val;

    Integer_t(bool _val) : val(_val), t(E_int);
    void* getVal() { return &val; }
};

class String_t : public Exp_t{
public:
    char* val;

    Integer_t(char* _val) : val(_val), t(E_int);
    void* getVal() { return val; }
};

typedef struct objects_pool_t{
    Integer_t integerVal;
    Bool_t boolVal;
    String_t stringVal;

    Exp_t expVal;

}objects_pool;

#define YYSTYPE objects_pool

#endif
