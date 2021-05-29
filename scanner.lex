%{
	#include <stdio.h>
    #include "u.hpp"
    #include "parser.tab.hpp"
    #include "hw3_output.hpp"

    void printLexError();
    void output::errorLex(int lineno);
%}

%option yylineno
%option noyywrap

whitespace	                                        ([ \t\r\n])
noZeroDigit	                                        ([1-9])
digit		                                        ([0-9])
%%
void					                            return VOID;
int                                                 return INT;
byte                                                return BYTE;
b                                                   return B;
bool                                                return BOOL;
and                                                 return AND;
or                                                  return OR;
not                                                 return NOT;
true                                                return TRUE;
false                                               return FALSE;
return                                              return RETURN;
if                                                  return IF;
else                                                return ELSE;
while                                               return WHILE;
break                                               return BREAK;
continue                                            return CONTINUE;
switch                                              return SWITCH;
case                                                return CASE;
default                                             return DEFAULT;
:                                                   return COLON;
;                                                   return SC;
,                                                   return COMMA;
\(                                                  return LPAREN;
\)                                                  return RPAREN;
\{                                                  return LBRACE;
\}                                                  return RBRACE;
=                                                   return ASSIGN;
"<"|">"|"<="|">="                                   return RELOP;
"=="|"!="                                           return EQUALITY;
"*"|"/"                                             return BINOP_MD;
"+"|"-"                                             return BINOP_PM;
[a-zA-Z][a-zA-Z0-9]*                                return ID;
{noZeroDigit}{digit}*                               {return NUM;}
0                                                   return NUM;
\"([^\n\r\"\\]|\\[rnt"\\])+\"                       {if (!yytext) yylval.expVal = Exp_t(string(yytext)); return STRING;}
\/\/[^\r\n]*(\r|\n|\r\n)?                           ;
{whitespace}                                        ;
.                                                   printLexError();
%%

void printLexError(){
    output::errorLex(yylineno);
    exit(0);
}