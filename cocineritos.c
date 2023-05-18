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

const char VACIO = '.';
const char MANO_VACIA = 'V';
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
const char CARNE = 'B';
const char MILANESA = 'I';
const char PAN = 'N';
const char MOVER_DERECHA = 'D';
const char MOVER_IZQUIERDA = 'A';
const char MOVER_ARRIBA = 'W';
const char MOVER_ABAJO = 'S';
const char ENSALADA = 'E';
const char PIZZA = 'P';
const char HAMBURGUESA = 'H';
const char SANDWICH = 'S';
const char PUERTA_DE_SALIDA = 'P';
const char MATAFUEGOS = 'M';
const char FUEGO = 'F';

const int OBSTACULOS_POR_CUADRANTE = 10;
const int MITAD_DE_COLUMNAS = 10;
const int MITAD_DE_FILAS_TOTAL = 11;
const int MITAD_FILAS_PRIMER_CUADRANTE = 5;
const int MITAD_FILAS_SEGUNDO_CUADRANTE = 15;
const int CATEGORIA_PRECIO_1 = 100;
const int CATEGORIA_PRECIO_2 = 150;
const int CANTIDAD_INGREDIENTES_ENSALADA = 2;
const int CANTIDAD_INGREDIENTES_PIZZA = 3;
const int CANTIDAD_INGREDIENTES_HAMBURGUESA = 4;
const int CANTIDAD_INGREDIENTES_SANDWICH = 6;
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
const int SIGUE_JUGANDO = 0;
const int PERDIO = -1;
const int GANO = 1;
// pre:
// pos: Añade la localizacion de las paredes al struct juego_t juego

