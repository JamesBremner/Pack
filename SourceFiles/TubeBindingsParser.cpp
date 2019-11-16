#include "cPackEngine.h"

TubeBindingsParser::TubeBindingsParser() {
}

TubeBindingsParser::TubeBindingsParser(const TubeBindingsParser& orig) {
}

TubeBindingsParser::~TubeBindingsParser() {
}





bool TubeBindingsParser::isDimError( int dim )
{
    if ( dim != 2 )
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

Bin* TubeBindingsParser::buildBin( string bin_id, vector<string> bin_size_v)
{
    Bin *bin; bin = new Bin1D();
    bin->set_id( bin_id );
    bin->set_side_1( new Side(atof(bin_size_v[0].c_str()), 'w') );
    bin->set_side_2( new Side(atof(bin_size_v[1].c_str()), 'h') );

    return bin;
}

Item* TubeBindingsParser::buildItem( string item_id, vector<string> item_size_v)
{
    Item2D* item2d = new Item2D();
    item2d->set_id( item_id );
    item2d->set_side_1( new Side( atof(item_size_v[0].c_str()), 'w' ) );
    item2d->set_side_2( new Side( atof(item_size_v[1].c_str()), 'h' ) );

    return item2d;
}
