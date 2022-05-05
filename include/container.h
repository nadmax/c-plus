#ifndef CONTAINER_H
# define CONTAINER_H

# include "object.h"
# include "iterator.h"
# include "raise.h"

typedef struct Container_s Container;

typedef IteratorClass* (*iter)(Container*);
typedef size_t (*len)(Container*);
typedef Object* (*getitem)(Container*, ...);
typedef void (*setitem)(Container*, ...);

struct Container_s {
    Class base;
    len __len__;
    iter __begin__;
    iter __end__;
    getitem __getitem__;
    setitem __setitem__;
};

# define len(c)             ((Container *)c)->__len__(c)
# define begin(c)           ((Container *)c)->__begin__(c)
# define end(c)             ((Container *)c)->__end__(c)
# define getitem(c, ...)    ((Container *)c)->__getitem__(c, __VA_ARGS__)
# define setitem(c, ...)    ((Container *)c)->__setitem__(c, __VA_ARGS__)

#endif