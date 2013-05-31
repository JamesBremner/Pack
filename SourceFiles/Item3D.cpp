
#include "stdafx.h"

/* 
 * File:   Item3D.cpp
 * Author: arash
 * 
 * Created on June 14, 2012, 1:17 PM
 */
using namespace std;

Item3D::Item3D() {
}

Item3D::Item3D(const Item3D& orig) {
}

Item3D::~Item3D() {
}

void Item3D::ScaleSize( float f )
{
	side_1_->set_size( side_1_->size() * f );
	side_2_->set_size( side_2_->size() * f );
	side_3_->set_size( side_3_->size() * f );
}

void Item3D::encodeAsJSON(stringstream &jsonStr)
{

    jsonStr << "{";
    jsonStr << "\"item_size\": \"" << origSize() << "\",";
    jsonStr << "\"id\": \"" << id_ << "\",";
    jsonStr << "\"size_1\": " << origSide1()->size() << ",";
    jsonStr << "\"size_2\": " << origSide2()->size() << ",";
    jsonStr << "\"size_3\": " << origSide3()->size() << ",";
    jsonStr << "\"constraints\": " << constraints();
    jsonStr << "}";

}

