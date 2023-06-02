#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "cocineritos.h"
#include "chambuchito.h"

#define MAX_INGREDIENTES 10
#define MAX_PAREDES 200
#define MAX_HERRAMIENTAS 50
#define MAX_OBSTACULOS 50
#define MAX_COMIDA 5
#define MAX_COL 21
#define MAX_FIL 21
#define MAX_PAREDES 200
#define TOMAR_ALIMENTO 'R'
#define CAMBIAR_PERSONAJE 'X'
#define USAR_CUCHILLO 'C'
#define INTERACTUAR_CON_MESA 'T'
#define USAR_HORNO 'H'
#define USAR_MATAFUEGOS 'M'

const char VACIO = '.';
const char MANO_VACIA = 'V';
const char PARED = '#';
const char MESA = '_';
const char SALIDA = 'P';
const char AGUJERO = 'A';
const char FUEGO = 'F';
const char CUCHILLO = 'C';
const char HORNO = 'H';
const char PUERTA_DE_SALIDA = 'P';
const char MATAFUEGOS = 'M';
const char STITCH = 'S';
const char REUBEN = 'R';
const char ENSALADA = 'E';
const char PIZZA = 'P';
const char HAMBURGUESA = 'H';
const char SANDWICH = 'S';
const char LECHUGA = 'L';
const char TOMATE = 'T';
const char JAMON = 'J';
const char QUESO = 'Q';
const char MASA = 'O';
const char CARNE = 'B';
const char MILANESA = 'I';
const char PAN = 'N';
const char MOVER_DERECHA = 'D';
const char MOVER_IZQUIERDA = 'A';
const char MOVER_ARRIBA = 'W';
const char MOVER_ABAJO = 'S';

const int OBSTACULOS_POR_CUADRANTE = 10;
const int MITAD_DE_COLUMNAS = 10;
const int MITAD_DE_FILAS_TOTAL = 11;
const int MITAD_FILAS_PRIMER_CUADRANTE = 5;
const int MITAD_FILAS_SEGUNDO_CUADRANTE = 15;
const int CATEGORIA_PRECIO_1 = 100;
const int CATEGORIA_PRECIO_2 = 150;
const int CANTIDAD_INGREDIENTES_ENSALADA = 2;
const int CANTIDAD_LECHUGAS_ENSALADA = 1;
const int CANTIDAD_TOMATES_ENSALADA = 1;
const int CANTIDAD_INGREDIENTES_PIZZA = 3;
const int CANTIDAD_JAMONES_PIZZA = 1;
const int CANTIDAD_QUESOS_PIZZA = 1;
const int CANTIDAD_MASAS_PIZZA = 1;
const int CANTIDAD_INGREDIENTES_HAMBURGUESA = 4;
const int CANTIDAD_LECHUGA_HAMBURGUESA = 1;
const int CANTIDAD_TOMATE_HAMBURGUESA = 1;
const int CANTIDAD_PAN_HAMBURGUESA = 1;
const int CANTIDAD_CARNE_HAMBURGUESA = 1;
const int CANTIDAD_INGREDIENTES_SANDWICH = 6;
const int CANTIDAD_LECHUGAS_SANDWICH = 1;
const int CANTIDAD_TOMATES_SANDWICH = 1;
const int CANTIDAD_JAMONES_SANDWICH = 1;
const int CANTIDAD_QUESOS_SANDWICH = 1;
const int CANTIDAD_PAN_SANDWICH = 1;
const int CANTIDAD_MILANESAS_SANDWICH = 1;
const int POSICION_FILA_MESA = 10;
const int POSICION_COLUMNA_MESA = 10;
const int FILA_ARRIBA_DE_MESA = 9;
const int FILA_ABAJO_DE_MESA = 11;
const int POSICION_FILA_SALIDA = 20;
const int POSICION_COLUMNA_SALIDA = 10;
const int POSICION_FILA_STITCH = 5;
const int POSICION_COLUMNA_STITCH = 10;
const int POSICION_FILA_REUBEN = 5;
const int POSICION_COLUMNA_REUBEN = 10;
const int CANTIDAD_STITCHS = 1;
const int CANTIDAD_REUBENS = 1;
const int MAX_AGUJEROS_POR_CUADRANTE = 10;
const int MAX_FUEGOS = 1;
const int CANTIDAD_CUCHILLOS = 2;
const int CANTIDAD_HORNOS = 2;
const int CANTIDAD_MATAFUEGOS = 1;
const int POSICION_INICIAL_STITCH_FILA = 1;
const int POSICION_INICIAL_STITCH_COLUMNA = 1;
const int POSICION_INICIAL_REUBEN_FILA = 11;
const int POSICION_INICIAL_REUBEN_COLUMNA = 1;
const int MOVIMIENTOS_NECESARIOS_PARA_APARECER_UN_FUEGO = 15;
const int NUMERO_BASE_FILAS_RANDOM_PRIMER_CUADRANTE = 1;
const int NUMERO_BASE_FILAS_RANDOM_SEGUNDO_CUADRANTE = 11;
const int VARIACION_FILAS_RANDOM_PRIMER_CUADRANTE = 9;
const int VARIACION_FILAS_RANDOM_SEGUNDO_CUADRANTE = 9;
const int NUMERO_BASE_COLUMNAS_RANDOM = 1;
const int VARIACION_COLUMNAS_RANDOM = 19;
const int SIGUE_JUGANDO = 0;
const int PERDIO = -1;
const int GANO = 1;

// Pre: -
// pos: Añade la localizacion de las paredes al struct juego_t juego

void inicializar_nivel_paredes(coordenada_t paredes[MAX_PAREDES], int *tope_paredes)
{
  *tope_paredes = 0;
  for (int i = 0; i < MAX_FIL; i++)
  {
    for (int j = 0; j < MAX_COL; j++)
    {
      if ((j == 0 || j == 20) || (i == 0 || i == 10 || i == 20))
      {
        paredes[*tope_paredes].fil = i;
        paredes[*tope_paredes].col = j;
        (*tope_paredes)++;
      }
    }
  }
}

// VALIDACIONES

// Pre: -
// Pos: Valida que no este por encima de la mesa y por debajo

bool pisa_mesa(int numero_fila_random, int numero_columna_random)
{
  bool libre = true;
  if ((numero_fila_random == FILA_ARRIBA_DE_MESA && numero_columna_random == POSICION_COLUMNA_MESA) || (numero_fila_random == FILA_ABAJO_DE_MESA && numero_columna_random == POSICION_COLUMNA_MESA))
  {
    libre = false;
  }
  return libre;
}

// Pre: -
// Pos: Valida que no haya un char tipo PARED en una posicion

bool no_hay_pared(coordenada_t paredes[MAX_PAREDES], int tope_paredes, coordenada_t mesa, int numero_fila_random, int numero_columna_random)
{
  bool libre = true;

  for (int i = 0; i < tope_paredes; i++)
  {
    if ((paredes[i].fil == numero_fila_random && paredes[i].col == numero_columna_random) || (mesa.fil == numero_fila_random && mesa.col == numero_columna_random))
    {
      libre = false;
    }
  }
  return libre;
}

// Pre: -
// Pos: Valida que no haya un char tipo OBSTACULOS en una posicion

bool no_hay_obstaculo(objeto_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos, int numero_fila_random, int numero_columna_random)
{
  bool libre = true;
  for (int i = 0; i < tope_obstaculos; i++)
  {
    if (numero_fila_random == obstaculos[i].posicion.fil && numero_columna_random == obstaculos[i].posicion.col)
    {
      libre = false;
    }
  }

  return libre;
}

// Pre: -
// Pos: Valida que no haya un char tipo OBSTACULO: FUEGO en una posicion

