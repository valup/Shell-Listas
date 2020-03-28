#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"
#include "slist.h"

#define MAX_LEN 100

Listas lista_crear() {
  return NULL;
}

int lista_vacia(Listas lista) {
  return lista == NULL;
}

Listas lista_agregar_final(Listas lista, char *nombre, SList slista){
  Listas nuevoNodo = malloc(sizeof(Lista));
  nuevoNodo->nombre = malloc(sizeof(char)*MAX_LEN);
  strcpy(nuevoNodo->nombre, nombre);
  nuevoNodo->lista = slista;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  Listas nodo = lista;
  for (;nodo->sig != NULL ;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

Listas lista_agregar_inicio(Listas lista, char *nombre, SList slista) {
  Listas nuevoNodo = malloc(sizeof(Lista));
  nuevoNodo->nombre = malloc(sizeof(char)*MAX_LEN);
  strcpy(nuevoNodo->nombre, nombre);
  nuevoNodo->lista = slista;
  nuevoNodo->sig = lista;

  return nuevoNodo;
}

void lista_destruir(Listas lista) {
  if (lista == NULL) {
    return;
  }

  Listas nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    slist_destruir(nodoAEliminar->lista);
    free(nodoAEliminar->nombre);
    free(nodoAEliminar);
  }
}

void lista_imprimir(Listas lista) {
  for (Listas l = lista; l != NULL; l = l->sig) {
    printf("%s: ", l->nombre);
    for (SNodo *nodo = l->lista; nodo != NULL; nodo = nodo->sig)
      printf("%d ", nodo->dato);
    puts("");
  }
}

//eliminar_lista: GList char* -> GList
//recibe una lista de listas y el nombre de una lista
//la busca y si la encuentra la destruye
Listas lista_eliminar(Listas lista, char* nombre) {
  if (lista == NULL) {
    return lista;
  }

  if (!strcmp(lista->nombre, nombre)) {
    Listas ret = lista->sig;

    slist_destruir(lista->lista);
    free(lista->nombre);
    free(lista);

    printf("Lista %s destruida exitosamente\n", nombre);
    printf("Listas: ");
    for (Listas nodo = lista; nodo->sig != NULL; nodo = nodo->sig)
      printf("%s ", nodo->nombre);
    printf("\n");
    return ret;
  }

  for (Listas nodo = lista; nodo->sig != NULL; nodo = nodo->sig) {
    if (!strcmp(nodo->nombre, nombre)) {
      Listas sig = nodo->sig->sig;

      slist_destruir(nodo->lista);
      free(nodo->sig->nombre);
      free(nodo->sig);

      nodo->sig = sig;
      printf("Lista %s destruida exitosamente\n", nombre);
      printf("Listas: ");
      for (Listas nodo = lista; nodo->sig != NULL; nodo = nodo->sig)
        printf("%s ", nodo->nombre);
      printf("\n");
      return lista;
    }
  }
  //solo sale si no encontro la lista
  printf("ERROR: no existe la lista %s\n", nombre);
}
