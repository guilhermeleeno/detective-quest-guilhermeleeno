//detective quest aventureiro

//obs. eu não tenho mais acesso ao conteudo do curso, estou fazendo com base nas informações que tem nesse arquivo...

//bloqueram tudo, até o app não entra mais
//Application error: a client-side exception has occurred (see the browser console for more information).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct da pista
struct Pista {
    char texto[100];
    struct Pista *esq;
    struct Pista *dir;
};

// criar uma pista
struct Pista* novaPista(char texto[]) {
    struct Pista *p = (struct Pista*)malloc(sizeof(struct Pista));
    strcpy(p->texto, texto);
    p->esq = NULL;
    p->dir = NULL;
    return p;
}

// insere bts ordem alfabética
struct Pista* inserirPista(struct Pista *raiz, char texto[]) {
    if (raiz == NULL) {
        return novaPista(texto);
    }

    if (strcmp(texto, raiz->texto) < 0) {
        raiz->esq = inserirPista(raiz->esq, texto);
    } else {
        raiz->dir = inserirPista(raiz->dir, texto);
    }

    return raiz;
}

// exibe as pistas em ordem alfabética

void listarPistas(struct Pista *raiz) {
    if (raiz == NULL) return;

    listarPistas(raiz->esq);
    printf(" - %s\n", raiz->texto);
    listarPistas(raiz->dir);
}

// esquema de exploração com as pistas
struct Sala {
    char nome[50];
    struct Sala *esq;
    struct Sala *dir;
    char pistaSala[100];  // pista associada à sala
};

struct Sala* criarSala(char nome[], char pista[]) {
    struct Sala *s = (struct Sala*)malloc(sizeof(struct Sala));
    strcpy(s->nome, nome);
    strcpy(s->pistaSala, pista);
    s->esq = NULL;
    s->dir = NULL;
    return s;
}

// adiciona pista ao entrar na sala
void explorar(struct Sala *atual, struct Pista **arvorePistas) {
    char opcao;

    while (1) {
        printf("\n📍 Você está na sala: %s\n", atual->nome);

        // Se a sala tiver pista, adiciona
        if (strlen(atual->pistaSala) > 0) {
            printf("🔎 Você encontrou uma pista: %s\n", atual->pistaSala);
            *arvorePistas = inserirPista(*arvorePistas, atual->pistaSala);
        }

        printf("\nMover:\n");
        printf("  (e) Ir para esquerda\n");
        printf("  (d) Ir para direita\n");
        printf("  (p) Revisar pistas coletadas\n");
        printf("  (s) Sair\n");
        printf("Escolha: ");
        scanf(" %c", &opcao);

        if (opcao == 's') {
            printf("\nSaindo da mansão...\n");
            return;
        }

        if (opcao == 'p') {
            printf("\n📚 Pistas coletadas:\n");
            if (*arvorePistas == NULL) {
                printf("Nenhuma pista ainda!\n");
            } else {
                listarPistas(*arvorePistas);
            }
            continue;
        }

        if (opcao == 'e') {
            if (atual->esq != NULL) {
                atual = atual->esq;
            } else {
                printf("Não existe sala à esquerda!\n");
            }
        }
        else if (opcao == 'd') {
            if (atual->dir != NULL) {
                atual = atual->dir;
            } else {
                printf("Não existe sala à direita!\n");
            }
        }
        else {
            printf("Opção inválida!\n");
        }
    }
}

// começa o main
int main() {
    struct Pista *arvorePistas = NULL;

    // Criando salas com possíveis pistas
    struct Sala *hall       = criarSala("Hall de Entrada", "");
    struct Sala *biblioteca = criarSala("Biblioteca", "Página rasgada de um diário");
    struct Sala *cozinha    = criarSala("Cozinha", "");
    struct Sala *sotao      = criarSala("Sótão", "Chave enferrujada");
    struct Sala *porao      = criarSala("Porão", "Pegadas de barro");
    struct Sala *jantar     = criarSala("Sala de Jantar", "Copo quebrado com cheiro estranho");

    //visual da arvore
    /*
            Hall
           /    \
    Biblioteca   Cozinha
      /    \        \
   Sótão  Porão   Sala Jantar
    */

    hall->esq = biblioteca;
    hall->dir = cozinha;

    biblioteca->esq = sotao;
    biblioteca->dir = porao;

    cozinha->dir = jantar;

    // Inicia exploração
    explorar(hall, &arvorePistas);

    return 0;
}
