#include <stdlib.h>

long exponent(long x, long y);


long *Generate_2p3q_Seq(int n, int *seq_size){

    long q = 0;
    long p = 0;
    while (exponent(3, q) < n){
        q++;
    }
    long qStar = q - 1;
    while (exponent(2, p) < n){
        p++;
    }
    long pStar = p - 1;
    //long maxSize = (((qStar + 2)*(qStar + 1))/2)+((pStar - qStar + 1)*(pStar - qStar));
    long* array;
    array = (long*)malloc(0 * sizeof(long));
    if (array == NULL){
        int *seq_size = 0;
        return NULL;
    }
    long i = 0;
    for (q = 0; q <= qStar; q++){
        for (p = 0; p <= pStar; p++){
            if (((exponent(2, p))*(exponent(3, q))) < n){
                array = (long*)realloc(array, sizeof(long) * (i + 1));  // should check that realloc is working right here. but cant check if array == NULL because it was already malloc-ed earlier
                array[i] = exponent(2, p) * exponent(3, q);
                i++;
            }
            else{
                p = pStar;
            }
        }
    }
    int *seq_size = i;
    //long* array2;
    //array2 = (long*)malloc(i * sizeof(long));

    //Sort array using insertion sort
    long j = 1;
    long x = 0;
    long b = 0;
    while (j < length(array)){
        x = array[j];
        b = j;
        while ((b > 0) && (array[b - 1] > x)){
            array[b] = array[b - 1];
            b--;
        }
        array[b] = x;
        j++;
    }

    //array2 = array;

    //return &array;
    return &array;

}

long exponent(long x, long y){
    long z = x;
    for (long i = 1; i < y; i++){
        z *= x;
    }
    return z;
}
