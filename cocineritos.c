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
#define MAX_COL 21
#define MAX_FIL 21  
#define MAX_PAREDES 200

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
const int MAX_CUCHILLOS = 2;
const int MAX_HORNOS = 2;

// pre:
// pos: Añade la localizacion de las paredes al struct juego_t juego

void inicializar_nivel_paredes(juego_t* juego) {
(*juego).tope_paredes = 0;
    for (int i = 0; i < MAX_FIL; i++){
      for (int j = 0; j < MAX_COL; j++){
      if ((j == 0 || j == 21) || (i == 0 || i == 10 || i == 20)){
          (*juego).paredes[(*juego).tope_paredes].fil = i;
          (*juego).paredes[(*juego).tope_paredes].col = j;
          (*juego).tope_paredes ++;
          } 

          }
        }
        }
         
      
    


bool hay_pared(juego_t* juego,int numero_fila_random, int numero_columna_random){
  bool libre = false;

  for(int i = 0; i < juego->tope_paredes; i++){
    if(juego->paredes[i].fil != numero_fila_random || juego->paredes[i].col != numero_columna_random) {
      libre = true;
    } 
  }
 return libre;
}

bool hay_obstaculo(juego_t* juego, int numero_fila_random, int numero_columna_random) {
  bool libre = false;
  for(int i = 0; i < (*juego).tope_obstaculos; i++){
    if((*juego).obstaculos[i].posicion.fil != numero_fila_random || (*juego).obstaculos[i].posicion.col != numero_columna_random) {
      libre = true;
    } 
   }

  return libre;
}

bool hay_herramienta(juego_t* juego, int numero_fila_random, int numero_columna_random) {
  bool libre = false;
  for(int i = 0; i < MAX_FIL; i++){
    if((*juego).herramientas[i].posicion.fil != numero_fila_random || (*juego).herramientas[i].posicion.col != numero_columna_random) {
      libre = true;
    } 
  }
  return libre;
}



void anadir_obstaculos(juego_t* juego) {
 (*juego).tope_obstaculos = 0;

  // añade 10 obstaculos al primer cuadrante
  while((*juego).tope_obstaculos < 10) {
  int numero_fila_random = rand() % 8 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(hay_pared(juego, numero_fila_random, numero_columna_random)){
  (*juego).obstaculos[(*juego).tope_obstaculos].posicion.fil = numero_fila_random;
  (*juego).obstaculos[(*juego).tope_obstaculos].posicion.col = numero_columna_random;
  (*juego).obstaculos[(*juego).tope_obstaculos].tipo = AGUJERO;
  (*juego).tope_obstaculos ++;
  }
  }


  //añade 10 obstaculos al 2do cuadrante
  while((*juego).tope_obstaculos < MAX_OBSTACULOS_TOTAL) {
  int numero_fila_random = rand() % 8 + 12; 
  int numero_columna_random = rand() % 19 + 1;
  if(hay_pared(juego, numero_fila_random, numero_columna_random)){
  (*juego).obstaculos[(*juego).tope_obstaculos].posicion.fil = numero_fila_random;
  (*juego).obstaculos[(*juego).tope_obstaculos].posicion.col = numero_columna_random;
  (*juego).obstaculos[(*juego).tope_obstaculos].tipo = AGUJERO;
  (*juego).tope_obstaculos ++;
  }
  }
}

void anadir_herramientas(juego_t* juego) {

(*juego).tope_herramientas = 0;

while((*juego).tope_herramientas < MAX_CUCHILLOS){
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(hay_pared(juego, numero_fila_random, numero_columna_random) && hay_obstaculo(juego, numero_fila_random, numero_columna_random)){
    (*juego).herramientas[(*juego).tope_herramientas].posicion.fil = numero_fila_random;
    (*juego).herramientas[(*juego).tope_herramientas].posicion.col = numero_columna_random;
    (*juego).herramientas[(*juego).tope_herramientas].tipo = CUCHILLO;
    (*juego).tope_herramientas ++;

  }
}


while((*juego).tope_herramientas < 4){
  int numero_fila_random = rand() % 8 + 12;
  int numero_columna_random = rand() % 19 + 1;
  if(hay_pared(juego, numero_fila_random, numero_columna_random) && hay_obstaculo(juego, numero_fila_random, numero_columna_random)){
    (*juego).herramientas[(*juego).tope_herramientas].posicion.fil = numero_fila_random;
    (*juego).herramientas[(*juego).tope_herramientas].posicion.col = numero_columna_random;
    (*juego).herramientas[(*juego).tope_herramientas].tipo = HORNO;
    (*juego).tope_herramientas ++;


  }
}

}

