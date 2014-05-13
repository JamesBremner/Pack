/*
 * File:   Item.cpp
 * Author: arash
 *
 * Created on June 14, 2012, 1:16 PM
 */

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
        " location " << myWLocation << "," << myHLocation << endl;
}
