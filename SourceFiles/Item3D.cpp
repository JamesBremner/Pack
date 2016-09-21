
#include "stdafx.h"

/*
 * File:   Item3D.cpp
 * Author: arash
 *
 * Created on June 14, 2012, 1:17 PM
 */
using namespace std;

Item3D::Item3D()
{
    set_side_1( new Side(0,'w'));
    set_side_2( new Side(0,'h'));
    set_side_3( new Side(0,'l'));
}

Item3D::Item3D(const Item3D& orig)
{
}

Item3D::~Item3D()
{
}

void Item3D::Spin( int axis )
{
    if( ! IsSpinAllowed( axis ) )
        return;

    Side *tmps;
    switch( axis )
    {
    case 1:
        tmps = side_2();
        set_side_2(side_3());
        set_side_3(tmps);
        break;
    case 2:
        tmps = side_1();
        set_side_1(side_3());
        set_side_3(tmps);
        break;
    case 3:
        tmps = side_1();
        set_side_1(side_2());
        set_side_2(tmps);
        break;
    }
}

/** Claculate spin axis compared to original orientation
*/

void Item3D::SpinAxisCalculate()
{
    // check if the item remains unrotated
    if( side_1()->orig_side() == 'w' &&
            side_2()->orig_side() == 'h' &&
            side_3()->orig_side() == 'l' )
        SpinAxis( 0 );

    else if( side_1()->orig_side() == 'w' )
        SpinAxis( 1 );

    else  if( side_2()->orig_side() == 'h' )
        SpinAxis( 2 );

    else
        SpinAxis( 3 );
}

void Item3D::encodeAsJSON(stringstream &jsonStr)
{

    jsonStr << "\n{";
    jsonStr << "\"item_size\": \"" << origSize() << "\",";
    jsonStr << "\"id\": \"" << id_ << "\",";
    jsonStr << "\"size_1\": " << origSide1()->size() << ",";
    jsonStr << "\"size_2\": " << origSide2()->size() << ",";
    jsonStr << "\"size_3\": " << origSide3()->size() << ",";
    jsonStr << "\"constraints\": " << RotationConstraints() << ",";
    jsonStr << "\"rotation\": " << SpinAxis() << ",";
    jsonStr << "\"W\": " << getWLocation() << ",";
    jsonStr << "\"H\": " << getHLocation() << ",";
    jsonStr << "\"L\": " << getLLocation() << ",";
    jsonStr << "\"Support\": " << Support();
    jsonStr << "}";

}


string Item3D::getCSV()
{
    stringstream s;
    s << side_1()->size() << ",";
    s << side_2()->size() << ",";
    s << side_3()->size() << ",";
    s  << getWLocation() << ",";
    s  << getHLocation() << ",";
    s  << getLLocation() << "\n";

    return s.str();
}


static bool valueInRange(double value, double min, double max)
{
    return (value >= min) && (value <= max);
}

bool Item3D::IsAboveBelow( item_t other )
{

//        cout << "IsAboveBelow " << progid() <<" "<< other->progid() << "\n";

    // boxes at the same height cannot overlap each other
    if( getHLocation() == other->getHLocation() )
        return false;

    double mw1 = getWLocation();
    double mw2 = mw1 + side_1()->size() - 1;
    double ml1 = getLLocation();
    double ml2 = ml1 + side_3()->size() - 1;
    double ow1 = other->getWLocation();
    double ow2 = ow1 + other->side_1()->size() - 1;
    double ol1 = other->getLLocation();
    double ol2 = ol1 + other->side_3()->size() - 1;


//    cout << mw1 <<" "<< mw2 <<" "<< ml1 <<" "<< ml2 <<"\n"<<
//         ow1 <<" "<< ow2 <<" "<< ol1 <<" "<< ol2 <<"\n";

    // http://stackoverflow.com/a/306379/16582

    bool wOverlap = valueInRange(mw1, ow1, ow2) ||
                    valueInRange(ow1, mw1, mw2);
    bool lOverlap = valueInRange(ml1, ol1, ol2) ||
                    valueInRange(ol1, ml1, ml2);

    return wOverlap && lOverlap;


}
