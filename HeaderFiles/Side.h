/* 
 * File:   Side.h
 * Author: arash
 *
 * Created on June 7, 2012, 3:34 PM
 */

#ifndef SIDE
#define	SIDE

class Side {

protected:
    
    double size_;
    char orig_side_;
        
    
public:
    
    Side();
    Side( double size, char orig_side );
    ~Side();
    
    double size();
    void set_size( double value);
    char orig_side();
    void set_orig_side( char value);
    
    
    virtual Side *size_side_to( double new_size );
    
};

#endif	/* SIDE*/
