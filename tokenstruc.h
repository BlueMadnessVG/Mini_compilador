#include "listaenlazada.h"
//tipos de datos que puede tomar el token
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
};

int crear_token(char Nombre[80], enum TipoToken Tipo, char Lexema[80], int valor, int NoLin){

    struct TokenStruc new_token;
    strcpy(new_token.Nombre, Nombre);
    strcpy(new_token.Lexema, Lexema);
    new_token.Tipo = Tipo;
    new_token.Valor = valor;
    new_token.NoLin = NoLin;
    insertarnodo(new_token);
    return 1;
}