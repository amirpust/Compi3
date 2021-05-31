#ifndef HW3_RELOPAUX_H
#define HW3_RELOPAUX_H

#include "Enums.h"
#include "Exp_t.h"

class RelopAUX{
public:
    RELOP_ENUM op;

    RelopAUX() : op(E_L) {};
    RelopAUX(const string& _op){
        if(_op == "<"){
            op = E_L;
        }
        if(_op == ">"){
            op = E_G;
        }
        if(_op == "<="){
            op = E_LOE;
        }
        if(_op == ">="){
            op = E_GOE;
        }
    };

    bool compare(Exp_t a, Exp_t b){
        switch (op){
            case E_G:
                return a < b;
            case E_L:
                return b < a;
            case E_GOE:
                return a <= b;
            case E_LOE:
                return b <= a;
        }
    }
};

#endif //HW3_RELOPAUX_H
