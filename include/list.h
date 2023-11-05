#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include "container.h"
#include "iterator.h"
#include "raise.h"
#include "new.h"
#include "int.h"
#include "delete.h"

typedef struct Node_s NodeClass;
typedef struct List_s ListClass;

extern const Class* List;

typedef void (*set_link)(NodeClass*, NodeClass*);
typedef void (*set_value)(NodeClass*, NodeClass*);
typedef NodeClass* (*get_link)(NodeClass*);
typedef Object* (*node_get_value)(NodeClass*);
typedef void (*push_front)(ListClass*, ...);
typedef void (*push_back)(ListClass*, ...);
typedef void (*pop_front)(ListClass*);
typedef void (*pop_back)(ListClass*);
typedef NodeClass* (*list_get_value)(ListClass*, uint32_t);

struct Node_s
{
    Class class;
    Class* m_type;
    Object* m_value;
    NodeClass* m_next;
    NodeClass* m_prev;
    set_link __set_prev__;
    set_link __set_next__;
    set_value __set_value__;
    get_link __get_prev__;
    get_link __get_next__;
    node_get_value __get_value__;
};

struct List_s
{
    Container base;
    size_t m_size;
    NodeClass* m_head;
    NodeClass* m_tail;
    push_front __push_front__;
    push_back __push_back__;
    pop_front __pop_front__;
    pop_back __pop_back__;
    list_get_value __get_at__;
};

typedef struct
{
    IteratorClass base;
    ListClass* m_list;
    NodeClass* m_current;
    size_t m_index;
} ListIteratorClass;

void ListIterator_ctor(ListIteratorClass*, va_list*);
bool ListIterator_eq(ListIteratorClass*, const ListIteratorClass*);
bool ListIterator_gt(ListIteratorClass*, const ListIteratorClass*);
bool ListIterator_lt(ListIteratorClass*, const ListIteratorClass*);
void ListIterator_incr(ListIteratorClass*);
Object* ListIterator_getval(ListIteratorClass*);
void ListIterator_setval(ListIteratorClass*, ...);

void Node_ctor(NodeClass*, va_list*);
void Node_dtor(NodeClass*);
char* Node_str(NodeClass*);
void Node_set_prev(NodeClass*, NodeClass*);
void Node_set_next(NodeClass*, NodeClass*);
void Node_set_value(NodeClass*, Class*, ...);
NodeClass* Node_get_prev(NodeClass*);
NodeClass* Node_get_next(NodeClass*);
Object *Node_get_value(NodeClass*);

void List_ctor(ListClass*, va_list*);
void List_dtor(ListClass*);
void list_push_front(ListClass*, ...);
void list_push_back(ListClass*, ...);
void list_pop_front(ListClass*);
void list_pop_back(ListClass*);
NodeClass* List_get_at(ListClass*, uint32_t);
size_t List_len(ListClass*);
ListIteratorClass* List_begin(ListClass*);
ListIteratorClass* List_end(ListClass*);
Object* List_getitem(ListClass*, ...);
void List_setitem(ListClass*, ...);
char* List_str(ListClass*);

#endif