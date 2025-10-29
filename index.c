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

struct Modelos
{
    char marca[20];
    char modelo[20];
};

struct produto
{
    int codigo;
    char marca[20];
    char modelo[40];
    float valor;
};

struct Carrinho
{
    struct Clientes cliente;
    struct produto prod[3];
    int quantidade[3];
    double subtotal;
    double desconto;
    double total;
};

// Declarações Funções

//CLientes

void cadastrarClientes(struct Clientes c);

void listarClientes(struct Clientes cliente[]);

// Funções de produtos

int codigo_produto(const char *marca, const char *modelo);

void listarProdutos(struct produto *produtos, int numProdutosCadastrados);

void cadastrarProdutos(struct produto *produtos);

// Função Principal

int main()
{
    setlocale(LC_ALL, "Portuguese");
    struct Clientes clientes[limiteClientes];
    struct produto produtos[limiteProdutos];

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
            listarClientes(clientes);
            break;
        case 3:
            cadastrarProdutos(&produtos[numProdutosCadastrados]);
            break;
        case 4:
            listarProdutos(produtos, numProdutosCadastrados);
            break;
        /* case 5:
            (produtos, numProdutosCadastrados);
            break; */
        case 6:
            printf("\nSaindo...\n");
            return 0;

        default:
            printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}

void cadastrarClientes(struct Clientes c)
{

    printf("Cadastro de Clientes:\n");
    
    getchar();

    printf("Digite o seu nome:\n");
    scanf("%s", c.nome);

    printf("Digite o seu CPF:\n");
    scanf("%11s", c.cpf);

    printf("Digite o seu sexo (M/F):\n");
    scanf(" %c", &c.sexo);

    printf("Digite o seu telefone fixo:\n");
    scanf("%s", c.tel.fixo);

    printf("Digite o seu telefone movel:\n");
    scanf("%s", c.tel.movel);

    for (int i = 0; i < 6; i++)
    {
        c.id[i] = c.cpf[i];
    }
    c.id[6] = '\0';

    numClientesCadastrados++;
    printf("\nCliente cadastrado com sucesso!\n");
}

void listarClientes(struct Clientes cliente[])
{

    if (numClientesCadastrados == 0)
    {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("\nLista de Clientes:\n");
    for (int i = 0; i < numClientesCadastrados; i++)
    {

        printf("\n Cliente %d:\n", i + 1);
        printf("ID: %s\n", cliente[i].id);
        printf("Nome: %s\n", cliente[i].nome);
        printf("CPF: %s\n", cliente[i].cpf);
        printf("Sexo: %c\n", cliente[i].sexo);
        printf("Telefone Fixo: %s\n", cliente[i].tel.fixo);
        printf("Telefone Movel: %s\n", cliente[i].tel.movel);
    }
}