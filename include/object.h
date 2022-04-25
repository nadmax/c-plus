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
typedef Object* (binary_op)(const Object*, const Object*);
typedef bool (binary_compare_op)(const Object*, const Object*);

typedef struct Class_s
{
    const size_t __size__;
    const char* __name__;
    ctor __ctor__;
    dtor __dtor__;
    to_string __str__;
    binary_op __add__;
    binary_op __sub__;
    binary_op __mul__;
    binary_op __div__;
    binary_compare_op __eq__;
    binary_compare_op __lt__;
    binary_compare_op __gt__;
} Class;

#define str(obj)    (((Class *)obj)->__str__ != NULL ? ((Class *)obj)->__str__(obj) : strdup(((Class *)obj)->__name__))
#define add(a, b)   ((Class *)a)->__add__(a, b)
# define sub(a, b)  ((Class *)a)->__sub__(a, b)
# define mul(a, b)  ((Class *)a)->__mul__(a, b)
# define div(a, b)  ((Class *)a)->__div__(a, b)
# define eq(a, b)   ((Class *)a)->__eq__(a, b)
# define gt(a, b)   ((Class *)a)->__gt__(a, b)
# define lt(a, b)   ((Class *)a)->__lt__(a, b)

#endif