bool no_hay_fuego(objeto_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos, int numero_fila_random, int numero_columna_random)
{
  bool libre = true;
  for (int i = 0; i < tope_obstaculos; i++)
  {
    if (numero_fila_random == obstaculos[i].posicion.fil && numero_columna_random == obstaculos[i].posicion.col && obstaculos[i].tipo == FUEGO)
    {
      libre = false;
    }
  }

  return libre;
}

// Pre: -
// Pos: Valida que no haya un char tipo FUEGO en toda la matriz

bool hay_fuego_en_alguna_parte(objeto_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos)
{
  bool libre = false;
  for (int i = 0; i < tope_obstaculos; i++)
  {
    if (obstaculos[i].tipo == FUEGO)
    {
      libre = true;
    }
  }
  return libre;
}

// Pre: -
// Pos: Valida que no haya un char tipo HERRAMIENTA en esa posicion

bool no_hay_herramienta(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int numero_fila_random, int numero_columna_random)
{
  bool libre = true;
  for (int i = 0; i < tope_herramientas; i++)
  {
    if (herramientas[i].posicion.fil == numero_fila_random && herramientas[i].posicion.col == numero_columna_random)
    {
      libre = false;
    }
  }
  return libre;
}

// Pre: -
// Pos: Valida que no haya un char tipo HERRAMIENTA: HORNO en esa posicion

bool no_hay_horno(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int numero_fila_random, int numero_columna_random)
{
  bool libre = true;
  for (int i = 0; i < tope_herramientas; i++)
  {
    if ((herramientas[i].posicion.fil == numero_fila_random) && (herramientas[i].posicion.col == numero_columna_random) && (herramientas[i].tipo == HORNO))
    {
      libre = false;
    }
  }
  return libre;
}

// Pre: -
// Pos: Valida que no haya un char tipo INGREDIENTE

bool no_hay_ingredientes(comida_t comida[MAX_COMIDA], int tope_comida, int numero_fila_random, int numero_columna_random)
{
  bool libre = true;
  for (int j = 0; j < tope_comida; j++)
  {
    for (int i = 0; i < comida[j].tope_ingredientes; i++)
    {
      if (comida[j].ingrediente[i].posicion.fil == numero_fila_random && comida[j].ingrediente[i].posicion.col == numero_columna_random)
      {
        libre = false;
      }
    }
  }
  return libre;
}

// Pre: -
// Pos: Valida que no haya un char tipo SALIDA

bool no_hay_puerta(coordenada_t salida, int fila, int columna)
{
  bool libre = true;
  if ((salida.fil == fila) && (salida.col == columna))
  {
    libre = false;
  }
  return libre;
}

// Pre: -
// Pos: Valida que no haya un char tipo PERSONAJE

bool no_hay_personaje(personaje_t stitch, personaje_t reuben, int fila, int columna)
{
  bool libre = true;
  if (((stitch.posicion.fil == fila) && (stitch.posicion.col == columna)) || ((reuben.posicion.fil == fila) && (reuben.posicion.col == columna)))
  {
    libre = false;
  }
  return libre;
}

// Pre: -
// Pos: Valida segun el precio_total y la comida actual del struct: juego si gana o no.

bool condicion_ganadora(juego_t juego)
{
  bool se_gano = false;
  if ((juego.precio_total <= CATEGORIA_PRECIO_1) && (juego.tope_comida_lista == juego.comida[juego.tope_comida - 1].tope_ingredientes) && (juego.comida_actual == PIZZA))
  {
    se_gano = true;
  }
  else if ((juego.precio_total > CATEGORIA_PRECIO_1) && (juego.precio_total <= CATEGORIA_PRECIO_2) && (juego.tope_comida_lista == juego.comida[juego.tope_comida - 1].tope_ingredientes) && (juego.comida_actual == HAMBURGUESA))
  {
    se_gano = true;
  }
  else if ((juego.precio_total > CATEGORIA_PRECIO_2) && (juego.tope_comida_lista == juego.comida[juego.tope_comida - 1].tope_ingredientes) && (juego.comida_actual == SANDWICH))
  {
    se_gano = true;
  }

  return se_gano;
}

// FIN VALIDACIONES

// HERRAMIENTAS DE PROGRAMACION

// Pre: -
// Pos: Calcula la distancia entre dos posiciones que se encuentran en la matriz;

int calcular_distancia(int fila1, int columna1, int fila2, int columna2)
{
  int distancia_total = 0;
  int resta_filas = abs(fila1 - fila2);
  int resta_columnas = abs(columna1 - columna2);

  distancia_total = resta_filas + resta_columnas;

  return distancia_total;
}

// Pre: Pasarle un struct y tope ya inicializado.
// Pos: Añade un ingrediente al vector segun el tipo, fila y columna que le pases.

void anadir_ingrediente_particular(comida_t comida[MAX_COMIDA], int tope_comida, int tope_ingrediente, char tipo, int fila, int col)
{
  comida[tope_comida].ingrediente[tope_ingrediente].posicion.fil = fila;
  comida[tope_comida].ingrediente[tope_ingrediente].posicion.col = col;
  comida[tope_comida].ingrediente[tope_ingrediente].tipo = tipo;
  comida[tope_comida].ingrediente[tope_ingrediente].esta_cortado = false;
  comida[tope_comida].ingrediente[tope_ingrediente].esta_cocinado = false;
  comida[tope_comida].tope_ingredientes++;
  // ejemplo de uso :
  //   anadir_ingrediente_particular((*juego).comida, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, LECHUGA, numero_fila_random, numero_columna_random);
}

// Pre: Pasarle un struct y tope ya inicializado.
// Pos: Añade un obstaculo al vector segun el tipo, fila y columna que le pases.

void anadir_obstaculo(objeto_t obstaculos[MAX_OBSTACULOS], int *tope_obstaculo, char tipo, int fila, int col)
{
  obstaculos[*tope_obstaculo].posicion.fil = fila;
  obstaculos[*tope_obstaculo].posicion.col = col;
  obstaculos[*tope_obstaculo].tipo = tipo;
  (*tope_obstaculo)++;
}

// Pre: Pasarle un struct y tope ya inicializado.
// Pos: Añade una herramienta al vector segun el tipo, fila y columna que le pases.

void anadir_herramienta(objeto_t herramientas[MAX_HERRAMIENTAS], int *tope_herramientas, char tipo, int fila, int col)
{
  herramientas[*tope_herramientas].posicion.fil = fila;
  herramientas[*tope_herramientas].posicion.col = col;
  herramientas[*tope_herramientas].tipo = tipo;
  (*tope_herramientas)++;
}

coordenada_t numeros_aleatorios_primer_cuadrante()
{
  coordenada_t coordenada;
  coordenada.fil = rand() % VARIACION_FILAS_RANDOM_PRIMER_CUADRANTE + NUMERO_BASE_FILAS_RANDOM_PRIMER_CUADRANTE;
  coordenada.col = rand() % VARIACION_COLUMNAS_RANDOM + NUMERO_BASE_COLUMNAS_RANDOM;
  return coordenada;
}

coordenada_t numeros_aleatorios_segundo_cuadrante()
{
  coordenada_t coordenada;
  coordenada.fil = rand() % VARIACION_FILAS_RANDOM_SEGUNDO_CUADRANTE + NUMERO_BASE_FILAS_RANDOM_SEGUNDO_CUADRANTE;
  coordenada.col = rand() % VARIACION_COLUMNAS_RANDOM + NUMERO_BASE_COLUMNAS_RANDOM;
  return coordenada;
}

// FIN HERRAMIENTAS DE PROGRAMACION

// INICIALIZACION

// AÑADIR OBSTACULOS, HERRAMIENTAS, MESA Y SALIDA

// Pre: -
// Pos: añade 20 OBSTACULOS del tipo AGUJEROS en el struct

