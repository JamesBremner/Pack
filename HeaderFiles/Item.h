/*
 * File:   Item.h
 * Author: arash
 *
 * Created on June 14, 2012, 1:16 PM
 */

#ifndef ITEM_H
#define	ITEM_H
using namespace std;

class Item : public virtual Shape2D
{
public:
    Item();
    Item(const Item& orig);
    virtual ~Item();

    int constraints();
    void set_constraints( int value );
    void setBin( int id )
    {
        myBinProgID = id;
    }
    int getBin() { return myBinProgID; }
    void Print();

    virtual void ScaleSize( float f ) { }

    virtual void encodeAsJSON(stringstream &jsonStr) = 0;

    virtual double getWLocation() = 0;
    virtual void setWLocation( double w ) = 0;
    virtual double getHLocation() = 0;
    virtual void setHLocation( double h ) = 0;
    bool getSpinLocation()  { return mySpinLocation; }
    void setSpinLocation( bool s ) { mySpinLocation = s; }


protected:
    double  myWLocation;
    double  myHLocation;
    bool    mySpinLocation;

private:

    int     constraints_;
    int     myBinProgID;
};

#endif	/* ITEM_H */

