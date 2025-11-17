#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// -----------------------------
// Estrutura da peça
// -----------------------------
typedef struct {
    char nome;  
    int id;
} Peca;

// -----------------------------
// Fila circular
// -----------------------------
typedef struct {
    Peca itens[TAM_FILA];
    int inicio, fim, quantidade;
} FilaPecas;

// -----------------------------
// Pilha de reserva
// -----------------------------
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} PilhaReserva;

// -----------------------------
// Gerar peça automaticamente
// -----------------------------
Peca gerarPeca(int id) {
    char tipos[4] = { 'I', 'O', 'T', 'L' };
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

// -----------------------------
// Inicialização da fila
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
// Inicialização da pilha
// -----------------------------
void inicializarPilha(PilhaReserva *pilha) {
    pilha->topo = -1;
}

// -----------------------------
// Enqueue
// -----------------------------
void enqueue(FilaPecas *fila, Peca p) {
    if (fila->quantidade == TAM_FILA) return;
    fila->itens[fila->fim] = p;
    fila->fim = (fila->fim + 1) % TAM_FILA;
    fila->quantidade++;
}

// -----------------------------
// Dequeue
// -----------------------------
int dequeue(FilaPecas *fila, Peca *out) {
    if (fila->quantidade == 0) return 0;
    *out = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % TAM_FILA;
    fila->quantidade--;
    return 1;
}

// -----------------------------
// Push
// -----------------------------
int push(PilhaReserva *pilha, Peca p) {
    if (pilha->topo == TAM_PILHA - 1) return 0;
    pilha->itens[++pilha->topo] = p;
    return 1;
}

// -----------------------------
// Pop
// -----------------------------
int pop(PilhaReserva *pilha, Peca *out) {
    if (pilha->topo == -1) return 0;
    *out = pilha->itens[pilha->topo--];
    return 1;
}

// -----------------------------
// Exibir estado das estruturas
// -----------------------------
void exibir(FilaPecas fila, PilhaReserva pilha) {
    printf("\n==== ESTADO ATUAL ====\n");

    printf("Fila de peças\t");
    int idx = fila.inicio;
    for (int i = 0; i < fila.quantidade; i++) {
        printf("[%c %d] ", fila.itens[idx].nome, fila.itens[idx].id);
        idx = (idx + 1) % TAM_FILA;
    }
    printf("\n");

    printf("Pilha de reserva (Topo → Base): ");
    if (pilha.topo == -1)
        printf("[vazia]");
    else
        for (int i = pilha.topo; i >= 0; i--)
            printf("[%c %d] ", pilha.itens[i].nome, pilha.itens[i].id);

    printf("\n========================\n");
}

// -----------------------------
// Troca única (fila[0] ↔ pilha[topo])
// -----------------------------
void trocarPeçaAtual(FilaPecas *fila, PilhaReserva *pilha) {
    if (pilha->topo == -1) {
        printf("\nPilha vazia! Não é possível trocar.\n");
        return;
    }
    if (fila->quantidade == 0) {
        printf("\nFila vazia! Não há peça atual.\n");
        return;
    }

    int pos = fila->inicio;

    Peca temp = fila->itens[pos];
    fila->itens[pos] = pilha->itens[pilha->topo];
    pilha->itens[pilha->topo] = temp;

    printf("\nTroca realizada com sucesso!\n");
}

// -----------------------------
// Troca múltipla (3 da fila ↔ 3 da pilha)
// -----------------------------
void trocaMultipla(FilaPecas *fila, PilhaReserva *pilha) {
    if (fila->quantidade < 3 || pilha->topo < 2) {
        printf("\nNão há peças suficientes para troca múltipla.\n");
        return;
    }

    int idx = fila->inicio;

    for (int i = 0; i < 3; i++) {
        Peca temp = fila->itens[(idx + i) % TAM_FILA];
        fila->itens[(idx + i) % TAM_FILA] = pilha->itens[pilha->topo - i];
        pilha->itens[pilha->topo - i] = temp;
    }

    printf("\nTroca múltipla realizada com sucesso!\n");
}

// -----------------------------
// Função principal
// -----------------------------
int main() {
    srand(time(NULL));

    FilaPecas fila;
    PilhaReserva pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int opcao;
    int proximoId = TAM_FILA;

    do {
        exibir(fila, pilha);

        printf("\nOpções:\n");
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Enviar peça da fila para a pilha\n");
        printf("3 - Usar peça da pilha\n");
        printf("4 - Trocar peça da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 peças da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        Peca removida;

        switch (opcao) {
            case 1: // Jogar
                if (dequeue(&fila, &removida)) {
                    printf("\nPeça jogada: [%c %d]\n", removida.nome, removida.id);
                    enqueue(&fila, gerarPeca(proximoId++));
                }
                break;

            case 2: // Reservar
                if (pilha.topo == TAM_PILHA - 1)
                    printf("\nPilha cheia! Não é possível reservar.\n");
                else if (dequeue(&fila, &removida)) {
                    push(&pilha, removida);
                    printf("\nPeça reservada: [%c %d]\n", removida.nome, removida.id);
                    enqueue(&fila, gerarPeca(proximoId++));
                }
                break;

            case 3: // Usar reservada
                if (pop(&pilha, &removida))
                    printf("\nPeça usada e removida da reserva: [%c %d]\n", removida.nome, removida.id);
                else
                    printf("\nPilha vazia!\n");
                break;

            case 4: // Troca simples
                trocarPeçaAtual(&fila, &pilha);
                break;

            case 5: // Troca múltipla
                trocaMultipla(&fila, &pilha);
                break;

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}