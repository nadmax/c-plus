#ifndef ITERATOR_H
#define ITERATOR_H

#include "object.h"
#include "raise.h"

typedef struct Iterator_s Iterator;

typedef void (*incr)(Iterator*);
typedef Object* (*getval)(Iterator*);
typedef void (*setval)(Iterator*, ...);

struct Iterator_s
{
    Class base;
    incr __incr__;
    getval __getval__;
    setval  __setval__;
};

#define incr(it)           ((Iterator *)it)->__incr__(it)
#define getval(it)         ((Iterator *)it)->__getval__(it)
#define setval(it, ...)    ((Iterator *)it)->__setval__(it, __VA_ARGS__)

#endif