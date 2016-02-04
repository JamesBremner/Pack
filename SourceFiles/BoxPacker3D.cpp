#include "stdafx.h"

#ifndef NULL
#define NULL   ((void *) 0)
#endif

using namespace std;

BoxPacker3D::BoxPacker3D()
{
}

BoxPacker3D::BoxPacker3D(const BoxPacker3D& orig)
{
}

BoxPacker3D::~BoxPacker3D()
{
}


bool BoxPacker3D::packIt( bin_t bin,  item_t item, bin_v_t &bins)
{

//    cout << "BoxPacker3D::packIt\n";

//	int constraints = item->constraints();
//
//    if (constraints == Item3D::CONSTRAINT_WIDTH)
//        return checkFitsConstrWidth(bin, item, bins);
//    else if (constraints == Item3D::CONSTRAINT_HEIGHT)
//        return checkFitsConstrHeight(bin, item, bins);
//    else if (constraints == Item3D::CONSTRAINT_LENGTH)
//        return checkFitsConstrLength(bin, item, bins);
//    else if (constraints == Item3D::CONSTRAINT_WIDTH_HEIGHT)
//        return checkFitsConstrWidthHeight(bin, item, bins);
//    else if (constraints == Item3D::CONSTRAINT_WIDTH_LENGTH)
//        return checkFitsConstrWidthLength(bin, item, bins);
//    else if (constraints == Item3D::CONSTRAINT_HEIGHT_LENGTH)
//        return checkFitsConstrHeightLength(bin, item, bins);
//    else
    return Fit(bin, item, bins);

}

void BoxPacker3D::splitBinWidth(bin_t bin, item_t item)
{


    map<string, double> sides = findSubBinSizes( bin, item );
    double dx_w = sides["dx_w"];
    double dx_h = sides["dx_h"];
    double dx_l = sides["dx_l"];

    if (dx_w <= 0)
        bin->set_x_sub_bin(NULL);
    else
    {

        bin_t sub_binX( new Bin3D() );
        sub_binX->set_side_1(bin->side_1()->size_side_to(dx_w));
        sub_binX->set_side_2(bin->side_2()->size_side_to(dx_h));
        sub_binX->set_side_3(bin->side_3()->size_side_to(dx_l));
        sub_binX->set_parent_bin(bin);
        sub_binX->set_id(bin->id());
        sub_binX->setLocationWidth( bin->getLocationWidth() + item->side_1()->size() );
        sub_binX->setLocationHeight( bin->getLocationHeight() );
        sub_binX->setLocationLength( bin->getLocationLength() );

        bin->set_x_sub_bin(sub_binX);


    }


}

void BoxPacker3D::splitBinHeight(bin_t bin, item_t item)
{


    map<string, double> sides = findSubBinSizes( bin, item );
    double dy_w = sides["dy_w"];
    double dy_h = sides["dy_h"];
    double dy_l = sides["dy_l"];


    if (dy_h <= 0)
        bin->set_y_sub_bin(NULL);
    else
    {

        bin_t sub_binY( new Bin3D() );
        sub_binY->set_side_1(bin->side_1()->size_side_to(dy_w));
        sub_binY->set_side_2(bin->side_2()->size_side_to(dy_h));
        sub_binY->set_side_3(bin->side_3()->size_side_to(dy_l));
        sub_binY->set_parent_bin(bin);
        sub_binY->set_id(bin->id());
        sub_binY->setLocationHeight( bin->getLocationHeight() + item->side_2()->size() );
        sub_binY->setLocationWidth( bin->getLocationWidth() );
        sub_binY->setLocationLength( bin->getLocationLength() );
        bin->set_y_sub_bin(sub_binY);


    }

}

void BoxPacker3D::splitBinLength(bin_t bin, item_t item)
{


    map<string, double> sides = findSubBinSizes( bin, item );
    double dz_w = sides["dz_w"];
    double dz_h = sides["dz_h"];
    double dz_l = sides["dz_l"];


    if (dz_l <= 0)
        bin->set_z_sub_bin(NULL);
    else
    {

        bin_t sub_binZ ( new Bin3D() );
        sub_binZ->set_side_1(bin->side_1()->size_side_to(dz_w));
        sub_binZ->set_side_2(bin->side_2()->size_side_to(dz_h));
        sub_binZ->set_side_3(bin->side_3()->size_side_to(dz_l));
        sub_binZ->set_parent_bin(bin);
        sub_binZ->set_id(bin->id());
        sub_binZ->setLocationLength( bin->getLocationLength() + item->side_3()->size() );
        sub_binZ->setLocationHeight( bin->getLocationHeight() );
        sub_binZ->setLocationWidth( bin->getLocationWidth() );
        bin->set_z_sub_bin(sub_binZ);


    }

}

