#ifndef NEW_H
#define NEW_H

#include <stdarg.h>
#include "object.h"

Object* new(const Class* class, ...);
Object* va_new(const Class* class, va_list* args);

#endif