#include "stdafx.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>


using namespace std;

cCut::cCut( double x0, double y0, double x1, double y1 )
{
    if( fabs( x0 - x1 ) < 0.01 )
    {
        myIsVertical = true;
        myIntercept = x0;
        if( y0 < y1 )
        {
            myStart = y0;
            myStop  = y1;
        }
        else
        {
            myStart = y1;
            myStop  = y0;
        }
    }
    else
    {
        myIsVertical = false;
        myIntercept = y0;
        if( x0 < x1 )
        {
            myStart = x0;
            myStop  = x1;
        }
        else
        {
            myStart = x1;
            myStop  = x0;
        }
    }
}
bool cCut::operator==( const cCut& other ) const
{
    if( myIsVertical != other.myIsVertical )
        return false;
    if( fabs ( myIntercept - other.myIntercept ) > 0.01 )
        return false;
    if( fabs ( myStart - other.myStart ) > 0.01 )
        return false;
    if( fabs ( myStop - other.myStop ) > 0.01 )
        return false;
    return true;
}

bool cCut::CanJoin( cCut& joined, const cCut& cut1, const cCut& cut2 )
{
    if( cut1 == cut2 )
    {
        joined = cut1;
        return true;
    }
    if( cut1.myIsVertical != cut2.myIsVertical )
        return false;
    if( fabs ( cut1.myIntercept - cut2.myIntercept ) > 0.01 )
        return false;
    if( fabs( cut1.myStop - cut2.myStart ) < 0.01 )
    {
        joined = cut1;
        joined.myStop = cut2.myStop;
        return true;
    }
    if( fabs( cut2.myStop - cut1.myStart ) < 0.01 )
    {
        joined = cut2;
        joined.myStop = cut1.myStop;
        return true;
    }
    return false;
}



void cCutList::Add( const cCut& cut )
{
    vector < cCut >::iterator it =
        std::find( myCut.begin(), myCut.end(), cut );
    if( it != myCut.end() )
        return;
    myCut.push_back( cut );
}
void cCutList::Join()
{
    bool found = true;
    while( found )
    {
        found = false;
        cCut cut;
        for( vector < cCut >::iterator it1 = myCut.begin();
                it1 != myCut.end(); it1++ )
        {
            for( vector < cCut >::iterator it2 = it1+1;
                    it2 != myCut.end(); it2++ )
            {
                if( cCut::CanJoin( cut, *it1, *it2 ) )
                {

//                    cout << "joining " << it1->get() << " and "
//                        << it2->get() << " making "
//                        << cut.get() << endl;

                    /*  Erase the joined lines

                    Erase second line first
                    So as not to invalidate first iterator

                    */
                    myCut.erase( it2 );
                    myCut.erase( it1 );

                    // add joined line
                    myCut.push_back( cut );

                    found = true;
                    break;
                }
            }
            if( found )
                break;

        }
    }
}
string cCut::get()
{
    stringstream ss;
    if( myIsVertical )
    {
        ss << "( " << myIntercept << "," << myStart << " ) to ( ";
        ss << myIntercept << "," << myStop << " )";
    }
    else
    {
        ss << "( " << myStart << "," << myIntercept << " ) to ( ";
        ss << myStop << "," << myIntercept << " )";
    }
    return ss.str();
}
string cCutList::get()
{
    stringstream ss;
    for( auto& c : myCut )
    {
        ss << c.get() << endl;
    }
    return ss.str();
}
