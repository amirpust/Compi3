#ifndef U_HPP
#define U_HPP

typedef union
{
    int val;
    char op;
}u;

#define YYSTYPE u

#endif
