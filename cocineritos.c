#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cocineritos.h"
#include "chambuchito.h"

#define MAX_INGREDIENTES 10
#define MAX_PAREDES 200
#define MAX_HERRAMIENTAS 50
#define MAX_OBSTACULOS 50
#define MAX_COMIDA 5
#define MAX_COL 20
#define MAX_FIL 20  


const char VACIO = '.';
const char PARED = '#';
const char MESA = '_';
const char SALIDA = 'P';
const char AGUJERO = 'A';
const char CUCHILLO = 'C';
const char HORNO = 'H';
const char STITCH = 'S';
const char REUBEN = 'R';
const char LECHUGA = 'L';
const char TOMATE = 'T';
const char JAMON = 'J';
const char QUESO = 'Q';
const char MASA = 'O';

const int OBSTACULOS_POR_CUADRANTE = 10;
const int MITAD_DE_COLUMNAS = 10;
const int MITAD_DE_FILAS_TOTAL = 11;
const int MITAD_FILAS_PRIMER_CUADRANTE = 5;
const int MITAD_FILAS_SEGUNDO_CUADRANTE = 15;
const int CATEGORIA_PRECIO_1 = 100;
const int CATEGORIA_PRECIO_2 = 150;
const int CANTIDAD_INGREDIENTES_ENSALADA = 2;
const int CANTIDAD_INGREDIENTES_PIZZA = 3;
const int POSICION_FILA_MESA = 10;
const int POSICION_COLUMNA_MESA = 10;
const int POSICION_FILA_SALIDA = 20;
const int POSICION_COLUMNA_SALIDA = 10;
const int POSICION_FILA_STITCH = 5;
const int POSICION_COLUMNA_STITCH = 10;
const int POSICION_FILA_REUBEN = 5;
const int POSICION_COLUMNA_REUBEN = 10;
const int MAX_OBSTACULOS_POR_CUADRANTE = 10;
const int MAX_OBSTACULOS_TOTAL = 20;


// pre:
// pos: Añade la localizacion de las paredes al struct juego_t juego

void inicializar_nivel_paredes(juego_t* juego) {

    for (int i = 0; i <= MAX_FIL; i++){
      for (int j = 0; j <= MAX_COL; j++){
        if(i == 0 || i == 10 || i == 20) {
          (*juego).paredes[i].fil = i;
          (*juego).paredes[i].col = j;
        
        } else if (i != 1 && i != 10 && i != 20){
          if (j == 0 || j == 21) {
          (*juego).paredes[i].fil = i;
          (*juego).paredes[i].col = j;
          }
        }
         
      }
    }
}

bool hay_pared(juego_t* juego,int numero_fila_random, int numero_columna_random){
  bool ocupado = false;

  for(int i = 0; i < MAX_FIL; i++){
    if((*juego).paredes[i].fil == numero_fila_random && (*juego).paredes[i].col == numero_columna_random) {
      ocupado = false;
    } else {
      ocupado = true;
    }
  }
 return ocupado;
}


void anadir_obstaculos(juego_t* juego) {
 (*juego).tope_obstaculos = 0;
 
  // añade 10 obstaculos al primer cuadrante
  while((*juego).tope_obstaculos < MAX_OBSTACULOS_POR_CUADRANTE) {
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  while(hay_pared(juego, numero_fila_random, numero_columna_random)){
  (*juego).obstaculos[numero_fila_random].posicion.fil = numero_fila_random;
  (*juego).obstaculos[numero_fila_random].posicion.col = numero_columna_random;
  (*juego).obstaculos[numero_fila_random].tipo = AGUJERO;
  (*juego).tope_obstaculos ++;
  }
  }

  //añade 10 obstaculos al 2do cuadrante
  while((*juego).tope_obstaculos < MAX_OBSTACULOS_TOTAL) {
  int numero_fila_random = rand() % 9 + 10; 
  int numero_columna_random = rand() % 19 + 1;
  while(hay_pared(juego, numero_fila_random, numero_columna_random)){
  (*juego).obstaculos[numero_fila_random].posicion.fil = numero_fila_random;
  (*juego).obstaculos[numero_fila_random].posicion.col = numero_columna_random;
  (*juego).obstaculos[numero_fila_random].tipo = AGUJERO;
  (*juego).tope_obstaculos ++;
  }
  }
}

/* void anadir_personajes_mesa_y_salida(juego_t* juego){


  (*juego).stitch.posicion.fil = POSICION_FILA_STITCH;
  (*juego).stitch.posicion.col = POSICION_COLUMNA_STITCH;
  (*juego).reuben.posicion.fil = POSICION_FILA_REUBEN;
  (*juego).reuben.posicion.col = POSICION_COLUMNA_REUBEN;
  (*juego).mesa.fil = POSICION_FILA_MESA;
  (*juego).mesa.col = POSICION_COLUMNA_MESA;
  (*juego).salida.fil = POSICION_FILA_SALIDA;
  (*juego).salida.col = POSICION_COLUMNA_SALIDA;

} */

void inicializar_juego(juego_t* juego) {


  inicializar_nivel_paredes(juego);
  anadir_obstaculos(juego);
 // anadir_personajes_mesa_y_salida(juego);




}
