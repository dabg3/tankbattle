#include <stddef.h>
#include <stdlib.h>
#include "internals.h"

void append_obj(struct mem_node **head, void *obj) {
        if (head == NULL) {
                return;
        }
        struct mem_node *new = malloc(sizeof(struct mem_node));
        new->obj = obj;
        new->next = NULL;
        struct mem_node **n = head;
        for (; *n; n = &(*n)->next) {}
        *n = new;
}

void * get_obj(struct mem_node **head, unsigned int index) {
        if (head == NULL) {
                return NULL;
        }
        struct mem_node **n = head;
        for(unsigned int i = 0; i < index && *n; n = &(*n)->next) {
                i++;
        }
        if (*n == NULL) {
                return NULL;
        }
        return (*n)->obj;
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
