struct mem_node {
        void *obj;
        struct mem_node *next;
};

void append_obj(struct mem_node **head, void *obj);
struct mem_node * remove_node(struct mem_node **head, struct mem_node *node);

/**
 * apply `fn` to all elements
 *
 * `fn` may free its parameter
 */
void apply(struct mem_node **head, void (*fn)(void *obj));

/**
 * remove nodes with mem_node->obj == NULL
 */
void collect_garbage(struct mem_node **head);
