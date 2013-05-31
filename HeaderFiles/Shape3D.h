/* 
 * File:   Shape3D.h
 * Author: arash
 *
 * Created on June 7, 2012, 3:51 PM
 */

#ifndef SHAPE3D_H
#define	SHAPE3D_H

using namespace std;

class Shape3D : virtual public Shape2D
{
    
   
protected:
        
    Side *side_3_;
    
public:   
    
    Shape3D();
    ~Shape3D();
    
    Side *side_3();
    void set_side_3( Side *value );
    
    Side * origSide1();
    Side * origSide2();
    Side * origSide3();
    string origSize();
    
       
    double volume();
    
    virtual bool operator <( Shape &b);
    virtual bool operator >( Shape &b);
    virtual bool operator ==( Shape &b);
    
};

#endif	/* SHAPE3D_H */
