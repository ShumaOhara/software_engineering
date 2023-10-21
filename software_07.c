/* count sort */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DATASIZE 8

void countsort(int* data, int* result, int max){
    int villa[max];
    for(int i = 0; i <= max; i++){
        villa[i] = 0;
    }
    for(int i = 0; i < DATASIZE; i++){
        for(int j = data[i]; j <= max; j++){
            villa[j] += 1;
        }
    }
    for(int i = 0; i <= max; i++){
        printf("%d ", villa[i]);
    }
    printf("\n");
    for(int i = DATASIZE; i > 0; i--){
        result[villa[data[i]]] = data[i];
        villa[data[i]] -= 1;
    }
    return;
}

int main(){
    int data[] = {2, 5, 3, 0, 2, 3, 0, 3};
    for(int i = 0; i < DATASIZE; i++){
        printf("%d ", data[i]);
    }
    printf("\n");
    int result[DATASIZE-1];
    int max;
    for(int i = 0; i < DATASIZE; i++){
        if(data[i] > max){
            max = data[i];
        }
    }
    countsort(data, result, max);
    return 0;
}