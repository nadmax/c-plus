#ifndef INT_H
#define INT_H

#include <stdio.h>
#include "object.h"
#include "new.h"

typedef struct
{
    Class base;
    int value;
} IntClass;

extern const Class *Int;

void Int_ctor(IntClass *, va_list *);
void Int_dtor(IntClass *);
char *Int_str(IntClass *);
IntClass *Int_add(const IntClass *, const IntClass *);
IntClass *Int_sub(const IntClass *, const IntClass *);
IntClass *Int_mul(const IntClass *, const IntClass *);
IntClass *Int_div(const IntClass *, const IntClass *);
bool Int_eq(const IntClass *, const IntClass *);
bool Int_gt(const IntClass *, const IntClass *);
bool Int_lt(const IntClass *, const IntClass *);

#endif