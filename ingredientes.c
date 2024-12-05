#include <stdio.h>
#include <stdlib.h>
#include "pizza.h"
#include "ingredientes.h"

void createIngredientes(void) {
    FILE *arquivo;
    arquivo = fopen("ingredientes.txt", "ab");
    ingredientes ing, ingTemp;
    int idJaExistente;

    do {
        system("cls");
        cabecalho();
        fflush(stdin);

        // Solicitar ID do ingrediente
        printf("Digite o id do ingrediente: ");
        scanf("%d", &ing.id);
        getchar();

        // Verificar se o ID já existe no arquivo
        idJaExistente = 0;
        FILE *controle = fopen("ingredientes.txt", "rb");
        if (controle == NULL) {
            printf("Erro ao abrir o arquivo de ingredientes.\n");
            return;
        }
        while (fread(&ingTemp, sizeof(ingredientes), 1, controle) == 1) {
            if (ing.id == ingTemp.id) {
                idJaExistente = 1;
                break;
            }
        }
        fclose(controle);

        if (idJaExistente) {
            printf("Erro: ID %d já está em uso. Escolha outro ID.\n", ing.id);
            sleep(2);
            return;  // Vai para o próximo loop para tentar com outro ID
        }

        // Solicitar o nome e preço do ingrediente
        printf("Digite o nome do ingrediente: ");
        fgets(ing.nome, 50, stdin);
        ing.nome[strcspn(ing.nome, "\n")] = '\0';  // Remove a nova linha
        fflush(stdin);

        printf("Digite o valor do ingrediente: ");
        scanf("%f", &ing.preco);

        // Confirmar o cadastro
        system("cls");
        printf("Ingrediente cadastrado com sucesso :)\n");
        sleep(2);

        // Gravar o ingrediente no arquivo
        fwrite(&ing, sizeof(ingredientes), 1, arquivo);
        puts("\n\nDeseja continuar? (s/n)");
    } while (getche() == 's');

    fclose(arquivo);
    sleep(5);
    system("cls");
}


void readIngredientes (void){

    ingredientes ing;
    system ("cls");
    cabecalho();
    FILE * arquivo;
    arquivo = fopen ("ingredientes.txt", "rb");
    if (arquivo == NULL){
        printf ("Nenhum arquivo encontrado");
    }else{
        while ( fread(&ing, sizeof (ingredientes), 1, arquivo) == 1){
            printf ("Id: %d\n", ing.id);
            printf ("Nome: %s\n", ing.nome);
            printf ("Valor: %.2f\n\n", ing.preco);
        }
    }
    sleep (5);
    system ("cls");
    fclose (arquivo);
}

void removerIngredientes(void) {
    FILE *arq;
    FILE *temp;
    ingredientes ing;
    int idToDelete;

    arq = fopen("ingredientes.txt", "rb");
    temp = fopen("tmp.txt", "wb");

    if (arq == NULL || temp == NULL) {
        printf("Problemas na abertura do arquivo!\n");
        return;
    }

    system("cls");
    printf("Digite o ID do ingrediente a deletar: ");
    scanf("%d", &idToDelete);
    fflush(stdin);

    while (fread(&ing, sizeof(ingredientes), 1, arq) == 1) {
        if (ing.id == idToDelete) {
            // Exibe os detalhes da pizza antes de excluí-la
            printf("Ingrediente encontrado:\n");
            printf("Id: %d\n", ing.id);
            printf("Nome: %s\n", ing.nome);
            printf("Valor: %.2f\n", ing.preco);
            printf("Deseja deletar este ingrediente? (s/n): ");
            if (getche() == 's') {
                printf("\nIngrediente deletado com sucesso.\n");
                continue;
            } else {
                fwrite(&ing, sizeof(ingredientes), 1, temp);
            }
        } else {
            fwrite(&ing, sizeof(ingredientes), 1, temp);
        }
    }

    fclose(arq);
    fclose(temp);

    // Apagar o arquivo original e renomear o temporário
    if (remove("ingredientes.txt") == 0 && rename("tmp.txt", "ingredientes.txt") == 0) {
        printf("\nOperação realizada com sucesso!\n");
    } else {
        remove("tmp.txt");
        printf("\nErro ao realizar a operação.\n");
    }
}

void editarIngredientes(void) {
    FILE *arq;
    FILE *temp;
    ingredientes ing;
    system ("cls");
    cabecalho();

    int idToEdit;
    int encontrou = 0;

    arq = fopen("ingredientes.txt", "rb");
    temp = fopen("tmp2.txt", "wb");

    if (arq == NULL || temp == NULL) {
        printf("Problemas na abertura do arquivo!\n");
        return;
    }

    printf("Digite o ID do ingrediente a editar: ");
    scanf("%d", &idToEdit);
    fflush(stdin);

    while (fread(&ing, sizeof(ingredientes), 1, arq) == 1) {
        if (ing.id == idToEdit) {
            encontrou = 1;

            // Exibe os detalhes do ingrediente antes de editá-la
            printf("\nIngrediente encontrado:\n");
            printf("Id: %d\n", ing.id);
            printf("Nome: %s\n", ing.nome);
            printf("Valor: %.2f\n", ing.preco);

            // Permitir edição
            printf("\nDigite os novos dados:\n");
            printf("Novo nome: ");
            fgets(ing.nome, sizeof(ing.nome), stdin);
            ing.nome[strcspn(ing.nome, "\n")] = 0; // Remove newline do fgets


            printf("Novo valor: ");
            scanf("%f", &ing.preco);
            fflush(stdin);

            printf("\nIngrediente editado com sucesso.\n");
        }

        fwrite(&ing, sizeof(ingredientes), 1, temp);
    }

    fclose(arq);
    fclose(temp);

    if (!encontrou) {
        printf("\nIngrediente com ID %d não encontrado.\n", idToEdit);
        remove("tmp2.txt");
    } else {
        // Apagar o arquivo original e renomear o temporário
        if (remove("ingredientes.txt") == 0 && rename("tmp2.txt", "ingredientes.txt") == 0) {
            printf("\nOperação realizada com sucesso!\n");
        } else {
            remove("tmp2.txt");
            printf("\nErro ao realizar a operação.\n");
        }
    }

    sleep (5);
    system ("cls");
}
