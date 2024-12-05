#ifndef PIZZA_H_INCLUDED
#define PIZZA_H_INCLUDED

#include "ingredientes.h"

#define MAX_INGREDIENTES 10  // Define o máximo de ingredientes por pizza

typedef struct pizza {
    int id;
    char nome[50];
    char tamanho;
    float preco;
    ingredientes ingrediente[MAX_INGREDIENTES];  // Vetor de ingredientes
} pizza;

void createPizza(void);
void readPizza(void);
void removerPizza(void);
void editarPizza(void);
void registraVenda (void);

#endif // PIZZA_H_INCLUDED
