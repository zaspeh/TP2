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
const char MOVER_DERECHA = 'D';
const char MOVER_IZQUIERDA = 'A';
const char MOVER_ARRIBA = 'W';
const char MOVER_ABAJO = 'S';
const char ENSALADA = 'E';
const char TOMAR_ALIMENTO = 'R';
const char CAMBIAR_PERSONAJE = 'X';

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
const int POSICION_INICIAL_STITCH_FILA = 1;
const int POSICION_INICIAL_STITCH_COLUMNA = 1;
const int POSICION_INICIAL_REUBEN_FILA = 11;
const int POSICION_INICIAL_REUBEN_COLUMNA = 1;

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
         



// VALIDACIONES 


   
      
bool puedo_agregar(int numero_fila_random, int numero_columna_random){
  bool libre = true;
  if ((numero_fila_random == 10 && numero_columna_random == 11) || (numero_fila_random == 12 && numero_columna_random == 11)) {
    libre = false;
  } 
  return libre;
}


bool no_hay_pared(juego_t juego,int numero_fila_random, int numero_columna_random){
  bool libre = true;

  for(int i = 0; i <= juego.tope_paredes; i++){
    if(juego.paredes[i].fil == numero_fila_random && juego.paredes[i].col == numero_columna_random) {
      libre = false;
    } 
  }
 return libre;
}

bool no_hay_obstaculo(juego_t juego, int numero_fila_random, int numero_columna_random) {
  bool libre = true;
  for(int i = 0; i <= juego.tope_obstaculos; i++){
    if(juego.obstaculos[i].posicion.fil == numero_fila_random && juego.obstaculos[i].posicion.col == numero_columna_random) {
      libre = false;
    } 
   }

  return libre;
}

bool no_hay_herramienta(juego_t juego, int numero_fila_random, int numero_columna_random) {
  bool libre = true;
  for(int i = 0; i <= juego.tope_herramientas; i++){
    if(juego.herramientas[i].posicion.fil == numero_fila_random && juego.herramientas[i].posicion.col == numero_columna_random) {
      libre = false;
    } 
  }
  return libre;
}

bool no_hay_ingredientes(juego_t juego, int numero_fila_random, int numero_columna_random){
  bool libre = true;
  for(int j = 0; j <= juego.tope_comida; j++){
    for(int i = 0; i <= juego.comida->tope_ingredientes; i ++){
      if(juego.comida[j].ingrediente[i].posicion.fil == numero_fila_random && juego.comida[j].ingrediente[i].posicion.col == numero_columna_random){
        libre = false;
      }
    }
  }
 return libre;
}



// FIN VALIDACIONES


// HERRAMIENTAS DE PROGRAMACION



int calcular_distancia(int fila1, int columna1, int fila2, int columna2) {
int distancia_total = 0;
int resta_filas = (fila1 - fila2);
int resta_columnas = (columna1 - columna2);

distancia_total = resta_filas + resta_columnas;

return  distancia_total;

}



// FIN HERRAMIENTAS DE PROGRAMACION








// INICIALIZACION

void anadir_obstaculos(juego_t* juego) {
 (*juego).tope_obstaculos = 0;

  // añade 10 obstaculos al primer cuadrante
  while((*juego).tope_obstaculos < 10) {
  int numero_fila_random = rand() % 8 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_pared(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_obstaculo(*juego, numero_fila_random, numero_fila_random)){
  (*juego).obstaculos[(*juego).tope_obstaculos].posicion.fil = numero_fila_random;
  (*juego).obstaculos[(*juego).tope_obstaculos].posicion.col = numero_columna_random;
  (*juego).obstaculos[(*juego).tope_obstaculos].tipo = AGUJERO;
  (*juego).tope_obstaculos ++;
  }
  }


  //añade 10 obstaculos al 2do cuadrante
  while((*juego).tope_obstaculos < 20) {
  int numero_fila_random = rand() % 8 + 12; 
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_pared(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_obstaculo(*juego, numero_fila_random, numero_fila_random)){
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
  if(no_hay_pared(*juego, numero_fila_random, numero_columna_random) && no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random)){
    (*juego).herramientas[(*juego).tope_herramientas].posicion.fil = numero_fila_random;
    (*juego).herramientas[(*juego).tope_herramientas].posicion.col = numero_columna_random;
    (*juego).herramientas[(*juego).tope_herramientas].tipo = CUCHILLO;
    (*juego).tope_herramientas ++;

  }
}


while((*juego).tope_herramientas < 4){
  int numero_fila_random = rand() % 8 + 12;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_pared(*juego, numero_fila_random, numero_columna_random) && no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random)){
    (*juego).herramientas[(*juego).tope_herramientas].posicion.fil = numero_fila_random;
    (*juego).herramientas[(*juego).tope_herramientas].posicion.col = numero_columna_random;
    (*juego).herramientas[(*juego).tope_herramientas].tipo = HORNO;
    (*juego).tope_herramientas ++;

  }
}
}

