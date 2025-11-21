/*
COFFEE BEAN PROBLEM
* This program aims to demonstrate the coffee bean problem,
* a demonstration that shows proving of haulting of a program.
* Ten Beans are placed at random in a linked list which acts as the can
* which are either black or white.
* Two beans are picked at random;
* If both are of the same colour, they are discarded 
* and one black bean is returned to the can.
* If both are of different colours, the white one is returned 
* and the black one discarded.
* The invariants are:
* -Each step reduces the number of beans in the can...eventually till only one is left
* -The parity of white beans is preserved
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BLACK 'B'
#define WHITE 'W'

typedef struct {
    char type;
} Bean;  //struct to represent a bean with a character representing its colour.

typedef struct Node Node;

//Nodes as elements in a single linked list.
struct Node {
    Bean *bean;
    Node *next;
};

typedef struct {
    Node *head;
    int size;
} LinkedList;

void init(Bean *bean, char type) {
    bean->type = type;
}

Node *create_node(Bean *bean) {
    //allocate node on the heap
    Node *node = (Node *) malloc(sizeof(Node));

    if (!node) {
        fprintf(stderr, "Failed to allocate memory to node\n");
        exit(EXIT_FAILURE);
    }

    node->bean = bean;
    node->next = NULL;

    return node;
}

void init_list(LinkedList *list) {
    list->size = 0;
    list->head = NULL;
}

void add(LinkedList *list, Bean *bean) {
    //create node with bean
    Node *node = create_node(bean);

    //if list is empty add node as first element
    if (list->head == NULL) {
        list->head = node;
    } else {
        Node *current = list->head;

        //loop through list till the end then add node at its tail
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = node;
    }
    list->size++;
}

Bean *get(LinkedList *list, int index) {
    if (list->head == NULL) {
        fprintf(stderr, "List is empty\n");
        return NULL;
    }

    if (list->size <= index || index < 0) {
        fprintf(stderr, "Index out of Bounds\n");
        return NULL;
    }

    int pos = 0;

    Node *current = list->head;

    //loop through list until index is reached
    while (current != NULL) {
        if (pos == index) {
            return current->bean; //return pointer to bean
        }

        current = current->next;
        ++pos;
    }
    return NULL;
}

void remove_frm_list(LinkedList *list, int index) {
    if (list->head == NULL) {
        fprintf(stderr, "List is empty\n");
        return;
    }

    if (list->size <= index || index < 0) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }

    Node *to_delete = list->head;  //iterator

    if (index == 0) { //remove head by assigning new head it its succeeding element
        to_delete = list->head;
        list->head = list->head->next;
    } else {
        Node *current = list->head;

        //iterate till element in the position just before target is reached
        for (int pos = 0; pos < index - 1; pos++) {
            current = current->next;
        }
        to_delete = current->next;
        current->next = to_delete->next;  //skip over to next element essentially removing pointer from list
    }
    //free memory of deleted node
    free(to_delete->bean);
    free(to_delete);
    list->size--;
}

void coffee_can_pick(LinkedList *list) {
    //pick beans at random
    int index1 = rand() % list->size;
    int index2 = rand() % list->size;
    
    //ensure beans arent picked from the same spot
    while (index1 == index2 && list->size != 1) {
        index2 = rand() % list->size;
    }

    //get beans at random generated index positions
    Bean *bean1 = get(list, index1);
    Bean *bean2 = get(list, index2);

    if (bean1->type == bean2->type) {
        //if tne same remove both and add black bean
        //ensures to remove the bean at the larger index first to avoid shifts
        if (index1 > index2) {
            remove_frm_list(list, index1);
            remove_frm_list(list, index2);
        } else {
            remove_frm_list(list, index2);
            remove_frm_list(list, index1);
        }

        Bean *bbean = (Bean *) malloc(sizeof(Bean));

        if (!bbean) {
            fprintf(stderr, "Failed to allocate memory to bean\n");
            exit(EXIT_FAILURE);
        }

        init(bbean, BLACK);

        add(list, bbean);
    }
    else { //else add white bean and discard white bean
        if (bean1->type == BLACK) {
            remove_frm_list(list, index1);
        } else {
            remove_frm_list(list, index2);
        }
    }
}

void coffee_can(LinkedList *list) {
    if (list->size == 0) {
        printf("Empty can\n");
        return;
    }

    //pick beans from can till only one is left
    while (list->size > 1) {
        coffee_can_pick(list);
    } 

    printf("The last bean is %s\n", (list->head->bean->type == BLACK ? "Black" : "White"));
}

void free_list(LinkedList *list) {
    Node *current = list->head;

    while (current != NULL) {
        Node *next = current->next;

        free(current->bean);
        free(current);

        current = next;
    }
}

int main() {
    srand(time (NULL));
 
    LinkedList list;
    init_list(&list);

    int no_blk = 0, no_wht = 0;

    for (int i = 0; i < 10; i++) {
        Bean *bean = (Bean *) malloc(sizeof(Bean));

        if (!bean) {
            fprintf(stderr, "Failed to allocate memory to bean\n");
            exit(EXIT_FAILURE);
        }

        //color of bean added is decided on whether a random number in this range is even
        //or odd
        int bw = rand() % 100;

        if (bw % 2 == 0) {
            init(bean, BLACK);
            ++no_blk;
        } else {
            init(bean, WHITE);
            ++no_wht;
        }
        add(&list, bean);
    }

    printf("Beans of colors white or black are being added to the can at random....\n");
    printf("There are %d white beans and %d black beans\n", no_wht, no_blk);

    coffee_can(&list);
    
    free_list(&list); //free allocated memory
    return 0;
}