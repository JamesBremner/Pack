/*
 * File:   BoxPacker3D.h
 * Author: arash
 *
 * Created on June 15, 2012, 12:47 PM
 */

#ifndef BOXPACKER3D_H
#define	BOXPACKER3D_H
using namespace std;

class BoxPacker3D : public BoxPacker2D {

public:



    bool packIt( bin_t bin,  item_t item, bin_v_t &bins );


    void splitBinWidth( bin_t bin, item_t item );
    void splitBinHeight( bin_t bin, item_t item );
    void splitBinLength( bin_t bin, item_t item );


protected:

    bool checkFitsNoConstr(bin_t bin,  item_t item, bin_v_t &bins );
    map<string, double> findSubBinSizes( bin_t bin, item_t item);

    bool Fit( bin_t bin,  item_t item, bin_v_t &bins );

    /** Merge unused space
@param[in] packbin  the bin we are packing
@param[in] newbin   the new unused space
@param[in] bins     all the unused bins
@return true if the merge took place
*/
   bool merger( bin_t packbin, bin_t newbin, bin_v_t &bins );

   void Split( bin_t sub_bin, bin_t bin );

};

#endif	/* BOXPACKER3D_H */

