#include <stdlib.h>
#include <stdio.h>

typedef struct _Node {
   long value;
   struct _Node *next;
} Node;

void push(Node * head, long val);
long arrayify(Node * head, int ind);


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
   fclose(fptr);
   *status = 0;
   return &head;

}

int List_Save_To_File(char *filename, Node *list){
   FILE *fptr;
   fptr = fopen(*filename, "w");
   if (fptr == NULL){
      return -1;
   }
   int i = 0;
   do {
      fwrite(list->value, sizeof(long), 1, fptr);
      list = list->next;
      i++;
    
   } while (list != NULL);
   fclose(fptr);
   return i;
}

Node *List_Shellsort(Node *list, long *n_comp){
   *n_comp = 0;
   int seq_size;
   long* sequence;
   Node* curr = list;
   int n = 0;
   while (curr != NULL){
      n++;
      curr = curr->next;
   }
   sequence = Generate_2p3q_Seq(n, &seq_size);  //generate sequence of gap values

   long gap;
   for (int seqInd = seq_size - 1; seqInd >= 0; seqInd--){
      gap = sequence[seqInd];


   }

}

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

long arrayify(Node * head, int ind){
   Node * current = head;
   for (int i = 0; i < ind; i++){
      current = current->next;
   }
   return current->value;
}