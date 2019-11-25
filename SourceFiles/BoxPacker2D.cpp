#include <random>
#include <chrono>
#include "cPackEngine.h"

#ifndef NULL
#define NULL   ((void *) 0)
#endif

using namespace std;

BoxPacker2D::BoxPacker2D()
{
}

BoxPacker2D::BoxPacker2D(const BoxPacker2D& orig)
{
    BoxPacker2D();
}

BoxPacker2D::~BoxPacker2D()
{

}

void BoxPacker2D::Sort( bin_v_t& bins )
{
//    cout << "=> Sort " << bins.size() << "\n";
//    theWorld.PrintAllBins();

    sort( bins.begin(), bins.end(),
          []( bin_t a, bin_t b )
    {
        // for a onebin pack, we want to work our way up from the bottom
        if( thePackEngine.myfOneBin )
        {
            return a->getLocationHeight() < b->getLocationHeight();
        }
        else
        {
            /*
              for multiple bin packing
              we try the unused spaces in partially packed bins
              smallest first
              then we try the largest unused bin
            */

//            bool Aused = ! a->IsUnusedBin();
//            bool Bused = ! b->IsUnusedBin();
//
//            if( ( ! Aused ) && Bused  )
//            {
//                cout << "swap " << a->id() << " " << b->id() << "\n";
//                // move used bin before unused
//                return true;
//            }
//
//            return false;

            if( ! a->IsUnusedBin() )
            {
                if( ! b->IsUnusedBin() )
                    return a->volume() < b->volume();   // smaller spaces first
                else
                    return true;        // spaces before empty bins
            }
            if( ! b->IsUnusedBin() )
                return false;            // spaces before empty bins, so this is in wrong order

            return a->volume() >= b->volume();      // bigger empty bins first

        }
    });

//    cout << "avalable bins: ";
//    for( auto member : bins )
//    {
//        cout << member->id() << " in " << member->Root( member )->id() << ", ";
//    }
//    cout << "\n";
}

void BoxPacker2D::packThem( bin_v_t& ref_bins, item_v_t& items )
{
    bin_v_t bins( ref_bins );

    items[0]->ClearPackSeq();

    if( ! thePackEngine.myfRandom )
    {
        // pack items starting with largest
        sort( items.begin(), items.end(),
              []( item_t a, item_t b )
        {
            return a->area() > b->area();
        });
    }
    else
    {
        // randomize
        std::default_random_engine engine
        (
            std::chrono::system_clock::now().time_since_epoch().count() );
        std::shuffle(items.begin(), items.end(), engine);
    }

//    cout << "packthem items\n";
//    for( auto i : items )
//    {
//        cout << i->id() <<" "<< i->side_1()->size() << " x " << i->side_2()->size() << "\n";
//    }

    // three passes, one for each positional constraint
    for( int kPositionPass = 0; kPositionPass < 3; kPositionPass++ )
    {

        // loop over items
        for( unsigned k=0; k < items.size(); ++k )
        {
            if( items[k]->IsPacked() )
                continue;

            switch( kPositionPass )
            {
            case 0:
                // first pack the bottom only items
                if( items[k]->PositionConstraints() != 1 )
                    continue;
                break;
            case 1:
                // now pack the any position items
                if( items[k]->PositionConstraints() != 0 )
                    continue;
                break;
            case 2:
                // finally pack the top items
                if( items[k]->PositionConstraints() != 2 )
                    continue;
                break;
            }

            /*
             sort unused spaces and empty bins
             into order to try fitting the item into
            */

            Sort( bins );

            // loop over bins until a fit is found

            bool is_bin_found = false;
            int bin_found_index = 0;
            for( auto member : bins )
            {
                // cout << "try " << items[k]->id() << " in "<< member->id() << "\n";
                if ( packIt( member, items[k], bins ) )
                {
                    //cout << "added item to bin " << member->id() << "\n";
                    is_bin_found = true;
                    break;
                }
                bin_found_index++;
            }

            if ( is_bin_found == true )
            {

                bin_t used = *(bins.begin() + bin_found_index);
                bins.erase( bins.begin() + bin_found_index );

                if( ! used->HasParent() )
                {
                    // about to pack an item in an unused bin
                    if( used->CanCopy() )
                    {
                        // we have an endless supply of there
                        // get a new bin ready for future use
                        bin_t new_bin( used->CreateNewEmptyCopy() );
                        bins.push_back( new_bin );
                        ref_bins.push_back( new_bin );
                    }
                }

            }
            else
            {
                // this item would not fit in any of the bins we have available
                thePackEngine.myUnpackedItems.push_back( items[k] );
            }
        }

        // delete unused extra bins
        pack::RemoveUnusedBins( thePackEngine );

    }
}



