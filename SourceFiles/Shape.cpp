#include "stdafx.h"

int Shape::lastID = 0;

Shape::Shape()
    : myWLocation( 0 )
    , myHLocation( 0 )
    , myLLocation( 0 )
{
    myID = lastID++;
}

Shape::Shape(const Shape& orig)
{
}

Shape::~Shape()
{
}


string Shape::id()
{
    return id_;
}

void Shape::set_id( string value )
{
    id_ = value;
}


