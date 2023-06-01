#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "chambuchito.h"
#include "cocineritos.h"

#define TOMAR_ALIMENTO 'R'
#define CAMBIAR_PERSONAJE 'X'
#define USAR_CUCHILLO 'C'
#define INTERACTUAR_CON_MESA 'T'
#define USAR_HORNO 'H'
#define USAR_MATAFUEGOS 'M'
#define MOVER_DERECHA  'D'
#define MOVER_IZQUIERDA 'A'
#define MOVER_ARRIBA 'W'
#define MOVER_ABAJO 'S'


bool letra_es_valida(char movimiento){
   bool es_valida = false;
   if(movimiento == TOMAR_ALIMENTO || movimiento == CAMBIAR_PERSONAJE || movimiento == USAR_CUCHILLO || movimiento == INTERACTUAR_CON_MESA || movimiento == USAR_HORNO || movimiento ==  USAR_MATAFUEGOS || movimiento == MOVER_DERECHA || movimiento == MOVER_ABAJO || movimiento == MOVER_ARRIBA || movimiento == MOVER_IZQUIERDA){
    es_valida = true;
   }
   return es_valida;
}

void introduccion(){
    printf("Bienvenido a mi juego! Espero que lo puedas disfrutar. Vengo a comentarte unas cosas que deberias saber antes de jugar:\n");
    printf("-Las letras S y R significan Stitch y Reuben respectivamente.\n");
    printf("-Es importante que le prestes atencion a los dialogos del juego ya que te van a ir actualizando lo que pasa en el momento estos van a aparecer arriba de la matriz una vez que hayas realizado un movimiento.\n");
    printf("-Es recomendable jugarlo en la resolucion 80x24 del compilador.\n");
    printf("-TEN CUIDADO, depende lo que respondas en el cuestionario va a afectar a la cantidad de niveles que va a tener el juego.\n");
    printf("-No podras atravesar: paredes, mesa, fuego y hornos.\n");
    printf("\n");
}

int main()
{
    char movimiento = ' ';
    int precio = 0;
    juego_t juego;
    srand((unsigned)time(NULL));

    introduccion();
    calcular_precio_chambuchito(&precio);
    inicializar_juego(&juego, precio);

    while (estado_juego(juego) == 0)
    {
        imprimir_terreno(juego);
        printf("¿Que movimiento desea hacer?\n");
        scanf(" %c", &movimiento);
        if(letra_es_valida(movimiento)){
            realizar_jugada(&juego, movimiento);
        } else {
            printf("Enviaste una letra que no es valida, intenta de nuevo!\n");
        }
        
    }

    return 0;
}