void anadir_mesa_y_salida(juego_t* juego) {
  bool hay_mesa = false;

  (*juego).mesa.fil = POSICION_FILA_MESA;
  (*juego).mesa.col = POSICION_COLUMNA_MESA;

  while(hay_mesa == false){
  int numero_fila_random = rand() % 8 + 12;
  int numero_columna_random = rand() % 19 + 1;

  if(no_hay_pared(*juego, numero_fila_random, numero_columna_random) && no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random)){
  (*juego).salida.fil = numero_fila_random;
  (*juego).salida.col = numero_columna_random;
  hay_mesa = true;
  }

  }
}

 void anadir_ensalada(juego_t* juego) {

  (*juego).tope_comida = 0;
  (*juego).comida->tope_ingredientes = 0;

  while((*juego).comida->tope_ingredientes < 1) {
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_pared(*juego, numero_fila_random, numero_columna_random) && no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random)){
  (*juego).comida[(*juego).tope_comida].ingrediente[(*juego).comida->tope_ingredientes].posicion.fil = numero_fila_random;
  (*juego).comida[(*juego).tope_comida].ingrediente[(*juego).comida->tope_ingredientes].posicion.col = numero_columna_random;
  (*juego).comida[(*juego).tope_comida].ingrediente[(*juego).comida->tope_ingredientes].tipo = LECHUGA;
  (*juego).comida->tope_ingredientes ++;
  }
  }

  while((*juego).comida->tope_ingredientes < 2) {
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_pared(*juego, numero_fila_random, numero_columna_random) && no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random)){
  (*juego).comida[(*juego).tope_comida].ingrediente[(*juego).comida->tope_ingredientes].posicion.fil = numero_fila_random;
  (*juego).comida[(*juego).tope_comida].ingrediente[(*juego).comida->tope_ingredientes].posicion.col = numero_columna_random;
  (*juego).comida[(*juego).tope_comida].ingrediente[(*juego).comida->tope_ingredientes].tipo = TOMATE;
  (*juego).comida->tope_ingredientes ++;
  }
  }
 (*juego).comida[(*juego).tope_comida].tipo = ENSALADA;
 (*juego).tope_comida++;
}

void anadir_ingredientes(juego_t* juego, int precio){

 if(precio <= CATEGORIA_PRECIO_1){
 anadir_ensalada(juego);

 } else if(CATEGORIA_PRECIO_1 < precio && precio <= CATEGORIA_PRECIO_2) {

 anadir_ensalada(juego);

 } else if(precio > CATEGORIA_PRECIO_2){

 anadir_ensalada(juego);

 }

} 

void anadir_personajes(juego_t* juego) {
  int cantidad_personajes = 0;

  while(cantidad_personajes < 1){
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1; 
  if(no_hay_pared(*juego, numero_fila_random, numero_columna_random) && no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random)){
    (*juego).stitch.posicion.fil = numero_fila_random;
    (*juego).stitch.posicion.col = numero_columna_random;
    (*juego).stitch.tipo = STITCH;
    cantidad_personajes ++;
  }
  }

  while(cantidad_personajes < 2) {
  int numero_fila_random = rand() % 8 + 12;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_pared(*juego, numero_fila_random, numero_columna_random) && no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random)) {
 (*juego).reuben.posicion.fil = numero_fila_random;
 (*juego).reuben.posicion.col = numero_columna_random;
 (*juego).reuben.tipo = REUBEN;
 cantidad_personajes ++;
  }
  }

}




void inicializar_juego(juego_t* juego, int precio) {

 srand (( unsigned)time(NULL));
 
  inicializar_nivel_paredes(juego);
  anadir_obstaculos(juego);
  anadir_herramientas(juego);
  anadir_ingredientes(juego, precio);
  anadir_mesa_y_salida(juego);
  anadir_personajes(juego);



}





// FIN INICIALIZACION





// CREACION MATRIZ