bool BoxPacker2D::packIt( bin_t bin, item_t item, bin_v_t &bins )
{

    //cout << "BoxPacker2D::packIt\n";

//    int constraints = item->constraints();

//    if ( constraints == Item2D::CONSTRAINT_WIDTH)
//        return checkFitsConstrWidth(bin, item, bins);
//    else if ( constraints == Item2D::CONSTRAINT_HEIGHT )
//        return checkFitsConstrHeight(bin, item, bins);
//    else
    return Fits(bin, item, bins );



}

bool BoxPacker2D::Fits( bin_t bin, item_t item, bin_v_t &bins )
{
    if( ! item->FitsInto( bin) )
    {
        if( !item->IsSpinAllowed( 1 ))
        {
            // does not fit
            return false;
        }
        else
        {
            // try rotating the item
            item->Spin(0);
            if( ! item->FitsInto( bin) )
            {
                // rotated item does not fit
                item->Spin(0);
                return false;
            }
            item->setSpinLocation( true );
        }
    }

    // fit found

//        cout << "packing item " << item->progid() << " ( " << item->getSpin() << " ) into bin " << bin->progid();
//        cout << " "<< bin->side_1()->size() <<" x "<< bin->side_2()->size();
//        cout << " located at " << bin->getLocationHeight() << "," << bin->getLocationWidth() << endl;
//        //if( bin_rotated ) cout << "bin rotated ";
//        if( item->getSpinLocation()  ) cout << "item rotated ";
//        cout << endl;

    bin->set_item( item );
    item->setBin( bin->Root( bin )->progid() );
    item->setHLocation( bin->getLocationHeight() );
    item->setWLocation( bin->getLocationWidth() );

    //if it fits split item and recurse
    splitBinWidth( bin, item );
    splitBinHeight( bin, item );


    if ( bin->get_x_sub_bin() != NULL )
    {
//            cout << "x_sub_bin " << bin2d->x_sub_bin()->progid() << " " <<
//                 bin2d->x_sub_bin()->side_1()->size() << " by " << bin2d->x_sub_bin()->side_2()->size() <<
//                 " at " << bin2d->x_sub_bin()->getLocationHeight() << "," <<  bin2d->x_sub_bin()->getLocationWidth() <<endl;
//

        // we have created a new bin from the unused space when the item was added to the bin
        // check if this space could be merged with any previously unused space in the user specified bin
        if( ! merger( bin, bin->get_x_sub_bin(), bins ) )
        {
            // no merge possible, so add unused space bin to total list of unused bins
            bins.push_back( bin->get_x_sub_bin() );

        }
        else
        {
            // unused space was merge, so forget about it
            // TODO: Check if this is a memory leak!
            bin->set_x_sub_bin( NULL );
        }

    }

    if( bin->get_y_sub_bin() != NULL )
    {
//            cout << "y_sub_bin " << bin2d->y_sub_bin()->progid() << " " <<
//                 bin2d->y_sub_bin()->side_1()->size() << " by " << bin2d->y_sub_bin()->side_2()->size() <<
//                 " at " << bin2d->y_sub_bin()->getLocationHeight() << "," <<  bin2d->y_sub_bin()->getLocationWidth() <<endl;

        if( ! merger( bin, bin->get_y_sub_bin(), bins ) )
        {

            bins.push_back( bin->get_y_sub_bin() );

        }
        else
        {
            bin->set_y_sub_bin( NULL );
        }
    }

    return true;

}

