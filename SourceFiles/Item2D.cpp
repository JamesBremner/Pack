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

void Item2D::AddToCutList( cCutList& l )
{
    l.Add( cCut(
               getWLocation(),
               getHLocation(),
               getWLocation(),
               getHLocation()+ side_1()->size()
           ));
    l.Add( cCut(
               getWLocation(),
               getHLocation()+ side_1()->size(),
               getWLocation()+ side_2()->size(),
               getHLocation() + side_1()->size()
           ));
    l.Add( cCut(
               getWLocation()+ side_2()->size(),
               getHLocation() + side_1()->size(),
               getWLocation()+ side_2()->size(),
               getHLocation()
           ));
    l.Add( cCut(
               getWLocation()+ side_2()->size(),
               getHLocation(),
               getWLocation(),
               getHLocation()
           ));
}

void Item2D::DrawList( std::stringstream& ss )
{
    const float scale = 2;
    int left = getWLocation() / scale;
    int top  = getHLocation() / scale;
    int w, h;
    if( ! SpinAxis() )
    {
        w = side_1()->size();
        h = side_2()->size();
    }
    else
    {
        w = side_2()->size();
        h = side_1()->size();
    }
    w /= scale;
    h /= scale;

    ss << "S.rectangle( { "
       << left <<", "
       << top << ", "
       << w << ", "
       << h << " } );\n";
    ss << "S.text(\"" << id() <<"\", {"
       << left+5 <<", "
       << top+5 <<", 50,30 } );\n";
//    ss << "S.line( { "
//        << left <<", "
//        << top << ", "
//        << left << ", "
//        << bottom << " } );\n";
//    ss << "S.line( { "
//        << left <<", "
//        << bottom << ", "
//        << right << ", "
//        << bottom << " } );\n";
//    ss << "S.line( { "
//        << right <<", "
//        << bottom << ", "
//        << right << ", "
//        << top << " } );\n";
//    ss << "S.line( { "
//        << right <<", "
//        << top << ", "
//        << left << ", "
//        << top << " } );\n";
}

