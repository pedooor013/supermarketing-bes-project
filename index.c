#include <stdio.h>
#include <string.h>
#include <locale.h>

/* Criação dos objetos para o programa */


struct Telefone{
    char fixo[15];
    char movel[16];
};

struct Clientes{
    char id[6];
    char nome[50];
    char cpf[12];
    char sexo;
    struct Telefone tel;
};
/* 

struct Modelos{
    char marca[20];
    char modelo[20];
};


struct Produtos{
    int id;
    char nome[20];
    struct Modelos models;
    double valor;
};
struct Carrinho{
    struct Clientes cliente;
    struct Produtos produto[3];
    int quantidade[3];
    double subtotal;
    double desconto;
    double total;
};
 */
// Funções Clientes

void cadastrarClientes(struct Clientes *cliente){
    printf("Cadastro de Clientes:\n");

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

    for(int i = 0; i < 6; i++){
        cliente -> id[i] = cliente -> cpf[i];
    }
    cliente->id[6] = '\0';

    printf("\nCliente cadastrado com sucesso!\n");
}

 // Listar Clientes 

 void listarClientes(struct Clientes cliente[], int qtd){

    if (qtd == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    for(int i = 0; i < qtd; i++){
        printf("\n Cliente %d:\n", i + 1);
        printf("ID: %s\n", cliente[i].id);
        printf("Nome: %s\n", cliente[i].nome);
        printf("CPF: %s\n", cliente[i].cpf);
        printf("Sexo: %c\n", cliente[i].sexo);
        printf("Telefone Fixo: %s\n", cliente[i].tel.fixo);
        printf("Telefone Movel: %s\n", cliente[i].tel.movel);
    }

 }

//Função Principal
int main(){
    setlocale(LC_ALL, "Portuguese");
    int escolhaUsuario, contagemDeUsuarios = 0;
    struct Clientes cliente[10];
    printf("Escolha qual tarefa você deseja fazer:\n\t01) Cadastrar um cliente;\n\t02) Listar clientes;\n\t03) Cadastrar produtos;\n\t04) Listar produtos;\n\t05) Rewalizar uma compra;\n\t06) Sair;\n");
    scanf("%d", &escolhaUsuario);

    switch(escolhaUsuario){
        case 1:
            cadastrarClientes(cliente[contagemDeUsuarios]);
            printf("\nCadastro realizado:\nID: %s\nNome: %s\nCPF: %s\nSexo: %c\nTelefone Fixo: %s\nTelefone Movel: %s", cliente[contagemDeUsuarios].id, cliente[contagemDeUsuarios].nome, cliente[contagemDeUsuarios].cpf, cliente[contagemDeUsuarios].sexo, cliente[contagemDeUsuarios].tel.fixo, cliente[contagemDeUsuarios].tel.movel);
            contagemDeUsuarios++;
            main();
            break;
        case 2:
            // listarClientes();
            break;
        case 3:
            // cadastrarProdutos();
            break;
        case 4:
            // listarProdutos();
            break;
        case 5:
            // realizarCompra();
            break;
        case 6:
            printf("\nSaindo...");
            return 0;
        default:
            printf("\nDigite um valor valido...");
            main();   
    }return 0;
}

