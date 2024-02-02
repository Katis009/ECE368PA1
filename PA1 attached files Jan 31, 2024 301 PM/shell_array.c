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
    fread(&array, sizeof(long), size, fptr);
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
    
    } while (*array != EOF);
    fclose(fptr);
    return i;
}

void Array_Shellsort(long *array, int size, long *n_comp);