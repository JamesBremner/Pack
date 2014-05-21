
#include "stdafx.h"

#ifndef NULL
#define NULL   ((void *) 0)
#endif
using namespace std;

Bin3D::Bin3D():Bin1D(), Bin2D(), Shape3D() {
}

Bin3D::Bin3D(const Bin3D& orig) {
}

Bin3D::~Bin3D() {
}

Bin * Bin3D::CreateNewEmptyCopy()
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
	snprintf(buf,19,"%9f",side_3_->size() );
	instructions.size_v.push_back( string( buf ) );

	// we should always be using the defaultyunits internally
	instructions.dimension_units = "in";

	// we would never come here unless we have an endless supply of these
	instructions.can_copy = true;

	return Bin::Build( instructions );

}

void Bin3D::Dumper()
{
	printf("%s items %d, ",
		id().c_str(),
		itemsInBinCount() );
}


void Bin3D::set_x_sub_bin(bin_t value)
{

    if ( side_1_->orig_side() == 'w' )
        x_sub_bin_ = value;
    else  if ( side_2_->orig_side() == 'w' )
        y_sub_bin_ = value;
    else
        z_sub_bin_ = value;
};


void Bin3D::set_y_sub_bin(bin_t value)
{
    if ( side_1_->orig_side() == 'h' )
        x_sub_bin_ = value;
    else  if ( side_2_->orig_side() == 'h' )
        y_sub_bin_ = value;
    else
        z_sub_bin_ = value;
};

void Bin3D:: set_z_sub_bin(bin_t value)
{
    if ( side_1_->orig_side() == 'l' )
        x_sub_bin_ = value;
    else  if ( side_2_->orig_side() == 'l' )
        y_sub_bin_ = value;
    else
        z_sub_bin_ = value;
};


void Bin3D::ScaleSize( float f )
{
	side_1_->set_size( side_1_->size() * f );
	side_2_->set_size( side_2_->size() * f );
	side_3_->set_size( side_3_->size() * f );
}

void Bin3D::itemsInBin(item_v_t &items)
{
    if ( Bin2D::item_ != NULL)
        items.push_back( Bin2D::item_ );

    if ( x_sub_bin_ != NULL )
        x_sub_bin_->itemsInBin( items );

    if ( y_sub_bin_ != NULL )
        y_sub_bin_->itemsInBin( items );

    if ( z_sub_bin_ != NULL )
        z_sub_bin_->itemsInBin( items );


}

void Bin3D::binRemSpace(vector<Bin*> &bins)
{

    if ( Bin2D::item_ == NULL )
        bins.push_back( this );

    if ( x_sub_bin_ != NULL )
        x_sub_bin_->binRemSpace( bins );

    if ( y_sub_bin_ != NULL )
        y_sub_bin_->binRemSpace( bins );

    if ( z_sub_bin_ != NULL )
        z_sub_bin_->binRemSpace( bins );

}

void Bin3D::totalChildSpaceUsed( double &used )
{

    if ( Bin2D::item_ != NULL ) {

	used += item_->volume();

    }


    if ( x_sub_bin_ != NULL )
        x_sub_bin_->totalChildSpaceUsed( used );

    if ( y_sub_bin_ != NULL )
        y_sub_bin_->totalChildSpaceUsed( used );

    if ( z_sub_bin_ != NULL )
        z_sub_bin_->totalChildSpaceUsed( used );
}

void Bin3D::totalRemSpaceAvailable( double &avail)
{
    if ( Bin2D::item_ == NULL )
        avail += volume();

    if ( x_sub_bin_ != NULL )
        x_sub_bin_->totalRemSpaceAvailable( avail );

    if ( y_sub_bin_ != NULL )
        y_sub_bin_->totalRemSpaceAvailable( avail );

    if ( z_sub_bin_ != NULL )
        z_sub_bin_->totalRemSpaceAvailable( avail );

}