void anadir_agujeros(objeto_t obstaculos[MAX_OBSTACULOS], int *tope_obstaculos, coordenada_t *posicion_agujeros)
{
  *tope_obstaculos = 0;

  // añade 10 obstaculos al primer cuadrante
  while (*tope_obstaculos < MAX_AGUJEROS_POR_CUADRANTE)
  {
    (*posicion_agujeros) = numeros_aleatorios_primer_cuadrante();
    if (pisa_mesa((*posicion_agujeros).fil, (*posicion_agujeros).col) && no_hay_obstaculo(obstaculos, *tope_obstaculos, (*posicion_agujeros).fil, (*posicion_agujeros).col))
    {
      anadir_obstaculo(obstaculos, tope_obstaculos, AGUJERO, (*posicion_agujeros).fil, (*posicion_agujeros).col);
    }
  }

  // añade 10 obstaculos al 2do cuadrante
  while (*tope_obstaculos < (2 * MAX_AGUJEROS_POR_CUADRANTE))
  {
    (*posicion_agujeros) = numeros_aleatorios_segundo_cuadrante();
    if (pisa_mesa((*posicion_agujeros).fil, (*posicion_agujeros).col) && no_hay_obstaculo(obstaculos, *tope_obstaculos, (*posicion_agujeros).fil, (*posicion_agujeros).col))
    {
      anadir_obstaculo(obstaculos, tope_obstaculos, AGUJERO, (*posicion_agujeros).fil, (*posicion_agujeros).col);
    }
  }
}

// Pre: -
// Pos: añade 1 OBSTACULO del tipo FUEGO al cuadrante de stitch

void anadir_fuego_cuadrante_stitch(juego_t *juego, coordenada_t *posicion_fuego)
{
  while ((*juego).tope_obstaculos < (MAX_FUEGOS + (2 * MAX_AGUJEROS_POR_CUADRANTE)))
  {
    (*posicion_fuego) = numeros_aleatorios_primer_cuadrante();
    if (pisa_mesa((*posicion_fuego).fil, (*posicion_fuego).col) && no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_fuego).fil, (*posicion_fuego).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_fuego).fil, (*posicion_fuego).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_fuego).fil, (*posicion_fuego).col) && no_hay_personaje((*juego).stitch, (*juego).reuben, (*posicion_fuego).fil, (*posicion_fuego).col))
    {
      anadir_obstaculo((*juego).obstaculos, &(*juego).tope_obstaculos, FUEGO, (*posicion_fuego).fil, (*posicion_fuego).col);
    }
  }
}

// Pre: -
// Pos: añade 1 OBSTACULO del tipo FUEGO al cuadrante de reuben

void anadir_fuego_cuadrante_reuben(juego_t *juego, coordenada_t *posicion_fuego)
{
  while ((*juego).tope_obstaculos < (MAX_FUEGOS + (2 * MAX_AGUJEROS_POR_CUADRANTE)))
  {
    (*posicion_fuego) = numeros_aleatorios_segundo_cuadrante();
    if (pisa_mesa((*posicion_fuego).fil, (*posicion_fuego).col) && no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_fuego).fil, (*posicion_fuego).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_fuego).fil, (*posicion_fuego).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_fuego).fil, (*posicion_fuego).col) && no_hay_puerta((*juego).salida, (*posicion_fuego).fil, (*posicion_fuego).col) && no_hay_personaje((*juego).stitch, (*juego).reuben, (*posicion_fuego).fil, (*posicion_fuego).col))
    {
      anadir_obstaculo((*juego).obstaculos, &(*juego).tope_obstaculos, FUEGO, (*posicion_fuego).fil, (*posicion_fuego).col);
    }
  }
}

// Pre: -
// Pos: añade 2 HERRAMIENTAS del tipo CUCHILLOS al cuadrante de stitch

void anadir_cuchillos(juego_t *juego, coordenada_t *posicion_cuchillos)
{

  (*juego).tope_herramientas = 0;

  while ((*juego).tope_herramientas < CANTIDAD_CUCHILLOS)
  {

    (*posicion_cuchillos) = numeros_aleatorios_primer_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_cuchillos).fil, (*posicion_cuchillos).col) && pisa_mesa((*posicion_cuchillos).fil, (*posicion_cuchillos).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_cuchillos).fil, (*posicion_cuchillos).col))
    {
      anadir_herramienta((*juego).herramientas, &(*juego).tope_herramientas, CUCHILLO, (*posicion_cuchillos).fil, (*posicion_cuchillos).col);
    }
  }
}

// Pre: -
// Pos: añade 2 HERRAMIENTAS del tipo HORNO al cuadrante de reuben

void anadir_hornos(juego_t *juego, coordenada_t *posicion_hornos)
{

  while ((*juego).tope_herramientas < (CANTIDAD_CUCHILLOS + CANTIDAD_HORNOS))
  {

    (*posicion_hornos) = numeros_aleatorios_segundo_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_hornos).fil, (*posicion_hornos).col) && pisa_mesa((*posicion_hornos).fil, (*posicion_hornos).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_hornos).fil, (*posicion_hornos).col))
    {
      anadir_herramienta((*juego).herramientas, &(*juego).tope_herramientas, HORNO, (*posicion_hornos).fil, (*posicion_hornos).col);
    }
  }
}

// Pre: -
// Pos: añade 1 HERRAMIENTA del tipo MATAFUEGO al cuadrante de stitch

void anadir_matafuegos_cuadrante_stitch(juego_t *juego, coordenada_t *posicion_fuego)
{

  while ((*juego).tope_herramientas < (CANTIDAD_CUCHILLOS + CANTIDAD_HORNOS + CANTIDAD_MATAFUEGOS))
  {
    (*posicion_fuego) = numeros_aleatorios_primer_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_fuego).fil, (*posicion_fuego).col) && pisa_mesa((*posicion_fuego).fil, (*posicion_fuego).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_fuego).fil, (*posicion_fuego).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_fuego).fil, (*posicion_fuego).col) && no_hay_puerta((*juego).salida, (*posicion_fuego).fil, (*posicion_fuego).col))
    {
      anadir_herramienta((*juego).herramientas, &(*juego).tope_herramientas, MATAFUEGOS, (*posicion_fuego).fil, (*posicion_fuego).col);
    }
  }
}

// Pre: -
// Pos: añade 1 HERRAMIENTA del tipo MATAFUEGO al cuadrante de reuben

void anadir_matafuegos_cuadrante_reuben(juego_t *juego, coordenada_t *posicion_fuego)
{

  while ((*juego).tope_herramientas < (CANTIDAD_CUCHILLOS + CANTIDAD_HORNOS + CANTIDAD_MATAFUEGOS))
  {
    (*posicion_fuego) = numeros_aleatorios_segundo_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_fuego).fil, (*posicion_fuego).col) && pisa_mesa((*posicion_fuego).fil, (*posicion_fuego).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_fuego).fil, (*posicion_fuego).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_fuego).fil, (*posicion_fuego).col) && no_hay_puerta((*juego).salida, (*posicion_fuego).fil, (*posicion_fuego).col))
    {
      anadir_herramienta((*juego).herramientas, &(*juego).tope_herramientas, MATAFUEGOS, (*posicion_fuego).fil, (*posicion_fuego).col);
    }
  }
}

// Pre: -
// Pos: añade 1 mesa en POSICION_FILA_MESA y POSICION_COLUMNA_MESA y una puerta en el cuadrante de reuben

void anadir_mesa_y_salida(juego_t *juego, coordenada_t *posicion_puerta)
{
  bool hay_mesa = false;

  (*juego).mesa.fil = POSICION_FILA_MESA;
  (*juego).mesa.col = POSICION_COLUMNA_MESA;

  while (hay_mesa == false)
  {
    (*posicion_puerta) = numeros_aleatorios_segundo_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_puerta).fil, (*posicion_puerta).col) && pisa_mesa((*posicion_puerta).fil, (*posicion_puerta).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_puerta).fil, (*posicion_puerta).col))
    {
      (*juego).salida.fil = (*posicion_puerta).fil;
      (*juego).salida.col = (*posicion_puerta).col;
      hay_mesa = true;
    }
  }
}

