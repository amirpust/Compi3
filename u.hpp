#ifndef U_HPP
#define U_HPP

enum TYPE {
    E_byte,
    E_int,
    E_string
};

typedef struct exp_t {
    TYPE t;

} exp_t;

typedef struct test_object_t{
    int val;
    char op[100];
    exp_t exp;
}test_object;
#define YYSTYPE test_object

#endif
