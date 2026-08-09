//LABERINTO: Creacion de un laberinto de 2D recursivo

// Includes

#include <stdlib.h>

// Constantes

// Tipos

typedef enum {NORTH=1,EAST=2,WEST=4,SOUTH=8} Direction;

struct Pair;
struct Laberinth;

// Funciones

struct Laberinth* lab_new(unsigned int rows,unsigned int columns);
// construye un laberinto de r: filas i c: columnas

void lab_del(struct Laberinth** l);
//liberamos el espacio del laberinto

unsigned int lab_get(struct Laberinth* l,unsigned int r,unsigned int c);
// da las salidas de la habitacion situada en fila r, columna c


    
