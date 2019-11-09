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
        float maxWeight;
    };

    Bin();
    Bin(const Bin& orig);
    virtual ~Bin();

    /** Will item fit geometrically into bin */
    virtual bool Fit( item_t item ) { return false; }

    /** Can bin take weight of another item */
    virtual bool FitWeight( item_t item ) { return false; };

    bool HasParent();
    bin_t parent_bin();
    bin_t original_parent_bin();
    void set_parent_bin( bin_t value );
    void set_original_parent_bin( bin_t value );

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
    virtual string getCSV() { return string(""); }
    virtual string getSTL( int offset ) { return string(""); }

    double getLocationHeight()
    {
        return myHOffsetFromRoot;
    }
    double getLocationBottom()
    {
        return myHOffsetFromRoot + side_2()->size();
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

    virtual bool IsSameRoot( bin_t other )
    {
        int id;
        if( ! myOriginalParentBin )
            id = progid();
        else
            id = myOriginalParentBin->progid();

        return ( id == other->original_parent_bin()->progid() );
    }

    static Bin* Build(  bin_build_instructions& instructions );

    virtual void CreateCutList( cCutList& l ) {}
    virtual void DrawList( std::stringstream& ss ) {  }

    void Print();

    float MaxWeight()
    {
        return myMaxWeight;
    }
    void MaxWeight( float w )
    {
        myMaxWeight = w;
    }

    virtual void Ground() {}
    virtual bool Ground( item_t item ) { return false; }
    virtual void Support( ) {}
    virtual void itemsIncHeightOrder( item_v_t &items ) {}
    virtual double Support( item_t test, item_v_t& items ) { return 0.0; }
    virtual bool IsUnusedBin() { return false; }

protected:


    bin_t myParentBin;
    bin_t myOriginalParentBin;
    bin_t y_sub_bin_;
    bin_t x_sub_bin_;
    bin_t z_sub_bin_;
    item_t item_;
    bool myCanCopy;
    double myHOffsetFromRoot;
    double myWOffsetFromRoot;
    double myLOffsetFromRoot;
    float myMaxWeight;
};

#endif	/* BIN_H */

