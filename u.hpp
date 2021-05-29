#ifndef U_HPP
#define U_HPP

#include <iostream>
#include <string>
#include "hw3_output.hpp"
using namespace std;
extern int lineno;

enum TYPE {
    E_bool,
    E_byte,
    E_int,
    E_string
};

class Exp_t{
public:
    TYPE t;
    bool b;
    int i;
    string s;

    Exp_t() : t(E_bool), s("") {
        cout << "DEFAULT" << endl;
    };

    Exp_t(bool b) : t(E_bool), b(b) {
        cout << "BOOL" << endl;
    };

    Exp_t(int i, TYPE t = E_int) : t(t), i(i) {
        if (t == E_byte && i >= (1 << 8)){
            output::errorByteTooLarge(lineno, i);
            exit(1); //TODO
        }
        cout << "INT/BYTE" << endl;
    };

    Exp_t(string _str) : t(E_string), s(_str) {
        cout << "TEST: " << _str << endl;
    }

    Exp_t(const Exp_t& c) : t(c.t), b(c.b), i(c.i), s(c.s) {
        if (t == E_byte && i >= (1 << 8)){
            output::errorByteTooLarge(lineno, i);
            exit(1); //TODO
        }
        cout << "COPY " << endl;

    }

    void printFullExp(){
        cout << "{"
            << "type: " << t
            << ", bool: " << b
            << ", int: " << i
            << ", string: " << s
            << "}" << endl;
    }
};

typedef struct objects_pool_t{
    Exp_t expVal;
    string idVal;

    int intVal;
    bool boolVal;
    string stringVal;
}objects_pool;

#define YYSTYPE objects_pool

#endif
