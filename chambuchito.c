#include <stdio.h>
#include "chambuchito.h"

const char PAN_BLANCO = 'B';
const char PAN_INTEGRAL = 'I';
const char PAN_AVENA_MIEL = 'A';
const char PAN_OREGANO = 'Q';
const char QUESO_DAMBO = 'D';
const char QUESO_CHEDDAR = 'C';
const char QUESO_GRUYERE = 'G';
const char SIN_QUESO = 'S';
const char PROTE_ROAST_BEEF = 'R';
const char PROTE_ATUN = 'A';
const char PROTE_SOJA = 'S';
const char PROTE_POLLO = 'P';
const char SIN_PROTE = 'N';
const int PRECIO_PAN_BASICO = 5;
const int PRECIO_PAN_ESPECIAL = 8;
const int PRECIO_QUESO_BASICO = 5;
const int PRECIO_QUESO_ESPECIAL = 8;
const int PRECIO_ROASTBEEF = 7;
const int PRECIO_ATUN = 9;
const int PRECIO_POLLO = 5;
const int PRECIO_SOJA = 3;

// Pre: 
// Pos: Asigna un valor valido a la variable segun lo que responda el usuario. (el varia varia desde "15" a "30" segun elija el usuario).
void pregunta_sobre_medida(int* medida){
    printf("¿De que medida desea su chambuchito? (Las medidas son desde 15cm hasta 30cm).\n");
    scanf(" %i", medida);
    while(*medida < 15 || *medida > 30) {
        printf("Por favor ingrese numero entre 15 y 30!\n");
        scanf(" %i", medida);
    }
}

// Pre: 
// Pos: Asigna un valor valido a la variable segun lo que responda el usuario. (el valor varia entre las constantes "PRECIO_PAN_XXX").
void pregunta_sobre_pan(int* precio_pregunta_pan){
    char tipo_pan = ' ';
    
    printf("¿Que pan desea en su chambuchito? (B: Blanco, I: Integral, A: Avena y miel, Q: Oregano).\n");
    scanf(" %c", &tipo_pan);

    while((tipo_pan != PAN_BLANCO) && (tipo_pan != PAN_INTEGRAL) && (tipo_pan != PAN_AVENA_MIEL) && (tipo_pan != PAN_OREGANO)) {
     printf("Por favor introduce algun tipo de pan con su respectiva letra.\n");
     scanf(" %c", &tipo_pan);
     }
    if(tipo_pan == PAN_BLANCO || tipo_pan == PAN_INTEGRAL) { 
     *precio_pregunta_pan = PRECIO_PAN_BASICO;
     } else {
     *precio_pregunta_pan = PRECIO_PAN_ESPECIAL;
    }

}

// Pre:
// Pos: Asigna un valor valido a la variable segun lo que responda el usuario. (el valor varia entre las constantes "PRECIO_QUESO_XXX").
void pregunta_sobre_queso(int* precio_pregunta_queso){
     char tipo_queso = ' ';

     printf("¿De que queso queres tu chambuchito? (D: Dambo, C: Cheddar, G: Gruyere, S: Sin queso)\n");
     scanf(" %c", &tipo_queso);
    while((tipo_queso != QUESO_DAMBO) && (tipo_queso != QUESO_CHEDDAR) && (tipo_queso != QUESO_GRUYERE) && (tipo_queso != SIN_QUESO)){
     printf("Por favor introduce algun tipo de queso con su respectiva letra. \n");
     scanf(" %c", &tipo_queso);
     }
    if((tipo_queso == QUESO_DAMBO) || (tipo_queso == QUESO_CHEDDAR)) {
     *precio_pregunta_queso = PRECIO_QUESO_BASICO;
     } else if (tipo_queso == QUESO_GRUYERE) {
        *precio_pregunta_queso = PRECIO_QUESO_ESPECIAL;
        } else {
            *precio_pregunta_queso = 0;
            }
}

// Pre:
// Pos: Asigna un valor valido a la variable segun lo que responda el usuario. (el valor varia entre las constantes "PRECIO_ATUN / ROASTBEEF / POLLO / SOJA").
void pregunta_sobre_prote_y_temperatura(int* precio_pregunta_prote) {
     char tipo_prote = ' ';
     char  chambuchito_temperatura = ' ';

     printf("¿Que proteina queres en tu chambuchito? Ojo que si elegis atun el sandwich no se calienta! (R: Roast Beef, A: Atun, S: Soja, P: Pollo, N: Nada de prote)\n");
     scanf(" %c", &tipo_prote);
    while((tipo_prote != PROTE_ROAST_BEEF) && (tipo_prote != PROTE_ATUN) && (tipo_prote != PROTE_SOJA) && (tipo_prote != PROTE_POLLO) && (tipo_prote != SIN_PROTE)) {
     printf("Por favor introduce algun tipo de prote con su respectiva letra. \n");
     scanf(" %c", &tipo_prote);
     }
    switch(tipo_prote){
     case 'R': *precio_pregunta_prote = PRECIO_ROASTBEEF; break;
     case 'A': *precio_pregunta_prote = PRECIO_ATUN; break;
     case 'S': *precio_pregunta_prote = PRECIO_SOJA; break;
     case 'P': *precio_pregunta_prote = PRECIO_POLLO; break;
     case 'N': *precio_pregunta_prote = 0; break;
     }
    if(tipo_prote != PROTE_ATUN) {
     printf("¿Deseás tu chambuchito caliente? (S: Si, N: No)\n");
     scanf(" %c", &chambuchito_temperatura);
    }

}

void calcular_precio_chambuchito (int* precio) {
 *precio = 0;
 int medida = 0;
 int precio_pregunta_pan = 0;
 int precio_pregunta_queso = 0;
 int precio_pregunta_prote = 0;

 pregunta_sobre_medida(&medida);
 pregunta_sobre_pan(&precio_pregunta_pan);
 pregunta_sobre_queso(&precio_pregunta_queso);
 pregunta_sobre_prote_y_temperatura(&precio_pregunta_prote);


 double precio_total = (precio_pregunta_pan + precio_pregunta_queso + precio_pregunta_prote) * (0.3 * medida);
 *precio = (int) precio_total;
 
}
