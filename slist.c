#include "slist.h"
#include <stdlib.h>
#include <stdio.h>

void print_entero(int dato) {
  printf("%d ", dato);
}

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

int slist_longitud(SList lista) {
  int i = 0;
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig, i++);
  return i;
}

SList slist_concatenar(SList l1, SList l2) {
  if (l1 == NULL ) {
    return l2;
  } else if (l2 == NULL) {
    return l1;
  }
  SList nodo = l1;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  nodo->sig = l2;
  return l1;
}

SList slist_insertar(SList l, int pos, int dato) {
  SNodo *nuevo = malloc(sizeof(SNodo));
  nuevo->dato = dato;
  if (l == NULL || pos == 0) {
    nuevo->sig = l;
    return nuevo;
  }
  int i;
  SNodo *nodo = l;
  for (i = 0; nodo->sig != NULL && i < pos - 1; nodo = nodo->sig, i++);
  nuevo->sig = nodo->sig;
  nodo->sig = nuevo;
  return l;
}

SList slist_eliminar(SList l, int pos) {
  if (l == NULL) {
    return l;
  } else if (pos == 0) {
    SNodo* nodo = l->sig;
    free(l);
    return nodo;
  }
  int i;
  SNodo *nodo = l;
  for (i = 0; i < pos - 1; nodo = nodo->sig, i++) {
    if (nodo->sig == NULL)
      return l;
  }
  if (nodo->sig != NULL) {
    SNodo* sig = nodo->sig->sig;
    free(nodo->sig);
    nodo->sig = sig;
  }
  return l;
}

int slist_contiene(SList l, int dato) {
  for (SNodo *nodo = l; nodo != NULL; nodo = nodo->sig) {
    if (nodo->dato == dato)
      return 1;
  }
  return 0;
}

int slist_indice(SList l, int dato) {
  int i = 0;
  for (SNodo *nodo = l; nodo != NULL; nodo = nodo->sig, i++) {
    if (nodo->dato == dato)
      return i;
  }
  return -1;
}

SList slist_intersecar(SList l1, SList l2) {
  SList l = slist_crear();
  for (SNodo *nodo = l1; nodo != NULL; nodo = nodo->sig) {
    if (slist_contiene(l2, nodo->dato) && !slist_contiene(l, nodo->dato)) {
      l = slist_agregar_inicio(l, nodo->dato);
    }
  }
  return l;
}

SList slist_intersecar_custom(SList l1, SList l2, Comparacion comp) {
  SList l = slist_crear();
  for (SNodo *n1 = l1; n1 != NULL; n1 = n1->sig) {
    for (SNodo *n2 = l1; n2 != NULL; n2 = n2->sig) {
      if ((*comp)(n1->dato,n2->dato) && !slist_contiene(l, n1->dato)) {
        l = slist_agregar_inicio(l, n1->dato);
      }
    }
  }
  return l;
}

SList slist_ordenar(SList l, Comparacion comp) {
  if (l ==  NULL) {
    return l;
  }
  if (l->sig == NULL) {
    return l;
  }
  SList o = slist_crear();
  o = l;
  l = l->sig;
  o->sig = NULL;
  while (l != NULL) {
    if ((*comp)(l->dato, o->dato)) {
      SNodo* n = o;
      o = l;
      l = l->sig;
      o->sig = n;
    } else {
      int i = 0, flag = 0;
      for (SNodo *n = o; n != NULL && !flag; n = n->sig) {
        if (n->sig == NULL) {
          n->sig = l;
          l = l->sig;
          n->sig->sig = NULL;
          flag = 1;
        } else if ((*comp)(l->dato, n->sig->dato)) {
          SNodo* n1 = n->sig;
          n->sig = l;
          l = l->sig;
          n->sig->sig = n1;
          flag = 1;
        }
      }
    }
  }
  return o;
}

SList slist_reverso(SList l) {
  SList r = slist_crear();
  for (SList n = l; n != NULL; n = n->sig)
    r = slist_agregar_inicio(r, n->dato);
  return r;
}

SList slist_intercalar(SList l1, SList l2) {
  SList l = slist_crear(), n1 = l1, n2 = l2;
  while (n1 != NULL || n2 != NULL) {
    if (n1 != NULL) {
      l = slist_agregar_final(l, n1->dato);
      n1 = n1->sig;
    }
    if (n2 != NULL) {
      l = slist_agregar_final(l, n2->dato);
      n2 = n2->sig;
    }
  }
  return l;
}