double Bin3D:: binSpaceUsed()
{

    double total_used = 0;
    totalChildSpaceUsed( total_used );

    if ( total_used == 0)
        return 0;
    else
        return total_used / volume();

}

double Bin3D:: remSpaceAvail()
{
    double avail = 0;
    totalRemSpaceAvailable( avail );

    return avail / volume();

}


void Bin3D::encodeAsJSON(stringstream &jsonStr, bool isDeep)
{
    jsonStr << "{\"bin_size\": \"" << origSize() << "\",";
    jsonStr << "\"id\": \"" << id_ << "\",";
    jsonStr << "\"size_1\": " << origSide1()->size() << ",";
    jsonStr << "\"size_2\": " << origSide2()->size() << ",";
    jsonStr << "\"size_3\": " << origSide3()->size() << ",";
    jsonStr << "\"items_count\": " << itemsInBinCount() << ",";
    jsonStr << "\"rems_count\": " << remsInBinCount() << ",";
    jsonStr << "\"bin_perc_used\": " << binSpaceUsed() << ",";
    jsonStr << "\"rem_perc_avail\": " << remSpaceAvail() << ",";
    jsonStr << "\"total_size\": " << volume() << ",";

    item_v_t items;
    itemsInBin(items);

    jsonStr << "\"items\": [";
    for(unsigned i=0; i < items.size(); ++i)
    {
         items[i]->encodeAsJSON(jsonStr);

        if( i != items.size() - 1)
            jsonStr << ",";
    }


    jsonStr << "],";

    vector<Bin*> bins;
    binRemSpace(bins);


    jsonStr << "\"rems\": [";
    for(unsigned i=0; i < bins.size(); ++i)
    {
        Bin3D * bin3d = dynamic_cast<Bin3D*>(bins[i]);
        jsonStr << "{";
        jsonStr << "\"rem_size\": \"" << bin3d->origSize() << "\",";
        jsonStr << "\"size_1\": " << bin3d->origSide1()->size() << ",";
        jsonStr << "\"size_2\": " << bin3d->origSide2()->size() << ",";
        jsonStr << "\"size_3\": " << bin3d->origSide3()->size();
        jsonStr << "}";

        if( i != bins.size() - 1)
            jsonStr << ",";
    }



    jsonStr << "]";

    items.clear();
    bins.clear();

    if(isDeep)
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

        jsonStr << ",";

        if ( z_sub_bin_ == NULL)
            jsonStr << "\"z_sub_bin\": null";
        else
        {
            jsonStr << "\"z_sub_bin\": ";
            z_sub_bin()->encodeAsJSON( jsonStr, isDeep );

        }
    }

    jsonStr << "}";

}

double Bin3D::binUtilizationRating()
{
    bin_t root = Root(shared_from_this());

    if ( root->binSpaceUsed() != 0)
     	return root->binSpaceUsed() * volume();
    else
        return volume();
}

bool  Bin3D:: operator <( Shape &b)
{

    Bin3D *bin = dynamic_cast<Bin3D*>(&b);

	unsigned u_a = (unsigned) (this->binUtilizationRating() * 1000);
	unsigned u_b = (unsigned) (bin->binUtilizationRating() * 1000);
    return u_a < u_b;

}

bool  Bin3D:: operator >( Shape &b)
{
    Bin3D *bin = dynamic_cast<Bin3D*>(&b);

	unsigned u_a = (unsigned) (this->binUtilizationRating() * 1000);
	unsigned u_b = (unsigned) (bin->binUtilizationRating() * 1000);
    return u_a > u_b;


}

bool  Bin3D:: operator ==( Shape &b)
{
    Bin3D *bin = dynamic_cast<Bin3D*>(&b);

	unsigned u_a = (unsigned) (this->binUtilizationRating() * 1000);
	unsigned u_b = (unsigned) (bin->binUtilizationRating() * 1000);
    return u_a == u_b;

}

