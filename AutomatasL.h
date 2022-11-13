#ifndef AUTOMATASL_H_INCLUDED
#define AUTOMATASL_H_INCLUDED

#include "CrearTokens.h"

//AUTOMATA PARA CARACTERES ESPECIALES
int tipo_simbolo(char token[50]){

    int i;


    if (strlen(token) == 2){
        const char *simbolo[4] = {">=", "<=", "!=", "=="};

        for(i=0 ; i < 4; i++){
            if(strcmp(token, simbolo[i]) == 0){
                i = 4;

                crear_token("Tipo_sim", Sim, token, 0, lineas);
                return 1;
            }
        }
    }
    else{
        const char *simbolo[14] = {"+", "-", "*", "/", "%", ">", "<", "=", ";", "(", ")", "{", "}", ","};
        for(i=0 ; i < 14; i++){
            if(strcmp(token, simbolo[i]) == 0){
                i = 14;
                crear_token("Tipo_sim", Sim, token, 0, lineas);
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
                printf("ERROR EN EL TOKEN INGRESADO");
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

    const char *palabras[15] = {"var", "const", "mientras", "fin", "si", "sino", "entero", "punto", "cadena", "funcion", "cuerpo", "lp", "pantalla", "teclado"};

    int i;
    for(i=0 ; i < 14; i++){
        if(strcmp(token, palabras[i]) == 0){
            i = 14;
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

    crear_token("Tipo_texto_plano", text, token, 0, lineas);

    return 1;
}


#endif // AUTOMATASL_H_INCLUDED
