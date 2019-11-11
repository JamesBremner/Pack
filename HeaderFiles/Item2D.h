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

    virtual void Spin( int axis );

    double bottom()
    {
        return getHLocation() + side2size();
    }
    double right()
    {
        return getWLocation() + side1size();
    }
    /** Check that item fits inside bin
        @param[in] bin to try fitting inside
        @return true if item fits

        Assumes that any neccessary rotation has taken place
    */
    bool FitsInto( bin_t bin );

    string getSpin();
    virtual void AddToCutList( cCutList& l );
    virtual void DrawList( std::stringstream& ss);
    string getCSV();
    virtual void encodeAsJSON(stringstream &jsonStr);

private:

};

#endif	/* ITEM2D_H */

