#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include "raise.h"
#include "list.h"
#include "new.h"
#include "int.h"

typedef struct Node_s Node;
typedef struct List_s List;

extern const Class* List;

typedef void (*set_link)(Node*, Node*);
typedef void (*set_value)(Node*, Node*);
typedef Node* (*get_link)(Node*);
typedef Object* (*get_value)(Node*);

typedef void (*push_front)(List*, ...);
typedef void (*push_back)(List*, ...);
typedef void (*pop_front)(List*);
typedef void (*pop_back)(List*);
typedef Node* (*get_value)(List*, uint32_t);

typedef struct Node_s
{
    Class class;
    Class* m_type;
    Object* m_value;
    Node* m_next;
    Node* m_prev;

    set_link __set_prev__;
    set_link __set_next__;
    set_value __set_value__;
    get_link __get_prev__;
    get_link __get_next__;
    get_value __get_value__;
} Node;

typedef struct List_s
{
    Container base;
    size_t m_size;
    Node* m_head;
    Node* m_tail;

    push_front __push_front__;
    push_back __push_back__;
    pop_front __pop_front__;
    pop_back __pop_back__;
    get_value __get_at__;
} List;

typedef struct ListIterator_s
{
    Iterator base;
    List* m_list;
    Node* m_current;
    size_t m_index;
} ListIterator;

#endif