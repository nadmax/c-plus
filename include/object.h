#ifndef OBJECT_H
#define OBJECT_H

#include <sys/types.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include "raise.h"

typedef void Object;
typedef void (*ctor)(Object*, va_list*);
typedef void (*dtor)(Object*);
typedef char* (*to_string)(Object*);
typedef Object* (*binary_operator)(const Object*, const Object*);
typedef bool (*binary_comparator)(const Object*, const Object*);

typedef struct
{
    const size_t __size__;
    const char* __name__;
    ctor __ctor__;
    dtor __dtor__;
    to_string __str__;
    binary_operator __add__;
    binary_operator __sub__;
    binary_operator __mul__;
    binary_operator __div__;
    binary_comparator __eq__;
    binary_comparator __lt__;
    binary_comparator __gt__;
} Class;

#define str(obj)    (((Class*)obj)->__str__ != NULL ? ((Class*)obj)->__str__(obj) : strdup(((Class*)obj)->__name__))
#define add(a, b)   ((Class*)a)->__add__(a, b)
#define sub(a, b)   ((Class*)a)->__sub__(a, b)
#define mul(a, b)   ((Class*)a)->__mul__(a, b)
#define div(a, b)   ((Class*)a)->__div__(a, b)
#define eq(a, b)    ((Class*)a)->__eq__(a, b)
#define gt(a, b)    ((Class*)a)->__gt__(a, b)
#define lt(a, b)    ((Class*)a)->__lt__(a, b)

#endif