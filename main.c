#include <stdio.h>
#include <stdlib.h>
#include "pizza.h"
#include "ingredientes.h"
#include <locale.h>

int menu (void);

void cabecalho (void);

int main()
{
    setlocale (LC_ALL, "Portuguese");
    cabecalho();
    int opc = menu();

    while (opc != 0){

    if (opc == 1){
        readPizza();
        cabecalho();
        opc = menu ();
    }


    if (opc == 2){
        readIngredientes();
        cabecalho();
        opc = menu ();
    }

    if (opc == 3){
        createPizza();
        cabecalho();
        opc = menu ();
    }

    if (opc == 4){
        createIngredientes();
        cabecalho();
        opc = menu ();
    }

    if (opc == 5){
        removerPizza();
        cabecalho();
        opc = menu ();
    }

    if (opc == 6){
        removerIngredientes();
        cabecalho();
        opc = menu ();
    }

    if (opc == 7){
        editarPizza();
        cabecalho();
        opc = menu ();
    }

    if (opc == 8){
        editarIngredientes();
        cabecalho();
        opc = menu ();
    }

    if (opc == 9){
        registrarVenda();
        cabecalho();
        opc = menu ();
    }

    if(opc == 10){
        readVendas();
        cabecalho();
        opc = menu();
    }

    if(opc == 99){
        zeraFluxo();
        cabecalho();
        opc = menu();
    }


}
    if (opc == 0){
        printf ("\nMuito obrigado pela visita, encerrando o sistema em 3");
        sleep (1);
        printf (", 2");
        sleep (1);
        printf (", 1");
        sleep (1);
        printf ("\nAté a próxima!!\n\n");
        sleep (2);
    }

    return 0;
}


int menu (void){

    int opc;
    puts("Digite a opcao desejada\n");
    printf ("(1) - Listar todas as pizzas\n");
    printf ("(2) - Listar todos ingredientes\n");
    printf ("(3) - Cadastrar pizza\n");
    printf ("(4) - Cadastrar ingrediente\n");
    printf ("(5) - Deletar pizza\n");
    printf ("(6) - Deletar ingrediente\n");
    printf ("(7) - Editar pizza\n");
    printf ("(8) - Editar ingredientes\n");
    printf ("(9) - Registrar venda\n");
    printf ("(10)- Histórico de vendas\n");
    printf ("(0) - Sair do menu\n\n");
    printf ("(99) - Zerar fluxo de caixa\n\n");
    scanf ("%d", &opc);

    return opc;

}

void cabecalho (void){
    system ("cls");
    printf ("-------------------------------\n");
    printf ("", somaVendas());
    printf ("-------------------------------\n\n");
}
