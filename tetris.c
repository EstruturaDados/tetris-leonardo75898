#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

// Struct para representar uma peça
typedef struct {
    char nome; // 'I', 'O', 'T', 'L', etc.
    int id;
} Peca;

// Fila circular
typedef struct {
    Peca fila[TAM_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

int id_global = 1;

// Função para gerar peça aleatória
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L', 'S', 'Z', 'J'};
    Peca nova;
    nova.nome = tipos[rand() % 7];
    nova.id = id_global++;
    return nova;
}

// Inicializa a fila com 5 peças
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;

    for (int i = 0; i < TAM_FILA; i++) {
        f->fila[f->fim] = gerarPeca();
        f->fim = (f->fim + 1) % TAM_FILA;
        f->total++;
    }
}

// Mostra o estado atual da fila
void mostrarFila(Fila *f) {
    printf("\nFila de Peças:\n");
    int i = f->inicio;
    for (int count = 0; count < f->total; count++) {
        printf("Posição %d: Peça %c (ID %d)\n", count + 1, f->fila[i].nome, f->fila[i].id);
        i = (i + 1) % TAM_FILA;
    }
    if (f->total == 0) {
        printf("[Fila vazia]\n");
    }
    printf("\n");
}

// Remove a peça da frente da fila
void jogarPeca(Fila *f) {
    if (f->total == 0) {
        printf("Não há peças para jogar.\n");
        return;
    }
    Peca p = f->fila[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->total--;
    printf("Você jogou a peça %c (ID %d)\n", p.nome, p.id);
}

// Insere uma nova peça no final da fila
void inserirPeca(Fila *f) {
    if (f->total == TAM_FILA) {
        printf("Fila cheia! Não é possível inserir nova peça.\n");
        return;
    }
    Peca nova = gerarPeca();
    f->fila[f->fim] = nova;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->total++;
    printf("Nova peça inserida: %c (ID %d)\n", nova.nome, nova.id);
}

int main() {
    srand(time(NULL)); // Inicializa a semente aleatória

    Fila fila;
    inicializarFila(&fila);

    int opcao;

    do {
        printf("==== TETRIS STACK ====\n");
        printf("1 - Visualizar fila\n");
        printf("2 - Jogar peça (remover da frente)\n");
        printf("3 - Inserir nova peça (no final)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                mostrarFila(&fila);
                break;
            case 2:
                jogarPeca(&fila);
                mostrarFila(&fila);
                break;
            case 3:
                inserirPeca(&fila);
                mostrarFila(&fila);
                break;
            case 0:
                printf("Encerrando o programa. Até logo!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
