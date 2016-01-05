
#include "stdafx.h"

Item::Item()
: myBinProgID( -1 )
 {
}

Item::Item(const Item& orig) {
}

Item::~Item() {
}

int Item::RotationConstraints()
{
    return myRotationConstraints;
}
int Item::PositionConstraints()
{
    return myPositionConstraints;
}

void Item::set_constraints( int value )
{
    myRotationConstraints = value % 100;
    myPositionConstraints =  value  / 100;
}
bool Item::IsSpinAllowed( int axis )
{
    if( myRotationConstraints == 7 )
        return false;
    switch( axis )
    {
    case 1:
        break;
    }

    return true;
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