// FIN AÑADIR OBSTACULOS, HERRAMIENTAS, MESA Y SALIDA

// AÑADIR ALIMENTOS

// Pre: -
// Pos: Añade a un struct del tipo juego_t los ingredientes de un ENSALADA

void anadir_ensalada(juego_t *juego, coordenada_t *posicion_ingredientes)
{

  (*juego).comida[(*juego).tope_comida].tope_ingredientes = 0;

  while ((*juego).comida[(*juego).tope_comida].tope_ingredientes < CANTIDAD_LECHUGAS_ENSALADA)
  {
    (*posicion_ingredientes) = numeros_aleatorios_primer_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && pisa_mesa((*posicion_ingredientes).fil, (*posicion_ingredientes).col))
    {
      anadir_ingrediente_particular((*juego).comida, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, LECHUGA, (*posicion_ingredientes).fil, (*posicion_ingredientes).col);
    }
  }

  while ((*juego).comida[(*juego).tope_comida].tope_ingredientes < (CANTIDAD_LECHUGAS_ENSALADA + CANTIDAD_TOMATES_ENSALADA))
  {
    (*posicion_ingredientes) = numeros_aleatorios_primer_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && pisa_mesa((*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_ingredientes).fil, (*posicion_ingredientes).col))
    {
      anadir_ingrediente_particular((*juego).comida, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, TOMATE, (*posicion_ingredientes).fil, (*posicion_ingredientes).col);
    }
  }

  (*juego).comida[(*juego).tope_comida].tipo = ENSALADA;
  (*juego).comida_actual = ENSALADA;
  (*juego).tope_comida++;
}

// Pre: -
// Pos: Añade a un struct del tipo juego_t los ingredientes de un PIZZA

void anadir_pizza(juego_t *juego, coordenada_t *posicion_ingredientes)
{

  (*juego).comida[(*juego).tope_comida].tope_ingredientes = 0;

  while ((*juego).comida[(*juego).tope_comida].tope_ingredientes < CANTIDAD_JAMONES_PIZZA)
  {
    (*posicion_ingredientes) = numeros_aleatorios_primer_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && pisa_mesa((*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_ingredientes).fil, (*posicion_ingredientes).col))
    {
      anadir_ingrediente_particular((*juego).comida, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, JAMON, (*posicion_ingredientes).fil, (*posicion_ingredientes).col);
    }
  }

  while ((*juego).comida[(*juego).tope_comida].tope_ingredientes < (CANTIDAD_JAMONES_PIZZA + CANTIDAD_QUESOS_PIZZA))
  {
    (*posicion_ingredientes) = numeros_aleatorios_primer_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && pisa_mesa((*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_ingredientes).fil, (*posicion_ingredientes).col))
    {
      anadir_ingrediente_particular((*juego).comida, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, QUESO, (*posicion_ingredientes).fil, (*posicion_ingredientes).col);
    }
  }

  while ((*juego).comida[(*juego).tope_comida].tope_ingredientes < (CANTIDAD_JAMONES_PIZZA + CANTIDAD_QUESOS_PIZZA + CANTIDAD_MASAS_PIZZA))
  {
    (*posicion_ingredientes) = numeros_aleatorios_segundo_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && pisa_mesa((*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_puerta((*juego).salida, (*posicion_ingredientes).fil, (*posicion_ingredientes).col))
    {
      anadir_ingrediente_particular((*juego).comida, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, MASA, (*posicion_ingredientes).fil, (*posicion_ingredientes).col);
    }
  }
  (*juego).comida[(*juego).tope_comida].tipo = PIZZA;
  (*juego).comida_actual = PIZZA;
  (*juego).tope_comida++;
}

// Pre: -
// Pos: Añade a un struct del tipo juego_t los ingredientes de un HAMBURGUESA

void anadir_hamburguesa(juego_t *juego, coordenada_t *posicion_ingredientes)
{

  (*juego).comida[(*juego).tope_comida].tope_ingredientes = 0;

  while ((*juego).comida[(*juego).tope_comida].tope_ingredientes < CANTIDAD_LECHUGA_HAMBURGUESA)
  {
    (*posicion_ingredientes) = numeros_aleatorios_primer_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && pisa_mesa((*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_ingredientes).fil, (*posicion_ingredientes).col))
    {
      anadir_ingrediente_particular((*juego).comida, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, LECHUGA, (*posicion_ingredientes).fil, (*posicion_ingredientes).col);
    }
  }

  while ((*juego).comida[(*juego).tope_comida].tope_ingredientes < (CANTIDAD_LECHUGA_HAMBURGUESA + CANTIDAD_TOMATE_HAMBURGUESA))
  {
    (*posicion_ingredientes) = numeros_aleatorios_primer_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && pisa_mesa((*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_ingredientes).fil, (*posicion_ingredientes).col))
    {
      anadir_ingrediente_particular((*juego).comida, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, TOMATE, (*posicion_ingredientes).fil, (*posicion_ingredientes).col);
    }
  }

  while ((*juego).comida[(*juego).tope_comida].tope_ingredientes < (CANTIDAD_LECHUGA_HAMBURGUESA + CANTIDAD_TOMATE_HAMBURGUESA + CANTIDAD_PAN_HAMBURGUESA))
  {
    (*posicion_ingredientes) = numeros_aleatorios_primer_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && pisa_mesa((*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_ingredientes).fil, (*posicion_ingredientes).col))
    {
      anadir_ingrediente_particular((*juego).comida, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, PAN, (*posicion_ingredientes).fil, (*posicion_ingredientes).col);
    }
  }

  while ((*juego).comida[(*juego).tope_comida].tope_ingredientes < (CANTIDAD_LECHUGA_HAMBURGUESA + CANTIDAD_TOMATE_HAMBURGUESA + CANTIDAD_PAN_HAMBURGUESA + CANTIDAD_CARNE_HAMBURGUESA))
  {
    (*posicion_ingredientes) = numeros_aleatorios_segundo_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && pisa_mesa((*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_puerta((*juego).salida, (*posicion_ingredientes).fil, (*posicion_ingredientes).col))
    {
      anadir_ingrediente_particular((*juego).comida, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, CARNE, (*posicion_ingredientes).fil, (*posicion_ingredientes).col);
    }
  }

  (*juego).comida[(*juego).tope_comida].tipo = HAMBURGUESA;
  (*juego).comida_actual = HAMBURGUESA;
  (*juego).tope_comida++;
}

// Pre: -
// Pos: Añade a un struct del tipo juego_t los ingredientes de un SANDWICH

