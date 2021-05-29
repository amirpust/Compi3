#ifndef HW3_EXP_T_H
#define HW3_EXP_T_H


class Exp_t{
public:
    TYPE t;
    int i;
    string s;

    Exp_t()  = default;

    Exp_t(TYPE t) : t(t) {};


    Exp_t(bool i) : t(E_bool), i(i) {
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

    Exp_t(const Exp_t& c) : t(c.t), i(c.i), s(c.s) {
        if (t == E_byte && i >= (1 << 8)){
            output::errorByteTooLarge(lineno, i);
            exit(1); //TODO
        }
        cout << "COPY " << endl;

    }

    void printFullExp(){
        cout << "{"
             << "type: " << t
             << ", int: " << i
             << ", string: " << s
             << "}" << endl;
    }

    bool operator==(const Exp_t& e){
        if (t == e.t){
            return i == e.i && s == e.s;
        }
        else{
            if ((t == E_byte && e.t == E_int) ||
                (t == E_int && e.t == E_byte)){
                return i == e.i;
            }
        }
        //TODO - exception
        return false;
    }

    bool operator<=(const Exp_t& e){
        if (t == e.t){
            return i <= e.i && s <= e.s;
        }
        else{
            if ((t == E_byte && e.t == E_int) ||
                (t == E_int && e.t == E_byte)){
                return i <= e.i;
            }
        }
        //TODO - exception
        return false;
    }
    bool operator<(const Exp_t& e){
        if (t == e.t){
            return i < e.i || s < e.s;
        }
        else{
            if ((t == E_byte && e.t == E_int) ||
                (t == E_int && e.t == E_byte)){
                return i < e.i;
            }
        }
        //TODO - exception
        return false;
    }

    void castType(TYPE newT){
        if( newT == E_void || newT == E_string ){
            //todo: exception
            return;
        }
        else{
            t = newT;
        }
    }

    bool bothAreOrArentStrings(TYPE t2){
        return (t == t2) || (t != E_string && t2 != E_string);
    }
};

typedef vector<Exp_t> ExpList;


#endif //HW3_EXP_T_H
