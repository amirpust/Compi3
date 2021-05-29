#ifndef HW3_ENUMS_H
#define HW3_ENUMS_H

extern int lineno;

enum TYPE {
    E_bool,
    E_byte,
    E_int,
    E_string,
    E_void
};

enum RELOP_ENUM{
    E_L,
    E_G,
    E_LOE,
    E_GOE
};

class RelopAUX{
public:
    RELOP_ENUM op;
    RelopAUX(string& _op){
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

#endif //HW3_ENUMS_H