void anadir_sandwich(juego_t *juego, coordenada_t *posicion_ingredientes)
{

  (*juego).comida[(*juego).tope_comida].tope_ingredientes = 0;

  while ((*juego).comida[(*juego).tope_comida].tope_ingredientes < CANTIDAD_LECHUGAS_SANDWICH)
  {
    (*posicion_ingredientes) = numeros_aleatorios_primer_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && pisa_mesa((*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_ingredientes).fil, (*posicion_ingredientes).col))
    {
      anadir_ingrediente_particular((*juego).comida, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, LECHUGA, (*posicion_ingredientes).fil, (*posicion_ingredientes).col);
    }
  }

  while ((*juego).comida[(*juego).tope_comida].tope_ingredientes < (CANTIDAD_LECHUGAS_SANDWICH + CANTIDAD_TOMATES_SANDWICH))
  {
    (*posicion_ingredientes) = numeros_aleatorios_primer_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && pisa_mesa((*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_ingredientes).fil, (*posicion_ingredientes).col))
    {
      anadir_ingrediente_particular((*juego).comida, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, TOMATE, (*posicion_ingredientes).fil, (*posicion_ingredientes).col);
    }
  }

  while ((*juego).comida[(*juego).tope_comida].tope_ingredientes < (CANTIDAD_LECHUGAS_SANDWICH + CANTIDAD_TOMATES_SANDWICH + CANTIDAD_PAN_SANDWICH))
  {
    (*posicion_ingredientes) = numeros_aleatorios_primer_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && pisa_mesa((*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_ingredientes).fil, (*posicion_ingredientes).col))
    {
      anadir_ingrediente_particular((*juego).comida, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, PAN, (*posicion_ingredientes).fil, (*posicion_ingredientes).col);
    }
  }

  while ((*juego).comida[(*juego).tope_comida].tope_ingredientes < (CANTIDAD_LECHUGAS_SANDWICH + CANTIDAD_TOMATES_SANDWICH + CANTIDAD_PAN_SANDWICH + CANTIDAD_JAMONES_SANDWICH))
  {
    (*posicion_ingredientes) = numeros_aleatorios_primer_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && pisa_mesa((*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_ingredientes).fil, (*posicion_ingredientes).col))
    {
      anadir_ingrediente_particular((*juego).comida, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, JAMON, (*posicion_ingredientes).fil, (*posicion_ingredientes).col);
    }
  }

  while ((*juego).comida[(*juego).tope_comida].tope_ingredientes < (CANTIDAD_LECHUGAS_SANDWICH + CANTIDAD_TOMATES_SANDWICH + CANTIDAD_PAN_SANDWICH + CANTIDAD_JAMONES_SANDWICH + CANTIDAD_QUESOS_SANDWICH))
  {
    (*posicion_ingredientes) = numeros_aleatorios_primer_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && pisa_mesa((*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_ingredientes).fil, (*posicion_ingredientes).col))
    {
      anadir_ingrediente_particular((*juego).comida, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, QUESO, (*posicion_ingredientes).fil, (*posicion_ingredientes).col);
    }
  }

  while ((*juego).comida[(*juego).tope_comida].tope_ingredientes < (CANTIDAD_LECHUGAS_SANDWICH + CANTIDAD_TOMATES_SANDWICH + CANTIDAD_PAN_SANDWICH + CANTIDAD_JAMONES_SANDWICH + CANTIDAD_QUESOS_SANDWICH + CANTIDAD_MILANESAS_SANDWICH))
  {
    (*posicion_ingredientes) = numeros_aleatorios_segundo_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && pisa_mesa((*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_ingredientes).fil, (*posicion_ingredientes).col) && no_hay_puerta((*juego).salida, (*posicion_ingredientes).fil, (*posicion_ingredientes).col))
    {
      anadir_ingrediente_particular((*juego).comida, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, MILANESA, (*posicion_ingredientes).fil, (*posicion_ingredientes).col);
    }
  }
  (*juego).comida[(*juego).tope_comida].tipo = SANDWICH;
  (*juego).comida_actual = SANDWICH;
  (*juego).tope_comida++;
}

// FIN AÑADIR ALIMENTOS

// Pre: -
// Pos: Inicializa a stitch y reuben en el struct, con una posicion aleatoria en el mapa sin colisionar

void anadir_ambos_personajes(juego_t *juego, coordenada_t *posicion_personajes)
{
  int cantidad_personajes = 0;

  while (cantidad_personajes < CANTIDAD_STITCHS)
  {
    (*posicion_personajes) = numeros_aleatorios_primer_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_personajes).fil, (*posicion_personajes).col) && pisa_mesa((*posicion_personajes).fil, (*posicion_personajes).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_personajes).fil, (*posicion_personajes).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_personajes).fil, (*posicion_personajes).col))
    {
      (*juego).stitch.posicion.fil = (*posicion_personajes).fil;
      (*juego).stitch.posicion.col = (*posicion_personajes).col;
      (*juego).stitch.tipo = STITCH;
      cantidad_personajes++;
    }
  }

  while (cantidad_personajes < (CANTIDAD_STITCHS + CANTIDAD_REUBENS))
  {

    (*posicion_personajes) = numeros_aleatorios_segundo_cuadrante();
    if (no_hay_obstaculo((*juego).obstaculos, (*juego).tope_obstaculos, (*posicion_personajes).fil, (*posicion_personajes).col) && no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*posicion_personajes).fil, (*posicion_personajes).col) && pisa_mesa((*posicion_personajes).fil, (*posicion_personajes).col) && no_hay_ingredientes((*juego).comida, (*juego).tope_comida, (*posicion_personajes).fil, (*posicion_personajes).col))
    {
      (*juego).reuben.posicion.fil = (*posicion_personajes).fil;
      (*juego).reuben.posicion.col = (*posicion_personajes).col;
      (*juego).reuben.tipo = REUBEN;
      cantidad_personajes++;
    }
  }
}

void inicializar_juego(juego_t *juego, int precio)
{
  (*juego).movimientos = 0;
  (*juego).tope_comida_lista = 0;
  (*juego).tope_comida = 0;
  (*juego).personaje_activo = STITCH;
  (*juego).stitch.objeto_en_mano = MANO_VACIA;
  (*juego).reuben.objeto_en_mano = MANO_VACIA;
  (*juego).precio_total = precio;
  (*juego).comida_actual = MANO_VACIA;
  coordenada_t coordenadas_aleatorias;

  inicializar_nivel_paredes((*juego).paredes, &(*juego).tope_paredes);
  anadir_agujeros((*juego).obstaculos, &(*juego).tope_obstaculos, &coordenadas_aleatorias);
  anadir_cuchillos(juego, &coordenadas_aleatorias);
  anadir_hornos(juego, &coordenadas_aleatorias);
  anadir_ensalada(juego, &coordenadas_aleatorias);
  anadir_mesa_y_salida(juego, &coordenadas_aleatorias);
  anadir_ambos_personajes(juego, &coordenadas_aleatorias);
}

// FIN INICIALIZACION

// CREACION MATRIZ

// Pre: haber inicializado una matriz
// Pos: llena la matriz de vacio.
void limpiar_matriz(char matriz[MAX_FIL][MAX_COL])
{

  // primero lo lleno de "vacio"
  for (int i = 0; i < MAX_FIL; i++)
  {
    for (int j = 0; j < MAX_COL; j++)
    {
      matriz[i][j] = VACIO;
    }
  }
}

// Pre: pasarle un struct tipo juego_t ya inicializado.
// Pos: añade las paredes a la matriz segun su posicion.

void incorporar_paredes(coordenada_t paredes[MAX_PAREDES], int tope_paredes, char matriz[MAX_FIL][MAX_COL])
{
  for (int x = 0; x < tope_paredes; x++)
  {
    for (int i = 0; i < MAX_FIL; i++)
    {
      for (int j = 0; j < MAX_COL; j++)
      {
        if (paredes[x].fil == i && paredes[x].col == j)
        {
          matriz[i][j] = PARED;
        }
      }
    }
  }
}

// Pre: pasarle un struct tipo juego_t ya inicializado.
// Pos: añade los obstaculos a la matriz segun su posicion.

void incorporar_obstaculos(objeto_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos, char matriz[MAX_FIL][MAX_COL])
{
  for (int x = 0; x < tope_obstaculos; x++)
  {
    for (int i = 0; i < MAX_FIL; i++)
    {
      for (int j = 0; j < MAX_COL; j++)
      {
        if (obstaculos[x].posicion.fil == i && obstaculos[x].posicion.col == j)
        {
          matriz[i][j] = obstaculos[x].tipo;
        }
      }
    }
  }
}

// Pre: pasarle un struct tipo juego_t ya inicializado.
// Pos: añade las herramientas a la matriz segun su posicion.

