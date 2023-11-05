#ifndef VERTEX_H
#define VERTEX_H

#include <stdio.h>
#include "new.h"
#include "object.h"

typedef struct Vertex_s VertexClass;

extern const Class* Vertex;

struct Vertex_s
{
    Class base;
    int x;
    int y;
    int z;
};

void Vertex_ctor(VertexClass*, va_list*);
void Vertex_dtor(VertexClass*);
char* Vertex_str(VertexClass*);
VertexClass* Vertex_add(const VertexClass*, const VertexClass*);
VertexClass* Vertex_sub(const VertexClass*, const VertexClass*);
VertexClass* Vertex_mul(const VertexClass*, const VertexClass*);
VertexClass* Vertex_div(const VertexClass*, const VertexClass*);

#endif