void limpiar_matriz(char matriz[MAX_FIL][MAX_COL]){

    // primero lo lleno de "vacio"
    for(int i = 0; i < MAX_FIL; i ++){
        for (int j = 0; j < MAX_COL; j++){
        matriz[i][j] = VACIO;
        }
        
    }
  
}
void incorporar_paredes(juego_t* juego, char matriz[MAX_FIL][MAX_COL]){
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

void incorporar_obstaculos(juego_t* juego, char matriz[MAX_FIL][MAX_COL]){
  for(int x = 0; x < MAX_OBSTACULOS; x++){
  for(int i = 0; i < MAX_FIL; i++) {
    for(int j = 0; j < MAX_COL; j++) {
     if(juego->obstaculos[x].posicion.fil == i && juego->obstaculos[x].posicion.col == j && juego->obstaculos[x].tipo == AGUJERO){
     matriz[i][j] = AGUJERO;
    } 
    }
  }
}
}

void incorporar_herramientas(juego_t* juego, char matriz[MAX_FIL][MAX_COL]){
    for(int x = 0; x < juego->tope_herramientas; x++){
  for(int i = 0; i < MAX_FIL; i++) {
    for(int j = 0; j < MAX_COL; j++) {
     if(juego->herramientas[x].posicion.fil == i && juego->herramientas[x].posicion.col == j){
      matriz[i][j] = juego->herramientas[x].tipo;
    } 
    }
  }
}
}

void incorporar_ingredientes(juego_t* juego, char matriz[MAX_FIL][MAX_COL]){
for(int y = 0; y <= juego->tope_comida; y++) {
   for(int x = 0; x <= juego->comida->tope_ingredientes; x++){
    for(int i = 0; i < MAX_FIL; i++) {
    for(int j = 0; j < MAX_COL; j++) {
     if(juego->comida[y].ingrediente[x].posicion.fil == i && juego->herramientas[x].posicion.col == j){
      matriz[i][j] = juego->comida[y].ingrediente[x].tipo;
     }
    }
    }
   }
}
}

void incorporar_mesa_y_salida(juego_t* juego, char matriz[MAX_FIL][MAX_COL]){
   matriz[POSICION_FILA_MESA][POSICION_COLUMNA_MESA] = MESA;
   matriz[(*juego).salida.fil][(*juego).salida.col] = SALIDA;

}

void incorporar_personajes(juego_t* juego, char matriz[MAX_FIL][MAX_COL]) {
  matriz[(*juego).stitch.posicion.fil][(*juego).stitch.posicion.col] = STITCH;
  matriz[(*juego).reuben.posicion.fil][(*juego).reuben.posicion.col] = REUBEN;
}


void incorporar_elementos_en_matriz(juego_t* juego, char matriz[MAX_FIL][MAX_COL]) {
  incorporar_paredes(juego, matriz);
  incorporar_obstaculos(juego, matriz);
  incorporar_herramientas(juego, matriz);
  incorporar_ingredientes(juego, matriz);
  incorporar_mesa_y_salida(juego, matriz);
  incorporar_personajes(juego, matriz);

}

void mostrar_nivel(char matriz[MAX_FIL][MAX_COL]) {
    for (int i = 0; i <= MAX_FIL; i++){
     for (int j = 0; j <= MAX_COL; j++){
        printf("%c", matriz[i][j]);
     }
     printf("\n");
    }
    
}



void imprimir_terreno(juego_t* juego){
  char matriz[MAX_FIL][MAX_COL];

  limpiar_matriz(matriz);
  incorporar_elementos_en_matriz(juego, matriz);
  mostrar_nivel(matriz);
}





// FIN CREACION MATRIZ




// MOVIMIENTOS

void personaje_activo(juego_t* juego, char* movimiento){
    if((*juego).personaje_activo == STITCH){
      (*juego).personaje_activo = REUBEN;
      imprimir_terreno(juego);
    } else {
      (*juego).personaje_activo = STITCH;
      imprimir_terreno(juego);
    }
  }


void chequear_pared(juego_t* juego, char* movimiento, int* cant_movimientos){
  if((*juego).personaje_activo == STITCH){
    if((*movimiento == MOVER_DERECHA) && (no_hay_pared(*juego, (*juego).stitch.posicion.fil,(*juego).stitch.posicion.col + 1))) {
    (*juego).stitch.posicion.col ++;
    cant_movimientos ++;
    imprimir_terreno(juego);
  } else if ((*movimiento == MOVER_IZQUIERDA) && (no_hay_pared(*juego, (*juego).stitch.posicion.fil,(*juego).stitch.posicion.col - 1))){
    (*juego).stitch.posicion.col --;
    cant_movimientos ++;
    imprimir_terreno(juego);
  } else if((*movimiento == MOVER_ABAJO) && (no_hay_pared(*juego, (*juego).stitch.posicion.fil + 1,(*juego).stitch.posicion.col))){
    (*juego).stitch.posicion.fil ++;
    cant_movimientos ++;
    imprimir_terreno(juego);
  } else if((*movimiento == MOVER_ARRIBA) && (no_hay_pared(*juego, (*juego).stitch.posicion.fil - 1,(*juego).stitch.posicion.col))) {
    (*juego).stitch.posicion.fil --;
    cant_movimientos ++;
    imprimir_terreno(juego);
  } else{
    imprimir_terreno(juego);
    printf("Stitch: Es extraño... es como si me estuvieras dando ordenes sin sentido...\n");
  }
  } else if ((*juego).personaje_activo == REUBEN) {

    if((*movimiento == MOVER_DERECHA) && (no_hay_pared(*juego, (*juego).reuben.posicion.fil,(*juego).reuben.posicion.col + 1))) {
    (*juego).reuben.posicion.col ++;
    cant_movimientos ++;
    imprimir_terreno(juego);
  } else if ((*movimiento == MOVER_IZQUIERDA) && (no_hay_pared(*juego, (*juego).reuben.posicion.fil,(*juego).reuben.posicion.col - 1))){
    (*juego).reuben.posicion.col --;
    cant_movimientos ++;
    imprimir_terreno(juego);
  } else if((*movimiento == MOVER_ABAJO) && (no_hay_pared(*juego, (*juego).reuben.posicion.fil + 1,(*juego).reuben.posicion.col))){
    (*juego).reuben.posicion.fil ++;
    cant_movimientos ++;
    imprimir_terreno(juego);
  } else if((*movimiento == MOVER_ARRIBA) && (no_hay_pared(*juego, (*juego).reuben.posicion.fil - 1,(*juego).reuben.posicion.col))) {
    (*juego).reuben.posicion.fil --;
    cant_movimientos ++;
    imprimir_terreno(juego);
  } else{
    imprimir_terreno(juego);
    printf("Reuben: Es extraño... es como si me estuvieras dando ordenes sin sentido...\n");
  }
  }
 }


void chequear_obstaculo(juego_t* juego, char* movimiento, int* cant_movimientos){
  if((*juego).personaje_activo == STITCH){
    if(!no_hay_obstaculo(*juego, (*juego).stitch.posicion.fil,(*juego).stitch.posicion.col)) {
         printf("COMO NO LO VISTE?!?!? CAÌSTE EN UN AGUJERO. PERDISTE :( \n");
         *cant_movimientos = 25;
    }
  } else {
        if(!no_hay_obstaculo(*juego, (*juego).reuben.posicion.fil,(*juego).reuben.posicion.col)) {
         printf("COMO NO LO VISTE?!?!? CAÌSTE EN UN AGUJERO. PERDISTE :( \n");
         *cant_movimientos = 25;
    }
  }

  
 }

/* void tomar_ingrediente(juego_t juego, movimiento){
 if(movimiento == TOMAR_ALIMENTO && (calcular_distancia((*juego).stitch.posicion.fil, (*juego).stitch.posicion.col,)))
 }
 */
/*
void chequear_herramienta(juego_t* juego, char* movimiento, int* cant_movimientos){
  if(!no_hay_herramienta(*juego,(*juego).stitch.posicion.fil,(*juego).stitch.posicion.col) && (*movimiento == CUCHILLO) && tener el ingrediente en la mano){
   
  }
}
*/


void realizar_jugada(juego_t* juego, char* movimiento, int precio) {
  int cant_movimientos = 0;
  (*juego).personaje_activo = STITCH;

  while(cant_movimientos < 25) {
  printf("¿Que movimiento desea hacer?\n");
  scanf(" %c", movimiento);
  if(*movimiento == CAMBIAR_PERSONAJE){
      personaje_activo(juego, movimiento);
  } else {
  chequear_pared(juego, movimiento, &cant_movimientos);
  chequear_obstaculo(juego, movimiento, &cant_movimientos);
//  tomar_ingrediente(juego, movimiento);
//  chequear_herramienta(juego, movimiento);
  }
  }


  printf("Desea jugar de nuevo? [S/N]\n");
  scanf(" %c", movimiento);
  if(*movimiento == 'S') {
    inicializar_juego(juego, precio);
    imprimir_terreno(juego);
    realizar_jugada(juego, movimiento);
  }
}





// FIN MOVIMIENTOS