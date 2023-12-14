#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

enum move_dir
{
    MD_UP,
    MD_RIGHT,
    MD_DOWN,
    MD_LEFT,
    MD_NONE
};

typedef void (*move_callback) (enum move_dir);

struct node {
    move_callback value_cb;
    struct node *next;
};

struct node* node_create(move_callback valuecb) {
    struct node* node = malloc(sizeof(struct node));
    if (node) {
        node->value_cb = valuecb;
        node->next  = NULL;   
    }
    return node;
}

void cb_add_front(struct node** old, move_callback value ) {
  struct node* new = node_create(value);
  new->next = *old;
  *old = new;
  return;
}

void list_destroy(struct node *list)
{
    struct node *tmp;

    while (list != NULL)
    {
        tmp = list;
        list = list->next;
        free(tmp);
    }
}


struct robot
{
    const char *name;
    struct node *callbacks;
};


void register_callback(struct robot* robot, move_callback new_cb) {
    cb_add_front(&(robot->callbacks), new_cb);
}

void unregister_all_callbacks(struct robot* robot) {
    list_destroy(robot->callbacks);
}

void move(struct robot* robot, enum move_dir dir) {
    struct node* cb_list = robot->callbacks;
    while (cb_list)
    {
        cb_list->value_cb(dir);
        cb_list = cb_list->next;
    }
}


int main() {

}