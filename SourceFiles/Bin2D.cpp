
#include "stdafx.h"

#ifndef NULL
#define NULL   ((void *) 0)
#endif
using namespace std;

Bin2D::Bin2D():Bin() {

    x_sub_bin_ = NULL;
    y_sub_bin_ = NULL;
    myWOffsetFromRoot = 0;
    myHOffsetFromRoot = 0;
}

Bin2D::Bin2D(const Bin2D& orig) {


}

Bin2D::~Bin2D()
{

}



void Bin2D::set_x_sub_bin( bin_t value)
{

    if ( side_1_->orig_side() == 'w' )
        x_sub_bin_ = value;
    else
        y_sub_bin_ = value;
};




void Bin2D::set_y_sub_bin( bin_t value)
{
    if ( side_2_->orig_side() == 'h' )
        y_sub_bin_ = value;
    else
        x_sub_bin_ = value;
};

void Bin2D:: itemsInBin( item_v_t &items)
{
    if ( item_ != NULL)
        items.push_back( item_ );

    if ( x_sub_bin_ != NULL )
        x_sub_bin_->itemsInBin( items );

    if ( y_sub_bin_ != NULL )
        y_sub_bin_->itemsInBin( items );

}



void Bin2D:: binRemSpace( vector<Bin*> &bins)
{
    if ( item_ == NULL )
        bins.push_back( this );

    if ( x_sub_bin_ != NULL )
        x_sub_bin_->binRemSpace( bins );

    if ( y_sub_bin_ != NULL )
        y_sub_bin_->binRemSpace( bins );


}




void Bin2D:: totalChildSpaceUsed( double &used )
{
    if ( item_ != NULL )
        used += item_->area();

    if ( x_sub_bin_ != NULL )
        x_sub_bin_->totalChildSpaceUsed( used );

    if ( y_sub_bin_ != NULL )
        y_sub_bin_->totalChildSpaceUsed( used );


}

void Bin2D:: totalRemSpaceAvailable(double& avail)
{
    if ( item_ == NULL )
        avail += area();

    if ( x_sub_bin_ != NULL )
        x_sub_bin_->totalRemSpaceAvailable( avail );

    if ( y_sub_bin_ != NULL )
        y_sub_bin_->totalRemSpaceAvailable( avail );

}

Bin * Bin2D::CreateNewEmptyCopy()
{
	Bin::bin_build_instructions instructions;
	char buf[20];

	// identify this as a new copy
	string sid = id();
	int p = sid.find("_cpy");
	if( p == -1 ) {
		sid += "_cpy2";
	} else {
		int cpy = atoi( sid.substr(p+4).c_str() );
		snprintf(buf,9,"%d",cpy+1);
		sid = sid.substr(0,p+4) + buf;
	}
	instructions.bin_id = sid;

	// copy the dimensions
	snprintf(buf,19,"%9f",side_1_->size() );
	instructions.size_v.push_back( string( buf ) );
	snprintf(buf,19,"%9f",side_2_->size() );
	instructions.size_v.push_back( string( buf ) );

	// we should always be using the defaultyunits internally
	instructions.dimension_units = "in";

	// we would never come here unless we have an endless supply of these
	instructions.can_copy = true;

	return Bin::Build( instructions );

}


     void Bin2D::Dumper()
     {
         cout << progid() << " " << side_1()->size() << "," << side_2()->size() <<
            " at " << getLocationHeight() << "," << getLocationWidth() << endl;
     }
void Bin2D::encodeAsJSON(stringstream &jsonStr, bool isDeep)
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

    vector<Bin*> bins;
    binRemSpace(bins);

    jsonStr << "\"rems\": [";
    for(unsigned i=0; i < bins.size(); ++i)
    {
        Bin2D * bin2d = dynamic_cast<Bin2D*>(bins[i]);
        jsonStr << "{";
        jsonStr << "\"rem_size\": \"" << bin2d->origSize() << "\",";
        jsonStr << "\"size_1\": " << bin2d->origSide1()->size() << ",";
        jsonStr << "\"size_2\": " << bin2d->origSide2()->size();
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
            jsonStr << "\"item\": null,";
        else
        {
            jsonStr << "\"item\": ";
            item_->encodeAsJSON(jsonStr);
            jsonStr << ",";

        }
        if ( x_sub_bin_ == NULL)
            jsonStr << "\"x_sub_bin\": null";
        else
        {
            jsonStr << "\"x_sub_bin\": ";
            get_x_sub_bin()->encodeAsJSON( jsonStr, isDeep );

        }

        jsonStr << ",";

        if ( y_sub_bin_ == NULL)
            jsonStr << "\"y_sub_bin\": null";
        else
        {
            jsonStr << "\"y_sub_bin\": ";
            get_y_sub_bin()->encodeAsJSON( jsonStr, isDeep );

        }
    }

    jsonStr << "}";

}

     void Bin2D::CreateCutList( cCutList& l )
    {
        l.clear();
        item_v_t items;
        itemsInBin(items);
        for( auto i : items )
        {
            i->AddToCutList( l );
        }
        l.Join();

    }

bool  Bin2D:: operator <( Shape &b)
{
    Bin2D *bin = dynamic_cast<Bin2D*>(&b);

	unsigned u_a = (unsigned) (this->binUtilizationRating() * 1000);
	unsigned u_b = (unsigned) (bin->binUtilizationRating() * 1000);
    return u_a < u_b;


}

bool  Bin2D:: operator >( Shape &b)
{
    Bin2D *bin = dynamic_cast<Bin2D*>(&b);

	unsigned u_a = (unsigned) (this->binUtilizationRating() * 1000);
	unsigned u_b = (unsigned) (bin->binUtilizationRating() * 1000);
    return u_a > u_b;

}

bool  Bin2D:: operator ==( Shape &b)
{
    Bin2D *bin = dynamic_cast<Bin2D*>(&b);

	unsigned u_a = (unsigned) (this->binUtilizationRating() * 1000);
	unsigned u_b = (unsigned) (bin->binUtilizationRating() * 1000);
    return u_a == u_b;


}

double Bin2D::binUtilizationRating()
{

    if ( binSpaceUsed() != 0)
        return binSpaceUsed() * area();
    else
        return area();
}
