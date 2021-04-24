#ifndef STRUCT_H
#define STRUCT_H

typedef struct _NODE {
    struct _NODE* next;
    int distance;
    int id;
} Node;

typedef struct _GRAPH {
    int len;
    Node** heads;
} Graph;

#endif