void incorporar_herramientas(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, char matriz[MAX_FIL][MAX_COL])
{
  for (int x = 0; x < tope_herramientas; x++)
  {
    for (int i = 0; i < MAX_FIL; i++)
    {
      for (int j = 0; j < MAX_COL; j++)
      {
        if (herramientas[x].posicion.fil == i && herramientas[x].posicion.col == j)
        {
          matriz[i][j] = herramientas[x].tipo;
        }
      }
    }
  }
}

// Pre: pasarle un struct tipo juego_t ya inicializado.
// Pos: añade lamesa y la salida a la matriz segun su posicion.

void incorporar_mesa_y_salida(coordenada_t mesa, coordenada_t salida, char matriz[MAX_FIL][MAX_COL])
{
  matriz[mesa.fil][mesa.col] = MESA;
  matriz[salida.fil][salida.col] = SALIDA;
}

// Pre: pasarle un struct tipo juego_t ya inicializado.
// Pos: añade los ingredientes a la matriz segun su posicion.

void incorporar_ingredientes(comida_t comida[MAX_COMIDA], int tope_comida, char matriz[MAX_FIL][MAX_COL])
{
  for (int y = 0; y < tope_comida; y++)
  {
    for (int x = 0; x < comida[y].tope_ingredientes; x++)
    {
      for (int i = 0; i < MAX_FIL; i++)
      {
        for (int j = 0; j < MAX_COL; j++)
        {
          if (comida[y].ingrediente[x].posicion.fil == i && comida[y].ingrediente[x].posicion.col == j)
          {
            matriz[i][j] = comida[y].ingrediente[x].tipo;
          }
        }
      }
    }
  }
}

// Pre: pasarle un struct tipo juego_t ya inicializado.
// Pos: añade los personajes a la matriz segun su posicion.

void incorporar_personajes(personaje_t stitch, personaje_t reuben, char matriz[MAX_FIL][MAX_COL])
{
  matriz[stitch.posicion.fil][stitch.posicion.col] = STITCH;
  matriz[reuben.posicion.fil][reuben.posicion.col] = REUBEN;
}

// Pre: pasarle un struct tipo juego_t ya inicializado.
// Pos: incorpora todos los elementos de juego_t a la matriz segun su posicion.

void incorporar_elementos_en_matriz(juego_t *juego, char matriz[MAX_FIL][MAX_COL])
{
  incorporar_paredes((*juego).paredes, (*juego).tope_paredes, matriz);
  incorporar_obstaculos((*juego).obstaculos, (*juego).tope_obstaculos, matriz);
  incorporar_herramientas((*juego).herramientas, (*juego).tope_herramientas, matriz);
  incorporar_mesa_y_salida((*juego).mesa, (*juego).salida, matriz);
  incorporar_ingredientes((*juego).comida, (*juego).tope_comida, matriz);
  incorporar_personajes((*juego).stitch, (*juego).reuben, matriz);
}

// Pre: -
// Pos: imprime por pantalla la matriz.

void mostrar_nivel(char matriz[MAX_FIL][MAX_COL])
{
  for (int i = 0; i < MAX_FIL; i++)
  {
    for (int j = 0; j < MAX_COL; j++)
    {
      printf("%c", matriz[i][j]);
    }
    printf("\n");
  }
}

void imprimir_terreno(juego_t juego)
{
  char matriz[MAX_FIL][MAX_COL];

  limpiar_matriz(matriz);
  incorporar_elementos_en_matriz(&juego, matriz);
  mostrar_nivel(matriz);
}

// FIN CREACION MATRIZ

// CHEQUEOS

// Pre: -
// Pos: Chequea que el personaje no se meta en la pared ni en el fuego, si el personaje activo es reuben se fija que no colisione con un horno

void chequear_movimiento(juego_t *juego, char movimiento, personaje_t *jugador)
{

  if ((movimiento == MOVER_DERECHA) && (no_hay_pared((*juego).paredes, (*juego).tope_paredes, (*juego).mesa, (*jugador).posicion.fil, (*jugador).posicion.col + 1)) && (no_hay_fuego((*juego).obstaculos, (*juego).tope_obstaculos, (*jugador).posicion.fil, (*jugador).posicion.col + 1)) && no_hay_horno((*juego).herramientas, (*juego).tope_herramientas, (*juego).reuben.posicion.fil, ((*juego).reuben.posicion.col + 1)))
  {
    (*jugador).posicion.col++;
    if ((*juego).movimientos < MOVIMIENTOS_NECESARIOS_PARA_APARECER_UN_FUEGO)
    {
      (*juego).movimientos++;
    }
  }
  else if ((movimiento == MOVER_IZQUIERDA) && (no_hay_pared((*juego).paredes, (*juego).tope_paredes, (*juego).mesa, (*jugador).posicion.fil, (*jugador).posicion.col - 1)) && (no_hay_fuego((*juego).obstaculos, (*juego).tope_obstaculos, (*jugador).posicion.fil, (*jugador).posicion.col - 1)) && no_hay_horno((*juego).herramientas, (*juego).tope_herramientas, (*juego).reuben.posicion.fil, ((*juego).reuben.posicion.col - 1)))
  {
    (*jugador).posicion.col--;
    if ((*juego).movimientos < MOVIMIENTOS_NECESARIOS_PARA_APARECER_UN_FUEGO)
    {
      (*juego).movimientos++;
    }
  }
  else if ((movimiento == MOVER_ABAJO) && (no_hay_pared((*juego).paredes, (*juego).tope_paredes, (*juego).mesa, (*jugador).posicion.fil + 1, (*jugador).posicion.col)) && (no_hay_fuego((*juego).obstaculos, (*juego).tope_obstaculos, (*jugador).posicion.fil + 1, (*jugador).posicion.col)) && no_hay_horno((*juego).herramientas, (*juego).tope_herramientas, (*juego).reuben.posicion.fil + 1, ((*juego).reuben.posicion.col)))
  {
    (*jugador).posicion.fil++;
    if ((*juego).movimientos < MOVIMIENTOS_NECESARIOS_PARA_APARECER_UN_FUEGO)
    {
      (*juego).movimientos++;
    }
  }
  else if ((movimiento == MOVER_ARRIBA) && (no_hay_pared((*juego).paredes, (*juego).tope_paredes, (*juego).mesa, (*jugador).posicion.fil - 1, (*jugador).posicion.col)) && (no_hay_fuego((*juego).obstaculos, (*juego).tope_obstaculos, (*jugador).posicion.fil - 1, (*jugador).posicion.col)) && no_hay_horno((*juego).herramientas, (*juego).tope_herramientas, (*juego).reuben.posicion.fil - 1, ((*juego).reuben.posicion.col)))
  {
    (*jugador).posicion.fil--;
    if ((*juego).movimientos < MOVIMIENTOS_NECESARIOS_PARA_APARECER_UN_FUEGO)
    {
      (*juego).movimientos++;
    }
  }
  else
  {
    printf("%c: Me resulta imposible meterme ahi :u\n", (*jugador).tipo);
  }
}

// Pre: -
// Pos: Valida si reuben pasa por encima del apuerta y si reuben tiene un objeto cocinado o cortado en la mano, lo entrega.

void chequear_puerta(juego_t *juego)
{

  if (!no_hay_puerta((*juego).salida, (*juego).reuben.posicion.fil, (*juego).reuben.posicion.col) && ((*juego).personaje_activo == REUBEN))
  {

    for (int i = 0; i < (*juego).tope_comida; i++)
    {
      for (int j = 0; j < (*juego).comida[i].tope_ingredientes; j++)
      {

        if ((*juego).comida[i].ingrediente[j].tipo == (*juego).reuben.objeto_en_mano)
        {
          if ((*juego).comida[i].ingrediente[j].esta_cortado || (*juego).comida[i].ingrediente[j].esta_cocinado)
          {
            //    ingrediente_listo(juego, i, j);
            (*juego).comida_lista[(*juego).tope_comida_lista].tipo = (*juego).reuben.objeto_en_mano;
            (*juego).comida_lista[(*juego).tope_comida_lista].esta_cocinado = (*juego).comida[i].ingrediente[j].esta_cocinado;
            (*juego).comida_lista[(*juego).tope_comida_lista].esta_cortado = (*juego).comida[i].ingrediente[j].esta_cortado;
            (*juego).tope_comida_lista++;
            (*juego).reuben.objeto_en_mano = MANO_VACIA;
            printf("R: Una comida menos!\n");
          }
        }
      }
    }
  }
}

