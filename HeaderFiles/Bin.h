/*
 * File:   Bin.h
 * Author: arash
 *
 * Created on June 13, 2012, 11:51 AM
 */

#ifndef BIN_H
#define	BIN_H

using namespace std;

struct bin_build_instructions;

class Bin : public virtual Shape2D, public std::enable_shared_from_this< Bin >
{

public:

    struct bin_build_instructions
    {
        string bin_id;
        vector<string> size_v;
        string dimension_units;
        bool can_copy;
    };

    Bin();
    Bin(const Bin& orig);
    virtual ~Bin();

    virtual bool Fit( item_t item ) { return false; }


    bin_t parent_bin();
    void set_parent_bin( bin_t value );
    void set_item ( item_t item2D );
    virtual bin_t Root( bin_t bin );


    virtual void Dumper() {}


    virtual void itemsInBin(item_v_t &items) = 0;
    virtual void binRemSpace(bin_v_t &bins) = 0;
    virtual Bin* CreateNewEmptyCopy()
    {
        return NULL;
    }

    virtual int itemsInBinCount();
    virtual int remsInBinCount();
    void setCanCopy( bool flag )
    {
        myCanCopy = flag;
    }
    bool CanCopy()
    {
        return myCanCopy;
    }

    virtual double binSpaceUsed();
    virtual double remSpaceAvail();
    //this one takes into account how much large space is left over that can perhaps be used for other things
    virtual double adjBinSpaceUsed();
    //in the grand scheme of things where does this bin fall
    virtual double binUtilizationRating() = 0;

    virtual void totalChildSpaceUsed( double &used ) = 0;
    virtual void totalRemSpaceAvailable( double &avail) = 0;
    virtual void encodeAsJSON(stringstream &jsonStr, bool isDeep) = 0;

    double getLocationHeight()
    {
        return myHOffsetFromRoot;
    }
    void setLocationHeight( double h ) { myHOffsetFromRoot = h; }
    double getLocationWidth()
    {
        return myWOffsetFromRoot;
    }
    void setLocationWidth( double w ) { myWOffsetFromRoot = w;}
    double getLocationLength()
    {
        return myLOffsetFromRoot;
    }
    void setLocationLength( double w ) { myLOffsetFromRoot = w;}

    bin_t get_x_sub_bin() { return x_sub_bin_; }
    bin_t get_y_sub_bin() { return y_sub_bin_; }
    bin_t get_z_sub_bin() { return z_sub_bin_; }
    virtual void set_x_sub_bin(bin_t value) { }
    virtual void set_y_sub_bin(bin_t value) { }
    virtual void set_z_sub_bin( bin_t value )  { }

    virtual bool operator <( Shape &b) = 0;
    virtual bool operator >( Shape &b) = 0;
    virtual bool operator ==( Shape &b) = 0;

    static Bin* Build(  bin_build_instructions& instructions );

    virtual void CreateCutList( cCutList& l ) {}

    void Print();

protected:


    bin_t parent_bin_;
    bin_t y_sub_bin_;
    bin_t x_sub_bin_;
    bin_t z_sub_bin_;
    item_t item_;
    bool myCanCopy;
    double myHOffsetFromRoot;
    double myWOffsetFromRoot;
    double myLOffsetFromRoot;
};

#endif	/* BIN_H */

