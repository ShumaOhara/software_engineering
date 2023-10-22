/* quick sort (size 1000000 ver.) */
/* 動かすと僕のPCは固まるので動かす時は変数いじってから！！ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DATASIZE 50

int partition(int **data, int head, int end){
    int key = (*data)[end];
    int count = head -1;
    for(int i = head; i < end; i++){
        if((*data)[i] <= key){
            count += 1;
            int lock = (*data)[i];
            (*data)[i] = (*data)[count];
            (*data)[count] = lock;
        }
    }
    (*data)[end] = (*data)[count+1];
    (*data)[count+1] = key;
    for(int j = 0; j < DATASIZE; j++){
        printf("%d ", (*data)[j]);
    }
    printf("\n");
    return count+1;
}

void quicksort(int *data, int head, int end){
        if(end - head > 0){
        int p = partition(&data, head, end);
        quicksort(data, head, p-1);
        quicksort(data, p+1, end);
    }
    return;
}

int main(){
    int *data = (int *)malloc(DATASIZE * sizeof(int));
    for(int i = 0; i < DATASIZE; i++){
        data[i] = (rand() % DATASIZE);
    }
    quicksort(data, 0, DATASIZE-1);
    for(int i = 0; i < DATASIZE; i++){
        printf("%d ", data[i]);
    }
    printf("\n");
    return 0;
}