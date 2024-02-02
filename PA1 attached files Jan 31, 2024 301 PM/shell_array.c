#include <stdlib.h>
#include <stdio.h>

long *Array_Load_From_File(char *filename, int *size){
    *size = (sizeof(filename)/sizeof(long));
    long* array;
    array = (long*)malloc(sizeof(filename));
    if (array == NULL){
        int *size = 0;
        return NULL;
    }
    FILE *fptr;
    fptr = fopen(*filename, "r");
    if (fptr == NULL){
        int *size = 0;
        return NULL;
    }
    int nRead = fread(&array, sizeof(long), size, fptr);
    if (nRead != size){
        fprint("ERROR -> Array_Load_From_File: fread did not read the same number of elements as size"); //DELETE THIS BEFORE SUBMITTING YOU WILL LOSE POINTS
    }
    fclose(fptr);
    return &array;

}

int Array_Save_To_File(char *filename, long *array, int size){
    FILE *fptr;
    fptr = fopen(*filename, "w");
    if ((fptr == NULL) || (*array == NULL)){
        return -1;
    }
    int i = 0;
    do {
        fwrite(*array, sizeof(long), 1, fptr);
        i++;
    
    } while (*array != EOF); // fptr was *array it seemed wrong so i changed it but maybe it was that way for a reason idk
    fclose(fptr);
    return i;
}

void Array_Shellsort(long *array, int size, long *n_comp){

    *n_comp = 0;
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
                        *n_comp++;
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