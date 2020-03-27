#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

typedef void (*FuncionVisitante) (int dato);

typedef int (*Comparacion) (int n1, int n2);

typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

/**
 * Devuelve una lista vacía.
 */
SList slist_crear();

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Determina si la lista es vacía.
 */
int slist_vacia(SList lista);

/**
 * Agrega un elemento al final de la lista.
 */
SList slist_agregar_final(SList lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar_inicio(SList lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void slist_recorrer(SList lista, FuncionVisitante visit);

int slist_longitud(SList lista);

SList slist_concatenar(SList l1, SList l2);

SList slist_insertar(SList l, int pos, int dato);

SList slist_eliminar(SList l, int pos);

int slist_contiene(SList l, int dato);

int slist_indice(SList l, int dato);

SList slist_intersecar(SList l1, SList l2);

SList slist_intersecar_custom(SList l1, SList l2, int (*comp) (int, int));

SList slist_ordenar(SList l, int (*comp) (int, int));

SList slist_reverso(SList l);

SList slist_intercalar(SList l1, SList l2);

#endif /* __SLIST_H__ */
