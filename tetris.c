#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

// Estrutura da peça
typedef struct {
    char nome;
    int id;
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// Variável global para gerar IDs únicos
int proximoId = 0;

// Gera uma nova peça automaticamente
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};

    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = proximoId++;

    return nova;
}

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->quantidade == TAM_FILA;
}

// Insere peça no final da fila (enqueue)
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia! Nao foi possivel inserir nova peca.\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
}

// Remove peça da frente da fila (dequeue)
Peca dequeue(Fila *f) {
    Peca removida = {' ', -1};

    if (filaVazia(f)) {
        printf("Fila vazia! Nenhuma peca para jogar.\n");
        return removida;
    }

    removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;

    return removida;
}

// Exibe a fila atual
void exibirFila(Fila *f) {
    printf("\nFila de pecas:\n");

    if (filaVazia(f)) {
        printf("[vazia]\n");
        return;
    }

    int pos = f->inicio;

    for (int i = 0; i < f->quantidade; i++) {
        printf("[%c %d] ", f->itens[pos].nome, f->itens[pos].id);
        pos = (pos + 1) % TAM_FILA;
    }

    printf("\n");
}

int main() {
    srand(time(NULL));

    Fila fila;
    inicializarFila(&fila);

    // Preenche a fila com 5 peças iniciais
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;

    do {
        exibirFila(&fila);

        printf("\n=== MENU ===\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca jogada = dequeue(&fila);

                if (jogada.id != -1) {
                    printf("Peca jogada: [%c %d]\n",
                           jogada.nome, jogada.id);
                }
                break;
            }

            case 2:
                enqueue(&fila, gerarPeca());
                printf("Nova peca inserida!\n");
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}