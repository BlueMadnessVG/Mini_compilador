//CODIGO DE LECTURA DE ARCHIVOS EN C
#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenstruc.h"
#include "listaenlazada.h"

//estructura de datos para la lista enlazada



//variable goblal para leer el puntero del automata
FILE *arch;

int lineas = 1;


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

//FUNCION PARA COMPROBAR EL TIPO DE TOKEN
int comprobar_lexico()
{
    char car;
    car = fgetc(arch);

    //CICLO PARA RECORRER TODO EL ARCHIVO
    while(car != EOF){

        if(car == '\n'){
            lineas++;
        }
        printf("%d", lineas);
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
                crear_token("Tipo_p-reservada", PalRes, token, 0, lineas);
                //insertarnodo(token);
            }
            else if(tipo_id(token) == 1){
               // printf("\n variable tipo identificador\n");

                //crear el nuevo token
                crear_token("Tipo_id", Id, token, 0, lineas);
            }
            else if(tipo_numero(token) == 1){

                //crear el nuevo token
                crear_token("Tipo_numero", Num, token, token, lineas);
            }
            else{
                printf("\n ERROR EN EL TOKEN INGRESADO\n");
            }
        }
    }

    return 0;
}


























//cantidad de errores
int errores = 0;



//IDENTIFICACION DEL TIPO DE DATO
int TipoDato(){

    const char *dato[3] = { "entero", "real", "cadena" };

    int i, tipo = 10;
    for( i = 0; i < 3; i++ ){
        if( strcmp( aux->info.Lexema, dato[i] ) == 0 ){
            tipo = i;
            i = 5;
        }
    }
    return tipo;
}
//IDENTIFICACION DE CONSTANTES
int s_constantes() {

    const char *variable[2] = { "const", "=" };
    int tipo_dato;

    //IDENTIFICAMOS LA PRIMERA TERMINAL DE LA DEFINICION DE VARIABLES
    if( strcmp(aux->info.Lexema, variable[0]) == 0 ){
        aux = aux -> der;
        //VERIFICACION DE TIPO DE DATO VALIDO
        tipo_dato = TipoDato();
        if( tipo_dato != 10 ){
            aux = aux -> der;
            //VERIFICACION DE DECLARACION DE IDENTIFICADOR
            if( aux->info.Tipo == 1 ) {
                aux = aux ->der;
                //VERIFICACION DE ASIGNACION DE VALOR
                if( strcmp( aux->info.Lexema, variable[1] ) == 0 ){
                    aux = aux ->der;
                    //VERIFICACION DE IGUALDAD CORRECTA
                    //igualda de numeros
                    if ( (tipo_dato == 0 || tipo_dato == 1) && ( aux->info.Tipo == 1 || aux ->info.Tipo == 2 ) ){
                        aux = aux -> der;
                        if( strcmp( aux->info.Lexema, ";" ) == 0 ) {
                            printf("\n !DECLARACION DE CONSTANTES CORRECTA! \n");
                            aux = aux->der;
                            return 1;
                        }
                        else {
                           printf("\n Falta punto y coma (;) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                        }
                    }
                    //igualdad de cadenas
                    else if ( tipo_dato == 2 && ( aux->info.Tipo == 2 || aux ->info.Tipo == 4 ) ) {
                        printf("\n !DECLARACION DE CONSTANTES CORRECTA! \n");
                        aux = aux -> der;
                        return 1;

                    }
                    else {
                        printf("\n Error de iguldad, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                    }
                }
                else if( strcmp( aux->info.Lexema, ";" ) == 0 ) {
                    printf("\n !DECLARACION DE CONSTANTES CORRECTA! \n");
                    aux = aux->der;
                    return 1;
                }
                else {
                   printf("\n Falta punto y coma (;) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                }
            }
            else{
                printf("\n Error al reconoser un identificador, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
            }
        }
        else{
            printf("\n Tipo de dato no valido, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
        }
    }
    return 0;
}
//IDENTIFICACION DEL VARIABLES
int s_variable() {

    const char *variable[2] = { "var", "=" };
    int tipo_dato;

    //IDENTIFICAMOS LA PRIMERA TERMINAL DE LA DEFINICION DE VARIABLES
    if( strcmp(aux->info.Lexema, variable[0]) == 0 ){

        aux = aux -> der;
        //VERIFICACION DE TIPO DE DATO VALIDO
        tipo_dato = TipoDato();
        if( tipo_dato != 10 ){
            aux = aux -> der;
            //VERIFICACION DE DECLARACION DE IDENTIFICADOR
            if( aux->info.Tipo == 1 ) {
                aux = aux ->der;
                //VERIFICACION DE ASIGNACION DE VALOR
                if( strcmp( aux->info.Lexema, variable[1] ) == 0 ){

                    aux = aux ->der;
                    //VERIFICACION DE IGUALDAD CORRECTA
                    //igualda de numeros
                    if ( (tipo_dato == 0 || tipo_dato == 1) && ( aux->info.Tipo == 1 || aux ->info.Tipo == 2 ) ){
                        aux = aux -> der;
                        if( strcmp( aux->info.Lexema, ";" ) == 0 ) {
                            printf("\n !DECLARACION DE VARIABLES CORRECTA! \n");
                            aux = aux->der;
                            return 1;
                        }
                        else {
                           printf("\n Falta punto y coma (;) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                        }
                    }
                    //igualdad de cadenas
                    else if ( tipo_dato == 2 && ( aux->info.Tipo == 2 || aux ->info.Tipo == 4 ) ) {
                        printf("\n !DECLARACION DE VARIABLES CORRECTA! \n");
                        aux = aux -> der;
                        return 1;

                    }
                    else {
                        printf("\n Error de iguldad, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                    }

                }
                else if( strcmp( aux->info.Lexema, ";" ) == 0 ) {
                    printf("\n !DECLARACION DE VARIABLES CORRECTA! \n");
                    aux = aux->der;
                    return 1;

                }
                else {
                   printf("\n Falta punto y coma (;) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                }
            }
            else{
                printf("\n Error al reconoser un identificador, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
            }
        }
        else{
            printf("\n Tipo de dato no valido, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
        }
    }
    return 0;
}
//IDENTIFICACION DE LEER POR TECLADO
int s_leer() {

    const char *leer[3] = { "teclado", "(", ")" };

    //IDENTIFICAMOS LA PRIMERA TERMINAL DE LEER POR TECLADO
    if ( strcmp( aux ->info.Lexema, leer[0] ) == 0 ){
        aux = aux->der;
        if( strcmp( aux ->info.Lexema, leer[1] ) == 0  ) {
            aux = aux -> der;
            if ( aux ->info.Tipo == 1 ) {
                aux = aux -> der;
                if( strcmp( aux ->info.Lexema, leer[2] ) == 0  ) {
                    aux = aux -> der;
                    if( strcmp( aux->info.Lexema, ";" ) == 0 ){
                        printf("\n !LEER POR TECLADO CORRECTO! \n");
                        aux = aux->der;
                        return 1;
                    }
                    else{
                        printf("\n Falta punto y coma (;) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                    }
                }
                else {
                    printf("\n Falta un parentesis ( ')' ), en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                }
            }
            else {
                printf("\n Error al reconoser un identificador, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
            }
        }
        else {
            printf("\n Falta un parentesis ( '(' ), en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
        }
    }
    return 0;
}

int valor() {

    if ( aux ->info.Tipo == 1 || aux ->info.Tipo == 4 ){
        aux = aux->der;
        if ( strcmp( aux ->info.Lexema, "," ) == 0 ){
            aux = aux ->der;
            valor();
        }
        else {
            return 1;
        }
    }
    else{
        return 0;
    }
}

//IDENTIFICACION DE ESCRIBIR EN PANTALLA
int s_escribir() {

    const char *escribir[3] = { "pantalla", "(", ")" };

    if( strcmp( aux ->info.Lexema, escribir[0] ) == 0 ) {
        aux = aux->der;
        if(strcmp( aux ->info.Lexema, escribir[1] ) == 0) {
            aux = aux->der;
            if( valor() == 1 ){
                if( strcmp( aux ->info.Lexema, escribir[2]) == 0 ){
                    aux = aux -> der;
                    if( strcmp( aux->info.Lexema, ";" ) == 0 ){
                        printf("\n !IMPRIMIR PANTALLA CORRECTO! \n");
                        aux = aux->der;
                        return 1;
                    }
                    else{
                        printf("\n Falta punto y coma (;) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                    }
                }
                else {
                  printf("\n Falta parentesis ( ')' ) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                }
            }
            else {
                printf("\n Error en los datos ingresados en pantalla, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
            }
        }
        else {
            printf("\n Falta parentesis ( '(' ) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
        }
    }

    return 0;
}
//IDENTIFICACION PARA LIMPIAR PANTALLA
int s_limpiar() {

    const char *limpiar[3] = { "lp", "(", ")" };

    if( strcmp( aux ->info.Lexema, limpiar[0] ) == 0 ){
        aux = aux ->der;
        if( strcmp( aux ->info.Lexema, limpiar[1] ) == 0 ){
            aux = aux ->der;
            if( strcmp( aux ->info.Lexema, limpiar[2] ) == 0){
                aux = aux ->der;
                if( strcmp( aux->info.Lexema, ";" ) == 0 ){
                    printf("\n !LIMPIAR PANTALLA CORRECTO! \n");
                    aux = aux->der;
                    return 1;
                }
                else{
                    printf("\n Falta punto y coma (;) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                }
            }
            else {
               printf("\n Falta parentesis ( ')' ) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
            }
        }
        else {
            printf("\n Falta parentesis ( '(' ) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
        }
    }
    return 0;
}
//IDENTIFICAION DE OPERACION
int operacion() {

    const char *operacion[10] = { "+", "-", "*", "/", "<", ">", "<=", ">=", "==", "!=" };

    int i, sim;
    for( i = 0; i < 10; i++ ){
        if( strcmp( aux->info.Lexema, operacion[i] ) == 0 ){

            i = 15;
        }
    }
    return i;

}
//IDENTIFICACION DE EXPRECION
int exprecion(int par) {

    const char *exp[2] = { "(", ")" };
    if( strcmp( aux->info.Lexema, exp[0] ) == 0 ){
        par ++;
        aux = aux ->der;
        exprecion(par);
    }
    else if ( strcmp( aux->info.Lexema, exp[1] ) == 0){
        if( par > 0 ){
            par--;
        }
        else {
           printf("\n Error en la exprecion, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
            return 0;
        }
        aux = aux ->der;
        if( aux->info.Tipo == 3 ){
            if( operacion() == 16 ){
                aux = aux ->der;
                if ( aux->info.Tipo == 1 || aux->info.Tipo == 2 || aux->info.Tipo == 4 ){
                    exprecion(par);
                }
                else{
                    printf("\n Error en la exprecion, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                    return 0;
                }
            }
            else if ( par > 0 ){
                if(strcmp( aux->info.Lexema, exp[1] ) != 0){
                    printf("\n Error en la exprecion, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                    return 0;
                }
                else{
                    exprecion(par);
                }
            }
            else {
                return 1;
            }
        }
        else {
            printf("\n Error en la exprecion, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
            return 0;
        }

    }
    else if ( aux->info.Tipo == 1 || aux->info.Tipo == 2 || aux->info.Tipo == 4 ) {
        aux = aux->der;
        if ( aux->info.Tipo == 3 ) {
            if( operacion() == 16 ){
                aux = aux ->der;
                if ( aux->info.Tipo == 1 || aux->info.Tipo == 2 || aux->info.Tipo == 4 || strcmp( aux->info.Lexema, exp[0] ) == 0 ){
                    exprecion(par);
                }
                else{
                    printf("\n Error en la exprecion, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                    return 0;
                }
            }
            else if ( strcmp( aux->info.Lexema, exp[0] ) == 0 ){
                par++;
                exprecion(par);
            }
            else if ( par > 0 ){
                if(strcmp( aux->info.Lexema, exp[1] ) != 0){
                    printf("\n Error en la exprecion, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                    return 0;
                }
                else{
                    exprecion(par);
                }
            }
            else {
                return 1;
            }
        }
        else {
            printf("\n Error en la exprecion, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
            return 0;
        }
    }
    else {
        return 0;
    }
}

//IDENTIFICAION DE CONDICION SI
int s_si() {

    const char *condicion[5] = { "si", "(", ")", "{", "}" };

    if( strcmp( aux->info.Lexema, condicion[0] ) == 0 ){
        aux = aux->der;
        if( strcmp( aux->info.Lexema, condicion[1] ) == 0 ){
            aux = aux->der;
            if( exprecion(0) == 1 ) {
                if( strcmp( aux->info.Lexema, condicion[2] ) == 0 ){
                    aux = aux->der;
                    if ( strcmp( aux->info.Lexema, condicion[3] ) == 0 ){
                        aux=aux->der;
                        if( s_instruccion() == 1 ){
                            if( strcmp( aux->info.Lexema, condicion[4] ) == 0 ){
                                printf("\n !CONDICION SI CORRECTA! \n");
                                aux = aux->der;
                                return 1;
                            }
                            else{
                                printf("\n Falta laves ( } ) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                            }
                        }
                        else {
                            printf("\n Tienes un error en el la condicion si, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                        }
                    }
                    else {
                       printf("\n Falta laves ( { ) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                    }
                }
                else {
                   printf("\n Falta parentesis ( ')' ) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                }
            }
            else {
                printf("\n Error en el exprecion de la condicon si, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
            }
        }
        else{
            printf("\n Falta parentesis ( '(' ) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
        }
    }

    return 0;
}
//IDENTIFICACION DE CONDICION SINO
int s_sino() {

    const char *condicion[3] = { "sino", "{", "}" };

    if( strcmp( aux->info.Lexema, condicion[0] ) == 0 ){
        aux = aux->der;
        if( strcmp( aux->info.Lexema, condicion[1] ) == 0 ){
            aux=aux->der;
            if( s_instruccion() == 1 ){
                if( strcmp( aux->info.Lexema, condicion[2] ) == 0 ){
                    printf("\n !CONDICION SINO CORRECTA! \n");
                    aux = aux->der;
                    return 1;
                }
                else{
                    printf("\n Falta laves ( } ) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                }
            }
            else {
                printf("\n Tienes un error en el la condicion sino, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
            }
        }
        else{
            printf("\n Falta llaves ( '{' ) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
        }
    }

    return 0;
}
//IDENTIFICACION DE CICLO MIENTRAS
int s_mientras(){

    const char *condicion[5] = { "mientras", "(", ")", "{", "}" };

    if( strcmp( aux->info.Lexema, condicion[0] ) == 0 ){
        aux = aux->der;
        if( strcmp( aux->info.Lexema, condicion[1] ) == 0 ){
            aux = aux->der;
            if( exprecion(0) == 1 ) {
                if( strcmp( aux->info.Lexema, condicion[2] ) == 0 ){
                    aux = aux->der;
                    if ( strcmp( aux->info.Lexema, condicion[3] ) == 0 ){
                        aux=aux->der;
                        if( s_instruccion() == 1 ){
                            if( strcmp( aux->info.Lexema, condicion[4] ) == 0 ){
                                printf("\n !CICLO MIENTRAS CORRECTA! \n");
                                aux = aux->der;
                                return 1;
                            }
                            else{
                                printf("\n Falta laves ( } ) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                            }
                        }
                        else {
                            printf("\n Tienes un error en el ciclo mientras, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                        }
                    }
                    else {
                       printf("\n Falta laves ( { ) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                    }
                }
                else {
                   printf("\n Falta parentesis ( ')' ) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                }
            }
            else {
                printf("\n Error en el exprecion del ciclo mientras, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
            }
        }
        else{
            printf("\n Falta parentesis ( '(' ) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
        }
    }
    return 0;
}
//IDENTIFICACION DE IGUALDAD DE VARIABLES
int s_igualdad() {

   if( aux->info.Tipo == 1 ){
        aux = aux->der;
        if( strcmp( aux->info.Lexema, "=" ) == 0 ){
            aux = aux->der;
            if( exprecion(0) == 1 ){
                if( strcmp( aux->info.Lexema, ";" ) == 0 ){
                    printf("\n !IGUALDAD CORRECTA! \n");
                    aux = aux->der;
                    return 1;
                }
                else {
                    printf("\n Falta punto y coma (;) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                }
            }
            else {
                printf("\n Error en el exprecion de la igualdad, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
            }
        }
        else{
            printf("\n Falta igual ( '=' ) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
        }
   }
   return 0;
}

//IDENTIFICACION DE INSTRUCCIONES
int s_instruccion() {

    //COMPARAMOS EL VALOR CON UN ;
    if ( aux == NULL ){

        return 0;
    }
    else if ( strcmp( aux -> info.Lexema, "}" ) == 0 ){
        return 1;
    }
    else if( s_variable() == 1 ){
        s_instruccion();
    }
    else if( s_constantes() == 1 ){
        s_instruccion();
    }
    else if( s_leer() == 1 ){
        s_instruccion();
    }
    else if( s_escribir() == 1 ){
       s_instruccion();
    }
    else if ( s_limpiar() == 1 ){
        s_instruccion();
    }
    else if ( s_si() == 1 ){
        s_instruccion();
    }
    else if ( s_sino() == 1 ){
        s_instruccion();
    }
    else if ( s_mientras() == 1){
        s_instruccion();
    }
    else if ( s_igualdad() == 1 ){
        s_instruccion();
    }
    else {
        errores++;

        if( strcmp( aux -> info.Lexema, "}" ) != 0 ) {

            while( strcmp( aux->info.Lexema, ";" ) != 0 && strcmp( aux -> info.Lexema, "}" ) != 0 ){
                aux = aux->der;
            }

            if( strcmp( aux -> info.Lexema, "}" ) != 0 ){
                aux = aux->der;
                s_instruccion();
            }
            else{
                return 0;
            }
        }
        else {
            s_instruccion();
        }
    }
}

int s_cuerpo(){

    const char *cuerpo[3] = { "cuerpo", "{", "}" };
    int i;
    if( strcmp(aux->info.Lexema, cuerpo[0]) == 0 ){
        aux = aux -> der;
        if( strcmp(aux->info.Lexema, cuerpo[1]) == 0 ){
            aux =aux ->der;
            if( s_instruccion() == 1 ){
                if( strcmp( aux->info.Lexema, cuerpo[2] ) == 0 ){
                    aux = aux ->der;
                    if( aux == NULL ){
                        printf("\n CUEPOR DEL PROGRAMA CORRECTO \n");
                    }
                    else {
                        errores++;
                        printf("\n Tienes un error en el cuerpo del programa, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                    }
                }
                else{
                    errores++;
                    printf("\n Falta laves ( } ) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
                }
            }
            else {
                errores++;
                printf("\n Tienes un error en el cuerpo del programa, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
            }
        }
        else {
            errores++;
            printf("\n Falta laves ( { ) al final, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
        }
    }
    else {
        errores++;
        printf("\n Falta el cuerpo del programa, en liena: %d, en el token: %s \n", aux->info.NoLin, aux->info.Lexema);
    }

    if ( errores == 0 ){
        printf( "\n\n === SINTAXIS DEL PROGRAMA CORRECTA === \n" );
        printf( "\n Tu programa tiene: 0 errores \n", errores );
    }
    else {
        printf( "\n\n === ERROR DE SINTAXIS === \n" );
        printf( "\n Tu programa tiene: %d errores, por favor corrigelos para poder continuar \n", errores );
        while ( aux != NULL ){
            aux = aux->der;
        }
    }

    return 0;
}

int comprobar_sintaxis(){

    printf( "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n ===  COMPROBAR SINTAXIS  === \n" );

    aux = raiz;
    while( aux != NULL ){
        //ENTRA AL AUTOMATA DEL CUERPO
        s_cuerpo();
    }

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
        comprobar_lexico();
        comprobar_sintaxis();

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
