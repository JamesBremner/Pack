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

    virtual void packThem( bin_v_t& ref_bins, item_v_t& items ) = 0;
    virtual bool packIt( bin_t bin, item_t item, bin_v_t &bins ) = 0;


};

#endif	/* PACKER_H */

