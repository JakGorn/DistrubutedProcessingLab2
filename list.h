#ifndef _LIST_H_
#define _LIST_H_

struct list_element
{
    void *value;
    struct list_element *next;
    struct list_element *previous;
};

struct list
{
    struct list_element *top;
    int (*comparator)(const void *v1, const void *v2);
};

struct list *init_list(int (*comparator)(const void *, const void *));

void insert(struct list *list, void *value);

struct list_element *delete_element(struct list *list, int index);

int find(struct list *list, void *value);

void traverse(struct list *list, void (*foo)(const void *));

void free_list(struct list *list, void (*remover)(void *));

#endif // _LIST_H_