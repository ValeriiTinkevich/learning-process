#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>

struct maybe_int64
{
    bool valid;
    int64_t value;
};

struct maybe_int64 some_int64(int64_t i)
{
    return (struct maybe_int64){.value = i, .valid = true};
}

const struct maybe_int64 none_int64 = {0};

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

size_t list_length(struct list const *list)
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
    if (*old == NULL)
    {
        list_add_front(old, value);
        return;
    }
    struct list *last = *old;
    while (last->next != NULL)
    {
        last = last->next;
    }
    last->next = node_create(value);
}

int64_t list_sum(const struct list *list)
{
    int64_t sum;
    for (sum = 0; list; list = list->next)
        sum += list->value;
    return sum;
}

struct maybe_int64 list_at(const struct list *list, size_t idx)
{
    size_t length = list_length(list);
    if (idx >= length || list == NULL)
    {
        return none_int64;
    }
    if (idx == 0)
    {
        return some_int64(list->value);
    }
    for (size_t i = 0; i < length; i++)
    {
        if (i == idx)
        {
            return some_int64(list->value);
        }
        list = list->next;
    }
    return none_int64;
}

struct list *list_reverse(const struct list *list)
{
    struct list *copy_list = NULL;
    if (list == NULL)
        return NULL;
    while (list)
    {
        list_add_front(&copy_list, list->value);
        list = list->next;
    }

    return copy_list;
}

struct maybe_int64 maybe_read_int64()
{
    int64_t value;
    if (scanf("%" SCNd64, &value) > 0)
    {
        return some_int64(value);
    }
    else
    {
        return none_int64;
    }
}

struct list* list_read() {
    struct maybe_int64 value = maybe_read_int64();
    if (value.valid) {
        struct list* start = node_create(value.value);
        struct list* startcpy = start;
        struct maybe_int64 value = maybe_read_int64();
        while (value.valid)
        {
            startcpy->next = node_create(value.value);
            startcpy = startcpy->next;
            value = maybe_read_int64();
        }
        return start;
    }
    return NULL;
}


int main()
{
    struct list* start = list_read();
    printf("% " PRId64, start->value);
    printf("% " PRId64, start->next->value);
}
