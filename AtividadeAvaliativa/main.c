#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node *createNode(int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (!newNode) {
    printf("Erro ao alocar memória.\n");
    exit(1);
  }
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

void inserirOrdenado(Node **head, int data) {
  Node *newNode = createNode(data);

  if (*head == NULL || (*head)->data >= data) {
    newNode->next = *head;
    *head = newNode;
    return;
  }

  Node *current = *head;
  while (current->next != NULL && current->next->data < data) {
    current = current->next;
  }

  newNode->next = current->next;
  current->next = newNode;
}

void removerElemento(Node **head, int data) {
  Node *current = *head;
  Node *previous = NULL;

  if (current != NULL && current->data == data) {
    *head = current->next;
    free(current);
    return;
  }

  while (current != NULL && current->data != data) {
    previous = current;
    current = current->next;
  }

  if (current == NULL) {
    printf("Elemento %d não encontrado na lista.\n", data);
    return;
  }

  previous->next = current->next;
  free(current);
}

Node *buscarElemento(Node *head, int data) {
  Node *current = head;
  while (current != NULL) {
    if (current->data == data) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

int contarElementos(Node *head) {
  int count = 0;
  Node *current = head;
  while (current != NULL) {
    count++;
    current = current->next;
  }
  return count;
}

void mostrarLista(Node *head) {
  Node *temp = head;
  while (temp != NULL) {
    printf("\n%d ", temp->data);
    temp = temp->next;
  }
  printf("\nNULL\n");
}

int main() {
  Node *head = NULL;

  inserirOrdenado(&head, 10);
  inserirOrdenado(&head, 20);
  inserirOrdenado(&head, 30);
  inserirOrdenado(&head, 40);
  inserirOrdenado(&head, 50);

  printf("\nElementos da lista antes da remoção: ");
  mostrarLista(head);

  int total = contarElementos(head);
  printf("Número total de elementos na lista antes da remoção: %d\n", total);

  removerElemento(&head, 10);
  printf("\nRemovendo o elementos da lista: %d ", 10);

  printf("\nElementos da lista: ");
  mostrarLista(head);

  int busca = 30;
  Node *resultado = buscarElemento(head, busca);
  if (resultado) {
    printf("\nElemento %d encontrado na lista.\n", resultado->data);
  } else {
    printf("\nElemento %d não encontrado na lista.\n", busca);
  }

  busca = 50;
  resultado = buscarElemento(head, busca);
  if (resultado) {
    printf("\nElemento %d encontrado na lista.\n", resultado->data);
  } else {
    printf("\nElemento %d não encontrado na lista.\n", busca);
  }

  total = contarElementos(head);
  printf("Número total de elementos na lista após remoção: %d\n", total);

  while (head != NULL) {
    Node *temp = head;
    head = head->next;
    free(temp);
  }

  return 0;
}