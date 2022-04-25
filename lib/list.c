#include "list.h"

void ListIterator_ctor(ListIterator* this, va_list* args)
{
    if (!this || !args)
        raise("NULL value given");
    this->_list = va_arg(*args, List) ;
    this->m_index = va_arg(*args, int);
    this->_current = this->_list->_first;
}

bool ListIterator_eq(ListIterator* this, const ListIterator* other)
{
    if (!this || !other)
        raise("NULL value given");
    return (this->m_index == other->m_index);
}

bool ListIterator_gt(ListIterator* this, const ListIterator* other)
{
    if (!this || !other)
        raise("NULL value given");
    return (this->m_index > other->m_index);
}

bool ListIterator_lt(ListIterator* this, const ListIterator* other)
{
    if (!this || !other)
        raise("NULL value given");
    return (this->m_index < other->m_index);
}

void ListIterator_incr(ListIterator* this)
{
    if (!this)
        raise("NULL value given");
    this->_current = this->_current->_next;
    this->m_index += 1;
}

Object* ListIterator_getval(ListIterator* this)
{
    if (!this)
        raise("NULL value given");
    if (this->m_index >= this->_list->_size)
        raise("Out of range");
    return (this->_current);
}

void ListIterator_setval(ListIterator* this, ...)
{
    va_list args;
    Object* obj = NULL;
    Node  node = NULL;

    if (!this)
        raise("NULL value given");
    va_start(args, this);
    node = this->_current;
    node->_type = (Class *)va_arg(va, size_t);
    obj = va_new(node->_type, &args);
    delete(node->_value);
    node->_value = obj;
    va_end(args);
}

static const ListIterator _descr = {
    {
        {
            .__size__ = sizeof(ListIterator), 
            .__name__ = "ListIterator",
            .__ctor__ = (ctor)&ListIterator_ctor,
            .__dtor__ = NULL,
            .__str__ = NULL,
            .__add__ = NULL,
            .__sub__ = NULL,
            .__mul__ = NULL,
            .__div__ = NULL,
            .__eq__ = (binary_comparator)&ListIterator_eq,
            .__gt__ = (binary_comparator)&ListIterator_gt,
            .__lt__ = (binary_comparator)&ListIterator_lt,
        },
        .__incr__ = (incr_t)&ListIterator_incr,
        .__getval__ = (getval_t)&ListIterator_getval,
        .__setval__ = (setval_t)&ListIterator_setval,
    },
    ._list = NULL,
    .m_index = 0};

static const Class* ListIterator = (const Class*)&_descr;

// ============== Nodes ==============

void Node_ctor(Node* this, va_list* args)
{
    if (!this || !args)
        raise("NULL value given");
    this->_type = va_arg(*args, Class *);
    if (!this->_type)
        raise("NULL value given");
    this->_value = va_new(this->_type, args);
}

void Node_dtor(Node* this)
{
    if (!this)
        raise("NULL value given");
    delete(this->_value);
}

char* Node_str(Node* this)
{
    if (!this)
        raise("Null value given");
    return str(this->_value);
}

void Node_set_prev(Node* this, Node* other)
{
    if (!this || !other)
        raise("NULL value given");
    this->_prev = other;
}

void Node_set_next(Node* this, Node* other)
{
    if (!this || !other)
        raise("NULL value given");
    this->_next = other;
}

void Node_set_value(Node* this, Class *type, ...)
{
    va_list va;
    Object *obj = NULL;

    if (!this || !type)
        raise("NULL value given");
    va_start(va, type);
    this->_type = type;
    obj = va_new(this->_type, &va);
    delete(this->_value);
    this->_value = obj;
    va_end(va);
}

Node* Node_get_prev(Node* this)
{
    if (!this)
        raise("NULL value given");
    return this->_prev;
}

Node* Node_get_next(Node* this)
{
    if (!this)
        raise("NULL value given");
    return this->_next;
}

Object *Node_get_value(Node* this)
{
    if (!this)
        raise("NULL value given");
    return this->_value;
}

static const Node _descr = {
    {
        .__size__ = sizeof(Node), 
        .__name__ = "Node",
        .__ctor__ = (ctor_t)&Node_ctor,
        .__dtor__ = (dtor_t)&Node_dtor,
        .__str__ = (to_string_t)&Node_str,
        .__add__ = NULL,
        .__sub__ = NULL,
        .__mul__ = NULL,
        .__div__ = NULL,
        .__eq__ = NULL,
        .__gt__ = NULL,
        .__lt__ = NULL
    },
    ._type = NULL,
    ._value = NULL,
    ._next = NULL,
    ._prev = NULL,
    .__set_prev__ = (node_set_link)&Node_set_prev,
    .__set_next__ = (node_set_link)&Node_set_next,
    .__set_value__ = (node_set_value)&Node_set_value,
    .__get_prev__ = (node_get_link)&Node_get_prev,
    .__get_next__ = (node_get_link)&Node_get_next,
    .__get_value__ = (node_get_value)&Node_get_value
};

static const Class* Node = (const Class*)&_descr;

// ============== LIST ==============

void List_ctor(List* this, va_list* args)
{
    if (!this || !args)
        raise("NULL value given");
}

void List_dtor(List* this)
{
    Node* prev = NULL;
    Node* next = NULL;

    if (!this)
        raise("NULL value given");
    prev = this->_first;
    while (prev) {
            next = prev->_next;
            delete(prev);
            prev = next;
    }
}

void list_push_front(List* this, ...)
{
    Node* new_node = NULL;
    va_list va;

    va_start(va, this);
    if (!this)
        raise("Out of Memory");
    new_node = va_new(Node, &va);
    va_end(va);
    new_node->_next = this->_first;
    this->_first = new_node;
    if (!this->_size)
        this->_last = new_node;
    else {
        this->_first->_prev = NULL;
        this->_first->_next->_prev = this->_first;
    }
    (this->_size)++;
}

