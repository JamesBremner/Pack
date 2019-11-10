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

    double bottom()
    {
        return getHLocation() + side2size();
    }
    double right()
    {
        return getWLocation() + side1size();
    }

    string getSpin();
    virtual void AddToCutList( cCutList& l );
    virtual void DrawList( std::stringstream& ss);
    string getCSV();
    virtual void encodeAsJSON(stringstream &jsonStr);

private:

};

#endif	/* ITEM2D_H */