bool BoxPacker3D::checkFitsConstrWidth( Bin* bin, Item *item, vector<Bin*> &bins)
{
//    Bin3D * bin3d = dynamic_cast<Bin3D*> (bin);
//    Item3D *item3d = (Item3D*) item;
//
//
//    if (bin3d->side_2()->size() < bin3d->side_3()->size()) {
//
//        Side *tmps;
//        tmps = bin3d->side_2();
//        bin3d->set_side_2(bin3d->side_3());
//        bin3d->set_side_3(tmps);
//    }
//
//
//    if (item3d->side_2()->size() < item3d->side_3()->size()) {
//
//        Side *tmps;
//        tmps = item3d->side_2();
//        item3d->set_side_2(item3d->side_3());
//        item3d->set_side_3(tmps);
//    }
//
//    if (item3d->side_1()->size() <= bin3d->side_1()->size() &&
//            item3d->side_2()->size() <= bin3d->side_2()->size() &&
//            item3d->side_3()->size() <= bin3d->side_3()->size()) {
//
//        bin->set_item(item);
//
//        //if it fits split item and recurse
//        splitBinWidth(bin, item);
//        splitBinHeight(bin, item);
//        splitBinLength(bin, item);
//
//
//
//        if (bin3d->x_sub_bin() != NULL) {
//
//            bins.push_back(bin3d->x_sub_bin());
//
//        }
//        if (bin3d->y_sub_bin() != NULL) {
//
//            bins.push_back(bin3d->y_sub_bin());
//        }
//        if (bin3d->z_sub_bin() != NULL) {
//
//            bins.push_back(bin3d->z_sub_bin());
//        }
//
//        return true;
//
//    }

    return false;

}

bool BoxPacker3D::checkFitsConstrHeight(Bin *bin, Item *item, vector<Bin*> &bins)
{
//    Bin3D * bin3d = dynamic_cast<Bin3D*> (bin);
//    Item3D *item3d = (Item3D*) item;
//
//
//    if (bin3d->side_1()->size() < bin3d->side_3()->size()) {
//
//        Side *tmps;
//        tmps = bin3d->side_1();
//        bin3d->set_side_1(bin3d->side_3());
//        bin3d->set_side_3(tmps);
//    }
//
//
//
//    if (item3d->side_1()->size() < item3d->side_3()->size()) {
//
//        Side *tmps;
//        tmps = item3d->side_1();
//        item3d->set_side_1(item3d->side_3());
//        item3d->set_side_3(tmps);
//    }
//
//
//
//    if (item3d->side_1()->size() <= bin3d->side_1()->size() &&
//            item3d->side_2()->size() <= bin3d->side_2()->size() &&
//            item3d->side_3()->size() <= bin3d->side_3()->size()) {
//
//        bin->set_item(item);
//
//        //if it fits split item and recurse
//        splitBinWidth(bin, item);
//        splitBinHeight(bin, item);
//        splitBinLength(bin, item);
//
//        //Bin2D * bin2d = dynamic_cast<Bin2D*> (bin);
//
//        if (bin3d->x_sub_bin() != NULL) {
//
//            bins.push_back(bin3d->x_sub_bin());
//
//        }
//        if (bin3d->y_sub_bin() != NULL) {
//
//            bins.push_back(bin3d->y_sub_bin());
//        }
//        if (bin3d->z_sub_bin() != NULL) {
//
//            bins.push_back(bin3d->z_sub_bin());
//        }
//
//        return true;
//
//    }

    return false;

}

