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
#define MOVER_DERECHA 'D'
#define MOVER_IZQUIERDA 'A'
#define MOVER_ARRIBA 'W'
#define MOVER_ABAJO 'S'
#define MOSTRAR_CONTROLES 'Z'
#define STITCH 'S'
#define REUBEN 'R'
#define LECHUGA 'L'
#define TOMATE 'T'
#define JAMON 'J'
#define QUESO 'Q'
#define MASA 'O'
#define CARNE 'B'
#define MILANESA 'I'
#define PAN 'N'
#define SALIDA 'P'
#define AGUJERO 'A'
#define FUEGO 'F'
#define HORNO 'H'
#define CUCHILLO 'C'

bool letra_es_valida(char movimiento)
{
    bool es_valida = false;
    if (movimiento == TOMAR_ALIMENTO || movimiento == CAMBIAR_PERSONAJE || movimiento == USAR_CUCHILLO || movimiento == INTERACTUAR_CON_MESA || movimiento == USAR_HORNO || movimiento == USAR_MATAFUEGOS || movimiento == MOVER_DERECHA || movimiento == MOVER_ABAJO || movimiento == MOVER_ARRIBA || movimiento == MOVER_IZQUIERDA)
    {
        es_valida = true;
    }
    return es_valida;
}

void mostrar_manual()
{
    printf("-Estos son los controles: %c %c %c %c (movimiento), %c (Tomar y soltar alimento), %c (Cambiar de personaje), %c (Usar cuchillo), %c (Usar horno), %c (Interactuar con la mesa), %c (Usar matafuegos).\n", MOVER_ARRIBA, MOVER_IZQUIERDA, MOVER_ABAJO, MOVER_DERECHA, TOMAR_ALIMENTO, CAMBIAR_PERSONAJE, USAR_CUCHILLO, USAR_HORNO, INTERACTUAR_CON_MESA, USAR_MATAFUEGOS);
}

void introduccion_al_juego()
{
    printf(" \
    Bienvenido a mi juego! Espero que lo puedas disfrutar. Vengo a comentarte unas cosas que deberias saber antes de jugar:\n \
    -Primero que nada es recomendable jugar en la resolucion 187x27 del compilador.\n");
    printf("     -Las letras %c y %c significan Stitch y Reuben respectivamente.\n", STITCH, REUBEN);
    printf("     -Es importante que le prestes atencion a los dialogos del juego ya que te van a ir actualizando lo que pasa en el momento, estos van a aparecer arriba de la matriz una vez que hayas realizado un movimiento.\n \
    -TEN CUIDADO, depende lo que respondas en el cuestionario va a afectar a la cantidad de comidas que vas a tener que cocinar, a mas caro el sandwich mas comidas!\n \
    -No podras atravesar: paredes, mesa, fuego y hornos. \n");
    mostrar_manual();
    printf("     -Al enviar la letra %c apareceran los controles por pantalla.\n", MOSTRAR_CONTROLES);
    printf("     -Algunas convenciones: %c (Fuego), %c (Agujero), %c (Puerta de salida/entrega), %c (horno), %c (cuchillo), %c (Lechuga), %c (Tomate), %c (Jamon), %c (Queso), %c (Masa), %c (Carne), %c (Milanesa), %c (Pan).\n", FUEGO, AGUJERO, SALIDA, HORNO, CUCHILLO, LECHUGA, TOMATE, JAMON, QUESO, MASA, CARNE, MILANESA, PAN);
    printf("\n");
}

void informacion_por_pantalla(juego_t juego)
{
    printf("Precio total: %i\n", juego.precio_total);
    if (juego.personaje_activo == juego.stitch.tipo)
    {
        printf("Personaje activo: %c\n", juego.stitch.tipo);
        printf("Objeto en mano: %c\n", juego.stitch.objeto_en_mano);
    }
    else
    {
        printf("Personaje activo: %c\n", juego.reuben.tipo);
        printf("Objeto en mano: %c\n", juego.reuben.objeto_en_mano);
    }
}

int main()
{
    char movimiento = ' ';
    int precio = 0;
    juego_t juego;
    srand((unsigned)time(NULL));

    introduccion_al_juego();
    calcular_precio_chambuchito(&precio);
    inicializar_juego(&juego, precio);
    imprimir_terreno(juego);

    while (estado_juego(juego) == 0)
    {
        imprimir_terreno(juego);
        informacion_por_pantalla(juego);
        printf("¿Que movimiento desea hacer?\n");
        scanf(" %c", &movimiento);
        if (letra_es_valida(movimiento))
        {
            realizar_jugada(&juego, movimiento);
        }
        else if (movimiento == MOSTRAR_CONTROLES)
        {
            mostrar_manual();
        }
        else
        {
            printf("Enviaste una letra que no es valida, intenta de nuevo!\n");
        }
    }

    return 0;
}
