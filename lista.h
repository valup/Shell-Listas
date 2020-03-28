#ifndef __LISTA_H__
#define __LISTA_H__
#include "slist.h"

typedef struct _Lista {
  char* nombre; //nombre que da el usuario a la lista
  SNodo* lista;
  struct _Lista *sig;
} Lista;

typedef Lista *Listas;

/*
* Devuelve una lista vacía.
*/
Listas lista_crear();

/**
 * Destruccion de la lista.
 */
void lista_destruir(Listas lista);

/**
 * Determina si la lista es vacía.
 */
int lista_vacia(Listas lista);

/**
 * Agrega un elemento al final de la lista.
 */
Listas lista_agregar_final(Listas lista, char *nombre, SList slista);

/**
 * Agrega un elemento al inicio de la lista.
 */
Listas lista_agregar_inicio(Listas lista, char *nombre, SList slista);

/**
 * Recorrido de las listas.
 */
void lista_imprimir(Listas lista);

/**
 * Elimina una lista.
 */
Listas lista_eliminar(Listas lista, char* nombre);



#endif /* __LISTA_H__ */
