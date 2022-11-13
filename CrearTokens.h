#ifndef CREARTOKENS_H_INCLUDED
#define CREARTOKENS_H_INCLUDED

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

//estructura de datos para la lista enlazada

struct nodo
{
    struct TokenStruc info;
    //PUNTEROS
    struct nodo *izq;
    struct nodo *der;
};

//punto de inicio de la lista
struct nodo *raiz;
//punto actual de la lista
struct nodo *actual;
struct nodo *aux;
//METODO PARA INSERTAR UN NUEVO NODO A LA LISTA ENLAZADA
void insertarnodo(struct TokenStruc token)
{
    struct nodo *nuevo;
    //asigna un tamaño en memoria de tipo *nodo*
    nuevo = malloc(sizeof(struct nodo));

    nuevo -> info = token;
    nuevo -> izq = NULL;
    nuevo -> der = NULL;

    if(raiz == NULL)
    {
        raiz = nuevo;
        actual = nuevo;
    }
    else
    {
        nuevo -> izq = actual;
        actual -> der = nuevo;
        actual = nuevo;
    }

imprimirlista();
}

int imprimirlista(){
    aux=actual;
    while (aux!=NULL)
    {
        printf("\n--DATOS DEL TOKEN--\n\n");
        printf("LEXEMA ---> ");
        printf(aux->info.Lexema);
        printf("\nTIPO DE TOKEN ---> ");
        printf("%d", aux->info.Tipo);
        printf("\n");
        aux=aux->der;
    }

    return 0;
}

//variable goblal para leer el puntero del automata
FILE *arch;

int lineas = 1;
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

#endif // CREARTOKENS_H_INCLUDED
