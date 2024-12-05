#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pizza.h"
#include "ingredientes.h"

#define MAX_INGREDIENTES 10  // Define o máximo de ingredientes por pizza

void createPizza(void) {
    int quant, cont = 0, encontrou = 0, encontrada = 0, controlID;
    system("cls");
    cabecalho();

    FILE *arquivo;
    FILE *controle;
    arquivo = fopen("pizzaria.txt", "ab");
    controle = fopen("ingredientes.txt", "rb");

    pizza p;
    ingredientes ing;
    char ingrediente[50];

    if (controle == NULL) {
        printf("Erro ao abrir o arquivo de ingredientes :(\n");
    } else {
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo de pizzas :(\n");
        } else {
            fflush(stdin);
            printf("Digite o id da pizza: ");
            scanf("%d", &controlID);
            fflush(stdin);

            // Verificar se o ID já existe no arquivo de pizzas
            FILE *verificaID;
            verificaID = fopen("pizzaria.txt", "rb");
            if (verificaID == NULL) {
                printf("Erro ao abrir o arquivo para verificar o ID :(\n");
            } else {
                while (fread(&p, sizeof(pizza), 1, verificaID) == 1) {
                    if (p.id == controlID) {
                        printf("Erro: O ID %d já está sendo utilizado por outra pizza. Tente outro ID.\n", controlID);
                        fclose(verificaID);
                        sleep (3);
                        return;  // Retorna sem cadastrar a pizza
                    }else{
                        p.id = controlID;
                    }
                }
                fclose(verificaID);
            }


            // Inicializar todos os ingredientes para garantir que não haja lixo
            memset(p.ingrediente, 0, sizeof(p.ingrediente));

            printf("Digite o nome da pizza: ");
            fgets(p.nome, 50, stdin);
            p.nome[strcspn(p.nome, "\n")] = '\0';
            fflush(stdin);

            printf("Digite o tamanho da pizza (P/M/G): ");
            scanf(" %c", &p.tamanho);

            printf("Digite o valor da pizza: ");
            scanf("%f", &p.preco);
            getchar();
            fflush(stdin);

            // Pergunta ao usuário quantos ingredientes deseja adicionar
            printf("Quantos ingredientes deseja adicionar à pizza? ");
            scanf("%d", &quant);
            getchar();

            // Garantir que não ultrapasse o limite de ingredientes
            if (quant > MAX_INGREDIENTES) {
                printf("O número máximo de ingredientes é %d. Ajustando a quantidade.\n", MAX_INGREDIENTES);
                quant = MAX_INGREDIENTES;
            }

            // Laço para adicionar múltiplos ingredientes
            for (int i = 0; i < quant; i++) {
                printf("\nDigite o nome do ingrediente %d: ", i + 1);
                fgets(ingrediente, 50, stdin);  // Use fgets no lugar de gets
                ingrediente[strcspn(ingrediente, "\n")] = '\0';  // Remove o '\n' do final da string

                encontrada = 0;
                rewind(controle);  // Garanta que o ponteiro de arquivo 'controle' está no início
                while (fread(&ing, sizeof(ingredientes), 1, controle) == 1) {
                    if (strcmp(ingrediente, ing.nome) == 0) {
                        printf("Ingrediente encontrado!!\n\n");
                        strcpy(p.ingrediente[i].nome, ing.nome);
                        p.ingrediente[i].id = ing.id;
                        p.ingrediente[i].preco = ing.preco;
                        encontrada++;
                    }
                    fflush(stdin);
                }

                if (encontrada == 0) {
                    printf("Ingrediente inválido! Ingrediente disponível não encontrado: %s\n\n", ingrediente);
                    i--;  // Decrementa o índice para permitir nova tentativa de inserir o ingrediente
                }
            }

            // Adicionando a pizza no arquivo
            fwrite(&p, sizeof(pizza), 1, arquivo);
            printf("\n\nPizza cadastrada com sucesso!\n");
        }
    }

    sleep(2);
    system("cls");

    fclose(arquivo);
    fclose(controle);
}



