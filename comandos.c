#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "slist.h"
#include "glist.h"

#define MAX_LEN 100

typedef struct _Lista {
  char* nombre; //nombre que da el usuario a la lista
  SNodo* lista;
} Lista;

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

int menor(int a, int b) {
  return a < b;
}

// char* argumentos(char* com, int* cant) {
//   int longs[4] = {0,0,0,0}, i = 0, j = 1, l = 0;
//   for(;com[i] != '\0' && *cant < 4; i++) {
//     if (com[i] == ' ') {
//       longs[*cant] = j;
//       (*cant)++;
//       j = 1;
//     } else { j++;}
//   }
//   longs[*cant] = j;
//   (*cant)++;
//   char** args = malloc(sizeof(char*)*(*cant));
//   for(i = 0, j = 0; j <= (*cant); j++) {
//     args[j] = malloc(sizeof(char)*longs[j]);
//     for(l = 0; com[i] != ' ' && com[i] != '\0'; i++, l++) {
//       args[j][l] = com[i];
//     }
//     args[j][l] = '\0';
//     i++;
//   }
//   return args;
// }

//eliminar_lista: GList char* -> GList
//recibe una lista de listas y el nombre de una lista
//la busca y si la encuentra la destruye
GList eliminar_lista(GList listas, char* nombre) {
  //assert(listas != NULL);

  Lista* l = (Lista*) listas->dato;
  //compara con primera lista
  if (!strcmp(l->nombre, nombre)) {
    GList ret = listas->sig;
    Lista* l = (Lista*) listas->dato;

    slist_destruir(l->lista);
    free(listas->dato);
    free(listas);

    printf("Lista %s destruida exitosamente\n", nombre);
    return ret;
  }

  for (GList nodo = listas; nodo->sig != NULL; nodo = nodo->sig) {
    l = (Lista*) nodo->sig->dato;
    //compara con lista siguiente
    if (!strcmp(l->nombre, nombre)) {
      GList sig = nodo->sig->sig;

      slist_destruir(l->lista);
      free(nodo->sig->dato);
      free(nodo->sig);

      nodo->sig = sig;
      printf("Lista %s destruida exitosamente\n", nombre);
      return listas;
    }
  }
  //solo sale si no encontro la lista
  printf("ERROR: no hay lista creada con ese nombre");
}

//indice: SList int -> void
//recibe una slist y un dato e imprime en pantalla
//todas las posiciones del dato en la lista si esta
void indice(SList lista, int dato) {
  int i = 0, cont = 0;
  for (SList nodo = lista; nodo != NULL; i++, nodo = nodo->sig) {
    if (nodo->dato ==  dato) {
      printf("%d ", i);
      cont++;
    }
  }
  if (!cont) {
    puts("ERROR: El dato no esta en la lista");
  }
}

//destruir_listas: GList -> void
//recibe una lista de listas y la destruye
void destruir_listas(GList listas) {
  GNodo *nodoAEliminar;
  while (listas != NULL) {
    nodoAEliminar = listas;
    listas = listas->sig;
    Lista* l = (Lista *) nodoAEliminar->dato;
    slist_destruir(l->lista);
    free(l);
    free(nodoAEliminar);
  }
}

