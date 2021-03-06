%{
	#include <stdio.h>
	#include <iostream>
    #include "Enums.hpp"
    #include "RelopAUX.hpp"
    #include "Exp_t.hpp"
    #include "Table.hpp"
    #include "ObjectsPool.hpp"



    #include "hw3_output.hpp"
    #include "parser.tab.hpp"

    void printLexError();
    void output::errorLex(int lineno);
    using namespace std;
%}

%option yylineno
%option noyywrap

whitespace	                                        ([ \t\r\n])
noZeroDigit	                                        ([1-9])
digit		                                        ([0-9])
%%
void					                            {yylval.typeVal = E_void; return VOID;}
int                                                 {yylval.typeVal = E_int; return INT;}
byte                                                {yylval.typeVal = E_byte; return BYTE;}
b                                                   {return B;   }
bool                                                {yylval.typeVal = E_bool; return BOOL;}
and                                                 {return AND; }
or                                                  {return OR;  }
not                                                 {return NOT; }
true                                                {yylval.boolVal = true; return TRUE;}
false                                               {yylval.boolVal = false; return FALSE;}
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
"<"|">"|"<="|">="                                   {yylval.relopAUX = RelopAUX(string(yytext)) ; return RELOP;}
"=="|"!="                                           return EQUALITY;
"*"|"/"                                             { yylval.intVal = (yytext[0] == '*' ) ; return BINOP_MD;}
"+"|"-"                                             { yylval.intVal = -1 ;if(yytext[0] == '+' ) yylval.intVal = 1; return BINOP_PM;}
[a-zA-Z][a-zA-Z0-9]*                                {yylval.idVal = string(yytext);  return ID;}
{noZeroDigit}{digit}*                               {yylval.intVal = stoi(yytext); return NUM;}
0                                                   {yylval.intVal = 0; return NUM;}
\"([^\n\r\"\\]|\\[rnt"\\])+\"                       {yylval.stringVal = string(yytext); return STRING;}
\/\/[^\r\n]*(\r|\n|\r\n)?                           ;
{whitespace}                                        ;
.                                                   printLexError();
%%

int lineno = yylineno;

void printLexError(){
    output::errorLex(yylineno);
    exit(0);
}