// Pre: -
// Pos: Cuando se termina de entregar un plato de comida añade el siguiento acorde al precio de juego_t y su comida actual.

void chequear_comidas(juego_t *juego)
{
  coordenada_t coordenadas_aleatorias;
  if (((*juego).precio_total <= CATEGORIA_PRECIO_1) && ((*juego).tope_comida_lista == (*juego).comida[(*juego).tope_comida - 1].tope_ingredientes))
  {

    if ((*juego).comida_actual == ENSALADA)
    {
      (*juego).tope_comida_lista = 0;
      anadir_pizza(juego, &coordenadas_aleatorias);
    }
  }
  else if ((CATEGORIA_PRECIO_1 < (*juego).precio_total) && ((*juego).precio_total <= CATEGORIA_PRECIO_2) && (*juego).tope_comida_lista == (*juego).comida[(*juego).tope_comida - 1].tope_ingredientes)
  {

    if ((*juego).comida_actual == ENSALADA)
    {
      (*juego).tope_comida_lista = 0;
      anadir_pizza(juego, &coordenadas_aleatorias);
    }
    else if ((*juego).comida_actual == PIZZA)
    {
      (*juego).tope_comida_lista = 0;
      anadir_hamburguesa(juego, &coordenadas_aleatorias);
    }
  }
  else if (((*juego).precio_total > CATEGORIA_PRECIO_2) && ((*juego).tope_comida_lista == (*juego).comida[(*juego).tope_comida - 1].tope_ingredientes))
  {

    if ((*juego).comida_actual == ENSALADA)
    {
      (*juego).tope_comida_lista = 0;
      anadir_pizza(juego, &coordenadas_aleatorias);
    }
    else if ((*juego).comida_actual == PIZZA)
    {
      (*juego).tope_comida_lista = 0;
      anadir_hamburguesa(juego, &coordenadas_aleatorias);
    }
    else if ((*juego).comida_actual == HAMBURGUESA)
    {
      (*juego).tope_comida_lista = 0;
      anadir_sandwich(juego, &coordenadas_aleatorias);
    }
  }
}

// Pre: -
// Pos: Si el personaje activo se encuentra por encima de un matafuego con sus manos vacias, entonces el personaje toma el matafuegos

void chequear_matafuegos(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, personaje_t *jugador)
{
  int i = 0;
  while (i < tope_herramientas)
  {
    if (!no_hay_herramienta(herramientas, tope_herramientas, (*jugador).posicion.fil, (*jugador).posicion.col) && (herramientas[i].posicion.fil == (*jugador).posicion.fil) && (herramientas[i].posicion.col == (*jugador).posicion.col) && (herramientas[i].tipo == MATAFUEGOS))
    {
      if ((*jugador).objeto_en_mano == MANO_VACIA)
      {
        herramientas[i].posicion.fil = -1;
        herramientas[i].posicion.col = -1;
        (*jugador).objeto_en_mano = MATAFUEGOS;
        i = tope_herramientas;
        printf("%c: Agarre el matafuegos!\n", (*jugador).tipo);
      }
    }
    i++;
  }
}

// Pre: -
// Pos: Se fija cuando hacer aparecer un fuego.

void chequear_aparecer_un_fuego(juego_t *juego)
{

  if ((*juego).movimientos == MOVIMIENTOS_NECESARIOS_PARA_APARECER_UN_FUEGO)
  {
    coordenada_t coordenadas_aleatorias;
    if ((*juego).personaje_activo == STITCH)
    {
      anadir_matafuegos_cuadrante_stitch(juego, &coordenadas_aleatorias);
      anadir_fuego_cuadrante_stitch(juego, &coordenadas_aleatorias);
    }
    else if ((*juego).personaje_activo == REUBEN)
    {
      anadir_matafuegos_cuadrante_reuben(juego, &coordenadas_aleatorias);
      anadir_fuego_cuadrante_reuben(juego, &coordenadas_aleatorias);
    }
  }
}

// FIN CHEQUEOS

// MOVIMIENTOS

// Pre: -
// Pos: Cambia de personaje

void personaje_activo(juego_t *juego)
{

  if ((*juego).personaje_activo == STITCH)
  {
    (*juego).personaje_activo = REUBEN;
  }
  else
  {
    (*juego).personaje_activo = STITCH;
  }
  printf("El personaje activo actual es %c!\n", (*juego).personaje_activo);
}

// Pre: -
// Pos: Dependiendo de si el personaje activo este arriba de un ingrediente y tiene sus manos vacias, podra tomarlo, a su vez si tiene algo en la mano no podra, y por ultimo si quiere soltar el ingrediente puede hacerlo si no hay nada en su posicion.

void tomar_ingrediente(comida_t comida[MAX_COMIDA], int tope_comida, objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, personaje_t *jugador)
{

  for (int i = 0; i < tope_comida; i++)
  {
    for (int j = 0; j < comida[i].tope_ingredientes; j++)
    {
      if (!no_hay_ingredientes(comida, tope_comida, (*jugador).posicion.fil, (*jugador).posicion.col) && ((*jugador).objeto_en_mano == MANO_VACIA))
      {

        if ((comida[i].ingrediente[j].posicion.fil == (*jugador).posicion.fil) && (comida[i].ingrediente[j].posicion.col == (*jugador).posicion.col))
        {
          (*jugador).objeto_en_mano = comida[i].ingrediente[j].tipo;
          comida[i].ingrediente[j].posicion.fil = -1;
          comida[i].ingrediente[j].posicion.col = -1;
          printf("%c: Tome un ingrediente del tipo %c\n", (*jugador).tipo, comida[i].ingrediente[j].tipo);
        }
      }
      else if (!no_hay_ingredientes(comida, tope_comida, (*jugador).posicion.fil, (*jugador).posicion.col) && ((*jugador).objeto_en_mano != MANO_VACIA))
      {
        j = comida[i].tope_ingredientes;
        i = tope_comida;
        printf("%c: Tengo las manos ocupadas :/\n", (*jugador).tipo);
      }
      else if (no_hay_ingredientes(comida, tope_comida, (*jugador).posicion.fil, (*jugador).posicion.col) && no_hay_herramienta(herramientas, tope_herramientas, (*jugador).posicion.fil, (*jugador).posicion.col) && (comida[i].ingrediente[j].tipo == (*jugador).objeto_en_mano))
      {
        comida[i].ingrediente[j].posicion.fil = (*jugador).posicion.fil;
        comida[i].ingrediente[j].posicion.col = (*jugador).posicion.col;
        (*jugador).objeto_en_mano = MANO_VACIA;
        printf("%c: Solte un ingrediente del tipo %c\n", (*jugador).tipo, comida[i].ingrediente[j].tipo);
      }
    }
  }
}

// Pre: -
// Pos: Permite a stitch cortar los ingredientes.

