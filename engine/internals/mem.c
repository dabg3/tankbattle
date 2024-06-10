#include <stddef.h>
#include <stdlib.h>
#include "internals.h"

//struct mem_node *textures_head; //better let user manage textures?
//struct mem_node *render_objs_head;
//struct mem_node *game_objs_head;

void append_obj(struct mem_node **head, void *obj) {
        if (head == NULL) {
                return;
        }
        struct mem_node *new = malloc(sizeof(struct mem_node));
        new->obj = obj;
        struct mem_node **n = head;
        for (; *n; n = &(*n)->next) {}
        *n = new;
}

struct mem_node * remove_node(struct mem_node **head, struct mem_node *node) {
        if (head == NULL) {
                return NULL;
        }
        struct mem_node **n = head;
        for (; *n && *n != node; n = &(*n)->next) {}
        if (*n == NULL) {
                return NULL;
        }
        struct mem_node *found = *n;
        *n = found->next;
        free(found);
        return *n;
}

void apply(struct mem_node **head, void (*fn)(void *obj)) {
        if (head == NULL) {
                return;
        }
        struct mem_node **n = head;
        while (*n) {
                fn((*n)->obj);
                n = &(*n)->next;
        }
}

void collect_garbage(struct mem_node **head) {
        if (head == NULL) {
                return;
        }
        struct mem_node **n = head;
        while (*n) {
                if ((*n)->obj == NULL) {
                        *n = remove_node(n, *n);
                } else {
                        n = &(*n)->next;
                }
        }
}