void inicializar_nivel_paredes(juego_t* juego) {
(*juego).tope_paredes = 0;
    for (int i = 0; i < MAX_FIL; i++){
      for (int j = 0; j < MAX_COL; j++){
      if ((j == 0 || j == 20) || (i == 0 || i == 10 || i == 20)){
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

  for(int i = 0; i < juego.tope_paredes; i++){
    if((juego.paredes[i].fil == numero_fila_random && juego.paredes[i].col == numero_columna_random) || ((juego).mesa.fil == numero_fila_random && (juego).mesa.col == numero_columna_random)) {
      libre = false;
    } 
  }
 return libre;
}

bool no_hay_obstaculo(juego_t juego, int numero_fila_random, int numero_columna_random) {
  bool libre = true;
  for(int i = 0; i < juego.tope_obstaculos; i++){
    if(numero_fila_random == juego.obstaculos[i].posicion.fil && numero_columna_random == juego.obstaculos[i].posicion.col) {
      libre = false;
    } 
   }

  return libre;
}

bool no_hay_herramienta(juego_t juego, int numero_fila_random, int numero_columna_random) {
  bool libre = true;
  for(int i = 0; i < juego.tope_herramientas; i++){
    if(juego.herramientas[i].posicion.fil == numero_fila_random && juego.herramientas[i].posicion.col == numero_columna_random) {
      libre = false;
    } 
  }
  return libre;
}

bool no_hay_ingredientes(juego_t juego, int numero_fila_random, int numero_columna_random){
  bool libre = true;
  for(int j = 0; j < juego.tope_comida; j++){
    for(int i = 0; i < juego.comida[j].tope_ingredientes; i ++){
      if(juego.comida[j].ingrediente[i].posicion.fil == numero_fila_random && juego.comida[j].ingrediente[i].posicion.col == numero_columna_random){
        libre = false;
      }
    }
  }
 return libre;
}

bool no_hay_puerta(juego_t juego, int fila, int columna){
  bool libre = true;
  if((juego.salida.fil == fila) && (juego.salida.col == columna)){
   libre = false;
  }
  return libre;
}

bool no_hay_personaje(juego_t juego, int fila, int columna){
    bool libre = true;
  if(((juego.stitch.posicion.fil == fila) && (juego.stitch.posicion.col == columna)) || ((juego.reuben.posicion.fil == fila) && (juego.reuben.posicion.col == columna))){
   libre = false;
  }
  return libre;
}

bool condicion_ganadora(juego_t juego){
  bool se_gano = false;
 if((juego.precio_total <= CATEGORIA_PRECIO_1) && (juego.tope_comida_lista == juego.comida[juego.tope_comida -1].tope_ingredientes) && (juego.comida_actual == PIZZA)){
  se_gano = true;
 } else if((juego.precio_total > CATEGORIA_PRECIO_1) && (juego.precio_total <= CATEGORIA_PRECIO_2) && (juego.tope_comida_lista == juego.comida[juego.tope_comida -1].tope_ingredientes) && (juego.comida_actual == HAMBURGUESA)) {
  se_gano = true;
 } else if((juego.precio_total > CATEGORIA_PRECIO_2) && (juego.tope_comida_lista == juego.comida[juego.tope_comida -1].tope_ingredientes) && (juego.comida_actual == SANDWICH)){
  se_gano = true;
 }

 return se_gano;
}

// FIN VALIDACIONES




// HERRAMIENTAS DE PROGRAMACION



int calcular_distancia(int fila1, int columna1, int fila2, int columna2) {
int distancia_total = 0;
int resta_filas = abs(fila1 - fila2);
int resta_columnas = abs(columna1 - columna2);

distancia_total = resta_filas + resta_columnas;

return  distancia_total;

}

void ingrediente_listo(juego_t* juego, int lugar_comida, int lugar_ingrediente){
  for(int i = lugar_ingrediente; i < (*juego).comida[lugar_comida].tope_ingredientes; i++){
    (*juego).comida[lugar_comida].ingrediente[i] = (*juego).comida[lugar_comida].ingrediente[i + 1];
  }
  (*juego).comida[lugar_comida].tope_ingredientes --;
}

void anadir_ingrediente_particular(juego_t* juego, int tope_comida, int tope_ingrediente, char tipo, int fila, int col){
 (*juego).comida[tope_comida].ingrediente[tope_ingrediente].posicion.fil = fila;
 (*juego).comida[tope_comida].ingrediente[tope_ingrediente].posicion.col = col;
 (*juego).comida[tope_comida].ingrediente[tope_ingrediente].tipo = tipo;
 (*juego).comida[tope_comida].ingrediente[tope_ingrediente].esta_cortado = false;
 (*juego).comida[tope_comida].ingrediente[tope_ingrediente].esta_cocinado = false;
 (*juego).comida[tope_comida].tope_ingredientes ++;
// ejemplo de uso : 
//   anadir_ingrediente_particular(juego, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, LECHUGA, numero_fila_random, numero_columna_random);
}


void anadir_obstaculo(juego_t* juego, int tope_obstaculo, char tipo, int fila, int col){
  (*juego).obstaculos[tope_obstaculo].posicion.fil = fila;
  (*juego).obstaculos[tope_obstaculo].posicion.col = col;
  (*juego).obstaculos[tope_obstaculo].tipo = tipo;
  (*juego).tope_obstaculos ++;
}

void anadir_herramienta(juego_t* juego, int tope_herramientas, char tipo, int fila, int col){
    (*juego).herramientas[tope_herramientas].posicion.fil = fila;
    (*juego).herramientas[tope_herramientas].posicion.col = col;
    (*juego).herramientas[tope_herramientas].tipo = tipo;
    (*juego).tope_herramientas ++;
}


// FIN HERRAMIENTAS DE PROGRAMACION








// INICIALIZACION

void anadir_obstaculos(juego_t* juego) {
 (*juego).tope_obstaculos = 0;

  // añade 10 obstaculos al primer cuadrante
  while((*juego).tope_obstaculos < 10) {
  int numero_fila_random = rand() % 8 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if( puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random)){
  anadir_obstaculo(juego, (*juego).tope_obstaculos, AGUJERO, numero_fila_random, numero_columna_random);
  }
  }


  //añade 10 obstaculos al 2do cuadrante
  while((*juego).tope_obstaculos < 20) {
  int numero_fila_random = rand() % 8 + 12; 
  int numero_columna_random = rand() % 19 + 1;
  if( puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random)){
  anadir_obstaculo(juego, (*juego).tope_obstaculos, AGUJERO, numero_fila_random, numero_columna_random);
  }
  }
}

void anadir_fuego_cuadrante_stitch(juego_t* juego){
  int nuevo_tope = (*juego).tope_obstaculos ++;
   while((*juego).tope_obstaculos < nuevo_tope) {
  int numero_fila_random = rand() % 8 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random) && no_hay_puerta((*juego), numero_fila_random, numero_columna_random) && no_hay_personaje(*juego, numero_fila_random, numero_columna_random) ){
  anadir_obstaculo(juego, (*juego).tope_obstaculos, FUEGO, numero_fila_random, numero_columna_random);
  }
  }

}


void anadir_fuego_cuadrante_reuben(juego_t* juego){
  int nuevo_tope = (*juego).tope_obstaculos ++;
  while((*juego).tope_obstaculos < nuevo_tope) {
  int numero_fila_random = rand() % 8 + 12;
  int numero_columna_random = rand() % 19 + 1;
  if(puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random) && no_hay_puerta((*juego), numero_fila_random, numero_columna_random) && no_hay_personaje(*juego, numero_fila_random, numero_columna_random) ){
  anadir_obstaculo(juego, (*juego).tope_obstaculos, FUEGO, numero_fila_random, numero_columna_random);
  }
  }

}

void anadir_cuchillos(juego_t* juego) {

(*juego).tope_herramientas = 0;

while((*juego).tope_herramientas < 2){
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if( no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random)){
anadir_herramienta(juego, (*juego).tope_herramientas, CUCHILLO, numero_fila_random, numero_columna_random);
  }
}
}

void anadir_hornos(juego_t* juego) {

while((*juego).tope_herramientas < 4){
  int numero_fila_random = rand() % 8 + 12;
  int numero_columna_random = rand() % 19 + 1;
  if( no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random)){
anadir_herramienta(juego, (*juego).tope_herramientas, HORNO, numero_fila_random, numero_columna_random);
  }
}
}

void anadir_matafuegos_cuadrante_stitch(juego_t* juego) {

while((*juego).tope_herramientas < 5){
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random) && no_hay_puerta((*juego), numero_fila_random, numero_columna_random)){
anadir_herramienta(juego, (*juego).tope_herramientas, MATAFUEGOS, numero_fila_random, numero_columna_random);
  }
}

}

