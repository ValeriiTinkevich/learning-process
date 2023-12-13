#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>

struct list
{
    int64_t value;
    struct list *next;
};

struct list *node_create(int64_t value)
{
    struct list *list = malloc(sizeof(struct list));
    if (list)
    {
        list->value = value;
        list->next = NULL;
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

size_t list_length(struct list *list)
{
    struct list *current_ptr = (struct list *)list;
    size_t counter = 0;
    while (current_ptr != NULL)
    {
        current_ptr = current_ptr->next;
        counter++;
    }
    return counter;
}

void list_destroy(struct list *list)
{
    struct list *tmp;

    while (list != NULL)
    {
        tmp = list;
        list = list->next;
        free(tmp);
    }
}

struct list *list_last(struct list *list)
{
    if (list == NULL)
        return NULL;
    while (list->next != NULL)
    {
        list = list->next;
    }
    return list;
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

int main()
{
    struct list *a = node_create(1);
    list_add_front(&a, 2);
    printf("%" PRId64, a->value);
}
