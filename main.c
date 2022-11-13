//CODIGO DE LECTURA DE ARCHIVOS EN C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "AutomatasL.h"
#include "CrearTokens.h"
#include "ObtenerToken.h"
#include "AutomatasS.h"
#include "ComprobarSintaxis.h"

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
        printf("=== VALIDACION DE LEXICO === \n\n");

        comprobar_lexico();

        printf("\n\n=== VALIDACION DE LEXICO === \n\n");

        printf("\n\n=== VALIDACION DE SINTAXIS === \n\n");
        comprobar_sintaxis();

        printf("\n\n=== VALIDACION DE SINTAXIS === \n\n");

    }

    //CERRAR EL ARCHIVO *IMPORTANTE*
    fclose(arch);
    return 0;
}
