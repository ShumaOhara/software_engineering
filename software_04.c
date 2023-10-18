#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUCKETSIZE 9
#define DELTA 2

struct Table{
    int value;
    int num;
    int state;
};

void init(int i, struct Table *table){
    table[i].num = i;
    table[i].value = -1;
    table[i].state = 0;
}

void printtable(struct Table *table){
    for(int i = 0; i < BUCKETSIZE; i++){
        printf("%d, %d, %d\n", table[i].num, table[i].value, table[i].state);
    }
}

int insert(int value, struct Table *table){
    int i = value % BUCKETSIZE;
    for(int j = 0; j < BUCKETSIZE; j++){
        if(table[i].state == 0 || table[i].state == 2){
            table[i].state = 1;
            table[i].value = value;
            return 0;
        }
        i = i + DELTA;
    }
    return 1;
}

int search(int value, struct Table *table){
    int i = value % BUCKETSIZE;
    for(int j = 0; j < BUCKETSIZE; j++){
        if(table[i].value == value){
            printf("%d is in No.%d\n", value, table[i].num);
            return 0;
        }
        i = i + DELTA;
    }
    return 1;
}

int main(){
    struct Table *table;
    int data[] = {15, 13, 14, 1, 7, 0, 9, 2, 3};
    table = malloc(BUCKETSIZE * sizeof(struct Table));
    for(int i = 0; i < BUCKETSIZE; i++){
        init(i, table);
    }
    for(int i = 0; i < BUCKETSIZE; i++){
        insert(data[i], table);
    }
    printtable(table);
    for(int i = 0; i < BUCKETSIZE; i++){
        search(data[i], table);
    }
    return 0;
}