void anadir_matafuegos_cuadrante_reuben(juego_t* juego) {

while((*juego).tope_herramientas < 5){
  int numero_fila_random = rand() % 8 + 12;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random) && no_hay_puerta((*juego), numero_fila_random, numero_columna_random)){
anadir_herramienta(juego, (*juego).tope_herramientas, MATAFUEGOS, numero_fila_random, numero_columna_random);
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

  if( no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random)){
  (*juego).salida.fil = numero_fila_random;
  (*juego).salida.col = numero_columna_random;
  hay_mesa = true;
  }

  }
}



// AÑADIR ALIMENTOS




 void anadir_ensalada(juego_t* juego) {

  (*juego).comida[(*juego).tope_comida].tope_ingredientes = 0;

  while((*juego).comida[(*juego).tope_comida].tope_ingredientes < 1) {
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random)){
  anadir_ingrediente_particular(juego, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, LECHUGA, numero_fila_random, numero_columna_random);
  }
  }

  while((*juego).comida[(*juego).tope_comida].tope_ingredientes < 2) {
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random)){
  anadir_ingrediente_particular(juego, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, TOMATE, numero_fila_random, numero_columna_random);
  }
  }

 (*juego).comida[(*juego).tope_comida].tipo = ENSALADA;
 (*juego).comida_actual = ENSALADA;
 (*juego).tope_comida++;

}

void anadir_pizza(juego_t* juego){

  (*juego).comida[(*juego).tope_comida].tope_ingredientes = 0;

  while((*juego).comida[(*juego).tope_comida].tope_ingredientes < 1) {
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random)){
  anadir_ingrediente_particular(juego, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, JAMON, numero_fila_random, numero_columna_random);
  }
  }

  while((*juego).comida[(*juego).tope_comida].tope_ingredientes < 2) {
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random)){
  anadir_ingrediente_particular(juego, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, QUESO, numero_fila_random, numero_columna_random);
  }
  }

    while((*juego).comida[(*juego).tope_comida].tope_ingredientes < 3) {
  int numero_fila_random = rand() % 8 + 12;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random) && no_hay_puerta((*juego), numero_fila_random, numero_columna_random)){
  anadir_ingrediente_particular(juego, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, MASA, numero_fila_random, numero_columna_random);
  }
  }
  (*juego).comida[(*juego).tope_comida].tipo = PIZZA;
  (*juego).comida_actual = PIZZA;
  (*juego).tope_comida ++;

}

void anadir_hamburguesa(juego_t* juego){

  (*juego).comida[(*juego).tope_comida].tope_ingredientes = 0;

  while((*juego).comida[(*juego).tope_comida].tope_ingredientes < 1) {
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random)){
  anadir_ingrediente_particular(juego, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, LECHUGA, numero_fila_random, numero_columna_random);
  }
  }

  while((*juego).comida[(*juego).tope_comida].tope_ingredientes < 2) {
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random)){
  anadir_ingrediente_particular(juego, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, TOMATE, numero_fila_random, numero_columna_random);
  }
  }

  while((*juego).comida[(*juego).tope_comida].tope_ingredientes < 3) {
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random)){
  anadir_ingrediente_particular(juego, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, PAN, numero_fila_random, numero_columna_random);
  }
  }

  while((*juego).comida[(*juego).tope_comida].tope_ingredientes < 4) {
  int numero_fila_random = rand() % 8 + 12;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random) && no_hay_puerta((*juego), numero_fila_random, numero_columna_random)){
  anadir_ingrediente_particular(juego, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, CARNE, numero_fila_random, numero_columna_random);
  }
  }

  (*juego).comida[(*juego).tope_comida].tipo = HAMBURGUESA;
  (*juego).comida_actual = HAMBURGUESA;
  (*juego).tope_comida ++;
}

void anadir_sandwich(juego_t* juego){

  (*juego).comida[(*juego).tope_comida].tope_ingredientes = 0;

  while((*juego).comida[(*juego).tope_comida].tope_ingredientes < 1) {
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random)){
  anadir_ingrediente_particular(juego, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, LECHUGA, numero_fila_random, numero_columna_random);
  }
  }

  while((*juego).comida[(*juego).tope_comida].tope_ingredientes < 2) {
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random)){
  anadir_ingrediente_particular(juego, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, TOMATE, numero_fila_random, numero_columna_random);
  }
  }

  while((*juego).comida[(*juego).tope_comida].tope_ingredientes < 3) {
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random)){
  anadir_ingrediente_particular(juego, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, PAN, numero_fila_random, numero_columna_random);
  }
  }

  while((*juego).comida[(*juego).tope_comida].tope_ingredientes < 4) {
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random)){
  anadir_ingrediente_particular(juego, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, JAMON, numero_fila_random, numero_columna_random);
  }
  }

    while((*juego).comida[(*juego).tope_comida].tope_ingredientes < 5) {
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random)){
  anadir_ingrediente_particular(juego, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, QUESO, numero_fila_random, numero_columna_random);
  }
  }

  while((*juego).comida[(*juego).tope_comida].tope_ingredientes < 6) {
  int numero_fila_random = rand() % 8 + 12;
  int numero_columna_random = rand() % 19 + 1;
  if(no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random) && no_hay_puerta((*juego), numero_fila_random, numero_columna_random)){
  anadir_ingrediente_particular(juego, (*juego).tope_comida, (*juego).comida[(*juego).tope_comida].tope_ingredientes, MILANESA, numero_fila_random, numero_columna_random);
  }
  }
  (*juego).comida[(*juego).tope_comida].tipo = SANDWICH;
  (*juego).comida_actual = SANDWICH;
  (*juego).tope_comida ++;

}