void list_push_back(List* this, ...)
{
    Node* new_node = NULL;
    va_list va;

    va_start(va, this);
    if (!this)
        raise("Out of Memory");
    new_node = va_new(Node, &va);
    va_end(va);
    new_node->_prev = this->_last;
    this->_last = new_node;
    if (!this->_size)
        this->_first = new_node;
    else {
        this->_last->_next = NULL;
        this->_last->_prev->_next = this->_last;
    }
    (this->_size)++;
}

void list_pop_front(List* this)
{
    Node* old_node = NULL;

    if (!this)
        raise("Out of Memory");
    old_node = this->_first;
    if (this->_first == this->_last) {
        this->_last = NULL;
    }
    this->_first = old_node->_next;
    delete(old_node);
    if (this->_first)
        this->_first->_prev = NULL;
    this->_size--;
}

void list_pop_back(List* this)
{
    Node* old_node = NULL;

    if (!this)
        raise("Out of Memory");
    old_node = this->_last;
    if (this->_first == this->_last) {
        this->_first = NULL;
    }
    this->_last = old_node->_prev;
    delete(old_node);
    if (this->_last) {
        this->_last->_next = NULL;
    }
    this->_size--;
}

Node* List_get_at(List* this, uint32_t position)
{
    Node* node = NULL;

    if (!this)
        raise("Out of Memory");
    node = this->_first;
    for (uint32_t i = 0; i < position; i++) {
        if (!node)
            raise("Out of bounds");
        node = node->_next;
    }
    return (node);
}

size_t List_len(List* this)
{
    if (!this)
        raise("NULL value given");
    return (this->_size);
}

Iterator* List_begin(List* this)
{
    if (!this)
        raise("NULL value given");
    return (new (ListIterator, this, 0));
}

Iterator* List_end(List* this)
{
    if (!this)
        raise("NULL value given");
    return (new (ListIterator, this, this->_size));
}

Object* List_getitem(List* this, ...)
{
    va_list va;
    Node* node = NULL;
    size_t index = 0;

    if (!this)
        raise("NULL value given");
    va_start(va, this);
    index = va_arg(va, size_t);
    if (index < this->_size) {
        node = List_get_at(this, index);
        return (node->_value);
    }
    va_end(va);
    return (NULL);
}

void List_setitem(List* this, ...)
{
    size_t pos = 0;
    va_list va;
    Object *obj = NULL;
    Node* node = NULL;

    if (!this)
        raise("NULL value given");
    va_start(va, this);
    pos = va_arg(va, size_t);
    if (pos >= this->_size)
        raise("Index out of bounds");
    node = List_get_at(this, pos);
    obj = va_new(node->_type, &va);
    delete(node->_value);
    node->_value = obj;
    va_end(va);
}

char* List_str(List* this)
{
    int len = 0;
    Node* node =  NULL;
    char *str = NULL;
    Class *obj_class = NULL;
    char *res = NULL;

    if (!this)
        raise("NULL value given");

    // calculate str size
    len += snprintf(NULL, 0, "<List ()>");
    node = this->_first;
    while (node) {
        if (!node->_value)
            continue;
        obj_class = (Class *)node->_value;
        if (obj_class->__str__) {
            str = obj_class->__str__(obj_class);
            if (!str)
                raise("Out of memory");
            len += strlen(str) + 2;
            free(str);
        }
        else {
            len += snprintf(NULL, 0, "<%s>, ", obj_class->__name__);
        }
        if (!node->_next)
                len -= 2;
        node = node->_next;
    }

    // malloc str
    res = malloc(sizeof(char) * (len + 1));
    if (!res)
        raise("Out of Memory");

    // get string
    len = sprintf(res, "<List (");
    node = this->_first;
    while (node) {
        if (!node->_value)
            continue;
        obj_class = (Class *)node->_value;
        if (obj_class->__str__) {
            str = obj_class->__str__(obj_class);
            if (node->_next)
                len += sprintf(&(res[len]), "%s, ", str);
            else
                len += sprintf(&(res[len]), "%s", str);
            free(str);
        }
        else {
            if (node->_next)
                len += sprintf(&(res[len]), "<%s>, ", obj_class->__name__);
            else
                len += sprintf(&(res[len]), "<%s>", obj_class->__name__);
        }
        node = node->_next;
    }
    len += sprintf(&(res[len]), ")>");
    res[len] = '\0';
    return res;
}

static const List _descr = {
    {
        {
            .__size__ = sizeof(List), 
            .__name__ = "List",
            .__ctor__ = (ctor)&List_ctor,
            .__dtor__ = (dtor)&List_dtor,
            .__str__ = (to_string)&List_str,
            .__add__ = NULL,
            .__sub__ = NULL,
            .__mul__ = NULL,
            .__div__ = NULL,
            .__eq__ = NULL,
            .__gt__ = NULL,
            .__lt__ = NULL,
        },
        .__len__ = (len_t)&List_len,
        .__begin__ = (iter_t)&List_begin,
        .__end__ = (iter_t)&List_end,
        .__getitem__ = (getitem_t)&List_getitem,
        .__setitem__ = (setitem_t)&List_setitem,
    },
    ._size = 0,
    ._first = NULL,
    ._last = NULL,
    .__push_front__ = (list_front_push)&list_push_front,
    .__push_back__ = (list_back_push)&list_push_back,
    .__pop_front__ = (list_front_pop)&list_pop_front,
    .__pop_back__ = (list_back_pop)&list_pop_back,
    .__get_at__ = (list_get_value)&List_get_at
};

const Class* List = (const Class*)&_descr;