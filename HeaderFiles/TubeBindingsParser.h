/* 
 * File:   TubeBindingsParser.h
 * Author: arash
 *
 * Created on July 12, 2012, 9:19 AM
 */

#ifndef TUBEBINDINGSPARSER_H
#define	TUBEBINDINGSPARSER_H

#include "BoxBindingsParser.h"


class TubeBindingsParser : public BoxBindingsParser{
public:
    TubeBindingsParser();
    TubeBindingsParser(const TubeBindingsParser& orig);
    virtual ~TubeBindingsParser();
    
protected:
    
    bool isDimError( int dim );
    Bin *buildBin( string bin_id, vector<string> bin_size_v);
    Item *buildItem( string item_id, vector<string> item_size_v);

};

#endif	/* TUBEBINDINGSPARSER_H */