// FIN AÑADIR ALIMENTOS





/* void anadir_ingredientes(juego_t* juego){

 if((*juego).precio_total <= CATEGORIA_PRECIO_1){
 anadir_ensalada(juego);
 } else if(CATEGORIA_PRECIO_1 < (*juego).precio_total && (*juego).precio_total <= CATEGORIA_PRECIO_2) {
 anadir_ensalada(juego);
 } else if((*juego).precio_total > CATEGORIA_PRECIO_2){
 anadir_ensalada(juego);
 }

} */

void anadir_ambos_personajes(juego_t* juego) {
  int cantidad_personajes = 0;

  while(cantidad_personajes < 1){
  int numero_fila_random = rand() % 9 + 1;
  int numero_columna_random = rand() % 19 + 1; 
  if( no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random)){
    (*juego).stitch.posicion.fil = numero_fila_random;
    (*juego).stitch.posicion.col = numero_columna_random;
    (*juego).stitch.tipo = STITCH;
    cantidad_personajes ++;
  }
  }

  while(cantidad_personajes < 2) {
  int numero_fila_random = rand() % 8 + 12;
  int numero_columna_random = rand() % 19 + 1;
  if( no_hay_obstaculo(*juego, numero_fila_random, numero_columna_random) && no_hay_herramienta(*juego, numero_fila_random, numero_columna_random) && puedo_agregar(numero_fila_random, numero_columna_random) && no_hay_ingredientes(*juego, numero_fila_random, numero_columna_random)) {
 (*juego).reuben.posicion.fil = numero_fila_random;
 (*juego).reuben.posicion.col = numero_columna_random;
 (*juego).reuben.tipo = REUBEN;
 cantidad_personajes ++;
  }
  }

}




