
#include "stdafx.h"

#ifndef NULL
#define NULL   ((void *) 0)
#endif
using namespace std;

Bin3D::Bin3D():Bin1D(), Bin2D(), Shape3D()
{
    myLOffsetFromRoot = 0;
}

Bin3D::Bin3D(const Bin3D& orig)
{
}

Bin3D::~Bin3D()
{
}

Bin * Bin3D::CreateNewEmptyCopy()
{
    Bin::bin_build_instructions instructions;
    char buf[20];

    // identify this as a new copy
    string sid = id();
    int p = sid.find("_cpy");
    if( p == -1 )
    {
        sid += "_cpy2";
    }
    else
    {
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

bool Bin3D::IsUnusedBin()
{
    // check for uunused space in a bigger bin
    if( parent_bin() != NULL )
        return false;

    item_v_t iv;
    itemsInBin( iv );
    return ( ! iv.size() );
}

void Bin3D::itemsInPackOrder( item_v_t &items )
{
    itemsInBin( items );

    sort( items.begin(), items.end(),
          []( item_t a, item_t b )
    {
        return a->PackSeq() < b->PackSeq();
    });
}
void Bin3D::itemsIncHeightOrder( item_v_t &items )
{
    itemsInBin( items );

    sort( items.begin(), items.end(),
          []( item_t a, item_t b )
    {
        return a->getHLocation() < b->getHLocation();
    });
}
void Bin3D::binRemSpace( bin_v_t &bins)
{

    if ( Bin2D::item_ == NULL )
        bins.push_back( shared_from_this() );

    if ( x_sub_bin_ != NULL )
        x_sub_bin_->binRemSpace( bins );

    if ( y_sub_bin_ != NULL )
        y_sub_bin_->binRemSpace( bins );

    if ( z_sub_bin_ != NULL )
        z_sub_bin_->binRemSpace( bins );

}

void Bin3D::totalChildSpaceUsed( double &used )
{

    if ( Bin2D::item_ != NULL )
    {

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

bool Bin3D::Fit( item_t item )
{
//    cout << "Bin3D::Fit " << item->side_1()->size() <<" "<< item->side_2()->size() <<" "<< item->side_3()->size() <<" in "<<
//        side_1()->size() <<" "<< side_2()->size() <<" " << side_2()->size() << endl;

    if( ! (item->side_1()->size() <= side_1()->size() &&
            item->side_2()->size() <= side_2()->size() &&
            item->side_3()->size() <= side_3()->size()) )
        return false;


    return true;
}

bool Bin3D::FitWeight( item_t item )
{
    //cout << "FitWeight " << progid() <<" "<< original_parent_bin()->progid() << "\n";

    if( original_parent_bin()->MaxWeight() <= 0 )
        return true;

    float curWeight = 0;
    item_v_t items;
    original_parent_bin()->itemsInBin( items );
    for( auto i : items )
        curWeight += i->Weight();
    if( curWeight + item->Weight() > original_parent_bin()->MaxWeight() )
        return false;

    return true;

}

string Bin3D::getCSV()
{
    stringstream s;
    item_v_t items;
    itemsInPackOrder(items);
    for( auto& i : items )
        s << i->getCSV();
    return s.str();
}

string Bin3D::getSTL( int offset )
{
     stringstream s;
    item_v_t items;
    itemsInPackOrder(items);
    for( auto& i : items )
        s << i->getSTL( offset );
    s << Shape3D::getSTL( offset );
    return s.str();
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
    itemsInPackOrder(items);

    jsonStr << "\"items\": [";
    for(unsigned i=0; i < items.size(); ++i)
    {
        items[i]->encodeAsJSON(jsonStr);

        if( i != items.size() - 1)
            jsonStr << ",";
    }


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
        jsonStr << "\"size_3\": " << bins[i]->origSide3()->size();
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

    jsonStr << "}\n";

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

    return this->binUtilizationRating() < bin->binUtilizationRating();

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

void Bin3D::Ground()
{
    item_v_t items;
    itemsInBin( items );

    bool slide = true;

    while( slide )
    {
        slide = false;

        // sort by increasing height
        stable_sort( items.begin(), items.end(),
                     []( item_t a, item_t b )
        {
            return a->getHLocation() < b->getHLocation();
        });

        for( auto test = items.begin();
                test != items.end(); test++ )
        {
            // no need to test the items that are already grounded
            if( (*test)->getHLocation() == 0 )
                continue;

            // find top of highest box below test
            double highestBelow = 0;
            for( auto below = items.begin();
                    below != test; below++ )
            {
                if( (*below)->IsAboveBelow( *test ) )
                {
                    double height = (*below)->getHLocation() + (*below)->side_2()->size();
                    //cout << "height " << height << "\n";
                    if( height > highestBelow )
                        highestBelow = height;
                }
            }

            //cout << "highestBelow " << highestBelow << "\n";

            // try sliding down
            if( highestBelow < (*test)->getHLocation() )
            {
                //cout << "slide\nbefore ";
                //(*test)->Print();

                (*test)->setHLocation( highestBelow );

                //cout << "after ";
                //(*test)->Print();

                // a box was moved down, so we will start again
                slide = true;
                break;
            }

        }
    }
}
bool Bin3D::Ground( item_t test )
{
    // check if the item is already on the ground
    if( test->getHLocation() == 0 )
        return false;

    item_v_t items;
    itemsIncHeightOrder( items );

    // find top of highest box below test
    double highestBelow = 0;
    for( auto below = items.begin();
            below != items.end(); below++ )
    {
        if( (*below)->getHLocation()  >=  test->getHLocation() )
            break;

        if( (*below)->IsAboveBelow( test ) )
        {
            double height = (*below)->getHLocation() + (*below)->side_2()->size();
            //cout << "height " << height << "\n";
            if( height > highestBelow )
                highestBelow = height;
        }
    }

    if( highestBelow < test->getHLocation() )
    {
        //cout << "slide\nbefore ";
        //(*test)->Print();

        test->setHLocation( highestBelow );
        return true;
    }
    return false;
}
void Bin3D::Support()
{
    item_v_t items;
    itemsIncHeightOrder( items );

    for( auto test : items )
    {
        // check if the item is on the ground
        if( test->getHLocation() == 0 )
        {
            test->Support( 100 );
            continue;
        }

        // calculate area of items supporting test item
        double s = Support( test, items );

        test->Support( (int) ( 100 * s / test->AreaWidthLength() ) );

    }
}
double Bin3D::Support( item_t test, item_v_t& items )
{
    double s = 0;

    for( auto below : items )
    {
        if( below->getHLocation()  >=  test->getHLocation() )
            return s;

        if( below->IsAboveBelow( test ) )
        {
            // found an item below the test

            // check that it is immediatly below
            if( below->getHLocation() + below->side_2()->size() ==
                    test->getHLocation() )
            {
                s += below->OverlapArea( test );
            }
        }
    }
    return s;

}
