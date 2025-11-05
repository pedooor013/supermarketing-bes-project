#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>

#define limiteProdutosCarrinho 15
#define limiteClientes 15
#define limiteProdutos 15
#define limiteDeCarrinhosCadastrados 15

int numClientesCadastrados = 0, numProdutosCadastrados = 0, numCarrinhosCadastrados = 0;

//Pix copia e cola e codigo de boleto FALSOS

char *codigoBoleto[] = {
    "00190000090123456789000000000012345670000000",
    "03399000090098765432000000000045678910000000",
    "10490000090111122233300000000078901230000000",
    "23790000090222233344400000000089012340000000",
    "34191000090333344455500000000090123450000000",
    "39991000090444455566600000000001234560000000",
    "42291000090555566677700000000012345670000000",
    "74890000090666677788800000000023456780000000",
    "10491000090777788899900000000034567890000000",
    "23791000090888899900000000045678900000000",
    "34192000090999900011100000000056789010000000",
    "03391000091011122233300000000067890120000000",
    "00192000091122233344400000000078901230000000",
    "39992000091233344455500000000089012340000000",
    "42292000091344455566600000000090123450000000"
};

char *pixCopiaCola[] = {
    "2025-11-05:01:Ab3kG9xY2MnQ4pR7sT1Z",
    "2025-11-05:02:Zt4Lf8QwK1rPo9Sx3YbC",
    "2025-11-05:03:Hn7Vm2QpLs9Xc4Tb8Jo",
    "2025-11-05:04:K4dPq9ZxR2sVb6Nm7Uy",
    "2025-11-05:05:Yt3Wq8HpL0zXc5Mn2Rf",
    "2025-11-05:06:Bc9Gt1VxP4kLz7Qw3Se",
    "2025-11-05:07:Mz6Qw2NvL8rTp5Xs1Ha",
    "2025-11-05:08:Rv1Kp9SzX4mQ7Lh3TwB",
    "2025-11-05:09:Jq8Ln3VzP5sWy2Rx0Km",
    "2025-11-05:10:Uf2Tx9QwL6zPr3Sv1Nb",
    "2025-11-05:11:Cb7Lp4QzR1sNv8Xm2Yk",
    "2025-11-05:12:Dx3Qw9VkL5rTp2Sz7Ha",
    "2025-11-05:13:Ns6Pr2QwX8zLm1Tv4Kb",
    "2025-11-05:14:Pq4Vz9LmR2sXk7Tb1Hy",
    "2025-11-05:15:Sz1Qw8RpL6nVx3Tm9Kb"
};


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
    double valorParcela;
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

    //CLIENTES TESTE
        // --- DADOS DE TESTE ---
    // Clientes de modelo (id com 6 chars + '\\0')
    strcpy(clientes[0].id, "111111");
    strcpy(clientes[0].nome, "Ana Silva");
    strcpy(clientes[0].cpf, "11111111111");
    clientes[0].sexo = 'F';
    strcpy(clientes[0].tel.fixo, "11223344");
    strcpy(clientes[0].tel.movel, "11999999999");

    strcpy(clientes[1].id, "222222");
    strcpy(clientes[1].nome, "Bruno Costa");
    strcpy(clientes[1].cpf, "22222222222");
    clientes[1].sexo = 'M';
    strcpy(clientes[1].tel.fixo, "22334455");
    strcpy(clientes[1].tel.movel, "11988888888");

    strcpy(clientes[2].id, "333333");
    strcpy(clientes[2].nome, "Carla Souza");
    strcpy(clientes[2].cpf, "33333333333");
    clientes[2].sexo = 'F';
    strcpy(clientes[2].tel.fixo, "33445566");
    strcpy(clientes[2].tel.movel, "11977777777");

    strcpy(clientes[3].id, "444444");
    strcpy(clientes[3].nome, "Daniel Oliveira");
    strcpy(clientes[3].cpf, "44444444444");
    clientes[3].sexo = 'M';
    strcpy(clientes[3].tel.fixo, "44556677");
    strcpy(clientes[3].tel.movel, "11966666666");

    strcpy(clientes[4].id, "555555");
    strcpy(clientes[4].nome, "Eduarda Lima");
    strcpy(clientes[4].cpf, "55555555555");
    clientes[4].sexo = 'F';
    strcpy(clientes[4].tel.fixo, "55667788");
    strcpy(clientes[4].tel.movel, "11955555555");

    numClientesCadastrados = 5;

    // Produtos de modelo — ID gerado pelo criarCodigoProduto()
    strcpy(produto[0].marca, "Samsung");
    strcpy(produto[0].modelo, "Galaxy S21");
    produto[0].valor = 3500.00;
    criarCodigoProduto(produto[0].marca, produto[0].modelo, &produto[0].id);

    strcpy(produto[1].marca, "Apple");
    strcpy(produto[1].modelo, "iPhone 14");
    produto[1].valor = 5000.00;
    criarCodigoProduto(produto[1].marca, produto[1].modelo, &produto[1].id);

    strcpy(produto[2].marca, "Dell");
    strcpy(produto[2].modelo, "Inspiron 15");
    produto[2].valor = 4200.00;
    criarCodigoProduto(produto[2].marca, produto[2].modelo, &produto[2].id);

    strcpy(produto[3].marca, "Logitech");
    strcpy(produto[3].modelo, "MX Master 3S");
    produto[3].valor = 550.00;
    criarCodigoProduto(produto[3].marca, produto[3].modelo, &produto[3].id);

    strcpy(produto[4].marca, "Sony");
    strcpy(produto[4].modelo, "WH-1000XM5");
    produto[4].valor = 2100.00;
    criarCodigoProduto(produto[4].marca, produto[4].modelo, &produto[4].id);

    numProdutosCadastrados = 5;


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
    
    int numProdutosNoCarrinho = 0;
    bool pesquisaDeProdutos = false;
    
    do{
    
        do{

            listarProdutos(produto);
            printf("Escolha o produto pelo seu ID que quer adicionar ao seu carrinho : ");
            scanf("%d", &produtoSelecionado);

            for(int identificadorDeProdutos = 0; identificadorDeProdutos < numProdutosCadastrados; identificadorDeProdutos++){
                if(produtoSelecionado == produto[identificadorDeProdutos].id){
                    carrinho.produto[numProdutosNoCarrinho] = produto[identificadorDeProdutos];
                    numProdutosNoCarrinho++;
                    pesquisaDeProdutos = true;
                }
            }
        }while(pesquisaDeProdutos != true);

        printf("\n\nDeseja adicionar mais produtos ao seu carrinho: Sim (S) / Não (N)\n");
        scanf(" %c", &pararEscolhaProdutos);
        pararEscolhaProdutos = toupper(pararEscolhaProdutos);
    }while(pararEscolhaProdutos != 'N');

    carrinho.subtotal = 0;
    
    printf("\n\n=== Produtos Cadastrados no Carrinho ===\n\n");
    for(int contadorDeProdutos = 0; contadorDeProdutos < numProdutosNoCarrinho; contadorDeProdutos++){
        printf("ID: %d\n", carrinho.produto[contadorDeProdutos].id);
        printf("Marca: %s\n", carrinho.produto[contadorDeProdutos].marca);
        printf("Modelo: %s\n", carrinho.produto[contadorDeProdutos].modelo);
        printf("Valor: R$%.2f\n", carrinho.produto[contadorDeProdutos].valor);

        printf("\n==============\n\n");

        carrinho.subtotal = carrinho.subtotal + carrinho.produto[contadorDeProdutos].valor;
    }

    printf("\n\nPreço da compra: R$%.2lf\n", carrinho.subtotal);

    //APLICAR AQUI O CODIGO DO CUPOM

    char escolhaPagamento;

    printf("\n\nEscolha o metodo de pagamento: \nAté 10x no credito com juros (C);\nAté 6x no boleto sem juros (B);\nPix a vista com 10%% de desconto (P);\nDigite: ");
    scanf(" %c", &escolhaPagamento);
    escolhaPagamento = toupper(escolhaPagamento);
    
    printf("\n==============\n\n");
    
    int quantidadeDeParcelas;
    
    if(escolhaPagamento == 'C'){
        do{
            printf("\n\nEm quantas vezes você deseja pagar: \nAté 3x sem juros;\nAté 6x juros de 5%%;\nAté 8x juros de 10%%;\nAté 10x 15%% de juros;\n\nDigite:");
            scanf("%d", &quantidadeDeParcelas);
        }while((quantidadeDeParcelas > 10) || (quantidadeDeParcelas <= 0));
        
        if(quantidadeDeParcelas >= 9){
            carrinho.totalCompra = ((carrinho.subtotal * 15) / 100) + carrinho.subtotal;
        }else if(quantidadeDeParcelas >= 7){
            carrinho.totalCompra = ((carrinho.subtotal * 10) / 100) + carrinho.subtotal;
        }else if(quantidadeDeParcelas >= 4){
            carrinho.totalCompra = ((carrinho.subtotal * 5) / 100) + carrinho.subtotal;
        }else{
            carrinho.totalCompra = carrinho.subtotal;
        }
        carrinho.valorParcela = (carrinho.totalCompra / quantidadeDeParcelas);
        printf("\nValor final da compra: R$%.2lf;\nValor de cada parcela: R$%.2lf", carrinho.totalCompra, carrinho.valorParcela);
    }else if(escolhaPagamento == 'B'){
        
        do{
            printf("\n\nEm quantas vezes você deseja pagar:\nDigite:");
            scanf("%d", &quantidadeDeParcelas);
        }while((quantidadeDeParcelas > 6) || (quantidadeDeParcelas <= 0));

        carrinho.totalCompra = carrinho.subtotal;
        carrinho.valorParcela = carrinho.totalCompra / quantidadeDeParcelas;
        
        printf("\nValor final da compra: R$%.2lf;\nValor de cada parcela: R$%.2lf;", carrinho.totalCompra, carrinho.valorParcela);
        
        int numArrayBoleto = rand() % 15;

        printf("\n\nCodigo de boleto gerado: %s\n\n", codigoBoleto[numArrayBoleto]);

    }else if(escolhaPagamento == 'P'){
        carrinho.totalCompra = (carrinho.subtotal - ((carrinho.subtotal * 10) / 100));
        printf("\nValor final da compra: R$%.2lf;", carrinho.totalCompra);

        int numArrayPix = rand() % 15; 

        printf("\n\nPix copia e cola gerado: %s\n\n", pixCopiaCola[numArrayPix]);
    }
    
    
    return carrinho;
}

// struct Produtos
// {
//     int id;
//     char marca[20];
//     char modelo[50];
//     double valor;
// };

// struct Carrinho
// {
//     struct Clientes cliente;
//     struct Produtos produto[limiteProdutosCarrinho];
//     int quantidadeProdutos[limiteProdutosCarrinho];
//     double subtotal;
//     double valorParcela;
//     char formaDePagamento;
//     double descontoPagamento;
//     double descontoCupom;
//     double totalCompra;
// };
