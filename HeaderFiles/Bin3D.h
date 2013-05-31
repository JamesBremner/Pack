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
    
    virtual ~Bin3D();
        
    void set_x_sub_bin(Bin *value);
    void set_y_sub_bin(Bin *value);
    void set_z_sub_bin(Bin *value);

	virtual void ScaleSize( float f );

    
    void itemsInBin(vector<Item*> &items);
    void binRemSpace(vector<Bin*> &bins);
    double binUtilizationRating();
    void totalChildSpaceUsed( double &used );
    void totalRemSpaceAvailable( double &avail);
    
    double binSpaceUsed();
    double remSpaceAvail();
    
    virtual void encodeAsJSON(stringstream &jsonStr, bool isDeep);
    
    bool operator <( Shape &b);
    bool operator >( Shape &b);
    bool operator ==( Shape &b);
    
protected:
    

};

#endif	/* BIN3D_H */

