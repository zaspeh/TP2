#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cocineritos.h"

#define MAX_COL 20
#define MAX_FIL 20  

const char VACIO = '.';
const char PARED = '#';
const char MESA = '_';
const char SALIDA = 'S';
const char AGUJERO = 'A';
const char CUCHILLO = 'C';
const char HORNO = 'H';

// pre:
// pos: crea la matriz 21x21 con sus respectivas paredes, piso, mesa y salida.
void inicializar_nivel(char nivel[MAX_FIL][MAX_COL]) {
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
    nivel[10][10] = MESA;
    nivel[20][10] = SALIDA;
}

void añadir_obstaculos(char nivel[MAX_FIL][MAX_COL]) {
  int cant_agujeros_arriba = 0;
  int cant_agujeros_abajo = 0;

   //añado 10 obstaculos aleatorios en el cuadrante superior
    for (int i = 0; i < 11; i++){
    for (int j = 0; j < MAX_COL; j++){
 if(cant_agujeros_arriba <= 10) {
        int num_fila_aleatorio = rand() % 10 + 0;
        int num_col_aleatorio = rand() % 20 + 0;

   if(nivel[num_fila_aleatorio][num_col_aleatorio] != PARED){
      nivel[num_fila_aleatorio][num_col_aleatorio] = AGUJERO;
      cant_agujeros_arriba += 1;
      }

      
    }
  }
 }

// añado 10 obstaculos aleatorios en el cuadrante inferior
 for (int i = 11; i < 21; i++){
  for (int j = 0; j < MAX_COL; j++){
 if(cant_agujeros_abajo < 10) {
        int num_fila_aleatorio = rand() % 10 + 11;
        int num_col_aleatorio = rand() % 20 + 0;

   if(nivel[num_fila_aleatorio][num_col_aleatorio] != PARED){
      nivel[num_fila_aleatorio][num_col_aleatorio] = AGUJERO;
      cant_agujeros_abajo += 1;
      }
    }
  }
 }


}

void añadir_herramientas(char nivel[MAX_FIL][MAX_COL]){
 int cant_cuchillos = 0;
 int cant_hornos = 0;

// añado 2 cuchillos de forma aleatoria  en el cuadrante superior
   for (int i = 0; i < 11; i++){
  for (int j = 0; j < MAX_COL; j++){
 if(cant_cuchillos < 2) {
        int num_fila_aleatorio = rand() % 10 + 0;
        int num_col_aleatorio = rand() % 20 + 0;

   if(nivel[num_fila_aleatorio][num_col_aleatorio] != PARED && nivel[num_fila_aleatorio][num_col_aleatorio] != AGUJERO){
      nivel[num_fila_aleatorio][num_col_aleatorio] = CUCHILLO;
      cant_cuchillos += 1;
      }
    }
  }
 }

// añado 2 hornos de forma aleatoria en el cuadrante inferior
  for (int i = 11; i < 21; i++){
  for (int j = 0; j < MAX_COL; j++){
 if(cant_hornos < 2) {
        int num_fila_aleatorio = rand() % 10 + 11;
        int num_col_aleatorio = rand() % 20 + 0;

   if(nivel[num_fila_aleatorio][num_col_aleatorio] != PARED && nivel[num_fila_aleatorio][num_col_aleatorio] != AGUJERO && nivel[num_fila_aleatorio][num_col_aleatorio] != CUCHILLO){
      nivel[num_fila_aleatorio][num_col_aleatorio] = HORNO;
      cant_hornos += 1;
      }
    }
  }
 }



}



void mostrar_nivel(char nivel[MAX_FIL][MAX_COL]) {
    for (int i = 0; i <= MAX_FIL; i++){
     for (int j = 0; j <= MAX_COL; j++){
        printf("%c", nivel[i][j]);
     }
     printf("\n");
    }
    
}




int main() {
  char nivel[MAX_FIL][MAX_COL];
  inicializar_nivel(nivel);
  añadir_obstaculos(nivel);
  añadir_herramientas(nivel);



  mostrar_nivel(nivel);
 return 0;
}