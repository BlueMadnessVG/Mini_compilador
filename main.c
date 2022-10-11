//CODIGO DE LECTURA DE ARCHIVOS EN C
#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "listaenlazada.h"
#include "tokenstruc.h"

//variable goblal para leer el puntero del automata
FILE *arch;
//AUTOMATA PARA CARACTERES ESPECIALES
int tipo_simbolo(char token[50]){

    int i;


    if (strlen(token) == 2){
        const char *simbolo[4] = {">=", "<=", "!=", "=="};

        for(i=0 ; i < 4; i++){
            if(strcmp(token, simbolo[i]) == 0){
                i = 4;

                crear_token("Tipo_sim", Sim, token, 0, 0, 0);
                return 1;
            }
        }
    }
    else{
        const char *simbolo[13] = {"+", "-", "*", "/", "%", ">", "<", "=", ";", "(", ")", "{", "}"};
        for(i=0 ; i < 13; i++){
            if(strcmp(token, simbolo[i]) == 0){
                i = 13;
                crear_token("Tipo_sim", Sim, token, 0, 0, 0);
                return 1;
            }
        }
    }

    return 0;
}

//AUTOMATA PARA NUMEROS
int tipo_numero(char token[50]){
    int i, punto = 0;
    if(isdigit(token[0])){

        for(i = 1; i < strlen(token); i++){
            if(isdigit(token[i]) == 0){

                int numero = (token[i] == '.');
                if(numero == 1 && punto == 0 && (i+1) < strlen(token) ){
                    punto = 1;
                }
                else{
                    return 0;
                }
            }
        }
    }
    else{
        return 0;
    }

    return 1;
}

//AUTOMATA PARA IDENTIFICADORES
int tipo_id(char token[50]){

    int i;
    if(isalpha(token[0])){
        for(i = 1; i < strlen(token); i++){
            if(isalnum(token[i]) == 0){
                printf("no es valido");
                return 0;
            }
        }
    }
    else{
        return 0;
    }
    return 1;
}

//AUTOMATA PARA PALABRAS RESERVADAS
int tipo_palabra(char token[50]){

    const char *palabras[14] = {"var", "const", "mientras", "fin", "si", "entero", "punto", "cadena", "funcion", "cuerpo", "lp", "pantalla", "teclado"};

    int i;
    for(i=0 ; i < 13; i++){
        if(strcmp(token, palabras[i]) == 0){
            i = 13;
            return 1;
        }
    }

    return 0;
}

//AUTOMATA PARA TEXTO PLANO
int tipo_textPlano(char token[50], char car)
{
    //CICLO PARA RECORRER TODO EL CARACTER
    while (car != '\"' && car != '\'')
    {
        strncat(token, &car, 1);
        car = fgetc(arch);

        if(car == '\n' || car  == EOF){
            car = fgetc(arch);
            printf("\n ERROR EN EL TOKEN INGRESADO \n");
            return 0;
        }
    }
    //GUARDA EL ULTIMO " O ' Y TOMA EL SIGUIENTE CARACTER
    strncat(token, &car, 1);

    crear_token("Tipo_texto_plano", text, token, 0, 0, 0);

    return 1;
}

//FUNCION PARA COMPROBAR EL TIPO DE TOKEN
int comprobar_token()
{

    char car;
    car = fgetc(arch);

    //CICLO PARA RECORRER TODO EL ARCHIVO
    while(car != EOF){

        //IDENTIFICAMOS CARACTERES ESPECIALES
        if (isspace(car) != 0){
            car = fgetc(arch);
        }
        else if (ispunct(car))
        {
            char token[50] = "";
            strncat(token, &car, 1);
            car = fgetc(arch);
            //LINEAS DE TEXTO ENTRE ""
            if (token[0] == '\"' || token[0] == '\''){

                if(tipo_textPlano(token, car) == 1){
                    car = fgetc(arch);
                }
                else{
                    car = fgetc(arch);
                }
                //crear el nuevo token
            }
            //CARACTERES ESPECIALES
            else{

                //CARACTERES CONJUSNTOS == >= <= !=
                if(car == '='){
                    strncat(token, &car, 1);
                    car = fgetc(arch);

                }

                if (tipo_simbolo(token) != 1)
                {
                    printf("\n ERROR EN EL TOKEN INGRESADO\n");
                }

            }
        }
        //IDENTIFICAMOS PALABRAS O NUMEROS
        else{

            char token[50] = "";
            strncat(token, &car, 1);

            //CICLO PARA RECORRER TODO EL CARACTER
            while (isspace(car) == 0 && ispunct(car) == 0)
            {
                car = fgetc(arch);
                if(isspace(car) == 0 && ispunct(car) == 0){
                    strncat(token, &car, 1);
                }
            }

            if (isdigit(token[0]))
            {
                int numero = (car == '.');
                if (numero == 1)
                {
                    strncat(token, &car, 1);
                    car = fgetc(arch);
                    printf("entro");
                    while (isdigit(car))
                    {

                        if(isdigit(car)){
                            strncat(token, &car, 1);
                            car = fgetc(arch);
                        }
                    }
                }
            }

            //IDENTIFICAMOS EL TIPO DE CARACTER
            if(tipo_palabra(token) == 1){
               // printf("\n variable tipo palabra reservada\n");

                //crear el nuevo token
                crear_token("Tipo_p-reservada", PalRes, token, 0, 0, 0);
                //insertarnodo(token);
            }
            else if(tipo_id(token) == 1){
               // printf("\n variable tipo identificador\n");

                //crear el nuevo token
                crear_token("Tipo_id", Id, token, 0, 0, 0);
            }
            else if(tipo_numero(token) == 1){

                //crear el nuevo token
                crear_token("Tipo_numero", Num, token, token, 0, 0);
            }
            else{
                printf("\n ERROR EN EL TOKEN INGRESADO\n");
            }
        }
    }

    return 0;
}

int main()
{
    //toma el archivo de texto
    arch = fopen("archivo.txt", "r");

    if(arch == NULL)
    {
        printf("Error de apertura del archivo. \n\n");
    }
    else
    {
        printf("=== CONTENIDO === \n\n");

        //lee el caracter, lo guarda y avansa al siguiente caracter
        comprobar_token();

        /*
        while(car != EOF){
            car = fgetc(arch);
            comprobar_token(car);
        }
         */

    }

    //CERRAR EL ARCHIVO *IMPORTANTE*
    fclose(arch);
    return 0;
}
