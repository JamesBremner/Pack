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

    
    
    BoxPacker3D();
    BoxPacker3D(const BoxPacker3D& orig);
    virtual ~BoxPacker3D();

    bool packIt( Bin *bin, Item *item, vector<Bin*> &bins );
    

    void splitBinWidth( Bin *bin, Item *item );
    void splitBinHeight( Bin *bin, Item *item );
    void splitBinLength( Bin *bin, Item *item );
   
    
protected:
    
    
    bool checkFitsConstrWidth(Bin *bin, Item *item, vector<Bin*> &bins);
    bool checkFitsConstrHeight(Bin *bin, Item *item, vector<Bin*> &bins);
    bool checkFitsConstrLength(Bin *bin, Item *item, vector<Bin*> &bins);
    bool checkFitsConstrWidthHeight(Bin *bin, Item *item, vector<Bin*> &bins);
    bool checkFitsConstrWidthLength(Bin *bin, Item *item, vector<Bin*> &bins);
    bool checkFitsConstrHeightLength(Bin *bin, Item *item, vector<Bin*> &bins);
    bool checkFitsNoConstr(Bin *bin, Item *item, vector<Bin*> &bins );
    map<string, double> findSubBinSizes(Bin *bin, Item *item);

};

#endif	/* BOXPACKER3D_H */

