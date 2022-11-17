//CODIGO DE LECTURA DE ARCHIVOS EN C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// #include "AutomatasL.h"
// #include "CrearTokens.h"
// #include "ObtenerToken.h"
// #include "AutomatasS.h"
// #include "ComprobarSintaxis.h"



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
        record_exp,
        cuerpo_exp,
        asigvar_exp,
        asigcons_exp,
        mientras_exp,
        si_exp,
        sino_exp,
        pantalla_exp,
        teclado_exp
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
        struct
        {
            char* cuerpo;
            char llave;
            struct Exp* bloque;
            char llave_c;
        } cuerpoExp;

        struct
        {
            char* var;
            char* tipodato;
            char* ident;
            char igual;
            union{
                struct
                {
                    char operator;
                    struct Exp* left;
                     struct Exp* right;
                } binaryExp;
                int valorint;
                double valordec;
                char* valorcad;
            }valor;
        } asigvar;
        
        struct
        {
            char* cons;
            char* tipodato;
            char* ident;
            char igual;
            union{
                struct
                {
                    char operator;
                    struct Exp* left;
                     struct Exp* right;
                } binaryExp;
                int valorint;
                double valordec;
                char* valorcad;
            }valor;
        }asigconst;
        
        struct
        {
            char* mientras;
            char par1;
            struct
                {
                    char operator;
                    struct Exp* left;
                     struct Exp* right;
                } binaryExp;
            char par2;
            char llave1;
            struct Exp* bloque;
            char llave2; 
        } mientras;
        struct
        {
            char* si;
            char par1;
            struct
                {
                    char operator;
                    struct Exp* left;
                     struct Exp* right;
                } binaryExp;
            char par2;
            char llave1;
            struct Exp* bloque;
            char llave2; 
        } si;
        struct 
        {
            char* sino;
            char llave1;
            struct Exp* bloque;
            char llave2;
        }sino;

        struct 
        {
            char* teclado;
            char par1;
            char* ident;
            char par2;
        }teclado;
        struct 
        {
            char* pantalla;
            char par1;
            union{
                char* ident;
                char* cadena;
            }impr;
            char par2;
        }pantalla;
        
    } op;
} ast;

typedef struct Exp_list
{
  ast* elem;
  struct Exp_list* next;
} ast_list;


ast* make_binaryExp ( char operator, ast* left, ast* right )
{
    ast* e = (ast*) malloc(sizeof(ast));
    e->tag = binary_exp;
    e->op.binaryExp.operator = operator;
    e->op.binaryExp.left = left;
    e->op.binaryExp.right = right;
    printf("%s\n", e->op.binaryExp);
    return e;
};

ast* make_integerExp(int value)
{
    ast* e = (ast*) malloc(sizeof(ast));
    e->tag = integer_exp;
    e->op.integerExp = value;
    printf("%d\n", e->op.integerExp);
    return e;
}

ast* make_cuerpoExp( char* cuerpo, ast* bloque ) {

    ast* e = (ast*) malloc(sizeof(ast));
    e->tag = cuerpo_exp;
    e->op.cuerpoExp.cuerpo = "cuerpo";
    e->op.cuerpoExp.llave = '{';
    e->op.cuerpoExp.bloque = bloque;
    e->op.cuerpoExp.llave_c = '}';
    printf("%s\n", e->op.cuerpoExp.cuerpo);
    return e;
}

ast* make_asigvar( char* var, char* tipodato,char* ident,char igual) {

    ast* e = (ast*) malloc(sizeof(ast));
    e->tag=asigvar_exp;
    e->op.asigvar.var="var";
    e->op.asigvar.tipodato=tipodato;
    e->op.asigvar.ident=ident;
    e->op.asigvar.igual='=';
   // e->op.asigvar.valor= falta aqui asignar el valor de la union
  //  printf("%s\n", e->op.cuerpoExp.cuerpo);
    return e;
}

ast* make_const( char* const, char* tipodato,char* ident,char igual) 
{

    ast* e = (ast*) malloc(sizeof(ast));
    e->tag=asigcons_exp;
    e->op.asigconst.cons="const";
    e->op.asigconst.ident=ident;
    e->op.asigconst.tipodato=tipodato;
    e->op.asigconst.igual='=';
   // e->op.asigvar.valor= falta aqui asignar el valor de la union
    //printf("%s\n", e->op.cuerpoExp.cuerpo);
    return e;
}

ast* make_mientras( char oper, ast* bloque,ast* left,ast*right) {

    ast* e = (ast*) malloc(sizeof(ast));
    e->tag=mientras_exp;
    e->op.mientras.mientras="mientras";
    e->op.mientras.par1='(';
    e->op.mientras.binaryExp.operator=oper;
    e->op.mientras.binaryExp.left=left;
    e->op.mientras.binaryExp.right=right;
    e->op.mientras.par2=')';
    e->op.mientras.llave1='{';
    e->op.mientras.bloque=bloque;
    e->op.mientras.llave2='}';
   // e->op.asigvar.valor= falta aqui asignar el valor de la union
  //  printf("%s\n", e->op.cuerpoExp.cuerpo);
    return e;
}
ast* make_si( char oper, ast* bloque,ast* left,ast*right) {

    ast* e = (ast*) malloc(sizeof(ast));
    e->tag=si_exp;
    e->op.si.si="si";
    e->op.si.par1='(';
    e->op.si.binaryExp.operator=oper;
    e->op.si.binaryExp.left=left;
    e->op.si.binaryExp.right=right;
    e->op.si.par2=')';
    e->op.si.llave1='{';
    e->op.si.bloque=bloque;
    e->op.si.llave2='}';
   // e->op.asigvar.valor= falta aqui asignar el valor de la union
  //  printf("%s\n", e->op.cuerpoExp.cuerpo);
    return e;
}

ast* make_sino(ast* bloque){
ast* e = (ast*) malloc(sizeof(ast));
    e->tag=sino_exp;
    e->op.sino.sino="sino";
    e->op.sino.llave1='{';
    e->op.sino.bloque=bloque;
    e->op.sino.llave2='}';

}



int main()
{

    make_cuerpoExp( aux->info.Lexema, make_integerExp(2));
    return 0;
/*
    //toma el archivo de texto
    arch = fopen("archivo.txt", "r");

    if(arch == NULL)
    {
        printf("Error de apertura del archivo. \n\n");
    }
    else
    {
        printf("=== VALIDACION DE LEXICO === \n\n");

        comprobar_lexico();

        printf("\n\n=== VALIDACION DE LEXICO === \n\n");

        printf("\n\n=== VALIDACION DE SINTAXIS === \n\n");
        comprobar_sintaxis();

        printf("\n\n=== VALIDACION DE SINTAXIS === \n\n");

    }

    //CERRAR EL ARCHIVO *IMPORTANTE*
    fclose(arch);*/
    return 0;
}
