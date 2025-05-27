#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *head = NULL;

void listPrint();

void addHeadNode(int data);

void addEndNode(int data);

void addBetweenNode(int data, int position);

void deleteNode(int position);

void freeList();

int main() {
    int choice, data, position;

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1- List Print\n");
        printf("2- Add Head Node\n");
        printf("3- Add End Node\n");
        printf("4- Add Between Node\n");
        printf("5- Delete Node\n");
        printf("6- Exit Program\n");

        printf("Select choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                listPrint();
                break;
            case 2:
                printf("Enter an integer: ");
                scanf("%d", &data);
                addHeadNode(data);
                break;
            case 3:
                printf("Enter an integer: ");
                scanf("%d", &data);
                addEndNode(data);
                break;
            case 4:
                printf("Enter an integer: ");
                scanf("%d", &data);
                printf("Enter a position (starting from 0): ");
                scanf("%d", &position);
                addBetweenNode(data, position);
                break;
            case 5:
                printf("Enter position to delete (starting from 0): ");
                scanf("%d", &position);
                deleteNode(position);
                break;
            case 6:
                printf("Exit program...\n");
                freeList();
                exit(0);
            default:
                printf("Wrong choice, try again!\n");
        }
    }
}

void listPrint() {
    Node *node = head;

    printf("List: ");
    while (node != NULL) {
        printf("%d --> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

void addHeadNode(int data) {
    Node *node = malloc(sizeof(Node));

    if (!node) {
        printf("A memory allocation error occurred\n");
        return;
    }

    node->data = data;
    node->next = head;
    head = node;
}

void addEndNode(int data) {
    Node *node = malloc(sizeof(Node));

    if (!node) {
        printf("A memory allocation error occurred\n");
        return;
    }

    node->data = data;
    node->next = NULL;

    if (head == NULL) {
        head = node;
        return;
    }

    Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = node;
}

void addBetweenNode(int data, int position) {
    if (position < 0) {
        printf("The sorting index cannot be less than 0.\n");
        return;
    }

    Node *node = malloc(sizeof(Node));
    
    if (!node) {
        printf("A memory allocation error occurred\n");
        return;
    }

    node->data = data;

    if (position == 0) {
        node->next = head;
        head = node;
        return;
    }

    Node *temp = head;
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position is greater than list length!\n");
        free(node);
        return;
    }

    node->next = temp->next;
    temp->next = node;
}

void deleteNode(int position) {
    if (head == NULL || position < 0) {
        printf("The list is empty or the position is invalid!\n");
        return;
    }

    Node *temp = head;

    if (position == 0) {
        head = temp->next;
        free(temp);
        printf("Position 0 has been deleted!\n");
        return;
    }

    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Position is larger than list length! Delete failed.\n");
        return;
    }

    Node *delNode = temp->next;
    temp->next = delNode->next;
    free(delNode);
    printf("The node at position %d was deleted.\n", position);
}

void freeList() {
    Node *current = head;
    Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    head = NULL;
}