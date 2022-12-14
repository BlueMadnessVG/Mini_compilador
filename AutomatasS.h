#ifndef AUTOMATASS_H_INCLUDED
#define AUTOMATASS_H_INCLUDED

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
                           printf("\n Falta punto y coma (;) en linea: %d\n", aux->info.NoLin);
                        }
                    }
                    //igualdad de cadenas
                    else if ( tipo_dato == 2 && ( aux->info.Tipo == 2 || aux ->info.Tipo == 4 ) ) {
                        aux = aux -> der;
                       if( strcmp( aux->info.Lexema, ";" ) == 0 ) {
                            printf("\n !DECLARACION DE CONSTANTES CORRECTA! \n");
                            aux = aux->der;
                            return 1;
                        }
                        else {
                           printf("\n Falta punto y coma (;) en linea: %d", aux->info.NoLin );
                        }
                    }
                    else {
                        printf("\n Error de iguldad, en linea: %d\n", aux->info.NoLin);
                    }
                }
                else if( strcmp( aux->info.Lexema, ";" ) == 0 ) {
                    printf("\n !DECLARACION DE CONSTANTES CORRECTA! \n");
                    aux = aux->der;
                    return 1;
                }
                else {
                   printf("\n Falta punto y coma (;) en linea: %d\n", aux->info.NoLin);
                }
            }
            else{
                printf("\n Error al reconocer un identificador, en linea: %d\n", aux->info.NoLin);
            }
        }
        else{
            printf("\n Tipo de dato no valido, en linea: %d\n", aux->info.NoLin, aux->info.Lexema);
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
                           printf("\n Falta punto y coma (;) en linea: %d\n", aux->info.NoLin);
                        }
                    }
                    //igualdad de cadenas
                    else if ( tipo_dato == 2 && ( aux->info.Tipo == 2 || aux ->info.Tipo == 4 ) ) {
                        aux = aux -> der;
                        if( strcmp( aux->info.Lexema, ";" ) == 0 ) {
                            printf("\n !DECLARACION DE VARIABLES CORRECTA! \n");
                            aux = aux->der;
                            return 1;
                        }
                        else {
                           printf("\n Falta punto y coma (;) en linea: %d\n", aux->info.NoLin);
                        }

                    }
                    else {
                        printf("\n Error de iguldad, en linea: %d\n", aux->info.NoLin);
                    }

                }
                else if( strcmp( aux->info.Lexema, ";" ) == 0 ) {
                    printf("\n !DECLARACION DE VARIABLES CORRECTA! \n");
                    aux = aux->der;
                    return 1;

                }
                else {
                   printf("\n Falta punto y coma (;) en linea: %d\n", aux->info.NoLin);
                }
            }
            else{
                printf("\n Error al reconocer un identificador, en linea: %d\n", aux->info.NoLin);
            }
        }
        else{
            printf("\n Tipo de dato no valido, en linea: %d\n", aux->info.NoLin);
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
                        printf("\n Falta punto y coma (;) en linea: %d\n", aux->info.NoLin);
                    }
                }
                else {
                    printf("\n Falta un parentesis ( ')' ), en linea: %d\n", aux->info.NoLin);
                }
            }
            else {
                printf("\n Error al reconocer un identificador, en linea: %d\n", aux->info.NoLin);
            }
        }
        else {
            printf("\n Falta un parentesis ( '(' ), en linea: %d\n", aux->info.NoLin);
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
                        printf("\n Falta punto y coma (;) en linea: %d\n", aux->info.NoLin);
                    }
                }
                else {
                  printf("\n Falta parentesis ( ')' ) en linea: %d\n", aux->info.NoLin);
                }
            }
            else {
                printf("\n Error en los datos ingresados en pantalla, en linea: %d\n", aux->info.NoLin);
            }
        }
        else {
            printf("\n Falta parentesis ( '(' ) en linea: %d\n", aux->info.NoLin);
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
                    printf("\n Falta punto y coma (;) en linea: %d\n", aux->info.NoLin);
                }
            }
            else {
               printf("\n Falta parentesis ( ')' ) en linea: %d\n", aux->info.NoLin);
            }
        }
        else {
            printf("\n Falta parentesis ( '(' ) en linea: %d\n", aux->info.NoLin);
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
           printf("\n Error en la expresion, en linea: %d\n", aux->info.NoLin, aux->info.Lexema);
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
                    printf("\n Error en la expresion, en linea: %d\n", aux->info.NoLin);
                    return 0;
                }
            }
            else if ( par > 0 ){
                if(strcmp( aux->info.Lexema, exp[1] ) != 0){
                    printf("\n Error en la expresion, en linea: %d\n", aux->info.NoLin);
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
            printf("\n Error en la expresion, en linea: %d\n", aux->info.NoLin);
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
                    printf("\n Error en la expresion, en linea: %d\n", aux->info.NoLin);
                    return 0;
                }
            }
            else if ( strcmp( aux->info.Lexema, exp[0] ) == 0 ){
                par++;
                exprecion(par);
            }
            else if ( par > 0 ){
                if(strcmp( aux->info.Lexema, exp[1] ) != 0){
                    printf("\n Error en la expresion, en linea: %d\n", aux->info.NoLin);
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
            printf("\n Error en la expresion, en linea: %d\n", aux->info.NoLin);
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
                                printf("\n Falta llave ( } ) en linea: %d\n", aux->info.NoLin);
                            }
                        }
                        else {
                            printf("\n Tienes un error en el la condicion si, falta una llave ( } ) de la condicion si \n");
                        }
                    }
                    else {
                       printf("\n Falta llave ( { ) en linea: %d\n", aux->info.NoLin);
                    }
                }
                else {
                   printf("\n Falta parentesis ( ')' ) en linea: %d\n", aux->info.NoLin);
                }
            }
            else {
                printf("\n Error en el expresion de la condicion si, en linea: %d\n", aux->info.NoLin);
            }
        }
        else{
            printf("\n Falta parentesis ( '(' ) en linea: %d\n", aux->info.NoLin);
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
                    printf("\n Falta llave ( } ) en linea: %d\n", aux->info.NoLin);
                }
            }
            else {
                printf("\n Tienes un error en el la condicion sino, en linea: %d\n", aux->info.NoLin);
            }
        }
        else{
            printf("\n Falta lllave ( '{' ) en linea: %d\n", aux->info.NoLin, aux->info.Lexema);
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
                                printf("\n Falta llave ( } ) en linea: %d\n", aux->info.NoLin);
                            }
                        }
                        else {
                            printf("\n Tienes un error en el ciclo mientras, falta una llave ( } ) del ciclo mientras \n");
                        }
                    }
                    else {
                       printf("\n Falta llave ( { ) en linea: %d\n", aux->info.NoLin);
                    }
                }
                else {
                   printf("\n Falta parentesis ( ')' ) en linea: %d\n", aux->info.NoLin);
                }
            }
            else {
                printf("\n Error en el expresion del ciclo mientras, en linea: %d\n", aux->info.NoLin);
            }
        }
        else{
            printf("\n Falta parentesis ( '(' ) en linea: %d\n", aux->info.NoLin);
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
                    printf("\n Falta punto y coma (;) en linea: %d\n", aux->info.NoLin);
                }
            }
            else {
                printf("\n Error en el expresion de la igualdad, en linea: %d\n", aux->info.NoLin);
            }
        }
        else{
            printf("\n Falta igual ( '=' ) en linea: %d\n", aux->info.NoLin, aux->info.Lexema);
        }
   }
   return 0;
}

#endif // AUTOMATASS_H_INCLUDED
