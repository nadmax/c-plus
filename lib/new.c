#include "new.h"

void delele(Object* obj)
{
    Class* class = (Class*)obj;

    if (!obj)
        raise("Object is null");
    else if (class->__dtor__)
        class->__dtor__(obj);
    free(obj);
}

Object* va_new(const Class* class, va_list* args)
{
    Object* new = NULL;

    if (!class)
        raise("Class is null");
    new = malloc(class->__size__);
    if (!new)
        raise("Memory allocation failed");
    memcpy(new, class, class->__size__);
    if (class->__ctor__)
        class->__ctor__(new, args);
    
    return new;
}

Object* new(const Class* class, ...)
{
    Object* new = NULL;
    va_list args;

    va_start(args, class);
    new = va_new(class, &args);
    va_end(args);

    return new;
}