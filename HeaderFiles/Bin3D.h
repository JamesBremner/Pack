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


    void itemsInBin(item_v_t &items);
    void binRemSpace(bin_v_t &bins);
    double binUtilizationRating();
    void totalChildSpaceUsed( double &used );
    void totalRemSpaceAvailable( double &avail);

    double binSpaceUsed();
    double remSpaceAvail();

    bool Fit( item_t item );

    virtual void encodeAsJSON(stringstream &jsonStr, bool isDeep);

    bool operator <( Shape &b);
    bool operator >( Shape &b);
    bool operator ==( Shape &b);

protected:


};

#endif	/* BIN3D_H */

