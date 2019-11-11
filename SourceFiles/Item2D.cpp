#include "stdafx.h"
#include <iosfwd>
#include <sstream>

using namespace std;

Item2D::Item2D():Shape2D(), Item()
{

}

Item2D::Item2D(const Item& orig):Shape2D()
{
}

Item2D::~Item2D()
{
}



void Item2D::encodeAsJSON(stringstream &jsonStr)
{


    jsonStr << "{";

    jsonStr << "\"item_size\": \"" << origSize() << "\",";
    jsonStr << "\"user_id\": \"" << id() << "\",";
    jsonStr << "\"prog_id\": \"" << myID << "\",";
//    jsonStr << "\"size_1\": " << origSide1()->size() << ",";
//    jsonStr << "\"size_2\": " << origSide2()->size() << ",";
    jsonStr << "\"constraints\": " << RotationConstraints() << ",";
    jsonStr << "\"bin\": " << getBin() << ",";
    if( getSpinLocation() )
        jsonStr << "\"rotation\" : \"yes\",";
    else
        jsonStr << "\"rotation\" : \"no\",";
    jsonStr << "\"W\": " << getWLocation() << ",";
    jsonStr << "\"H\": " << getHLocation();

    jsonStr << "}";


}

string Item2D::getSpin()
{
    stringstream ss;
    ss << side_1_->orig_side() <<side_2_->orig_side();
    return ss.str();
}

void Item2D::Spin( int axis )
{
    //cout << "item rotating " << item2d->side_1()->orig_side() <<  item2d->side_2()->orig_side() << endl;
    Side *tmps;
    tmps = side_1();
    set_side_1( side_2() );
    set_side_2( tmps );
    //cout << "item rotated " << item2d->side_1()->orig_side() <<  item2d->side_2()->orig_side() << endl;
}

bool Item2D::FitsInto( bin_t bin )
{
    return (   side1size() <= bin->side1size() &&
               side2size() <= bin->side2size() );
}

void Item2D::AddToCutList( cCutList& l )
{
//    cout << "AddToCutList " << id()
//         <<" "<<getWLocation()<<" "<<getHLocation()<< "\n";

    l.Add( cCut(
               getWLocation(),
               getHLocation(),
               getWLocation(),
               bottom()
           ));
    l.Add( cCut(
               getWLocation(),
               bottom(),
               right(),
               bottom()
           ));
    l.Add( cCut(
               right(),
               bottom(),
               right(),
               getHLocation()
           ));
    l.Add( cCut(
               right(),
               getHLocation(),
               getWLocation(),
               getHLocation()
           ));
}

void Item2D::DrawList( std::stringstream& ss )
{
//    cout << "DrawList " << progid() <<" "<< getWLocation() <<" "<< getHLocation()
//        <<" "<< side1size() <<" "<< side2size()
//        <<" "<< mySpinLocation << "\n";

    const float scale = 2;
    int left = getWLocation() / scale;
    int top  = getHLocation() / scale;
    int w = side1size() / scale;
    int h = side2size() / scale;


    ss << "S.rectangle( { "
       << left <<", "
       << top << ", "
       << w << ", "
       << h << " } );\n";
    ss << "S.text(\"" << id() <<"\", {"
       << left+5 <<", "
       << top+5 <<", 50,30 } );\n";
}
string Item2D::getCSV()
{
    stringstream s;
    s << id() << ",";
    s << side_1()->size() << ",";
    s << side_2()->size() << ",";
    s  << getWLocation() << ",";
    s  << getHLocation() << "\n";

    return s.str();
}

