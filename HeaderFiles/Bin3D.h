/*
 * File:   Bin3D.h
 * Author: arash
 *
 * Created on June 14, 2012, 10:40 AM
 */

#ifndef BIN3D_H
#define	BIN3D_H
using namespace std;

class Bin3D : public Bin1D, public Bin2D, public Shape3D
{

public:
    Bin3D();
    Bin3D(const Bin3D& orig);

	Bin * CreateNewEmptyCopy();

    virtual ~Bin3D();

    void set_x_sub_bin(bin_t value);
    void set_y_sub_bin(bin_t value);
    void set_z_sub_bin(bin_t value);

	virtual void Dumper();

    /** The items packed into the bin, in random order
    */
    void itemsInBin(item_v_t &items);

    /** The items packed into the bin, in packing order
    */
    void itemsInPackOrder( item_v_t &items );

    /** The items packed into the bin, in increasing height order
    */
    void itemsIncHeightOrder( item_v_t &items );

    void binRemSpace(bin_v_t &bins);
    double binUtilizationRating();
    void totalChildSpaceUsed( double &used );
    void totalRemSpaceAvailable( double &avail);

    double binSpaceUsed();
    double remSpaceAvail();

    bool Fit( item_t item );

    virtual void encodeAsJSON(stringstream &jsonStr, bool isDeep);
    string getCSV();
    virtual void Ground();

    /** if item has no support slide down until supported

    @param[in] item to test

    @return true if slide occurred
    */
    bool Ground( item_t item );

    /** Calculate item support for all items in bin
    */
    void Support();

    /** Calculate support for a single item

    @param[in] test calculate suppirt for this item
    @param[in] items in bin in height order

    @return area supported

    */
    double Support( item_t test, item_v_t& items );

    bool operator <( Shape &b);
    bool operator >( Shape &b);
    bool operator ==( Shape &b);

protected:


};

#endif	/* BIN3D_H */

