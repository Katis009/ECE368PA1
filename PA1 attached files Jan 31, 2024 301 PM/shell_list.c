#include <stdlib.h>
#include <stdio.h>

typedef struct _Node {
   long value;
   struct _Node *next;
} Node;

void push(Node * head, long val);
Node *arrayify(Node * head, int ind);
void exchange(Node * head, int a, int b);


Node *List_Load_From_File(char *filename, int *status){  //returns head of list
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

int List_Save_To_File(char *filename, Node *list){ // returns the number of integers successfully written to the file
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
      int r = 0;
      int last_element;
      int sorted = 0;
      int last_exchange = n;
      while((r < gap) && ((r + gap) < n)){
         while (sorted == 0){
            sorted = 1;
            last_element = last_exchange - 1;
            for (int b = gap + r; b <= last_element; b += gap){
               *n_comp++;
               if (arrayify(list, (b - gap))->value > arrayify(list, b)->value){
                  exchange(list, (b - gap), b);
                  last_exchange = b;
                  sorted = 0;
               }
            }
         }
         r++;
      }


   }
   return 

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

Node *arrayify(Node * head, int ind){
   Node * current = head;
   for (int i = 0; i < ind; i++){
      current = current->next;
   }
   return &current;
}

void exchange(Node * head, int a, int b){
   //Node * tempBprev = arrayify(head, b - 1);
   Node * tempBprev2 = arrayify(head, b - 2);
   //Node * tempAprev = arrayify(head, a - 1);
   Node * tempBprev = tempBprev2->next;
   Node * tempB = tempBprev->next;
   if (arrayify(head, a) == head){
      if ((b - a) == 1){
         head->next = tempB->next;
         tempBprev->next->next = head;
         head = tempBprev->next;
      }
      else{
         Node * tempA = head; 
         head->next = tempB->next;
         tempBprev->next->next = tempA->next;
         tempBprev2->next->next = head;
         head = tempBprev->next;
      }
      
   }
   else if ((b - a) == 1){
      tempBprev->next->next = tempBprev2->next;
      arrayify(head, a - 1)->next = tempBprev->next;
      tempBprev->next->next->next = tempB->next;
   }
   else {
      arrayify(head, b)->next = arrayify(head, a + 1);
      arrayify(head, b - 1)->next = arrayify(head, a);
      arrayify(head, a)->next = tempB->next;
      arrayify(head, a - 1)->next = tempBprev->next;
   }

   
   
}