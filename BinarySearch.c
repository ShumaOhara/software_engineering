#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int a[] = {5, 7, 15, 18, 22, 35, 40, 48, 50, 54, 60, 62, 68, 70, 77, 80, 85, 88, 90, 96};

int binary_search(int K, int m, int n){
    int i, j, p;
    i = m; j = n;
    while(i <= j){
        p = (i+j)/2;
        if(K < a[p]) j = p-1;
        else if(K > a[p]) i = p+1;
        else if(K == a[p]){
            return p;
        }
    }
    return -1;
}

int main(){
    printf("%d", a[binary_search(50, 0, 18)]);
    return 0;
}
