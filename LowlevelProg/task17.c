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

void list_add_front(struct list **old, int64_t value)
{
    struct list *new = node_create(value);
    new->next = *old;
    *old = new;
    return;
}

void list_add_back(struct list **old, int64_t value)
{
    if (*old == NULL) {
        list_add_front(old, value);
        return;
    }
    struct list* last = *old;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = node_create(value);

}

static int64_t sum( int64_t x, int64_t y) { return x + y; }

typedef int64_t folding(int64_t, int64_t);

/* Свернуть список l с помощью функции f. */
int64_t list_fold(
        const struct list* l, 
        int64_t init, 
        folding f) {
    int64_t result = init;
    const struct list* tmp = l;
    while (tmp) {
        result = f(result, tmp->value);
        tmp = tmp->next;
    }
    return result;
}

/* Просуммируйте список с помощью list_fold и sum */
int64_t list_sum( const struct list* l ) {
    int64_t init = 0;
    return list_fold(l, init, sum);
    
}

int main() {
    struct list* list;
    list = node_create(1);
    list_add_back(&list, 2);
    list_add_back(&list, 3);
    printf("%" PRId64, list_sum(list));
}

