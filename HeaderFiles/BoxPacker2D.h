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
    
    virtual void packThem( vector<Bin*>& ref_bins, vector<Item*> items);
    virtual bool packIt( Bin *bin, Item *item, vector<Bin*> &bins );
    virtual void splitBinWidth( Bin *bin, Item *item );
    virtual void splitBinHeight( Bin *bin, Item *item );
   
    
protected:
    
    
    virtual bool checkFitsConstrWidth(Bin *bin, Item *item, vector<Bin*> &bins);
    virtual bool checkFitsConstrHeight(Bin *bin, Item *item, vector<Bin*> &bins);
    virtual bool checkFitsNoConstr(Bin *bin, Item *item, vector<Bin*> &bins );
    
   

};

#endif	/* BOXPACKER2D_H */

