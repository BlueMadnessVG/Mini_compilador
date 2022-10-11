//CODIGO DE LECTURA DE ARCHIVOS EN C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "listaenlazada.h"


enum TipoToken
{
    PalRes,
    Id,
    Num,
    Sim,
    text
};

//estrucutra de datos para el token
struct TokenStruc
{
    char Nombre[80];
    enum TipoToken Tipo;
    char Lexema[80];
    int Valor;
    int NoLin;
    int NoCol;
};

int crear_token(char Nombre[80], enum TipoToken Tipo, char Lexema[80], int valor, int NoLin, int NoCoL){

    struct TokenStruc new_token;
    strcpy(new_token.Nombre, Nombre);
    strcpy(new_token.Lexema, Lexema);
    new_token.Tipo = Tipo;
    new_token.Valor = valor;
    insertarnodo(new_token);
    return 1;
}
