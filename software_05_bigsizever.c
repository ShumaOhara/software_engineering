/* insertion sort (size 1000000 ver.) */
/* 動かすと僕のPCは固まるので動かす時は変数いじってから！！ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DATASIZE 50

int sort(int *data){
    for(int i = 1; i < DATASIZE; i++){
        int key = data[i];
        for(int j = i; j >= 0; j--){
            if(key < data[j-1]){
                data[j] = data[j-1];
                data[j-1] = key;
            }
        }
        for(int a = 0; a < DATASIZE; a++){
            printf("%d ", data[a]);
            }
        printf("\n");
    }
    return 0;
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
    sort(data);
    return 0;
}