void inicializar_juego(juego_t* juego, int precio) {
 (*juego).movimientos = 0;
 (*juego).tope_comida_lista = 0;
 (*juego).tope_comida = 0;
 (*juego).personaje_activo = STITCH;
 (*juego).stitch.objeto_en_mano = MANO_VACIA;
 (*juego).reuben.objeto_en_mano = MANO_VACIA;
 (*juego).precio_total = precio;

 srand (( unsigned)time(NULL));

  inicializar_nivel_paredes(juego);
  anadir_obstaculos(juego);
  anadir_cuchillos(juego);
  anadir_hornos(juego);
  anadir_ensalada(juego);
  anadir_mesa_y_salida(juego);
  anadir_ambos_personajes(juego);



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
  for(int x = 0; x <= juego->tope_paredes; x++){
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
  for(int x = 0; x < (*juego).tope_obstaculos; x++){
  for(int i = 0; i < MAX_FIL; i++) {
    for(int j = 0; j < MAX_COL; j++) {
     if(juego->obstaculos[x].posicion.fil == i && juego->obstaculos[x].posicion.col == j){
     matriz[i][j] = juego->obstaculos[x].tipo;
     }
    } 
    }
  }
}


void incorporar_herramientas(juego_t* juego, char matriz[MAX_FIL][MAX_COL]){
  for(int x = 0; x < (*juego).tope_herramientas; x++){
  for(int i = 0; i < MAX_FIL; i++) {
    for(int j = 0; j < MAX_COL; j++) {
     if((*juego).herramientas[x].posicion.fil == i && (*juego).herramientas[x].posicion.col == j){
      matriz[i][j] = (*juego).herramientas[x].tipo;
    } 
    }
  }
}
}
void incorporar_mesa_y_salida(juego_t* juego, char matriz[MAX_FIL][MAX_COL]){
   matriz[(*juego).mesa.fil][(*juego).mesa.col] = MESA;
   matriz[(*juego).salida.fil][(*juego).salida.col] = SALIDA;

}

void incorporar_ingredientes(juego_t* juego, char matriz[MAX_FIL][MAX_COL]){
      for(int y = 0; y < juego->tope_comida; y++){
        for(int x = 0; x < juego->comida[y].tope_ingredientes; x++){
    for(int i = 0; i < MAX_FIL; i ++){
    for(int j = 0; j < MAX_COL; j++){
        if(juego->comida[y].ingrediente[x].posicion.fil == i && juego->comida[y].ingrediente[x].posicion.col == j){
          matriz[i][j] = juego->comida[y].ingrediente[x].tipo;
          }
          }
      }
    }
   }

}


void incorporar_personajes(juego_t* juego, char matriz[MAX_FIL][MAX_COL]) {
  matriz[(*juego).stitch.posicion.fil][(*juego).stitch.posicion.col] = STITCH;
  matriz[(*juego).reuben.posicion.fil][(*juego).reuben.posicion.col] = REUBEN;
}


void incorporar_elementos_en_matriz(juego_t* juego, char matriz[MAX_FIL][MAX_COL]) {
 incorporar_paredes(juego, matriz);
 incorporar_obstaculos(juego, matriz);
 incorporar_herramientas(juego, matriz);
 incorporar_mesa_y_salida(juego, matriz);
 incorporar_ingredientes(juego, matriz);
 incorporar_personajes(juego, matriz);

}

void mostrar_nivel(char matriz[MAX_FIL][MAX_COL]) {
    for (int i = 0; i < MAX_FIL; i++){
     for (int j = 0; j < MAX_COL; j++){
        printf("%c", matriz[i][j]);
     }
     printf("\n");
    }
    
}



void imprimir_terreno(juego_t juego){
  char matriz[MAX_FIL][MAX_COL];

  limpiar_matriz(matriz);
  incorporar_elementos_en_matriz(&juego, matriz);
  mostrar_nivel(matriz);
}





// FIN CREACION MATRIZ








// CHEQUEOS




void chequear_pared(juego_t* juego, char movimiento){
  if((*juego).personaje_activo == STITCH){
    if((movimiento == MOVER_DERECHA) && (no_hay_pared(*juego, (*juego).stitch.posicion.fil,(*juego).stitch.posicion.col + 1))) {
    (*juego).stitch.posicion.col ++;
    (*juego).movimientos ++;
  } else if ((movimiento == MOVER_IZQUIERDA) && (no_hay_pared(*juego, (*juego).stitch.posicion.fil,(*juego).stitch.posicion.col - 1))){
    (*juego).stitch.posicion.col --;
    (*juego).movimientos ++;
  } else if((movimiento == MOVER_ABAJO) && (no_hay_pared(*juego, (*juego).stitch.posicion.fil + 1,(*juego).stitch.posicion.col))){
    (*juego).stitch.posicion.fil ++;
    (*juego).movimientos ++;
  } else if((movimiento == MOVER_ARRIBA) && (no_hay_pared(*juego, (*juego).stitch.posicion.fil - 1,(*juego).stitch.posicion.col))) {
    (*juego).stitch.posicion.fil --;
    (*juego).movimientos ++;
  } 
      } 
  else if ((*juego).personaje_activo == REUBEN) {
    if((movimiento == MOVER_DERECHA) && (no_hay_pared(*juego, (*juego).reuben.posicion.fil,((*juego).reuben.posicion.col + 1))) && no_hay_herramienta(*juego, (*juego).reuben.posicion.fil,((*juego).reuben.posicion.col + 1))) {
    (*juego).reuben.posicion.col ++;
    (*juego).movimientos ++;
  } else if ((movimiento == MOVER_IZQUIERDA) && (no_hay_pared(*juego, (*juego).reuben.posicion.fil,((*juego).reuben.posicion.col - 1))) && no_hay_herramienta(*juego, (*juego).reuben.posicion.fil,((*juego).reuben.posicion.col - 1))){
    (*juego).reuben.posicion.col --;
    (*juego).movimientos ++;
  } else if((movimiento == MOVER_ABAJO) && (no_hay_pared(*juego, ((*juego).reuben.posicion.fil + 1),(*juego).reuben.posicion.col)) && no_hay_herramienta(*juego, ((*juego).reuben.posicion.fil + 1),(*juego).reuben.posicion.col)){
    (*juego).reuben.posicion.fil ++;
    (*juego).movimientos ++;
  } else if((movimiento == MOVER_ARRIBA) && (no_hay_pared(*juego, ((*juego).reuben.posicion.fil - 1),(*juego).reuben.posicion.col)) && no_hay_herramienta(*juego, ((*juego).reuben.posicion.fil - 1),(*juego).reuben.posicion.col)) {
    (*juego).reuben.posicion.fil --;
    (*juego).movimientos ++;
  }
  }
 }



void chequear_puerta(juego_t* juego){

  if(!no_hay_puerta( (*juego), (*juego).reuben.posicion.fil, (*juego).reuben.posicion.col) && ((*juego).personaje_activo == REUBEN)){

  for(int i = 0; i < (*juego).tope_comida; i ++){
  for(int j = 0; j < (*juego).comida[i].tope_ingredientes; j++){

  
    if((*juego).comida[i].ingrediente[j].tipo == (*juego).reuben.objeto_en_mano){
      if((*juego).comida[i].ingrediente[j].esta_cortado || (*juego).comida[i].ingrediente[j].esta_cocinado){
    //    ingrediente_listo(juego, i, j);
    (*juego).comida_lista[(*juego).tope_comida_lista].tipo = (*juego).reuben.objeto_en_mano;
    (*juego).comida_lista[(*juego).tope_comida_lista].esta_cocinado = (*juego).comida[i].ingrediente[j].esta_cocinado;
    (*juego).comida_lista[(*juego).tope_comida_lista].esta_cortado = (*juego).comida[i].ingrediente[j].esta_cortado;
    (*juego).tope_comida_lista ++;
    (*juego).reuben.objeto_en_mano = MANO_VACIA;
    printf("Reuben: Magicamente se emplato el ingrediente del tipo %c!\n", (*juego).reuben.objeto_en_mano);
        
    } 
  }
      }
      }

  }
}


void chequear_comidas(juego_t* juego){

 if((*juego).precio_total <= CATEGORIA_PRECIO_1){

 if(((*juego).tope_comida_lista == (*juego).comida[(*juego).tope_comida -1].tope_ingredientes) && ((*juego).comida_actual == ENSALADA)) {
 (*juego).tope_comida_lista = 0;
 anadir_pizza(juego);
 }


 } else if((CATEGORIA_PRECIO_1 < (*juego).precio_total) && ((*juego).precio_total <= CATEGORIA_PRECIO_2)) {

if(((*juego).tope_comida_lista == (*juego).comida[(*juego).tope_comida -1].tope_ingredientes) && ((*juego).comida_actual == ENSALADA)) {
(*juego).tope_comida_lista = 0;
anadir_pizza(juego);
} else if (((*juego).tope_comida_lista == (*juego).comida[(*juego).tope_comida -1].tope_ingredientes) && ((*juego).comida_actual == PIZZA)){
(*juego).tope_comida_lista = 0;
anadir_hamburguesa(juego);
}


 } else if((*juego).precio_total > CATEGORIA_PRECIO_2){

if(((*juego).tope_comida_lista == (*juego).comida[(*juego).tope_comida -1].tope_ingredientes) && ((*juego).comida_actual == ENSALADA)) {
(*juego).tope_comida_lista = 0;
anadir_pizza(juego);
} else if (((*juego).tope_comida_lista == (*juego).comida[(*juego).tope_comida -1].tope_ingredientes) && ((*juego).comida_actual == PIZZA)){
(*juego).tope_comida_lista = 0;
anadir_hamburguesa(juego);
} else if(((*juego).tope_comida_lista == (*juego).comida[(*juego).tope_comida -1].tope_ingredientes) && ((*juego).comida_actual == HAMBURGUESA)){
(*juego).tope_comida_lista = 0;
anadir_sandwich(juego);
}
 }
}

// FIN CHEQUEOS






// MOVIMIENTOS
  
 

void personaje_activo(juego_t* juego){

    if((*juego).personaje_activo == STITCH){
      (*juego).personaje_activo = REUBEN;
    } else {
      (*juego).personaje_activo = STITCH;
    }

  }

void tomar_ingrediente(juego_t* juego){


  if((*juego).personaje_activo == STITCH){
  for(int i = 0; i < (*juego).tope_comida; i++){
  for(int j = 0; j < (*juego).comida[i].tope_ingredientes; j ++){
 if(!no_hay_ingredientes(*juego, (*juego).stitch.posicion.fil, (*juego).stitch.posicion.col) && ((*juego).stitch.objeto_en_mano == MANO_VACIA)){

  if(((*juego).comida[i].ingrediente[j].posicion.fil == (*juego).stitch.posicion.fil) && ((*juego).comida[i].ingrediente[j].posicion.col == (*juego).stitch.posicion.col)){
  (*juego).stitch.objeto_en_mano = (*juego).comida[i].ingrediente[j].tipo;
  (*juego).comida[i].ingrediente[j].posicion.fil = -1;
  (*juego).comida[i].ingrediente[j].posicion.col = -1;

  printf("Stitch: Ohh mis manos recibieron un ingrediente del tipo %c!\n", (*juego).comida[i].ingrediente[j].tipo);
  } 
  } else if(!no_hay_ingredientes(*juego, (*juego).stitch.posicion.fil, (*juego).stitch.posicion.col) && ((*juego).stitch.objeto_en_mano != MANO_VACIA)){
  j = (*juego).comida[i].tope_ingredientes;
  i = (*juego).tope_comida;

  printf("Stitch: Cuantas cosas queres que tenga en la mano?\n");
  
 } else if(no_hay_ingredientes(*juego, (*juego).stitch.posicion.fil, (*juego).stitch.posicion.col) && no_hay_herramienta(*juego, (*juego).stitch.posicion.fil, (*juego).stitch.posicion.col) && ((*juego).comida[i].ingrediente[j].tipo == (*juego).stitch.objeto_en_mano)){
  (*juego).comida[i].ingrediente[j].posicion.fil = (*juego).stitch.posicion.fil;
  (*juego).comida[i].ingrediente[j].posicion.col = (*juego).stitch.posicion.col;
  (*juego).stitch.objeto_en_mano = MANO_VACIA;
 
 }
     }
     }


} else if((*juego).personaje_activo == REUBEN){
  for(int i = 0; i < (*juego).tope_comida; i++){
  for(int j = 0; j < (*juego).comida[i].tope_ingredientes; j ++){
 if(!no_hay_ingredientes(*juego, (*juego).reuben.posicion.fil, (*juego).reuben.posicion.col) && ((*juego).reuben.objeto_en_mano == MANO_VACIA)){

  if(((*juego).comida[i].ingrediente[j].posicion.fil == (*juego).reuben.posicion.fil) && ((*juego).comida[i].ingrediente[j].posicion.col == (*juego).reuben.posicion.col)){
  (*juego).reuben.objeto_en_mano = (*juego).comida[i].ingrediente[j].tipo;
  (*juego).comida[i].ingrediente[j].posicion.fil = -1;
  (*juego).comida[i].ingrediente[j].posicion.col = -1;

  printf("Reuben: Ohh mis manos recibieron un ingrediente del tipo %c!\n", (*juego).comida[i].ingrediente[j].tipo);
  } 

 } else if(!no_hay_ingredientes(*juego, (*juego).reuben.posicion.fil, (*juego).reuben.posicion.col) && ((*juego).reuben.objeto_en_mano != MANO_VACIA)){
  j = (*juego).comida[i].tope_ingredientes;
  i = (*juego).tope_comida;

  printf("Reuben: Cuantas cosas queres que tenga en la mano?\n");

 } else if(no_hay_ingredientes(*juego, (*juego).reuben.posicion.fil, (*juego).reuben.posicion.col) && no_hay_herramienta(*juego, (*juego).stitch.posicion.fil, (*juego).stitch.posicion.col) && ((*juego).comida[i].ingrediente[j].tipo == (*juego).reuben.objeto_en_mano)){
  (*juego).comida[i].ingrediente[j].posicion.fil = (*juego).reuben.posicion.fil;
  (*juego).comida[i].ingrediente[j].posicion.col = (*juego).reuben.posicion.col;
  (*juego).reuben.objeto_en_mano = MANO_VACIA;
 
 }
  }
  }
}

}


void usar_cuchillo(juego_t* juego){
  if((*juego).personaje_activo == STITCH){
  if(!no_hay_herramienta(*juego,(*juego).stitch.posicion.fil,(*juego).stitch.posicion.col) && ((*juego).stitch.objeto_en_mano != MANO_VACIA)){ // despues validar matafuegos

  for(int i = 0; i < juego->tope_herramientas; i++){
   if((*juego).herramientas[i].posicion.fil == (*juego).stitch.posicion.fil && (*juego).herramientas[i].posicion.col == (*juego).stitch.posicion.col){

   for(int x = 0; x < juego->tope_comida; x++){
    for(int y = 0; y < juego->comida[x].tope_ingredientes; y++) {
   if((juego->comida[x].ingrediente[y].tipo == (*juego).stitch.objeto_en_mano) && (juego->comida[x].ingrediente[y].esta_cortado == false) ){
    juego->comida[x].ingrediente[y].esta_cortado = true;
    printf("Stitch: Jeje cortao bacalo\n");
   } 
   else if (((juego->comida[x].ingrediente[y].tipo == (*juego).stitch.objeto_en_mano) && (juego->comida[x].ingrediente[y].esta_cortado == false)) || juego->stitch.objeto_en_mano == MANO_VACIA){
    printf("Stitch: Es como si estuviera recibiendo ordenes sin sentido...\n");
    i = juego->tope_herramientas;

       }
          }
          }
  } 
          }   
  } 
 } else if ((*juego).personaje_activo == REUBEN){
  printf("Reuben: Es extraño.. tengo unas locas ganas de cortar algo aunque no conozco esa funcion...\n");
 }
}


void interactuar_con_mesa(juego_t* juego){
  if((*juego).personaje_activo == STITCH){
  for(int i = 0; i < juego->tope_comida; i++){
  for(int j = 0; j < juego->comida[i].tope_ingredientes; j++){
     if((juego->comida[i].ingrediente[j].tipo == juego->stitch.objeto_en_mano) && (calcular_distancia(juego->stitch.posicion.fil, juego->stitch.posicion.col, (*juego).mesa.fil, (*juego).mesa.col) <= 1) && no_hay_ingredientes(*juego, (*juego).mesa.fil, (*juego).mesa.col)){
     juego->comida[i].ingrediente[j].posicion.fil = (*juego).mesa.fil;
     juego->comida[i].ingrediente[j].posicion.col = (*juego).mesa.col;
     juego->stitch.objeto_en_mano = MANO_VACIA;
     printf("Stitch: REUBEN!!! VENÌ A BUSCARLO!\n");
     }  else if((calcular_distancia(juego->stitch.posicion.fil, juego->stitch.posicion.col, (*juego).mesa.fil , (*juego).mesa.col ) <= 1) && ((*juego).comida[i].ingrediente[j].posicion.fil == (*juego).mesa.fil) && ((*juego).comida[i].ingrediente[j].posicion.col == (*juego).mesa.col) && ((*juego).stitch.objeto_en_mano == MANO_VACIA)){
    (*juego).stitch.objeto_en_mano = (*juego).comida[i].ingrediente[j].tipo;
    (*juego).comida[i].ingrediente[j].posicion.fil = -1;
    (*juego).comida[i].ingrediente[j].posicion.col = -1;

  }  else if((calcular_distancia(juego->reuben.posicion.fil, juego->reuben.posicion.col, (*juego).mesa.fil, (*juego).mesa.col) <= 1) && ((*juego).comida[i].ingrediente[j].posicion.fil == (*juego).mesa.fil) && ((*juego).comida[i].ingrediente[j].posicion.col == (*juego).mesa.col)  && ((*juego).reuben.objeto_en_mano != MANO_VACIA)){
    printf("Reuben: Cuantas cosas queres que tenga en la mano?\n");
    i = juego->tope_comida;
    j = juego->comida[i].tope_ingredientes;
  }
      }
      }
  } else if((*juego).personaje_activo == REUBEN){
  for(int i = 0; i < juego->tope_comida; i++){
  for(int j = 0; j < juego->comida[i].tope_ingredientes; j++){
  if((calcular_distancia(juego->reuben.posicion.fil, juego->reuben.posicion.col, (*juego).mesa.fil , (*juego).mesa.col ) <= 1) && ((*juego).comida[i].ingrediente[j].posicion.fil == (*juego).mesa.fil) && ((*juego).comida[i].ingrediente[j].posicion.col == (*juego).mesa.col) && ((*juego).reuben.objeto_en_mano == MANO_VACIA)){
    (*juego).reuben.objeto_en_mano = (*juego).comida[i].ingrediente[j].tipo;
    (*juego).comida[i].ingrediente[j].posicion.fil = -1;
    (*juego).comida[i].ingrediente[j].posicion.col = -1;

  } else if((juego->comida[i].ingrediente[j].tipo == juego->reuben.objeto_en_mano) && (calcular_distancia(juego->reuben.posicion.fil, juego->reuben.posicion.col, (*juego).mesa.fil, (*juego).mesa.col) <= 1) && no_hay_ingredientes(*juego, (*juego).mesa.fil, (*juego).mesa.col)){
     juego->comida[i].ingrediente[j].posicion.fil = (*juego).mesa.fil;
     juego->comida[i].ingrediente[j].posicion.col = (*juego).mesa.col;
     juego->reuben.objeto_en_mano = MANO_VACIA;
     printf("reuben: REUBEN!!! VENÌ A BUSCARLO!\n");
     }

  else if((calcular_distancia(juego->reuben.posicion.fil, juego->reuben.posicion.col, (*juego).mesa.fil, (*juego).mesa.col) <= 1) && ((*juego).comida[i].ingrediente[j].posicion.fil == (*juego).mesa.fil) && ((*juego).comida[i].ingrediente[j].posicion.col == (*juego).mesa.col)  && ((*juego).reuben.objeto_en_mano != MANO_VACIA)){
    printf("Reuben: Cuantas cosas queres que tenga en la mano?\n");
    i = juego->tope_comida;
    j = juego->comida[i].tope_ingredientes;
  }
   }
   }
  }


}


void interactuar_con_horno(juego_t* juego){

  if((*juego).personaje_activo == STITCH){
  printf("Stitch: Si tan solo yo pudiera usar los hornos *llora*\n");
  } 

  else if((*juego).personaje_activo == REUBEN){
  for(int i = 0; i < (*juego).tope_herramientas; i++){

  if(calcular_distancia((*juego).reuben.posicion.fil, (*juego).reuben.posicion.col, (*juego).herramientas[i].posicion.fil, (*juego).herramientas[i].posicion.col) == 1){
  for(int j = 0; j < (*juego).tope_comida; j++){
  for(int k = 0; k < (*juego).comida[j].tope_ingredientes; k++){
  if(((*juego).reuben.objeto_en_mano == MASA || (*juego).reuben.objeto_en_mano == CARNE || (*juego).reuben.objeto_en_mano == MILANESA) && ((*juego).comida[j].ingrediente[k].tipo == (*juego).reuben.objeto_en_mano) && !(*juego).comida[j].ingrediente[k].esta_cocinado){
    (*juego).comida[j].ingrediente[k].esta_cocinado = true;
    printf("Reuben: Cocinadisimo!!\n");
    k = (*juego).comida[j].tope_ingredientes;
    j = (*juego).tope_comida;
  }
    }
    }
  }
    }
    
  }
}



// FIN MOVIMIENTOS





void realizar_jugada(juego_t* juego, char movimiento) {
  chequear_pared(juego, movimiento);
  chequear_puerta(juego);
  chequear_comidas(juego);
  switch(movimiento){
  case CAMBIAR_PERSONAJE: 
  personaje_activo(juego);
  break;
  case TOMAR_ALIMENTO:
  tomar_ingrediente(juego);
  break;
  case USAR_CUCHILLO:
  usar_cuchillo(juego);
  break;
  case INTERACTUAR_CON_MESA:
  interactuar_con_mesa(juego);
  break;
  case USAR_HORNO:
  interactuar_con_horno(juego);
  break;
  } 
  if((*juego).movimientos == 15){
    if((*juego).personaje_activo == STITCH){
   anadir_matafuegos_cuadrante_stitch(juego);
   anadir_fuego_cuadrante_stitch(juego);

    } else if ((*juego).personaje_activo == REUBEN){
    anadir_matafuegos_cuadrante_reuben(juego);
    anadir_fuego_cuadrante_reuben(juego);

    }
  } 
  

  imprimir_terreno(*juego);


}

int estado_juego(juego_t juego){
  int resultado = SIGUE_JUGANDO;
  if(!no_hay_obstaculo(juego, juego.stitch.posicion.fil, juego.stitch.posicion.col) || !no_hay_obstaculo(juego, juego.reuben.posicion.fil, juego.reuben.posicion.col)){
    resultado = PERDIO;
  } else if(condicion_ganadora(juego)){
    resultado = GANO;
  }

  return resultado;
}






