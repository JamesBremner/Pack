
#include "stdafx.h"

int Item::nextPackSeq = 0;

Item::Item()
    : myBinProgID( -1 )
    , mySupport( 0 )
    , mySpinAxis( 0 )
{
}

Item::Item(const Item& orig)
{
}

Item::~Item()
{
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
    // chack for any rotation constraint
    if( ! myRotationConstraints )
        return true;

    // check for no rotation constraint
    if( myRotationConstraints == 7 )
        return false;

    // check for single axis rotation constraint
    switch( axis )
    {
    case 1:
        if( myRotationConstraints == 2 ||
                myRotationConstraints == 4 ||
                myRotationConstraints == 6 )
            return true;
        break;
    case 2:
        if( myRotationConstraints == 3 ||
                myRotationConstraints == 5 ||
                myRotationConstraints == 6 )
            return true;
        break;
    case 3:
        if( myRotationConstraints == 1 ||
                myRotationConstraints == 4 ||
                myRotationConstraints == 5 )
            return true;
        break;

    }

    return false;
}
void Item::Print()
{
    cout << "Item " << id() << " " << progid() << " in bin " << myBinProgID <<
         " location " << myWLocation << "," << myHLocation << "," << myLLocation
         << " sides " << side_1()->size() <<" " << side_2()->size() <<" "<< side_3()->size()
         << " orig " << origSide1()->size() <<" "<< origSide2()->size() <<" "<< origSide3()->size()
         << " os " << side_1()->orig_side() <<" "<< side_2()->orig_side() <<" "<< side_3()->orig_side()
         << " spin " << mySpinAxis
         << endl;
}
