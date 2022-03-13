#include <list.h>
#include <stdio.h>
#include <stdlib.h>

struct list *init_list(int (*comparator)(const void *, const void *))
{
    struct list *list = (struct list *)malloc(sizeof(struct list));
    if (list)
    {
        list->top = NULL;
        list->comparator = comparator;
        return list;
    }
    printf("Malloc allocation failed\n");
    return NULL;
};

void insert(struct list *list, void *value)
{
    struct list_element *list_point = list->top;
    struct list_element *save = NULL;
    while (list_point && list->comparator(value, list_point->value) <= 0)
    {
        save = list_point;
        list_point = list_point->next;
    }
    struct list_element *e = (struct list_element *)malloc(sizeof(struct list_element));
    if (e)
    {
        e->value = value;
        if (!list_point)
        {
            e->next = NULL;
            e->previous = save;
            if (save)
                save->next = e;
            else
                list->top = e;
        }
        else
        {
            e->next = list_point;
            e->previous = list_point->previous;
            list_point->previous = e;
            if (save)
                save->next = e;
            else
                list->top = e;
        }
    }
    else
    {
        printf("Malloc allocation failed\n");
    }
}

struct list_element *delete_element(struct list *list, int index)
{
    int i = 1;
    struct list_element *list_point = list->top;
    struct list_element *value_address = NULL;
    while (index - i && list_point)
    {
        list_point = list_point->next;
        i++;
    }
    if (list_point)
    {
        if (list_point->previous)
            list_point->previous->next = list_point->next;
        else
            list->top = list_point->next;

        if (list_point->next)
            list_point->next->previous = list_point->previous;

        value_address = list_point->value;
        free(list_point);
    }
    else
    {
        printf("No element under %d index, delete unsuccesful\n", index);
    }
    return value_address;
}

int find(struct list *list, void *value)
{
    int i = 1;
    struct list_element *list_point = list->top;
    while (list_point)
    {
        if (!list->comparator(value, list_point->value))
            return i;
        i++;
        list_point = list_point->next;
    }
    return 0;
}

void traverse(struct list *list, void (*foo)(const void *))
{
    struct list_element *e = list->top;
    while (e)
    {
        foo(e->value);
        e = e->next;
    }
}

void free_list(struct list *list, void (*remover)(void *))
{
    struct list_element *tmp1, *tmp2;
    tmp1 = list->top;

    while (tmp1)
    {
        if (remover)
            remover(tmp1->value);
        tmp2 = tmp1;
        tmp1 = tmp1->next;
        free(tmp2);
    }
    free(list);
}
