#include <stdio.h>

typedef struct node
{
    int data;
    struct Node* next;
}Node;

typedef struct list
{
    Node* head;
    //현재주소
    Node* crnt;
}List;

void initialize(List* list)
{
    list->head = NULL;
    list->crnt = NULL;
}

// integer x 를 data 멤버로 갖는 새 노드 생성
// 노드 생성에 필요한 메모리는 동적 할당 받음
// Return the pointer to memory allocation dynamically, if succeeded
// Return NULL, if failed
Node* createNode(int x)
{
    Node* temp;
    temp = (Node*)calloc(1, sizeof(Node));

    if (temp == NULL)
    {
        printf("Memory allocation failed\n");
    }
    else
    {
        temp->data = x;
        temp->next = NULL;
    }

    if(temp != NULL)
        printf("Node is created. Data : %d\n", temp->data);
    
    return temp;
}

// Create node with int x
// Insert the created node int the front
void insertFront(List* list, int x)
{
    Node* temp;
    temp = createNode(x);

    if (temp == NULL)
    {
        exit(1);
    }

    temp->next = list->head;
    list->head = temp;
    list->crnt = temp;

    printf("First Node Data Head pointer is now pointed to : %d\n"
    , list->head->data);

    return;
}

//Print all the node data int the list
void printList(List* list)
{
    Node* temp;
    //list is empty
    if(list->head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    temp  = list->head;

    printf("head -> ");
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Create node with int x
// Insert the created node in the rear
void insertRear(List* list, int x)
{
    Node* newNode;
    Node* temp;

    newNode = createNode(x);

    //fail to create node
    if(newNode == NULL)
        exit(1);

    //List is empty
    if(list->head == NULL)
    {
        list->head = newNode;
        list->crnt = newNode;
        return;
    }

    // List has at leat on node
    // Find the last node
    temp = list->head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    list->crnt = newNode;

    return;
}

int main()
{
    List myList;
    List yourList;

    initialize(&myList);
    insertFront(&myList, 5);
    insertFront(&myList, 2);
    insertFront(&myList, 3);
    insertFront(&myList, 1);

    printList(&myList);

    initialize(&yourList);
    insertRear(&yourList, 5);
    insertRear(&yourList, 4);
    insertRear(&yourList, 3);

    printList(&yourList);

    return 0;
}