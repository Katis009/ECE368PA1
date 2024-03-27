#include <stdlib.h>
#include <stdio.h>
#define __SEQUENCE_H__


typedef struct _Node {
   long value;
   struct _Node *next;
} Node;

void push(Node ** head, long val);
Node *arrayify(Node * head, int ind);
void exchange(Node ** head, int a, int b);
long *Generate_2p3q_Seq(int n, int *seq_size);



Node *List_Load_From_File(char *filename, int *status){  //returns head of list
   //int n = sizeof(filename)/sizeof(long); 
   Node* head = (Node*)calloc(1, sizeof(Node));
      if (head == NULL){
         *status = -1;
         return head;
      }
   FILE *fptr;
   fptr = fopen(filename, "r");
   if (fptr == NULL){
      *status = -1;
      return head;
   }
   //    fread(&array, sizeof(long), size, fptr);
   long val = 0;
   while(!feof(fptr)){
      //Node* newNode = (Node*)malloc(sizeof(Node));
      fread(&val, sizeof(long), 1, fptr);
      push(&head, val);
   }
   fclose(fptr);
   *status = 0;
   return head;

}

int List_Save_To_File(char *filename, Node *list){ // returns the number of integers successfully written to the file
   Node* curr = list;
   int size = 0;
   while (curr != NULL){
      size++;
      curr = curr->next;
   }
   FILE *fptr;
   //fptr = (FILE*)calloc(size, size * sizeof(long)); //array save to file didnt need calloc cuz fopen or frwite already allocates memory
   fptr = fopen(filename, "w");
   if (fptr == NULL){
      return -1;
   }
   int i = 0;
   do {
      fwrite(&list->value, sizeof(long), 1, fptr);
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
               n_comp++;
               if (arrayify(list, (b - gap))->value > arrayify(list, b)->value){
                  exchange(&list, (b - gap), b);
                  last_exchange = b;
                  sorted = 0;
               }
            }
         }
         r++;
      }


   }
   return list;

}

void push(Node ** head, long val) {
   Node * current = *head;
   while (current->next != NULL) {
      current = current->next;
   }

   Node* new = (Node *) calloc(1, sizeof(Node)); 
   current->next = new;    //it gives error when i put & before new so i probably dont need it. i dont use it anywhere else for this kind of thing so its not a concern at this time
   new->value = val;
   new->next = NULL;
}

Node *arrayify(Node * head, int ind){
   Node * current = head;
   for (int i = 0; i < ind; i++){
      current = current->next;
   }
   return current;
}

void exchange(Node ** head, int a, int b){
   //Node * tempBprev = arrayify(head, b - 1);
   Node * tempBprev2 = arrayify(*head, b - 2);
   //Node * tempAprev = arrayify(head, a - 1);
   Node * tempBprev = arrayify(*head, b - 1); //tempBprev2->next;
   Node * tempB = tempBprev->next;
   if (arrayify(*head, a) == *head){
      if ((b - a) == 1){
         (*head)->next = tempB->next;  //a points to c now
         tempB->next = *head; //tempB now points to a
         *head = tempB; //head is redefined to b
      }
      else{
         Node * tempA = *head; 
         (*head)->next = tempB->next;  //a points to bNext now
         tempB->next = tempA->next; //b points to aNext now
         tempBprev2->next->next = *head;   //
         *head = tempBprev->next;
      }
      
   }
   else if ((b - a) == 1){
      tempBprev->next->next = tempBprev2->next;
      arrayify(*head, a - 1)->next = tempBprev->next;
      tempBprev->next->next->next = tempB->next;
   }
   else {
      arrayify(*head, b)->next = arrayify(*head, a + 1);
      arrayify(*head, b - 1)->next = arrayify(*head, a);
      arrayify(*head, a)->next = tempB->next;
      arrayify(*head, a - 1)->next = tempBprev->next;
   }

   
   
}
