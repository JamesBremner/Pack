#include "stdafx.h"

#ifndef NULL
#define NULL   ((void *) 0)
#endif

using namespace std;
using namespace boost;

BoxBindingsParser::BoxBindingsParser() {
    
    dim_ = 0;

}

BoxBindingsParser::BoxBindingsParser(const BoxBindingsParser& orig) {
}

BoxBindingsParser::~BoxBindingsParser() {
}

void BoxBindingsParser::parseBinsAndItems( const char *bins, const char *items,
                                         vector<Bin*> &bins_v, vector<Item*> &items_v,
                                         int &dim )
{
    vector<string> bin_v;
    split(bin_v, bins, is_any_of(","));
    vector<string> item_v;
    split(item_v, items, is_any_of(","));
    parseBins( bins_v, bin_v, dim );
    bin_v.clear();
    if ( dim > 3)
    {
        item_v.clear();
        return;
        
    }
    parseItems( items_v, item_v, dim );
    item_v.clear();    
}

void BoxBindingsParser::parseBins( vector<Bin*> &bins, vector<string> bin_v, int &dim )
{

    for(unsigned i= 0; i < bin_v.size(); i++)
    {
        string bin_str = bin_v[i];
        vector<string> id_bin;
        split(id_bin, bin_str, is_any_of(":"));
        
        
        if( id_bin.size() < 2 || id_bin.size() > 2)
        {
            dim = BoxBindingsParser::BIN_PARSE_ERROR;
            break;
        }
        string bin_id = id_bin[0];
        string bin_size = id_bin[1];
        id_bin.clear();
        
        vector<string> bin_size_v;
        split(bin_size_v, bin_size, is_any_of("x"));
                
        if ( isDimError( bin_size_v.size() ) == true )
        {
            dim = BoxBindingsParser::PACKER_ERROR;
            break;
        } 
        else
            dim = bin_size_v.size();
        
        bins.push_back( buildBin ( bin_id, bin_size_v ) );
        
        bin_size_v.clear();
        
    }
    
}

Bin *BoxBindingsParser::buildBin( string bin_id, vector<string> bin_size_v )
{
    Bin *bin;
    Bin3D *bin3d;
    switch( bin_size_v.size() )
    {
        case 1:                     
            bin = new Bin1D();
            bin->set_id( bin_id );
            bin->set_side_1( new Side(atof(bin_size_v[0].c_str()), 'w') );
            bin->set_side_2( new Side(atof(bin_size_v[1].c_str()), 'h') );
             
            break;
            
        case 2:
            bin = new Bin2D();
            bin->set_id( bin_id );
            bin->set_side_1( new Side(atof(bin_size_v[0].c_str()), 'w') );
            bin->set_side_2( new Side(atof(bin_size_v[1].c_str()), 'h') );
          
            break;
            
        case 3:
            bin = new Bin3D();
            bin3d = dynamic_cast<Bin3D*>(bin);
            bin3d->set_id( bin_id );
            bin3d->set_side_1( new Side(atof(bin_size_v[0].c_str()), 'w') );
            bin3d->set_side_2( new Side(atof(bin_size_v[1].c_str()), 'h') );
            bin3d->set_side_3( new Side(atof(bin_size_v[2].c_str()), 'l') );            
               
            break;
            
        default:            
            break;
        
        
    }
    
    return bin;
    
}

void BoxBindingsParser::parseItems( vector<Item*> &items, vector<string> item_v, int &dim )
{
    for(unsigned i= 0; i < item_v.size(); i++)
    {
        string item_str = item_v[i];
        vector<string> id_item;
        split(id_item, item_str, is_any_of(":"));
        
       
        if( id_item.size() < 3 || id_item.size() > 3 )
        {
            dim = BoxBindingsParser::ITEM_PARSE_ERROR;
            break;
        }
        
        string item_id = id_item[0];
        int constraints = atof( id_item[1].c_str() );
        string item_size = id_item[2];

        
        id_item.clear();
        
        vector<string> item_size_v;
        split(item_size_v, item_size, is_any_of("x"));
        
        if ( isDimError( item_size_v.size() ) == true )
        {
            dim = BoxBindingsParser::PACKER_ERROR;
            break;
        } 
        else  
            dim = item_size_v.size();
        
        items.push_back( buildItem ( item_id, item_size_v, constraints) );
        
        item_size_v.clear();
        
    }
}


Item *BoxBindingsParser::buildItem( string item_id, vector<string> item_size_v, int constraints)
{
    Item* item;
    Item2D* item2d;
    Item3D* item3d;
 
    switch( item_size_v.size() )
    {
        case 1:                     
            item = new Item2D();
            item2d = dynamic_cast<Item2D*>(item);
            item2d->set_id( item_id );
            item2d->set_side_1( new Side( atof(item_size_v[0].c_str()), 'w' ) );
            item2d->set_side_2( new Side( atof(item_size_v[1].c_str()), 'h' ) );
            break;
            
        case 2:
            item = new Item2D();
            item2d = dynamic_cast<Item2D*>(item);
            item2d->set_id( item_id );
            item2d->set_side_1( new Side( atof(item_size_v[0].c_str()), 'w' ) );
            item2d->set_side_2( new Side( atof(item_size_v[1].c_str()), 'h' ) );
            break;
            
        case 3:
            item = new Item3D();
            item3d = dynamic_cast<Item3D*>(item);
            item3d->set_id( item_id );
            item3d->set_side_1( new Side( atof(item_size_v[0].c_str()), 'w' ));
            item3d->set_side_2( new Side( atof(item_size_v[1].c_str()), 'h'  ) );
            item3d->set_side_3( new Side( atof(item_size_v[2].c_str()), 'l'  ) );            
            break;
            
        default:            
            break;
        
        
    }   

	item->set_constraints( constraints );
    
    return item;  
}

bool BoxBindingsParser::isDimError( int dim )
{
    if ( dim < 2 || dim > 3 )
        return true;
    
    if( dim_ == 0)
    {
        dim_ = dim;
        return false;
    }
    else
    {
        if ( dim_ != dim )
            return true;
        else
            return false;
    }
}
