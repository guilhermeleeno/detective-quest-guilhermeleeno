//detective nivel novato

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Struct da sala
struct Sala {
    char nome[50];
    struct Sala *esq;
    struct Sala *dir;
};

// Criando a Sala
struct Sala* criarSala(char nome[]) {
    struct Sala *nova = (struct Sala*)malloc(sizeof(struct Sala));
    strcpy(nova->nome, nome);
    nova->esq = NULL;
    nova->dir = NULL;
    return nova;
}

//Explorando
void explorar(struct Sala *atual) {
    if (atual == NULL) return;

    char opcao;

    while (1) {
        printf("\n📍 Você está na sala: %s\n", atual->nome);
        printf("Mover:\n");
        printf("  (e) Ir para sala à esquerda\n");
        printf("  (d) Ir para sala à direita\n");
        printf("  (s) Sair da mansão\n");
        printf("Escolha: ");
        scanf(" %c", &opcao);

        if (opcao == 's') {
            printf("\nVocê decidiu sair da mansão...\n");
            return;
        }

        if (opcao == 'e') {
            if (atual->esq != NULL) {
                atual = atual->esq;
            } else {
                printf("Não existe sala à esquerda!\n");
            }
        } else if (opcao == 'd') {
            if (atual->dir != NULL) {
                atual = atual->dir;
            } else {
                printf("Não existe sala à direita!\n");
            }
        } else {
            printf("Opção inválida!\n");
        }
    }
}

//Aplicando no main
int main() {

//Criando as salas fixas (árvore pronta)
    struct Sala *hall        = criarSala("Hall de Entrada");
    struct Sala *biblioteca  = criarSala("Biblioteca");
    struct Sala *cozinha     = criarSala("Cozinha");
    struct Sala *salaJantar  = criarSala("Sala de Jantar");
    struct Sala *sotao       = criarSala("Sótão");
    struct Sala *porao       = criarSala("Porão");

    //desenho de como ficou a estutura da arvore
    /*
            Hall
           /    \
     Biblioteca  Cozinha
        /  \      /   \
   Sótão  Porão  Sala Jantar  (NULL)
    */

    hall->esq = biblioteca;
    hall->dir = cozinha;

    biblioteca->esq = sotao;
    biblioteca->dir = porao;

    cozinha->esq = salaJantar;

    // Começa a exploração
    explorar(hall);

    return 0;
}
