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


// Pos: Devuelve una posicion randon en el primer cuadrante, solo toma lugares libres (sin pared, solo vacio) 
void aleatorizar_numeros_primer_cuadrante(char nivel[MAX_FIL][MAX_COL],int* numero_fila_random,int* numero_columna_random) {
  (*numero_fila_random) = rand() % 9 + 1;
  (*numero_columna_random) = rand() % 19 + 1;

   while(nivel[*numero_fila_random][*numero_columna_random] != VACIO){
     (*numero_fila_random) = rand() % 9 + 1;
     (*numero_columna_random) = rand() % 19 + 1;
   }
}

void aleatorizar_numeros_segundo_cuadrante(char nivel[MAX_FIL][MAX_COL], int* numero_fila_random, int* numero_columna_random) {
  (*numero_fila_random) = rand() % 9 + 10; 
  (*numero_columna_random) = rand() % 19 + 1;

   while(nivel[*numero_fila_random][*numero_columna_random] != VACIO){
     (*numero_fila_random) = rand() % 8 + 12;
     (*numero_columna_random) = rand() % 19 + 1;
   }
}

// pre:
// pos: crea una matriz 21x21 con sus respectivas paredes y piso,
void inicializar_nivel_vacio_y_paredes(char nivel[MAX_FIL][MAX_COL]) {
    // primero lo lleno de "vacio"
    for(int i = 0; i <= MAX_FIL; i ++){

        for (int j = 0; j <= MAX_COL; j++){
        nivel[i][j] = VACIO;
        }
        
    }
    // luego le añado las paredes
    for (int i = 0; i <= MAX_FIL; i++){
      for (int j = 0; j <= MAX_COL; j++){
        if(i == 0 || i == 10 || i == 20) {
            nivel[i][j] = PARED;
        } else if (i != 1 && i != 10 && i != 20){
          if (j == 0 || j == 21) {
            nivel[i][j] = PARED;
          }
        }
         
      }
    }
}

void añadir_obstaculos_mesa_y_salida(char nivel[MAX_FIL][MAX_COL]) {
  int cant_agujeros_arriba = 0;
  int cant_agujeros_abajo = 0;
  int num_fila_aleatorio = 0;
  int num_col_aleatorio = 0;

   //añado 10 obstaculos aleatorios en el cuadrante superior
  while(cant_agujeros_arriba < 10){
      aleatorizar_numeros_primer_cuadrante(nivel, &num_fila_aleatorio, &num_col_aleatorio);
      nivel[num_fila_aleatorio][num_col_aleatorio] = AGUJERO;
      cant_agujeros_arriba += 1;
  }

      


   // añado 10 obstaculos aleatorios en el cuadrante inferior

   while(cant_agujeros_abajo < 10) {
      aleatorizar_numeros_segundo_cuadrante(nivel, &num_fila_aleatorio, &num_col_aleatorio);
      nivel[num_fila_aleatorio][num_col_aleatorio] = AGUJERO;
      cant_agujeros_abajo += 1;
  }
  nivel[10][MITAD_DE_COLUMNAS] = MESA;
  nivel[20][MITAD_DE_COLUMNAS] = SALIDA;
}

void añadir_herramientas(char nivel[MAX_FIL][MAX_COL]){
 int cant_cuchillos = 0;
 int cant_hornos = 0;
  int num_fila_aleatorio = 0;
  int num_col_aleatorio = 0;

  // añado 2 cuchillos de forma aleatoria  en el cuadrante superior
 while(cant_cuchillos < 2) {

  aleatorizar_numeros_primer_cuadrante(nivel, &num_fila_aleatorio, &num_col_aleatorio);
  nivel[num_fila_aleatorio][num_col_aleatorio] = CUCHILLO;
  cant_cuchillos += 1;
      
  }
  
  // añado 2 hornos de forma aleatoria en el cuadrante inferior
  while(cant_hornos < 2) {

  aleatorizar_numeros_segundo_cuadrante(nivel, &num_fila_aleatorio, &num_col_aleatorio);
  nivel[num_fila_aleatorio][num_col_aleatorio] = HORNO;
  cant_hornos += 1;
      
  }
}

 



