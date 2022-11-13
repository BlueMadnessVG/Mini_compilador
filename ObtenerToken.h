#ifndef OBTENERTOKEN_H_INCLUDED
#define OBTENERTOKEN_H_INCLUDED


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


#endif // OBTENERTOKEN_H_INCLUDED
