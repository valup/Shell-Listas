#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "slist.h"
#include "lista.h"

#define MAX_LEN 100

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

int menor(int a, int b) {
  return a < b;
}

//indice: SList int -> void
//recibe una slist y un dato e imprime en pantalla
//todas las posiciones del dato en la lista si esta
void indice(SList lista, int dato) {
  int i = 0, cont = 0;
  for (SList nodo = lista; nodo != NULL; i++, nodo = nodo->sig) {
    if (nodo->dato == dato) {
      printf("%d ", i);
      cont++;
    }
  }
  if (!cont) {
    puts("ERROR: El dato no esta en la lista");
  } else {
    printf("\n");
  }
}

void empty_stdin()
{
    int c = getchar();
    while (c != '\n' && c != EOF)
        c = getchar();
}

int main(int argc, char const *argv[]) {
  printf("Ingrese 'help' para informacion sobre los comandos\n");

  // Lista de listas creadas
  Listas lista = lista_crear();

  // Buffer para leer la entrada estandar
  char* buf = malloc(sizeof(char)*MAX_LEN);

  // Bucle de Shell
  while (1) {
    printf(">> ");

    // [^\n] indica "leer hasta encontar.."
    scanf("%[^\n]s", buf);

    // Limpiamos el buffer para le proxima entrada
    empty_stdin();

    int args = 0;
    //args = cant de argumentos del comando

    char **partes = malloc(sizeof(char*)*4);
    char *parte = malloc(sizeof(char)*MAX_LEN);
    parte = strtok(buf, " ");

    // Asignamos memoria para las cadenas a utlizar
    for(int i = 0; i < 4; i++)
      partes[i] = malloc(sizeof(char)*MAX_LEN);


    //partes guardara los argumentos del comando
    //que son separados en parte con strtok
    while(parte){
      strcpy(partes[args++], parte);
      parte = strtok(NULL," ");
    }

    // Crear nueva lista enlazada
    if(!strcmp(partes[0], "crear")){
      Listas lista_ptr = lista;
      int existe = 0;
      while (lista_ptr)
      {
        // Si la lista ya existe, no volver a crearla
        if (!strcmp(partes[1], lista_ptr->nombre))
        {
          printf("La lista %s ya existe!\n", partes[1]);
          existe = 1;
          break;
        }
        lista_ptr = lista_ptr->sig;
      }

      // Si existe la lista, volver al shell
      if (existe)
        continue;


      SList slist = slist_crear();
      lista = lista_agregar_inicio(lista, partes[1], slist);
      printf("Lista %s creada exitosamente\n", partes[1]);

    }
    else if (!strcmp(partes[0],"destruir"))
    {
      //assert(args > 1);
      lista = lista_eliminar(lista, partes[1]);

    }

    else if (!strcmp(partes[0], "imprimir"))
    {
      Listas lista_ptr = lista;
      while(lista_ptr)
      {
        if (!strcmp(lista_ptr->nombre, partes[1]))
        {
          slist_recorrer(lista_ptr->lista, imprimir_entero);
          break;
        }
        lista_ptr = lista_ptr->sig;
      }

      if (!lista_ptr)
        printf("ERROR: no existe la lista %s\n", partes[1]);
    }
    else if (!strcmp(partes[0], "agregar_final"))
    {
      Listas lista_ptr = lista;
      while(lista_ptr)
      {
        if (!strcmp(lista_ptr->nombre, partes[1]))
        {
          lista_ptr->lista = slist_agregar_final(lista_ptr->lista, atoi(partes[2]));
          printf("Elemento agregado exitosamente: %s = ", partes[1]);
          slist_recorrer(lista_ptr->lista, imprimir_entero);
          break;
        }
        lista_ptr = lista_ptr->sig;
      }

      if (!lista_ptr)
        printf("ERROR: no existe la lista %s\n", partes[1]);

    }
    else if (!strcmp(partes[0], "agregar_inicio"))
    {

      Listas lista_ptr = lista;
      while(lista_ptr)
      {
        if (!strcmp(lista_ptr->nombre, partes[1]))
        {
          lista_ptr->lista = slist_agregar_inicio(lista_ptr->lista, atoi(partes[2]));
          printf("Elemento agregado exitosamente: %s = ", partes[1]);
          slist_recorrer(lista_ptr->lista, imprimir_entero);
          break;
        }
        lista_ptr = lista_ptr->sig;
      }

      if (!lista_ptr)
        printf("ERROR: no existe la lista %s\n", partes[1]);

    }
    else if (!strcmp(partes[0],"agregar_pos"))
    {
      //assert(args > 2);
      //assert(isdigit(partes[2]) && isdigit(partes[3]));

      Listas lista_ptr = lista;
      while(lista_ptr)
      {
        if (!strcmp(lista_ptr->nombre, partes[1]))
        {
          lista_ptr->lista = slist_insertar(lista_ptr->lista, atoi(partes[3]), atoi(partes[2]));
          printf("Elemento agregado exitosamente: %s = ", partes[1]);
          slist_recorrer(lista_ptr->lista, imprimir_entero);
          break;
        }
        lista_ptr = lista_ptr->sig;
      }

      if (!lista_ptr)
        printf("ERROR: no existe la lista %s\n", partes[1]);

    }
    else if (!strcmp(partes[0],"longitud"))
    {
      //assert(args > 1);

      Listas lista_ptr = lista;
      while(lista_ptr)
      {
        if (!strcmp(lista_ptr->nombre, partes[1]))
        {
          printf("Longitud de %s = %d\n", partes[1], slist_longitud(lista_ptr->lista));
          break;
        }
        lista_ptr = lista_ptr->sig;
      }

      if (!lista_ptr)
        printf("ERROR: no existe la lista %s\n", partes[1]);

    }

    else if (!strcmp(partes[0], "concatenar"))
    {
      Listas lista_ptr1 = lista;
      Listas lista_ptr2 = lista;

      // Checkear que lista1 exista
      while (lista_ptr1){
        if (!strcmp(lista_ptr1->nombre, partes[1]))
          break;
        lista_ptr1 = lista_ptr1->sig;
      }

      if (!lista_ptr1){
        printf("ERROR: no existe la lista %s\n", partes[1]);
        continue;
      }

      // Checkear que lista2 exista
      while (lista_ptr2){
        if (!strcmp(lista_ptr2->nombre, partes[2]))
          break;
        lista_ptr2 = lista_ptr2->sig;
      }

      if (!lista_ptr2){
        printf("ERROR: no existe la lista %s\n", partes[2]);
        continue;
      }

      // Concatenar listas
      //SList slist = slist_concatenar(lista_ptr1->lista, lista_ptr2->lista);
      SList slist_ptr = lista_ptr1->lista;
      SList slist = slist_crear();

      while(slist_ptr)
      {
        slist = slist_agregar_final(slist, slist_ptr->dato);
        slist_ptr = slist_ptr->sig;
      }

      slist_ptr = lista_ptr2->lista;

      while(slist_ptr)
      {
        slist = slist_agregar_final(slist, slist_ptr->dato);
        slist_ptr = slist_ptr->sig;
      }

      lista = lista_agregar_final(lista, partes[3], slist);

    }

    else if (!strcmp(partes[0], "eliminar"))
    {
      Listas lista_ptr = lista;
      while(lista_ptr)
      {
        if (!strcmp(lista_ptr->nombre, partes[1]))
          break;
        lista_ptr = lista_ptr->sig;
      }

      if (!lista_ptr)
      {
        printf("ERROR: no existe la lista %s\n", partes[1]);
        continue;
      }

      lista_ptr->lista = slist_eliminar(lista_ptr->lista, atoi(partes[2]));
      printf("Elemento eliminado exitosamente: %s = ", partes[1]);
      slist_recorrer(lista_ptr->lista, imprimir_entero);

    }
    else if (!strcmp(partes[0], "contiene"))
    {
      Listas lista_ptr = lista;
      while(lista_ptr)
      {
        if(!strcmp(lista_ptr->nombre, partes[1]))
          break;
        lista_ptr = lista_ptr->sig;
      }

      if(!lista_ptr){
        printf("ERROR: no existe la lista %s\n", partes[1]);
        continue;
      }

      if(slist_contiene(lista_ptr->lista, atoi(partes[2])))
        puts("SI");
      else
        puts("NO");

    }
    else if (!strcmp(partes[0], "indice"))
    {
      //assert(args > 2);
      //assert(isdigit(partes[2]));
      Listas lista_ptr = lista;
      while(lista_ptr)
      {
        if(!strcmp(lista_ptr->nombre, partes[1]))
          //slist_indice(lista_ptr->lista, atoi(partes[2]));
          break;
        lista_ptr = lista_ptr->sig;
      }

      if(!lista_ptr){
        printf("ERROR: no existe la lista %s\n", partes[1]);
        continue;
      }

      int elem = atoi(partes[2]);
      int index = 0;
      SList slist_aux = lista_ptr->lista;

      while(slist_aux)
      {
        if(slist_aux->dato == elem)
          printf("%d ", index);
        slist_aux = slist_aux->sig;
        index++;
      }
      printf("\n");
    }
    else if (!strcmp(partes[0],"intersecar"))
    {
      //assert(args > 3);

      Listas lista_ptr1 = lista;
      Listas lista_ptr2 = lista;

      // Checkear que lista1 exista
      while (lista_ptr1){
        if (!strcmp(lista_ptr1->nombre, partes[1]))
          break;
        lista_ptr1 = lista_ptr1->sig;
      }

      if (!lista_ptr1){
        printf("ERROR: no existe la lista %s\n", partes[1]);
        continue;
      }

      // Checkear que lista2 exista
      while (lista_ptr2){
        if (!strcmp(lista_ptr2->nombre, partes[2]))
          break;
        lista_ptr2 = lista_ptr2->sig;
      }

      if (!lista_ptr2){
        printf("ERROR: no existe la lista %s\n", partes[2]);
        continue;
      }

      // Concatenar listas
      SList slist = slist_intersecar(lista_ptr1->lista, lista_ptr2->lista);

      lista = lista_agregar_final(lista, partes[3], slist);

      printf("Listas intersecadas exitosamente: %s = ", partes[3]);
      slist_recorrer(slist, imprimir_entero);
      printf("\n");
    }
    else if (!strcmp(partes[0],"ordenar"))
    {
      //assert(args > 1);

      Listas lista_ptr = lista;
      while(lista_ptr)
      {
        if (!strcmp(lista_ptr->nombre, partes[1]))
        {
          break;
        }
        lista_ptr = lista_ptr->sig;
      }

      if (!lista_ptr)
        printf("ERROR: no existe la lista %s\n", partes[1]);

      lista_ptr->lista = slist_ordenar(lista_ptr->lista, menor);
      printf("Lista ordenada exitosamente: %s = ", partes[1]);
      slist_recorrer(lista_ptr->lista, imprimir_entero);

    }
    else if (!strcmp(partes[0],"quit"))
    {
      //libero antes de salir
      //unica forma de salir
      for (int i = 0; i < 4; i++) {
        free(partes[i]);
      }
      free(partes);
      free(parte);
      free(buf);
      lista_destruir(lista);

      return 0;
    }

    else if (!strcmp(partes[0], "help"))
    {
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

    }
    else
    {
      puts("ERROR: comando invalido");
    }
    for (int i = 0; i < 4; i++) {
      free(partes[i]);
    }
    free(partes);
    free(parte);
  }
  return 0;
}
