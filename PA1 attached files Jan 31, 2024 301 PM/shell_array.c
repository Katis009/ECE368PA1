#include <stdlib.h>
#include <stdio.h>
#define __SEQUENCE_H__
long *Generate_2p3q_Seq(int n, int *seq_size);

long *Array_Load_From_File(char *filename, int *size){
    //array = (long*)calloc(n, n * sizeof(long));     //fseek ftell

    FILE *fptr;
    fptr = fopen(filename, "r");
    if (fptr == NULL){
        *size = 0;
        return NULL;
    }

    fseek(fptr, 0, SEEK_END);
    long len = ftell(fptr);
    long n = len / 4;   //a long is 4 bytes and len is the number of bytes in fptr

    long* array;
    array = (long*)calloc(n, n * sizeof(long));
    if (array == NULL){
        *size = 0;
        return NULL;
    }

    fread(array, sizeof(long), n, fptr);    //returned value used to be nRead. it doesnt say to comparre that w size so i just changed it to size
    
    //size = sizeof(array)/sizeof(long);
    *size = (int) n;
    fclose(fptr);
    return array;

}

int Array_Save_To_File(char *filename, long *array, int size){
    FILE *fptr;
    //fptr = (FILE*)calloc(size, size * sizeof(long));
    fptr = fopen(filename, "w");
    if (fptr == NULL){
        return -1;
    }
    if (array == NULL){
        return -1;
    }
    int i = 0;
    do {
        fwrite(array, sizeof(long), 1, fptr);
        i++;
    
    } while (i < size); 
    fclose(fptr);
    return i;
}

void Array_Shellsort(long *array, int size, long *n_comp){

    n_comp = 0;
    //long *Generate_2p3q_Seq(int n, int *seq_size)
    int seq_size;
    long* sequence;
    //sequence = (long*)malloc(sizeof(long) * seq_size); // seq_size is not initialized yet here
    sequence = Generate_2p3q_Seq(size, &seq_size);

    long gap;
    for (int seqInd = seq_size - 1; seqInd >= 0; seqInd--){
        gap = sequence[seqInd];
    
        //for (int i = gap; i < size; i += 1){
        //    long temp = array[i];


            long curr;
            int last_element;
            int sorted = 0;
            int last_exchange = size;
            int r = 0;
            while ((r < gap) && ((r + gap) < size)){
                

                while (sorted == 0){
                    sorted = 1;
                    last_element = last_exchange - 1;
                    for (int b = gap + r; b <= last_element; b += gap){
                        n_comp++;
                        if (array[b - gap] > array[b]){
                            curr = array[b];
                            array[b] = array[b - gap];
                            array[b - gap] = curr;
                            last_exchange = b;
                            sorted = 0;
                        }
                    }
                }
                r++;
            }
            /*
            long j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap){
                array[j] = array[j - gap];
                *n_comp++;
            }
            *n_comp++;
            array[j] = temp;
            */
        //}
    }
}
