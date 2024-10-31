#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

typedef struct CircularQueue {
  int items[MAX_SIZE];
  int front;
  int rear;
  int count;
} CircularQueue;

CircularQueue *criarFilaCircular() {
  CircularQueue *queue = (CircularQueue *)malloc(sizeof(CircularQueue));
  queue->front = 0;
  queue->rear = -1;
  queue->count = 0;
  return queue;
}

int isFull(CircularQueue *queue) { return queue->count == MAX_SIZE; }

int isEmpty(CircularQueue *queue) { return queue->count == 0; }

int contarElementos(CircularQueue *queue) { return queue->count; }

void enqueue(CircularQueue *queue, int value) {
  if (isFull(queue)) {
    queue->front = (queue->front + 1) % MAX_SIZE;
  }

  queue->rear = (queue->rear + 1) % MAX_SIZE;
  queue->items[queue->rear] = value;

  if (!isFull(queue)) {
    queue->count++;
  }
}

int dequeue(CircularQueue *queue) {
  if (isEmpty(queue)) {
    printf("Fila vazia!\n");
    return -1;
  }

  int value = queue->items[queue->front];
  queue->front = (queue->front + 1) % MAX_SIZE;
  queue->count--;
  return value;
}

int primeiroElementoFila(CircularQueue *queue) {
  if (isEmpty(queue)) {
    printf("Fila vazia!\n");
    return -1;
  }
  return queue->items[queue->front];
}

void freeFilaCircular(CircularQueue *queue) { free(queue); }

typedef struct Node {
  int data;
  int priority;
  struct Node *next;
} Node;

typedef struct PriorityQueue {
  Node *front;
} PriorityQueue;

PriorityQueue *criarFilaPrioridade() {
  PriorityQueue *queue = (PriorityQueue *)malloc(sizeof(PriorityQueue));
  queue->front = NULL;
  return queue;
}

int isEmptyPriority(PriorityQueue *queue) { return queue->front == NULL; }

void enqueuePriority(PriorityQueue *queue, int value, int priority) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = value;
  newNode->priority = priority;
  newNode->next = NULL;

  if (queue->front == NULL || queue->front->priority < priority) {
    newNode->next = queue->front;
    queue->front = newNode;
  } else {
    Node *current = queue->front;
    while (current->next != NULL && current->next->priority >= priority) {
      current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
  }
}

int dequeuePriority(PriorityQueue *queue) {
  if (isEmptyPriority(queue)) {
    printf("Fila de prioridade vazia!\n");
    return -1;
  }

  Node *temp = queue->front;
  int value = temp->data;
  queue->front = queue->front->next;
  free(temp);
  return value;
}

int primeiroElementoFilaPrioridade(PriorityQueue *queue) {
  if (isEmptyPriority(queue)) {
    printf("Fila de prioridade vazia!\n");
    return -1;
  }
  return queue->front->data;
}

void freeFilaPrioridade(PriorityQueue *queue) {
  while (!isEmptyPriority(queue)) {
    dequeuePriority(queue);
  }
  free(queue);
}

// Função para separar elementos pares e ímpares
void separarParesImpares(int *lista, int tamanho, CircularQueue **filaPares,
                         CircularQueue **filaImpares) {
  *filaPares = criarFilaCircular();
  *filaImpares = criarFilaCircular();

  for (int i = 0; i < tamanho; i++) {
    if (lista[i] % 2 == 0) {
      enqueue(*filaPares, lista[i]);
    } else {
      enqueue(*filaImpares, lista[i]);
    }
  }
}

int main() {
  CircularQueue *filaCircular = criarFilaCircular();
  PriorityQueue *filaPrioridade = criarFilaPrioridade();

  enqueue(filaCircular, 10);
  enqueue(filaCircular, 20);
  enqueue(filaCircular, 30);
  enqueue(filaCircular, 40);
  enqueue(filaCircular, 50);

  printf("\nPrimeiro elemento da fila circular: %d\n",
         primeiroElementoFila(filaCircular));

  enqueuePriority(filaPrioridade, 10, 1);
  enqueuePriority(filaPrioridade, 20, 3);
  enqueuePriority(filaPrioridade, 30, 2);
  enqueuePriority(filaPrioridade, 40, 5);
  enqueuePriority(filaPrioridade, 50, 4);

  printf("\nPrimeiro elemento da fila de prioridade: %d\n",
         primeiroElementoFilaPrioridade(filaPrioridade));

  printf("\nDesenfileirando da fila circular: %d\n", dequeue(filaCircular));
  printf("\nDesenfileirando da fila circular: %d\n", dequeue(filaCircular));

  printf("\nDesenfileirando da fila de prioridade: %d\n",
         dequeuePriority(filaPrioridade));
  printf("\nDesenfileirando da fila de prioridade: %d\n",
         dequeuePriority(filaPrioridade));

  // Separação de pares e ímpares
  int lista[] = {10, 21, 32, 43, 54, 65};
  CircularQueue *filaPares;
  CircularQueue *filaImpares;
  separarParesImpares(lista, 6, &filaPares, &filaImpares);

  // Exibindo os elementos das filas
  printf("\nElementos pares na fila:\n");
  while (!isEmpty(filaPares)) {
    printf("%d ", dequeue(filaPares));
  }

  printf("\nElementos ímpares na fila:\n");
  while (!isEmpty(filaImpares)) {
    printf("%d ", dequeue(filaImpares));
  }

  // Liberar memória
  freeFilaCircular(filaPares);
  freeFilaCircular(filaImpares);
  freeFilaCircular(filaCircular);
  freeFilaPrioridade(filaPrioridade);

  return 0;
}
