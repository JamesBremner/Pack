#include "stdafx.h"
#ifndef NULL
#define NULL   ((void *) 0)
#endif
using namespace std;

TubePacker::TubePacker() {
}

TubePacker::TubePacker(const TubePacker& orig) {
}

TubePacker::~TubePacker() {
}

void TubePacker::packThem( vector<Bin*> bins, vector<Item*> items)
{
    
    for( unsigned k=0; k < items.size(); ++k )
    {
        sort(bins.begin(), bins.end(), Utils::compareAscShape);
        
        bool is_bin_found = false;
        int bin_found_index = 0;
        for( vector<Bin*>::iterator member = bins.begin(); member != bins.end(); member++ )
        {   
            if ( packIt( *member, items[k], bins ) == true) 
            {
                
                is_bin_found = true;
                break;
            }
            bin_found_index++;
        } 
        
        if ( is_bin_found == true )
                bins.erase( bins.begin() + bin_found_index ); 
    }
    
    
}

bool TubePacker::packIt( Bin *bin, Item *item, vector<Bin*> &bins)
{
    
    Item2D *item2d = dynamic_cast<Item2D*>(item);
    
    if( item2d->side_1()->size() <= bin->side_1()->size() && item2d->side_2()->size() <= bin->side_2()->size() )
    {
        
        
        bin->set_item( item );
        
        //if it fits split item and recurse
        splitBinLength( bin, item );
        
        Bin1D * bin1d = dynamic_cast<Bin1D*>(bin);
        
        if ( bin1d->z_sub_bin() != NULL )
        {
            
            bins.push_back( bin1d->z_sub_bin() );

        }
        
        return true;

    }
    
    return false;

}

void TubePacker::splitBinLength( Bin *bin, Item *item )
{
    Item2D *item2d = dynamic_cast<Item2D*>(item);
    
    double dz_w = bin->side_1()->size();
    double dz_l = bin->side_2()->size() - item2d->side_2()->size();
    
    Bin1D * bin1d = dynamic_cast<Bin1D*>(bin);
    
    if ( dz_l <= 0 )
            bin1d->set_z_sub_bin( NULL );
    else
    {
       
        Bin1D *sub_binZ = new Bin1D();
        sub_binZ->set_side_1( bin->side_1()->size_side_to( dz_w ));
        sub_binZ->set_side_2( bin->side_2()->size_side_to( dz_l ));
        sub_binZ->set_parent_bin( bin );
        sub_binZ->set_id(bin->id());
        bin1d->set_z_sub_bin( sub_binZ );
        
        
    }
     
    
}

