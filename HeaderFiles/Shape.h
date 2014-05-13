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


    virtual bool operator <( Shape &b) = 0;
    virtual bool operator >( Shape &b) = 0;
    virtual bool operator ==( Shape &b) = 0;

protected:

    string id_;             /// User's ID
    int myID;               /// Unique ID assigned by program
    static int lastID;       /// last used unique ID

};

#endif	/* SHAPE_H */