bool BoxPacker3D::checkFitsConstrLength(Bin *bin, Item *item, vector<Bin*> &bins)
{
//    Bin3D * bin3d = dynamic_cast<Bin3D*> (bin);
//    Item3D *item3d = (Item3D*) item;
//
//    //sort both bin and item
//    if (bin3d->side_1()->size() < bin3d->side_2()->size()) {
//
//        Side *tmps;
//        tmps = bin3d->side_1();
//        bin3d->set_side_1(bin3d->side_2());
//        bin3d->set_side_2(tmps);
//    }
//
//
//    if (item3d->side_1()->size() < item3d->side_2()->size()) {
//
//        Side *tmps;
//        tmps = item3d->side_1();
//        item3d->set_side_1(item3d->side_2());
//        item3d->set_side_2(tmps);
//    }
//
//
//    if (item3d->side_1()->size() <= bin3d->side_1()->size() &&
//            item3d->side_2()->size() <= bin3d->side_2()->size() &&
//            item3d->side_3()->size() <= bin3d->side_3()->size()) {
//
//        bin->set_item(item);
//
//        //if it fits split item and recurse
//        splitBinWidth(bin, item);
//        splitBinHeight(bin, item);
//        splitBinLength(bin, item);
//
//        //Bin2D * bin2d = dynamic_cast<Bin2D*> (bin);
//
//        if (bin3d->x_sub_bin() != NULL) {
//
//            bins.push_back(bin3d->x_sub_bin());
//
//        }
//        if (bin3d->y_sub_bin() != NULL) {
//
//            bins.push_back(bin3d->y_sub_bin());
//        }
//        if (bin3d->z_sub_bin() != NULL) {
//
//            bins.push_back(bin3d->z_sub_bin());
//        }
//
//
//        return true;
//
//    }
//
    return false;

}

bool BoxPacker3D::Fit( bin_t bin,  item_t item, bin_v_t &bins )
{
//    cout << "BoxPacker3D::Fit\n";
//    bin->Print();
//    item->Print();

    if( bin->Fit( item ) )
    {
        // item fits without rotation
    }
    else
    {
        // item does not fit
        // try rotating it

        item->Spin( 1 );
        if( bin->Fit( item ) )
        {
            //cout << "spin 1";
        }
        else
        {
            item->Spin( 1 );
            item->Spin( 2 );
            if( bin->Fit( item ) )
            {
                //cout << "spin 2";
            }
            else
            {
                item->Spin( 2 );
                item->Spin( 3 );
                if( bin->Fit( item ) )
                {
                    //cout << "spin 3";
                }
                else
                {
                    // Does not fit in any orientation
                    // spin back to original and give up
                    //cout << "No fit\n";
                    item->Spin( 3 );
                    return false;
                }
            }
        }
    }

    // packing item

    // add item to bin
    bin->set_item(item);

    item->setBin( bin->Root( bin )->progid() );
    item->setPackSeq();
    item->setHLocation( bin->getLocationHeight() );
    item->setWLocation( bin->getLocationWidth() );
    item->setLLocation( bin->getLocationLength() );
    item->SpinAxisCalculate();

//    if( item->getHLocation() > 0 )
//    {
//        // occasionally the item will be hanging in mid-air
//        // this is due to fragmentation of the unused space
//        // slide it downwards so that it will be supported
//        bin->Root( bin )->Ground( item );
//        item_v_t h_items;
//        bin->Root( bin )->itemsIncHeightOrder( h_items );
//        if( bin->Root( bin )->Support( item, h_items ) / item->AreaWidthLength() < 0.7 )
//        {
//            cout << "low support\n";
//            bin->set_item( NULL );
//            item->setBin( -1 );
//            return false;
//        }
//        // restore original item height
//        item->setHLocation( bin->getLocationHeight() );
//    }


//    item->Print();

    splitBinWidth(bin, item);
    splitBinHeight(bin, item);
    splitBinLength(bin, item);


    if (bin->get_x_sub_bin() != NULL)
    {
        // we have created a new bin from the unused space when the item was added to the bin
        // check if this space could be merged with any previously unused space in the user specified bin
        if( ! merger( bin, bin->get_x_sub_bin(), bins ) )
        {

            bins.push_back(bin->get_x_sub_bin());
        }
        else
        {
            // unused space was merged, so forget about it
            bin->set_x_sub_bin( NULL );
        }

    }
    if (bin->get_y_sub_bin() != NULL)
    {
        // we have created a new bin from the unused space when the item was added to the bin
        // check if this space could be merged with any previously unused space in the user specified bin
        if( ! merger( bin, bin->get_y_sub_bin(), bins ) )
        {

            bins.push_back(bin->get_y_sub_bin());
        }
        else
        {
            // unused space was merged, so forget about it
            bin->set_y_sub_bin( NULL );
        }


    }
    if (bin->get_z_sub_bin() != NULL)
    {
        // we have created a new bin from the unused space when the item was added to the bin
        // check if this space could be merged with any previously unused space in the user specified bin
        if( ! merger( bin, bin->get_z_sub_bin(), bins ) )
        {

            bins.push_back(bin->get_z_sub_bin());
        }
        else
        {
            // unused space was merged, so forget about it
            bin->set_z_sub_bin( NULL );
        }


    }

    return true;

}

