#include "stdafx.h"
#ifndef NULL
#define NULL   ((void *) 0)
#endif
using namespace std;

Shape3D::Shape3D():Shape2D()
{
    side_3_ = NULL;
};

Shape3D::~Shape3D() 
{
    
    if(side_3_ != NULL)
        delete side_3_;
};

Side *Shape3D::side_3()
{
    return side_3_;
};

void Shape3D::set_side_3(Side *value)
{
    side_3_ = value;
};

Side * Shape3D::origSide1()
{    
    if( side_1_->orig_side() == 'w')
        return side_1_;
    else if( side_2_->orig_side() == 'w')
        return side_2_;
    else
        return side_3_;
}

Side * Shape3D::origSide2()
{
    if( side_1_->orig_side() == 'h')
        return side_1_;
    else if( side_2_->orig_side() == 'h')
        return side_2_;
    else
        return side_3_;
}

Side * Shape3D::origSide3()
{
    if( side_1_->orig_side() == 'l')
        return side_1_;
    else if( side_2_->orig_side() == 'l')
        return side_2_;
    else
        return side_3_;
}

string Shape3D::origSize()
{
    stringstream ss;
    ss << origSide1()->size() << " x " << origSide2()->size() << " x " << origSide3()->size();
    return ss.str();
   
}


double Shape3D::volume()
{
    return (side_1_->size() * side_2_->size() * side_3_->size());
}

bool  Shape3D:: operator <( Shape &b) 
{

    Shape3D *b3d = dynamic_cast<Shape3D*>(&b); 

	unsigned u_a = (unsigned) (this->volume() * 1000);
	unsigned u_b = (unsigned) (b3d->volume() * 1000);
    return u_a < u_b;

    
}

bool  Shape3D:: operator >( Shape &b)
{ 
    Shape3D *b3d = dynamic_cast<Shape3D*>(&b);


	unsigned u_a = (unsigned) (this->volume() * 1000);
	unsigned u_b = (unsigned) (b3d->volume() * 1000);
    return u_a > u_b;
    
}

bool  Shape3D:: operator ==( Shape &b)
{
    Shape3D *b3d = dynamic_cast<Shape3D*>(&b);

	unsigned u_a = (unsigned) (this->volume() * 1000);
	unsigned u_b = (unsigned) (b3d->volume() * 1000);
    return u_a == u_b;

    
}


