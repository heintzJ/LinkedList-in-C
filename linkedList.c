#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node NodeType;
// node struct with data and a pointer to the next node
typedef struct node {
        char data[10];
        NodeType *next;
} NodeType;

NodeType* addNodeFront(NodeType *List, char* val){
        NodeType *new = (NodeType *)malloc(sizeof(NodeType)); // allocate memory for new node
        strcpy(new->data, val); // copy val to the data of the new node
        new->next=List; // set head of list to next of the new node, inserting it at the front
        return new;
}

NodeType* addNodeBack(NodeType *List, char* val){
        NodeType *new = (NodeType *)malloc(sizeof(NodeType));
        strcpy(new->data, val);
        new->next=NULL; // set next of new node to null, as it will go on the end of the list

        // if the list is empty
        if (List == NULL) {
                return new;
        }
        NodeType *current=List;
        // iterate along the list until current is at the end
        while (current->next != NULL){
                current=current->next;
        }
        current->next=new; // set the last node's next to the new node
        return List;
}

NodeType* removeNodeFront(NodeType *List){
        // if the list is empty, return null
        if (List == NULL){
                return NULL;
        }
        NodeType *front=List;
        List=front->next; // set the head of the list to the second element
        free(front); // free the first node
        return List;
}

NodeType* removeNodeBack(NodeType *List){
        // if the list is empty, return null
        if (List == NULL){
                return NULL;
        }
        NodeType *current=List;
        // if there is only one node in the list
        if (current->next == NULL){
                free(current);
                return NULL;
        }
        // iterate along the list until current is the second last node
        while (current->next->next != NULL){
                current=current->next;
        }
        // free the last node
        free(current->next);
        current->next=NULL; // make the second last node point to null
        return List;
}

NodeType* addNodeAfter(NodeType *List, char* insert, char* searchString){
        NodeType *current=List;
        // iterate along the list until the end or the search string is found
        while (current != NULL && strcmp(current->data, searchString) != 0) {
                current=current->next;
        }
        // when the search string is found and current is not null
        if (current != NULL){
                NodeType *new = (NodeType *)malloc(sizeof(NodeType)); // allocate memory for the new node
                strcpy(new->data, insert); // put the insert value into the data of the new node
                new->next=current->next; // new points to the next of current
                current->next=new; // current points to new, placing new just after it
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
                return node->data; // return the value of the node
        } else {
                return NULL;
        }
}

void printList(NodeType *List){
        // empty list
        if (List == NULL){
                printf("NULL\n");
                return;
        }
        // recursively print the list
        NodeType *current=List;
        printf("%s -> ", current->data);
        printList(current->next);
}

int main(void){
        // testing
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

        // free the whole list
        while (List != NULL) {
                NodeType* temp = List;
                List = List->next;
                free(temp);
        }
        return 0;
}