bool BoxPacker2D::merger( bin_t packbin, bin_t newbin, bin_v_t &bins )
{
    //cout << "->Merger" << endl;
    //newbin->Dumper();
    //cout << "candidates:" << endl;
    bin_t newbinroot = newbin->Root( newbin );
    // loop over all bins
    for( auto bin : bins )
    {
        // check that this is part of the user specified bin we are adding to
        if( ! newbin->IsSameRoot( bin) )
            continue;
        // check that this is not the bin we are packing item into
        if( packbin == bin )
            continue;
        // we have a merge candidate
//        bin->Dumper();
        if( newbin->side_1()->size() == bin->side_1()->size() )
        {
            if( newbin->getLocationHeight() + newbin->side_2()->size() ==
                    bin->getLocationHeight() )
            {
                //cout << "merge!" << endl;
                bin->side_2()->set_size( newbin->side_2()->size() + bin->side_2()->size() );
                bin->setLocationHeight( newbin->getLocationHeight() );
                return true;
            }
            else if ( bin->getLocationHeight() + bin->side_2()->size() ==
                      newbin->getLocationHeight() )
            {
                //cout << "merge!" << endl;
                bin->side_2()->set_size( newbin->side_2()->size() + bin->side_2()->size() );
                return true;
            }
        }
        else if( newbin->side_2()->size() == bin->side_2()->size() )
        {
            if( newbin->getLocationWidth() + newbin->side_1()->size() ==
                    bin->getLocationWidth() )
            {
                //cout << "merge!" << endl;
                bin->side_1()->set_size( newbin->side_1()->size() + bin->side_1()->size() );
                bin->setLocationWidth(newbin->getLocationWidth() );
                return true;
            }
            else if ( bin->getLocationWidth() + bin->side_1()->size() ==
                      newbin->getLocationWidth() )
            {
                //cout << "merge!" << endl;
                bin->side_1()->set_size( newbin->side_1()->size() + bin->side_1()->size() );
                return true;
            }
        }
    }
//    cout << "<-Merger" << endl;
    return false;
}

void BoxPacker2D::splitBinWidth( bin_t bin, item_t item )
{

    double dx_w = bin->side_1()->size() - item->side_1()->size();
    double dx_h = item->side_2()->size();



    if ( dx_w <= 0 )
        bin->set_x_sub_bin( NULL );
    else
    {

        bin_t sub_binX( new Bin2D);
        sub_binX->set_side_1( bin->side_1()->size_side_to( dx_w ));
        sub_binX->set_side_2( bin->side_2()->size_side_to( dx_h ));
        sub_binX->set_parent_bin( bin );
        sub_binX->set_original_parent_bin( bin->Root( bin ) );
        sub_binX->set_id(bin->id());
        sub_binX->setLocationWidth( bin->getLocationWidth() + item->side_1()->size() );
        sub_binX->setLocationHeight( bin->getLocationHeight() );
        bin->set_x_sub_bin( sub_binX );


    }


}

void BoxPacker2D::splitBinHeight( bin_t bin, item_t item )
{

    double dy_w = bin->side_1()->size();
    double dy_h = bin->side_2()->size() - item->side_2()->size();



    if ( dy_h <= 0 )
        bin->set_y_sub_bin( NULL );
    else
    {

        bin_t sub_binY( new Bin2D() );
        sub_binY->set_side_1( bin->side_1()->size_side_to( dy_w ));
        sub_binY->set_side_2( bin->side_2()->size_side_to( dy_h ));
        sub_binY->set_parent_bin( bin );
        sub_binY->set_original_parent_bin( bin->Root( bin ) );
        sub_binY->set_id(bin->id());
        sub_binY->setLocationHeight( bin->getLocationHeight() + item->side_2()->size() );
        sub_binY->setLocationWidth( bin->getLocationWidth() );
        bin->set_y_sub_bin( sub_binY );


    }

}