int main(int argc, char const *argv[]) {
  printf("Ingrese 'help' para informacion sobre los comandos\n");
  GList listas = glist_crear();//lista de listas creadas
  char* buf = malloc(sizeof(char) * MAX_LEN);
  while (1) {
    printf(">> ");
    scanf("%s", buf);

    int args = 0, esta, esta1, esta2;
    Lista *l1, *l2;
    //args = cant de argumentos del comando
    //esta, esta1 y esta2 son usados por varios comandos
    //para chequear si se encuentra la lista buscada
    //l1 y l2 se usan en concatenar e intersecar

    char *partes[4], *parte = strtok(buf, " ");
    //partes guardara los argumentos del comando
    //que son separados en parte con strtok
    for(; args < 4 && parte != NULL; args++) {
      partes[args] = malloc(sizeof(parte));
      strcpy(partes[args], parte);
      parte = strtok(NULL," ");
    }
    for(int i = 0; i < args; i++) {
      printf("%s\n", partes[i]);//test de argumentos
      //el programa sigue antes de terminar de imprimirlos
    }

    if(!strcmp(partes[0],"crear")) {
      //assert(args > 1);

      Lista* l = malloc(sizeof(Lista));
      l->nombre = partes[1];
      l->lista = slist_crear();

      listas = glist_agregar_inicio(listas, (void*) l);
      printf("Lista %s creada exitosamente\n", partes[1]);

    } else if (!strcmp(partes[0],"destruir")) {
      //assert(args > 1);
      listas = eliminar_lista(listas, partes[1]);

    } else if (!strcmp(partes[0],"imprimir")) {
      //assert(args > 1);

      esta = 0;
      for (GList nodo = listas; nodo != NULL && !esta; nodo = nodo->sig) {
        Lista* l = (Lista*) nodo->dato;

        if (!strcmp(l->nombre,partes[1])) {
          //compara el nombre buscado con los de las listas creadas
          esta++;
          slist_recorrer(l->lista,imprimir_entero);
          puts("");
        }
      }

      if (!esta) {
        printf("ERROR: no existe la lista %s\n", partes[1]);
      }
    } else if (!strcmp(partes[0],"agregar_final")) {
      //assert(args > 2);
      //assert(isdigit(partes[2]));

      esta = 0;
      for (GList nodo = listas; nodo != NULL && !esta; nodo = nodo->sig) {
        Lista* l = (Lista*) nodo->dato;

        if (!strcmp(l->nombre, partes[1])) {
          esta++;
          l->lista = slist_agregar_final(l->lista, atoi(partes[2]));

          printf("Elemento agregado exitosamente: %s = ", partes[1]);
          slist_recorrer(l->lista, imprimir_entero);
          puts("");
        }
      }

      if (!esta) {
        printf("ERROR: no existe la lista %s\n", partes[1]);
      }

    } else if (!strcmp(partes[0],"agregar_inicio")) {
      //assert(args > 2);
      //assert(isdigit(partes[2]));

      esta = 0;
      for (GList nodo = listas; nodo != NULL && !esta; nodo = nodo->sig) {
        Lista* l = (Lista*) nodo->dato;

        if (!strcmp(l->nombre, partes[1])) {
          esta++;
          l->lista = slist_agregar_inicio(l->lista, atoi(partes[2]));

          printf("Elemento agregado exitosamente: %s = ", partes[1]);
          slist_recorrer(l->lista, imprimir_entero);
          puts("");
        }
      }

      if (!esta) {
        printf("ERROR: no existe la lista %s\n", partes[1]);
      }

    } else if (!strcmp(partes[0],"agregar_pos")) {
      //assert(args > 2);
      //assert(isdigit(partes[2]) && isdigit(partes[3]));

      esta = 0;
      for (GList nodo = listas; nodo != NULL && !esta; nodo = nodo->sig) {
        Lista* l = (Lista*) nodo->dato;

        if (!strcmp(l->nombre, partes[1])) {
        esta++;
        l->lista = slist_insertar(l->lista, atoi(partes[3]), atoi(partes[2]));

        printf("Elemento agregado exitosamente: %s = ", partes[1]);
        slist_recorrer(l->lista, imprimir_entero);
        puts("");
        }
      }

      if (!esta) {
        printf("ERROR: no existe la lista %s\n", partes[1]);
      }

    } else if (!strcmp(partes[0],"longitud")) {
      //assert(args > 1);

      esta = 0;
      for (GList nodo = listas; nodo != NULL && !esta; nodo = nodo->sig) {
        Lista* l = (Lista*) nodo->dato;

        if (!strcmp(l->nombre, partes[1])) {
          esta++;
          printf("Longitud de %s = %d\n", partes[1], slist_longitud(l->lista));
        }
      }

      if (!esta) {
        printf("ERROR: no existe la lista %s\n", partes[1]);
      }

    } else if (!strcmp(partes[0],"concatenar")) {
      //assert(args > 3);

      esta1 = 0, esta2 = 0;
      for (GList nodo = listas; nodo != NULL && (!esta1 || !esta2); nodo = nodo->sig) {
        Lista* n = (Lista*) nodo->dato;
        //si coincide alguno de los nombres
        //la guardo en el lugar correspondiente
        //y marco cual encontre
        if (!strcmp(n->nombre, partes[1])) {
          l1 = n;
          esta1++;
        } else if (!strcmp(l1->nombre, partes[2])) {
          l2 = n;
          esta2++;
        }
      }

      if (!esta1) {
        printf("ERROR: no existe la lista %s\n", partes[1]);
      } else if (!esta2) {
        printf("ERROR: no existe la lista %s\n", partes[1]);
      } else {
        Lista* l = malloc(sizeof(Lista));
        l->nombre = partes[3];
        l->lista = slist_concatenar(l1->lista, l2->lista);

        listas = glist_agregar_inicio(listas, (void*) l);
        printf("Lista creada exitosamente: %s = ", partes[3]);
        slist_recorrer(l->lista, imprimir_entero);
        puts("");
      }

    } else if (!strcmp(partes[0],"eliminar")) {
      //assert(args > 2);
      //assert(isdigit(partes[2]));

      esta = 0;
      for (GList nodo = listas; nodo != NULL && !esta; nodo = nodo->sig) {
        Lista* l = (Lista*) nodo->dato;

        if (!strcmp(l->nombre, partes[1])) {
          esta++;
          l->lista = slist_eliminar(l->lista, atoi(partes[2]));

          printf("Elemento eliminado exitosamente: %s = ", partes[1]);
          slist_recorrer(l->lista, imprimir_entero);
          puts("");
        }
      }

      if (!esta) {
        printf("ERROR: no existe la lista %s\n", partes[1]);
      }

    } else if (!strcmp(partes[0],"contiene")) {
      //assert(args > 2);
      //assert(isdigit(partes[2]));

      esta = 0;
      for (GList nodo = listas; nodo != NULL && !esta; nodo = nodo->sig) {
        Lista* l = (Lista*) nodo->dato;

        if (!strcmp(l->nombre, partes[1])) {
          esta++;
          if (slist_contiene(l->lista, atoi(partes[2]))) {
            puts("SI");
          } else { puts("NO"); }
        }
      }

      if (!esta) {
        printf("ERROR: no existe la lista %s\n", partes[1]);
      }

    } else if (!strcmp(partes[0],"indice")) {
      //assert(args > 2);
      //assert(isdigit(partes[2]));

      esta = 0;
      for (GList nodo = listas; nodo != NULL && !esta; nodo = nodo->sig) {
        Lista* l = (Lista*) nodo->dato;

        if (!strcmp(l->nombre, partes[1])) {
          esta++;
          indice(l->lista, atoi(partes[2]));
        }
      }

      if (!esta) {
        printf("ERROR: no existe la lista %s\n", partes[1]);
      }

    } else if (!strcmp(partes[0],"intersecar")) {
      //assert(args > 3);

      esta1 = 0, esta2 = 0;
      for (GList nodo = listas; nodo != NULL && (!esta1 || !esta2); nodo = nodo->sig) {
        Lista* n = (Lista*) nodo->dato;

        if (!strcmp(n->nombre, partes[1])) {
          l1 = n;
          esta1++;
        } else if (!strcmp(l1->nombre, partes[2])) {
          l2 = n;
          esta2++;
        }
      }

      if (!esta1) {
        printf("ERROR: no existe la lista %s\n", partes[1]);
      } else if (!esta2) {
        printf("ERROR: no existe la lista %s\n", partes[1]);
      } else {
        Lista* l = malloc(sizeof(Lista));
        l->nombre = partes[3];
        l->lista = slist_intersecar(l1->lista, l2->lista);

        listas = glist_agregar_inicio(listas, (void*) l);
        printf("Lista creada exitosamente: %s = ", partes[3]);
        slist_recorrer(l->lista, imprimir_entero);
        puts("");
      }

    } else if (!strcmp(partes[0],"ordenar")) {
      //assert(args > 1);

      esta = 0;
      for (GList nodo = listas; nodo != NULL && !esta; nodo = nodo->sig) {
        Lista* l = (Lista*) nodo->dato;

        if (!strcmp(l->nombre, partes[1])) {
          esta++;
          l->lista = slist_ordenar(l->lista, menor);
          printf("Lista ordenada exitosamente: %s = ", partes[1]);
          slist_recorrer(l->lista, imprimir_entero);
          puts("");
        }
      }

      if (!esta) {
        printf("ERROR: no existe la lista %s\n", partes[1]);
      }

    } else if (!strcmp(partes[0],"quit")) {
      //libero antes de salir
      //unica forma de salir
      destruir_listas(listas);
      free(buf);
      return 0;

    } else if (!strcmp(partes[0],"help")) {
      puts("Comandos:");
      puts("crear l: crea una lista de nombre l");
      puts("destruir l: destruye la lista l");
      puts("imprimir l: imprime el contenido actual de la lista l");
      puts("agregar_final l n: agrega entero n al final de la lista l");
      puts("agregar_inicio l n: agrega entero n al inicio de la lista l");
      puts("agregar_pos l n p: agrega entero n en la posicion p de la lista l");
      puts("longitud l: devuelve la longitud de la lista l");
      puts("concatenar l1 l2 l3: crea la lista l3 concatenando las listas existentes l1 y l2");
      puts("eliminar l p: elimina el elemento en la posicion p de la lista l");
      puts("contiene l n: imprime 'SI' si la lista l tiene el entero n, 'NO' en caso contrario");
      puts("indice l n: imprime la/s posicion/es en la/s que esta el entero n en la lista l");
      puts("intersecar l1 l2 l3: crea la lista l3 intersecando las listas existentes l1 y l2");
      puts("ordenar l: ordena los elementos de la lista l de menor a mayor");
      puts("quit: sale del prompt");

    } else {
      puts("ERROR: comando invalido");
    }
  }
  return 0;
}