void anadir_ensalada(juego_t* juego) {

  (*juego).tope_comida = 0;

  while((*juego).tope_comida < 1) {
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(hay_pared(juego, numero_fila_random, numero_columna_random) && hay_obstaculo(juego, numero_fila_random, numero_columna_random) && hay_herramienta(juego, numero_fila_random, numero_columna_random)){
  (*juego).comida[numero_fila_random].ingrediente[numero_fila_random].posicion.fil = numero_fila_random;
  (*juego).comida[numero_fila_random].ingrediente[numero_fila_random].posicion.col = numero_columna_random;
  (*juego).comida[numero_fila_random].tipo = LECHUGA;
  (*juego).tope_comida++;
  }
  }

  while((*juego).tope_comida < 2) {
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(hay_pared(juego, numero_fila_random, numero_columna_random) && hay_obstaculo(juego, numero_fila_random, numero_columna_random) && hay_herramienta(juego, numero_fila_random, numero_columna_random)){
  (*juego).comida[numero_fila_random].ingrediente[numero_fila_random].posicion.fil = numero_fila_random;
  (*juego).comida[numero_fila_random].ingrediente[numero_fila_random].posicion.col = numero_columna_random;
  (*juego).comida[numero_fila_random].tipo = TOMATE;
  (*juego).tope_comida ++;
  }
  }


}

/* void anadir_ingredientes(juego_t* juego, int precio){

 if(precio <= CATEGORIA_PRECIO_1){

 } else if(CATEGORIA_PRECIO_1 < precio && precio <= CATEGORIA_PRECIO_2) {

 } else if(precio > CATEGORIA_PRECIO_2){
  
 }

} */


void limpiar_matriz(char matriz[MAX_FIL][MAX_COL]){

    // primero lo lleno de "vacio"
    for(int i = 0; i < MAX_FIL; i ++){
        for (int j = 0; j < MAX_COL; j++){
        matriz[i][j] = VACIO;
        }
        
    }
  
}
void anadir_paredes(juego_t* juego, char matriz[MAX_FIL][MAX_COL]){
  for(int x = 0; x < juego->tope_paredes; x++){
  for(int i = 0; i < MAX_FIL; i++) {
    for(int j = 0; j < MAX_COL; j++) {
     if(juego->paredes[x].fil == i && juego->paredes[x].col == j){
     matriz[i][j] = PARED;
    } 
    }
  }
}
}


void anadir_elementos_en_matriz(juego_t* juego, char matriz[MAX_FIL][MAX_COL]) {


  anadir_paredes(juego, matriz);
  
  for(int x = 0; x < juego->tope_obstaculos; x++){
  for(int i = 0; i < MAX_FIL; i++) {
    for(int j = 0; j < MAX_COL; j++) {
     if(juego->obstaculos[x].posicion.fil == i && juego->obstaculos[x].posicion.col == j){
     matriz[i][j] = AGUJERO;
    } 
    }
  }
}
  for(int x = 0; x < juego->tope_herramientas; x++){
  for(int i = 0; i < MAX_FIL; i++) {
    for(int j = 0; j < MAX_COL; j++) {
     if(juego->herramientas[x].posicion.fil == i && juego->herramientas[x].posicion.col == j){
     if(juego->herramientas[x].tipo == CUCHILLO) {
      matriz[i][j] = CUCHILLO;
     } else if(juego->herramientas[x].tipo == HORNO){
      matriz[i][j] = HORNO;
     }
    } 
    }
  }
}

}

void mostrar_nivel(char matriz[MAX_FIL][MAX_COL]) {
    for (int i = 0; i <= MAX_FIL; i++){
     for (int j = 0; j <= MAX_COL; j++){
        printf("%c", matriz[i][j]);
     }
     printf("\n");
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

void inicializar_juego(juego_t* juego, int precio) {
 char matriz[MAX_FIL][MAX_COL];

  inicializar_nivel_paredes(juego);
  anadir_obstaculos(juego);
  anadir_herramientas(juego);
  // anadir_ingredientes(juego, precio);
 // anadir_personajes_mesa_y_salida(juego);



  limpiar_matriz(matriz);
  anadir_elementos_en_matriz(juego, matriz);
  mostrar_nivel(matriz);
}
