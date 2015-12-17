
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


void Item3D::encodeAsJSON(stringstream &jsonStr)
{

    jsonStr << "{";
    jsonStr << "\"item_size\": \"" << origSize() << "\",";
    jsonStr << "\"id\": \"" << id_ << "\",";
    jsonStr << "\"size_1\": " << origSide1()->size() << ",";
    jsonStr << "\"size_2\": " << origSide2()->size() << ",";
    jsonStr << "\"size_3\": " << origSide3()->size() << ",";
    jsonStr << "\"constraints\": " << constraints() << ",";
    jsonStr << "\"rotation\": " << SpinAxis() << ",";
    jsonStr << "\"W\": " << getWLocation() << ",";
    jsonStr << "\"H\": " << getHLocation() << ",";
    jsonStr << "\"L\": " << getLLocation();
    jsonStr << "}";

}

