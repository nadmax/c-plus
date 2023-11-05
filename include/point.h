#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include "new.h"
#include "object.h"

typedef struct Point_s PointClass;

extern const Class* Point;

struct Point_s
{
    Class base;
    int x;
    int y;
};

void Point_ctor(PointClass*, va_list*);
void Point_dtor(PointClass*);
char* Point_str(PointClass*);
PointClass* Point_add(const PointClass*, const PointClass*);
PointClass* Point_sub(const PointClass*, const PointClass*);
PointClass* Point_mul(const PointClass*, const PointClass*);
PointClass* Point_div(const PointClass*, const PointClass*);

#endif