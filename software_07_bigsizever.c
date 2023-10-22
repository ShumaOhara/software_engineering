/* count sort (size 1000000 ver.) */
/* 動かすと僕のPCは固まるので動かす時は変数いじってから！！ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DATASIZE 50

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
    for(int i = DATASIZE-1; i >= 0; i--){
        result[villa[data[i]]-1] = data[i];
        villa[data[i]] -= 1;
    }
    return;
}

int main(){
    int *data = (int *)malloc(DATASIZE * sizeof(int));
    for(int i = 0; i < DATASIZE; i++){
        data[i] = (rand() % DATASIZE);
    }
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
    printf("Max:%d\n", max);
    countsort(data, result, max);
    for(int i = 0; i < DATASIZE; i++){
        printf("%d ", result[i]);
    }
    printf("\n");
    return 0;
}