/*
 * File:   Shape2D.h
 * Author: arash
 *
 * Created on June 7, 2012, 3:43 PM
 */
#pragma once
#ifndef SHAPE2D_H
#define	ISHAPE2D_H



#endif	/* SHAPE2D_H */

#ifndef NULL
#define NULL   ((void *) 0)
#endif

using namespace std;

class Shape2D : public Shape
{

protected:
    Side *side_1_;
    Side *side_2_;

public:
    Shape2D();
    Shape2D(const Shape2D& orig);
    ~Shape2D();

    Side *side_1();
    void set_side_1(Side *value);
    Side *side_2();
    void set_side_2(Side *value);
    virtual Side * side_3()
    {
        return NULL;
    }

    virtual void ScaleSize( float f );


    virtual Side * origSide1();
    virtual Side * origSide2();
    virtual Side * origSide3()
    {
        return NULL;
    }
    virtual string origSize();


    bool IsSpun()
    {
        return ( side_1_->orig_side() != 'w' );
    }

    double side1size()
    {
        return side_1()->size();
    }
    double side2size()
    {
        return side_2()->size();
    }

    double area();
    virtual bool operator <( Shape &b);
    virtual bool operator >( Shape &b);
    virtual bool operator ==( Shape &b);


};

