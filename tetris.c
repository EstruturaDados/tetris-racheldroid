#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// --------------------------------------
// Struct que representa uma peça do jogo
// --------------------------------------
typedef struct {
    char nome;  // Tipo da peça ('I', 'O', 'T', 'L')
    int id;     // Identificador único
} Peca;

// -----------------------------
// Fila circular de peças
// -----------------------------
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} FilaPecas;

// -----------------------------
// Pilha de peças reservadas
// -----------------------------
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} PilhaReserva;

// -----------------------------
// Gera peça automaticamente
// -----------------------------
Peca gerarPeca(int id) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

// -----------------------------
// Inicializa fila com peças
// -----------------------------
void inicializarFila(FilaPecas *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->quantidade = 0;

    for (int i = 0; i < TAM_FILA; i++) {
        fila->itens[fila->fim] = gerarPeca(i);
        fila->fim = (fila->fim + 1) % TAM_FILA;
        fila->quantidade++;
    }
}

// -----------------------------
// Inicializa pilha vazia
// -----------------------------
void inicializarPilha(PilhaReserva *pilha) {
    pilha->topo = -1;
}

// -----------------------------
// Enfileirar peça na fila
// -----------------------------
void enqueue(FilaPecas *fila, Peca p) {
    fila->itens[fila->fim] = p;
    fila->fim = (fila->fim + 1) % TAM_FILA;
    fila->quantidade++;
}

// -----------------------------
// Desenfileirar peça (dequeue)
// -----------------------------
int dequeue(FilaPecas *fila, Peca *removida) {
    if (fila->quantidade == 0)
        return 0;

    *removida = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % TAM_FILA;
    fila->quantidade--;
    return 1;
}

// -----------------------------
// Empilhar peça (push)
// -----------------------------
int push(PilhaReserva *pilha, Peca p) {
    if (pilha->topo == TAM_PILHA - 1)
        return 0;

    pilha->topo++;
    pilha->itens[pilha->topo] = p;
    return 1;
}

// -----------------------------
// Desempilhar peça (pop)
// -----------------------------
int pop(PilhaReserva *pilha, Peca *removida) {
    if (pilha->topo == -1)
        return 0;

    *removida = pilha->itens[pilha->topo];
    pilha->topo--;
    return 1;
}

// -----------------------------
// Exibir estado da fila e pilha
// -----------------------------
void exibirEstado(FilaPecas fila, PilhaReserva pilha) {

    printf("\n===== ESTADO ATUAL =====\n");

    // Fila
    printf("Fila de peças:\t");
    int idx = fila.inicio;
    for (int i = 0; i < fila.quantidade; i++) {
        Peca p = fila.itens[idx];
        printf("[%c %d] ", p.nome, p.id);
        idx = (idx + 1) % TAM_FILA;
    }
    printf("\n");

    // Pilha
    printf("Pilha de reserva\t(Topo -> Base): ");
    if (pilha.topo == -1) {
        printf("[vazia]");
    } else {
        for (int i = pilha.topo; i >= 0; i--) {
            printf("[%c %d] ", pilha.itens[i].nome, pilha.itens[i].id);
        }
    }

    printf("\n=========================\n");
}

// -----------------------------
// Função principal com menu
// -----------------------------
int main() {
    srand(time(NULL));

    FilaPecas fila;
    PilhaReserva pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int opcao;
    int proximoId = TAM_FILA; // IDs continuam contando após peças iniciais

    printf("=== SISTEMA TETRIS STACK ===\n");

    do {
        exibirEstado(fila, pilha);

        printf("\nOpções:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        Peca removida;

        switch (opcao) {

            case 1: // jogar peça
                if (dequeue(&fila, &removida)) {
                    printf("\nPeça jogada: [%c %d]\n", removida.nome, removida.id);
                }
                break;

            case 2: // reservar peça (fila -> pilha)
                if (pilha.topo == TAM_PILHA - 1) {
                    printf("\n[Aviso] Pilha cheia! Não é possível reservar mais peças.\n");
                } else if (dequeue(&fila, &removida)) {
                    push(&pilha, removida);
                    printf("\nPeça reservada: [%c %d]\n", removida.nome, removida.id);
                }
                break;

            case 3: // usar peça reservada (pop)
                if (pop(&pilha, &removida)) {
                    printf("\nPeça usada (removida da reserva): [%c %d]\n", removida.nome, removida.id);
                } else {
                    printf("\nPilha vazia! Nenhuma peça reservada disponível.\n");
                }
                break;

            case 0:
                printf("\nEncerrando o programa.\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

        // Após cada ação, gerar peça nova e colocar no final da fila
        if (opcao != 0) {
            Peca nova = gerarPeca(proximoId++);
            enqueue(&fila, nova);
            printf("Nova peça gerada e adicionada à fila: [%c %d]\n", nova.nome, nova.id);
        }

    } while (opcao != 0);

    return 0;
}
