/*
 * File:   Item2D.h
 * Author: arash
 *
 * Created on June 8, 2012, 5:19 PM
 */

#ifndef ITEM2D_H
#define	ITEM2D_H
using namespace std;

class Item2D : public virtual Item
{
public:

    static const int NO_CONSTRAINTS = 0;
    static const int CONSTRAINT_WIDTH = 1;
    static const int CONSTRAINT_HEIGHT = 2;
    Item2D();
    Item2D(const Item& orig);
    virtual ~Item2D();

    virtual void encodeAsJSON(stringstream &jsonStr);

    virtual double getWLocation()
    {
        return myWLocation;
    }
    virtual void setWLocation( double w )
    {
        myWLocation = w;
    }
    virtual double getHLocation()
    {
        return myHLocation;
    }
    virtual void setHLocation( double h )
    {
        myHLocation = h;
    }
    string getSpin()
    {
    stringstream ss;
    ss << side_1_->orig_side() <<side_2_->orig_side();
    return ss.str();
    }
    virtual void AddToCutList( cCutList& l );


private:

};

#endif	/* ITEM2D_H */

