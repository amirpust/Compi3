#ifndef U_HPP
#define U_HPP

typedef union
{
    int val;
    char op[100];
}u;

#define YYSTYPE u

#endif
