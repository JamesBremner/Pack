/*
 * File:   Bin2D.h
 * Author: arash
 *
 * Created on June 8, 2012, 5:14 PM
 */

#ifndef BIN2D_H
#define	BIN2D_H

using namespace std;

class Bin2D : public virtual Bin
{

public:

    Bin2D();
    Bin2D(const Bin2D& orig);
    virtual ~Bin2D();


    virtual void set_x_sub_bin(bin_t value);
    virtual void set_y_sub_bin(bin_t value);

    virtual void itemsInBin(item_v_t &items);
    virtual void binRemSpace(bin_v_t &bins);
    virtual double binUtilizationRating();
    virtual void totalChildSpaceUsed( double &used );
    virtual void totalRemSpaceAvailable( double &avail);
    virtual Bin * CreateNewEmptyCopy();
    virtual void Dumper();
    virtual void encodeAsJSON(stringstream &jsonStr, bool isDeep);
    virtual void CreateCutList( cCutList& l );
    virtual void DrawList( std::stringstream& ss );
    bool IsUnusedBin();

    virtual bool operator <( Shape &b);
    virtual bool operator >( Shape &b);
    virtual bool operator ==( Shape &b);

protected:



};

#endif	/* BIN2D_H */

