/* quick sort */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DATASIZE 12

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
}

int main(){
    int data[] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
    for(int i = 0; i < DATASIZE; i++){
        printf("%d ", data[i]);
    }
    printf("\n");
    quicksort(data, 0, DATASIZE-1);
    for(int i = 0; i < DATASIZE; i++){
        printf("%d ", data[i]);
    }
    return 0;
}
