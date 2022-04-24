#ifndef OBJECT_H
#define OBJECT_H

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
    binary_compare_op __lt__;
    binary_compare_op __gt__;
    binary_compare_op __eq__;
} Class;

#define str(obj) (((Class*)obj)->__str__(obj))

#endif