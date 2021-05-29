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
    bool b;

    Exp_t() : t(E_bool) {
        cout << "DEFAULT" << endl;
    };

    Exp_t(bool b) : b(b), t(E_bool) {
        cout << "BOOL" << endl;
    };

    Exp_t(char* test) {
        cout << "TEST:" << test << endl;
    }

    Exp_t(Exp_t& test) {
        cout << "Copy" << endl;
    }
};

typedef struct objects_pool_t{
    Exp_t expVal;
}objects_pool;

#define YYSTYPE objects_pool

#endif
