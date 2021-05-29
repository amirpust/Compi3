#ifndef U_HPP
#define U_HPP

#include <iostream>
#include <string>
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
    bool b;
    string str;

    Exp_t() : t(E_bool), str("") {
        cout << "DEFAULT" << endl;
    };

    Exp_t(bool b) : b(b), t(E_bool) {
        cout << "BOOL" << endl;
    };

    Exp_t(string _str) : str(_str) {
        cout << "TEST: " << _str << endl;
    }

    Exp_t(Exp_t& test) {
        cout << "Copy: " << test.str << endl;
    }
};

typedef struct objects_pool_t{
    Exp_t expVal;
    string idVal;
}objects_pool;

#define YYSTYPE objects_pool

#endif
