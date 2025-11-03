#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

#define limiteProdutosCarrinho 15
#define limiteClientes 15
#define limiteProdutos 15
#define limiteDeCarrinhosCadastrados 15

int numClientesCadastrados = 0, numProdutosCadastrados = 0, numCarrinhosCadastrados = 0;

/* Criação dos objetos para o programa */

struct Telefone
{
    char fixo[15];
    char movel[16];
};

struct Clientes
{
    char id[7];
    char nome[50];
    char cpf[12];
    char sexo;
    struct Telefone tel;
};

struct Produtos
{
    int id;
    char marca[20];
    char modelo[50];
    double valor;
};

struct Carrinho
{
    struct Clientes cliente;
    struct Produtos produto[limiteProdutosCarrinho];
    int quantidadeProdutos[limiteProdutosCarrinho];
    double subtotal;
    char formaDePagamento;
    double descontoPagamento;
    double descontoCupom;
    double totalCompra;
};

// Declaração de array em escopo global

struct Clientes clientes[limiteClientes];
struct Produtos produto[limiteProdutos];
struct Carrinho carrinho[limiteDeCarrinhosCadastrados];

// Declarações Funções

// Clientes

struct Clientes cadastrarClientes(struct Clientes cliente);

void listarClientes(struct Clientes cliente[]);

// Produtos

int criarCodigoProduto(char *marca, char *modelo, int *id);

struct Produtos cadastrarProdutos(struct Produtos produto);

void listarProdutos(struct Produtos produto[]);

// Carrinho

struct Carrinho cadastrarCarrinho(struct Carrinho carrinho);

double valorCompraSubtotal(struct Produtos produto, int quantidadeProdutos);

double valorCompraTotal(struct Produtos produto, int quantidadeProdutos);

double calculoDeDescontoPagamento(struct Carrinho carrinho);

double calculoDeDescontoCupom(struct Carrinho carrinho);

// Função Principal

