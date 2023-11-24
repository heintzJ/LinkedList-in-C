#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node NodeType;
typedef struct node {
        char data[10];
        NodeType *next;
} NodeType;

NodeType* addNodeFront(NodeType *List, char* val){
        NodeType *new = (NodeType *)malloc(sizeof(NodeType));
        strcpy(new->data, val);
        new->next=List;
        return new;
}

NodeType* addNodeBack(NodeType *List, char* val){
        NodeType *new = (NodeType *)malloc(sizeof(NodeType));
        strcpy(new->data, val);
        new->next=NULL;

        if (List == NULL) {
                return new;
        }
        NodeType *current=List;
        while (current->next != NULL){
                current=current->next;
        }
        current->next=new;
        return List;
}

NodeType* removeNodeFront(NodeType *List){
        if (List == NULL){
                return NULL;
        }
        NodeType *front=List;
        List=front->next;
        free(front);
        return List;
}

NodeType* removeNodeBack(NodeType *List){
        if (List == NULL){
                return NULL;
        }
        NodeType *current=List;
        if (current->next == NULL){
                free(current);
                return NULL;
        }
        while (current->next->next != NULL){
                current=current->next;
        }
        free(current->next);
        current->next=NULL;
        return List;
}

NodeType* addNodeAfter(NodeType *List, char* insert, char* searchString){
        NodeType *current=List;
        while (current != NULL && strcmp(current->data, searchString) != 0) {
                current=current->next;
        }
        // when the search string is found and current is not null
        if (current != NULL){
                NodeType *new = (NodeType *)malloc(sizeof(NodeType));
                strcpy(new->data, insert);
                new->next=current->next;
                current->next=new;
        }
        return List;
}

NodeType* removeNode(NodeType *List, char* remove){
        NodeType *current=List;

        // special case of first element is the matched string
        if (strcmp(current->data, remove) == 0){
                free(current);
                return NULL;
        }
        NodeType *prev;
        // iterate through list until the end, or string is matched
        while (current != NULL && strcmp(current->data, remove) != 0){
                prev=current;
                current=current->next;
        }
        // when the search string is matched and current->next is not null
        if (current != NULL){
                free(current);
                prev->next=NULL;
                return List;
        }
        return List;
}

char* getFrontText(NodeType *node){
        if (node != NULL){
                return node->data;
        } else {
                return NULL;
        }
}

void printList(NodeType *List){
        if (List == NULL){
                printf("NULL\n");
                return;
        }
        NodeType *current=List;
        printf("%s -> ", current->data);
        printList(current->next);
}

int main(void){
        NodeType *List;
        List=NULL;
        List = addNodeFront(List, "Hello");
        printf("Added 'Hello' to front\n");
        printList(List);

        List = addNodeBack(List, "World");
        printf("Added 'World' to back\n");
        printList(List);

        List = removeNodeFront(List);
        printf("Removed front\n");
        printList(List);

        List = addNodeFront(List, "Hello");
        printf("Added 'Hello' to front\n");
        printList(List);

        List = removeNodeBack(List);
        printf("Removed back\n");
        printList(List);

        List = addNodeAfter(List, "World", "Hello");
        printf("Added 'World' after 'Hello'\n");
        printList(List);

        List = removeNode(List, "World");
        printf("Removed 'World'\n");
        printList(List);

        printf("%s\n", getFrontText(List));

        while (List != NULL) {
                NodeType* temp = List;
                List = List->next;
                free(temp);
        }
        return 0;
}
