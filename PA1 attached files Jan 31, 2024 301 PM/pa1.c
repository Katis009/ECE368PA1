#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define __SEQUENCE_H__
#define __SHELL_ARRAY_H__
#define __SHELL_LIST_H__

long *Array_Load_From_File(char *filename, int *size);
int Array_Save_To_File(char *filename, long *array, int size);
void Array_Shellsort(long *array, int size, long *n_comp);

typedef struct _Node {
   long value;
   struct _Node *next;
} Node;

Node *List_Load_From_File(char *filename, int *status);
int List_Save_To_File(char *filename, Node *list);
Node *List_Shellsort(Node *list, long *n_comp);


int main(int argc, char* argv[]){

    int size;
    char* filename = argv[2];
    char* outFile = argv[3];
    char* flag = argv[1];
    int ifA = strcmp(flag, "-a");
    int ifL = strcmp(flag, "-l");
    if (ifA == 0){
        long* array =  Array_Load_From_File(filename, &size);
        if (array == NULL){
            exit(EXIT_FAILURE);
        }
        long n_comp;
        Array_Shellsort(array, size, &n_comp);
        printf("%ld\n", n_comp);
        int arrayLength = Array_Save_To_File(outFile, array, size);  //does outFile need a & in front of it?? idk??
        if (size == arrayLength){
            printf("size = arrayLength\n");
        }
        else{
            printf("sizes arent same\n");
        }

    }
    else if (ifL == 0){
        int status;
        Node* head = List_Load_From_File(filename, &status);   //filename and status might need a * or & in front of them idk
        if (status == -1){
            exit(EXIT_FAILURE);
        }
        long n_comp;
        head = List_Shellsort(head, &n_comp);
        printf("%ld\n", n_comp);
        int listLength = List_Save_To_File(outFile, head);
        
        
    }

    
    return 0;
}
