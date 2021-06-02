#ifndef HW3_EXP_T_HPP
#define HW3_EXP_T_HPP

#include <iostream>
#include <string>
#include "hw3_output.hpp"
#include "Enums.hpp"

class Exp_t{
public:
    TYPE t;
    Exp_t():t(E_bool) {};
    explicit Exp_t(TYPE t) : t(t) {};
    Exp_t(TYPE t, int i) : t(t) {
        if ( t == E_byte && i >= (1 << 8)){
            output::errorByteTooLarge(lineno, i);
            exit(5456);
        }
    };
    Exp_t(const Exp_t& c) = default;

    bool isNumerical() const{
        return t == E_int || t == E_byte;
    }
    TYPE getDualType(const Exp_t& e) const {
        if (t == E_byte && e.t == E_byte)
            return E_byte;

        return E_int;
    }
    bool castType(TYPE newT){
        if(newT == E_void || t == E_void){
            output::errorMismatch(lineno);
            *output::logFile << "Casting void" << endl;
            exit(1);
        }
        if (newT == E_int && t == E_byte){
            t = E_int;
            return true;
        }
        if (t == newT){
            return true;
        };

        return false;
    }

    Exp_t& operator=(const Exp_t& e){
        if (!Exp_t(e).castType(t)){
            output::errorMismatch(lineno);
            exit(-1);
        }
        return (*this);
    };
    /*
    Exp_t operator+(const Exp_t& e) const {
        if(!isNumerical() || !e.isNumerical()){
            exit(621);
        }

        return Exp_t(getDualType(e)) ;
    }
    Exp_t operator-(const Exp_t& e) const {
        if(!isNumerical() || !e.isNumerical()){
        }

        return Exp_t(getDualType(e)) ;
    }
    */
    /*
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
        return false;
    }
    bool operator<=(const Exp_t& e){
        if (!isNumerical() || !e.isNumerical()){
        }

        return t <= e.t;
    }
    bool operator<(const Exp_t& e){
        if (!isNumerical() || !e.isNumerical()){
        }

        return t < e.t;
    } */
};

typedef vector<Exp_t> ExpList;


#endif //HW3_EXP_T_HPP
