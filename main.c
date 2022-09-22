#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

/////////////////////////////////// FIRMAS //////////////////////////////////////////
void cargaPila(Pila *pilita);
int pilaAarregloImpar(Pila pilita, int arreglo[]);
int buscaMayorArreglo(int arreglo[], int validos);
void quitarMenorPila(Pila *pilita);
float promedioArreglo(int arreglo[], int validos);
int pedirPosArreglo(int validos);
void mostrarEnPosArreglo(int arreglo[], int pos);
void mostrarPila(Pila pilita);

//AGREGO FUNCION MOSTRAR ARREGLO
void mostratArreglo(int arreglo[], int validos);

int main()
{
    ///////////////////////////////// DECLARACIONES //////////////////////////////////
    //declaro e inicializo la pila
    Pila dada;
    inicpila(&dada);

    //declaro el arreglo y sus validos
    int arregloImpar[20];
    int validosArreglo;

    //declaro otras variables necesarias
    int mayorArreglo;
    float promArreglo;
    int posicion;

    /////////////////////////// LLAMADAS A FUNCIONES ////////////////////////////////

    //cargo la pila por teclado
    cargaPila(&dada);
    printf("PILA DADA\n");
    printf("---------\n");
    mostrarPila(dada);

    //paso los elementos impares de la pila al arreglo
    validosArreglo=pilaAarregloImpar(dada,arregloImpar);
    printf("\nARREGLO IMPAR\n");
    printf("--------------\n");
    mostratArreglo(arregloImpar,validosArreglo);//muestro el arreglo

    //busco el mayor y lo muestro
    mayorArreglo=buscaMayorArreglo(arregloImpar,validosArreglo);
    printf("\nEl mayor elemento del arreglo es %d\n", mayorArreglo);

    //calculo el promedio del arreglo
    promArreglo=promedioArreglo(arregloImpar,validosArreglo);
    printf("\nEl promedio de los elementos en el arreglo es: %.2f", promArreglo);

    //quito el menor elemento de la pila
    quitarMenorPila(&dada);
    printf("\nPILA SIN MENOR\n");
    printf("---------------\n");
    mostrarPila(dada);

    system("pause");

    posicion=pedirPosArreglo(validosArreglo);//pido posicion a buscar
    //vuelvo a mostrar todo el arreglo para verificar la posicion
    printf("\nARREGLO IMPAR\n");
    printf("--------------\n");
    mostratArreglo(arregloImpar,validosArreglo);//muestro el arreglo
    printf("\nEL ELEMENTO DE LA POSICION %d\n", posicion);//titulo
    printf("-----------------------------\n");
    mostrarEnPosArreglo(arregloImpar, posicion);

    return 0;
}

////////////////////////////////// FUNCIONES ////////////////////////////////////////

/**1.
 Hacer una función que cargue una pila de números enteros mientras el usuario así
 lo desea. La pila se envía por parámetro.
**/
void cargaPila(Pila *pilita)
{
    //declaro e inicializo un char para detener la carga
    char mander='s';

    //inicio ciclo de carga
    while(mander=='s')
    {
        leer(pilita);//el usuario carga la pila por teclado

        //pregunto al usuario si sigue el ciclo
        printf("\nDesea seguir cargando elementos? (s/n)\n");
        fflush(stdin);//limpio el buffer
        scanf("%c", &mander);

        //limpio la pantalla
        system("cls");
    }
}

/**2.
Copiar los elementos impares de la pila a un arreglo. Dicho arreglo es de dimensión 20.
Controlar que no se puedan pasar más elementos. Los elementos deben quedar en la pila.
**/
int pilaAarregloImpar(Pila pilita, int arreglo[])
{
    //declaro los elementos validos
    int validos=0;

    //declaro e inicializo una pila auxiliar
    Pila pares;
    inicpila(&pares);

    //paso los elementos impares con limite de carga de 20 elementos
    //y mientras la pila tenga elementos
    while((validos<20)&&(!pilavacia(&pilita)))
    {
        if((tope(&pilita)%2))
        {
            //si da 1 es impar y paso el elemento a validos y lo elimino de pilita
            arreglo[validos]=desapilar(&pilita);
            validos++;//incremento los validos
        }
        else
        {
            //si son pares lo paso a una pila auxiliar
            apilar(&pares, desapilar(&pilita));
        }
    }
    //no vuelvo a poner los elementos en la pila pilita porque lo pase en parametros por copia

    //retorno los validos
    return validos;
}

