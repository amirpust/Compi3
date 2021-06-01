#ifndef HW3_ENUMS_H
#define HW3_ENUMS_H

#include <string>


extern int lineno;

enum TYPE {
    E_bool,
    E_byte,
    E_int,
    E_string,
    E_void
};

std::string printType[] = {
        "BOOL",
        "B",
        "INT",
        "STRING",
        "VOID"
};

enum RELOP_ENUM{
    E_L,
    E_G,
    E_LOE,
    E_GOE
};

enum SCOPE_REASON{
    GLOBAL_SCOPE,
    REGULAR_SCOPE,
    IF_SCOPE,
    CASE_SCOPE,
    SWITCH_SCOPE,
    LOOP_SCOPE
};


#endif //HW3_ENUMS_H
