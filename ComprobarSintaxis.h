#ifndef COMPROBARSINTAXIS_H_INCLUDED
#define COMPROBARSINTAXIS_H_INCLUDED

//cantidad de errores
int errores = 0;

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

    aux = raiz;
    while( aux != NULL ){
        //ENTRA AL AUTOMATA DEL CUERPO
        s_cuerpo();
    }

}


#endif // COMPROBARSINTAXIS_H_INCLUDED
