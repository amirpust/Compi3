#ifndef HW3_EXP_T_H
#define HW3_EXP_T_H

#include <iostream>
#include <string>
#include "hw3_output.hpp"
#include "Enums.h"

class Exp_t{
public:
    TYPE t;
    int i;
    string s;

    Exp_t():t(E_bool), i(0), s(){};

    explicit Exp_t(TYPE t) : t(t) {};
    explicit Exp_t(bool i) : t(E_bool), i(i) {
        cout << "BOOL" << endl;
    };
    explicit Exp_t(int i, TYPE t = E_int) : t(t), i(i) {
        if (t == E_byte && i >= (1 << 8)){
            output::errorByteTooLarge(lineno, i);
            exit(1); //TODO: exception
        }
        cout << "INT/BYTE" << endl;
    };
    explicit Exp_t(string _str) : t(E_string), s(_str) {
        cout << "TEST: " << _str << endl;
    }
    Exp_t(const Exp_t& c) : t(c.t), i(c.i), s(c.s) {
        if (t == E_byte && i >= (1 << 8)){
            output::errorByteTooLarge(lineno, i);
            exit(1); //TODO: exception
        }
        cout << "COPY " << endl;

    }

    bool isNumerical() const{
        return t == E_int || t == E_byte;
    }
    TYPE getDualType(const Exp_t& e) const {
        if (t == E_byte && e.t == E_byte)
            return E_byte;

        return E_int;
    }
    bool castType(TYPE newT){
        if (newT == E_int && t == E_byte){
            t = E_int;
            return true;
        }
        if (t == newT){
            return true;
        };

        return false;
    }
    bool bothAreOrArentStrings(TYPE t2){
        return (t == t2) || (t != E_string && t2 != E_string);
    }
    void printFullExp(){
        cout << "{"
             << "type: " << t
             << ", int: " << i
             << ", string: " << s
             << "}" << endl;
    }

    Exp_t& operator=(const Exp_t& e) = default;
    Exp_t operator+(const Exp_t& e) const {
        if(!isNumerical() || !e.isNumerical()){
            //TODO: exception
        }

        //TODO: check overflow
        return Exp_t(i + e.i, getDualType(e)) ;
    }
    Exp_t operator-(const Exp_t& e) const {
        if(!isNumerical() || !e.isNumerical()){
            //TODO: exception
        }

        //TODO: check overflow
        return Exp_t(i - e.i, getDualType(e)) ;
    }

    bool operator==(const Exp_t& e){
        if ( isNumerical() && e.isNumerical()){
            return i == e.i;
        }
        if (t == E_bool && e.t == E_bool){
            return i == e.i;
        }
        if ( t == E_string && e.t == E_string){
            return s == e.s;
        }
        //TODO - exception
        return false;
    }
    bool operator<=(const Exp_t& e){
        if (!isNumerical() || !e.isNumerical()){
            //TODO: exception
        }

        return t <= e.t;
    }
    bool operator<(const Exp_t& e){
        if (!isNumerical() || !e.isNumerical()){
            //TODO: exception
        }

        return t < e.t;
    }
};

typedef vector<Exp_t> ExpList;


#endif //HW3_EXP_T_H