/**3.
Buscar y retornar el mayor elemento del arreglo del punto anterior.
**/
int buscaMayorArreglo(int arreglo[], int validos)
{
    //declaro la variable para buscar el mayor
    int mayor=0;

    //recorro el arreglo
    for(int i=0; i<validos; i++)
    {
        if((i==0)||(mayor<arreglo[i]))
        {
            //si es el primer elemento lo asigno a mayor
            //o si el mayor es menor al elemento actual en el recorrido del arreglo
            mayor=arreglo[i];
        }
    }

    //retorno el mayor
    return mayor;
}

/**4.
Buscar el menor elemento de la pila del punto 2 y quitarlo de la pila.
La pila debe quedar en orden.
**/
void quitarMenorPila(Pila *pilita)
{
    //declaro e inicializo una pila auxiliar
    Pila aux;
    inicpila(&aux);

    //declaro una bandera para saber si ya elimine el menor
    int flag=0;

    //declaro el menor elemento y asimilo el tope como el menor
    int menor=tope(pilita);
    apilar(&aux, desapilar(pilita));//arranco a comparar luego de este numero

    //recorro la pila mientras tiene elementos
    while(!pilavacia(pilita))
    {
        if(menor>tope(pilita))
        {
            //si el menor es mayor al tope de la pila
            menor=tope(pilita);//el nuevo menor es el tope
        }

        apilar(&aux, desapilar(pilita));//muevo el elemento a la pila auxiliar para seguir recorriendolo
    }

    while(!pilavacia(&aux))
    {
        if((menor==tope(&aux))&&(flag==0))
        {
            //si menor es igual al tope y la bandera no esta arriba
            menor=desapilar(&aux);//elimino el menor de aux
            flag=1;
        }
        else
        {
            //sino es el menor lo devuelvo a la pila
            apilar(pilita, desapilar(&aux));
        }
    }
}

/**5.
Realizar una función que saque el promedio de los elementos del arreglo.
**/
float promedioArreglo(int arreglo[], int validos)
{
    //declaro las variables
    int suma=0;//lo inicio en 0 para sumar elementos arriba
    float promedio;

    //sumo todos los elementos
    for(int i=0; i<validos; i++)
    {
        suma+=arreglo[i];
    }

    //calculo el promedio
    promedio=(float)suma/validos;//casteo el resultado a float ///NOTA, en mi compu no funciona si casteo cada elemento, solo funciona si casteo luego del signo igual una vez

    return promedio;
}

/**6.
Realizar dos funciones para a) pedirle al usuario una posición del arreglo
(con validaciones) y b) mostrar una posición determinada del arreglo.
**/
int pedirPosArreglo(int validos)
{
    //declaro variables
    int pos=0;
    //declaro una bandera
    int flag=0;

    while((flag==0))
    {
        system("cls");//limpio pantalla antes de pedir la posicion
        printf("BUSCAR ELEMENTO POR POSICION\n");
        printf("----------------------------\n");
        //interaccion con el usuario
        printf("Posiciones validas de 0 a %d\n", validos);
        printf("Digite la posicion que desea ver: ");
        fflush(stdin);//limpio el buffer
        scanf("%d", &pos);

        if(pos>validos)
        {
            //aviso del error
            printf("ERROR: la posicion esta fuera de los limites del arrego\n");
            printf("                                    Vuelva a intentarlo\n");
            //pausa para leer el mensaje
            system("pause");
            //luego limpio pantalla
            system("cls");
        }
        else
        {
            flag=1;//sale de preguntar
        }
    }

    return (pos-1);//retorno la posicion a buscar, resto 1 para buscar en el arreglo
}

void mostrarEnPosArreglo(int arreglo[], int pos)
{
    printf("pos[%d] -> %d", (pos+1), arreglo[pos]);
}

/**7.
Realizar una función para mostrar una pila sin invocar a la función mostrar(&pila).
No utilizar arreglos.
**/
void mostrarPila(Pila pilita)
{
    //declaro Pila auxiliar
    Pila aux;
    inicpila(&aux);

    //titulo de tope
    printf("TOPE\n");
    printf("----\n");
    //recorro la pila
    while(!pilavacia(&pilita))
    {
        //mientras pilita tenga datos
        printf("%d\n", tope(&pilita));//muestro el tope

        apilar(&aux, desapilar(&pilita));//desapilo pilita en aux para ver los siguientes elementos
    }
    //titulo base
    printf("----\n");
    printf("BASE\n");
}

/**FUNCION EXTRA MOSTRAR ARREGLO**/
void mostratArreglo(int arreglo[], int validos)
{
    //recorro el arreglo
    for(int i=0; i<validos; i++)
    {
        printf("[%d] -> %d\n", (i+1), arreglo[i]);
    }
}

