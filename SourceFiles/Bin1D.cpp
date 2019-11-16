#include "cPackEngine.h"
#ifndef NULL
#define NULL   ((void *) 0)
#endif


/*
 * File:   Bin1D.cpp
 * Author: arash
 *
 * Created on June 13, 2012, 11:23 AM
 */
using namespace std;

Bin1D::Bin1D():Bin() {

    z_sub_bin_ = NULL;

}

Bin1D::Bin1D(const Bin1D& orig) {

    Bin1D();
}

Bin1D::~Bin1D() {

}



bin_t Bin1D::z_sub_bin()
{
    return z_sub_bin_;
};

void Bin1D:: itemsInBin( item_v_t &items)
{
    if ( item_ != NULL)
        items.push_back( item_ );

    if ( z_sub_bin_ != NULL )
        z_sub_bin_->itemsInBin( items );


}



void Bin1D:: binRemSpace( bin_v_t &bins)
{
    if ( item_ == NULL )
        bins.push_back( shared_from_this() );

    if ( z_sub_bin_ != NULL )
        z_sub_bin_->binRemSpace( bins );



}





void Bin1D:: totalChildSpaceUsed( double &used )
{
    if ( item_ != NULL )
        used += item_->area();

    if ( z_sub_bin_ != NULL )
        z_sub_bin_->totalChildSpaceUsed( used );

}



void Bin1D:: totalRemSpaceAvailable(double& avail)
{
    if ( item_ == NULL )
        avail += area();

    if ( z_sub_bin_ != NULL )
        z_sub_bin_->totalRemSpaceAvailable( avail );


}


void Bin1D::encodeAsJSON(stringstream &jsonStr, bool isDeep)
{

    jsonStr << "{\"bin_size\": \"" << origSize() << "\",";
    jsonStr << "\"userid\": \"" << id_ << "\",";
    jsonStr << "\"progid\": \"" << myID << "\",";
    jsonStr << "\"size_1\": " << origSide1()->size() << ",";
    jsonStr << "\"size_2\": " << origSide2()->size() << ",";
    jsonStr << "\"items_count\": " << itemsInBinCount() << ",";
    jsonStr << "\"rems_count\": " << remsInBinCount() << ",";
    jsonStr << "\"bin_perc_used\": " << binSpaceUsed() << ",";
    jsonStr << "\"rem_perc_avail\": " << remSpaceAvail() << ",";
    jsonStr << "\"total_size\": " << area() << ",";

    item_v_t items;
    itemsInBin(items);


    jsonStr << "\"items\": [";
    for(unsigned i=0; i < items.size(); ++i)
    {
        items[i]->encodeAsJSON(jsonStr);

        if( i != items.size() - 1)
            jsonStr << ",";
    }

    items.clear();
    jsonStr << "],";

    bin_v_t bins;
    binRemSpace(bins);

    jsonStr << "\"rems\": [";
    for(unsigned i=0; i < bins.size(); ++i)
    {
        jsonStr << "{";
        jsonStr << "\"rem_size\": \"" << bins[i]->origSize() << "\",";
        jsonStr << "\"size_1\": " << bins[i]->origSide1()->size() << ",";
        jsonStr << "\"size_2\": " << bins[i]->origSide2()->size() << ",";
        jsonStr << "\"W\": " << bins[i]->getLocationWidth() << ",";
        jsonStr << "\"W\": " << bins[i]->getLocationHeight();
        jsonStr << "}";

        if( i != bins.size() - 1)
            jsonStr << ",";
    }

    bins.clear();
    jsonStr << "]";

    if (isDeep)
    {
        jsonStr << ",";
        if (item_ == NULL)
            jsonStr << "\"item\": {},";
        else
        {
            jsonStr << "\"item\": ";
            item_->encodeAsJSON(jsonStr);
            jsonStr << ",";

        }
        if ( z_sub_bin_ == NULL)
            jsonStr << "\"z_sub_bin\": {}";
        else
        {
            jsonStr << "\"z_sub_bin\": ";
            z_sub_bin()->encodeAsJSON( jsonStr, isDeep );

        }
    }

    jsonStr << "}";

}

bool  Bin1D:: operator <( Shape &b)
{
    Bin1D *bin = dynamic_cast<Bin1D*>(&b);

    return this->binUtilizationRating() < bin->binUtilizationRating();

}

bool  Bin1D:: operator >( Shape &b)
{
    Bin1D *bin = dynamic_cast<Bin1D*>(&b);

    return this->binUtilizationRating() > bin->binUtilizationRating();

}

bool  Bin1D:: operator ==( Shape &b)
{
    Bin1D *bin = dynamic_cast<Bin1D*>(&b);

    return this->binUtilizationRating() == bin->binUtilizationRating();

}

double Bin1D::binUtilizationRating()
{

    if ( binSpaceUsed() != 0)
        return binSpaceUsed() * area();
    else
        return area();
}


