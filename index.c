#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int limiteClientes = 15, limiteProdutos = 15;

int numClientesCadastrados = 0;
int numProdutosCadastrados = 0;

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

// Funções Clientes

void cadastrarClientes(struct Clientes *cliente)
{
    printf("Cadastro de Clientes:\n");

    getchar(); // vai limpar o buffer do teclado
    printf("Digite o seu nome:\n");
    scanf("%49[^\n]", cliente->nome);

    printf("Digite o seu CPF:\n");
    scanf("%11s", cliente->cpf);

    printf("Digite o seu sexo (M/F):\n");
    scanf(" %c", &cliente->sexo);

    printf("Digite o seu telefone fixo:\n");
    scanf("%s", cliente->tel.fixo);

    printf("Digite o seu telefone movel:\n");
    scanf("%s", cliente->tel.movel);

    for (int i = 0; i < 6; i++)
    {
        cliente->id[i] = cliente->cpf[i];
    }
    cliente->id[6] = '\0';

    printf("\nCliente cadastrado com sucesso!\n");
}

// Listar Clientes

void listarClientes(struct Clientes cliente[limiteClientes], int qtd)
{

    if (qtd == 0)
    {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("\nLista de Clientes:\n");
    for (int i = 0; i < qtd; i++)
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

// Funções de produtos

int codigo_produto(const char *marca, const char *modelo);
void listarProdutos(struct produto *produtos, int numProdutosCadastrados);

void cadastrarProdutos(struct produto *produtos)
{
    printf("\n--- Cadastro de Produtos ---\n");

    printf("Digite a marca do produto: ");
    scanf("%29s", produtos->marca);

    printf("Digite o modelo do produto: ");
    scanf("%39s", produtos->modelo);

    printf("Digite o valor do produto: ");
    scanf("%f", &produtos->valor);

    produtos->codigo = codigo_produto(produtos->marca, produtos->modelo);

    printf("Código gerado: %d\n", produtos->codigo);

    printf("\n--- Produto Cadastrado com Sucesso ---\n");
}

int codigo_produto(const char *marca, const char *modelo)
{
    if (strlen(marca) < 2 || strlen(modelo) < 2)
    {
        return 0;
    }

    int C1 = (int)marca[0];
    int C2 = (int)marca[1];

    int C3 = (int)modelo[0];
    int C4 = (int)modelo[1];

    long long hash_ll = (long long)C1 * 31 * 31 * 31 +
                        (long long)C2 * 31 * 31 +
                        (long long)C3 * 31 +
                        (long long)C4;

    return (int)hash_ll;
}

void listarProdutos(struct produto *produtos, int numProdutosCadastrados)
{
    int i;

    printf("\n=======================================================\n");
    printf("                  LISTA DE PRODUTOS CADASTRADOS\n");
    printf("=======================================================\n");
    printf("| %-5s | %-10s | %-15s | %-8s | %-7s |\n", "ITEM", "MARCA", "MODELO", "VALOR", "HASH");
    printf("-------------------------------------------------------\n");

    for (i = 0; i < numProdutosCadastrados; i++)
    {
        printf("| %-5d | %-10s | %-15s | R$%-5.2f | %-7d |\n",
                i + 1,
                produtos[i].marca,
                produtos[i].modelo,
                produtos[i].valor,
                produtos[i].codigo);
    }
    printf("=======================================================\n");
}

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
            if (numClientesCadastrados < 10)
            {
                cadastrarClientes(&clientes[numClientesCadastrados]);
                numClientesCadastrados++;
            }
            else
            {
                printf("\nLimite de clientes atingido!\n");
            }
            main();
            break;
        case 2:
            listarClientes(clientes, numClientesCadastrados);
            main();
            break;
        case 3:
            cadastrarProdutos(&produtos[numProdutosCadastrados]);
            printf("\nNUMERO DE PRODUTOS CADASTRADOS ===> %d\n", numProdutosCadastrados);

            numProdutosCadastrados++;
            main();
            break;
        case 4:
            listarProdutos(produtos, numProdutosCadastrados);
            main();
            break;
        /* case 5:
            (produtos, numProdutosCadastrados);
            main();
            break; */
        case 6:
            printf("\nSaindo...\n");
            main();
            break;

        default:
            printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}