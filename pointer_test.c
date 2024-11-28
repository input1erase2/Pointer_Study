#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int data;
    struct _node* next;
} Node;

Node* makeNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void arguTest1(Node* n1) {
    printf("[arguTest1 start]=================\n\n");
    printf("[Value of pointer argument] >> n1 = %p\n", n1);
    printf("[Addr of pointer argument] >> addr(n1) = %p\n\n", &n1);
    
    printf("[Before modifying] >> n1->next = ");
    if (n1->next == NULL) printf("NULL\n\n");
    else printf("%p\n\n", n1->next);
    
    n1->data = 100;
    n1->next = makeNode(1000);
    n1 = n1->next;
    
    printf("[After modifying] >> n1 = %p\n\n", n1);
    printf("[arguTest1 end]=================\n\n");
}

void arguTest2(Node** n2) {
    printf("[arguTest2 start]================\n\n");
    printf("[Value of pointer argument] >> n2 = %p\n", n2);
    printf("[Addr of pointer argument] >> addr(n2) = %p\n\n", &n2);
    
    printf("[Before modifying] >> (*n2)->next = ");
    if ((*n2)->next == NULL) printf("NULL\n\n");
    else printf("%p\n\n", (*n2)->next);
    
    (*n2)->data = 200;
    
    if ((*n2)->next != NULL) free((*n2)->next);
    (*n2)->next = makeNode(2000);
    
    node* delNode = (*n2);
    (*n2) = (*n2)->next;
    free(delNode);
    
    printf("[After modifying] >> (*n2) = %p\n\n", (*n2));
    printf("[arguTest2 end]=================\n\n");
}

int main() {
    Node* node = makeNode(10);
    printf("[Original] >> addr(n) = %p\n", node);
    printf("[Addr of original Pointer] >> addr(n) = %p\n\n", &node);
    
    /*=================================================*/
    
    arguTest1(node);
    
    printf("[Data of ] >> n->data = %d\n", node->data);
    printf("[Value of pointer ] >> n = %p\n", node);
    if (node->next != NULL)
        printf("[Data of ] >> n->next = %d\n", node->next->data);
    else
        printf("[Data of ] >> n->next = NULL\n");
    printf("\n\n");
    
    /*=================================================*/
    
    arguTest2(&node);
    
    printf("[Data of ] >> n->data = %d\n", node->data);
    printf("[value of pointer ] >> n = %p\n", node);
    if (node->next != NULL) {
        printf("[Data of ] >> n->next = %d\n", node->next->data);
        free(node->next);
    }
    else
        printf("[Data of ] >> n->next = NULL\n");
    printf("\n\n");
    
    free(node);
    return 0;
}