void añadir_ensalada(char nivel[MAX_FIL][MAX_COL]) {
  int cant_lechuga = 0;

  for(int i = 0; i < CANTIDAD_INGREDIENTES_ENSALADA; i++) {
   int numero_fila_random = rand() % 9 + 1;
   int numero_columna_random = rand() % 19 + 1;

  while(nivel[numero_fila_random][numero_columna_random] != VACIO){
     numero_fila_random = rand() % 9 + 1;
     numero_columna_random = rand() % 19 + 1;
  }

   if(cant_lechuga < 1 && nivel[numero_fila_random][numero_columna_random] == VACIO) {
    nivel[numero_fila_random][numero_columna_random] = LECHUGA;
    cant_lechuga ++;
   } else if (nivel[numero_fila_random][numero_columna_random] == VACIO) {
    nivel[numero_fila_random][numero_columna_random] = TOMATE;
   }
  }
}

void añadir_pizza(char nivel[MAX_FIL][MAX_COL]) {

  int cantidad_de_ingredientes_total = 0;
  int numero_fila_random_primer_cuadrante = 0;
  int numero_columna_random_primer_cuadrante = 0;
  int numero_fila_random_segundo_cuadrante = 0;
  int numero_columna_random_segundo_cuadrante = 0;

  while(cantidad_de_ingredientes_total < CANTIDAD_INGREDIENTES_PIZZA) {

   aleatorizar_numeros_primer_cuadrante(nivel, &numero_fila_random_primer_cuadrante, &numero_columna_random_primer_cuadrante);
   aleatorizar_numeros_segundo_cuadrante(nivel, &numero_fila_random_segundo_cuadrante, &numero_columna_random_segundo_cuadrante);

   if(cantidad_de_ingredientes_total < 1) {
    nivel[numero_fila_random_primer_cuadrante][numero_columna_random_primer_cuadrante] = JAMON;
    cantidad_de_ingredientes_total ++;
   } else if (cantidad_de_ingredientes_total < 2) {
    nivel[numero_fila_random_primer_cuadrante][numero_columna_random_primer_cuadrante] = QUESO;
    cantidad_de_ingredientes_total ++;
   } else {
    nivel[numero_fila_random_segundo_cuadrante][numero_columna_random_segundo_cuadrante] = MASA;
    cantidad_de_ingredientes_total ++;
   }
  }

}



void añadir_ingredientes(char nivel[MAX_FIL][MAX_COL],int precio) {
  //primero añado ensalada y pizza
  if (precio <= CATEGORIA_PRECIO_1) {
  añadir_ensalada(nivel);
  añadir_pizza(nivel);
  } else if (CATEGORIA_PRECIO_1 < precio && precio <= CATEGORIA_PRECIO_2) {
  añadir_ensalada(nivel);
  añadir_pizza(nivel);

  }
}



void añadir_personajes(char nivel[MAX_FIL][MAX_COL]) {
  nivel[MITAD_FILAS_PRIMER_CUADRANTE][MITAD_DE_COLUMNAS] = STITCH;
  nivel[MITAD_FILAS_SEGUNDO_CUADRANTE][MITAD_DE_COLUMNAS] = REUBEN;
}


void mostrar_nivel(char nivel[MAX_FIL][MAX_COL]) {
    for (int i = 0; i <= MAX_FIL; i++){
     for (int j = 0; j <= MAX_COL; j++){
        printf("%c", nivel[i][j]);
     }
     printf("\n");
    }
    
}



void inicializar_juego(int precio) {
  char nivel[MAX_FIL][MAX_COL];

  inicializar_nivel_vacio_y_paredes(nivel);
  añadir_obstaculos_mesa_y_salida(nivel);
  añadir_herramientas(nivel);
  añadir_ingredientes(nivel, precio);
  añadir_personajes(nivel);




  mostrar_nivel(nivel);
}
