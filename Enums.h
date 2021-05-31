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

enum SCOPE_REASON{
    REGULAR,
    IF,
    CASE,
    SWITCH,
    LOOP
};


#endif //HW3_ENUMS_H
