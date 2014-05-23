/*
 * File:   Shape.h
 * Author: arash
 *
 * Created on June 15, 2012, 12:51 PM
 */

#ifndef SHAPE_H
#define	SHAPE_H

using namespace std;

class Shape {
public:
    Shape();
    Shape(const Shape& orig);
    virtual ~Shape();

    string id();
    void set_id( string value );
    int progid() { return myID; }

    virtual void set_side_1(Side *value) {};
    virtual void set_side_2(Side *value) {};
    virtual void set_side_3(Side *value) {};

    virtual Side * origSide1() = 0;
    virtual Side * origSide2() = 0;
    virtual Side * origSide3() = 0;
    virtual Side * side_1() = 0;
   virtual Side * side_2() = 0;
   virtual Side * side_3() = 0;

    virtual double volume() { return 0; }

    virtual bool operator <( Shape &b) = 0;
    virtual bool operator >( Shape &b) = 0;
    virtual bool operator ==( Shape &b) = 0;

protected:

    string id_;             /// User's ID
    int myID;               /// Unique ID assigned by program
    static int lastID;       /// last used unique ID

};

#endif	/* SHAPE_H */

