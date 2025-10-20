#include <stdio.h>

/* Criação dos objetos para o programa */

struct Clientes{
    int id;
    char nome[50];
    double cpf;
    char sexo;
    struct Telefone tel;
};

struct Telefone{
    char fixo[15];
    char movel[16];
};

struct Produtos{
    int id;
    char nome[20];
    struct Modelos models;
    double valor;
};

struct Modelos{
    char marca[20];
    char modelo[20];
};

struct Carrinho{
    struct Clientes cliente;
    struct Produtos produto[3];
    int quantidade[3];
    double subtotal;
    double desconto;
    double total;
};

//Função Principal
int main(){
    int escolhaUsuario;
    printf("Escolha qual tarefa você deseja fazer:\n\t01) Cadastrar um cliente;\n\t02) Listar clientes;\n\t03) Cadastrar produtos;\n\t04) Listar produtos;\n\t05) Realizar uma compra;\n\t06) Sair;\n");
    scanf("%d", &escolhaUsuario);

    switch(escolhaUsuario){
        case 1:
            cadastrarClientes();
            break;
        case 2:
            listarClientes();
            break;
        case 3:
            cadastrarProdutos();
            break;
        case 4:
            listarProdutos();
            break;
        case 5:
            realizarCompra();
            break;
        case 6:
            printf("\nSaindo...");
            return 0;
        default:
            printf("\nDigite um valor valido...");
            main();   
    }
}