bool BoxPacker3D::checkFitsNoConstr( bin_t bin,  item_t item, bin_v_t &bins )
{

    cout << "\nBoxPacker3D::checkFitsNoConstr\n";
    //sort both bin and item
    if (bin->side_1()->size() < bin->side_2()->size())
    {

        Side *tmps;
        tmps = bin->side_1();
        bin->set_side_1(bin->side_2());
        bin->set_side_2(tmps);
    }


    if (bin->side_1()->size() < bin->side_3()->size())
    {

        Side *tmps;
        tmps = bin->side_1();
        bin->set_side_1(bin->side_3());
        bin->set_side_3(tmps);
    }

    if (bin->side_2()->size() < bin->side_3()->size())
    {

        Side *tmps;
        tmps = bin->side_2();
        bin->set_side_2(bin->side_3());
        bin->set_side_3(tmps);
    }

    cout << "DBG1 ";
    item->Print();

    if (item->side_1()->size() < item->side_2()->size())
    {

        Side *tmps;
        tmps = item->side_1();
        item->set_side_1(item->side_2());
        item->set_side_2(tmps);
    }

    if (item->side_1()->size() < item->side_3()->size())
    {

        Side *tmps;
        tmps = item->side_1();
        item->set_side_1(item->side_3());
        item->set_side_3(tmps);
    }
    bin->Print();
    item->Print();
    if (item->side_2()->size() < item->side_3()->size())
    {

        Side *tmps;
        tmps = item->side_2();
        item->set_side_2(item->side_3());
        item->set_side_3(tmps);
    }

    cout << "DBG2 ";
    item->Print();

    if (item->side_1()->size() <= bin->side_1()->size() &&
            item->side_2()->size() <= bin->side_2()->size() &&
            item->side_3()->size() <= bin->side_3()->size())
    {

        // packing item

        bin->set_item(item);
        item->setBin( bin->Root( bin )->progid() );
        item->setHLocation( bin->getLocationHeight() );
        item->setWLocation( bin->getLocationWidth() );
        item->setLLocation( bin->getLocationLength() );

        if( item->side_1()->orig_side() == 'w' )
            item->SpinAxis( 1 );
        else  if( item->side_2()->orig_side() == 'h' )
            item->SpinAxis( 2 );
        else  if( item->side_3()->orig_side() == 'l' )
            item->SpinAxis( 3 );
        else
            item->SpinAxis( 0 );


        bin->Print();
        item->Print();

        splitBinWidth(bin, item);
        splitBinHeight(bin, item);
        splitBinLength(bin, item);


        if (bin->get_x_sub_bin() != NULL)
        {
            bins.push_back(bin->get_x_sub_bin());

        }
        if (bin->get_y_sub_bin() != NULL)
        {

            bins.push_back(bin->get_y_sub_bin());
        }
        if (bin->get_z_sub_bin() != NULL)
        {

            bins.push_back(bin->get_z_sub_bin());
        }

        return true;

    }


    return false;

}

bool BoxPacker3D::checkFitsConstrWidthHeight(Bin *bin, Item *item, vector<Bin*> &bins)
{
//    Bin3D * bin3d = dynamic_cast<Bin3D*> (bin);
//    Item3D *item3d = (Item3D*) item;
//
//    if (item3d->side_1()->size() <= bin3d->side_1()->size() &&
//            item3d->side_2()->size() <= bin3d->side_2()->size() &&
//            item3d->side_3()->size() <= bin3d->side_3()->size()) {
//
//        bin->set_item(item);
//
//        //if it fits split item and recurse
//        splitBinWidth(bin, item);
//        splitBinHeight(bin, item);
//        splitBinLength(bin, item);
//
//
//        if (bin3d->z_sub_bin() != NULL) {
//
//            bins.push_back(bin3d->z_sub_bin());
//        }
//
//        return true;
//
//    }
//
    return false;

}

