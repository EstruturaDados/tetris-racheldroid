#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5   // Tamanho fixo da fila de peças futuras

// -----------------------------
// Definição da struct da peça
// -----------------------------
typedef struct {
    char nome;   // Tipo da peça ('I', 'O', 'T', 'L')
    int id;      // Identificador único
} Peca;

// -----------------------------
// Estrutura para fila circular
// -----------------------------
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} FilaPecas;

// -----------------------------
// Função que gera automaticamente uma nova peça
// -----------------------------
Peca gerarPeca(int id) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca nova;

    nova.nome = tipos[rand() % 4]; // Escolhe tipo aleatório
    nova.id = id;

    return nova;
}

// -----------------------------
// Inicializa a fila com peças
// -----------------------------
void inicializarFila(FilaPecas *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->quantidade = 0;

    // Preenche a fila inicialmente
    for (int i = 0; i < TAM_FILA; i++) {
        Peca p = gerarPeca(i);
        fila->itens[fila->fim] = p;
        fila->fim = (fila->fim + 1) % TAM_FILA;
        fila->quantidade++;
    }
}

// -----------------------------
// Inserir peça na fila (enqueue)
// -----------------------------
int enqueue(FilaPecas *fila, Peca peca) {
    if (fila->quantidade == TAM_FILA) {
        printf("\n[Aviso] A fila está cheia! Não é possível inserir nova peça.\n");
        return 0;
    }

    fila->itens[fila->fim] = peca;
    fila->fim = (fila->fim + 1) % TAM_FILA;
    fila->quantidade++;
    return 1;
}

// -----------------------------
// Remover peça da fila (dequeue)
// -----------------------------
int dequeue(FilaPecas *fila, Peca *removida) {
    if (fila->quantidade == 0) {
        printf("\n[Aviso] A fila está vazia! Não há peça para jogar.\n");
        return 0;
    }

    *removida = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % TAM_FILA;
    fila->quantidade--;
    return 1;
}

// -----------------------------
// Exibir o estado da fila
// -----------------------------
void exibirFila(FilaPecas fila) {
    printf("\nFila de peças:\n");

    if (fila.quantidade == 0) {
        printf("[vazia]\n");
        return;
    }

    int idx = fila.inicio;

    for (int i = 0; i < fila.quantidade; i++) {
        Peca p = fila.itens[idx];
        printf("[%c %d] ", p.nome, p.id);
        idx = (idx + 1) % TAM_FILA;
    }

    printf("\n");
}

// -----------------------------
// Função principal com menu
// -----------------------------
int main() {
    srand(time(NULL));

    FilaPecas fila;
    inicializarFila(&fila);

    int opcao;
    int proximoId = TAM_FILA;  // id continua após os iniciais

    printf("=== Tetris Stack - Fila de Pecas Futuras ===\n");

    do {
        exibirFila(fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca removida;
            if (dequeue(&fila, &removida)) {
                printf("\nPeça jogada: [%c %d]\n", removida.nome, removida.id);
            }

        } else if (opcao == 2) {
            Peca nova = gerarPeca(proximoId++);
            if (enqueue(&fila, nova)) {
                printf("\nPeça adicionada: [%c %d]\n", nova.nome, nova.id);
            }

        } else if (opcao != 0) {
            printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    printf("\nEncerrando o programa. Até mais!\n");
    return 0;
}