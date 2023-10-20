/*insertion sort */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DATASIZE 12

int sort(int *array){
    for(int i = 1; i < DATASIZE; i++){
        int key = array[i];
        for(int j = i; j >= 0; j--){
            if(key < array[j-1]){
                array[j] = array[j-1];
                array[j-1] = key;
            }
        }
        for(int a = 0; a < DATASIZE; a++){
                printf("%d ", array[a]);
            }
        printf("\n");
    }
    return 0;
}

int main(){
    int data[DATASIZE] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
    sort(data);
    return 0;
}