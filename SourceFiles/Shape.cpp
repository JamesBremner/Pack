#include "stdafx.h"

int Shape::lastID = 0;

Shape::Shape() {
    myID = lastID++;
}

Shape::Shape(const Shape& orig) {
}

Shape::~Shape() {
}


string Shape::id()
{
    return id_;
}

void Shape::set_id( string value )
{
    id_ = value;
}