bool BoxPacker3D::checkFitsConstrWidthLength(Bin *bin, Item *item, vector<Bin*> &bins)
{
//    Bin3D * bin3d = dynamic_cast<Bin3D*> (bin);
//    Item3D *item3d = (Item3D*) item;
//
//    if (item3d->side_1()->size() <= bin3d->side_1()->size() &&
//            item3d->side_2()->size() <= bin3d->side_2()->size() &&
//            item3d->side_3()->size() <= bin3d->side_3()->size()) {
//
//        bin->set_item(item);
//
//        //if it fits split item and recurse
//        splitBinWidth(bin, item);
//        splitBinHeight(bin, item);
//        splitBinLength(bin, item);
//
//
//        if (bin3d->y_sub_bin() != NULL) {
//
//            bins.push_back(bin3d->y_sub_bin());
//        }
//
//        return true;
//
//    }

    return false;

}

bool BoxPacker3D::checkFitsConstrHeightLength(Bin *bin, Item *item, vector<Bin*> &bins)
{
//    Bin3D * bin3d = dynamic_cast<Bin3D*> (bin);
//    Item3D *item3d = (Item3D*) item;
//
//    if (item3d->side_1()->size() <= bin3d->side_1()->size() &&
//            item3d->side_2()->size() <= bin3d->side_2()->size() &&
//            item3d->side_3()->size() <= bin3d->side_3()->size()) {
//
//        bin->set_item(item);
//
//        //if it fits split item and recurse
//        splitBinWidth(bin, item);
//        splitBinHeight(bin, item);
//        splitBinLength(bin, item);
//
//
//        if (bin3d->x_sub_bin() != NULL) {
//
//            bins.push_back(bin3d->x_sub_bin());
//        }
//
//        return true;
//
//    }

    return false;

}

map<string, double> BoxPacker3D::findSubBinSizes( bin_t bin, item_t item)
{

    double w_diff = bin->side_1()->size() - item->side_1()->size();
    double h_diff = bin->side_2()->size() - item->side_2()->size();
    double l_diff = bin->side_3()->size() - item->side_3()->size();


    double dx_w, dx_h, dx_l;
    double dy_w, dy_h, dy_l;
    double dz_w, dz_h, dz_l;

    if (l_diff >= w_diff && w_diff >= h_diff)
    {

        dx_w = bin->side_1()->size() - item->side_1()->size();
        dx_h = item->side_2()->size();
        dx_l = bin->side_3()->size();

        dy_w = bin->side_1()->size();
        dy_h = bin->side_2()->size() - item->side_2()->size();
        dy_l = bin->side_3()->size();

        dz_w = item->side_1()->size();
        dz_h = item->side_2()->size();
        dz_l = bin->side_3()->size() - item->side_3()->size();

    }
    else if (l_diff >= h_diff && h_diff >= w_diff)
    {

        dx_w = bin->side_1()->size() - item->side_1()->size();
        dx_h = bin->side_2()->size();
        dx_l = bin->side_3()->size();

        dy_w = item->side_1()->size();
        dy_h = bin->side_2()->size() - item->side_2()->size();
        dy_l = bin->side_3()->size();

        dz_w = item->side_1()->size();
        dz_h = item->side_2()->size();
        dz_l = bin->side_3()->size() - item->side_3()->size();

    }
    else if (w_diff >= h_diff && h_diff >= l_diff)
    {

        dx_w = bin->side_1()->size() - item->side_1()->size();
        dx_h = item->side_2()->size();
        dx_l = item->side_3()->size();

        dy_w = bin->side_1()->size();
        dy_h = bin->side_2()->size() - item->side_2()->size();
        dy_l = item->side_3()->size();

        dz_w = bin->side_1()->size();
        dz_h = bin->side_2()->size();
        dz_l = bin->side_3()->size() - item->side_3()->size();

    }
    else if (w_diff >= l_diff && l_diff >= h_diff)
    {
        dx_w = bin->side_1()->size() - item->side_1()->size();
        dx_h = item->side_2()->size();
        dx_l = item->side_3()->size();

        dy_w = bin->side_1()->size();
        dy_h = bin->side_2()->size() - item->side_2()->size();
        dy_l = bin->side_3()->size();

        dz_w = bin->side_1()->size();
        dz_h = item->side_2()->size();
        dz_l = bin->side_3()->size() - item->side_3()->size();

    }
    else if (h_diff >= w_diff && w_diff >= l_diff)
    {
        dx_w = bin->side_1()->size() - item->side_1()->size();
        dx_h = bin->side_2()->size();
        dx_l = item->side_3()->size();

        dy_w = item->side_1()->size();
        dy_h = bin->side_2()->size() - item->side_2()->size();
        dy_l = item->side_3()->size();

        dz_w = bin->side_1()->size();
        dz_h = bin->side_2()->size();
        dz_l = bin->side_3()->size() - item->side_3()->size();

    }
    else if (h_diff >= l_diff && l_diff >= w_diff)
    {

        dx_w = bin->side_1()->size() - item->side_1()->size();
        dx_h = bin->side_2()->size();
        dx_l = bin->side_3()->size();

        dy_w = item->side_1()->size();
        dy_h = bin->side_2()->size() - item->side_2()->size();
        dy_l = item->side_3()->size();

        dz_w = item->side_1()->size();
        dz_h = bin->side_2()->size();
        dz_l = bin->side_3()->size() - item->side_3()->size();

    }

    map<string, double> sides;
    sides["dx_w"] = dx_w;
    sides["dx_h"] = dx_h;
    sides["dx_l"] = dx_l;

    sides["dy_w"] = dy_w;
    sides["dy_h"] = dy_h;
    sides["dy_l"] = dy_l;

    sides["dz_w"] = dz_w;
    sides["dz_h"] = dz_h;
    sides["dz_l"] = dz_l;

    return sides;

}

