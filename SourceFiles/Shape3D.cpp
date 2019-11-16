#include "cPackEngine.h"
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

void Shape3D::ScaleSize( float f )
{
	side_1_->set_size( side_1_->size() * f );
	side_2_->set_size( side_2_->size() * f );
	side_3_->set_size( side_3_->size() * f );
}


double Shape3D::volume()
{
    return (side_1_->size() * side_2_->size() * side_3_->size());
}

double Shape3D::AreaWidthLength() const
{
    return (side_1_->size() * side_3_->size());
}

double Shape3D::OverlapArea( std::shared_ptr<Shape> b )
{
    double wA1 = getWLocation();
    double wA2 = getWLocation() + side_1_->size();
    double lA1 = getLLocation();
    double lA2 = getLLocation() + side_3_->size();

    double wB1 = b->getWLocation();
    double wB2 = b->getWLocation() + b->side_1()->size();
    double lB1 = b->getLLocation();
    double lB2 = b->getLLocation() + b->side_3()->size();

    using std::min;
    using std::max;
    return ( min( wA2, wB2 ) - max( wA1, wB1 ) ) * ( min( lA2, lB2 ) - max( lA1, lB1 ) );

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

string Shape3D::getSTL( int offset )
{
    stringstream s;
    s << "solid " << id() << "\n";
    s << "facet normal  0.000000e+000 0.000000e+000  -1.000000e+000\n   outer loop\n";
    s << "vertex " << getWLocation() + offset  <<" "<< getLLocation() <<" "<< getHLocation() << "\n";
    s << "vertex " << getWLocation2() + offset <<" "<< getLLocation() <<" "<< getHLocation() << "\n";
    s << "vertex " << getWLocation() + offset  <<" "<< getLLocation2()<<" "<< getHLocation() << "\n";
    s << "endloop\nendfacet\n";
    s << "facet normal  0.000000e+000 0.000000e+000  -1.000000e+000\n   outer loop\n";
    s << "vertex " << getWLocation() + side_1()->size() + offset <<" "<< getLLocation() <<" "                   << getHLocation() << "\n";
    s << "vertex " << getWLocation() + side_1()->size() + offset <<" "<< getLLocation() + side_3()->size() <<" "<< getHLocation() << "\n";
    s << "vertex " << getWLocation() + offset <<" "                   << getLLocation() + side_3()->size() <<" "<< getHLocation() << "\n";
    s << "endloop\nendfacet\n";
    s << "facet normal  0.000000e+000 0.000000e+000  +1.000000e+000\n   outer loop\n";
    s << "vertex " << getWLocation() + side_1()->size() + offset <<" "<< getLLocation() + side_3()->size()<<" "   << getHLocation2() <<"\n";
    s << "vertex " << getWLocation()  + offset                   <<" "<< getLLocation() + side_3()->size() <<" "  << getHLocation2()<<"\n";
    s << "vertex " << getWLocation() + side_1()->size() + offset <<" "<< getLLocation() <<" "                     << getHLocation2() <<"\n";
    s << "endloop\nendfacet\n";
    s << "facet normal  0.000000e+000 0.000000e+000  +1.000000e+000\n   outer loop\n";
    s << "vertex " << getWLocation() + offset <<" "                   << getLLocation() <<" "                   << getHLocation2() <<"\n";
    s << "vertex " << getWLocation() + side_1()->size() + offset <<" "<< getLLocation() <<" "                   << getHLocation2() <<"\n";
    s << "vertex " << getWLocation()  + offset <<" "                   << getLLocation() + side_3()->size() <<" "<< getHLocation2() <<"\n";
    s << "endloop\nendfacet\n";

    s << "facet normal  -1 0 0\n   outer loop\n";
    s << "vertex " << getWLocation()  + offset <<" "<< getLLocation()  <<" " << getHLocation() <<"\n";
    s << "vertex " << getWLocation2()  + offset<<" "<< getLLocation() <<" "  << getHLocation()<<"\n";
    s << "vertex " << getWLocation()  + offset <<" "<< getLLocation() <<" "  << getHLocation2() <<"\n";
    s << "endloop\nendfacet\n";
    s << "facet normal  -1 0 0 \n   outer loop\n";
    s << "vertex " << getWLocation2()  + offset<<" " << getLLocation() <<" " << getHLocation2() <<"\n";
    s << "vertex " << getWLocation()   + offset<<" "<< getLLocation() <<" "  << getHLocation2() <<"\n";
    s << "vertex " << getWLocation2()  + offset <<" " << getLLocation()  <<" "<< getHLocation() <<"\n";
    s << "endloop\nendfacet\n";

    s << "facet normal  1 0 0\n   outer loop\n";
    s << "vertex " << getWLocation()  + offset <<" "<< getLLocation2()  <<" " << getHLocation() <<"\n";
    s << "vertex " << getWLocation()  + offset <<" "<< getLLocation2() <<" "  << getHLocation2() <<"\n";
    s << "vertex " << getWLocation2()  + offset<<" "<< getLLocation2() <<" "  << getHLocation()<<"\n";
    s << "endloop\nendfacet\n";
    s << "facet normal  1 0 0 \n   outer loop\n";
    s << "vertex " << getWLocation2()  + offset<<" " << getLLocation2() <<" " << getHLocation2() <<"\n";
    s << "vertex " << getWLocation2()  + offset <<" " << getLLocation2()  <<" "<< getHLocation() <<"\n";
    s << "vertex " << getWLocation()   + offset<<" "<< getLLocation2() <<" "  << getHLocation2() <<"\n";
    s << "endloop\nendfacet\n";

    s << "facet normal  0 -1 0\n   outer loop\n";
    s << "vertex " << getWLocation()  + offset <<" "<< getLLocation()  <<" " << getHLocation() <<"\n";
    s << "vertex " << getWLocation()  + offset <<" "<< getLLocation2() <<" "  << getHLocation() <<"\n";
    s << "vertex " << getWLocation()  + offset<<" "<< getLLocation() <<" "  << getHLocation2()<<"\n";
    s << "endloop\nendfacet\n";
    s << "facet normal  0 -1 0\n   outer loop\n";
    s << "vertex " << getWLocation()  + offset<<" " << getLLocation2() <<" " << getHLocation2() <<"\n";
    s << "vertex " << getWLocation()  + offset <<" " << getLLocation()  <<" "<< getHLocation2() <<"\n";
    s << "vertex " << getWLocation()   + offset<<" "<< getLLocation2() <<" "  << getHLocation() <<"\n";
    s << "endloop\nendfacet\n";

    s << "facet normal  0 1 0\n   outer loop\n";
    s << "vertex " << getWLocation2()  + offset <<" "<< getLLocation()  <<" " << getHLocation() <<"\n";
    s << "vertex " << getWLocation2()  + offset<<" "<< getLLocation() <<" "  << getHLocation2()<<"\n";
    s << "vertex " << getWLocation2()  + offset <<" "<< getLLocation2() <<" "  << getHLocation() <<"\n";
    s << "endloop\nendfacet\n";
    s << "facet normal  0 1 0\n   outer loop\n";
    s << "vertex " << getWLocation2()  + offset<<" " << getLLocation2() <<" " << getHLocation2() <<"\n";
    s << "vertex " << getWLocation2()   + offset<<" "<< getLLocation2() <<" "  << getHLocation() <<"\n";
    s << "vertex " << getWLocation2()  + offset <<" " << getLLocation()  <<" "<< getHLocation2() <<"\n";
    s << "endloop\nendfacet\n";


    s << "endsolid "<< id() << "\n";
    return s.str();
}

