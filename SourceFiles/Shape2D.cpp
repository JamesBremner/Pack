
#include <iosfwd>
#include <sstream>

#ifndef NULL
#define NULL   ((void *) 0)
#endif



using namespace std;

Shape2D::Shape2D()
{
    side_2_ = NULL;
    side_1_ = NULL;    

};

Shape2D:: Shape2D(const Shape2D& orig)
{
    Shape2D();
}

Shape2D::~Shape2D() 
{
    if ( side_2_ != NULL)
        delete side_2_;
    if ( side_1_ != NULL )
        delete side_1_;    

};

Side *Shape2D::side_1()
{
    return side_1_;
};

void Shape2D::set_side_1(Side *value)
{
    side_1_ = value;
};

Side *Shape2D::side_2()
{
    return side_2_;
};

void Shape2D::set_side_2(Side *value)
{
    side_2_ = value;
};

Side * Shape2D::origSide1()
{    
    if( side_1_->orig_side() == 'w')
        return side_1_;
    else
        return side_2_;
}

Side * Shape2D::origSide2()
{
    if( side_2_->orig_side() == 'h')
        return side_2_;
    else
        return side_1_;
}

string Shape2D::origSize()
{
    stringstream ss;
    ss << origSide1()->size() << " x " << origSide2()->size();
    return ss.str();
   
}



double Shape2D:: area()
{
    
    return side_1_->size() * side_2_->size();
    
}

bool  Shape2D:: operator <( Shape &b) 
{
    Shape2D *b2d = (Shape2D*) &b;

	unsigned u_a = (unsigned) (this->area() * 1000);
	unsigned u_b = (unsigned) (b2d->area() * 1000);
    return u_a < u_b;
    
}

bool  Shape2D:: operator >( Shape &b)
{ 
    Shape2D *b2d = (Shape2D*) &b;

	unsigned u_a = (unsigned) (this->area() * 1000);
	unsigned u_b = (unsigned) (b2d->area() * 1000);
    return u_a > u_b;
    
}

bool  Shape2D:: operator ==( Shape &b)
{
    Shape2D *b2d = (Shape2D*) &b;

	unsigned u_a = (unsigned) (this->area() * 1000);
	unsigned u_b = (unsigned) (b2d->area() * 1000);
    return u_a == u_b;
    
}


