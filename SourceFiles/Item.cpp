
#include "stdafx.h"

Item::Item()
: myBinProgID( -1 )
 {
}

Item::Item(const Item& orig) {
}

Item::~Item() {
}

int Item::constraints()
{
	    return constraints_;
}

void Item::set_constraints( int value )
{
	    constraints_ = value;
}
void Item::Print()
{
    cout << "Item " << id() << " " << progid() << " in " << myBinProgID <<
        " location " << myWLocation << "," << myHLocation
        << " sides " << side_1()->size() <<" " << side_2()->size() <<" "<< side_3()->size()
        << " orig " << origSide1()->size() <<" "<< origSide2()->size() <<" "<< origSide3()->size()
        << " os " << side_1()->orig_side() <<" "<< side_2()->orig_side() <<" "<< side_3()->orig_side()
        << " spin " << mySpinAxis
        << endl;
}
