#include "point.h"

void Point_ctor(Point* this, va_list* args)
{
    if (!this || !args)
        raise("NULL value given");
    this->x = va_arg(*args, int);
    this->y = va_arg(*args, int);
}

void Point_dtor(Point* this)
{
    if (!this)
        raise("NULL value given");
    (void)this;
}

char *Point_str(Point* this)
{
    ssize_t bufsz = 0;
    char* buf = NULL;

    if (!this)
        raise("NULL value given");
    bufsz = snprintf(NULL, 0, "<Point (%d, %d)>", this->x, this->y);
    buf = malloc(bufsz + 1);
    if (!buf)
        raise("Out of memory");
    snprintf(buf, bufsz + 1, "<Point (%d, %d)>", this->x, this->y);

    return buf;
}

Point* Point_add(const Point* this, const Point* other)
{
    Point* point = NULL;

    if (!this || !other)
        raise("NULL value given");
    point = new(Point, this->x + other->x, this->y + other->y);
    if (!point)
        raise("Out of memory");

    return point;
}

Point* Point_sub(const Point* this, const Point* other)
{
    Point* point = NULL;

    if (!this || !other)
        raise("NULL value given");
    point = new(Point, this->x - other->x, this->y - other->y);
    if (!point)
        raise("Out of memory");

    return point;
}

static const Point _descr = {
    {
     .__size__ = sizeof(Point),
     .__name__ = "Point",
     .__ctor__ = (ctor_t)&Point_ctor,
     .__dtor__ = (dtor_t)&Point_dtor,
     .__str__ = (to_string_t)&Point_str,
     .__add__ = (binary_operator_t)&Point_add,
     .__sub__ = (binary_operator_t)&Point_sub,
     .__mul__ = NULL,
     .__div__ = NULL,
     .__eq__ = NULL,
     .__gt__ = NULL,
     .__lt__ = NULL
    },
    .x = 0,
    .y = 0
};

const Class *Point = (const Class*)&_descr;