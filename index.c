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

// Funções Clientes

//Função Principal
int main(){
}

