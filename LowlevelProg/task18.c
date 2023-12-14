#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

struct list {
    int64_t value;
    struct list* next;
};

struct list* node_create(int64_t value) {
    struct list* list = malloc(sizeof(struct list));
    if (list) {
        list->value = value;
        list->next  = NULL;   
    }
    return list;
}

/*  Сгенерировать список длины sz с помощью значения init и функции f
 Результат: init, f(init), f(f(init)), ... */
struct list* list_iterate(int64_t init, size_t sz, int64_t(f)(int64_t))
{
    if (sz == 0) return NULL;
    struct list *newnode, *temp;

    struct list *head = (struct list *)malloc(sizeof(struct list));

    head->value = init; 
    head->next = NULL; 
    temp = head;    
    for(size_t i = 1; i< sz; i++)
    {
        newnode = (struct list *)malloc(sizeof(struct list));
        init = f(init);
        newnode->value = init; 
        newnode->next = NULL; 

        temp->next = newnode; 
        temp = temp->next;    
    }
    return head;
}

