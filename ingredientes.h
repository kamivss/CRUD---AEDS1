#ifndef INGREDIENTES_H_INCLUDED
#define INGREDIENTES_H_INCLUDED

typedef struct ingredientes {

    int id;
    char nome[50];
    float preco;

}ingredientes;

void createIngredientes (void);
void readIngredientes (void);
void removerIngredientes(void);
void editarIngredientes(void);

#endif // INGREDIENTES_H_INCLUDED
