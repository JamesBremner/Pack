
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

void Bin3D::set_x_sub_bin(Bin *value)
{
    
    if ( side_1_->orig_side() == 'w' )
        x_sub_bin_ = value;
    else  if ( side_2_->orig_side() == 'w' )
        y_sub_bin_ = value;
    else
        z_sub_bin_ = value;
};


void Bin3D::set_y_sub_bin(Bin *value)
{
    if ( side_1_->orig_side() == 'h' )
        x_sub_bin_ = value;
    else  if ( side_2_->orig_side() == 'h' )
        y_sub_bin_ = value;
    else
        z_sub_bin_ = value;
};

void Bin3D:: set_z_sub_bin(Bin *value)
{
    if ( side_1_->orig_side() == 'l' )
        x_sub_bin_ = value;
    else  if ( side_2_->orig_side() == 'l' )
        y_sub_bin_ = value;
    else
        z_sub_bin_ = value;
};


void Bin3D::itemsInBin(vector<Item*> &items)
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
    
        Item3D* item3d = (Item3D*)Bin2D::item_; 
	used += item3d->volume();
	
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
    
    vector<Item*> items;
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
            x_sub_bin()->encodeAsJSON( jsonStr, isDeep );

        }

        jsonStr << ",";

        if ( y_sub_bin_ == NULL)
            jsonStr << "\"y_sub_bin\": null";
        else
        {
            jsonStr << "\"y_sub_bin\": ";        
            y_sub_bin()->encodeAsJSON( jsonStr, isDeep );

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
    Bin3D *root = dynamic_cast<Bin3D*>(Root((Bin*)this));
    
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

