#include <stdlib.h>
#include <stdio.h>

typedef struct _Node {
   long value;
   struct _Node *next;
} Node;

void push(Node * head, long val);

Node *List_Load_From_File(char *filename, int *status){
   int n = sizeof(filename)/sizeof(long); 
   Node* head = (Node*)malloc(sizeof(Node));
      if (head == NULL){
         int *status = -1;
         return &head;
      }
   FILE *fptr;
   fptr = fopen(*filename, "r");
   if (fptr == NULL){
      int *status = -1;
      return &head;
   }
   //    fread(&array, sizeof(long), size, fptr);
   long val;
   while(!feof(fptr)){
      //Node* newNode = (Node*)malloc(sizeof(Node));
      fread(val, sizeof(long), 1, fptr);
      push(head, val);
   }
   *status = 0;
   return &head;

}

int List_Save_To_File(char *filename, Node *list);

Node *List_Shellsort(Node *list, long *n_comp);

void push(Node * head, long val) {
    Node * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = (Node *) malloc(sizeof(Node));
    if (current->next == NULL){
         int *status = -1;
         return &current->next;
      }
    current->next->value = val;
    current->next->next = NULL;
}