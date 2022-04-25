#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include "new.h"
#include "object.h"

typedef struct Point_s
{
    Class base;
    int x;
    int y;
} Point;

extern const Class* point;

void Point_ctor(Point*, va_list*);
void Point_dtor(Point*);
char *Point_str(Point*);
Point* Point_add(const Point*, const Point*);
Point* Point_sub(const Point*, const Point*);

#endif