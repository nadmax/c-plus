#ifndef ITERATOR_H
#define ITERATOR_H

#include "object.h"
#include "raise.h"

typedef struct Iterator_s IteratorClass;
typedef void (*incr_t)(IteratorClass*);
typedef Object* (*getval_t)(IteratorClass* this);
typedef void (*setval_t)(IteratorClass*, ...);

struct Iterator_s
{
    Class base;
    incr_t __incr__;
    getval_t __getval__;
    setval_t  __setval__;
};

#define incr(it)           ((Iterator*)it)->__incr__(it)
#define getval(it)         ((Iterator*)it)->__getval__(it)
#define setval(it, ...)    ((Iterator*)it)->__setval__(it, __VA_ARGS__)

#endif