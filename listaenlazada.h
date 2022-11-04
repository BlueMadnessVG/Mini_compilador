#include "tokenstruc.h"
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

void imprimirlista(){
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


}