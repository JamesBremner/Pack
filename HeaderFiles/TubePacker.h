/* 
 * File:   TubePacker.h
 * Author: arash
 *
 * Created on June 13, 2012, 1:52 PM
 */

#ifndef TUBEPACKER_H
#define	TUBEPACKER_H

#include "Packer.h"


using namespace std;

class TubePacker : public Packer {
public:
    TubePacker();
    TubePacker(const TubePacker& orig);
    virtual ~TubePacker();
    
    void packThem( vector<Bin*> bins, vector<Item*> items);
    bool packIt( Bin *bin, Item *item, vector<Bin*> &bins);
    void splitBinLength( Bin *bin, Item *item );
    
private:

    
};

#endif	/* TUBEPACKER_H */

