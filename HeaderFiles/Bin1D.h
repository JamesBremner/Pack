/*
 * File:   Bin1D.h
 * Author: arash
 *
 * Created on June 13, 2012, 11:23 AM
 */

#ifndef BIN1D_H
#define	BIN1D_H
using namespace std;

class Bin1D : public virtual Bin
{

protected:
    bin_t z_sub_bin_;

public:
    Bin1D();
    Bin1D(const Bin1D& orig);
    virtual ~Bin1D();


    bin_t z_sub_bin();
    virtual void set_z_sub_bin(bin_t value);

    virtual void itemsInBin(item_v_t &items);
    virtual void binRemSpace(vector<Bin*> &bins);
    virtual double binUtilizationRating();
    virtual void totalChildSpaceUsed( double &used );
    virtual void totalRemSpaceAvailable( double &avail);

    virtual void encodeAsJSON(stringstream &jsonStr, bool isDeep);

    virtual bool operator <( Shape &b);
    virtual bool operator >( Shape &b);
    virtual bool operator ==( Shape &b);


};

#endif	/* BIN1D_H */

