#include "stdafx.h"


Shape::Shape() {
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


