//detective quest aventureiro

//obs. eu não tenho mais acesso ao conteudo do curso, estou fazendo com base nas informações que tem nesse arquivo...

//bloqueram tudo, até o app não entra mais
//Application error: a client-side exception has occurred (see the browser console for more information).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10   // Tamanho da tabela hash

// struct pistas
struct PistaNodo {
    char texto[100];
    struct PistaNodo *prox;
};


// Estrutura do suspeito (cada posição da hash)

struct Suspeito {
    char nome[50];
    int contador;                // quantas pistas associadas
    struct PistaNodo *pistas;    // lista encadeada de pistas
    struct Suspeito *prox;       // colisões (encadeamento externo)
};

// Tabela hash
struct Suspeito* tabela[TAM];


// Função hash simples (soma ASCII do nome mod TAM)

int hash(char nome[]) {
    int soma = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        soma += nome[i];
    }
    return soma % TAM;
}


// Inicializa hash com NULLs

void inicializarHash() {
    for (int i = 0; i < TAM; i++) {
        tabela[i] = NULL;
    }
}

// Cria estrutura de suspeito

struct Suspeito* criarSuspeito(char nome[]) {
    struct Suspeito *s = (struct Suspeito*)malloc(sizeof(struct Suspeito));
    strcpy(s->nome, nome);
    s->contador = 0;
    s->pistas = NULL;
    s->prox = NULL;
    return s;
}


// Busca suspeito na tabela hash (com colisões)

struct Suspeito* buscarSuspeito(char nome[]) {
    int idx = hash(nome);
    struct Suspeito *atual = tabela[idx];

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual;
        }
        atual = atual->prox;
    }

    return NULL; // não encontrado
}

// Insere pista dentro da lista deste suspeito

void adicionarPistaAoSuspeito(struct Suspeito *suspeito, char texto[]) {
    struct PistaNodo *novo = (struct PistaNodo*)malloc(sizeof(struct PistaNodo));
    strcpy(novo->texto, texto);
    novo->prox = suspeito->pistas;
    suspeito->pistas = novo;

    suspeito->contador++; // incrementa quantidade
}

// Insere relação (suspeito + pista)

void inserirHash(char nomeSuspeito[], char pista[]) {
    int idx = hash(nomeSuspeito);

    // Procura se já existe
    struct Suspeito *s = buscarSuspeito(nomeSuspeito);

    // Não existe → criar
    if (s == NULL) {
        s = criarSuspeito(nomeSuspeito);
        s->prox = tabela[idx];     // encadeamento em caso de colisão
        tabela[idx] = s;
    }

    // Adiciona pista ao suspeito
    adicionarPistaAoSuspeito(s, pista);
}


// Exibe todos os suspeitos e suas pistas

void listarAssociacoes() {
    printf("\n===== SUSPEITOS E SUAS PISTAS =====\n");

    for (int i = 0; i < TAM; i++) {
        struct Suspeito *s = tabela[i];

        while (s != NULL) {
            printf("\nSuspeito: %s\n", s->nome);
            printf("Citações: %d\n", s->contador);
            printf("Pistas:\n");

            struct PistaNodo *p = s->pistas;
            while (p != NULL) {
                printf(" - %s\n", p->texto);
                p = p->prox;
            }

            s = s->prox; // prossiga na lista de colisão
        }
    }
}

// Determina o suspeito mais provável

void suspeitoMaisProvavel() {
    struct Suspeito *mais = NULL;

    for (int i = 0; i < TAM; i++) {
        struct Suspeito *s = tabela[i];

        while (s != NULL) {
            if (mais == NULL || s->contador > mais->contador) {
                mais = s;
            }
            s = s->prox;
        }
    }

    printf("\n===== SUSPEITO MAIS PROVÁVEL =====\n");

    if (mais == NULL) {
        printf("Nenhum suspeito registrado.\n");
        return;
    }

    printf("Suspeito: %s\n", mais->nome);
    printf("Citações: %d\n", mais->contador);
}


// MAIN (exemplo de uso)

int main() {

    inicializarHash();

    // Exemplos de pistas coletadas
    inserirHash("Sr. Corvino", "Pegadas de barro");
    inserirHash("Dona Mirela", "Copo quebrado");
    inserirHash("Sr. Corvino", "Chave enferrujada");
    inserirHash("Dona Mirela", "Página rasgada");
    inserirHash("Sombra Alta", "Som metálico no porão");
    inserirHash("Sr. Corvino", "Diário rasgado");

    listarAssociacoes();
    suspeitoMaisProvavel();

    return 0;
}
