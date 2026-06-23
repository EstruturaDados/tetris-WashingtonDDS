#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// =====================
// Estrutura da peça
// =====================
typedef struct {
    char nome;
    int id;
} Peca;

// =====================
// Estrutura da fila
// =====================
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// =====================
// Estrutura da pilha
// =====================
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

// Gerador de IDs únicos
int proximoId = 0;

// =====================
// Geração de peças
// =====================
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};

    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = proximoId++;

    return nova;
}

// =====================
// Funções da fila
// =====================
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

int filaCheia(Fila *f) {
    return f->quantidade == TAM_FILA;
}

void enqueue(Fila *f, Peca p) {
    if (filaCheia(f))
        return;

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
}

Peca dequeue(Fila *f) {
    Peca removida = {' ', -1};

    if (filaVazia(f))
        return removida;

    removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;

    return removida;
}

// =====================
// Funções da pilha
// =====================
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

void push(Pilha *p, Peca item) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia! Nao e possivel reservar.\n");
        return;
    }

    p->itens[++p->topo] = item;
}

Peca pop(Pilha *p) {
    Peca removida = {' ', -1};

    if (pilhaVazia(p)) {
        printf("Pilha vazia!\n");
        return removida;
    }

    removida = p->itens[p->topo--];
    return removida;
}

// =====================
// Exibição
// =====================
void exibirFila(Fila *f) {
    printf("Fila de pecas:\n");

    int pos = f->inicio;

    for (int i = 0; i < f->quantidade; i++) {
        printf("[%c %d] ", f->itens[pos].nome,
                          f->itens[pos].id);

        pos = (pos + 1) % TAM_FILA;
    }

    printf("\n");
}

void exibirPilha(Pilha *p) {
    printf("Pilha de reserva (Topo -> Base): ");

    if (pilhaVazia(p)) {
        printf("[vazia]");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ",
                   p->itens[i].nome,
                   p->itens[i].id);
        }
    }

    printf("\n");
}

void exibirEstado(Fila *fila, Pilha *pilha) {
    printf("\n================================\n");
    exibirFila(fila);
    exibirPilha(pilha);
    printf("================================\n");
}

// =====================
// Programa principal
// =====================
int main() {

    srand(time(NULL));

    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Preenche fila inicial
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;

    do {
        exibirEstado(&fila, &pilha);

        printf("\n=== MENU ===\n");
        printf("1 - Jogar peca\n");
        printf("2 - Reservar peca\n");
        printf("3 - Usar peca reservada\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: {
                Peca jogada = dequeue(&fila);

                if (jogada.id != -1) {
                    printf("\nPeca jogada: [%c %d]\n",
                           jogada.nome,
                           jogada.id);

                    // Mantém a fila cheia
                    enqueue(&fila, gerarPeca());
                }
                break;
            }

            case 2: {

                if (pilhaCheia(&pilha)) {
                    printf("\nA reserva esta cheia!\n");
                    break;
                }

                Peca reservada = dequeue(&fila);

                if (reservada.id != -1) {

                    push(&pilha, reservada);

                    printf("\nPeca reservada: [%c %d]\n",
                           reservada.nome,
                           reservada.id);

                    // Mantém a fila cheia
                    enqueue(&fila, gerarPeca());
                }

                break;
            }

            case 3: {

                Peca usada = pop(&pilha);

                if (usada.id != -1) {
                    printf("\nPeca reservada utilizada: [%c %d]\n",
                           usada.nome,
                           usada.id);
                }

                break;
            }

            case 0:
                printf("\nEncerrando o programa...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}