#include <list.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparator_int(const void *p, const void *q)
{
    int v1 = *(int *)p;
    int v2 = *(int *)q;

    return (v1 > v2) - (v1 < v2);
}

int comparator_string(const void *p, const void *q)
{
    char *v1 = (char *)p;
    char *v2 = (char *)q;

    return strcmp(v1, v2);
}

void remover(void *value)
{
    free(value);
}

void print_int(const void *value)
{
    printf("%d ", *(int *)value);
}

void print_string(const void *value)
{
    printf("%s ", (char *)value);
}

void insert_int(struct list *list, int values[], int nr_elements)
{
    for (int i = 0; i < nr_elements; i++)
    {
        int *value = (int *)malloc(sizeof(int));
        if (value)
        {
            *value = values[i];
            insert(list, value);
        }
        else
        {
            printf("Malloc allocation failed\n");
        }
    }
}

void insert_string(struct list *list, const char *values[], int nr_elements)
{
    for (int i = 0; i < nr_elements; i++)
    {
        char *value = (char *)malloc(sizeof(char) * (strlen(values[i]) + 1));
        if (value)
        {
            strcpy(value, values[i]);
            insert(list, value);
        }
        else
        {
            printf("Malloc allocation failed\n");
        }
    }
}

void test_int(struct list *list, int values[], int nr_elements)
{
    printf("Testing list for int values:\n");

    list = init_list(comparator_int);

    insert_int(list, values, nr_elements);

    printf("List elements: ");
    traverse(list, print_int);
    printf("\n");

    int find_test = 7;
    int index = find(list, &find_test);
    if (index)
        printf("Value %d is under index %d in the list\n", find_test, index);
    else
        printf("No value %d in the list\n", find_test);

    printf("List elements: ");
    traverse(list, print_int);
    printf("\n");

    index = 3;
    struct list_element *e = delete_element(list, index);
    if (e)
    {
        printf("Element under index %d deleted from the list\n", index);
    }
    free(e);

    printf("List elements: ");
    traverse(list, print_int);
    printf("\n");

    free_list(list, remover);
}

void test_string(struct list *list, const char *values[], int nr_elements)
{
    printf("Testing list for string values:\n");

    list = init_list(comparator_string);

    insert_string(list, values, nr_elements);

    printf("List elements: ");
    traverse(list, print_string);
    printf("\n");

    char find_test[] = "red";
    int index = find(list, &find_test);
    if (index)
        printf("Value %s is under index %d in the list\n", find_test, index);
    else
        printf("No value %s in the list\n", find_test);

    printf("List elements: ");
    traverse(list, print_string);
    printf("\n");

    index = 1;
    struct list_element *e = delete_element(list, 1);
    if (e)
    {
        printf("Element under index %d deleted from the list\n", index);
    }
    free(e);

    printf("List elements: ");
    traverse(list, print_string);
    printf("\n");

    free_list(list, remover);
}

int main()
{
    struct list *list = NULL;
    int values[] = {1, 7, 32, 32, 1, 2, 34, 4};
    const char *words[] = {"red", "blue", "green", "black", "yellow"};

    test_int(list, values, sizeof(values) / sizeof(int));

    test_string(list, words, sizeof(words) / sizeof(words[0]));

    return 0;
}
