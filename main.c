/*
Lucas Bachur - Marcos Cassinerio
LCC - Trabajo Practico 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Representamos a las personas mediante una estructura Personas que tiene 6 arrays de chars que representan
// nombre, apellido, localidad, edad, genero e interes que le corresponden a cierta persona

struct Personas {
    char nombre[20];
    char apellido[20];
    char localidad[70];
    char edad[5];
    char genero[20];
    char interes[20];
} Persona;

// tomarLocalidades: char[][]
// La funcion toma un array bidimensional de caracteres y guarda en este el contenido del archivo "codigoLocalidades.txt",
// donde la localidad de codigo n esta guardada en el array localidades[n].

void tomarLocalidades(char localidades[][70]) {
    long localidadesPos = 0;

    FILE *localidadesFile;
    localidadesFile = fopen("codigoLocalidades.txt", "r");

    char linea[70];

    while (!feof((FILE*)localidadesFile)) {
        fgets(linea, 70, (FILE*)localidadesFile);

        int comaBandera = 0, localidadesCont = 0;

        for (int cont = 0 ; (cont < (strlen(linea) - 1)) && ((linea[cont] != ' ') || (linea[cont+1] != ' ')) ; ++cont) {
            if (linea[cont] == ',') {
                comaBandera = 1;

                ++cont;
            }
            if (comaBandera == 1) {
                localidades[localidadesPos][localidadesCont] = linea[cont];

                ++localidadesCont;
            }
        }

        localidades[localidadesPos][localidadesCont] = '\0';

        ++localidadesPos;
    }

    fclose(localidadesFile);
}

// cantidadLocalidades: -> long
// La funcion lee el archivo "codigoLocalidades.txt" y devuelve la cantidad de lineas(localidades) que hay en este.

long cantidadLocalidades() {
    long cantLocalidades = 0;

    char buff[255];

    FILE *localidadesFile;
    localidadesFile = fopen("codigoLocalidades.txt", "r");

    while (!feof((FILE*)localidadesFile)) {
        fgets(buff, 255, (FILE*)localidadesFile);

        ++cantLocalidades;
    }

    fclose(localidadesFile);

    return cantLocalidades;
}

// tomarNumerosRandom: long[] long long
// La funcion genera una lista de n numeros random (sin repetir), siendo n el segundo parametro de la funcion.
// Esta lista de numeros random ademas esta ordenada de menor a mayor.

void tomarNumerosRamdom(long numerosRandom[], long personasATomar, long cantPersonas) {
    for (long cont = 0 ; cont < personasATomar ; ++cont) {
        long numeroRandom = rand()%cantPersonas, repetido = 0;

        for (long h = 0 ; h <= cont ; ++h) {
            if (h == cont) {
                numerosRandom[h] = numeroRandom;
            } else {
                if (numerosRandom[h] == numeroRandom) {
                    h = cont;

                    repetido = 1;
                }
                if (numerosRandom[h] > numeroRandom) {
                    long actual = numerosRandom[h], sig;
                            
                    if ((h+1) != cont) {
                        sig = numerosRandom[h+1];
                    }

                    numerosRandom[h] = numeroRandom;

                    numeroRandom = actual;

                    while (h < cont) {
                        ++h;

                        if (h != cont) {
                            actual = sig;
                            
                            sig = numerosRandom[h+1];
                        }

                        numerosRandom[h] = numeroRandom;

                        numeroRandom = actual;
                    }
                }
            }
        }
        if (repetido == 1) {
            --cont;
        }
    }
}

// tomarPersonas: Personas[] long long char[][]
// La funcion toma un array de Personas, un long que indica el largo del array, otro long que indica la cantidad de personas a tomar
// y un array bidimensional de caracteres que contiene las localidades ubicadas por su codigo.
// Se lee el archivo "personas.txt" (que contiene los datos de cada persona) y toma un grupo de esa lista segun las posiciones que indique
// la lista de numeros random(que se genera con tomarNumerosRamdom). Luego, se guarda la informacion de estas personas en el array
// de Personas.

void tomarPersonas(struct Personas personas[], long cantPersonas, long personasATomar, char localidades[][70]) {
    long numerosRandom[personasATomar];

    char genero[2][2] = {
        "M",
        "F"
    }, interes[4][2] = {
        "F",
        "M",
        "A",
        "N"
    };

    tomarNumerosRamdom(numerosRandom, personasATomar, cantPersonas);

    for (int n = 0 ; n < personasATomar ; ++n) {
        printf("%lu\n", numerosRandom[n]);
    }

    FILE *personasFile;
    personasFile = fopen("personas.txt", "r");
    
    char linea[70];

    long posPersonas = 0;
    for (long cont = 1 ; !feof((FILE*)personasFile) || cont < numerosRandom[personasATomar - 1] ; ++cont) {    
        fgets(linea, 70, (FILE*)personasFile);
        
        if (cont == numerosRandom[posPersonas]) {
            int comas = 0;

            char coma[2] = ",", *token;

            token = strtok(linea, coma);
            
            while( token != NULL ) {

                if (comas == 0) {
                    strcpy(personas[posPersonas].nombre, token);
                }

                if (comas == 1) {
                    strcpy(personas[posPersonas].apellido, token);
                }

                if (comas == 2) {
                    char *pEnd;
                    strcpy(personas[posPersonas].localidad, localidades[strtol(token, &pEnd, 10) - 1]);
                }

                if (comas == 3) {
                    char *pEnd;
                    strcpy(personas[posPersonas].edad, token);
                }

                if (comas == 4) {
                    char *pEnd;
                    strcpy(personas[posPersonas].genero, genero[strtol(token, &pEnd, 10) - 1]);
                }

                if (comas == 5) {
                    token[1] = '\0';
                    char *pEnd;
                    strcpy(personas[posPersonas].interes, interes[strtol(token, &pEnd, 10) - 1]);
                }
                
                token = strtok(NULL, coma);

                ++comas;
            }

            ++posPersonas;
        }
    }
}

// cantidadPersonas: -> long
// La funcion lee el archivo "personas.txt" y devuelve la cantidad de lineas(personas) que hay en este.

long cantidadPersonas() {
    long cantPersonas = 0;

    char buff[255];

    FILE *personasFile;
    personasFile = fopen("personas.txt", "r");

    while (!feof((FILE*)personasFile)) {
        fgets(buff, 255, (FILE*)personasFile);

        ++cantPersonas;
    }

    fclose(personasFile);

    return cantPersonas;
}

// imprimirEnArchivo: Personas[] long
// La funcion toma un array de Personas y un long que contiene el largo del array.
// Se genera un archivo "salida.txt" y en este se escribe la lista de personas que se le paso como parametro a la funcion.

void imprimirEnArchivo(struct Personas personas[], long personasATomar){
    FILE *salida;

    salida = fopen("salida.txt","w+");

    for (int n = 0 ; n < personasATomar ; ++n) {
        char linea[100];
        strcpy(linea, "");
        strcat(linea, personas[n].nombre);
        strcat(linea, ",");
        strcat(linea, personas[n].apellido);
        strcat(linea, ",");
        strcat(linea, personas[n].localidad);
        strcat(linea, ",");
        strcat(linea, personas[n].edad);
        strcat(linea, ",");
        strcat(linea, personas[n].genero);
        strcat(linea, ",");
        strcat(linea, personas[n].interes);
        strcat(linea, "\n");

        fputs(linea, salida);
    }

    fclose(salida);
}

int main(){
    long cantLocalidades = cantidadLocalidades(), cantPersonas = cantidadPersonas(), personasATomar = 0;

    char localidades[cantLocalidades][70];

    tomarLocalidades(localidades);

    printf("Ingrese la cantidad de personas a tomar:\n");

    while (personasATomar == 0) {
        scanf("%d", &personasATomar);

        if (personasATomar <= 0 || personasATomar > cantPersonas) {
            printf("El numero ingresado no es nardo, ingrese de nuevo:\n");

            personasATomar = 0;
        }
    }

    struct Personas personas[personasATomar];

    tomarPersonas(personas, cantPersonas, personasATomar, localidades);

    imprimirEnArchivo(personas, personasATomar);

    return 0;
}
