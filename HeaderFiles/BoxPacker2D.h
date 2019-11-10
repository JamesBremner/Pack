/*
 * File:   Packer2D.h
 * Author: arash
 *
 * Created on June 8, 2012, 11:06 AM
 */

#ifndef BOXPACKER2D_H
#define	BOXPACKER2D_H

using namespace std;

class BoxPacker2D : public Packer
{

public:


    BoxPacker2D();
    BoxPacker2D(const BoxPacker2D& orig);
    virtual ~BoxPacker2D();

    virtual void packThem( bin_v_t& ref_bins, item_v_t& items);
    virtual bool packIt( bin_t bin, item_t item, bin_v_t &bins );
    virtual void splitBinWidth( bin_t bin, item_t item );
    virtual void splitBinHeight( bin_t bin, item_t item );


protected:


    virtual bool checkFitsConstrWidth(Bin *bin, Item *item, vector<Bin*> &bins);
    virtual bool checkFitsConstrHeight(Bin *bin, Item *item, vector<Bin*> &bins);
    virtual bool checkFitsNoConstr( bin_t bin, item_t item, bin_v_t &bins );

    /** Sort unused spaces and bins into order we want to try packing the next item
    @param[in] bins
    */
    void Sort( bin_v_t& bins );

    /** Merge unused space
    @param[in] packbin  the bin we are packing
    @param[in] newbin   the new unused space
    @param[in] bins     all the unused bins
    @return true if the merge took place
    */
    virtual bool merger( bin_t packbin, bin_t newbin, bin_v_t &bins );
};

#endif	/* BOXPACKER2D_H */

