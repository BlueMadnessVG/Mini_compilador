//CODIGO DE LECTURA DE ARCHIVOS EN C
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//tipos de datos que puede tomar el token
enum TipoToken
{
    PalRes,
    Id,
    Num,
    Sim
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

//variable goblal para leer el puntero del automata
FILE *arch;

int crear_token(char Nombre[80], enum TipoToken Tipo, char Lexema[80], int valor, int NoLin, int NoCoL){

    struct TokenStruc new_token;
    strcpy(new_token.Nombre, Nombre);
    strcpy(new_token.Lexema, Lexema);
    new_token.Tipo = Tipo;
    new_token.Valor = valor;

    return 1;
}

//AUTOMATA PARA CARACTERES ESPECIALES
int tipo_simbolo(char token[50]){

    int i;
    printf("%s", token);

    if (strlen(token) == 2){
        const char *simbolo[4] = {">=", "<=", "!=", "=="};

        for(i=0 ; i < 4; i++){
            if(strcmp(token, simbolo[i]) == 0){
                i = 4;

                printf("\n varibale tipo simbolo\n");
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
                printf("\n varibale tipo simbolo\n");
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
                if(token[i] == '.' && punto == 0 && (i+1) != strlen(token)){
                    punto = 1;
                }
                else{
                    printf("no es valido");
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

//AUTOMATA PARA PALABRAS RESERBADAS
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
            //CARACTERES CONJUSNTOS == >= <= !=
            if(ispunct(car) != 0 && car == '='){
                strncat(token, &car, 1);
                car = fgetc(arch);

                tipo_simbolo(token);
            }
            else{
                tipo_simbolo(token);
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
            printf("%s", token);

            //IDENTIFICAMOS EL TIPO DE CARACTER
            if(tipo_palabra(token) == 1){
                printf("\n variable tipo palabra reservada\n");

                //crear el nuevo token
                crear_token("Tipo_p-reserbada", PalRes, token, 0, 0, 0);
            }
            else if(tipo_id(token) == 1){
                printf("\n variable tipo identificador\n");

                //crear el nuevo token
                crear_token("Tipo_id", Id, token, 0, 0, 0);
            }
            else{
                printf("\n variable tipo numero\n");

                //crear el nuevo token
                crear_token("Tipo_numero", Num, token, token, 0, 0);
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
