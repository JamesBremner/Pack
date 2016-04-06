/*
 * File:   Bin.cpp
 * Author: arash
 *
 * Created on June 13, 2012, 11:51 AM
 */

#include "stdafx.h"



Bin::Bin():Shape2D()
{

    item_ = NULL;
}

Bin::Bin(const Bin& orig)
{

    Shape2D();
}

Bin::~Bin()
{


}

void Bin::set_parent_bin(bin_t value)
{
    myParentBin = value;
};

bin_t Bin::parent_bin()
{
    if( myParentBin )
        return myParentBin;
    else
        return shared_from_this();
}
bool Bin::HasParent()
{
    return (bool)myParentBin;
}

void Bin::set_original_parent_bin( bin_t value )
{
    myOriginalParentBin = value;
}

bin_t Bin::original_parent_bin()
{
    if( myOriginalParentBin )
        return myOriginalParentBin;
    else
        return shared_from_this();
}

void Bin:: set_item ( item_t item )
{

    item_ = item;

}

int Bin:: itemsInBinCount()
{
    item_v_t items;
    itemsInBin(items);
    int count = (int)items.size();
    items.clear();

    return count;
}

int Bin:: remsInBinCount()
{
    bin_v_t rems;
    binRemSpace(rems);
    int count = (int)rems.size();
    rems.clear();

    return count;
}

double Bin:: binSpaceUsed()
{
    double total_used = 0;
    totalChildSpaceUsed( total_used );


    if ( total_used == 0)
        return 0;
    else
        return total_used / area();

}

double Bin:: remSpaceAvail()
{
    double avail = 0;
    totalRemSpaceAvailable( avail );

    return avail / area();

}

//this one takes into account how much large space is left over that can perhaps be used for other things
double Bin:: adjBinSpaceUsed( )
{
    if ( binSpaceUsed() == 0 )
        return 0;
    else if ( binSpaceUsed() == 1)
        return 1;
    else if (remSpaceAvail() == 0 )
        return binSpaceUsed();


    return (remSpaceAvail() / remsInBinCount()) + binSpaceUsed();

}

bin_t Bin::Root( bin_t bin )
{
    return original_parent_bin();

}



void Bin::Print()
{
    cout << "Bin " << id() << " " << progid()
         << " sides " << side_1()->size() <<" " << side_2()->size() <<" "<< side_3()->size()
         << endl;
}


