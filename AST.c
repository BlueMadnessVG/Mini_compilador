#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct Exp
{
    enum
    {
        integer_exp,
        string_exp,
        variable_exp,
        binary_exp,
        unary_exp,
        call_exp,
        projection_exp,
        record_exp
    } tag;
    union
    {
        int integerExp;
        char stringExp;
        char variableExp;  
        struct
        {
            char operator;
            struct Exp* left;
            struct Exp* right;
        } binaryExp; 
        struct
        {
            char operator;
            struct Exp* operand;
        } unaryExp;
        struct
        {
            char name;
            struct Exp_list* arguments;
        } callExp;
        struct
        {
            struct Exp* record;
            char attribute;
        } projectionExp;
        struct rec
        {
            char attribute;
            struct Exp* value;
            struct rec* next;
        } recordExp;
    } op;
} ast;

typedef struct Exp_list
{
  ast* elem;
  struct Exp_list* next;
} ast_list;


static ast* make_binaryExp ( char operator, ast* left, ast* right )
{
    ast* e = (ast*) malloc(sizeof(ast));
    e->tag = binary_exp;
    e->op.binaryExp.operator = operator;
    e->op.binaryExp.left = left;
    e->op.binaryExp.right = right;
    return e;
};

static ast* make_integerExp(int value)
{
    ast* e = (ast*) malloc(sizeof(ast));
    e->tag = integer_exp;
    e->op.integerExp = value;
    return e;
}


int main()
{
    make_binaryExp("+",
                   make_binaryExp("-",
                                  make_variableExp("x"),
                                  make_integerExp(2)),
                    make_integerExp(3));
    return 0;
}