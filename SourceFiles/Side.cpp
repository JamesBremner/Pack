
#include "stdafx.h"


Side::Side()
{


}

Side::Side( double size, char orig_side)
{
    size_ = size;
    orig_side_ = orig_side;

}

Side::~Side()
{


}

double Side::size() const
{
    return size_;
}

void Side::set_size( double value)
{

    size_ = value;
}



char Side::orig_side()
{
    return orig_side_;
}

void Side::set_orig_side( char value )
{
    orig_side_ = value;
}



Side *Side::size_side_to( double new_size )
{

    Side *new_side = new Side();
    new_side->set_size( new_size );
    new_side->set_orig_side( orig_side_ );
    return new_side;

}
