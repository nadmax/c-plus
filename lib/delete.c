#include "delete.h"

void delete(Object* obj)
{
    Class* class = (Class*)obj;

    if (!obj)
        raise("Object is null");
    else if (class->__dtor__)
        class->__dtor__(obj);
    free(obj);
}