bool BoxPacker3D::merger( bin_t packbin, bin_t newbin, bin_v_t &bins )
{

//    cout << "\n->3DMerger" << endl;
//    newbin->Print();
//    cout << "candidates:" << endl;
    bin_t newbinroot = newbin->Root( newbin );
    // loop over all bins
    for( auto bin : bins )
    {
        // check that this is part of the user specified bin we are adding to
        if( newbinroot != bin->Root( bin ) )
            continue;
        // check that this is not the bin we are packing item into
        if( packbin == bin )
            continue;
        // we have a merge candidate
        // bin->Print();

        if( newbin->side_1()->size() == bin->side_1()->size() &&
                newbin->side_2()->size() == bin->side_2()->size() )
        {
            if( newbin->getLocationLength() + newbin->side_3()->size() ==
                    bin->getLocationLength() )
            {
                // cout << "merge!\n";
                bin->side_3()->set_size(  newbin->side_3()->size() + bin->side_3()->size());
                bin->setLocationLength(  newbin->getLocationLength() );
                return true;
            }
            if( bin->getLocationLength() + bin->side_3()->size() ==
                    newbin->getLocationLength() )
            {
                //cout << "merge!\n";
                bin->side_3()->set_size(  newbin->side_3()->size() + bin->side_3()->size());
                return true;
            }
        }
        if( newbin->side_1()->size() == bin->side_1()->size() &&
                newbin->side_3()->size() == bin->side_3()->size() )
        {
            if( newbin->getLocationHeight() + newbin->side_2()->size() ==
                    bin->getLocationHeight() )
            {
                //cout << "merge!\n";
                bin->side_2()->set_size(  newbin->side_2()->size() + bin->side_2()->size());
                bin->setLocationHeight(  newbin->getLocationHeight() );
                return true;
            }
            if( bin->getLocationHeight() + bin->side_2()->size() ==
                    newbin->getLocationHeight() )
            {
                //cout << "merge!\n";
                bin->side_2()->set_size(  newbin->side_2()->size() + bin->side_2()->size());
                return true;
            }
        }
        if( newbin->side_2()->size() == bin->side_2()->size() &&
                newbin->side_3()->size() == bin->side_3()->size() )
        {
            if( newbin->getLocationWidth() + newbin->side_1()->size() ==
                    bin->getLocationWidth() )
            {
                //cout << "merge!\n";
                bin->side_1()->set_size(  newbin->side_1()->size() + bin->side_1()->size());
                bin->setLocationWidth(  newbin->getLocationWidth() );
                return true;
            }
            if( bin->getLocationWidth() + bin->side_1()->size() ==
                    newbin->getLocationWidth() )
            {
                // cout << "merge!\n";
                bin->side_1()->set_size(  newbin->side_1()->size() + bin->side_1()->size());
                return true;
            }
        }
    }

    return false;
}
