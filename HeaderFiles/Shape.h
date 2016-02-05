/*
 * File:   Shape.h
 * Author: arash
 *
 * Created on June 15, 2012, 12:51 PM
 */

#ifndef SHAPE_H
#define	SHAPE_H

using namespace std;

class Shape
{
public:
    Shape();
    Shape(const Shape& orig);
    virtual ~Shape();

    string id();
    void set_id( string value );
    int progid()
    {
        return myID;
    }

    virtual void set_side_1(Side *value) {};
    virtual void set_side_2(Side *value) {};
    virtual void set_side_3(Side *value) {};

    virtual Side * origSide1() = 0;
    virtual Side * origSide2() = 0;
    virtual Side * origSide3() = 0;
    virtual Side * side_1() = 0;
    virtual Side * side_2() = 0;
    virtual Side * side_3() = 0;

    virtual void ScaleSize( float f ) = 0;

    virtual double volume()
    {
        return 0;
    }
    virtual double AreaWidthLength() const
    {
        return 0;
    }
    virtual double OverlapArea( std::shared_ptr<Shape> b )
    {
        return 0;
    }


    virtual bool operator <( Shape &b) = 0;
    virtual bool operator >( Shape &b) = 0;
    virtual bool operator ==( Shape &b) = 0;

    double getWLocation() const
    {
        return myWLocation;
    }
    void setWLocation( double w )
    {
        myWLocation = w;
    }
    double getHLocation() const
    {
        return myHLocation;
    }
    void setHLocation( double h )
    {
        myHLocation = h;
    }
    double getLLocation() const
    {
        return myLLocation;
    }
    void setLLocation( double h )
    {
        myLLocation = h;
    }
    double getWLocation2()
    {
        return myWLocation + side_1()->size();
    }
    double getHLocation2()
    {
        return myHLocation + side_2()->size();
    }
    double getLLocation2()
    {
        return myLLocation + side_3()->size();
    }

    virtual string getSTL( int offset ) { return string(""); }

protected:

    string id_;             /// User's ID
    int myID;               /// Unique ID assigned by program
    static int lastID;       /// last used unique ID

    double  myWLocation;
    double  myHLocation;
    double  myLLocation;

};

#endif	/* SHAPE_H */