void usar_cuchillo(juego_t *juego)
{
  if ((*juego).personaje_activo == STITCH)
  {
    if (!no_hay_herramienta((*juego).herramientas, (*juego).tope_herramientas, (*juego).stitch.posicion.fil, (*juego).stitch.posicion.col) && ((*juego).stitch.objeto_en_mano != MANO_VACIA))
    {
      int i = 0;
      while (i < juego->tope_herramientas)
      {
        if ((*juego).herramientas[i].posicion.fil == (*juego).stitch.posicion.fil && (*juego).herramientas[i].posicion.col == (*juego).stitch.posicion.col)
        {

          for (int x = 0; x < juego->tope_comida; x++)
          {
            for (int y = 0; y < juego->comida[x].tope_ingredientes; y++)
            {
              if ((juego->comida[x].ingrediente[y].tipo == (*juego).stitch.objeto_en_mano) && (juego->comida[x].ingrediente[y].esta_cortado == false))
              {
                juego->comida[x].ingrediente[y].esta_cortado = true;
                printf("S: Corte el ingrediente que tenia en la mano jeje\n");
              }
              else if (((juego->comida[x].ingrediente[y].tipo == (*juego).stitch.objeto_en_mano) && (juego->comida[x].ingrediente[y].esta_cortado == false)) || juego->stitch.objeto_en_mano == MANO_VACIA)
              {
                i = juego->tope_herramientas;
              }
            }
          }
        }
        i++;
      }
    }
  }
}

// Pre: -
// Pos: permite al personaje_activo apagar un fuego cuando use el matafuegos a distancia manhattan <= 2 del mismo (con el matafuegos en la mano).

void usar_matafuegos(juego_t *juego, personaje_t *jugador)
{

  int i = 0;
  while (i < (*juego).tope_obstaculos)
  {
    if ((*juego).obstaculos[i].tipo == FUEGO)
    {
      if ((calcular_distancia((*jugador).posicion.fil, (*jugador).posicion.col, (*juego).obstaculos[i].posicion.fil, (*juego).obstaculos[i].posicion.col) <= 2) && ((*jugador).objeto_en_mano == MATAFUEGOS))
      {
        (*jugador).objeto_en_mano = MANO_VACIA;
        (*juego).tope_obstaculos--;
        (*juego).tope_herramientas--;
        (*juego).movimientos = 0;
        i = (*juego).tope_obstaculos;
        printf("%c: Use el matafuegos! Pero magicamente desaparecio :O\n", (*jugador).tipo);
      }
    }
    i++;
  }
}

// Pre: -
// Pos: Permite a los personajes poner y dejar ingredientes en la mesa

void interactuar_con_mesa(comida_t comida[MAX_COMIDA], int tope_comida, coordenada_t mesa, personaje_t *jugador)
{

  if ((calcular_distancia((*jugador).posicion.fil, (*jugador).posicion.col, mesa.fil, mesa.col) <= 1))
  {

    int i = 0;
    int j = 0;

    while (i < tope_comida)
    {
      while (j < comida[i].tope_ingredientes)
      {

        if ((comida[i].ingrediente[j].tipo == (*jugador).objeto_en_mano) && no_hay_ingredientes(comida, tope_comida, mesa.fil, mesa.col))
        {
          comida[i].ingrediente[j].posicion.fil = mesa.fil;
          comida[i].ingrediente[j].posicion.col = mesa.col;
          (*jugador).objeto_en_mano = MANO_VACIA;
          printf("%c: Deje el ingrediente en la mesa, aunque esta un poco sucia :3\n", (*jugador).tipo);
        }
        else if ((comida[i].ingrediente[j].posicion.fil == mesa.fil) && (comida[i].ingrediente[j].posicion.col == mesa.col) && ((*jugador).objeto_en_mano == MANO_VACIA))
        {
          (*jugador).objeto_en_mano = comida[i].ingrediente[j].tipo;
          comida[i].ingrediente[j].posicion.fil = -1;
          comida[i].ingrediente[j].posicion.col = -1;
          printf("%c: Tome el ingrediente de la mesa, esta lleno de polvo :v\n", (*jugador).tipo);
        }
        else if ((comida[i].ingrediente[j].posicion.fil == mesa.fil) && (comida[i].ingrediente[j].posicion.col == mesa.col) && ((*jugador).objeto_en_mano != MANO_VACIA))
        {
          printf("%c: No hay espacio en la mesa!\n", (*jugador).tipo);
          i = tope_comida;
          j = comida[i].tope_ingredientes;
        }
        j++;
      }
      i++;
    }
  }
}

// Pre: -
// Pos: Permite a Reuben usar el horno

void interactuar_con_horno(juego_t *juego)
{

  if ((*juego).personaje_activo == REUBEN)
  {
    for (int i = 0; i < (*juego).tope_herramientas; i++)
    {

      if (calcular_distancia((*juego).reuben.posicion.fil, (*juego).reuben.posicion.col, (*juego).herramientas[i].posicion.fil, (*juego).herramientas[i].posicion.col) == 1)
      {

        int j = 0;
        int k = 0;

        while (j < (*juego).tope_comida)
        {
          while (k < (*juego).comida[j].tope_ingredientes)
          {
            if (((*juego).reuben.objeto_en_mano == MASA || (*juego).reuben.objeto_en_mano == CARNE || (*juego).reuben.objeto_en_mano == MILANESA) && ((*juego).comida[j].ingrediente[k].tipo == (*juego).reuben.objeto_en_mano) && !(*juego).comida[j].ingrediente[k].esta_cocinado)
            {
              (*juego).comida[j].ingrediente[k].esta_cocinado = true;
              printf("R: Cocinadisimo!\n");
              k = (*juego).comida[j].tope_ingredientes;
              j = (*juego).tope_comida;
            }
            j++;
            k++;
          }
        }
      }
    }
  }
}

void chequear_jugada(juego_t *juego, char movimiento, personaje_t *jugador)
{
  switch (movimiento)
  {
  case CAMBIAR_PERSONAJE:
    personaje_activo(juego);
    break;
  case TOMAR_ALIMENTO:
    tomar_ingrediente((*juego).comida, (*juego).tope_comida, (*juego).herramientas, (*juego).tope_herramientas, &(*jugador));
    break;
  case USAR_CUCHILLO:
    if (!hay_fuego_en_alguna_parte((*juego).obstaculos, (*juego).tope_obstaculos))
    {
      usar_cuchillo(juego);
    }
    break;
  case USAR_MATAFUEGOS:
    usar_matafuegos(juego, &(*jugador));
    break;
  case INTERACTUAR_CON_MESA:
    if (!hay_fuego_en_alguna_parte((*juego).obstaculos, (*juego).tope_obstaculos))
    {
      interactuar_con_mesa((*juego).comida, (*juego).tope_comida, (*juego).mesa, &(*jugador));
    }
    break;
  case USAR_HORNO:
    interactuar_con_horno(juego);
    break;
  }
}
// FIN MOVIMIENTOS

void realizar_jugada(juego_t *juego, char movimiento)
{
  if ((*juego).personaje_activo == REUBEN)
  {
    chequear_movimiento(juego, movimiento, &(*juego).reuben);
    chequear_matafuegos((*juego).herramientas, (*juego).tope_herramientas, &(*juego).reuben);
    chequear_puerta(juego);
    chequear_jugada(juego, movimiento, &(*juego).reuben);
  }
  else
  {
    chequear_movimiento(juego, movimiento, &(*juego).stitch);
    chequear_matafuegos((*juego).herramientas, (*juego).tope_herramientas, &(*juego).stitch);
    chequear_jugada(juego, movimiento, &(*juego).stitch);
  }

  chequear_comidas(juego);
  chequear_aparecer_un_fuego(juego);
}

int estado_juego(juego_t juego)
{
  int resultado = SIGUE_JUGANDO;

  if (!no_hay_obstaculo(juego.obstaculos, juego.tope_obstaculos, juego.stitch.posicion.fil, juego.stitch.posicion.col) || !no_hay_obstaculo(juego.obstaculos, juego.tope_obstaculos, juego.reuben.posicion.fil, juego.reuben.posicion.col))
  {
    resultado = PERDIO;
  }
  else if (condicion_ganadora(juego))
  {
    resultado = GANO;
  }

  return resultado;
}
