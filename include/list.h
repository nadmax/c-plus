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

struct Node_s
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
};

struct List_s
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
};

typedef struct ListIterator_s
{
    Iterator base;
    List* m_list;
    Node* m_current;
    size_t m_index;
} ListIterator;

void ListIterator_ctor(ListIterator*, va_list*);
bool ListIterator_eq(ListIterator*, const ListIterator*);
bool ListIterator_gt(ListIterator*, const ListIterator*);
bool ListIterator_lt(ListIterator*, const ListIterator*);
void ListIterator_incr(ListIterator*);
Object* ListIterator_getval(ListIterator*);
void ListIterator_setval(ListIterator*, ...);

void Node_ctor(Node*, va_list*);
void Node_dtor(Node*);
char* Node_str(Node*);
void Node_set_prev(Node*, Node*);
void Node_set_next(Node*, Node*);
void Node_set_value(Node*, Class*, ...);
Node* Node_get_prev(Node*);
Node* Node_get_next(Node*);
Object *Node_get_value(Node*);

void List_ctor(List*, va_list*);
void List_dtor(List*);
void list_push_front(List*, ...);
void list_push_back(List*, ...);
void list_pop_front(List*);
void list_pop_back(List*);
Node* List_get_at(List*, uint32_t);
size_t List_len(List*);
Iterator* List_begin(List*);
Iterator* List_end(List*);
Object* List_getitem(List*, ...);
void List_setitem(List*, ...);
char* List_str(List*);

#endif