#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int limiteClientes = 15, limiteProdutos = 15;

int numClientesCadastrados = 0, numProdutosCadastrados = 0;

/* Criação dos objetos para o programa */

struct Telefone
{
    char fixo[15];
    char movel[16];
};

struct Clientes
{
    char id[6];
    char nome[50];
    char cpf[12];
    char sexo;
    struct Telefone tel;
};

// Declarações Funções

//CLientes

struct Clientes cadastrarClientes(struct Clientes cliente);

// Função Principal

int main()
{
    setlocale(LC_ALL, "Portuguese");
    struct Clientes clientes[limiteClientes];

    int opcao;

    do
    {
        printf("\nMenu de Clientes:\n");
        printf("1) Cadastrar Cliente\n");
        printf("2) Listar Clientes\n");
        printf("3) Cadastrar Produtos\n");
        printf("4) Listar Produtos\n");
        printf("5) Carrinho de Compras\n");
        printf("6) Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            if (numClientesCadastrados < limiteClientes)
            {
                cadastrarClientes(clientes[numClientesCadastrados]);
            }
            else
            {
                printf("\nLimite de clientes atingido!\n");
            }
            break;
        case 2:
            // listarClientes(clientes);
            break;
        case 3:
            printf("\nSaindo...\n");
            return 0;

        default:
            printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}

struct Clientes cadastrarClientes(struct Clientes cliente)
{
    printf("\nCadastro de cliente:\n");

    getchar();

    printf("\nDigite o nome do cliente:\n");
    scanf("%49[^\n]", cliente.nome);    

    printf("\nDigite o CPF do cliente:\n");
    scanf("%s", cliente.cpf);

    printf("\nDigite o sexo (M/F) do cliente:\n");
    scanf(" %c", &cliente.sexo);

    printf("\nDigite o tefone fixo do cliente:\n");
    scanf("%s", cliente.tel.fixo);

    printf("\nDigite o telefone movel do cliente:\n");
    scanf("%s", cliente.tel.movel);

    for(int contadorDeCasasCPF = 0; contadorDeCasasCPF < 6; contadorDeCasasCPF++){
        cliente.id[contadorDeCasasCPF] = cliente.cpf[contadorDeCasasCPF];
    }
    cliente.id[6] = '\0';

    printf("\n=== Cadastro do Cliente com ID: %s realizado! \n", cliente.id);

    return cliente;
}


