#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>


struct list {
    int64_t value;
    struct list* next;
};

void print_int64(int64_t i);


struct list* node_create(int64_t value) {
    struct list* list = malloc(sizeof(struct list));
    if (list) {
        list->value = value;
        list->next  = NULL;   
    }
    return list;
}

int64_t abs_int64(int64_t x) {
    return abs(x);
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


struct list* list_map(const struct list* l, int64_t (f) (int64_t))  {
    if(l == NULL) {
        return NULL;
    } else {
        struct list* newlist = (struct list*) malloc(sizeof(struct list));
        newlist->value = f(l->value);
        newlist->next = list_map(l->next, f);
        return newlist;
    }
}

struct list* list_copy( const struct list *l ) {
    if(l == NULL) {
        return NULL;
    } else {
        struct list* newlist = (struct list*) malloc(sizeof(struct list));
        newlist->value = l->value;
        newlist->next = list_copy(l->next);
        return newlist;
    }
}


struct list* list_abs(const struct list* l ) {
    struct list* newlist = list_map(l, abs_int64);
    return newlist;
}

int main() {
    struct list* list;
    list = node_create(-11111);
    list_add_back(&list, -2);
    list_add_back(&list, -3);
    

    struct list* tmp = list_abs(list);
    while (tmp) {
        printf("%  " PRId64, tmp->value);
        tmp = tmp->next;
    }
}