int main()
{
    setlocale(LC_ALL, "Portuguese");
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

        getchar();

        switch (opcao)
        {
        case 1:
            if (numClientesCadastrados < limiteClientes)
            {
                clientes[numClientesCadastrados] = cadastrarClientes(clientes[numClientesCadastrados]);
                numClientesCadastrados++;
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
            (numProdutosCadastrados < limiteProdutos)
                ? (produto[numProdutosCadastrados] = cadastrarProdutos(produto[numProdutosCadastrados]), numProdutosCadastrados++)
                : printf("\n=== Limite de produtos atingido! ===\n");

            break;

        case 4:
            listarProdutos(produto);

            break;

        case 5:
            cadastrarCarrinho(carrinho[numCarrinhosCadastrados]);

            break;

        case 6:
            printf("\nSaindo...\n");
            return 0;

        default:
            printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}
// Funções Clientes

struct Clientes cadastrarClientes(struct Clientes cliente)
{
    printf("\nCadastro de cliente:\n");

    printf("\nDigite o nome do cliente:\n");
    fgets(cliente.nome, sizeof(cliente.nome), stdin);

    size_t tamanhoNome = strlen(cliente.nome);

    if ((tamanhoNome > 0) && (cliente.nome[tamanhoNome - 1] == '\n'))
    {
        cliente.nome[tamanhoNome - 1] = '\0';
    }

    printf("\nDigite o CPF do cliente:\n");
    scanf("%s", cliente.cpf);

    printf("\nDigite o sexo (M/F) do cliente:\n");
    scanf(" %c", &cliente.sexo);

    printf("\nDigite o tefone fixo do cliente:\n");
    scanf("%s", cliente.tel.fixo);

    printf("\nDigite o telefone movel do cliente:\n");
    scanf("%s", cliente.tel.movel);

    for (int contadorDeCasasCPF = 0; contadorDeCasasCPF < 7; contadorDeCasasCPF++)
    {
        cliente.id[contadorDeCasasCPF] = cliente.cpf[contadorDeCasasCPF];
    }

    cliente.id[6] = '\0';

    printf("\n=== Cadastro do Cliente com ID: %s realizado! ===\n\n", cliente.id);

    return cliente;
}

void listarClientes(struct Clientes cliente[])
{
    int contadorClientes = 0;

    printf("\n=== Listagem de Clientes Cadastrados ===\n");

    for (contadorClientes = 0; contadorClientes < numClientesCadastrados; contadorClientes++)
    {
        printf("ID: %s\n", cliente[contadorClientes].id);
        printf("Nome: %s\n", cliente[contadorClientes].nome);
        printf("CPF: %s\n", cliente[contadorClientes].cpf);
        printf("Sexo (M/F): %c\n", cliente[contadorClientes].sexo);
        printf("Telefone Fixo: %s\n", cliente[contadorClientes].tel.fixo);
        printf("Telefone Movel: %s\n", cliente[contadorClientes].tel.movel);

        printf("\n==============\n");
    }

    printf("\n=== Contamos com %d usuarios cadastrados na nossa base ===\n", numClientesCadastrados);
}

// Funções Produtos

int criarCodigoProduto(char *marca, char *modelo, int *id)
{
    *id = (int)(

        (long)marca[0] * 31 * 31 * 31 +
        (long)marca[1] * 31 * 31 +
        (long)modelo[0] * 31 +
        (long)modelo[1] * 1

    );

    return *id;
}

struct Produtos cadastrarProdutos(struct Produtos produto)
{

    printf("\n\n=== Cadastro de Produtos ===\n");

    printf("Digite a marca do produto: ");
    scanf(" %[^\n]", produto.marca);

    printf("Digite o modelo do produto: ");
    scanf(" %[^\n]", produto.modelo);

    printf("Digite o valor do produto: R$");
    scanf("%lf", &produto.valor);

    produto.id = criarCodigoProduto(produto.marca, produto.modelo, &produto.id);

    printf("\n=== Cadastro do Produto com ID: %d realizado! ===\n\n", produto.id);

    return produto;
}

void listarProdutos(struct Produtos produto[])
{

    int contadorDeProdutos = 0;

    printf("\n\n=== Listagem de Produtos Cadastrados ===\n\n");

    for (contadorDeProdutos = 0; contadorDeProdutos < numProdutosCadastrados; contadorDeProdutos++)
    {
        printf("ID: %d\n", produto[contadorDeProdutos].id);
        printf("Marca: %s\n", produto[contadorDeProdutos].marca);
        printf("Modelo: %s\n", produto[contadorDeProdutos].modelo);
        printf("Valor: R$%.2f\n", produto[contadorDeProdutos].valor);

        printf("\n==============\n");
    }

    printf("\n=== Contamos com %d produtos cadastrados na nossa base ===\n\n", numProdutosCadastrados);
}

struct Carrinho cadastrarCarrinho(struct Carrinho carrinho)
{

    char clienteSelecionado[7];
    int produtoSelecionado;

    bool usuarioEncontrado = false;
    char pararEscolhaProdutos;

    printf("\n=== Carrinho de Compras ===\n");

    do
    {
        printf("\nSelecione um cliente pelo seu ID:\n");
        listarClientes(clientes);
        printf("\nDigite: ");
        scanf(" %[^\n]", clienteSelecionado);

        for (int identificadorDeCliente = 0; identificadorDeCliente < numClientesCadastrados; identificadorDeCliente++)
        {
            if (strcmp(clienteSelecionado, clientes[identificadorDeCliente].id) == 0)
            {
                strcpy(carrinho.cliente.id, clientes[identificadorDeCliente].id);
                strcpy(carrinho.cliente.nome, clientes[identificadorDeCliente].nome);
                usuarioEncontrado = true;
            }
        }

        if (carrinho.cliente.id[0] == '\0')
        {
            printf("\n=== Usuario Invalido! ===\n");
        }
    } while (usuarioEncontrado != true);

    printf("\n\n=== Selecione até %d produtos ===\n\n", limiteProdutosCarrinho);
    
    do{
        int numProdutosNoCarrinho = 0;
        bool pesquisaDeProdutos = false;
        do{

            listarProdutos(produto);
            printf("Escolha o produto pelo seu ID que quer adicionar ao seu carrinho : ");
            scanf("%d", &produtoSelecionado);

            for(int identificadorDeProdutos = 0; identificadorDeProdutos < numProdutosCadastrados; identificadorDeProdutos++){
                if(produtoSelecionado == produto[identificadorDeProdutos].id){
                    carrinho.produto[numProdutosNoCarrinho].id = produto[identificadorDeProdutos].id;
                    numProdutosNoCarrinho++;
                    pesquisaDeProdutos = true;
                }
            }
        }while(pesquisaDeProdutos != true);

        printf("\n\nDeseja adicionar mais produtos ao seu carrinho: Sim (S) / Não (N)\n");
        scanf("%c", &pararEscolhaProdutos);
    }while((pararEscolhaProdutos != 'N') || (pararEscolhaProdutos != 'n'));
    
    return carrinho;
}

/* struct Carrinho
{
    struct Clientes cliente;
    struct Produtos produto[limiteProdutosCarrinho];
    int quantidadeProdutos[limiteProdutosCarrinho];
    double subtotal;
    char formaDePagamento;
    double descontoPagamento;
    double descontoCupom;
    double totalCompra
}; */