void readPizza(void) {
    pizza p;
    system("cls");
    cabecalho();
    FILE *arquivo;
    arquivo = fopen("pizzaria.txt", "rb");

    if (arquivo == NULL) {
        printf("Nenhum arquivo encontrado\n");
    } else {
        while (fread(&p, sizeof(pizza), 1, arquivo) == 1) {
            printf("Id: %d\n", p.id);
            printf("Nome: %s\n", p.nome);
            printf("Tamanho: %c\n", p.tamanho);
            printf("Valor: %.2f\n", p.preco);

            printf("Ingredientes: ");
            for (int i = 0; i < MAX_INGREDIENTES && p.ingrediente[i].nome[0] != '\0'; i++) {
                printf("%s ", p.ingrediente[i].nome);
            }
            printf("\n\n");
        }
    }
    fclose(arquivo);
    sleep(5);
    system("cls");
}



void removerPizza(void) {
    FILE *arq;
    FILE *temp;
    pizza p;
    int idToDelete;

    arq = fopen("pizzaria.txt", "rb");
    temp = fopen("tmp.txt", "wb");

    if (arq == NULL || temp == NULL) {
        printf("Problemas na abertura do arquivo!\n");
        return;
    }

    system("cls");
    printf("Digite o ID da pizza a deletar: ");
    scanf("%d", &idToDelete);
    fflush(stdin);

    while (fread(&p, sizeof(pizza), 1, arq) == 1) {
        if (p.id == idToDelete) {
            // Exibe os detalhes da pizza antes de excluí-la
            printf("Pizza encontrada:\n");
            printf("Id: %d\n", p.id);
            printf("Nome: %s\n", p.nome);
            printf("Tamanho: %c\n", p.tamanho);
            printf("Valor: %.2f\n", p.preco);
            printf("Deseja deletar essa pizza? (s/n): ");
            if (getche() == 's') {
                printf("\nPizza deletada com sucesso.\n");
                continue;
            } else {
                fwrite(&p, sizeof(pizza), 1, temp);
            }
        } else {
            fwrite(&p, sizeof(pizza), 1, temp);
        }
    }

    fclose(arq);
    fclose(temp);

    // Apagar o arquivo original e renomear o temporário
    if (remove("pizzaria.txt") == 0 && rename("tmp.txt", "pizzaria.txt") == 0) {
        printf("\nOperação realizada com sucesso!\n");
    } else {
        remove("tmp.txt");
        printf("\nErro ao realizar a operação.\n");
    }
}

void editarPizza(void) {
    FILE *arq;
    FILE *temp;
    pizza p;
    system ("cls");
    cabecalho();

    int idToEdit;
    int encontrou = 0;

    arq = fopen("pizzaria.txt", "rb");
    temp = fopen("tmp.txt", "wb");

    if (arq == NULL || temp == NULL) {
        printf("Problemas na abertura do arquivo!\n");
        return;
    }

    printf("Digite o ID da pizza a editar: ");
    scanf("%d", &idToEdit);
    fflush(stdin);

    while (fread(&p, sizeof(pizza), 1, arq) == 1) {
        if (p.id == idToEdit) {
            encontrou = 1;

            // Exibe os detalhes da pizza antes de editá-la
            printf("\nPizza encontrada:\n");
            printf("Id: %d\n", p.id);
            printf("Nome: %s\n", p.nome);
            printf("Tamanho: %c\n", p.tamanho);
            printf("Valor: %.2f\n", p.preco);

            // Permitir edição
            printf("\nDigite os novos dados:\n");
            printf("Novo nome: ");
            fgets(p.nome, sizeof(p.nome), stdin);
            p.nome[strcspn(p.nome, "\n")] = 0; // Remove newline do fgets

            printf("Novo tamanho (P/M/G): ");
            scanf(" %c", &p.tamanho);
            fflush(stdin);

            printf("Novo valor: ");
            scanf("%f", &p.preco);
            fflush(stdin);

            printf("\nPizza editada com sucesso.\n");
        }

        fwrite(&p, sizeof(pizza), 1, temp);
    }

    fclose(arq);
    fclose(temp);

    if (!encontrou) {
        printf("\nPizza com ID %d não encontrada.\n", idToEdit);
        remove("tmp.txt");
    } else {
        // Apagar o arquivo original e renomear o temporário
        if (remove("pizzaria.txt") == 0 && rename("tmp.txt", "pizzaria.txt") == 0) {
            printf("\nOperação realizada com sucesso!\n");
        } else {
            remove("tmp.txt");
            printf("\nErro ao realizar a operação.\n");
        }
    }

    sleep (5);
    system ("cls");
}

