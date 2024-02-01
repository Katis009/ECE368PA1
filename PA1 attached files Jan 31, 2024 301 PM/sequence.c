long *Generate_2p3q_Seq(int n, int *seq_size){

    int q = 0;
    int p = 0;
    while (3^q < n){
        q++;
    }
    int qStar = q - 1;
    while (2^p < n){
        p++;
    }
    int pStar = p - 1;
    int maxSize = (((qStar + 2)*(qStar + 1))/2)+((pStar - qStar + 1)*(pStar - qStar));
    int array[maxSize];


}
