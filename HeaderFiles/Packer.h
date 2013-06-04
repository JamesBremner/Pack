/* 
 * File:   Packer.h
 * Author: arash
 *
 * Created on June 13, 2012, 1:45 PM
 */

#ifndef PACKER_H
#define	PACKER_H
using namespace std;

class Packer {

public:

    Packer();
    Packer(const Packer& orig);
    virtual ~Packer();
    
    virtual void packThem( vector<Bin*>& bins, vector<Item*> items) = 0;
    virtual bool packIt( Bin *bin, Item *item, vector<Bin*> &bins ) = 0;


};

#endif	/* PACKER_H */