void registrarVenda(void) {
    FILE *arquivo, *vendas;
    pizza p;
    int idVenda;
    int encontrada = 0;
    int adicionarIngredientes;
    int quantNovosIngredientes;
    char novoIngrediente[50];
    ingredientes ing;
    float totalVenda = 0.0;
    char ingredientesAdicionados[MAX_INGREDIENTES][50];  // Armazenar nomes dos ingredientes adicionados
    int countIngredientesAdicionados = 0;  // Contador de ingredientes adicionados

    system("cls");
    cabecalho();

    arquivo = fopen("pizzaria.txt", "rb");
    vendas = fopen("vendas.txt", "ab");

    if (arquivo == NULL || vendas == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    // Solicitar o ID da pizza que o cliente deseja comprar
    printf("Digite o ID da pizza para registrar a venda: ");
    scanf("%d", &idVenda);
    fflush(stdin);

    // Procurar a pizza no arquivo
    while (fread(&p, sizeof(pizza), 1, arquivo) == 1) {
        if (p.id == idVenda) {
            encontrada = 1;
            printf("\nPizza encontrada:\n");
            printf("ID: %d\n", p.id);
            printf("Nome: %s\n", p.nome);
            printf("Tamanho: %c\n", p.tamanho);
            printf("Valor base: %.2f\n", p.preco);

            // Perguntar se o cliente deseja adicionar novos ingredientes
            printf("\nDeseja adicionar novos ingredientes? (1 - Sim, 0 - Não): ");
            scanf("%d", &adicionarIngredientes);
            fflush(stdin);

            // Se o cliente deseja adicionar ingredientes, pedir os detalhes
            if (adicionarIngredientes == 1) {
                printf("Quantos novos ingredientes deseja adicionar? ");
                scanf("%d", &quantNovosIngredientes);
                getchar();

                // Garantir que não ultrapasse o limite de ingredientes
                if (quantNovosIngredientes > MAX_INGREDIENTES - 1) {  // -1 porque já existem ingredientes
                    printf("O número máximo de ingredientes é %d. Ajustando a quantidade.\n", MAX_INGREDIENTES);
                    quantNovosIngredientes = MAX_INGREDIENTES - 1;
                }

                // Adicionar novos ingredientes à pizza e atualizar o preço
                for (int i = 0; i < quantNovosIngredientes; i++) {
                    printf("\nDigite o nome do ingrediente %d: ", i + 1);
                    fgets(novoIngrediente, 50, stdin);
                    novoIngrediente[strcspn(novoIngrediente, "\n")] = '\0';  // Remove o '\n' do final da string

                    // Verificar se o ingrediente existe no arquivo de ingredientes
                    FILE *controle = fopen("ingredientes.txt", "rb");
                    int ingredienteEncontrado = 0;
                    while (fread(&ing, sizeof(ingredientes), 1, controle) == 1) {
                        if (strcmp(novoIngrediente, ing.nome) == 0) {
                            printf("Ingrediente %s encontrado e adicionado %.2f ao valor da pizza!\n", ing.nome, ing.preco);
                            // Adicionar o ingrediente à pizza
                            for (int j = 0; j < MAX_INGREDIENTES; j++) {
                                if (p.ingrediente[j].nome[0] == '\0') {
                                    strcpy(p.ingrediente[j].nome, ing.nome);
                                    p.ingrediente[j].id = ing.id;
                                    p.ingrediente[j].preco = ing.preco;
                                    p.preco += ing.preco; // soma o preco com o ingrediente adicionado
                                    strcpy(ingredientesAdicionados[countIngredientesAdicionados], ing.nome);
                                    countIngredientesAdicionados++;
                                    break;
                                }
                            }

                            ingredienteEncontrado = 1;
                            break;
                        }
                    }
                    fclose(controle);

                    if (!ingredienteEncontrado) {
                        printf("Ingrediente %s não encontrado no catálogo.\n", novoIngrediente);
                        i--;  // Permitir nova tentativa
                    }
                }
            }

            // Exibir os dados finais da pizza
            printf("\nPizza finalizada:\n");
            printf("Nome: %s\n", p.nome);

            // Exibir apenas os ingredientes que foram adicionados
            if (countIngredientesAdicionados > 0) {
                printf("Ingredientes adicionados:\n");
                for (int i = 0; i < countIngredientesAdicionados; i++) {
                    printf(" - %s\n", ingredientesAdicionados[i]);
                }
            } else {
                printf("Nenhum ingrediente adicional foi adicionado.\n");
            }

            printf("Novo preço total: %.2f\n", p.preco);


            // Confirmar a venda
            printf("\nDeseja registrar a venda dessa pizza? (s/n): ");
            if (getche() == 's') {
                fwrite(&p, sizeof(pizza), 1, vendas);
                printf("\nVenda registrada com sucesso!\n");
            } else {
                printf("\nVenda cancelada.\n");
            }
            break;
        }
    }

    if (!encontrada) {
        printf("Pizza não encontrada!\n");
    }

    fclose(arquivo);
    fclose(vendas);

    // Pausa para visualização
    sleep(5);
    system("cls");
}


// funcao para visualizar o historico de vendas

void readVendas() {
    system("cls");
    pizza p;
    FILE *vendas = fopen("vendas.txt", "rb");

    if (vendas == NULL) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    printf("\nHistórico de Vendas:\n");
    while (fread(&p, sizeof(pizza), 1, vendas) == 1) {
        printf("ID: %d\n", p.id);
        printf("Nome: %s\n", p.nome);
        printf("Tamanho: %c\n", p.tamanho);
        printf("Preço: R$ %.2f\n", p.preco);
        printf("Ingredientes: ");
        for (int i = 0; i < MAX_INGREDIENTES; i++) {
            if (p.ingrediente[i].nome[0] != '\0') {
                printf("%s (R$ %.2f) ", p.ingrediente[i].nome, p.ingrediente[i].preco);
            }
        }
        printf("\n-------------------------------\n");
    }

    fclose(vendas);
    sleep(5);
    system("cls");
}


float somaVendas (void){

    float total = 0;
    pizza p;
    FILE *vendas = fopen("vendas.txt", "rb");

    if (vendas == NULL) {
        return 0;
    }

    while (fread(&p, sizeof(pizza), 1, vendas) == 1) {
            total = total + p.preco;
}


    printf ("AEDS PIZZARIA\t Caixa: %.2f\n", total);
    fclose(vendas);
    return total;
}

void zeraFluxo (void){
    system("cls");
    cabecalho();
    printf("Deseja resetar o caixa e o historico de vendas? (s/n): ");
    if (getche() == 's') {
        FILE *vendas;
        vendas = fopen("vendas.txt", "wb");
        fclose(vendas);
    } else {
        return;
    }
}
