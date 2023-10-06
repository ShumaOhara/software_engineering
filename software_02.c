#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct list{
    struct list *next;
    int data;
};

int main(){
    struct list *p, *q, *head;
    p = malloc(sizeof(struct list));
    p->data = 1;
    head = p;
    for(int i = 2; i <= 100; i++){
        q = malloc(sizeof(struct list));
        q->data = i;
        p->next = q;
        p = q;
        q = q->next;
    }
    q = NULL;
    while(head != NULL){
        printf("%d ", head->data);
        head = head->next;
    }
    return 0;
}